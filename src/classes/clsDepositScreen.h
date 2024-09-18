#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "../Libs/clsInputValidation.h"

class clsDepositScreen : protected clsScreen
{

private:
    static void PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.getFirstName();
        cout << "\nLastName    : " << Client.getLastName();
        cout << "\nFull Name   : " << Client.fullName();
        cout << "\nEmail       : " << Client.getEmail();
        cout << "\nPhone       : " << Client.getPhone();
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nPassword    : " << Client.getPinCode();
        cout << "\nBalance     : " << Client.getAccountBalance();
        cout << "\n___________________\n";
    }

    static string ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:
    static void showDepositScreen()
    {
        DrawScreenHeader("\t   Deposit Screen");

        string accountNumber = ReadAccountNumber();

        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nClient with [" << accountNumber << "] does not exist.\n";
            accountNumber = ReadAccountNumber();
        }

        clsBankClient client1 = clsBankClient::find(accountNumber);
        PrintClient(client1);

        double amount = 0;
        cout << "\nPlease enter deposit amount? ";
        amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char answer = 'n';
        cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            client1.deposit(amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << client1.getAccountBalance();
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};
