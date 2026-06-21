#include "Bureaucrat.hpp"

int main(void)
{
    std::cout << "<<< TEST 1 : INSTATIATE + GET THE NAME + GET THE GRADE OF THE BUREAUCRAT >>> \n";
    std::cout << "<<< EXPECTED RESULT: Fritz, bureaucrat grade 12 >>>\n";
    Bureaucrat normalBureaucrat("Fritz", 12);
    std::cout << normalBureaucrat << std::endl;
    std::cout << "<<< TEST 2 : INCREMENT THE GRADE OF THE BUREAUCRAT >>> \n";
    std::cout << "<<< EXPECTED RESULT: Fritz, bureaucrat grade 11 >>>\n";
    normalBureaucrat.increment();
    std::cout << normalBureaucrat << std::endl;
    std::cout << "<<< TEST 3 : DECREMENT THE GRADE OF THE BUREAUCRAT >>>\n";
    std::cout << "<<< EXPECTED RESULT: Fritz, bureaucrat grade 12 >>>\n";
    normalBureaucrat.decrement();
    std::cout << normalBureaucrat << std::endl;
    std::cout << "<<< TEST 4 : INSTATIATE A BUREAUCRAT WITH A NEGATIVE GRADE >>>\n";
    std::cout << "<<< EXPECTED RESULT: Grade too high. The grade of a bureaucrat should be superior to 0 >>>\n";
    Bureaucrat negativeBureaucrat("Comrade Bark", -1);
    std::cout << "<<< TEST 5 : INSTATIATE A BUREAUCRAT WITH A GRADE SUPERIOR TO 150>>>\n";
    std::cout << "<<< EXPECTED RESULT: Grade too low. The grade of a bureaucrat should be inferior or equal to 150 >>>\n";
    Bureaucrat lowestBureaucrat("Comrade Useless", 152);
    std::cout << "<<< TEST 6 : INSTATIATE A BUREAUCRAT WITH THE HIGHEST GRADE (1), INCREMENT HIS GRADE TO 0>>>\n";
    std::cout << "<<< EXPECTED RESULT: Grade too low. The grade of a bureaucrat should be inferior or equal to 150 >>>\n";
    Bureaucrat topBureaucrat("Employee of the month", 1);
    topBureaucrat.increment();
    std::cout << "<<< TEST 7 : INSTATIATE A BUREAUCRAT WITH THE LOWEST GRADE (150), DECREMENT HIS GRADE TO 151>>>\n";
    std::cout << "<<< EXPECTED RESULT: Grade too low. The grade of a bureaucrat should be inferior or equal to 150 >>>\n";
    Bureaucrat uselessBureaucrat("Fritz", 150);
    uselessBureaucrat.decrement();
}