#include "Account.hpp"
#include <iostream>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
{
    _accountIndex = Account::_nbAccounts;
    _amount = initial_deposit;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
}

void Account::_displayTimestamp(void)
{
    std::time_t now;
    std::tm *local;

    now = std::time(NULL);
    local = std::localtime(&now);

    std::cout << "["
              << (local->tm_year + 1900)
              << std::setfill('0') << std::setw(2) << (local->tm_mon + 1)
              << std::setfill('0') << std::setw(2) << local->tm_mday
              << "_"
              << std::setfill('0') << std::setw(2) << local->tm_hour
              << std::setfill('0') << std::setw(2) << local->tm_min
              << std::setfill('0') << std::setw(2) << local->tm_sec
              << "]";

    std::cout << std::setfill(' ');
}

void	Account::displayAccountsInfos( void )
{
    std::cout << "Number of accounts is " << std::endl;
    std::cout << Account::_nbAccounts << std::endl;
    std::cout << "Total amount is " << std::endl;
    std::cout << Account::_totalAmount << std::endl;
    std::cout << "Total number of deposits is " << std::endl;
    std::cout << Account::_totalNbDeposits << std::endl;
    std::cout << "Total number of withdrawals is " << std::endl;
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


void	Account::displayStatus( void ) 
{
    _displayTimestamp();
    std::cout << " index:" << std::endl;
    std::cout << _accountIndex << std::endl;
    std::cout << ";amount" << std::endl;
    std::cout << _amount << std::endl;
    std::cout << "The number for this account is " << std::endl;
    std::cout << _nbDeposits << std::endl;
    std::cout << "The number number of withdrawals for this account is " << std::endl;
    std::cout << _nbWithdrawals << std::endl;
}
