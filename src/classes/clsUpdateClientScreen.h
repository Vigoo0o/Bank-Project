#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "../Libs/clsInputValidation.h"

class clsUpdateClientScreen : protected clsScreen

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

    static void ReadClientInfo(clsBankClient &Client)
    {
        cout << "\nEnter First Name: ";
        Client.setFirstName(clsInputValidate::ReadString());

        cout << "\nEnter Last Name: ";
        Client.setLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        Client.setEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        Client.setPhone(clsInputValidate::ReadString());

        cout << "\nEnter Pin Code: ";
        Client.setPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        Client.setAccountBalance(clsInputValidate::ReadFloatNumber());
    }

public:
    static void showUpdateClientScreen()
    {
        if (!checkAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return; // this will exit the function and it will not continue
        }
        DrawScreenHeader("\tUpdate Client Screen");

        string accountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client1 = clsBankClient::find(accountNumber);

        PrintClient(client1);

        cout << "\nAre you sure you want to update this client y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            ReadClientInfo(client1);

            clsBankClient::enSaveResult SaveResult;

            SaveResult = client1.save();

            switch (SaveResult)
            {
            case clsBankClient::enSaveResult::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";

                PrintClient(client1);
                break;
            }
            case clsBankClient::enSaveResult::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }
        }
    }
};
