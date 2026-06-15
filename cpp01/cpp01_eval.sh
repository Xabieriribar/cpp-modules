#!/usr/bin/env bash
# CPP01 evaluator-style tester for 42 C++ Module 01
# Usage: bash cpp01_eval.sh /path/to/cpp01
# Options:
#   VALGRIND=0 bash cpp01_eval.sh .       # disable valgrind
#   STRICT=1 bash cpp01_eval.sh .         # stricter output checks where possible

set -u

ROOT="${1:-.}"
VALGRIND="${VALGRIND:-1}"
STRICT="${STRICT:-0}"
FAILS=0
WARNS=0
TMPROOT="$(mktemp -d /tmp/cpp01_eval.XXXXXX)"

cleanup() {
    find "$ROOT" -maxdepth 2 -name '.main.cpp.cpp01_eval_backup' -type f | while read -r bak; do
        dir="$(dirname "$bak")"
        mv "$bak" "$dir/main.cpp" 2>/dev/null || true
    done
    rm -rf "$TMPROOT"
}
trap cleanup EXIT INT TERM

ok() { echo "[OK] $*"; }
fail() { echo "[FAIL] $*"; FAILS=$((FAILS + 1)); }
warn() { echo "[WARN] $*"; WARNS=$((WARNS + 1)); }
info() { echo "[INFO] $*"; }

section() {
    echo
    echo "========== $* =========="
}

has_ex() {
    [ -d "$ROOT/$1" ]
}

get_name_from_makefile() {
    awk -F= '
        /^[[:space:]]*NAME[[:space:]]*[?:+]?=/ {
            v=$2
            gsub(/^[[:space:]]+|[[:space:]]+$/, "", v)
            print v
        }
    ' Makefile 2>/dev/null | tail -n 1
}

find_exe() {
    local name
    name="$(get_name_from_makefile)"
    if [ -n "$name" ] && [ -x "./$name" ]; then
        printf '%s\n' "$name"
        return 0
    fi
    # Common CPP01 executable names
    for candidate in megaphone phonebook zombie horde brain violence replace harl harlFilter; do
        if [ -x "./$candidate" ]; then
            printf '%s\n' "$candidate"
            return 0
        fi
    done
    # Fallback: first executable regular file in exercise directory
    for f in ./*; do
        [ -f "$f" ] || continue
        [ -x "$f" ] || continue
        case "$f" in
            *.o|*.a|*.so|*.dylib|*.sh) continue ;;
        esac
        basename "$f"
        return 0
    done
    return 1
}

build_ex() {
    local dir="$1"
    (
        cd "$dir" || exit 99
        if [ ! -f Makefile ]; then
            echo "NO_MAKEFILE"
            exit 2
        fi
        make fclean >/dev/null 2>&1 || true
        if make re > "$TMPROOT/make.out" 2> "$TMPROOT/make.err"; then
            exit 0
        fi
        if make > "$TMPROOT/make.out" 2> "$TMPROOT/make.err"; then
            exit 0
        fi
        exit 1
    )
    local status=$?
    if [ "$status" -eq 0 ]; then
        ok "Compiles with Makefile"
        return 0
    fi
    if [ "$status" -eq 2 ]; then
        fail "$dir: Makefile missing"
    else
        fail "$dir: compilation failed"
        sed -n '1,120p' "$TMPROOT/make.out" 2>/dev/null || true
        sed -n '1,120p' "$TMPROOT/make.err" 2>/dev/null || true
    fi
    return 1
}

run_program() {
    local dir="$1"; shift
    local exe="$1"; shift
    local input_file="${1:-}"
    [ "$#" -eq 0 ] || shift
    local out="$TMPROOT/stdout.txt"
    local err="$TMPROOT/stderr.txt"
    : > "$out"
    : > "$err"
    (
        cd "$dir" || exit 99
        if [ -n "$input_file" ]; then
            timeout 8s "./$exe" "$@" < "$input_file" > "$out" 2> "$err"
        else
            timeout 8s "./$exe" "$@" > "$out" 2> "$err"
        fi
    )
    local code=$?
    if [ "$code" -eq 0 ]; then
        ok "Program exits with code 0"
        return 0
    fi
    if [ "$code" -eq 124 ]; then
        fail "Program timed out"
    else
        fail "Program returned non-zero or crashed: $code"
    fi
    echo "--- stdout ---"
    sed -n '1,120p' "$out" || true
    echo "--- stderr ---"
    sed -n '1,120p' "$err" || true
    return 1
}

run_valgrind() {
    local dir="$1"; shift
    local exe="$1"; shift
    local input_file="${1:-}"
    [ "$#" -eq 0 ] || shift
    local vg="$TMPROOT/valgrind.txt"
    if [ "$VALGRIND" = "0" ]; then
        info "Valgrind disabled"
        return 0
    fi
    if ! command -v valgrind >/dev/null 2>&1; then
        warn "Valgrind not installed; skipped"
        return 0
    fi
    (
        cd "$dir" || exit 99
        if [ -n "$input_file" ]; then
            timeout 20s valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=42 "./$exe" "$@" < "$input_file" > /dev/null 2> "$vg"
        else
            timeout 20s valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=42 "./$exe" "$@" > /dev/null 2> "$vg"
        fi
    )
    local code=$?
    if [ "$code" -eq 0 ]; then
        ok "Valgrind: no reported leaks/errors"
        return 0
    fi
    fail "Valgrind reported leaks/errors or program crashed"
    sed -n '1,160p' "$vg" || true
    return 1
}

backup_main() {
    local dir="$1"
    if [ ! -f "$dir/main.cpp" ]; then
        fail "$dir: main.cpp missing"
        return 1
    fi
    if [ ! -f "$dir/.main.cpp.cpp01_eval_backup" ]; then
        cp "$dir/main.cpp" "$dir/.main.cpp.cpp01_eval_backup"
    fi
    return 0
}

restore_main() {
    local dir="$1"
    if [ -f "$dir/.main.cpp.cpp01_eval_backup" ]; then
        mv "$dir/.main.cpp.cpp01_eval_backup" "$dir/main.cpp"
    fi
}

write_main() {
    local dir="$1"
    backup_main "$dir" || return 1
    cat > "$dir/main.cpp"
}

check_makefile_flags() {
    local dir="$1"
    if [ ! -f "$dir/Makefile" ]; then
        fail "$dir: Makefile missing"
        return
    fi
    grep -Eq -- '-Wall' "$dir/Makefile" && ok "$dir: Makefile has -Wall" || fail "$dir: Makefile missing -Wall"
    grep -Eq -- '-Wextra' "$dir/Makefile" && ok "$dir: Makefile has -Wextra" || fail "$dir: Makefile missing -Wextra"
    grep -Eq -- '-Werror' "$dir/Makefile" && ok "$dir: Makefile has -Werror" || fail "$dir: Makefile missing -Werror"
    grep -Eq -- '-std=c\+\+98' "$dir/Makefile" && ok "$dir: Makefile has -std=c++98" || warn "$dir: Makefile does not visibly include -std=c++98"
}

forbidden_scan_common() {
    local dir="$1"
    [ -d "$dir" ] || return
    local res="$TMPROOT/forbidden.txt"
    grep -RInE \
        'using[[:space:]]+namespace|\bfriend\b|\bprintf[[:space:]]*\(|\bmalloc[[:space:]]*\(|\bcalloc[[:space:]]*\(|\brealloc[[:space:]]*\(|\bfree[[:space:]]*\(|#include[[:space:]]*< *(vector|list|map|deque|set|algorithm) *>' \
        "$dir" --include='*.cpp' --include='*.hpp' --include='*.h' > "$res" 2>/dev/null || true
    if [ -s "$res" ]; then
        fail "$dir: forbidden or suspicious construct found"
        sed -n '1,80p' "$res"
    else
        ok "$dir: common forbidden scan clean"
    fi
}

contains_line() {
    local file="$1" pattern="$2" desc="$3"
    if grep -Fxq "$pattern" "$file"; then
        ok "$desc"
    else
        fail "$desc"
        echo "Expected exact line: $pattern"
        echo "Actual output:"
        sed -n '1,80p' "$file"
    fi
}

compile_extra() {
    local dir="$1" src="$2" outbin="$3"
    (
        cd "$dir" || exit 99
        c++ -Wall -Wextra -Werror -std=c++98 "$src" *.cpp -o "$outbin" > "$TMPROOT/extra_make.out" 2> "$TMPROOT/extra_make.err"
    )
}

# ---------------- ex00 ----------------
test_ex00() {
    local dir="$ROOT/ex00"
    section "ex00 BraiiiiiiinnnzzzZ"
    if [ ! -d "$dir" ]; then warn "ex00 missing; skipped"; return; fi
    check_makefile_flags "$dir"
    forbidden_scan_common "$dir"

    write_main "$dir" <<'CPP'
#include <iostream>
#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main()
{
    std::cout << "--- randomChump ---" << std::endl;
    randomChump("Stacky");

    std::cout << "--- newZombie ---" << std::endl;
    Zombie* heap = newZombie("Heapy");
    if (!heap)
    {
        std::cout << "FAIL_NULL" << std::endl;
        return 1;
    }
    heap->announce();
    delete heap;
    std::cout << "DONE" << std::endl;
    return 0;
}
CPP
    if build_ex "$dir"; then
        local exe
        exe="$(cd "$dir" && find_exe)" || { fail "ex00: executable not found"; restore_main "$dir"; return; }
        if run_program "$dir" "$exe" ""; then
            contains_line "$TMPROOT/stdout.txt" "Stacky: BraiiiiiiinnnzzzZ..." "randomChump announces exact text"
            contains_line "$TMPROOT/stdout.txt" "Heapy: BraiiiiiiinnnzzzZ..." "newZombie announces exact text"
            grep -qi 'Stacky.*destr\|Stacky.*destroy\|Stacky.*dead\|Stacky.*delete' "$TMPROOT/stdout.txt" && ok "Stack zombie destructor mentions its name" || warn "Could not detect destructor message mentioning Stacky"
            grep -qi 'Heapy.*destr\|Heapy.*destroy\|Heapy.*dead\|Heapy.*delete' "$TMPROOT/stdout.txt" && ok "Heap zombie destructor mentions its name" || warn "Could not detect destructor message mentioning Heapy"
        fi
        run_valgrind "$dir" "$exe" ""
    fi
    restore_main "$dir"
}

# ---------------- ex01 ----------------
test_ex01() {
    local dir="$ROOT/ex01"
    section "ex01 Moar brainz!"
    if [ ! -d "$dir" ]; then warn "ex01 missing; skipped"; return; fi
    check_makefile_flags "$dir"
    forbidden_scan_common "$dir"

    # Static single-allocation heuristic
    local zh
    zh="$(grep -RIl 'zombieHorde' "$dir" --include='*.cpp' | head -n 1)"
    if [ -n "$zh" ]; then
        grep -Eq 'new[[:space:]]+Zombie[[:space:]]*\[' "$zh" && ok "zombieHorde appears to use new Zombie[N]" || warn "Could not detect single allocation new Zombie[N] in zombieHorde source"
        grep -RInE 'new[[:space:]]+Zombie[[:space:]]*\(' "$dir" --include='*.cpp' >/dev/null && warn "Detected possible per-zombie new; horde must be one allocation" || ok "No obvious per-zombie new detected"
    fi

    write_main "$dir" <<'CPP'
#include <iostream>
#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name);

int main()
{
    int N = 5;
    Zombie* horde = zombieHorde(N, "HordeName");
    if (!horde)
    {
        std::cout << "FAIL_NULL" << std::endl;
        return 1;
    }
    for (int i = 0; i < N; ++i)
        horde[i].announce();
    delete [] horde;
    std::cout << "DONE" << std::endl;
    return 0;
}
CPP
    if build_ex "$dir"; then
        local exe
        exe="$(cd "$dir" && find_exe)" || { fail "ex01: executable not found"; restore_main "$dir"; return; }
        if run_program "$dir" "$exe" ""; then
            local count
            count="$(grep -Fc 'HordeName: BraiiiiiiinnnzzzZ...' "$TMPROOT/stdout.txt" || true)"
            [ "$count" -eq 5 ] && ok "All 5 horde zombies announce exact text" || fail "Expected 5 exact horde announcements, got $count"
        fi
        run_valgrind "$dir" "$exe" ""
    fi
    restore_main "$dir"
}

# ---------------- ex02 ----------------
test_ex02() {
    local dir="$ROOT/ex02"
    section "ex02 HI THIS IS BRAIN"
    if [ ! -d "$dir" ]; then warn "ex02 missing; skipped"; return; fi
    check_makefile_flags "$dir"
    forbidden_scan_common "$dir"
    if build_ex "$dir"; then
        local exe
        exe="$(cd "$dir" && find_exe)" || { fail "ex02: executable not found"; return; }
        if run_program "$dir" "$exe" ""; then
            local val_count addr_count unique_addr_count
            val_count="$(grep -o 'HI THIS IS BRAIN' "$TMPROOT/stdout.txt" | wc -l | tr -d ' ')"
            [ "$val_count" -ge 3 ] && ok "Prints the string value at least 3 times" || fail "Expected the value HI THIS IS BRAIN at least 3 times"
            grep -Eo '0x[0-9a-fA-F]+' "$TMPROOT/stdout.txt" > "$TMPROOT/addrs.txt" || true
            addr_count="$(wc -l < "$TMPROOT/addrs.txt" | tr -d ' ')"
            unique_addr_count="$(sort -u "$TMPROOT/addrs.txt" | wc -l | tr -d ' ')"
            if [ "$addr_count" -ge 3 ] && [ "$unique_addr_count" -eq 1 ]; then
                ok "The 3 printed addresses look identical"
            elif [ "$addr_count" -ge 3 ]; then
                fail "Expected the 3 printed addresses to be identical"
                cat "$TMPROOT/addrs.txt"
            else
                warn "Could not reliably parse 3 hexadecimal addresses"
            fi
        fi
        run_valgrind "$dir" "$exe" ""
    fi
}

# ---------------- ex03 ----------------
test_ex03() {
    local dir="$ROOT/ex03"
    section "ex03 Unnecessary violence"
    if [ ! -d "$dir" ]; then warn "ex03 missing; skipped"; return; fi
    check_makefile_flags "$dir"
    forbidden_scan_common "$dir"

    write_main "$dir" <<'CPP'
#include <iostream>
#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    {
        Weapon club = Weapon("crude spiked club");
        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }
    {
        HumanB empty("EmptyJim");
        empty.attack();
    }
    return 0;
}
CPP
    if build_ex "$dir"; then
        local exe
        exe="$(cd "$dir" && find_exe)" || { fail "ex03: executable not found"; restore_main "$dir"; return; }
        if run_program "$dir" "$exe" ""; then
            contains_line "$TMPROOT/stdout.txt" "Bob attacks with their crude spiked club" "HumanA initial weapon output exact"
            contains_line "$TMPROOT/stdout.txt" "Bob attacks with their some other type of club" "HumanA sees changed weapon type"
            contains_line "$TMPROOT/stdout.txt" "Jim attacks with their crude spiked club" "HumanB initial weapon output exact"
            contains_line "$TMPROOT/stdout.txt" "Jim attacks with their some other type of club" "HumanB sees changed weapon type"
            ok "HumanB without weapon did not crash"
        fi
        run_valgrind "$dir" "$exe" ""
    fi
    restore_main "$dir"
}

# ---------------- ex04 ----------------
test_ex04() {
    local dir="$ROOT/ex04"
    section "ex04 Sed is for losers"
    if [ ! -d "$dir" ]; then warn "ex04 missing; skipped"; return; fi
    check_makefile_flags "$dir"
    forbidden_scan_common "$dir"

    local res="$TMPROOT/ex04_forbidden.txt"
    grep -RInE '\.replace[[:space:]]*\(|std::string::replace' "$dir" --include='*.cpp' --include='*.hpp' --include='*.h' > "$res" 2>/dev/null || true
    if [ -s "$res" ]; then
        fail "ex04 uses std::string::replace or .replace(), forbidden by subject"
        sed -n '1,80p' "$res"
    else
        ok "ex04: no visible std::string::replace usage"
    fi
    grep -RInE '\bfopen[[:space:]]*\(|\bfclose[[:space:]]*\(|\bfread[[:space:]]*\(|\bfwrite[[:space:]]*\(|\bfprintf[[:space:]]*\(|\bprintf[[:space:]]*\(' "$dir" --include='*.cpp' --include='*.hpp' --include='*.h' > "$res" 2>/dev/null || true
    if [ -s "$res" ]; then
        fail "ex04 appears to use C file functions"
        sed -n '1,80p' "$res"
    else
        ok "ex04: no visible C stdio file functions"
    fi

    if build_ex "$dir"; then
        local exe
        exe="$(cd "$dir" && find_exe)" || { fail "ex04: executable not found"; return; }
        local work="$TMPROOT/ex04_work"
        mkdir -p "$work"
        printf 'abc abc\nxxxabcxxx\nnochange\n' > "$work/input.txt"
        (
            cd "$dir" || exit 99
            rm -f "$work/input.txt.replace"
            timeout 8s "./$exe" "$work/input.txt" "abc" "XYZ" > "$TMPROOT/stdout.txt" 2> "$TMPROOT/stderr.txt"
        )
        if [ $? -eq 0 ]; then
            ok "replacement program exits with code 0"
            printf 'XYZ XYZ\nxxxXYZxxx\nnochange\n' > "$TMPROOT/expected.txt"
            if diff -u "$TMPROOT/expected.txt" "$work/input.txt.replace" > "$TMPROOT/diff.txt" 2>&1; then
                ok "basic replacement output exact"
            else
                fail "basic replacement output differs"
                cat "$TMPROOT/diff.txt"
            fi
        else
            fail "replacement program failed on basic case"
            sed -n '1,80p' "$TMPROOT/stderr.txt"
        fi

        printf 'aaaa\naa\na\n' > "$work/overlap.txt"
        (
            cd "$dir" || exit 99
            rm -f "$work/overlap.txt.replace"
            timeout 8s "./$exe" "$work/overlap.txt" "aa" "b" > /dev/null 2> "$TMPROOT/stderr.txt"
        )
        if [ $? -eq 0 ]; then
            printf 'bb\nb\na\n' > "$TMPROOT/expected_overlap.txt"
            diff -u "$TMPROOT/expected_overlap.txt" "$work/overlap.txt.replace" > "$TMPROOT/diff.txt" 2>&1 && ok "non-overlapping repeated replacement works" || { fail "overlap replacement differs"; cat "$TMPROOT/diff.txt"; }
        else
            fail "replacement program failed on overlap case"
        fi

        (
            cd "$dir" || exit 99
            timeout 3s "./$exe" "$work/input.txt" "" "X" > "$TMPROOT/empty_s1.out" 2> "$TMPROOT/empty_s1.err"
        )
        local code=$?
        if [ "$code" -eq 124 ]; then
            fail "empty s1 causes timeout/infinite loop"
        else
            ok "empty s1 handled without infinite loop"
        fi
        run_valgrind "$dir" "$exe" "" "$work/input.txt" "abc" "XYZ"
    fi
}

# ---------------- ex05 ----------------
test_ex05() {
    local dir="$ROOT/ex05"
    section "ex05 Harl 2.0"
    if [ ! -d "$dir" ]; then warn "ex05 missing; skipped"; return; fi
    check_makefile_flags "$dir"
    forbidden_scan_common "$dir"

    local res="$TMPROOT/harl_static.txt"
    grep -RInE '::\*|\(.*\*.*\)' "$dir/Harl.cpp" "$dir/Harl.hpp" "$dir/Harl.h" 2>/dev/null > "$res" || true
    if [ -s "$res" ]; then
        ok "Harl appears to use pointers to member functions"
    else
        warn "Could not detect pointer-to-member-function syntax in Harl"
    fi
    local if_count
    if_count="$(grep -RInE '\bif[[:space:]]*\(' "$dir" --include='*.cpp' --include='*.hpp' --include='*.h' 2>/dev/null | wc -l | tr -d ' ')"
    [ "$if_count" -le 2 ] && ok "No obvious forest of if/else detected" || warn "Many if statements detected; subject asks no forest of if/else for Harl"

    write_main "$dir" <<'CPP'
#include <iostream>
#include "Harl.hpp"

int main()
{
    Harl harl;
    std::cout << "---DEBUG---" << std::endl;
    harl.complain("DEBUG");
    std::cout << "---INFO---" << std::endl;
    harl.complain("INFO");
    std::cout << "---WARNING---" << std::endl;
    harl.complain("WARNING");
    std::cout << "---ERROR---" << std::endl;
    harl.complain("ERROR");
    std::cout << "---UNKNOWN---" << std::endl;
    harl.complain("UNKNOWN");
    return 0;
}
CPP
    if build_ex "$dir"; then
        local exe
        exe="$(cd "$dir" && find_exe)" || { fail "ex05: executable not found"; restore_main "$dir"; return; }
        if run_program "$dir" "$exe" ""; then
            grep -q -- '---DEBUG---' "$TMPROOT/stdout.txt" && ok "DEBUG test reached" || fail "DEBUG marker missing"
            grep -q -- '---INFO---' "$TMPROOT/stdout.txt" && ok "INFO test reached" || fail "INFO marker missing"
            grep -q -- '---WARNING---' "$TMPROOT/stdout.txt" && ok "WARNING test reached" || fail "WARNING marker missing"
            grep -q -- '---ERROR---' "$TMPROOT/stdout.txt" && ok "ERROR test reached" || fail "ERROR marker missing"
            grep -qi 'debug' "$TMPROOT/stdout.txt" && ok "Some DEBUG output detected" || warn "No DEBUG-like text detected"
            grep -qi 'info' "$TMPROOT/stdout.txt" && ok "Some INFO output detected" || warn "No INFO-like text detected"
            grep -qi 'warning' "$TMPROOT/stdout.txt" && ok "Some WARNING output detected" || warn "No WARNING-like text detected"
            grep -qi 'error' "$TMPROOT/stdout.txt" && ok "Some ERROR output detected" || warn "No ERROR-like text detected"
        fi
        run_valgrind "$dir" "$exe" ""
    fi
    restore_main "$dir"
}

# ---------------- ex06 ----------------
test_ex06() {
    local dir="$ROOT/ex06"
    section "ex06 Harl filter"
    if [ ! -d "$dir" ]; then warn "ex06 missing; skipped. It is optional in the subject."; return; fi
    check_makefile_flags "$dir"
    forbidden_scan_common "$dir"
    grep -RInE '\bswitch[[:space:]]*\(' "$dir" --include='*.cpp' --include='*.hpp' --include='*.h' >/dev/null 2>&1 && ok "switch statement detected" || fail "No switch statement detected; ex06 requires switch"

    if build_ex "$dir"; then
        local exe
        if [ -x "$dir/harlFilter" ]; then
            exe="harlFilter"
            ok "Executable is named harlFilter"
        else
            exe="$(cd "$dir" && find_exe)" || { fail "ex06: executable not found"; return; }
            fail "Executable should be named harlFilter, found/use: $exe"
        fi

        # WARNING: should include WARNING and ERROR, not DEBUG/INFO markers
        run_program "$dir" "$exe" "" "WARNING" || true
        grep -q '\[ WARNING \]' "$TMPROOT/stdout.txt" && ok "WARNING filter prints WARNING block" || fail "WARNING block missing"
        grep -q '\[ ERROR \]' "$TMPROOT/stdout.txt" && ok "WARNING filter prints ERROR block" || fail "ERROR block missing after WARNING"
        grep -q '\[ DEBUG \]' "$TMPROOT/stdout.txt" && fail "WARNING filter should not print DEBUG" || ok "WARNING filter does not print DEBUG"
        grep -q '\[ INFO \]' "$TMPROOT/stdout.txt" && fail "WARNING filter should not print INFO" || ok "WARNING filter does not print INFO"

        run_program "$dir" "$exe" "" "ERROR" || true
        grep -q '\[ ERROR \]' "$TMPROOT/stdout.txt" && ok "ERROR filter prints ERROR block" || fail "ERROR block missing"
        grep -q '\[ WARNING \]' "$TMPROOT/stdout.txt" && fail "ERROR filter should not print WARNING" || ok "ERROR filter does not print WARNING"

        run_program "$dir" "$exe" "" "DEBUG" || true
        grep -q '\[ DEBUG \]' "$TMPROOT/stdout.txt" && grep -q '\[ INFO \]' "$TMPROOT/stdout.txt" && grep -q '\[ WARNING \]' "$TMPROOT/stdout.txt" && grep -q '\[ ERROR \]' "$TMPROOT/stdout.txt" \
            && ok "DEBUG filter prints all levels" || fail "DEBUG filter should print all levels"

        run_program "$dir" "$exe" "" "I am not sure how tired I am today..." || true
        grep -q 'Probably complaining about insignificant problems' "$TMPROOT/stdout.txt" && ok "Invalid level prints default insignificant-problems message" || fail "Invalid level default message missing"

        run_valgrind "$dir" "$exe" "" "WARNING"
    fi
}

# ---------------- global checks ----------------
global_layout_check() {
    section "Global CPP01 layout"
    [ -d "$ROOT" ] || { fail "Root path not found: $ROOT"; return; }
    for ex in ex00 ex01 ex02 ex03 ex04 ex05 ex06; do
        if [ -d "$ROOT/$ex" ]; then
            ok "$ex directory exists"
        else
            if [ "$ex" = "ex06" ]; then warn "$ex directory missing; optional"; else fail "$ex directory missing"; fi
        fi
    done
}

global_layout_check
test_ex00
test_ex01
test_ex02
test_ex03
test_ex04
test_ex05
test_ex06

section "SUMMARY"
if [ "$FAILS" -eq 0 ]; then
    echo "All mandatory checks passed. Warnings: $WARNS"
else
    echo "$FAILS failure(s). Warnings: $WARNS"
fi
exit "$FAILS"
