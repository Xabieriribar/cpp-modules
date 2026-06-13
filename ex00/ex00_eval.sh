#!/usr/bin/env bash
set -u

ROOT="${1:-.}"
VALGRIND="${VALGRIND:-1}"

if [ -d "$ROOT/ex00" ]; then
    EXDIR="$ROOT/ex00"
elif [ -f "$ROOT/Animal.hpp" ] && [ -f "$ROOT/Makefile" ]; then
    EXDIR="$ROOT"
else
    echo "Usage: bash ex00_eval.sh /path/to/cpp04 OR /path/to/cpp04/ex00"
    exit 2
fi

cd "$EXDIR" || exit 2

TMPDIR=$(mktemp -d /tmp/cpp04_ex00_tests.XXXXXX)
BACKUP="$TMPDIR/main.cpp.backup"
cp main.cpp "$BACKUP"

failures=0
current_output="$TMPDIR/out.txt"
current_err="$TMPDIR/err.txt"
current_vg="$TMPDIR/vg.txt"

restore_main() {
    if [ -f "$BACKUP" ]; then
        cp "$BACKUP" main.cpp
    fi
    rm -rf "$TMPDIR"
}
trap restore_main EXIT

ok() { echo "[OK] $1"; }
fail() { echo "[FAIL] $1"; failures=$((failures + 1)); }

get_name() {
    awk -F= '/^[[:space:]]*NAME[[:space:]]*=/ {gsub(/[[:space:]]/, "", $2); print $2}' Makefile | tail -n 1
}

compile_project() {
    rm -f "$current_output" "$current_err" "$current_vg"
    if make fclean > "$TMPDIR/make_fclean.log" 2>&1 && make re > "$TMPDIR/make.log" 2>&1; then
        ok "Compiles with Makefile"
    else
        fail "Compilation failed"
        cat "$TMPDIR/make.log"
        return 1
    fi

    exe=$(get_name)
    if [ -z "$exe" ]; then
        exe="a.out"
    fi
    if [ ! -x "./$exe" ]; then
        fail "Executable './$exe' not found or not executable"
        return 1
    fi
    return 0
}

run_project() {
    exe=$(get_name)
    if [ -z "$exe" ]; then
        exe="a.out"
    fi

    if "./$exe" > "$current_output" 2> "$current_err"; then
        ok "Program exits with code 0"
    else
        rc=$?
        fail "Program returned non-zero or crashed, code $rc"
        echo "--- stdout ---"
        cat "$current_output"
        echo "--- stderr ---"
        cat "$current_err"
        return 1
    fi

    if [ "$VALGRIND" != "0" ]; then
        if command -v valgrind >/dev/null 2>&1; then
            if valgrind --error-exitcode=97 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all "./$exe" > /dev/null 2> "$current_vg"; then
                ok "Valgrind: no reported leaks/errors"
            else
                fail "Valgrind reported leaks/errors"
                tail -n 80 "$current_vg"
            fi
        else
            echo "[SKIP] Valgrind not installed"
        fi
    fi
    return 0
}

extract_block() {
    file="$1"
    tag="$2"
    awk -v begin="[$tag BEGIN]" -v end="[$tag END]" '
        $0 == begin {flag=1; next}
        $0 == end {flag=0; next}
        flag {print}
    ' "$file" | sed '/^[[:space:]]*$/d'
}

write_main_t01() {
cat > main.cpp <<'CPP'
#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();

    std::cout << "[TYPE DOG]" << dog->getType() << std::endl;
    std::cout << "[TYPE CAT]" << cat->getType() << std::endl;

    std::cout << "[CAT SOUND BEGIN]" << std::endl;
    cat->makeSound();
    std::cout << "[CAT SOUND END]" << std::endl;

    std::cout << "[DOG SOUND BEGIN]" << std::endl;
    dog->makeSound();
    std::cout << "[DOG SOUND END]" << std::endl;

    std::cout << "[ANIMAL SOUND BEGIN]" << std::endl;
    meta->makeSound();
    std::cout << "[ANIMAL SOUND END]" << std::endl;

    delete cat;
    delete dog;
    delete meta;

    return 0;
}
CPP
}

write_main_t02() {
cat > main.cpp <<'CPP'
#include <iostream>
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    const WrongAnimal* wrongBase = new WrongAnimal();
    const WrongAnimal* wrongCatAsBase = new WrongCat();
    const WrongCat directWrongCat;

    std::cout << "[TYPE WRONGCAT]" << wrongCatAsBase->getType() << std::endl;

    std::cout << "[WRONG BASE SOUND BEGIN]" << std::endl;
    wrongBase->makeSound();
    std::cout << "[WRONG BASE SOUND END]" << std::endl;

    std::cout << "[WRONGCAT AS BASE SOUND BEGIN]" << std::endl;
    wrongCatAsBase->makeSound();
    std::cout << "[WRONGCAT AS BASE SOUND END]" << std::endl;

    std::cout << "[DIRECT WRONGCAT SOUND BEGIN]" << std::endl;
    directWrongCat.makeSound();
    std::cout << "[DIRECT WRONGCAT SOUND END]" << std::endl;

    delete wrongCatAsBase;
    delete wrongBase;

    return 0;
}
CPP
}

write_main_t03() {
cat > main.cpp <<'CPP'
#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    Animal* dog = new Dog();
    Animal* cat = new Cat();

    std::cout << "[DELETE DOG BEGIN]" << std::endl;
    delete dog;
    std::cout << "[DELETE DOG END]" << std::endl;

    std::cout << "[DELETE CAT BEGIN]" << std::endl;
    delete cat;
    std::cout << "[DELETE CAT END]" << std::endl;

    return 0;
}
CPP
}

write_main_t04() {
cat > main.cpp <<'CPP'
#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    Dog dogOriginal;
    Dog dogCopy(dogOriginal);
    Dog dogAssigned;
    dogAssigned = dogOriginal;

    Cat catOriginal;
    Cat catCopy(catOriginal);
    Cat catAssigned;
    catAssigned = catOriginal;

    WrongCat wrongOriginal;
    WrongCat wrongCopy(wrongOriginal);
    WrongCat wrongAssigned;
    wrongAssigned = wrongOriginal;

    std::cout << "[DOG COPY TYPE]" << dogCopy.getType() << std::endl;
    std::cout << "[DOG ASSIGN TYPE]" << dogAssigned.getType() << std::endl;
    std::cout << "[CAT COPY TYPE]" << catCopy.getType() << std::endl;
    std::cout << "[CAT ASSIGN TYPE]" << catAssigned.getType() << std::endl;
    std::cout << "[WRONG COPY TYPE]" << wrongCopy.getType() << std::endl;
    std::cout << "[WRONG ASSIGN TYPE]" << wrongAssigned.getType() << std::endl;

    std::cout << "[DOG COPY SOUND BEGIN]" << std::endl;
    dogCopy.makeSound();
    std::cout << "[DOG COPY SOUND END]" << std::endl;

    std::cout << "[CAT COPY SOUND BEGIN]" << std::endl;
    catCopy.makeSound();
    std::cout << "[CAT COPY SOUND END]" << std::endl;

    return 0;
}
CPP
}

write_main_t05() {
cat > main.cpp <<'CPP'
#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    Animal animals[2];
    Dog dogs[2];
    Cat cats[2];
    WrongAnimal wrongAnimals[2];
    WrongCat wrongCats[2];

    std::cout << "[ARRAYS OK]" << std::endl;
    return 0;
}
CPP
}

check_file_contains() {
    pattern="$1"
    msg="$2"
    if grep -Fq "$pattern" "$current_output"; then
        ok "$msg"
    else
        fail "$msg"
    fi
}

case_t01() {
    echo
    echo "========== T01 Animal/Cat/Dog polymorphism =========="
    write_main_t01
    compile_project || return
    run_project || return

    check_file_contains "[TYPE DOG]Dog" "Dog getType() through Animal* is Dog"
    check_file_contains "[TYPE CAT]Cat" "Cat getType() through Animal* is Cat"

    cat_sound=$(extract_block "$current_output" "CAT SOUND")
    dog_sound=$(extract_block "$current_output" "DOG SOUND")
    animal_sound=$(extract_block "$current_output" "ANIMAL SOUND")

    [ -n "$cat_sound" ] && ok "Cat makeSound() produced output" || fail "Cat makeSound() produced no output"
    [ -n "$dog_sound" ] && ok "Dog makeSound() produced output" || fail "Dog makeSound() produced no output"
    [ -n "$animal_sound" ] && ok "Animal makeSound() produced output" || fail "Animal makeSound() produced no output"

    if [ -n "$cat_sound" ] && [ -n "$animal_sound" ] && [ "$cat_sound" != "$animal_sound" ]; then
        ok "Cat through Animal* does not use Animal sound"
    else
        fail "Cat through Animal* appears to use Animal sound"
    fi

    if [ -n "$dog_sound" ] && [ -n "$animal_sound" ] && [ "$dog_sound" != "$animal_sound" ]; then
        ok "Dog through Animal* does not use Animal sound"
    else
        fail "Dog through Animal* appears to use Animal sound"
    fi

    if [ -n "$cat_sound" ] && [ -n "$dog_sound" ] && [ "$cat_sound" != "$dog_sound" ]; then
        ok "Cat and Dog sounds are different"
    else
        fail "Cat and Dog sounds should be different"
    fi
}

case_t02() {
    echo
    echo "========== T02 WrongAnimal/WrongCat non-polymorphism =========="
    write_main_t02
    compile_project || return
    run_project || return

    check_file_contains "[TYPE WRONGCAT]WrongCat" "WrongCat getType() through WrongAnimal* is WrongCat"

    base_sound=$(extract_block "$current_output" "WRONG BASE SOUND")
    wrongcat_as_base_sound=$(extract_block "$current_output" "WRONGCAT AS BASE SOUND")
    direct_wrongcat_sound=$(extract_block "$current_output" "DIRECT WRONGCAT SOUND")

    [ -n "$base_sound" ] && ok "WrongAnimal base sound produced output" || fail "WrongAnimal base sound produced no output"
    [ -n "$wrongcat_as_base_sound" ] && ok "WrongCat through WrongAnimal* produced output" || fail "WrongCat through WrongAnimal* produced no output"
    [ -n "$direct_wrongcat_sound" ] && ok "Direct WrongCat sound produced output" || fail "Direct WrongCat sound produced no output"

    if [ -n "$base_sound" ] && [ "$wrongcat_as_base_sound" = "$base_sound" ]; then
        ok "WrongCat through WrongAnimal* uses WrongAnimal sound"
    else
        fail "WrongCat through WrongAnimal* should use WrongAnimal sound"
        echo "WrongAnimal sound: $base_sound"
        echo "WrongCat as base sound: $wrongcat_as_base_sound"
    fi
}

case_t03() {
    echo
    echo "========== T03 virtual destructor through Animal* =========="
    write_main_t03
    compile_project || return
    run_project || return

    dog_delete=$(extract_block "$current_output" "DELETE DOG")
    cat_delete=$(extract_block "$current_output" "DELETE CAT")

    echo "$dog_delete" | grep -iq "dog" && ok "Deleting Dog through Animal* calls Dog destructor message" || fail "Deleting Dog through Animal* did not show Dog destructor message"
    echo "$cat_delete" | grep -iq "cat" && ok "Deleting Cat through Animal* calls Cat destructor message" || fail "Deleting Cat through Animal* did not show Cat destructor message"
}

case_t04() {
    echo
    echo "========== T04 Orthodox Canonical Form basic copy/assignment =========="
    write_main_t04
    compile_project || return
    run_project || return

    check_file_contains "[DOG COPY TYPE]Dog" "Dog copy constructor preserves type"
    check_file_contains "[DOG ASSIGN TYPE]Dog" "Dog assignment preserves type"
    check_file_contains "[CAT COPY TYPE]Cat" "Cat copy constructor preserves type"
    check_file_contains "[CAT ASSIGN TYPE]Cat" "Cat assignment preserves type"
    check_file_contains "[WRONG COPY TYPE]WrongCat" "WrongCat copy constructor preserves type"
    check_file_contains "[WRONG ASSIGN TYPE]WrongCat" "WrongCat assignment preserves type"

    dog_sound=$(extract_block "$current_output" "DOG COPY SOUND")
    cat_sound=$(extract_block "$current_output" "CAT COPY SOUND")
    [ -n "$dog_sound" ] && ok "Copied Dog can make sound" || fail "Copied Dog did not make sound"
    [ -n "$cat_sound" ] && ok "Copied Cat can make sound" || fail "Copied Cat did not make sound"
    [ "$dog_sound" != "$cat_sound" ] && ok "Copied Dog and copied Cat sounds are different" || fail "Copied Dog and copied Cat sounds should be different"
}

case_t05() {
    echo
    echo "========== T05 stack arrays and destructors =========="
    write_main_t05
    compile_project || return
    run_project || return

    check_file_contains "[ARRAYS OK]" "Stack arrays of all concrete classes can be constructed/destructed"
}

case_t06_header_independence() {
    echo
    echo "========== T06 header independence =========="

    headers="Animal.hpp Dog.hpp Cat.hpp WrongAnimal.hpp WrongCat.hpp"
    all_ok=1
    for h in $headers; do
        cat > "$TMPDIR/header_test.cpp" <<CPP
#include "$h"

int main()
{
    return 0;
}
CPP
        if c++ -Wall -Wextra -Werror -std=c++98 -I. -c "$TMPDIR/header_test.cpp" -o "$TMPDIR/header_test.o" > "$TMPDIR/header_$h.log" 2>&1; then
            ok "$h can be included independently"
        else
            fail "$h cannot be included independently"
            cat "$TMPDIR/header_$h.log"
            all_ok=0
        fi
    done
    return $all_ok
}

case_t07_forbidden_scan() {
    echo
    echo "========== T07 forbidden construct scan =========="

    if grep -RInE 'using[[:space:]]+namespace|\bfriend\b|\bprintf[[:space:]]*\(|\bmalloc[[:space:]]*\(|\bcalloc[[:space:]]*\(|\brealloc[[:space:]]*\(|\bfree[[:space:]]*\(|#include[[:space:]]*<vector>|#include[[:space:]]*<list>|#include[[:space:]]*<map>|#include[[:space:]]*<algorithm>' . --include='*.cpp' --include='*.hpp' --include='*.h' > "$TMPDIR/forbidden.log" 2>/dev/null; then
        fail "possible forbidden constructs found"
        cat "$TMPDIR/forbidden.log"
    else
        ok "no obvious forbidden constructs found"
    fi
}

case_t01
case_t02
case_t03
case_t04
case_t05
case_t06_header_independence
case_t07_forbidden_scan

echo
echo "========== SUMMARY =========="
if [ "$failures" -eq 0 ]; then
    echo "All ex00 tests passed."
else
    echo "$failures failure(s)."
fi

echo "Your original main.cpp has been restored."
exit "$failures"
