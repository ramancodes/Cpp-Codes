#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <conio.h>

using namespace std;

// registration class
class Registration
{
private:
    int choice;
    string user, pass;

    // register new user
    bool registerUser(const string &username, const string &password, const int &reg_type)
    {
        string filepath;
        map<string, string> users;
        switch (reg_type)
        {
        case 1:
            filepath = "jobseekers_credentials.txt";
            break;

        case 2:
            filepath = "employers_credentials.txt";
            break;

        case 3:
            filepath = "admin_credentials.txt";
            break;

        default:
            break;
        }

        ifstream file;
        file.open(filepath);

        // checks if the file exists
        if (file)
        {
            // Read existing user credentials from file
            ifstream userFile(filepath);
            if (!userFile.is_open())
            {
                cerr << "\n\t\t\t\t\tError opening file." << endl
                     << endl;
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
                cout << "\n\t\t\t\t\tUsername already exists." << endl
                     << endl;
                return false;
            }
        }

        // Register the new user mapping
        users[username] = password;

        ofstream outFile(filepath);
        if (!outFile.is_open())
        {
            cerr << "\n\t\t\t\t\tError opening user file for writing." << endl
                 << endl;
            return false;
        }

        for (const auto &entry : users)
        {
            outFile << entry.first << " " << entry.second << endl;
        }

        return true;
    }

    // take input (username & password) from the user
    void user_registration_input(int reg_type)
    {
        cout << "\t\t\t\t\tEnter username: ";
        cin >> user;

        cout << "\t\t\t\t\tEnter password: ";
        cin >> pass;

        if (registerUser(user, pass, reg_type))
        {
            char c;
            cout << "\n\t\t\t\t\tRegistration successful!" << endl
                 << endl;
            cout << "\t\t\t\t\tNow You can Login To The Application." << endl
                 << endl;
            cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }
        else
        {
            cout << "\t\t\t\t\tRegistration failed." << endl;
            cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }
    }

    // register new job seeker
    void jobseeker_registration(int reg_type)
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t ::Register As A Job Seeker::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;
        user_registration_input(reg_type);
    }

    // register new employer
    void employer_registration(int reg_type)
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t\t::Register As An Employer::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;
        user_registration_input(reg_type);
    }

    // register new admin
    void admin_registration(int reg_type)
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t\t::Register As An Admin::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;
        user_registration_input(reg_type);
    }

public:
    // registration calling function
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

        // choose whom to register
        switch (choice)
        {
        case 1:
            jobseeker_registration(choice);
            break;

        case 2:
            employer_registration(choice);
            break;

        case 3:
            admin_registration(choice);
            break;

        default:
            if (!choice == 0)
            {
                cout << "\n\t\t\t\t\tInvalid Input!! Please Try Again!!";
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
            }
            break;
        }
    }
};

// login class
class Login
{
private:
    string user, pass;
    int choice;

    // authenticate a user
    bool authenticateUser(const string &username, const string &password, const int &reg_type)
    {
        string filepath;
        map<string, string> users;

        // select file path
        switch (reg_type)
        {
        case 1:
            filepath = "jobseekers_credentials.txt";
            break;

        case 2:
            filepath = "employers_credentials.txt";
            break;

        case 3:
            filepath = "admin_credentials.txt";
            break;

        default:
            break;
        }

        // Try To Open The File
        ifstream userFile;
        userFile.open(filepath);

        // check if the exists or not
        if (userFile)
        {
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

            // Check if the provided username exists and the password matches
            auto it = users.find(username);
            if (it != users.end() && it->second == password)
            {
                userFile.close();
                return true;
            }
            else
            {
                userFile.close();
                cout << "\n\t\t\t\t\tInvalid username or password." << endl;
                return false;
            }
        }

        cerr << "\n\t\t\t\t\tError opening file." << endl;
        return false;
    }

    // take input (username & password) from the user
    bool user_login_input(int reg_type)
    {
        Registration Registration;
        string user_type;
        char c;

        cout << "\t\t\t\t\tEnter username: ";
        cin >> user;

        cout << "\t\t\t\t\tEnter password: ";
        cin >> pass;

        bool flag = authenticateUser(user, pass, reg_type);

        if (flag)
        {
            char c;
            cout << "\n\t\t\t\t\tAuthentication successful!" << endl;
            cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }
        else
        {
            cout << "\n\t\t\t\t\tAuthentication failed." << endl;

            switch (reg_type)
            {
            case 1:
                user_type = "Job Seeker";
                break;

            case 2:
                user_type = "Employer";
                break;

            case 3:
                user_type = "Admin";
                break;

            default:
                break;
            }

            cout << "\n\t\t\t\t\tYou are not registerd as a " << user_type << endl;
            cout << "\n\t\t\t\t\tPlease Register as " << user_type << endl;
            cout << "\t\t\t\t\tDo you want to go to register ? \n\t\t\t\t\t'Y/y' for yes 'N/n' for no"
                 << "\n\n\t\t\t\t\tEnter: ";
            cin >> c;
            if (c == 'Y' || c == 'y')
            {
                // redirect to the registration screen
                Registration.registration_call();
            }
        }

        return flag;
    }

    // login as a job seeker
    void jobseeker_login(int reg_type)
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t ::Login As A Job Seeker::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;

        // authenticate the job seeker
        if (user_login_input(reg_type))
        {
            system("CLS");
            cout << "\n\t\t\t\t\tContinue the Process" << endl;
            cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }
    }

    // login as an employer
    void employer_login(int reg_type)
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t\t::Login As An Employer::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;

        // authenticate the employer
        if (user_login_input(reg_type))
        {
            system("CLS");
            cout << "\n\t\t\t\t\tContinue the Process" << endl;
            cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }
    }

    // login as an admin
    void admin_login(int reg_type)
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t\t::Login As An Admin::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;

        // authenticate the job seeker
        if (user_login_input(reg_type))
        {
            system("CLS");
            cout << "\n\t\t\t\t\tContinue the Process" << endl;
            cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }
    }

public:
    // login call function
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

        // choose whom to login
        switch (choice)
        {
        case 1:
            jobseeker_login(choice);
            break;

        case 2:
            employer_login(choice);
            break;

        case 3:
            admin_login(choice);
            break;

        default:
            if (!choice == 0)
            {
                cout << "\n\t\t\t\t\tInvalid Input!! Please Try Again!!";
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
            }
            break;
        }
    }
};

// main function
int main()
{
    Login login;
    Registration registration;
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
            if (!choice == 0)
            {
                cout << "\n\t\t\t\t\tInvalid Input!! Please Try Again!!";
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
            }

            break;
        }

    } while (choice != 0);

    return 0;
}
