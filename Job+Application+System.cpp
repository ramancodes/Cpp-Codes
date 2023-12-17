#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <vector>
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
        bool flag;
        cout << "\n\t\t\t\t\tEnter username: ";
        cin >> user;

        cout << "\t\t\t\t\tEnter password: ";
        cin >> pass;

        flag = registerUser(user, pass, reg_type);

        if (flag)
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

public:
    // admin add user function
    void admin_add(int reg_type)
    {
        user_registration_input(reg_type);
    }

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

// class admin functions
class Admin
{
private:
    // Add new User By the Admin
    void add_user(int user_type)
    {
        Registration Registration;
        Registration.admin_add(user_type);
    }

    // edit the password of any user
    bool edit_password(const string &username, const int &reg_type)
    {
        string filepath;
        string newPassword;
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

        // Read existing user credentials from file
        ifstream userFile;
        userFile.open(filepath);

        if (userFile)
        {
            map<string, string> users;

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

            // Check if the username exists
            auto it = users.find(username);
            if (it != users.end())
            {
                // Enter the new password from the user
                cout << "\n\t\t\t\t\tEnter the new password: ";
                cin >> newPassword;

                // Update the user's password
                it->second = newPassword;

                // Write the updated user credentials to the file
                ofstream outFile(filepath);
                if (!outFile.is_open())
                {
                    cerr << "\n\t\t\t\t\tError opening user file for writing." << endl;
                    return false;
                }

                for (const auto &entry : users)
                {
                    outFile << entry.first << " " << entry.second << endl;
                }

                cout << "\n\t\t\t\t\tPassword for user " << username << " has been changed successfully." << endl;
                return true;
            }
            else
            {
                cout << "\n\t\t\t\t\tUser not found. Password modification failed." << endl;
                return false;
            }
        }

        cerr << "\n\t\t\t\t\tError opening user file." << endl;
        return false;
    }

    // remove a user from the file
    bool remove_user(const string &username, const int &reg_type)
    {
        string filepath;
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

        // Read existing user credentials from file
        ifstream userFile;
        userFile.open(filepath);
        if (userFile)
        {

            map<string, string> users;

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

            // Check if the username exists
            auto it = users.find(username);
            if (it != users.end())
            {
                // Remove the user from the map
                users.erase(it);

                // Write the updated user credentials to the file
                ofstream outFile(filepath);
                if (!outFile.is_open())
                {
                    cerr << "\n\t\t\t\t\tError opening user file for writing." << endl;
                    return false;
                }

                for (const auto &entry : users)
                {
                    outFile << entry.first << " " << entry.second << endl;
                }

                cout << "\n\t\t\t\t\tUser " << username << " has been deleted successfully." << endl;
                return true;
            }
            else
            {
                cout << "\n\t\t\t\t\tUser not found. Deletion failed." << endl;
                return false;
            }
        }

        cerr << "\n\t\t\t\t\tError opening user file." << endl;
        return false;
    }

public:
    // Call the functions of the admin
    void admin_func_call()
    {
        string user;
        int choice;
        do
        {
            system("CLS");
            cout << endl
                 << endl
                 << "\t\t\t\t\t----------------------------------" << endl
                 << "\t\t\t\t\t\t ::Admin Section::" << endl
                 << "\t\t\t\t\t----------------------------------" << endl
                 << endl
                 << endl
                 << "\t\t\t\t\t1. Add Job Seeker" << endl
                 << "\t\t\t\t\t2. Add Employer" << endl
                 << "\t\t\t\t\t3. Add Admin" << endl
                 << "\t\t\t\t\t4. Remove Job Seeker" << endl
                 << "\t\t\t\t\t5. Remove Employer" << endl
                 << "\t\t\t\t\t6. Remove Admin" << endl
                 << "\t\t\t\t\t7. Change Job Seeker Password" << endl
                 << "\t\t\t\t\t8. Change Employer Password" << endl
                 << "\t\t\t\t\t9. Change Admin Password" << endl
                 << "\t\t\t\t\t10. Remove Job Post" << endl
                 << "\t\t\t\t\t0. Log Out" << endl
                 << endl
                 << "\t\t\t\t\tEnter: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                add_user(2);
                break;

            case 2:
                add_user(2);
                break;

            case 3:
                add_user(3);
                break;

            case 4:
                cout << "\n\t\t\t\t\tEnter username: ";
                cin >> user;
                if (remove_user(user, 1))
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                break;

            case 5:
                cout << "\n\t\t\t\t\tEnter username: ";
                cin >> user;
                if (remove_user(user, 2))
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                break;

            case 6:
                cout << "\n\t\t\t\t\tEnter username: ";
                cin >> user;
                if (remove_user(user, 3))
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                break;

            case 7:
                cout << "\n\t\t\t\t\tEnter username: ";
                cin >> user;
                if (edit_password(user, 1))
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                break;

            case 8:
                cout << "\n\t\t\t\t\tEnter username: ";
                cin >> user;
                if (edit_password(user, 2))
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                break;

            case 9:
                cout << "\n\t\t\t\t\tEnter username: ";
                cin >> user;
                if (edit_password(user, 3))
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                }
                break;

            case 10:
                cout << "\n\n\t\t\t\t\tProcess Under Development ";
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
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
    }
};

// Job Seeker Class
class JobSeeker
{
private:
    struct Resume
    {
        string name;
        string contact;
        string email;
        string dob;
        string qualification;
        string skills;
        string experience;
    };

    struct Application
    {
        string jobTitle;
        string jobSeeker;
        string employerName;
    };

    // Add resume of job seeker -> resume.txt
    void addResume(const Resume &resume)
    {
        ofstream resumeFile("resumes.txt", ios::app);
        if (resumeFile.is_open())
        {
            resumeFile << resume.name << "|" << resume.contact << "|" << resume.email << "|" << resume.dob << "|" << resume.qualification << "|" << resume.skills << "|" << resume.experience << endl;
            cout << "\n\t\t\t\t\tResume saved successfully!" << endl;
        }
        else
        {
            cerr << "\n\t\t\t\t\tError opening resume file for writing." << endl;
        }
    }

    // show the resume of current job seeker -> resume.txt
    void showResume(const string &jobSeekerName)
    {
        ifstream resumeFile("resumes.txt");
        if (resumeFile.is_open())
        {
            string line;
            while (getline(resumeFile, line))
            {
                size_t pos = line.find("|");
                string name = line.substr(0, pos);
                if (name == jobSeekerName)
                {
                    cout << "\n\n\t\t\t\t\tResume for " << name << ": " << line.substr(pos + 1) << endl;
                    return;
                }
            }
            cout << "\n\n\t\t\t\t\tResume not found for " << jobSeekerName << "." << endl;
        }
        else
        {
            cerr << "\n\n\t\t\t\t\tError opening resume file for reading." << endl;
            cout<<"\n\t\t\t\t\tNo Resume Available." << endl;
        }
    }

    // update the resume of the job seeker -> resume.txt
    void updateResume(const string &jobSeekerName, const Resume &newResume)
    {
        ifstream resumeFile("resumes.txt");
        if (resumeFile.is_open())
        {
            vector<string> lines;
            string line;
            while (getline(resumeFile, line))
            {
                size_t pos = line.find("|");
                string name = line.substr(0, pos);
                if (name == jobSeekerName)
                {
                    lines.push_back(newResume.name + "|" + newResume.contact + "|" + newResume.email + "|" + newResume.dob + "|" + newResume.qualification + "|" + newResume.skills + "|" + newResume.experience);
                }
                else
                {
                    lines.push_back(line);
                }
            }

            // Write the updated resumes back to the file
            ofstream outFile("resumes.txt");
            if (outFile.is_open())
            {
                for (const auto &updatedLine : lines)
                {
                    outFile << updatedLine << endl;
                }
                cout << "\n\t\t\t\t\tResume updated successfully!" << endl;
            }
            else
            {
                cerr << "\n\t\t\t\t\tError opening resume file for writing." << endl;
            }
        }
        else
        {
            cerr << "\n\t\t\t\t\tError opening resume file for reading." << endl;
        }
    }

    // Show all the jobs available in the application -> jobs.txt
    bool showJobs()
    {
        ifstream jobFile("jobs.txt");
        if (jobFile.is_open())
        {
            string line;
            while (getline(jobFile, line))
            {
                size_t pos = line.find("|");
                cout << "\n\n\t\t\t\t\tJob Title: " << line.substr(0, pos) << endl;
                cout << "\n\t\t\t\t\tDescription: " << line.substr(pos + 1) << endl;
                cout << "------------------------" << endl;
            }
            return true;
        }

        cerr << "\n\t\t\t\t\tError opening job file for reading." << endl;
        cout << "\n\t\t\t\t\tNo Jobs Available" << endl;
        return false;
    }

    // apply for any job -> applications.txt
    void applyForJob(const Application &application)
    {
        ofstream applicationFile("applications.txt", ios::app);
        if (applicationFile.is_open())
        {
            applicationFile << application.jobSeeker << "|" << application.jobTitle << "|" << application.employerName << endl;
            cout << "\n\t\t\t\t\tApplication submitted successfully!" << endl;
        }
        else
        {
            cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
        }
    }

    // show all the applied jobs -> applications.txt
    void viewAppliedJobs(const string &jobSeekerName)
    {
        ifstream applicationFile("applications.txt");
        if (applicationFile.is_open())
        {
            string line;
            while (getline(applicationFile, line))
            {
                size_t pos = line.find("|");
                string applicant = line.substr(0, pos);
                string jobTitle = line.substr(pos + 1);
                if (applicant == jobSeekerName)
                {
                    cout << "\n\t\t\t\t\tYou applied for the job: " << jobTitle << endl;
                }
                else
                {
                    cout << "\n\t\t\t\t\tYou have not applied for any job.";
                }
            }
        }
        else
        {
            cerr << "\n\t\t\t\t\tError opening application file for reading." << endl;
            cout << "\n\t\t\t\t\tNo Jobs Applied." << endl;
        }
    }

public:
    // Job seeker function call
    void jobSeeker_func_call()
    {
        int choice;
        char c;
        string jobTitle, employerName, jobSeekerName;
    RenterName:
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t--------------------------------------" << endl
             << "\t\t\t\t\t  ::Welcome to Job Seeker Section!::" << endl
             << "\t\t\t\t\t--------------------------------------" << endl
             << endl
             << endl;
        // Enter Name
        cin.ignore();
        cout << "\n\t\t\t\t\tEnter your name : ";
        getline(cin, jobSeekerName);
        cout << "\n\t\t\t\t\tYour name is " << jobSeekerName << endl
             << "\t\t\t\t\tIs this Correct? (Y/y or N/n)" << endl
             << "\n\t\t\t\t\tEnter: ";
        cin >> c;

        if (c == 'y' || c == 'Y')
        {
            do
            {
                system("CLS");
                cout << endl
                     << endl
                     << "\t\t\t\t\t--------------------------------------" << endl
                     << "\t\t\t\t\t  ::Welcome to Job Seeker Section!::" << endl
                     << "\t\t\t\t\t--------------------------------------" << endl
                     << endl
                     << endl
                     << "\t\t\t\t\t1. Add Resume\n"
                     << "\t\t\t\t\t2. Show Resume\n"
                     << "\t\t\t\t\t3. Update Resume\n"
                     << "\t\t\t\t\t4. Search & Apply Available Jobs\n"
                     << "\t\t\t\t\t5. View Applied Jobs\n"
                     << "\t\t\t\t\t0. Exit\n"
                     << "\n\t\t\t\t\tEnter your choice: ";
                cin >> choice;

                switch (choice)
                {
                // 1. Add Resume
                case 1:
                {
                    Resume resume;
                    cin.ignore(); // Ignore newline character left in the buffer
                    resume.name = jobSeekerName;
                    // Enter contact
                    cout << "\n\n\t\t\t\t\tEnter Contact No: ";
                    getline(cin, resume.contact);
                    // Enter email
                    cout << "\t\t\t\t\tEnter email: ";
                    getline(cin, resume.email);
                    // Enter dob
                    cout << "\t\t\t\t\tEnter D.O.B.(DD/MM/YYYY): ";
                    getline(cin, resume.dob);
                    // Enter Qualification
                    cout << "\t\t\t\t\tEnter Qualification: ";
                    getline(cin, resume.qualification);
                    // Enter skills
                    cout << "\t\t\t\t\tEnter skills: ";
                    getline(cin, resume.skills);
                    // Enter Experience
                    cout << "\t\t\t\t\tEnter experience (months or years): ";
                    getline(cin, resume.experience);

                    // addResume Function Initiated
                    addResume(resume);
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                    break;
                }

                // 2. Show Resume
                case 2:
                {
                    showResume(jobSeekerName);
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                    break;
                }

                // 3. Update Resume
                case 3:
                {
                    Resume newResume;
                    cin.ignore(); // Ignore newline character left in the buffer
                    newResume.name = jobSeekerName;
                    // Enter contact
                    cout << "\n\t\t\t\t\tEnter Contact No: ";
                    getline(cin, newResume.contact);
                    // Enter email
                    cout << "\t\t\t\t\tEnter email: ";
                    getline(cin, newResume.email);
                    // Enter dob
                    cout << "\t\t\t\t\tEnter D.O.B.(DD/MM/YYYY): ";
                    getline(cin, newResume.dob);
                    // Enter Qualification
                    cout << "\t\t\t\t\tEnter Qualification: ";
                    getline(cin, newResume.qualification);
                    // Enter skills
                    cout << "\t\t\t\t\tEnter skills: ";
                    getline(cin, newResume.skills);
                    // Enter Experience
                    cout << "\t\t\t\t\tEnter experience (months or years): ";
                    getline(cin, newResume.experience);

                    // Update resume function initiated
                    updateResume(jobSeekerName, newResume);
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                    break;
                }

                // 4. Search & Apply for Jobs Available
                case 4:
                {
                    Application application;
                    do
                    {
                        system("CLS");
                        cout << endl
                             << endl
                             << "\t\t\t\t\t-------------------------------" << endl
                             << "\t\t\t\t\t     ::Available Jobs::" << endl
                             << "\t\t\t\t\t-------------------------------" << endl
                             << endl
                             << endl;
                        // show jobs
                        if (showJobs())
                        {
                            // apply for any job
                            cout << "\n\n\t\t\t\t\tDo You Want to Apply For Any Of The Available Jobs? (Y/y or N/n)"
                                 << "\n\n\t\t\t\t\tEnter: ";
                            cin >> c;
                            if (c == 'Y' || c == 'y')
                            {
                                cin.ignore();
                                application.jobSeeker = jobSeekerName;
                                cout << "\n\t\t\t\t\tEnter the Job Title you want to apply for: ";
                                getline(cin, application.jobTitle);
                                cout << "\n\n\t\t\t\t\tEnter the Employer Name: ";
                                getline(cin, application.employerName);
                                applyForJob(application);
                            }
                        }
                        else
                        {
                            c = 'n';
                        }
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();

                    } while (c == 'Y' || c == 'y');

                    break;
                }

                // 5. View Applied Jobs By the current Job Seeker
                case 5:
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << "\t\t\t\t\t     ::Applied Jobs::" << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << endl
                         << endl;
                    viewAppliedJobs(jobSeekerName);
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                    getch();
                    break;
                }
                default:
                {
                    if (!choice == 0)
                    {
                        cout << "\n\t\t\t\t\tInvalid Input!! Please Try Again!!";
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                    }
                    break;
                }
                }

            } while (choice != 0);
        }
        else
        {
            cout << "\n\t\t\t\t\tDo you want to retry? (Y/y or N/n)" << endl
                 << "\n\t\t\t\t\tEnter: ";
            cin >> c;

            if (c == 'y' || c == 'Y')
            {
                goto RenterName;
            }
        }
    }
};

// login class
class Login
{
private:
    Admin admin;
    JobSeeker jobseeker;
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
             << "\t\t\t\t\t     ::Login As A Job Seeker::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;

        // authenticate the job seeker
        if (user_login_input(reg_type))
        {
            jobseeker.jobSeeker_func_call();
        }
    }

    // login as an employer
    void employer_login(int reg_type)
    {
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << "\t\t\t\t\t      ::Login As An Employer::" << endl
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
             << "\t\t\t\t\t       ::Login As An Admin::" << endl
             << "\t\t\t\t\t---------------------------------------" << endl
             << endl;

        // authenticate the job seeker
        if (user_login_input(reg_type))
        {
            admin.admin_func_call();
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
