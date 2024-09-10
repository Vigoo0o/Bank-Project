#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
string FilePath = "clients.txt";

enum enMainMenueOpetions
{
    eClientList = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClientInfo = 4,
    eFindClient = 5,
    eTransactions = 6,
    eExit = 7
};

enum enTransactionsMenueOpetions
{
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalance = 3,
    eMainMenue = 4
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

void MainMenueScreen();
void TransactionsMenueScreen();
vector<stClient> LoadDataFromFileToVector(string FilePath);

void AddClientToFile(string FilePath, string stDataLine)
{
    fstream File;
    File.open(FilePath, ios::app);
    if (File.is_open())
    {
        File << stDataLine << "\n";
        File.close();
    }
}

string ConvertRecordToLine(stClient Client, string Delimetar = "//")
{
    string Line = "";

    Line = Client.AccountNumber + Delimetar;
    Line += Client.PinCode + Delimetar;
    Line += Client.Name + Delimetar;
    Line += Client.Phone + Delimetar;
    Line += to_string(Client.AccountBalance);

    return Line;
}

bool IsAccountExist(string AccountNumber, vector<stClient> vClients)
{
    for (const stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            return true;
        }
    }
    return false;
}

stClient ReadNewClient()
{
    stClient Client;
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);

    cout << "Account Number: ";
    getline(cin >> ws, Client.AccountNumber);

    while (IsAccountExist(Client.AccountNumber, vClients))
    {
        cout << "Client With [" << Client.AccountNumber << "] Already Exist, Enter Another Account Number: ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Pin Code: ";
    getline(cin, Client.PinCode);

    cout << "Name: ";
    getline(cin, Client.Name);

    cout << "Phone: ";
    getline(cin, Client.Phone);

    cout << "Balance: ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddClient()
{
    stClient Client;
    Client = ReadNewClient();
    AddClientToFile(FilePath, ConvertRecordToLine(Client));
}

void AddClients()
{
    cout << "-----------------------------------\n";
    cout << "\tAdd New Client Screen\n";
    cout << "-----------------------------------\n";

    char Answer = 'N';

    do
    {

        cout << "Adding New Client:\n\n";
        AddClient();

        cout << "\nClient add successfuly, Do you want to add more clients? y/n? ";
        cin >> Answer;
    } while (Answer == 'Y' || Answer == 'y');
}

vector<string> split(string str, string delimeter)
{
    vector<string> result;

    short position = 0;
    string sStr;

    while ((position = str.find(delimeter)) != string::npos)
    {
        sStr = str.substr(0, position);

        result.push_back(sStr);

        str.erase(0, position + delimeter.length());
    }

    result.push_back(str);

    return result;
}

stClient ConvertLineDataToRecord(string LineData, string Delimetar = "//")
{
    stClient Result;
    vector<string> Data = split(LineData, Delimetar);

    Result.AccountNumber = Data[0];
    Result.PinCode = Data[1];
    Result.Name = Data[2];
    Result.Phone = Data[3];
    Result.AccountBalance = stod(Data[4]);

    return Result;
}

vector<stClient> LoadDataFromFileToVector(string FilePath)
{
    vector<stClient> vClients;
    fstream File;

    File.open(FilePath, ios::in);
    if (File.is_open())
    {
        string Line;

        while (getline(File, Line))
        {
            stClient Client = ConvertLineDataToRecord(Line);
            vClients.push_back(Client);
        }
        File.close();
    }
    return vClients;
}

void PrintClientRecord(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowClientList()
{
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);

    cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "_______________________________________________________________________________________________\n\n";
    cout << "| " << setw(15) << left << "Account Number";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Name";
    cout << "| " << setw(12) << left << "Phone";
    cout << "| " << setw(12) << left << "Balance";
    cout << "\n_______________________________________________________________________________________________\n\n";

    if (vClients.size() == 0)
    {
        cout << "Not Client Avilabel In The System!\n";
    }
    else
    {
        for (const stClient &Client : vClients)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
    }

    cout << "_______________________________________________________________________________________________\n";
}

void SaveClientsDataToFile(string FilePath, vector<stClient> vClients)
{
    fstream File;
    File.open(FilePath, ios::out);

    if (File.is_open())
    {
        for (const stClient &C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                File << ConvertRecordToLine(C) << endl;
            }
        }
        File.close();
    }
}

void MarkForDelete(string AccountNumber, vector<stClient> &vClients)
{
    for (stClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            break;
        }
    }
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe Following Are The client Details:\n";
    cout << "------------------------------------------\n";
    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "Pin Code        : " << Client.PinCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "------------------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient &Client)
{
    for (const stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

string ReadAccountNumber()
{
    string AccountNumber;

    cout << "Please Enter Account Number: ";
    cin >> AccountNumber;

    return AccountNumber;
}

void DeleteAccount()
{

    cout << "-----------------------------------\n";
    cout << "\tDelete Client Screen\n";
    cout << "-----------------------------------\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre You Sure You Want To Delete This Client? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            MarkForDelete(AccountNumber, vClients);
            SaveClientsDataToFile(FilePath, vClients);

            vClients = LoadDataFromFileToVector(FilePath);

            cout << "\n\nClient Deleted Successfuly.\n";
        }
    }
    else
    {
        cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
    }
}

void UpdateClientData(stClient &C)
{
    system("clear");
    cout << "Update Client:\n\n";

    cout << "Pin Code: ";
    getline(cin >> ws, C.PinCode);

    cout << "Name: ";
    getline(cin, C.Name);

    cout << "Phone: ";
    getline(cin, C.Phone);

    cout << "Balance: ";
    cin >> C.AccountBalance;
}

bool GetClientToUpdate(string AccountNumber, vector<stClient> &vClients)
{
    for (stClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            UpdateClientData(C);
            return true;
        }
    }
    return false;
}

void UpdateClient()
{
    cout << "-----------------------------------\n";
    cout << "\tUpdate Client Screen\n";
    cout << "-----------------------------------\n\n";
    string AccountNumber = ReadAccountNumber();
    stClient Client;
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre You Sure You Want To Update This Client? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            GetClientToUpdate(AccountNumber, vClients);
            SaveClientsDataToFile(FilePath, vClients);

            cout << "\nClient Update Successfuly.\n";
        }
    }
    else
    {
        cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
    }
}

void FindClient()
{
    cout << "-----------------------------------\n";
    cout << "\tFind Client Screen\n";
    cout << "-----------------------------------\n\n";
    string AccountNumber = ReadAccountNumber();
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "Client With Account Number [" << AccountNumber << "] Is Not Found!\n";
    }
}

void ShowEndScreen()
{
    cout << "------------------------------\n";
    cout << "\tEnd Screen <3\n";
    cout << "------------------------------\n";
}

void GoBackToMainMenue()
{
    cout << "\n";
    system("read -p 'Press Enter To Go Back To Main Menue...' var");
    MainMenueScreen();
}

enMainMenueOpetions ReadMainMenueChoies()
{
    short choies = 0;

    cout << "\nChoose What Do You Want To Do? [1 To 7]? ";
    cin >> choies;

    return (enMainMenueOpetions)choies;
}

enTransactionsMenueOpetions ReadTransactionsChoies()
{
    short C = 0;

    cout << "Choose What Do Want To Do? [1 To 4]? ";
    cin >> C;

    return (enTransactionsMenueOpetions)C;
}

double ReadDeposit()
{
    double Deposit = 0;

    cout << "Please Enter Deposit Amount? ";
    cin >> Deposit;

    return Deposit;
}

void Deposit(string AccountNumber, vector<stClient> &vClients)
{
    double DepositAmount = ReadDeposit();
    char Answer = 'n';

    cout << "Are You Sure You Want Preform This Transaction? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        for (stClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += DepositAmount;
                cout << "\nDone Sucsessfuly, The New Balance Is: " << C.AccountBalance << endl;
                break;
            }
        }
    }
}

void DepositScreen()
{
    cout << "------------------------------\n";
    cout << "\teposit ScreenD\n";
    cout << "------------------------------\n\n";

    string AccountNumber = ReadAccountNumber();
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);
    stClient Client;

    while (!(IsAccountExist(AccountNumber, vClients)))
    {
        cout << "\nClient With [" << AccountNumber << "] Doesn't Exist!\n\n";
        AccountNumber = ReadAccountNumber();
    }

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        // Add and save deposite into the target client (into the Vector)
        Deposit(AccountNumber, vClients);

        // Refresh Data Base
        SaveClientsDataToFile(FilePath, vClients);
    }
}

void GoBackToTransactionsScreen()
{
    cout << "\n";
    system("read -p 'Press Enter To Go Back To Transactions Screen...' var");
    TransactionsMenueScreen();
}

void PrintClientRecordForTotalBalances(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

double TotalBlances(vector<stClient> vClients)
{
    double Total = 0;

    for (const stClient &C : vClients)
    {
        Total += C.AccountBalance;
    }
    return Total;
}

void TotalBlancesScreen()
{
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);

    cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "_______________________________________________________________________________________________\n\n";
    cout << "| " << setw(15) << left << "Account Number";
    cout << "| " << setw(40) << left << "Name";
    cout << "| " << setw(12) << left << "Balance";
    cout << "\n_______________________________________________________________________________________________\n\n";

    if (vClients.size() == 0)
    {
        cout << "Not Client Avilabel In The System!\n";
    }
    else
    {
        for (const stClient &Client : vClients)
        {
            PrintClientRecordForTotalBalances(Client);
            cout << endl;
        }
    }

    cout << "_______________________________________________________________________________________________\n";
    cout << "\n\t\t\t\t\t   Total Balances = " << TotalBlances(vClients) << endl;
}

double ReadWithdraw()
{
    double Withdraw = 0;

    cout << "Please Enter Withdraw Amount? ";
    cin >> Withdraw;

    return Withdraw;
}

void Withdraw(string AccountNumber, vector<stClient> &vClients)
{
    double WithdrawAmount = ReadWithdraw();
    char Answer = 'n';

    for (stClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            while (C.AccountBalance < WithdrawAmount)
            {
                cout << "Amount Exeeds The Balance, You Can Withdraw Up To: " << C.AccountBalance << endl;
                WithdrawAmount = ReadWithdraw();
            }
        }
    }

    cout << "Are You Sure You Want Preform This Transaction? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        for (stClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance -= WithdrawAmount;
                cout << "\nDone Sucsessfuly, The New Balance Is: " << C.AccountBalance << endl;
                break;
            }
        }
    }
}

void WithdrawScreen()
{
    cout << "------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "------------------------------\n\n";

    string AccountNumber = ReadAccountNumber();
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);
    stClient Client;

    while (!(IsAccountExist(AccountNumber, vClients)))
    {
        cout << "\nClient With [" << AccountNumber << "] Doesn't Exist!\n\n";
        AccountNumber = ReadAccountNumber();
    }

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        // Add and save deposite into the target client (into the Vector)
        Withdraw(AccountNumber, vClients);

        // Refresh Data Base
        SaveClientsDataToFile(FilePath, vClients);
    }
}

void PerformTranactionsOpetion(enTransactionsMenueOpetions Choies)
{
    switch (Choies)
    {
    case enTransactionsMenueOpetions::eDeposit:
        system("clear");
        DepositScreen();
        GoBackToTransactionsScreen();
        break;
    case enTransactionsMenueOpetions::eWithdraw:
        system("clear");
        WithdrawScreen();
        GoBackToTransactionsScreen();
        break;
    case enTransactionsMenueOpetions::eTotalBalance:
        system("clear");
        TotalBlancesScreen();
        GoBackToTransactionsScreen();
        break;
    case enTransactionsMenueOpetions::eMainMenue:
        GoBackToMainMenue();
        break;
    }
}

void TransactionsMenueScreen()
{
    system("clear");
    cout << "\n\t\t\t\t=========================================\n";
    cout << "\t\t\t\t          Transactions Menue Screen\n";
    cout << "\t\t\t\t=========================================\n";
    cout << "\t\t\t\t\t[1] Deposit.\n";
    cout << "\t\t\t\t\t[2] Withdraw.\n";
    cout << "\t\t\t\t\t[3] Total Balance.\n";
    cout << "\t\t\t\t\t[4] Main Menue.\n";
    cout << "\t\t\t\t=========================================\n";
    PerformTranactionsOpetion(ReadTransactionsChoies());
}

void PerformMainMenueOpetion(enMainMenueOpetions Choies)
{
    switch (Choies)
    {
    case enMainMenueOpetions::eClientList:
        system("clear");
        ShowClientList();
        GoBackToMainMenue();
        break;
    case enMainMenueOpetions::eAddNewClient:
        system("clear");
        AddClients();
        GoBackToMainMenue();
        break;
    case enMainMenueOpetions::eDeleteClient:
        system("clear");
        DeleteAccount();
        GoBackToMainMenue();
        break;
    case enMainMenueOpetions::eUpdateClientInfo:
        system("clear");
        UpdateClient();
        GoBackToMainMenue();
        break;
    case enMainMenueOpetions::eFindClient:
        system("clear");
        FindClient();
        GoBackToMainMenue();
        break;
    case enMainMenueOpetions::eExit:
        system("clear");
        ShowEndScreen();
        break;
    case enMainMenueOpetions::eTransactions:
        system("clear");
        TransactionsMenueScreen();
        break;
    }
}

void MainMenueScreen()
{
    system("clear");
    cout << "\n\t\t\t\t=========================================\n";
    cout << "\t\t\t\t               Main Menue Screen\n";
    cout << "\t\t\t\t=========================================\n";
    cout << "\t\t\t\t\t[1] Show Client List.\n";
    cout << "\t\t\t\t\t[2] Add New Client.\n";
    cout << "\t\t\t\t\t[3] Delete  Client.\n";
    cout << "\t\t\t\t\t[4] Update Client Info.\n";
    cout << "\t\t\t\t\t[5] Find Client.\n";
    cout << "\t\t\t\t\t[6] Transactions.\n";
    cout << "\t\t\t\t\t[7] Exit.\n";
    cout << "\t\t\t\t=========================================\n";
    PerformMainMenueOpetion(ReadMainMenueChoies());
}

int main()
{
    MainMenueScreen();
    return 0;
}