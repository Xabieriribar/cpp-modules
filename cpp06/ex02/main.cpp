#include "Base.hpp"

int main(void)
{
    std::srand(std::time(NULL));
    Base *random_class = generate();
    identify(random_class);
    return (0);
}