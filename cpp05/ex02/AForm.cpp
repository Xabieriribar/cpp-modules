#include "AForm.hpp"
#include "Bureaucrat.hpp"
static void validateGrades(int sign, int exec)
{
    if (sign < 1 || exec < 1) throw AForm::GradeTooHighException();
    if (sign > 150 || exec > 150) throw AForm::GradeTooLowException();
}
AForm::AForm() : _name("Default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {}
AForm::AForm(const std::string &name, int sign, int exec)
    : _name(name), _isSigned(false), _gradeToSign(sign), _gradeToExecute(exec)
{ validateGrades(_gradeToSign, _gradeToExecute); }
AForm::AForm(const AForm &other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}
AForm &AForm::operator=(const AForm &other)
{
    if (this != &other) _isSigned = other._isSigned;
    return *this;
}
AForm::~AForm() {}
const std::string &AForm::getName() const { return _name; }
bool AForm::getIsSigned() const { return _isSigned; }
int AForm::getGradeToSign() const { return _gradeToSign; }
int AForm::getGradeToExecute() const { return _gradeToExecute; }
void AForm::beSigned(const Bureaucrat &b)
{
    if (b.getGrade() > _gradeToSign) throw GradeTooLowException();
    _isSigned = true;
}
void AForm::execute(const Bureaucrat &b) const
{
    if (!_isSigned) throw FormNotSignedException();
    if (b.getGrade() > _gradeToExecute) throw GradeTooLowException();
    action();
}
const char *AForm::GradeTooHighException::what() const throw() { return "grade is too high"; }
const char *AForm::GradeTooLowException::what() const throw() { return "grade is too low"; }
const char *AForm::FormNotSignedException::what() const throw() { return "form is not signed"; }
std::ostream &operator<<(std::ostream &out, const AForm &f)
{
    out << f.getName() << ", signed: " << (f.getIsSigned() ? "yes" : "no")
        << ", grade required to sign: " << f.getGradeToSign()
        << ", grade required to execute: " << f.getGradeToExecute() << ".";
    return out;
}
