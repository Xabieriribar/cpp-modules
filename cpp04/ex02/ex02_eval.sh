#!/usr/bin/env bash
set -u

ROOT="${1:-.}"
VALGRIND_MODE="${VALGRIND:-1}"

if [ -d "$ROOT/ex02" ]; then
    EXDIR="$ROOT/ex02"
elif [ -f "$ROOT/Makefile" ] && [ "$(basename "$ROOT")" = "ex02" ]; then
    EXDIR="$ROOT"
else
    echo "Usage: bash ex02_eval.sh /path/to/cpp04-root-or-ex02"
    exit 2
fi

cd "$EXDIR" || exit 2

TMPDIR="$(mktemp -d /tmp/cpp04_ex02_tests.XXXXXX)"
FAILS=0
ORIGINAL_MAIN="$TMPDIR/main.cpp.original"

if [ ! -f main.cpp ]; then
    echo "[FATAL] main.cpp not found in $EXDIR"
    rm -rf "$TMPDIR"
    exit 2
fi

cp main.cpp "$ORIGINAL_MAIN"

cleanup() {
    cp "$ORIGINAL_MAIN" main.cpp 2>/dev/null || true
    make fclean >/dev/null 2>&1 || true
    rm -rf "$TMPDIR"
    echo "Your original main.cpp has been restored."
}
trap cleanup EXIT

pass() { echo "[OK] $1"; }
fail() { echo "[FAIL] $1"; FAILS=$((FAILS + 1)); }

BASE_HEADER="Animal.hpp"
BASE_CLASS="Animal"
if [ ! -f "Animal.hpp" ] && [ -f "AAnimal.hpp" ]; then
    BASE_HEADER="AAnimal.hpp"
    BASE_CLASS="AAnimal"
fi

get_exe() {
    local name
    name="$(awk -F= '/^[[:space:]]*NAME[[:space:]]*=/{gsub(/[[:space:]]/,"",$2); print $2}' Makefile | tail -n 1)"
    if [ -n "$name" ] && [ -x "$name" ]; then
        echo "$name"
        return 0
    fi
    find . -maxdepth 1 -type f -perm -111 ! -name '*.sh' ! -name '*.o' ! -name '*.cpp' ! -name '*.hpp' -printf '%f\n' | head -n 1
}

compile_run() {
    local title="$1"
    local src="$2"
    echo
    echo "========== $title =========="

    cp "$src" main.cpp
    make fclean >/dev/null 2>&1
    if make re >"$TMPDIR/build.log" 2>&1; then
        pass "Compiles with Makefile"
    else
        fail "Compilation failed"
        cat "$TMPDIR/build.log"
        return
    fi

    local exe
    exe="$(get_exe)"
    if [ -z "$exe" ] || [ ! -x "$exe" ]; then
        fail "Could not find executable after make"
        return
    fi

    if ./"$exe" >"$TMPDIR/out.txt" 2>"$TMPDIR/err.txt"; then
        pass "Program exits with code 0"
    else
        fail "Program returned non-zero or crashed"
        echo "--- stdout ---"
        cat "$TMPDIR/out.txt"
        echo "--- stderr ---"
        cat "$TMPDIR/err.txt"
        return
    fi

    if grep -q '^FAIL:' "$TMPDIR/out.txt"; then
        fail "Program printed explicit FAIL markers"
        grep '^FAIL:' "$TMPDIR/out.txt"
    else
        pass "No explicit FAIL markers"
    fi

    if command -v valgrind >/dev/null 2>&1 && [ "$VALGRIND_MODE" != "0" ]; then
        if valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=42 ./"$exe" >"$TMPDIR/vg.out" 2>"$TMPDIR/vg.err"; then
            pass "Valgrind: no reported leaks/errors"
        else
            fail "Valgrind reported leaks/errors"
            cat "$TMPDIR/vg.err"
        fi
    else
        pass "Valgrind skipped"
    fi

    echo "--- program output ---"
    cat "$TMPDIR/out.txt"
}

write_test_abstract_positive() {
cat > "$TMPDIR/t01.cpp" <<CPP
#include <iostream>
#include "$BASE_HEADER"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    const $BASE_CLASS* dog = new Dog();
    const $BASE_CLASS* cat = new Cat();

    std::cout << "TYPE_DOG=" << dog->getType() << std::endl;
    std::cout << "TYPE_CAT=" << cat->getType() << std::endl;

    dog->makeSound();
    cat->makeSound();

    delete dog;
    delete cat;

    return 0;
}
CPP
}

write_test_array_delete() {
cat > "$TMPDIR/t02.cpp" <<CPP
#include <iostream>
#include "$BASE_HEADER"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    $BASE_CLASS* animals[10];

    for (int i = 0; i < 5; ++i)
        animals[i] = new Dog();
    for (int i = 5; i < 10; ++i)
        animals[i] = new Cat();

    for (int i = 0; i < 10; ++i)
        delete animals[i];

    std::cout << "OK_ARRAY_DELETE_THROUGH_ABSTRACT_BASE" << std::endl;
    return 0;
}
CPP
}

write_test_dog_deep_copy() {
cat > "$TMPDIR/t03.cpp" <<'CPP'
#include <iostream>
#include <string>
#define private public
#include "Dog.hpp"
#undef private

static int fails = 0;

static void expect(bool condition, const char* msg)
{
    if (condition)
        std::cout << "OK: " << msg << std::endl;
    else
    {
        std::cout << "FAIL: " << msg << std::endl;
        ++fails;
    }
}

int main()
{
    Dog original;
    original.brain->ideas[42] = "dog original idea";

    Dog copy(original);
    expect(copy.brain != original.brain, "Dog copy constructor creates a different Brain pointer");
    expect(copy.brain->ideas[42] == "dog original idea", "Dog copy constructor copies Brain content");

    original.brain->ideas[42] = "dog changed idea";
    expect(copy.brain->ideas[42] == "dog original idea", "Dog copy remains independent after original mutation");

    Dog assigned;
    assigned = original;
    expect(assigned.brain != original.brain, "Dog assignment keeps a different Brain pointer");
    expect(assigned.brain->ideas[42] == "dog changed idea", "Dog assignment copies Brain content");

    Dog& ref = assigned;
    assigned = ref;
    expect(assigned.brain->ideas[42] == "dog changed idea", "Dog self-assignment through reference preserves data");

    return fails;
}
CPP
}

write_test_cat_deep_copy() {
cat > "$TMPDIR/t04.cpp" <<'CPP'
#include <iostream>
#include <string>
#define private public
#include "Cat.hpp"
#undef private

static int fails = 0;

static void expect(bool condition, const char* msg)
{
    if (condition)
        std::cout << "OK: " << msg << std::endl;
    else
    {
        std::cout << "FAIL: " << msg << std::endl;
        ++fails;
    }
}

int main()
{
    Cat original;
    original.brain->ideas[7] = "cat original idea";

    Cat copy(original);
    expect(copy.brain != original.brain, "Cat copy constructor creates a different Brain pointer");
    expect(copy.brain->ideas[7] == "cat original idea", "Cat copy constructor copies Brain content");

    original.brain->ideas[7] = "cat changed idea";
    expect(copy.brain->ideas[7] == "cat original idea", "Cat copy remains independent after original mutation");

    Cat assigned;
    assigned = original;
    expect(assigned.brain != original.brain, "Cat assignment keeps a different Brain pointer");
    expect(assigned.brain->ideas[7] == "cat changed idea", "Cat assignment copies Brain content");

    Cat& ref = assigned;
    assigned = ref;
    expect(assigned.brain->ideas[7] == "cat changed idea", "Cat self-assignment through reference preserves data");

    return fails;
}
CPP
}

abstract_negative_compile() {
    echo
    echo "========== T05 abstract base negative compile =========="
    cat > "$TMPDIR/abstract_negative.cpp" <<CPP
#include "$BASE_HEADER"

int main()
{
    $BASE_CLASS a;
    return 0;
}
CPP
    if c++ -Wall -Wextra -Werror -std=c++98 -I. -c "$TMPDIR/abstract_negative.cpp" -o "$TMPDIR/abstract_negative.o" >"$TMPDIR/abstract_negative.log" 2>&1; then
        fail "$BASE_CLASS can be instantiated; it should be abstract"
    else
        pass "$BASE_CLASS cannot be instantiated"
    fi
}

header_independence() {
    echo
    echo "========== T06 header independence =========="
    local headers="$BASE_HEADER Brain.hpp Dog.hpp Cat.hpp"
    local h
    for h in $headers; do
        if [ ! -f "$h" ]; then
            fail "$h missing"
            continue
        fi
        cat > "$TMPDIR/header_test.cpp" <<CPP
#include "$h"
int main() { return 0; }
CPP
        if c++ -Wall -Wextra -Werror -std=c++98 -I. -c "$TMPDIR/header_test.cpp" -o "$TMPDIR/header_test.o" >"$TMPDIR/header_build.log" 2>&1; then
            pass "$h can be included independently"
        else
            fail "$h does not compile independently"
            cat "$TMPDIR/header_build.log"
        fi
    done
}

forbidden_scan() {
    echo
    echo "========== T07 forbidden construct scan =========="
    local pattern='using namespace|friend|printf|malloc|calloc|realloc|free|#include[[:space:]]*<vector>|#include[[:space:]]*<list>|#include[[:space:]]*<map>|#include[[:space:]]*<algorithm>'
    if grep -REn "$pattern" . --include='*.cpp' --include='*.hpp' --include='*.h' >"$TMPDIR/forbidden.txt" 2>/dev/null; then
        fail "obvious forbidden constructs found"
        cat "$TMPDIR/forbidden.txt"
    else
        pass "no obvious forbidden constructs found"
    fi
}

echo "Using base class: $BASE_CLASS from $BASE_HEADER"

write_test_abstract_positive
compile_run "T01 abstract base used through pointers" "$TMPDIR/t01.cpp"
write_test_array_delete
compile_run "T02 array delete through abstract base" "$TMPDIR/t02.cpp"
write_test_dog_deep_copy
compile_run "T03 Dog deep copy" "$TMPDIR/t03.cpp"
write_test_cat_deep_copy
compile_run "T04 Cat deep copy" "$TMPDIR/t04.cpp"
abstract_negative_compile
header_independence
forbidden_scan

echo
echo "========== SUMMARY =========="
if [ "$FAILS" -eq 0 ]; then
    echo "All ex02 tests passed."
else
    echo "$FAILS failure(s)."
fi
exit "$FAILS"
