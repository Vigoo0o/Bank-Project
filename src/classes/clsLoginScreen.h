#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "../global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
    static void Login()
    {
        bool LoginFaild = false;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n\n";
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::find(Username, Password);

            LoginFaild = CurrentUser.isEmpty();

        } while (LoginFaild);

        clsMainScreen::showMainMenue();
    }

public:
    static void showLoginScreen()
    {
        system("clear");
        DrawScreenHeader("\t  Login Screen");
        Login();
    }
};