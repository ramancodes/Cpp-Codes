#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <conio.h>

using namespace std;

// registration class
class AdminRegistration
{
private:
    int choice;
    string user, pass;

    // register new admin
    bool registerUser(const string &username, const string &password)
    {
        string filepath = "admin_credentials.txt";
        map<string, string> users;

        ifstream file;
        file.open(filepath);

        // checks if the file exists
        if (file)
        {
            // Read existing user credentials from file
            ifstream userFile(filepath);
            if (!userFile.is_open())
            {
                cerr << "\n\t\t\t\t\tError opening admin file." << endl
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
            cerr << "\n\t\t\t\t\tError opening admin file for writing." << endl
                 << endl;
            return false;
        }

        for (const auto &entry : users)
        {
            outFile << entry.first << " " << entry.second << endl;
        }

        return true;
    }

    // take input (username & password) from the admin
    void user_registration_input()
    {
        cout << "\t\t\t\t\tEnter username: ";
        cin >> user;

        cout << "\t\t\t\t\tEnter password: ";
        cin >> pass;

        if (registerUser(user, pass))
        {
            cout << "\n\t\t\t\t\tRegistration successful!" << endl;
            cout << "\n\t\t\t\t\tNow You Can Login To the Application";
            cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
            getch();
        }
        else
        {
            cout << "\t\t\t\t\tRegistration failed." << endl;
            cout << "\t\t\t\t\tPress Enter Key To Exit ";
            getch();
        }
    }

public:
    // registration calling function
    void registration_call()
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t   Welcome To Job Application System" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t      ::Register As An Admin::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;
        user_registration_input();
    }
};

// main function
int main()
{
    AdminRegistration registration;
    registration.registration_call();

    return 0;
}
