#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "../Libs/clsInputValidation.h"

class clsFindUserScreen : protected clsScreen
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
    static void showFindUserScreen()
    {

        DrawScreenHeader("\t  Find User Screen");

        string userName;
        cout << "\nPlease Enter UserName: ";
        userName = clsInputValidate::ReadString();
        while (!clsUser::isUserExist(userName))
        {
            cout << "\nUser is not found, choose another one: ";
            userName = clsInputValidate::ReadString();
        }

        clsUser user1 = clsUser::find(userName);

        if (!user1.isEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        PrintUser(user1);
    }
};
