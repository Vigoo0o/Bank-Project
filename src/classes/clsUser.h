#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "../Libs/clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode Mode;
    string UserName;
    string Password;
    int Permissions;
    bool MarkedForDelete = false;

    static clsUser ConvertLinetoUserObject(string Line, string Seperator = "//")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
                       vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));
    }

    static string ConverUserObjectToLine(clsUser User, string Seperator = "//")
    {

        string UserRecord = "";
        UserRecord += User.getFirstName() + Seperator;
        UserRecord += User.getLastName() + Seperator;
        UserRecord += User.getEmail() + Seperator;
        UserRecord += User.getPhone() + Seperator;
        UserRecord += User.getUserName() + Seperator;
        UserRecord += User.getPassword() + Seperator;
        UserRecord += to_string(User.getPermissions());

        return UserRecord;
    }

    static vector<clsUser> LoadUsersDataFromFile()
    {

        vector<clsUser> vUsers;

        fstream MyFile;
        // /home/vigo0/Desktop/Bank-Management-System/db/users.txt
        MyFile.open("/home/vigo0/Desktop/Bank-Management-System/db/users.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsUser User = ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void SaveUsersDataToFile(vector<clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("/home/vigo0/Desktop/Bank-Management-System/db/users.txt", ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.markedForDeleted() == false)
                {
                    // we only write records that are not marked for delete.
                    DataLine = ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void Update()
    {
        vector<clsUser> vUsers;
        vUsers = LoadUsersDataFromFile();

        for (clsUser &U : vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }
        }

        SaveUsersDataToFile(vUsers);
    }

    void AddNew()
    {

        AddDataLineToFile(ConverUserObjectToLine(*this));
    }

    void AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("/home/vigo0/Desktop/Bank-Management-System/db/users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static clsUser GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enPermissions
    {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64
    };
    clsUser(enMode mode, string firstName, string lastName,
            string email, string phone, string userName, string password,
            int permissions) : clsPerson(firstName, lastName, email, phone)

    {
        Mode = mode;
        UserName = userName;
        Password = password;
        Permissions = permissions;
    }

    bool isEmpty()
    {
        return (Mode == enMode::EmptyMode);
    }

    bool markedForDeleted()
    {
        return MarkedForDelete;
    }

    string getUserName()
    {
        return UserName;
    }

    void setUserName(string userName)
    {
        UserName = userName;
    }

    void setPassword(string password)
    {
        Password = password;
    }

    string getPassword()
    {
        return Password;
    }

    void setPermissions(int permissions)
    {
        Permissions = permissions;
    }

    int getPermissions()
    {
        return Permissions;
    }

    static clsUser find(string userName)
    {

        fstream myFile;
        myFile.open("/home/vigo0/Desktop/Bank-Management-System/db/users.txt", ios::in); // read Mode

        if (myFile.is_open())
        {
            string Line;
            while (getline(myFile, Line))
            {
                clsUser User = ConvertLinetoUserObject(Line);
                if (User.UserName == userName)
                {
                    myFile.close();
                    return User;
                }
            }

            myFile.close();
        }
        return GetEmptyUserObject();
    }

    static clsUser find(string userName, string password)
    {

        fstream myFile;
        myFile.open("/home/vigo0/Desktop/Bank-Management-System/db/users.txt", ios::in); // read Mode

        if (myFile.is_open())
        {
            string Line;
            while (getline(myFile, Line))
            {
                clsUser User = ConvertLinetoUserObject(Line);
                if (User.UserName == userName && User.Password == password)
                {
                    myFile.close();
                    return User;
                }
            }

            myFile.close();
        }
        return GetEmptyUserObject();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2
    };

    enSaveResults save()
    {

        switch (Mode)
        {
        case enMode::EmptyMode:
        {
            if (isEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            // This will add new record to file or database
            if (clsUser::isUserExist(UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                AddNew();
                // We need to set the mode to update after add new
                Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }
    }

    static bool isUserExist(string userName)
    {

        clsUser user = clsUser::find(userName);
        return (!user.isEmpty());
    }

    bool deleteU()
    {
        vector<clsUser> vUsers;
        vUsers = LoadUsersDataFromFile();

        for (clsUser &U : vUsers)
        {
            if (U.UserName == UserName)
            {
                U.MarkedForDelete = true;
                break;
            }
        }

        SaveUsersDataToFile(vUsers);

        *this = GetEmptyUserObject();

        return true;
    }

    static clsUser getAddNewUserObject(string userName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", userName, "", 0);
    }

    static vector<clsUser> getUsersList()
    {
        return LoadUsersDataFromFile();
    }

    bool checkAccessPermission(enPermissions permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;

        if ((this->Permissions & permission) == permission)
            return true;
        else
            return false;
    }
};
