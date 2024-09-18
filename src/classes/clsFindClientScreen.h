#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "../Libs/clsInputValidation.h"

class clsFindClientScreen : protected clsScreen
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
    static void showFindClientScreen()
    {
        if (!checkAccessRights(clsUser::enPermissions::pFindClient))
        {
            return; // this will exit the function and it will not continue
        }
        DrawScreenHeader("\tFind Client Screen");

        string accountNumber;
        cout << "\nPlease Enter Account Number: ";
        accountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::find(accountNumber);

        if (!Client1.isEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        PrintClient(Client1);
    }
};
