#pragma once
#include <string>
#include <iostream>

using namespace std;

class clsPerson
{
private:
    string FirstName;
    string LastName;
    string Email;
    string Phone;

public:
    clsPerson(string firstName, string lastName, string email, string phone)
    {
        FirstName = firstName;
        LastName = lastName;
        Email = email;
        Phone = phone;
    }

    void setFirstName(string firstName)
    {
        FirstName = firstName;
    }
    string getFirstName()
    {
        return FirstName;
    }

    void setLastName(string lastName)
    {
        LastName = lastName;
    }
    string getLastName()
    {
        return LastName;
    }

    void setEmail(string email)
    {
        Email = email;
    }
    string getEmail()
    {
        return Email;
    }

    void setPhone(string phone)
    {
        Phone = phone;
    }
    string getPhone()
    {
        return Phone;
    }

    string fullName()
    {
        return FirstName + " " + LastName;
    }

    void print()
    {
        cout << "\nPerson Card:";
        cout << "\n------------------------------";
        cout << "\nFirst Name  : " << FirstName;
        cout << "\nLast Name   : " << LastName;
        cout << "\nFull Name   : " << fullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\n------------------------------\n";
    }
};