#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include <iomanip>
#include "../Libs/clsUtil.h"

class clsTotalBalancesScreen : protected clsScreen
{

private:
    static void PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.getAccountNumber();
        cout << "| " << setw(40) << left << Client.fullName();
        cout << "| " << setw(12) << left << Client.getAccountBalance();
    }

public:
    static void showTotalBalances()
    {

        vector<clsBankClient> vClients = clsBankClient::getClientsList();

        string title = "\t  Balances List Screen";
        string subTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        DrawScreenHeader(title, subTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n"
             << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n"
             << endl;

        double totalBalances = clsBankClient::getTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient client : vClients)
            {
                PrintClientRecordBalanceLine(client);
                cout << endl;
            }

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n"
             << endl;

        cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << totalBalances << endl;
        // cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(totalBalances) << ")";
    }
};
