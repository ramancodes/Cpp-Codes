#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>

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
             << "\t\t\t\t\t----------------------------------" << endl
             << "\t\t\t\t\t   ::Welcome to Login Screen!::" << endl
             << "\t\t\t\t\t----------------------------------" << endl
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
    string user, pass;

    bool registerUser(const string &username, const string &password)
    {

        map<string, string> users;

        ifstream file;
        file.open("users.txt");

        // checks if the file exists
        if (file)
        {
            // Read existing user credentials from file
            ifstream userFile("users.txt");
            if (!userFile.is_open())
            {
                cerr << "\t\t\t\t\tError opening file." << endl;
                return false;
            }

            // Populate map with username-password pairs from the file
            string line;
            while (getline(userFile, line))
            {
                istringstream iss(line);
                string storedUsername, storedPassword;
                if (iss >> storedUsername >> storedPassword)
                {
                    users[storedUsername] = storedPassword;
                }
            }

            // Check if the username already exists
            if (users.find(username) != users.end())
            {
                cout << "\t\t\t\t\tUsername already exists." << endl;
                return false;
            }
        }

        // Register the new user
        users[username] = password;

        ofstream outFile("users.txt");
        if (!outFile.is_open())
        {
            cerr << "\t\t\t\t\tError opening user file for writing." << endl;
            return false;
        }

        for (const auto &entry : users)
        {
            outFile << entry.first << " " << entry.second << endl;
        }

        // cout << "Registration successful!" << endl;
        return true;
    }

    // register new job seeker
    bool jobseeker_registration()
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t ::Register As A Job Seeker::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl<<endl;
        cout << "\t\t\t\t\tEnter username: ";
        cin >> user;

        cout << "\t\t\t\t\tEnter password: ";
        cin >> pass;

        if(registerUser(user, pass)){
            cout << "\t\t\t\t\tRegistration successful!" << endl;
            cout<<"\t\t\t\t\tLogin Again To Continue."<<endl;
            cout<<"\t\t\t\t\tPress Any Key To Continue"<<endl;
            getchar();
            Login login;
            login.login_call();
        }
        else{
            cout << "\t\t\t\t\tRegistration failed." << endl;
        }
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
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t ::Register To Job Application System::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl
             << "\t\t\t\t\t1. Job Seeker" << endl
             << "\t\t\t\t\t2. Employer" << endl
             << "\t\t\t\t\t3. Admin" << endl
             << "\t\t\t\t\t0. Home Screen" << endl
             << endl
             << "\t\t\t\t\tEnter: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            jobseeker_registration();
            break;
        
        default:
            break;
        }
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
             << endl
             << "\t\t\t\t\t----------------------------------" << endl
             << "\t\t\t\t\tWelcome To Job Application System" << endl
             << "\t\t\t\t\t----------------------------------" << endl
             << endl
             << endl
             << "\t\t\t\t\tDo you have an account? " << endl
             << "\t\t\t\t\tIf yes enter '1' to login." << endl
             << "\t\t\t\t\tIf no enter '2' to sign up." << endl
             << "\t\t\t\t\tEnter '0' to exit " << endl
             << endl
             << "\t\t\t\t\t1. Login" << endl
             << "\t\t\t\t\t2. Register As a New User" << endl
             << "\t\t\t\t\t0. Exit" << endl
             << endl
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
