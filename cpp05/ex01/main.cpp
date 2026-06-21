#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    //Exact goal: finish ex01
    //What must work?
    //What can fail?
    //What are the boundaries?
    //How will I test it?
    std::cout << "<<< TEST 1 : INSTATIATE AND GET THE INFORMATION OF THE FORM >>> \n";
    std::cout << "<<< EXPECTED RESULT:  >>>\n";
    Form frm("Test form 1", 12, 15);
    std::cout << frm << std::endl;
    std::cout << "<<< TEST 2 : INSTAITE A BUREAUCRAT WITH A GRADE INFERIOR TOO THE FORM GRADE AND TRY TO SIGN IT >>> \n";
    std::cout << "<<< EXPECTED RESULT:  >>>\n";
    Bureaucrat fancyBureaucrat("Fritz", 20);
    fancyBureaucrat.signForm(frm);
    return 0;
}