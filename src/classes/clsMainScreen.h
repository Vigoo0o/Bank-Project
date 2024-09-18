#pragma once
#include <iostream>
#include <iomanip>
#include "../Libs/clsInputValidation.h"
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "../global.h"
#include "clsLoginScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:
    enum enMainMenueOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eExit = 8
    };

    static short ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 8]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8? ");
        return Choice;
    }

    static void GoBackToMainMenue()
    {
        // cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        system("read -p 'Press Enter To Go Back To Main Menue...' var");
        showMainMenue();
    }

    static void ShowAllClientsScreen()
    {
        // cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientsList();
    }

    static void ShowAddNewClientsScreen()
    {
        // cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void ShowDeleteClientScreen()
    {
        // cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void ShowUpdateClientScreen()
    {
        // cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::showUpdateClientScreen();
    }

    static void ShowFindClientScreen()
    {
        // cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::showFindClientScreen();
    }

    static void ShowTransactionsMenue()
    {
        // cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::showTransactionsMenue();
    }

    static void ShowManageUsersMenue()
    {
        // cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::showManageUsersMenue();
    }

    static void Logout()
    {
        CurrentUser = clsUser::find("", "");
    }

    static void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("clear");
            ShowAllClientsScreen();
            GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("clear");
            ShowAddNewClientsScreen();
            GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("clear");
            ShowDeleteClientScreen();
            GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("clear");
            ShowUpdateClientScreen();
            GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("clear");
            ShowFindClientScreen();
            GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("clear");
            ShowTransactionsMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("clear");
            ShowManageUsersMenue();
            break;

        case enMainMenueOptions::eExit:
            system("clear");
            Logout();
            break;
        }
    }

public:
    static void showMainMenue()
    {

        system("clear");
        DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
    }
};
