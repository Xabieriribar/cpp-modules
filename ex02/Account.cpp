#include "Account.hpp"
#include <iostream>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account()
{
    _accountIndex = Account::_nbAccounts;
    _amount = 0;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
}

void	Account::displayAccountsInfos( void )
{
    std::cout << Account::_nbAccounts << std::endl;
    std::cout << Account::_totalAmount << std::endl;
    std::cout << Account::_totalNbDeposits << std::endl;
    std::cout << Account::_totalNbWithdrawals << std::endl;
}

int	Account::getNbWithdrawals( void )
{
    return Account::_totalNbWithdrawals;
}

int	Account::getNbDeposits( void )
{
    return Account::_totalNbDeposits;
}

int	Account::getTotalAmount( void )
{
    return Account::_totalAmount;
}

int	Account::getNbAccounts( void )
{
    return Account::_nbAccounts;
}

void	Account::makeDeposit( int deposit )
{
    _nbDeposits++;
    _amount+=deposit;
}

bool	Account::makeWithdrawal( int withdrawal )
{
    if (withdrawal > _amount)
        return false;
    _amount-=withdrawal;
    _nbWithdrawals++;
    return true;
}

int		Account::checkAmount( void ) 
{
    return _amount;
}