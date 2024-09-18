#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "../Libs/clsInputValidation.h"
#include <iomanip>
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private:
    enum enManageUsersMenueOptions
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenue = 6
    };

    static short ReadManageUsersMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void GoBackToManageUsersMenue()
    {
        system("read -p 'Press Enter To Go Back To Manage Users Menue...' var");
        showManageUsersMenue();
    }

    static void ShowListUsersScreen()
    {
        // cout << "\nList Users Screen Will Be Here.\n";
        clsListUsersScreen::showUsersList();
    }

    static void ShowAddNewUserScreen()
    {
        // cout << "\nAdd New User Screen Will Be Here.\n";
        clsAddNewUserScreen::showAddNewUserScreen();
    }

    static void ShowDeleteUserScreen()
    {
        // cout << "\nDelete User Screen Will Be Here.\n";
        clsDeleteUserScreen::showDeleteUserScreen();
    }

    static void ShowUpdateUserScreen()
    {
        // cout << "\nUpdate User Screen Will Be Here.\n";
        clsUpdateUserScreen::showUpdateUserScreen();
    }

    static void ShowFindUserScreen()
    {
        // cout << "\nFind User Screen Will Be Here.\n";
        clsFindUserScreen::showFindUserScreen();
    }

    static void PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("clear");
            ShowListUsersScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eAddNewUser:
        {
            system("clear");
            ShowAddNewUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eDeleteUser:
        {
            system("clear");
            ShowDeleteUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eUpdateUser:
        {
            system("clear");
            ShowUpdateUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eFindUser:
        {
            system("clear");

            ShowFindUserScreen();
            GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eMainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void showManageUsersMenue()
    {
        if (!checkAccessRights(clsUser::enPermissions::pFindClient))
        {
            return; // this will exit the function and it will not continue
        }
        system("clear");
        DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        PerformManageUsersMenueOption((enManageUsersMenueOptions)ReadManageUsersMenueOption());
    }
};
