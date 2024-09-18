#pragma once

#include <iostream>
#include "../Libs/clsString.h"
#include "clsBankClient.h"
// #include "clsScreen.h"
#include <iomanip>

class clsClientListScreen : protected clsScreen
{

private:
    static void printClientRecordLine(clsBankClient client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << client.getAccountNumber();
        cout << "| " << setw(20) << left << client.fullName();
        cout << "| " << setw(12) << left << client.getPhone();
        cout << "| " << setw(20) << left << client.getEmail();
        cout << "| " << setw(10) << left << client.getPinCode();
        cout << "| " << setw(12) << left << client.getAccountBalance();
    }

public:
    static void ShowClientsList()
    {
        if (!checkAccessRights(clsUser::enPermissions::pListClients))
        {
            return; // this will exit the function and it will not continue
        }

        vector<clsBankClient> vClients = clsBankClient::getClientsList();
        string title = "\t  Client List Screen";
        string subTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        DrawScreenHeader(title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient &client : vClients)
            {

                printClientRecordLine(client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }
};
