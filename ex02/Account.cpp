#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
{
    _accountIndex = Account::_nbAccounts;
    Account::_nbAccounts++;
    _amount = 0;
    _amount += initial_deposit;
    Account::_totalAmount += _amount;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
    _displayTimestamp();
    std::cout << " index:" << _accountIndex;
    std::cout << ";";
    std::cout << "amount:" << _amount;
    std::cout << ";";
    std::cout << "created";
    std::cout << std::endl;
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
    _displayTimestamp();
    std::cout << " accounts:" << Account::_nbAccounts;
    std::cout << ";";
    std::cout << "total:" << Account::_totalAmount;
    std::cout << ";";
    std::cout << "deposits:" << Account::_totalNbDeposits;
    std::cout << ";";
    std::cout << "withdrawals:" << Account::_totalNbWithdrawals;
    std::cout << std::endl;
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
    _displayTimestamp();
    std::cout << " index:" << _accountIndex;
    std::cout << ";";
    std::cout << "p_amount:" << _amount;
    std::cout << ";";
    std::cout << "deposit:" << deposit;
    std::cout << ";";
    _amount+=deposit;
    Account::_totalNbDeposits++;
    Account::_totalAmount += deposit;
    std::cout << "amount:" << _amount;
    std::cout << "nb_deposits:" << _nbDeposits;
    std::cout << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal )
{
    if (withdrawal > _amount)
    {
        _displayTimestamp(); 
        std::cout << " index:" << _accountIndex;
        std::cout << ";";
        std::cout << "p_amount:" << _amount;
        std::cout << ";";
        std::cout << "withdrawal:refused";
        std::cout << std::endl;
        return false;
    }
    _displayTimestamp(); 
    std::cout << " index:" << _accountIndex;
    std::cout << ";";
    std::cout << "p_amount:" << _amount;
    std::cout << ";";
    std::cout << "withdrawal:" << withdrawal;
    std::cout << ";";
    _amount-=withdrawal;
    Account::_totalAmount-=withdrawal;
    Account::_totalNbWithdrawals++;
    _nbWithdrawals++;
    std::cout << "amount:" << _amount;
    std::cout << ";";
    std::cout << "nb_withdrawals:" << _nbWithdrawals;
    std::cout << std::endl;
    return true;
}

int		Account::checkAmount( void ) 
{
    return _amount;
}


void	Account::displayStatus( void ) 
{
    _displayTimestamp();
    std::cout << " index:" << _accountIndex;
    std::cout << ";";
    std::cout << "amount:" << _amount;
    std::cout << ";";
    std::cout << "deposits:" << _nbDeposits;
    std::cout << ";";
    std::cout << "withdrawals:" << _nbWithdrawals;
    std::cout << std::endl;
}

Account::~Account(void)
{
    _displayTimestamp();
    std::cout << " index:" << _accountIndex;
    std::cout << ";";
    std::cout << "amount:" << _amount;
    std::cout << ";";
    std::cout << "closed";
    std::cout << std::endl;
}