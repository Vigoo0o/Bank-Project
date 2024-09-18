#pragma once
#include <iostream>
#include "../Libs/clsInputValidation.h"
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"

class clsDeleteClientScreen : protected clsScreen
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

public:
    static void ShowDeleteClientScreen()
    {
        if (!checkAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return; // this will exit the function and it will not continue
        }
        DrawScreenHeader("\tDelete Client Screen");

        string accountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        accountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client1 = clsBankClient::find(accountNumber);
        PrintClient(client1);

        cout << "\nAre you sure you want to delete this client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            if (client1.deleteC())
            {
                cout << "\nClient Deleted Successfully :-)\n";
                PrintClient(client1);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};
