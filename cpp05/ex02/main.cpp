#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void)
{
    //Exact goal: finish ex01
    //What must work?
    //What can fail?
    //What are the boundaries?
    //How will I test it?
    std::srand(std::time(NULL));
    std::cout << "<<< TEST 1 : MAKE A PRESIDENTIAL PARDON FORM EXECUTE>>> \n";

    PresidentialPardonForm presidentForm("home");
    Bureaucrat             badBureaucrat("Johny", 23);

    badBureaucrat.executeForm(presidentForm);

    std::cout << "<<< TEST 2 : BUREAUCRAT TRIES TO EXECUTE A PRESIDENTIAL PARDON FORM THAT ISN'T SIGNED>>> \n";

    Bureaucrat             lowGradeBureaucrat("Bibi", 149);

    lowGradeBureaucrat.executeForm(presidentForm);

    std::cout << "<<< TEST 3 : BUREAUCRAT TRIES TO EXECUTE A SIGNED PRESIDENTIAL PARDON FORM WITHOUT THE REQUIRED GRADE TO EXECUTE >>> \n";

    Bureaucrat             normalGradeBureaucrat("Bubalu", 140);

    normalGradeBureaucrat.signAForm(presidentForm);
    normalGradeBureaucrat.executeForm(presidentForm);

    std::cout << "<<< TEST 4 : BUREAUCRAT TRIES TO EXECUTE A SIGNED PRESIDENTIAL PARDON FORM WITH THE REQUIRED GRADE TO EXECUTE >>> \n";

    Bureaucrat             godLevelBureaucrat("Bubalu", 136);

    godLevelBureaucrat.signAForm(presidentForm);
    godLevelBureaucrat.executeForm(presidentForm);
    return 0;
 }