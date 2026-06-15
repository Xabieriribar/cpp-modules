#!/usr/bin/env bash
# CPP00 evaluator-style tester for ex00/ex01/ex02.
# Usage: bash cpp00_eval_fixed.sh /path/to/cpp00
# Optional: VALGRIND=0 bash cpp00_eval_fixed.sh .

set -u

ROOT="${1:-.}"
ROOT="$(cd "$ROOT" 2>/dev/null && pwd)" || { echo "Invalid path: ${1:-.}"; exit 1; }
VALGRIND="${VALGRIND:-1}"

checks=0
failures=0
warnings=0
TMPDIR="$(mktemp -d /tmp/cpp00_eval.XXXXXX)"

cleanup() { rm -rf "$TMPDIR"; }
trap cleanup EXIT

section() { printf '\n========== %s ==========%s' "$1" "\n"; }
ok() { checks=$((checks+1)); echo "[OK] $1"; }
fail() { checks=$((checks+1)); failures=$((failures+1)); echo "[FAIL] $1"; }
warn() { warnings=$((warnings+1)); echo "[WARN] $1"; }

require_dir() {
    [ -d "$ROOT/$1" ] || { fail "$1 directory exists"; return 1; }
    ok "$1 directory exists"
    return 0
}

get_exe() {
    local dir="$1" name
    name="$(awk -F= '/^[[:space:]]*NAME[[:space:]]*=/{gsub(/[[:space:]]/,"",$2); print $2}' "$dir/Makefile" 2>/dev/null | tail -n 1)"
    if [ -n "$name" ] && [ -x "$dir/$name" ]; then
        echo "$name"
        return 0
    fi
    # fallback: first executable file in exercise dir, excluding .o and scripts
    find "$dir" -maxdepth 1 -type f -perm -111 \
        ! -name '*.o' ! -name '*.sh' ! -name 'Makefile' -printf '%f\n' 2>/dev/null | head -n 1
}

make_re() {
    local dir="$1"
    ( cd "$dir" && make fclean >/dev/null 2>&1; make re >"$TMPDIR/make.out" 2>&1 )
    local st=$?
    if [ $st -eq 0 ]; then
        ok "$(basename "$dir") compiles with Makefile"
        return 0
    fi
    fail "$(basename "$dir") compilation failed"
    sed -n '1,160p' "$TMPDIR/make.out"
    return 1
}

run_vg() {
    local dir="$1" exe="$2" input_file="${3:-}"
    if [ "$VALGRIND" = "0" ]; then
        warn "Valgrind disabled for $(basename "$dir")"
        return 0
    fi
    if ! command -v valgrind >/dev/null 2>&1; then
        warn "Valgrind not installed; skipped for $(basename "$dir")"
        return 0
    fi
    if [ -n "$input_file" ]; then
        ( cd "$dir" && valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=97 "./$exe" < "$input_file" >"$TMPDIR/vg.out" 2>"$TMPDIR/vg.err" )
    else
        ( cd "$dir" && valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=97 "./$exe" >"$TMPDIR/vg.out" 2>"$TMPDIR/vg.err" )
    fi
    local st=$?
    if [ $st -eq 0 ]; then
        ok "$(basename "$dir") Valgrind: no reported errors"
    else
        fail "$(basename "$dir") Valgrind reported errors/leaks"
        sed -n '1,180p' "$TMPDIR/vg.err"
    fi
}

general_scan() {
    local ex="$1"
    local dir="$ROOT/$1"
    local out="$TMPDIR/${ex}_scan.out"
    # Do not scan ex02/tests.cpp for vector/algorithm: it is supplied by the subject/intranet.
    find "$dir" -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) \
        ! -path "$dir/tests.cpp" \
        -exec grep -nE 'using[[:space:]]+namespace|\bfriend\b|printf[[:space:]]*\(|malloc[[:space:]]*\(|calloc[[:space:]]*\(|realloc[[:space:]]*\(|free[[:space:]]*\(|#include[[:space:]]*<vector>|#include[[:space:]]*<list>|#include[[:space:]]*<map>|#include[[:space:]]*<algorithm>' {} + > "$out" 2>/dev/null
    if [ -s "$out" ]; then
        fail "$ex forbidden/general-rule scan is clean"
        cat "$out"
    else
        ok "$ex forbidden/general-rule scan is clean"
    fi
}

check_make_flags() {
    local ex="$1"
    local mf="$ROOT/$ex/Makefile"
    if [ ! -f "$mf" ]; then fail "$ex Makefile exists"; return; fi
    ok "$ex Makefile exists"
    local txt; txt="$(tr '\n' ' ' < "$mf")"
    echo "$txt" | grep -q -- '-Wall' && echo "$txt" | grep -q -- '-Wextra' && echo "$txt" | grep -q -- '-Werror'
    if [ $? -eq 0 ]; then ok "$ex Makefile has -Wall -Wextra -Werror"; else fail "$ex Makefile has -Wall -Wextra -Werror"; fi
    echo "$txt" | grep -q -- '-std=c++98'
    if [ $? -eq 0 ]; then ok "$ex Makefile has -std=c++98"; else warn "$ex Makefile does not visibly include -std=c++98; subject says it must still compile with it"; fi
}

normalize_ts() {
    # Replaces [YYYYMMDD_HHMMSS] by [timestamp]
    sed -E 's/^\[[0-9]{8}_[0-9]{6}\]/[timestamp]/'
}

run_ex00() {
    section "ex00 Megaphone"
    require_dir ex00 || return
    local dir="$ROOT/ex00"
    [ -f "$dir/megaphone.cpp" ] && ok "required file exists: megaphone.cpp" || fail "required file exists: megaphone.cpp"
    check_make_flags ex00
    general_scan ex00
    make_re "$dir" || return
    local exe; exe="$(get_exe "$dir")"
    if [ -z "$exe" ]; then fail "ex00 executable found"; return; fi
    ok "ex00 executable: $exe"

    local out exp
    out="$(cd "$dir" && "./$exe")"
    exp='* LOUD AND UNBEARABLE FEEDBACK NOISE *'
    [ "$out" = "$exp" ] && ok "no-argument feedback output is exact" || { fail "no-argument feedback output is exact"; printf 'Expected: <%s>\nActual:   <%s>\n' "$exp" "$out"; }

    out="$(cd "$dir" && "./$exe" "shhhhh... I think the students are asleep...")"
    exp='SHHHHH... I THINK THE STUDENTS ARE ASLEEP...'
    [ "$out" = "$exp" ] && ok "single argument uppercase output is exact" || { fail "single argument uppercase output is exact"; printf 'Expected: <%s>\nActual:   <%s>\n' "$exp" "$out"; }

    out="$(cd "$dir" && "./$exe" Damnit " ! " "Sorry students, I thought this thing was off.")"
    exp='DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.'
    [ "$out" = "$exp" ] && ok "multiple argument uppercase concatenation is exact" || { fail "multiple argument uppercase concatenation is exact"; printf 'Expected: <%s>\nActual:   <%s>\n' "$exp" "$out"; }

    out="$(cd "$dir" && "./$exe" "aBc123!?" " xyz")"
    exp='ABC123!? XYZ'
    [ "$out" = "$exp" ] && ok "letters uppercase while punctuation/digits stay unchanged" || { fail "letters uppercase while punctuation/digits stay unchanged"; printf 'Expected: <%s>\nActual:   <%s>\n' "$exp" "$out"; }

    run_vg "$dir" "$exe"
}

run_ex01() {
    section "ex01 PhoneBook"
    require_dir ex01 || return
    local dir="$ROOT/ex01"
    check_make_flags ex01
    general_scan ex01
    for f in Makefile; do [ -f "$dir/$f" ] && ok "required file exists: $f" || fail "required file exists: $f"; done
    find "$dir" -maxdepth 1 -type f \( -name '*.cpp' -o -name '*.hpp' -o -name '*.h' \) | grep -q . && ok "ex01 has cpp/header files" || fail "ex01 has cpp/header files"

    local alloc_out="$TMPDIR/ex01_alloc.out"
    grep -RInE '\bnew\b|\bdelete\b|malloc[[:space:]]*\(|calloc[[:space:]]*\(|realloc[[:space:]]*\(|free[[:space:]]*\(' "$dir" --include='*.cpp' --include='*.hpp' --include='*.h' > "$alloc_out" 2>/dev/null
    if [ -s "$alloc_out" ]; then
        fail "ex01 has no visible dynamic allocation"
        cat "$alloc_out"
    else
        ok "ex01 has no visible dynamic allocation"
    fi

    make_re "$dir" || return
    local exe; exe="$(get_exe "$dir")"
    if [ -z "$exe" ]; then fail "ex01 executable found"; return; fi
    ok "ex01 executable: $exe"

    # Basic ADD + SEARCH with index 0. Most 42 implementations display indexes 0..7.
    cat > "$TMPDIR/ex01_input_basic.txt" <<'IN'
ADD
Alice
Wonder
Ally
12345
rabbit hole
SEARCH
0
EXIT
IN
    ( cd "$dir" && timeout 5s "./$exe" < "$TMPDIR/ex01_input_basic.txt" > "$TMPDIR/ex01_basic.out" 2> "$TMPDIR/ex01_basic.err" )
    local st=$?
    if [ $st -eq 0 ]; then ok "ex01 ADD/SEARCH/EXIT exits normally"; else fail "ex01 ADD/SEARCH/EXIT exits normally"; cat "$TMPDIR/ex01_basic.err"; fi
    grep -q 'Alice' "$TMPDIR/ex01_basic.out" && ok "ex01 SEARCH output includes first name" || fail "ex01 SEARCH output includes first name"
    grep -q 'Wonder' "$TMPDIR/ex01_basic.out" && ok "ex01 SEARCH output includes last name" || fail "ex01 SEARCH output includes last name"
    grep -q 'Ally' "$TMPDIR/ex01_basic.out" && ok "ex01 SEARCH output includes nickname" || fail "ex01 SEARCH output includes nickname"
    grep -q 'rabbit hole' "$TMPDIR/ex01_basic.out" && ok "ex01 detailed contact can display darkest secret" || warn "darkest secret not found; maybe index base is 1 or output labels differ"

    # Truncation test: table should truncate long field to 9 chars + dot somewhere.
    cat > "$TMPDIR/ex01_input_trunc.txt" <<'IN'
ADD
VeryLongFirstname
VeryLongLastname
VeryLongNickname
111
secret
SEARCH
0
EXIT
IN
    ( cd "$dir" && timeout 5s "./$exe" < "$TMPDIR/ex01_input_trunc.txt" > "$TMPDIR/ex01_trunc.out" 2>/dev/null )
    if grep -Eq 'VeryLongF\.|VeryLongL\.|VeryLongN\.' "$TMPDIR/ex01_trunc.out"; then
        ok "ex01 table truncates long fields with dot"
    else
        fail "ex01 table truncates long fields with dot"
        sed -n '1,120p' "$TMPDIR/ex01_trunc.out"
    fi

    # 9th contact should replace oldest. Use distinctive names short enough not to truncate.
    : > "$TMPDIR/ex01_input_9.txt"
    for i in 1 2 3 4 5 6 7 8 9; do
        cat >> "$TMPDIR/ex01_input_9.txt" <<IN
ADD
F$i
L$i
N$i
$i$i$i
S$i
IN
    done
    cat >> "$TMPDIR/ex01_input_9.txt" <<'IN'
SEARCH
0
EXIT
IN
    ( cd "$dir" && timeout 5s "./$exe" < "$TMPDIR/ex01_input_9.txt" > "$TMPDIR/ex01_9.out" 2>/dev/null )
    grep -q 'F9' "$TMPDIR/ex01_9.out" && ok "ex01 adding 9 contacts keeps the 9th contact" || fail "ex01 adding 9 contacts keeps the 9th contact"
    if grep -q 'F1' "$TMPDIR/ex01_9.out"; then
        fail "ex01 oldest contact is replaced after 9th ADD"
    else
        ok "ex01 oldest contact is replaced after 9th ADD"
    fi

    run_vg "$dir" "$exe" "$TMPDIR/ex01_input_basic.txt"
}

run_ex02() {
    section "ex02 Account"
    require_dir ex02 || return
    local dir="$ROOT/ex02"
    for f in Makefile Account.cpp Account.hpp tests.cpp; do [ -f "$dir/$f" ] && ok "required file exists: $f" || fail "required file exists: $f"; done
    check_make_flags ex02
    general_scan ex02
    make_re "$dir" || return
    local exe; exe="$(get_exe "$dir")"
    if [ -z "$exe" ]; then fail "ex02 executable found"; return; fi
    ok "ex02 executable: $exe"

    ( cd "$dir" && "./$exe" > "$TMPDIR/ex02.out" 2> "$TMPDIR/ex02.err" )
    local st=$?
    [ $st -eq 0 ] && ok "ex02 tests executable exits normally" || { fail "ex02 tests executable exits normally"; cat "$TMPDIR/ex02.err"; }
    normalize_ts < "$TMPDIR/ex02.out" > "$TMPDIR/ex02.norm"

    # Static known checkpoints from the official tests/log, ignoring timestamp values.
    local missing=0
    for needle in \
        'index:0;amount:42;created' \
        'index:7;amount:16576;created' \
        'accounts:8;total:20049;deposits:0;withdrawals:0' \
        'index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1' \
        'index:7;p_amount:16576;deposit:20;amount:16596;nb_deposits:1' \
        'accounts:8;total:21524;deposits:8;withdrawals:0' \
        'index:0;p_amount:47;withdrawal:refused' \
        'index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1' \
        'index:7;p_amount:16596;withdrawal:7654;amount:8942;nb_withdrawals:1' \
        'accounts:8;total:12442;deposits:8;withdrawals:6' \
        'index:7;amount:8942;closed'
    do
        if ! grep -Fq "$needle" "$TMPDIR/ex02.norm"; then
            echo "Missing: $needle"
            missing=1
        fi
    done > "$TMPDIR/ex02_missing.out"
    if [ $missing -eq 0 ]; then
        ok "standard static account snapshots appear"
    else
        fail "standard static account snapshots appear"
        cat "$TMPDIR/ex02_missing.out"
        sed -n '1,140p' "$TMPDIR/ex02.out"
    fi

    # If a reference log exists, compare normalized output except destructor order.
    local ref
    ref="$(find "$dir" -maxdepth 1 -type f \( -name '*.log' -o -name '*199*.txt' \) | head -n 1)"
    if [ -n "$ref" ]; then
        normalize_ts < "$ref" > "$TMPDIR/ex02_ref.norm"
        grep -v ';closed$' "$TMPDIR/ex02_ref.norm" > "$TMPDIR/ex02_ref_no_closed"
        grep -v ';closed$' "$TMPDIR/ex02.norm" > "$TMPDIR/ex02_out_no_closed"
        if diff -u "$TMPDIR/ex02_ref_no_closed" "$TMPDIR/ex02_out_no_closed" > "$TMPDIR/ex02_diff.out"; then
            ok "ex02 output matches reference log except timestamps/destructor lines"
        else
            fail "ex02 output matches reference log except timestamps/destructor lines"
            sed -n '1,180p' "$TMPDIR/ex02_diff.out"
        fi
        grep ';closed$' "$TMPDIR/ex02_ref.norm" | sort > "$TMPDIR/ex02_ref_closed"
        grep ';closed$' "$TMPDIR/ex02.norm" | sort > "$TMPDIR/ex02_out_closed"
        if diff -u "$TMPDIR/ex02_ref_closed" "$TMPDIR/ex02_out_closed" > "$TMPDIR/ex02_closed_diff.out"; then
            ok "ex02 destructor closed lines match reference as a multiset"
        else
            fail "ex02 destructor closed lines match reference as a multiset"
            cat "$TMPDIR/ex02_closed_diff.out"
        fi
    else
        warn "no reference log found in ex02; used static checkpoint checks only"
    fi

    run_vg "$dir" "$exe"
}

run_ex00
run_ex01
run_ex02

section "SUMMARY"
echo "Checks:   $checks"
echo "Failures: $failures"
echo "Warnings: $warnings"
if [ "$failures" -eq 0 ]; then
    echo "RESULT: PASS"
    exit 0
else
    echo "RESULT: FAIL"
    exit 1
fi
