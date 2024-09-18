#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "../Libs/clsInputValidation.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:
    static void ReadUserInfo(clsUser &User)
    {
        cout << "\nEnter FirstName: ";
        User.setFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.setLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.setEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.setPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.setPassword(clsInputValidate::ReadString());

        cout << "\nEnter Permission: ";
        User.setPermissions(ReadPermissionsToSet());
    }

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

    static int ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        return Permissions;
    }

public:
    static void showAddNewUserScreen()
    {

        DrawScreenHeader("\t  Add New User Screen");

        string userName = "";

        cout << "\nPlease Enter UserName: ";
        userName = clsInputValidate::ReadString();
        while (clsUser::isUserExist(userName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            userName = clsInputValidate::ReadString();
        }

        clsUser newUser = clsUser::getAddNewUserObject(userName);

        ReadUserInfo(newUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = newUser.save();

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            PrintUser(newUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;
        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;
        }
        }
    }
};
