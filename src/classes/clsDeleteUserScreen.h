#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "../Libs/clsInputValidation.h"

class clsDeleteUserScreen : protected clsScreen
{

private:
    static void PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.getFirstName();
        cout << "\nLastName    : " << User.getLastName();
        cout << "\nFull Name   : " << User.fullName();
        cout << "\nEmail       : " << User.getEmail();
        cout << "\nPhone       : " << User.getPhone();
        cout << "\nUser Name   : " << User.getUserName();
        cout << "\nPassword    : " << User.getPassword();
        cout << "\nPermissions : " << User.getPermissions();
        cout << "\n___________________\n";
    }

public:
    static void showDeleteUserScreen()
    {

        DrawScreenHeader("\tDelete User Screen");

        string userName = "";

        cout << "\nPlease Enter UserName: ";
        userName = clsInputValidate::ReadString();
        while (!clsUser::isUserExist(userName))
        {
            cout << "\nUser is not found, choose another one: ";
            userName = clsInputValidate::ReadString();
        }

        clsUser user1 = clsUser::find(userName);
        PrintUser(user1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char answer = 'n';
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {

            if (user1.deleteU())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                PrintUser(user1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }
};
