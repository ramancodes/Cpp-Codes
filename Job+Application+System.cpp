#include <iostream>
#include <string>
#include <fstream>
#include<iomanip>

using namespace std;

// login class
class Login
{
private:
    string username;
    string password;
    int choice;

    bool jobseeker_login(string uname, string upass)
    {
    }
    bool employer_login(string ename, string epass)
    {
    }
    bool admin_login(string aname, string apass)
    {
    }

public:
    void login_call()
    {
        system("CLS");
        cout << endl
             << endl
             <<"\t\t\t\t\t----------------------------------"<<endl
             << "\t\t\t\t\t   ::Welcome to Login Screen!::" << endl
             <<"\t\t\t\t\t----------------------------------"<<endl
             << endl
             << endl
             << "\t\t\t\t\t1. Job Seeker Login" << endl
             << "\t\t\t\t\t2. Employee Login" << endl
             << "\t\t\t\t\t3. Admin Login" << endl
             << "\t\t\t\t\t0. Home Screen" << endl
             << endl
             << "\t\t\t\t\tEnter: ";
        cin >> choice;
    }
};

// registration class
class registration
{
private:
    int choice;
    bool jobseeker_registration()
    {
    }
    bool employer_registration()
    {
    }
    bool admin_registration()
    {
    }

public:
    void registration_call()
    {
        system("CLS");
        cout << endl
             << endl
             <<"\t\t\t\t\t---------------------------------------"<<endl
             << "\t\t\t\t\t ::Register To Job Application System::" << endl
             <<"\t\t\t\t\t---------------------------------------"<<endl
             << endl
             << "\t\t\t\t\t1. Job Seeker" << endl
             << "\t\t\t\t\t2. Employer" << endl
             << "\t\t\t\t\t3. Admin" << endl
             << "\t\t\t\t\t0. Home Screen" << endl
             << endl
             << "\t\t\t\t\tEnter: ";
        cin >> choice;
    }
};

int main()
{
    Login login;
    registration registration;
    int choice;
    do
    {
        system("CLS");
        cout << endl
        <<endl
            <<"\t\t\t\t\t----------------------------------"<<endl
            <<"\t\t\t\t\tWelcome To Job Application System" << endl
            <<"\t\t\t\t\t----------------------------------"<<endl
             << endl
             << endl
             << "\t\t\t\t\tDo you have an account? "<<endl
             <<"\t\t\t\t\tIf yes enter '1' to login."<<endl
             <<"\t\t\t\t\tIf no enter '2' to sign up." << endl
             <<"\t\t\t\t\tEnter '0' to exit "<<endl
             << endl
             << "\t\t\t\t\t1. Login" << endl
             << "\t\t\t\t\t2. Register As a New User" << endl
             << "\t\t\t\t\t0. Exit" << endl<<endl
             << "\t\t\t\t\tEnter: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            login.login_call();
            break;

        case 2:
            registration.registration_call();
            break;

        default:
            break;
        }

    } while (choice != 0);

    return 0;
}