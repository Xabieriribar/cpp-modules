#!/usr/bin/env bash

# CPP04 ex03 behavioral tester
# Usage:
#   bash ex03_eval.sh /path/to/cpp04/ex03
#   bash ex03_eval.sh .        # if you are already inside ex03
#
# Optional:
#   VALGRIND=0 bash ex03_eval.sh .
#   STRICT_OUTPUT=1 bash ex03_eval.sh .
#
# What it does:
#   - backs up your ex03/main.cpp
#   - writes one test main.cpp at a time
#   - runs make fclean && make re
#   - runs your executable
#   - checks expected output fragments
#   - runs valgrind when available, unless VALGRIND=0
#   - restores your original main.cpp at the end

set -u

ROOT="${1:-.}"
EXDIR="$ROOT"

# If user passes the cpp04 root instead of ex03, descend into ex03.
if [ -d "$ROOT/ex03" ] && [ -f "$ROOT/ex03/Makefile" ]; then
    EXDIR="$ROOT/ex03"
fi

if [ ! -d "$EXDIR" ] || [ ! -f "$EXDIR/Makefile" ]; then
    echo "[FATAL] Could not find ex03 Makefile. Pass the ex03 directory or the cpp04 root."
    exit 2
fi

if [ ! -f "$EXDIR/main.cpp" ]; then
    echo "[FATAL] Could not find $EXDIR/main.cpp"
    exit 2
fi

VALGRIND="${VALGRIND:-1}"
STRICT_OUTPUT="${STRICT_OUTPUT:-0}"

HAS_VALGRIND=0
if command -v valgrind >/dev/null 2>&1; then
    HAS_VALGRIND=1
fi

TMPDIR="$(mktemp -d /tmp/cpp04_ex03_tests.XXXXXX)"
BACKUP="$TMPDIR/main.cpp.backup"
cp "$EXDIR/main.cpp" "$BACKUP"

failures=0
warnings=0
current_test=""

restore_main() {
    if [ -f "$BACKUP" ]; then
        cp "$BACKUP" "$EXDIR/main.cpp"
    fi
    rm -rf "$TMPDIR"
}
trap restore_main EXIT INT TERM

print_header() {
    printf '\n========== %s ==========' "$1"
    printf '\n'
}

get_exe_name() {
    awk -F= '/^[[:space:]]*NAME[[:space:]]*=/{gsub(/[[:space:]]/,"",$2); print $2}' "$EXDIR/Makefile" | tail -n 1
}

build_project() {
    (cd "$EXDIR" && make fclean >/dev/null 2>&1 && make re >/tmp/cpp04_ex03_make.log 2>&1)
}

run_program() {
    local exe="$1"
    (cd "$EXDIR" && "./$exe") > "$TMPDIR/out.txt" 2> "$TMPDIR/err.txt"
    return $?
}

run_valgrind() {
    local exe="$1"
    if [ "$VALGRIND" = "0" ]; then
        echo "[SKIP] Valgrind disabled with VALGRIND=0"
        return 0
    fi
    if [ "$HAS_VALGRIND" = "0" ]; then
        echo "[SKIP] Valgrind not installed"
        return 0
    fi
    (cd "$EXDIR" && valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --errors-for-leak-kinds=all \
        --error-exitcode=42 \
        --quiet \
        "./$exe") > "$TMPDIR/valgrind_out.txt" 2> "$TMPDIR/valgrind_err.txt"
    local code=$?
    if [ "$code" -eq 0 ]; then
        echo "[OK] Valgrind: no reported leaks/errors"
        return 0
    fi
    echo "[FAIL] Valgrind reported leaks/errors or program crashed"
    cat "$TMPDIR/valgrind_err.txt"
    failures=$((failures + 1))
    return 1
}

extract_action_lines() {
    grep -E '^\* (shoots an ice bolt at|heals ).* \*$' "$1" || true
}

expect_contains() {
    local file="$1"
    local text="$2"
    local label="$3"
    if grep -Fqx "$text" "$file"; then
        echo "[OK] $label"
    else
        echo "[FAIL] $label"
        echo "Expected exact line: $text"
        echo "Actual relevant lines:"
        extract_action_lines "$file"
        failures=$((failures + 1))
    fi
}

expect_not_contains_regex() {
    local file="$1"
    local regex="$2"
    local label="$3"
    if grep -Eq "$regex" "$file"; then
        echo "[FAIL] $label"
        echo "Matched forbidden pattern: $regex"
        failures=$((failures + 1))
    else
        echo "[OK] $label"
    fi
}

warn_extra_output_if_strict() {
    local file="$1"
    local expected_file="$2"
    if [ "$STRICT_OUTPUT" != "1" ]; then
        return 0
    fi
    if diff -u "$expected_file" "$file" >/tmp/cpp04_ex03_diff.log 2>&1; then
        echo "[OK] strict output exactly matches expected output"
    else
        echo "[FAIL] strict output differs from expected output"
        cat /tmp/cpp04_ex03_diff.log
        failures=$((failures + 1))
    fi
}

write_main() {
    cat > "$EXDIR/main.cpp"
}

basic_compile_and_run() {
    local name="$1"
    print_header "$name"

    if ! build_project; then
        echo "[FAIL] Compilation failed"
        cat /tmp/cpp04_ex03_make.log
        failures=$((failures + 1))
        return 1
    fi
    echo "[OK] Compiles with Makefile"

    local exe
    exe="$(get_exe_name)"
    if [ -z "$exe" ]; then
        exe="a.out"
    fi
    if [ ! -x "$EXDIR/$exe" ]; then
        echo "[FAIL] Executable not found or not executable: $exe"
        failures=$((failures + 1))
        return 1
    fi

    if ! run_program "$exe"; then
        echo "[FAIL] Program returned non-zero or crashed"
        echo "--- stdout ---"
        cat "$TMPDIR/out.txt"
        echo "--- stderr ---"
        cat "$TMPDIR/err.txt"
        failures=$((failures + 1))
        return 1
    fi
    echo "[OK] Program exits with code 0"

    run_valgrind "$exe"
    return 0
}

# -------------------------
# Test 01: official subject
# -------------------------
write_main <<'CPP'
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);

    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;
    return 0;
}
CPP

if basic_compile_and_run "T01 official subject main"; then
    extract_action_lines "$TMPDIR/out.txt" > "$TMPDIR/actions.txt"
    cat > "$TMPDIR/expected.txt" <<'EOF'
* shoots an ice bolt at bob *
* heals bob's wounds *
EOF
    if diff -u "$TMPDIR/expected.txt" "$TMPDIR/actions.txt" >/tmp/cpp04_ex03_diff.log 2>&1; then
        echo "[OK] official action output matches"
    else
        echo "[FAIL] official action output differs"
        cat /tmp/cpp04_ex03_diff.log
        failures=$((failures + 1))
    fi
    warn_extra_output_if_strict "$TMPDIR/out.txt" "$TMPDIR/expected.txt"
fi

# ----------------------------------------------
# Test 02: create cure before ice, unknown, empty
# ----------------------------------------------
write_main <<'CPP'
#include <iostream>
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character bob("bob");

    MateriaSource empty;
    AMateria* none = empty.createMateria("ice");
    if (none == 0)
        std::cout << "OK_EMPTY_NULL" << std::endl;
    else
    {
        std::cout << "FAIL_EMPTY_NOT_NULL" << std::endl;
        delete none;
    }

    MateriaSource src;
    src.learnMateria(new Ice());
    src.learnMateria(new Cure());

    AMateria* cure = src.createMateria("cure");
    if (!cure)
        std::cout << "FAIL_CURE_NULL" << std::endl;
    else
    {
        std::cout << "TYPE=" << cure->getType() << std::endl;
        cure->use(bob);
        delete cure;
    }

    AMateria* unknown = src.createMateria("fire");
    if (unknown == 0)
        std::cout << "OK_UNKNOWN_NULL" << std::endl;
    else
    {
        std::cout << "FAIL_UNKNOWN_NOT_NULL" << std::endl;
        delete unknown;
    }
    return 0;
}
CPP

if basic_compile_and_run "T02 MateriaSource empty/order/unknown"; then
    expect_contains "$TMPDIR/out.txt" "OK_EMPTY_NULL" "empty MateriaSource returns NULL"
    expect_contains "$TMPDIR/out.txt" "TYPE=cure" "createMateria(\"cure\") finds cure by type"
    expect_contains "$TMPDIR/out.txt" "* heals bob's wounds *" "cure output is exact"
    expect_contains "$TMPDIR/out.txt" "OK_UNKNOWN_NULL" "unknown type returns NULL"
    expect_not_contains_regex "$TMPDIR/out.txt" 'FAIL_' "no explicit FAIL markers"
fi

# -----------------------------
# Test 03: clone basics
# -----------------------------
write_main <<'CPP'
#include <iostream>
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Ice ice;
    Cure cure;

    AMateria* iceClone = ice.clone();
    AMateria* cureClone = cure.clone();

    if (iceClone && iceClone != &ice && iceClone->getType() == "ice")
        std::cout << "OK_ICE_CLONE" << std::endl;
    else
        std::cout << "FAIL_ICE_CLONE" << std::endl;

    if (cureClone && cureClone != &cure && cureClone->getType() == "cure")
        std::cout << "OK_CURE_CLONE" << std::endl;
    else
        std::cout << "FAIL_CURE_CLONE" << std::endl;

    delete iceClone;
    delete cureClone;
    return 0;
}
CPP

if basic_compile_and_run "T03 AMateria clone/type"; then
    expect_contains "$TMPDIR/out.txt" "OK_ICE_CLONE" "Ice::clone returns new ice object"
    expect_contains "$TMPDIR/out.txt" "OK_CURE_CLONE" "Cure::clone returns new cure object"
    expect_not_contains_regex "$TMPDIR/out.txt" 'FAIL_' "no explicit FAIL markers"
fi

# ------------------------------------------------------
# Test 04: Character slots, invalid indexes, unequip
# ------------------------------------------------------
write_main <<'CPP'
#include <iostream>
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character me("me");
    Character bob("bob");

    AMateria* floor = new Ice();

    me.equip(floor);        // slot 0
    me.equip(new Cure());   // slot 1
    me.use(0, bob);
    me.use(1, bob);

    std::cout << "BEFORE_INVALID" << std::endl;
    me.use(-1, bob);
    me.use(4, bob);
    me.use(100, bob);
    me.unequip(-1);
    me.unequip(4);
    me.unequip(100);
    std::cout << "AFTER_INVALID" << std::endl;

    me.unequip(0);          // must not delete floor
    std::cout << "AFTER_UNEQUIP_SLOT0" << std::endl;
    me.use(0, bob);         // must do nothing

    floor->use(bob);        // must still be valid if unequip did not delete
    delete floor;

    me.equip(new Cure());   // must reuse slot 0
    std::cout << "AFTER_REEQUIP" << std::endl;
    me.use(0, bob);
    me.use(1, bob);
    me.use(2, bob);         // must do nothing
    return 0;
}
CPP

if basic_compile_and_run "T04 Character equip/unequip/bounds"; then
    expect_contains "$TMPDIR/out.txt" "BEFORE_INVALID" "program reached invalid-index section"
    expect_contains "$TMPDIR/out.txt" "AFTER_INVALID" "invalid indexes did not crash"
    expect_contains "$TMPDIR/out.txt" "AFTER_UNEQUIP_SLOT0" "unequip(0) returned safely"
    expect_contains "$TMPDIR/out.txt" "AFTER_REEQUIP" "program reached re-equip section"

    # Expected action sequence:
    # slot0 ice, slot1 cure, saved floor ice, new slot0 cure, slot1 cure.
    extract_action_lines "$TMPDIR/out.txt" > "$TMPDIR/actions.txt"
    cat > "$TMPDIR/expected.txt" <<'EOF'
* shoots an ice bolt at bob *
* heals bob's wounds *
* shoots an ice bolt at bob *
* heals bob's wounds *
* heals bob's wounds *
EOF
    if diff -u "$TMPDIR/expected.txt" "$TMPDIR/actions.txt" >/tmp/cpp04_ex03_diff.log 2>&1; then
        echo "[OK] Character slot/unequip action sequence is correct"
    else
        echo "[FAIL] Character slot/unequip action sequence differs"
        cat /tmp/cpp04_ex03_diff.log
        failures=$((failures + 1))
    fi
fi

# ------------------------------
# Test 05: full Character inventory
# ------------------------------
write_main <<'CPP'
#include <iostream>
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character me("me");
    Character bob("bob");

    AMateria* fifth = new Cure();

    me.equip(new Ice());
    me.equip(new Ice());
    me.equip(new Ice());
    me.equip(new Ice());
    me.equip(fifth);        // must not be accepted

    me.use(0, bob);
    me.use(1, bob);
    me.use(2, bob);
    me.use(3, bob);
    std::cout << "AFTER_SLOT3" << std::endl;
    me.use(4, bob);         // must do nothing

    delete fifth;           // if inventory accepted fifth, valgrind/double free will catch it
    return 0;
}
CPP

if basic_compile_and_run "T05 Character full inventory"; then
    extract_action_lines "$TMPDIR/out.txt" > "$TMPDIR/actions.txt"
    action_count="$(wc -l < "$TMPDIR/actions.txt" | tr -d ' ')"
    if [ "$action_count" = "4" ]; then
        echo "[OK] only four Materias were usable"
    else
        echo "[FAIL] expected exactly 4 action lines, got $action_count"
        cat "$TMPDIR/actions.txt"
        failures=$((failures + 1))
    fi
    expect_contains "$TMPDIR/out.txt" "AFTER_SLOT3" "slot 4 use did not crash"
fi

# ----------------------------------
# Test 06: Character copy constructor
# ----------------------------------
write_main <<'CPP'
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character bob("bob");

    Character* original = new Character("original");
    original->equip(new Ice());
    original->equip(new Cure());

    Character copy(*original);
    delete original;

    copy.use(0, bob);
    copy.use(1, bob);
    return 0;
}
CPP

if basic_compile_and_run "T06 Character copy constructor deep copy"; then
    expect_contains "$TMPDIR/out.txt" "* shoots an ice bolt at bob *" "copied slot 0 works after original deleted"
    expect_contains "$TMPDIR/out.txt" "* heals bob's wounds *" "copied slot 1 works after original deleted"
fi

# --------------------------------
# Test 07: Character assignment op
# --------------------------------
write_main <<'CPP'
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character bob("bob");

    Character* original = new Character("original");
    original->equip(new Ice());
    original->equip(new Cure());

    Character assigned("assigned");
    assigned.equip(new Cure());

    assigned = *original;
    delete original;

    assigned.use(0, bob);
    assigned.use(1, bob);

    assigned = assigned;
    assigned.use(0, bob);
    assigned.use(1, bob);
    return 0;
}
CPP

if basic_compile_and_run "T07 Character assignment/self-assignment"; then
    extract_action_lines "$TMPDIR/out.txt" > "$TMPDIR/actions.txt"
    cat > "$TMPDIR/expected.txt" <<'EOF'
* shoots an ice bolt at bob *
* heals bob's wounds *
* shoots an ice bolt at bob *
* heals bob's wounds *
EOF
    if diff -u "$TMPDIR/expected.txt" "$TMPDIR/actions.txt" >/tmp/cpp04_ex03_diff.log 2>&1; then
        echo "[OK] assignment and self-assignment action sequence is correct"
    else
        echo "[FAIL] assignment/self-assignment output differs"
        cat /tmp/cpp04_ex03_diff.log
        failures=$((failures + 1))
    fi
fi

# --------------------------------------
# Test 08: MateriaSource copy constructor
# --------------------------------------
write_main <<'CPP'
#include <iostream>
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character bob("bob");

    MateriaSource* original = new MateriaSource();
    original->learnMateria(new Ice());
    original->learnMateria(new Cure());

    MateriaSource copy(*original);
    delete original;

    AMateria* ice = copy.createMateria("ice");
    AMateria* cure = copy.createMateria("cure");

    if (!ice || !cure)
        std::cout << "FAIL_SOURCE_COPY_NULL" << std::endl;
    if (ice)
        ice->use(bob);
    if (cure)
        cure->use(bob);

    delete ice;
    delete cure;
    return 0;
}
CPP

if basic_compile_and_run "T08 MateriaSource copy constructor deep copy"; then
    expect_contains "$TMPDIR/out.txt" "* shoots an ice bolt at bob *" "source copy creates ice after original deleted"
    expect_contains "$TMPDIR/out.txt" "* heals bob's wounds *" "source copy creates cure after original deleted"
    expect_not_contains_regex "$TMPDIR/out.txt" 'FAIL_' "no explicit FAIL markers"
fi

# ------------------------------------
# Test 09: MateriaSource assignment op
# ------------------------------------
write_main <<'CPP'
#include <iostream>
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character bob("bob");

    MateriaSource* original = new MateriaSource();
    original->learnMateria(new Ice());
    original->learnMateria(new Cure());

    MateriaSource assigned;
    assigned.learnMateria(new Cure());

    assigned = *original;
    delete original;

    AMateria* ice = assigned.createMateria("ice");
    AMateria* cure = assigned.createMateria("cure");

    if (!ice || !cure)
        std::cout << "FAIL_SOURCE_ASSIGN_NULL" << std::endl;
    if (ice)
        ice->use(bob);
    if (cure)
        cure->use(bob);

    delete ice;
    delete cure;
    return 0;
}
CPP

if basic_compile_and_run "T09 MateriaSource assignment deep copy"; then
    expect_contains "$TMPDIR/out.txt" "* shoots an ice bolt at bob *" "assigned source creates ice after original deleted"
    expect_contains "$TMPDIR/out.txt" "* heals bob's wounds *" "assigned source creates cure after original deleted"
    expect_not_contains_regex "$TMPDIR/out.txt" 'FAIL_' "no explicit FAIL markers"
fi

# -------------------------------------
# Test 10: MateriaSource full capacity
# -------------------------------------
write_main <<'CPP'
#include <iostream>
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    Character bob("bob");
    MateriaSource src;

    AMateria* extra = new Cure();

    src.learnMateria(new Ice());
    src.learnMateria(new Ice());
    src.learnMateria(new Ice());
    src.learnMateria(new Ice());
    src.learnMateria(extra);       // source is full: extra should not become known

    AMateria* ice = src.createMateria("ice");
    AMateria* cure = src.createMateria("cure");

    if (ice)
        ice->use(bob);
    else
        std::cout << "FAIL_NO_ICE" << std::endl;

    if (cure == 0)
        std::cout << "OK_CURE_NOT_LEARNED" << std::endl;
    else
    {
        std::cout << "FAIL_FIFTH_LEARNED" << std::endl;
        delete cure;
    }

    delete ice;
    delete extra;                 // if source took ownership of extra despite being full, valgrind may catch it
    return 0;
}
CPP

if basic_compile_and_run "T10 MateriaSource full capacity"; then
    expect_contains "$TMPDIR/out.txt" "* shoots an ice bolt at bob *" "source still creates known ice"
    expect_contains "$TMPDIR/out.txt" "OK_CURE_NOT_LEARNED" "fifth Materia was not learned"
    expect_not_contains_regex "$TMPDIR/out.txt" 'FAIL_' "no explicit FAIL markers"
fi

# -------------------------------------
# Test 11: polymorphism via interfaces
# -------------------------------------
write_main <<'CPP'
#include "IMateriaSource.hpp"
#include "ICharacter.hpp"
#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    ICharacter* me = new Character("me");
    ICharacter* bob = new Character("bob");

    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    me->equip(src->createMateria("ice"));
    me->equip(src->createMateria("cure"));

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;
    return 0;
}
CPP

if basic_compile_and_run "T11 Interface polymorphism/destructors"; then
    expect_contains "$TMPDIR/out.txt" "* shoots an ice bolt at bob *" "ICharacter/IAMateriaSource ice call works"
    expect_contains "$TMPDIR/out.txt" "* heals bob's wounds *" "ICharacter/IAMateriaSource cure call works"
fi

# -------------------------------------
# Test 12: AMateria must be abstract
# -------------------------------------
print_header "T12 AMateria abstract negative compile"
cat > "$EXDIR/abstract_negative.cpp" <<'CPP'
#include "AMateria.hpp"

int main()
{
    AMateria m("ice");
    return 0;
}
CPP

if (cd "$EXDIR" && c++ -Wall -Wextra -Werror -std=c++98 -I. -c abstract_negative.cpp -o abstract_negative.o) >/tmp/cpp04_ex03_abs.log 2>&1; then
    echo "[FAIL] AMateria can be instantiated; it should be abstract"
    failures=$((failures + 1))
else
    echo "[OK] AMateria cannot be instantiated"
fi
rm -f "$EXDIR/abstract_negative.cpp" "$EXDIR/abstract_negative.o"

# ------------------
# Forbidden scan
# ------------------
print_header "T13 forbidden construct scan"
if grep -R "using namespace\|friend\|printf\|malloc\|calloc\|realloc\|free\|#include[[:space:]]*<vector>\|#include[[:space:]]*<list>\|#include[[:space:]]*<map>\|#include[[:space:]]*<algorithm>" \
    "$EXDIR" \
    --include='*.cpp' --include='*.hpp' --include='*.h' \
    | grep -v 'abstract_negative' > "$TMPDIR/forbidden.txt"; then
    echo "[FAIL] suspicious forbidden constructs found:"
    cat "$TMPDIR/forbidden.txt"
    failures=$((failures + 1))
else
    echo "[OK] no obvious forbidden constructs found"
fi

# Final build restore check
restore_main
trap - EXIT INT TERM

print_header "SUMMARY"
if [ "$failures" -eq 0 ]; then
    echo "All ex03 tests passed."
    exit 0
else
    echo "$failures failure(s)."
    echo "Your original main.cpp has been restored."
    exit 1
fi
