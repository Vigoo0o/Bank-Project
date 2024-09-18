#pragma once
#include "clsPerson.h"
#include "../Libs/clsString.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// static -> preserving their value even after they are out of their scope!

class clsBankClient : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };

    enMode Mode;
    string AccountNumber;
    string PinCode;
    float AccountBalance;
    bool MarkForDelete = false;

    // Becuase find() methd is static. Static only can call static member
    static clsBankClient ConvertLineDataToClientObject(string lineData)
    {
        vector<string> vClientData;
        vClientData = clsString::Split(lineData);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
                             vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static vector<clsBankClient> LoadClientsDataFromFile()
    {
        vector<clsBankClient> vClients;
        fstream MyFile;

        MyFile.open("/home/vigo0/Desktop/Bank-Management-System/db/clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = ConvertLineDataToClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }

        return vClients;
    }

    static clsBankClient GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static string ConvertClientObjectToLine(clsBankClient Object, string Separator = "//")
    {
        string Line = "";

        Line = Object.getFirstName() + Separator;
        Line += Object.getLastName() + Separator;
        Line += Object.getEmail() + Separator;
        Line += Object.getPhone() + Separator;
        Line += Object.getAccountNumber() + Separator;
        Line += Object.getPinCode() + Separator;
        Line += to_string(Object.getAccountBalance());

        return Line;
    }

    static void SaveClientsDataToFile(vector<clsBankClient> vClients)
    {
        fstream MyFile;

        MyFile.open("/home/vigo0/Desktop/Bank-Management-System/db/clients.txt", ios::out);

        if (MyFile.is_open())
        {
            for (clsBankClient &C : vClients)
            {
                if (C.getMarkForDelete() == false)
                {
                    MyFile << ConvertClientObjectToLine(C) << "\n";
                }
            }
            MyFile.close();
        }
    }

    void Update()
    {
        vector<clsBankClient> vClients = LoadClientsDataFromFile();

        for (clsBankClient &C : vClients)
        {
            if (C.getAccountNumber() == getAccountNumber())
            {
                C = *this;
            }
        }
        SaveClientsDataToFile(vClients);
    }

    void AddNew()
    {
        AddDataLineToFile(ConvertClientObjectToLine(*this));
    }

    void AddDataLineToFile(string Line)
    {
        fstream MyFile;
        MyFile.open("/home/vigo0/Desktop/Bank-Management-System/db/clients.txt", ios::app);

        if (MyFile.is_open())
        {
            MyFile << Line << "\n";
        }
        MyFile.close();
    }

    void MarkToDelete()
    {
        MarkForDelete = true;
    }

public:
    clsBankClient(enMode mode, string firstName, string lastName, string email,
                  string phone, string accountNumber, string pinCode, float accountBalance)
        : clsPerson(firstName, lastName, email, phone)
    {
        Mode = mode;
        AccountNumber = accountNumber;
        PinCode = pinCode;
        AccountBalance = accountBalance;
    }

    // Read Only Proparity
    string getAccountNumber()
    {
        return AccountNumber;
    }

    void setPinCode(string pinCode)
    {
        PinCode = pinCode;
    }
    string getPinCode()
    {
        return PinCode;
    }

    void setAccountBalance(float accountBalance)
    {
        AccountBalance = accountBalance;
    }
    float getAccountBalance()
    {
        return AccountBalance;
    }

    bool getMarkForDelete()
    {
        return MarkForDelete;
    }

    bool isEmpty()
    {
        return (Mode == enMode::EmptyMode);
    }

    static clsBankClient find(string accountNumber)
    {
        fstream myFile;
        myFile.open("/home/vigo0/Desktop/Bank-Management-System/db/clients.txt", ios::in);

        if (myFile.is_open())
        {
            string lineData;
            while (getline(myFile, lineData))
            {
                clsBankClient client = ConvertLineDataToClientObject(lineData);
                if (client.getAccountNumber() == accountNumber)
                {
                    myFile.close();
                    return client;
                }
            }
            myFile.close();
        }
        // else
        //     cout << "error open the myFile\n";
        return GetEmptyClientObject();
    }

    static clsBankClient find(string accountNumber, string pinCode)
    {
        fstream myFile;

        myFile.open("/home/vigo0/Desktop/Bank-Management-System/db/clients.txt", ios::in);
        if (myFile.is_open())
        {
            string lineData;
            while (getline(myFile, lineData))
            {
                clsBankClient client = ConvertLineDataToClientObject(lineData);
                if (client.getAccountNumber() == accountNumber && client.getPinCode() == pinCode)
                {
                    myFile.close();
                    return client;
                }
            }
            myFile.close();
        }
        return GetEmptyClientObject();
    }

    static bool isClientExist(string accountNumber)
    {
        clsBankClient client = clsBankClient::find(accountNumber);
        return !client.isEmpty();
    }

    enum enSaveResult
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildAccountNumberExist = 2
    };

    enSaveResult save()
    {
        switch (Mode)
        {
        case enMode::EmptyMode:
        {
            return enSaveResult::svFaildEmptyObject;
        }
        case enMode::UpdateMode:
        {
            Update();
            return enSaveResult::svSucceeded;
        }
        case enMode::AddNewMode:
        {
            if (isClientExist(AccountNumber))
            {
                return enSaveResult::svFaildAccountNumberExist;
            }
            else
            {
                AddNew();
                Mode = enMode::UpdateMode;
                return enSaveResult::svSucceeded;
            }
        }
        }
        return enSaveResult::svFaildEmptyObject;
    }

    static clsBankClient getAddNewClient(string accountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
    }

    bool deleteC()
    {
        vector<clsBankClient> vClients = LoadClientsDataFromFile();

        for (clsBankClient &C : vClients)
        {
            if (C.getAccountNumber() == getAccountNumber())
            {
                C.MarkToDelete();
                break;
            }
        }
        SaveClientsDataToFile(vClients);

        *this = GetEmptyClientObject();
        return true;
    }

    static vector<clsBankClient> getClientsList()
    {
        return LoadClientsDataFromFile();
    }

    static float getTotalBalances()
    {
        vector<clsBankClient> vClients = LoadClientsDataFromFile();

        double totalBalances = 0;

        for (clsBankClient &c : vClients)
        {
            totalBalances += c.AccountBalance;
        }

        return totalBalances;
    }

    void deposit(double amount)
    {
        AccountBalance += amount;
        save();
    }

    bool withdraw(double Amount)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }
        else
        {
            AccountBalance -= Amount;
            save();
            return true;
        }
    }
};