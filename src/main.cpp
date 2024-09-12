#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

enum enMainMenuePermitions
{
    pAll = -1,
    pClientList = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClientInfo = 8,
    pFindClient = 16,
    pTransactions = 32,
    pManageUsers = 64
};

enum enMainMenueOpetions
{
    eClientList = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClientInfo = 4,
    eFindClient = 5,
    eTransactions = 6,
    eManageUsers = 7,
    eLogout = 8
};

enum enTransactionsMenueOpetions
{
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalance = 3,
    eMainMenue = 4
};

enum enManageUserOpetions
{
    eUserList = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUserInfo = 4,
    eFindUser = 5,
    eMain = 6
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

struct stUser
{
    string Username;
    string Password;
    int Permitions;
    bool MarkForDelete = false;
};

const string FilePath = "clients.txt";
const string uFilePath = "users.txt";
stUser CurrentUser;

void MainMenueScreen();
void TransactionsMenueScreen();
void ManageUserScreen();
void Login();

void PermitionDeniedScreen()
{
    system("clear");
    cout << "----------------------------------------------------\n";
    cout << "Access Denied, You Don't Have Permition To Do This!.\n";
    cout << "----------------------------------------------------\n";
}

bool IsHasPermitoin(enMainMenuePermitions Permition) // Permition --> For What You Want To Access
{
    if (CurrentUser.Permitions == enMainMenuePermitions::pAll || (Permition & CurrentUser.Permitions) == Permition)
        return true;
    else
        return false;
}

string ReadString(string Massage = "Please Enter String: ")
{
    string str;

    cout << Massage;
    cin >> str;

    return str;
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

stUser uConverLineToRecord(string Line)
{
    stUser User;
    vector<string> Items = split(Line, "//");

    User.Username = Items[0];
    User.Password = Items[1];
    User.Permitions = stoi(Items[2]);

    return User;
}

string uConvertRecordToLine(stUser User, string Delimetar = "//")
{
    string Line = "";

    Line = User.Username + Delimetar;
    Line += User.Password + Delimetar;
    Line += to_string(User.Permitions);

    return Line;
}

void uSaveUsersDataToFile(string uFilePath, vector<stUser> vUsers)
{
    fstream File;
    File.open(uFilePath, ios::out);

    if (File.is_open())
    {
        for (const stUser &U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                File << uConvertRecordToLine(U) << endl;
            }
        }
        File.close();
    }
}

void PrintUserCard(stUser User)
{
    cout << "\nThe Following Are The User Details:\n";
    cout << "------------------------------------------\n";
    cout << "Username : " << User.Username << endl;
    cout << "Password : " << User.Password << endl;
    cout << "------------------------------------------\n";
}

vector<stUser> uLoadDataFromFile(string FilePath)
{
    vector<stUser> vUsers;
    fstream File;

    File.open(uFilePath, ios::in);

    if (File.is_open())
    {
        string Line;

        while (getline(File, Line))
        {
            stUser User = uConverLineToRecord(Line);
            vUsers.push_back(User);
        }
        File.close();
    }
    return vUsers;
}

void ShowEndScreen()
{
    cout << "------------------------------\n";
    cout << "\tEnd Screen <3\n";
    cout << "------------------------------\n";
}

bool FindUserByUsername(string Username, vector<stUser> vUsers, stUser &User)
{
    for (const stUser &U : vUsers)
    {
        if (U.Username == Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

void FindUser()
{
    cout << "-----------------------------------\n";
    cout << "\tFind User Screen\n";
    cout << "-----------------------------------\n\n";
    string Username = ReadString("Plese Enter Username: ");
    vector<stUser> vUsers = uLoadDataFromFile(uFilePath);
    stUser User;

    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);
    }
    else
    {
        cout << "User With Username [" << Username << "] Is Not Found!\n";
    }
}

void UpdateUserData(stUser &U)
{
    system("clear");
    cout << "Update User:\n\n";

    cout << "Username: ";
    getline(cin >> ws, U.Username);

    cout << "Password: ";
    getline(cin, U.Password);
}

bool GetUserToUpdate(string Username, vector<stUser> &vUsers)
{
    for (stUser &U : vUsers)
    {
        if (U.Username == Username)
        {
            UpdateUserData(U);
            return true;
        }
    }
    return false;
}

void UpdateUser()
{
    cout << "-----------------------------------\n";
    cout << "\tUpdate User Screen\n";
    cout << "-----------------------------------\n\n";
    string Username = ReadString("Plese Enter Username: ");
    vector<stUser> vUsers = uLoadDataFromFile(uFilePath);
    stUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);

        cout << "\nAre You Sure You Want To Update This User? y/n? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            GetUserToUpdate(Username, vUsers);
            uSaveUsersDataToFile(uFilePath, vUsers);

            cout << "\nUser Update Successfuly.\n";
        }
    }
    else
    {
        cout << "\nUser With Username (" << Username << ") Not Found!\n";
    }
}

void uMarkForDelete(string Username, vector<stUser> &vUsers)
{
    for (stUser &U : vUsers)
    {
        if (U.Username == Username)
        {
            U.MarkForDelete = true;
            break;
        }
    }
}

void DeleteUser()
{
    cout << "-----------------------------------\n";
    cout << "\tDelete User Screen\n";
    cout << "-----------------------------------\n\n";
    string Username = ReadString("Plese Enter Username: ");
    vector<stUser> vUsers = uLoadDataFromFile(uFilePath);
    stUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);

        cout << "\nAre You Sure You Want To Delete This User? y/n? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            uMarkForDelete(Username, vUsers);
            uSaveUsersDataToFile(uFilePath, vUsers);

            vUsers = uLoadDataFromFile(uFilePath);

            cout << "\n\nUser Deleted Successfuly.\n";
        }
    }
    else
    {
        cout << "\nUser With Username (" << Username << ") Not Found!\n";
    }
}

int ReadPermitionsToSet()
{
    int Permitions = 0;
    char Answer = 'n';

    cout << "Do You Want To Give Him Full Access? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        return -1;
    }

    cout << "\nDo You Want To Give Access To:\n";
    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permitions = enMainMenuePermitions::pClientList;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permitions += enMainMenuePermitions::pAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permitions += enMainMenuePermitions::pDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permitions += enMainMenuePermitions::pUpdateClientInfo;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permitions += enMainMenuePermitions::pFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permitions += enMainMenuePermitions::pTransactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permitions += enMainMenuePermitions::pManageUsers;
    }

    return Permitions;
}

void AddUserToFile(string uFilePath, string stDataLine)
{
    fstream File;
    File.open(uFilePath, ios::app);
    if (File.is_open())
    {
        File << stDataLine << "\n";
        File.close();
    }
}

bool IsUserExistByUsername(string Username, vector<stUser> vUsers)
{
    for (const stUser &U : vUsers)
    {
        if (U.Username == Username)
        {
            return true;
        }
    }
    return false;
}

stUser ReadNewUser()
{
    stUser User;
    vector<stUser> vUsers = uLoadDataFromFile(uFilePath);

    cout << "Username: ";
    getline(cin >> ws, User.Username);

    while (IsUserExistByUsername(User.Username, vUsers))
    {
        cout << "User With [" << User.Username << "] Already Exist, Enter Another Username: ";
        getline(cin >> ws, User.Username);
    }

    cout << "Password: ";
    getline(cin, User.Password);

    User.Permitions = ReadPermitionsToSet();

    return User;
}

void AddUser()
{
    stUser User;
    User = ReadNewUser();
    AddUserToFile(uFilePath, uConvertRecordToLine(User));
}

void AddUsers()
{
    cout << "-----------------------------------\n";
    cout << "\tAdd New Users Screen\n";
    cout << "-----------------------------------\n";

    char Answer = 'N';

    do
    {

        cout << "Adding New User:\n\n";
        AddUser();

        cout << "\nUser add successfuly, Do you want to add more Users? y/n? ";
        cin >> Answer;
    } while (toupper(Answer) == 'Y');
}

void PrintUserRecord(stUser User)
{
    cout << "| " << left << setw(15) << User.Username;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(40) << User.Permitions;
}

void ShowUserList()
{
    vector<stUser> vUsers = uLoadDataFromFile(uFilePath);

    cout << "\t\t\t\tUser List (" << vUsers.size() << ") User(s).\n";
    cout << "_______________________________________________________________________________________________\n\n";
    cout << "| " << setw(15) << left << "User Name";
    cout << "| " << setw(10) << left << "Passowrd";
    cout << "| " << setw(40) << left << "Permitions";
    cout << "\n_______________________________________________________________________________________________\n\n";

    if (vUsers.size() == 0)
    {
        cout << "Not Users Avilabel In The System!\n";
    }
    else
    {
        for (const stUser &User : vUsers)
        {
            PrintUserRecord(User);
            cout << endl;
        }
    }

    cout << "_______________________________________________________________________________________________\n";
}

void GoBackToManageUsersScreen()
{
    cout << "\n";
    system("read -p 'Press Enter To Go Back To Manage User Screen...' var");
    ManageUserScreen();
}

void PerformManageUserOpetion(enManageUserOpetions Choies)
{
    switch (Choies)
    {
    case enManageUserOpetions::eUserList:
        system("clear");
        ShowUserList();
        GoBackToManageUsersScreen();
        break;
    case enManageUserOpetions::eAddNewUser:
        system("clear");
        AddUsers();
        GoBackToManageUsersScreen();
        break;
    case enManageUserOpetions::eDeleteUser:
        system("clear");
        DeleteUser();
        GoBackToManageUsersScreen();
        break;
    case enManageUserOpetions::eUpdateUserInfo:
        system("clear");
        UpdateUser();
        GoBackToManageUsersScreen();
        break;
    case enManageUserOpetions::eFindUser:
        system("clear");
        FindUser();
        GoBackToManageUsersScreen();
        break;
    case enManageUserOpetions::eMain:
        system("clear");
        MainMenueScreen();
        break;
    }
}

enManageUserOpetions ReadManageUserChoies()
{
    short choies = 0;

    cout << "\nChoose What Do You Want To Do? [1 To 6]? ";
    cin >> choies;

    return (enManageUserOpetions)choies;
}

void ManageUserScreen()
{
    if (!IsHasPermitoin(enMainMenuePermitions::pManageUsers))
    {
        PermitionDeniedScreen();
        GoBackToMainMenue();
        return;
    }

    system("clear");
    cout << "\n\t\t\t\t=========================================\n";
    cout << "\t\t\t\t              Manage Menue Screen\n";
    cout << "\t\t\t\t=========================================\n";
    cout << "\t\t\t\t\t[1] Show User List.\n";
    cout << "\t\t\t\t\t[2] Add New User.\n";
    cout << "\t\t\t\t\t[3] Delete  User.\n";
    cout << "\t\t\t\t\t[4] Update User Info.\n";
    cout << "\t\t\t\t\t[5] Find User.\n";
    cout << "\t\t\t\t\t[6] Main Menue.\n";
    cout << "\t\t\t\t=========================================\n";
    PerformManageUserOpetion(ReadManageUserChoies());
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

void PrintClientRecordForTotalBalances(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.AccountBalance;
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

    double TotalBalances = 0;

    if (vClients.size() == 0)
    {
        cout << "Not Client Avilabel In The System!\n";
    }
    else
    {
        for (const stClient &Client : vClients)
        {
            TotalBalances += Client.AccountBalance;
            PrintClientRecordForTotalBalances(Client);
            cout << endl;
        }
    }

    cout << "_______________________________________________________________________________________________\n";
    cout << "\n\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
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

    string AccountNumber = ReadString("Plese Enter You Account Number: ");
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);
    stClient Client;

    while (!(IsAccountExist(AccountNumber, vClients)))
    {
        cout << "\nClient With [" << AccountNumber << "] Doesn't Exist!\n\n";
        AccountNumber = ReadString("Plese Enter You Account Number: ");
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

    string AccountNumber = ReadString("Plese Enter You Account Number: ");
    vector<stClient> vClients = LoadDataFromFileToVector(FilePath);
    stClient Client;

    while (!(IsAccountExist(AccountNumber, vClients)))
    {
        cout << "\nClient With [" << AccountNumber << "] Doesn't Exist!\n\n";
        AccountNumber = ReadString("Plese Enter You Account Number: ");
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
        MainMenueScreen();
        break;
    }
}

enTransactionsMenueOpetions ReadTransactionsChoies()
{
    short C = 0;

    cout << "Choose What Do Want To Do? [1 To 4]? ";
    cin >> C;

    return (enTransactionsMenueOpetions)C;
}

void TransactionsMenueScreen()
{
    if (!IsHasPermitoin(enMainMenuePermitions::pTransactions))
    {
        PermitionDeniedScreen();
        GoBackToMainMenue();
        return;
    }

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

void FindClient()
{
    if (!IsHasPermitoin(enMainMenuePermitions::pFindClient))
    {
        PermitionDeniedScreen();
        return;
    }

    cout << "-----------------------------------\n";
    cout << "\tFind Client Screen\n";
    cout << "-----------------------------------\n\n";
    string AccountNumber = ReadString("Plese Enter You Account Number: ");
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
    if (!IsHasPermitoin(enMainMenuePermitions::pUpdateClientInfo))
    {
        PermitionDeniedScreen();
        return;
    }

    cout << "-----------------------------------\n";
    cout << "\tUpdate Client Screen\n";
    cout << "-----------------------------------\n\n";
    string AccountNumber = ReadString("Plese Enter You Account Number: ");
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

void DeleteAccount()
{
    if (!IsHasPermitoin(enMainMenuePermitions::pDeleteClient))
    {
        PermitionDeniedScreen();
        return;
    }

    cout << "-----------------------------------\n";
    cout << "\tDelete Client Screen\n";
    cout << "-----------------------------------\n\n";
    string AccountNumber = ReadString("Plese Enter You Account Number: ");
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
    if (!IsHasPermitoin(enMainMenuePermitions::pAddNewClient))
    {
        PermitionDeniedScreen();
        return;
    }

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
    if (!IsHasPermitoin(enMainMenuePermitions::pClientList))
    {
        PermitionDeniedScreen();
        return;
    }

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

void GoBackToMainMenue()
{
    cout << "\n";
    system("read -p 'Press Enter To Go Back To Main Menue...' var");
    MainMenueScreen();
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
    case enMainMenueOpetions::eTransactions:
        system("clear");
        TransactionsMenueScreen();
        break;
    case enMainMenueOpetions::eManageUsers:
        system("clear");
        ManageUserScreen();
        break;
    case enMainMenueOpetions::eLogout:
        system("clear");
        Login();
        break;
    }
}

enMainMenueOpetions ReadMainMenueChoies()
{
    short choies = 0;

    cout << "\nChoose What Do You Want To Do? [1 To 7]? ";
    cin >> choies;

    return (enMainMenueOpetions)choies;
}

void MainMenueScreen()
{
    system("clear");
    cout << "Welcome Back " << CurrentUser.Username << "!." << endl;
    cout << "\n\t\t\t\t=========================================\n";
    cout << "\t\t\t\t               Main Menue Screen\n";
    cout << "\t\t\t\t=========================================\n";
    cout << "\t\t\t\t\t[1] Show Client List.\n";
    cout << "\t\t\t\t\t[2] Add New Client.\n";
    cout << "\t\t\t\t\t[3] Delete  Client.\n";
    cout << "\t\t\t\t\t[4] Update Client Info.\n";
    cout << "\t\t\t\t\t[5] Find Client.\n";
    cout << "\t\t\t\t\t[6] Transactions.\n";
    cout << "\t\t\t\t\t[7] Manage Users.\n";
    cout << "\t\t\t\t\t[8] Logout.\n";
    cout << "\t\t\t\t=========================================\n";
    PerformMainMenueOpetion(ReadMainMenueChoies());
}

bool IsUserExits(string Username, string Password, vector<stUser> vUsers)
{
    for (const stUser &U : vUsers)
    {
        if (U.Username == Username && U.Password == Password)
        {
            return true;
        }
    }
    return false;
}

bool FindUserByUsernameAndPassword(string Username, string Password, stUser &CurrentUser)
{
    vector<stUser> vUsers = uLoadDataFromFile(uFilePath);

    for (const stUser &U : vUsers)
    {
        if (U.Username == Username && U.Password == Password)
        {
            CurrentUser = U;
            return true;
        }
    }
    return false;
}

bool LoadCarrentUserInfo(string Username, string Password)
{
    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
        return true;
    else
        return false;
}

void Login()
{
    string Username, Password;
    vector<stUser> vUsers;
    bool LoginFaild = false;

    do
    {
        system("clear");
        cout << "-----------------------------------\n";
        cout << "\tLogin Screen\n";
        cout << "-----------------------------------\n";

        if (LoginFaild)
        {
            system("clear");
            cout << "Invalied Username/Password!\n";
        }

        Username = ReadString("Enter Username: ");
        Password = ReadString("Enter Password: ");

        vUsers = uLoadDataFromFile(uFilePath);
        LoginFaild = !LoadCarrentUserInfo(Username, Password);

    } while (LoginFaild);

    MainMenueScreen();
}

int main()
{
    Login();
    return 0;
}