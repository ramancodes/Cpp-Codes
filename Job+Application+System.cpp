// admin credentials -> username = admin, password = admin

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <conio.h>
#include <regex>
#include <cstdio>
#include <cstring>
#include <sstream>

using namespace std;

// registration class //done
class Registration
{
private:
    int choice;
    string user, pass, name;

    // Enumerator
    enum IN
    {
        IN_BACK = 8,
        IN_RET = 13
    };

    // Function that accepts the password
    std::string takePasswdFromUser(
        char sp = '*')
    {
        string passwd = "";
        char ch_ipt;
        while (true)
        {

            ch_ipt = getch();
            if (ch_ipt == IN::IN_RET)
            {
                cout << endl;
                return passwd;
            }
            else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
            {
                passwd.pop_back();
                cout << "\b \b";

                continue;
            }
            else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
            {
                continue;
            }

            passwd.push_back(ch_ipt);
            cout << sp;
        }
    }

    // register new user
    bool registerUser(const int &reg_type)
    {
        string filepath;
        map<string, pair<string, string>> users;
        switch (reg_type)
        {
        case 1:
            filepath = "jobseekers_credentials.txt";
            break;

        case 2:
            filepath = "employers_credentials.txt";
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
                string storedUsername, storedPassword, storedName;
                if (iss >> storedUsername >> storedPassword >> storedName)
                {
                    users[storedUsername] = make_pair(storedPassword, storedName);
                }
            }

            // Check if the username already exists
            if (users.find(user) != users.end())
            {
                cerr << "\n\t\t\t\t\tCannot use this Username. It already exists." << endl
                     << endl;
                return false;
            }
        }

        // Register the new user mapping
        users[user] = make_pair(pass, name);

        ofstream outFile(filepath);
        if (!outFile.is_open())
        {
            cerr << "\n\t\t\t\t\tError opening user file for writing." << endl
                 << endl;
            return false;
        }

        for (const auto &entry : users)
        {
            outFile << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
        }

        return true;
    }

    string removeSpaces(string inputString)
    {
        for (char &character : inputString)
        {
            if (character == ' ')
            {
                character = '_';
            }
        }
        return inputString;
    }

    string lowerString(string s)
    {
        string l;
        for (auto x : s)
        {

            l = l + (char)tolower(x);
        }
        return l;
    }

    string usernameTouserid(string inputString)
    {
        inputString = lowerString(inputString);
        int result = 0;
        string res;

        // Ensure that the string is not empty
        if (!inputString.empty())
        {
            // Iterate through the first 5 characters of the string
            for (int i = 0; i < inputString.length(); ++i)
            {
                // Add the ASCII code of each character to the result
                result += static_cast<int>(inputString[i]);

                // Shift the result left by 8 bits (equivalent to multiplying by 256)
                result <<= 8;
            }

            // Shift the result right by 8 bits to undo the last shift
            result >>= 8;
        }
        res = to_string(result);
        return res;
    }

    // take input (username & password) from the user
    void user_registration_input(int reg_type)
    {
        cin.ignore();
        cout << "\t\t\t\t\tEnter Your Name: ";
        getline(cin, name);
        name = removeSpaces(name);

        cout << "\t\t\t\t\tEnter username: ";
        cin >> user;
        user = usernameTouserid(user);

        cout << "\t\t\t\t\tEnter password: ";
        pass = takePasswdFromUser();
        pass = lowerString(pass);

        if (registerUser(reg_type))
        {
            char c;
            cout << "\n\t\t\t\t\tRegistration successful!" << endl
                 << endl;
            cout << "\t\t\t\t\tLogin To Continue." << endl
                 << endl;
            cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }
        else
        {
            cout << "\t\t\t\t\tRegistration failed." << endl;
            cout << "\t\t\t\t\tPress Enter Key To Continue ";
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
            break;
        }
    }
};

// class Job Application
class JobApplication
{
protected:
    struct ProfileData
    {
        string user_id;
        string name;
        string contact;
        string email;
        string dob;
        string qualification;
        string skills;
        string experience;
        string location;
    } profileData;

    struct JobData
    {
        string jobid;
        string user_id;
        string companyId;
        string companyName;
        string jobTitle;
        string requirements;
        string salary;
        string location;
        string issued_date;
        string end_date;
        string min_qualification;
        string vacancy;
    } jobData;

    string getCurrentDate()
    {
        time_t currentTime = time(nullptr);
        tm *localTime = localtime(&currentTime);
        int year = localTime->tm_year + 1900; // years since 1900
        int month = localTime->tm_mon + 1;    // months since January (0-based)
        int day = localTime->tm_mday;         // day of the month
        return (to_string(day) + "/" + to_string(month) + "/" + to_string(year));
    }

    string removeSpaces(string inputString)
    {
        for (char &character : inputString)
        {
            if (character == ' ')
            {
                character = '_';
            }
        }
        return inputString;
    }

    bool isValidContact(const string &input)
    {
        if (input.length() == 10)
        {
            for (char digit : input)
            {
                if (!isdigit(digit))
                {
                    return false; // Non-numeric character found
                }
            }
            return true; // All characters are digits
        }
        return false; // Incorrect length
    }

    string getUserContact()
    {
        string userInput;
        do
        {
            cin >> userInput;

            if (!isValidContact(userInput))
            {
                cout << "\n\t\t\t\t\tInvalid input. Please enter a 10-digit numeric value:";
            }

        } while (!isValidContact(userInput));

        return userInput;
    }

    bool isValidEmail(const string &email)
    {
        // Regular expression for a simple email validation
        regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

        return regex_match(email, emailRegex);
    }

    string getUserEmail()
    {
        string userEmail;

        do
        {
            cin >> userEmail;

            if (!isValidEmail(userEmail))
            {
                cout << "\n\t\t\t\t\tInvalid email address. Please enter a valid email:";
            }

        } while (!isValidEmail(userEmail));

        return userEmail;
    }


bool isDateValid(const string& dateStr, struct tm& date) {
    istringstream dateStream(dateStr);
    dateStream >> get_time(&date, "%d/%m/%Y");
    return !dateStream.fail();
}

int calculateAge(const struct tm& birthDate) {
    time_t currentTime = time(NULL);
    struct tm* today = localtime(&currentTime);

    int age = today->tm_year - birthDate.tm_year;
    if (today->tm_mon < birthDate.tm_mon || 
        (today->tm_mon == birthDate.tm_mon && today->tm_mday < birthDate.tm_mday)) {
        age--;
    }

    return age;
}

string getUserDateInput() {
    string input;
    struct tm birthDate = {};
    int age;

    do {
        cout << "\n\t\t\t\t\tEnter your birth date (DD/MM/YYYY): ";
        getline(cin, input);

        if (!isDateValid(input, birthDate)) {
            cout << "\n\t\t\t\t\tInvalid date format. Please try again.\n";
            continue;
        }

        age = calculateAge(birthDate);

        if (age <= 16) {
            cout << "\n\t\t\t\t\tAge must be greater than 16. Please enter a valid birth date.\n";
        }

    } while (age <= 16);

    return input;
}


    // Add Profile of job seeker //done -> need validation
    bool addprofile(const string filename, int updateflag = 0)
    {
        ProfileData newProfileData, itProfile;
        vector<ProfileData> profile, updatedProfile;
        newProfileData.user_id = profileData.user_id;
        newProfileData.name = profileData.name;
        string checkfilename = newProfileData.user_id + "_resume.txt";

        if (filename == checkfilename)
        {
            // read data from file -> resumes.txt
            ifstream applicantfile;
            applicantfile.open(filename);
            if (applicantfile)
            {
                string line;
                while (getline(applicantfile, line))
                {
                    istringstream iss(line);
                    if (iss >> itProfile.user_id >> itProfile.name >> itProfile.contact >> itProfile.email >> itProfile.dob >> itProfile.qualification >> itProfile.skills >> itProfile.experience)
                    {
                        profile.push_back(itProfile);
                    }
                }

                // Check if the job already exists
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        if (!updateflag)
                        {
                            cerr << "\n\t\t\t\t\tUser Profile Already Exists." << endl
                                 << endl;
                            return false;
                        }
                    }
                }
            }

            if (updateflag == 0 || updateflag == 1)
            {
                cout << "\n\t\t\t\t\tEnter contact: ";
                newProfileData.contact = getUserContact();
                cout << "\n\t\t\t\t\tEnter email: ";
                newProfileData.email = getUserEmail();
                cin.ignore();
                newProfileData.dob = getUserDateInput();
                cout << "\n\t\t\t\t\tEnter Job Qualification: \n";
                int c;
                cout << "\n\n\t\t\t\t\t1. MCA\n"
                     << "\n\t\t\t\t\t2. MBA\n"
                     << "\n\t\t\t\t\t3. M.Com.\n"
                     << "\n\t\t\t\t\t4. M.Sc.\n"
                     << "\n\t\t\t\t\t5. BCA\n"
                     << "\n\t\t\t\t\t6. BBA\n"
                     << "\n\t\t\t\t\t7. B.Com.\n"
                     << "\n\t\t\t\t\t8. B.Sc.\n"
                     << "\n\t\t\t\t\tEnter: ";
                cin >> c;
                switch (c)
                {
                case 1:
                    newProfileData.qualification = "MCA";
                    break;
                case 2:
                    newProfileData.qualification = "MBA";
                    break;
                case 3:
                    newProfileData.qualification = "M.Com.";
                    break;
                case 4:
                    newProfileData.qualification = "M.Sc.";
                    break;
                case 5:
                    newProfileData.qualification = "BCA";
                    break;
                case 6:
                    newProfileData.qualification = "BBA";
                    break;
                case 7:
                    newProfileData.qualification = "B.Com.";
                    break;
                case 8:
                    newProfileData.qualification = "B.Sc.";
                    break;
                default:
                    break;
                }
                cout << "\n\t\t\t\t\tEnter Skills: ";
                cin.ignore();
                getline(cin, newProfileData.skills);
                newProfileData.skills = removeSpaces(newProfileData.skills);
                // validation of salary
                // newProfileData.salary =
                cout << "\n\t\t\t\t\tEnter Experince(In Months): ";
                cin >> newProfileData.experience;
            }
            else if (updateflag == 2)
            {
                cout << "\n\t\t\t\t\tEnter contact: ";
                newProfileData.contact = getUserContact();
                // update contact
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.email = p.email;
                        newProfileData.dob = p.dob;
                        newProfileData.qualification = p.qualification;
                        newProfileData.skills = p.skills;
                        newProfileData.experience = p.experience;
                    }
                }
            }
            else if (updateflag == 3)
            {
                cout << "\n\t\t\t\t\tEnter email: ";
                newProfileData.email = getUserEmail();
                // add check email
                // update email
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.contact = p.contact;
                        newProfileData.dob = p.dob;
                        newProfileData.qualification = p.qualification;
                        newProfileData.skills = p.skills;
                        newProfileData.experience = p.experience;
                    }
                }
            }
            else if (updateflag == 4)
            {
                cout << "\n\t\t\t\t\tEnter DOB(DD/MM/YYYY): ";
                cin.ignore();
                newProfileData.dob = getUserDateInput();
                // update dob
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.contact = p.contact;
                        newProfileData.email = p.email;
                        newProfileData.qualification = p.qualification;
                        newProfileData.skills = p.skills;
                        newProfileData.experience = p.experience;
                    }
                }
            }
            else if (updateflag == 5)
            {
                cout << "\n\t\t\t\t\tEnter Job Qualification: \n";
                int c;
                cout << "\n\n\t\t\t\t\t1. MCA\n"
                     << "\n\t\t\t\t\t2. MBA\n"
                     << "\n\t\t\t\t\t3. M.Com.\n"
                     << "\n\t\t\t\t\t4. M.Sc.\n"
                     << "\n\t\t\t\t\t5. BCA\n"
                     << "\n\t\t\t\t\t6. BBA\n"
                     << "\n\t\t\t\t\t7. B.Com.\n"
                     << "\n\t\t\t\t\t8. B.Sc.\n"
                     << "\n\t\t\t\t\tEnter: ";
                cin >> c;
                switch (c)
                {
                case 1:
                    newProfileData.qualification = "MCA";
                    break;
                case 2:
                    newProfileData.qualification = "MBA";
                    break;
                case 3:
                    newProfileData.qualification = "M.Com.";
                    break;
                case 4:
                    newProfileData.qualification = "M.Sc.";
                    break;
                case 5:
                    newProfileData.qualification = "BCA";
                    break;
                case 6:
                    newProfileData.qualification = "BBA";
                    break;
                case 7:
                    newProfileData.qualification = "B.Com.";
                    break;
                case 8:
                    newProfileData.qualification = "B.Sc.";
                    break;
                default:
                    break;
                }
                // update qualification
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.contact = p.contact;
                        newProfileData.email = p.email;
                        newProfileData.dob = p.dob;
                        newProfileData.skills = p.skills;
                        newProfileData.experience = p.experience;
                    }
                }
            }
            else if (updateflag == 6)
            {
                cout << "\n\t\t\t\t\tEnter Skills: ";
                cin.ignore();
                getline(cin, newProfileData.skills);
                newProfileData.skills = removeSpaces(newProfileData.skills);
                // update skills
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.contact = p.contact;
                        newProfileData.email = p.email;
                        newProfileData.dob = p.dob;
                        newProfileData.qualification = p.qualification;
                        newProfileData.experience = p.experience;
                    }
                }
            }
            else if (updateflag == 8)
            {
                cout << "\n\t\t\t\t\tEnter Experince(In Months): ";
                cin >> newProfileData.experience;
                // update experience
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.contact = p.contact;
                        newProfileData.email = p.email;
                        newProfileData.dob = p.dob;
                        newProfileData.qualification = p.qualification;
                        newProfileData.skills = p.skills;
                    }
                }
            }

            if (updateflag)
            {
                // delete the data
                for (auto p : profile)
                {
                    if (p.user_id != newProfileData.user_id)
                    {
                        updatedProfile.push_back(p);
                    }
                }
                updatedProfile.push_back(newProfileData);
            }

            profile.push_back(newProfileData);

            // new job addition
            ofstream addition(filename);
            if (addition.is_open())
            {
                if (updateflag)
                {
                    for (auto s : updatedProfile)
                    {
                        addition << s.user_id << " " << s.name << " " << s.contact << " " << s.email << " " << s.dob << " " << s.qualification << " " << s.skills << " " << s.experience << endl;
                    }
                    cout << "\n\t\t\t\t\tProfile successfully Updated!" << endl;
                    return true;
                }
                for (auto s : profile)
                {
                    addition << s.user_id << " " << s.name << " " << s.contact << " " << s.email << " " << s.dob << " " << s.qualification << " " << s.skills << " " << s.experience << endl;
                }
                cout << "\n\t\t\t\t\tProfile successfully added!" << endl;
                return true;
            }
            cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
            return false;
        }
        else
        {
            // read data from file -> employers.txt
            ifstream applicantfile;
            applicantfile.open(filename);
            if (applicantfile)
            {
                string line;
                while (getline(applicantfile, line))
                {
                    istringstream iss(line);
                    if (iss >> itProfile.user_id >> itProfile.name >> itProfile.contact >> itProfile.email >> itProfile.location)
                    {
                        profile.push_back(itProfile);
                    }
                }

                // Check if the job already exists
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        if (!updateflag)
                        {
                            cerr << "\n\t\t\t\t\tUser Profile Already Exists." << endl
                                 << endl;
                            return false;
                        }
                    }
                }
            }

            if (updateflag == 0 || updateflag == 1)
            {
                cout << "\n\t\t\t\t\tEnter contact: ";
                newProfileData.contact = getUserContact();
                cout << "\n\t\t\t\t\tEnter email: ";
                newProfileData.email = getUserEmail();
                // add check email
                cout << "\n\t\t\t\t\tEnter Location: ";
                cin.ignore();
                getline(cin, newProfileData.location);
                newProfileData.location = removeSpaces(newProfileData.location);
            }
            else if (updateflag == 2)
            {
                cout << "\n\t\t\t\t\tEnter contact: ";
                newProfileData.contact = getUserContact();
                // update contact
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.email = p.email;
                        newProfileData.location = p.location;
                    }
                }
            }
            else if (updateflag == 3)
            {
                cout << "\n\t\t\t\t\tEnter email: ";
                newProfileData.email = getUserEmail();
                // add check email
                // update email
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.contact = p.contact;
                        newProfileData.location = p.location;
                    }
                }
            }
            else if (updateflag == 4)
            {
                cout << "\n\t\t\t\t\tEnter Location: ";
                cin.ignore();
                getline(cin, newProfileData.location);
                newProfileData.location = removeSpaces(newProfileData.location);
                // update skills
                for (auto p : profile)
                {
                    if (p.user_id == newProfileData.user_id)
                    {
                        newProfileData.contact = p.contact;
                        newProfileData.email = p.email;
                    }
                }
            }

            if (updateflag)
            {
                // delete the data
                for (auto p : profile)
                {
                    if (p.user_id != newProfileData.user_id)
                    {
                        updatedProfile.push_back(p);
                    }
                }
                updatedProfile.push_back(newProfileData);
            }

            profile.push_back(newProfileData);

            // new job addition
            ofstream addition(filename);
            if (addition.is_open())
            {
                if (updateflag)
                {
                    for (auto s : updatedProfile)
                    {
                        addition << s.user_id << " " << s.name << " " << s.contact << " " << s.email << " " << s.location << endl;
                    }
                    cout << "\n\t\t\t\t\tProfile successfully Updated!" << endl;
                    return true;
                }
                for (auto s : profile)
                {
                    addition << s.user_id << " " << s.name << " " << s.contact << " " << s.email << " " << s.location << endl;
                }
                cout << "\n\t\t\t\t\tProfile successfully added!" << endl;
                return true;
            }
            cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
            return false;
        }
        return false;
    }

    // show the Profile of current job seeker // done
    bool showProfile(const string filename)
    {
        ProfileData itProfile;
        vector<ProfileData> profile;
        string checkfilename = profileData.user_id + "_resume.txt";
        if (filename == checkfilename)
        {
            // read data from file -> resumes.txt
            ifstream applicantfile;
            applicantfile.open(filename);
            if (applicantfile)
            {
                string line;
                while (getline(applicantfile, line))
                {
                    istringstream iss(line);
                    if (iss >> itProfile.user_id >> itProfile.name >> itProfile.contact >> itProfile.email >> itProfile.dob >> itProfile.qualification >> itProfile.skills >> itProfile.experience)
                    {
                        profile.push_back(itProfile);
                    }
                }

                if (profile.empty())
                {
                    cout << "\n\t\t\t\t\tNo Profile Added." << endl;
                    return false;
                }

                // Check if the job already exists
                for (auto p : profile)
                {
                    if (p.user_id == profileData.user_id)
                    {
                        cout << "\n\t\t\t\t\t---------------------------------------------------------\n";
                        cout << "\n\t\t\t\t\t" << setw(20) << "UserId: " << setw(40) << p.user_id
                             << "\n\t\t\t\t\t" << setw(20) << "Name: " << setw(40) << p.name
                             << "\n\t\t\t\t\t" << setw(20) << "Contact: " << setw(40) << p.contact
                             << "\n\t\t\t\t\t" << setw(20) << "Email: " << setw(40) << p.email
                             << "\n\t\t\t\t\t" << setw(20) << "D.O.B.: " << setw(40) << p.dob
                             << "\n\t\t\t\t\t" << setw(20) << "Qualification: " << setw(40) << p.qualification
                             << "\n\t\t\t\t\t" << setw(20) << "Skills: " << setw(40) << p.skills
                             << "\n\t\t\t\t\t" << setw(20) << "Experince: " << setw(40) << p.experience
                             << endl;
                        cout << "\n\t\t\t\t\t---------------------------------------------------------\n";
                        return true;
                    }
                }
            }
            cerr << "\n\n\t\t\t\t\tError opening Profile file for reading." << endl;
            return false;
        }
        else
        {
            // read data from file -> resumes.txt
            ifstream applicantfile;
            applicantfile.open(filename);
            if (applicantfile)
            {
                string line;
                while (getline(applicantfile, line))
                {
                    istringstream iss(line);
                    if (iss >> itProfile.user_id >> itProfile.name >> itProfile.contact >> itProfile.email >> itProfile.location)
                    {
                        profile.push_back(itProfile);
                    }
                }

                if (profile.empty())
                {
                    cout << "\n\t\t\t\t\tNo Profile Added." << endl;
                    return false;
                }

                // Check if the job already exists
                for (auto p : profile)
                {
                    if (p.user_id == profileData.user_id)
                    {
                        cout << "\n\t\t\t\t\t------------------------------------------------------------\n";
                        cout << "\n\t\t\t\t\t" << setw(20) << "CompanyId: " << setw(40) << p.user_id
                             << "\n\t\t\t\t\t" << setw(20) << "Company Name: " << setw(40) << p.name
                             << "\n\t\t\t\t\t" << setw(20) << "Contact: " << setw(40) << p.contact
                             << "\n\t\t\t\t\t" << setw(20) << "Email: " << setw(40) << p.email
                             << "\n\t\t\t\t\t" << setw(20) << "Location: " << setw(40) << p.location
                             << endl;
                        cout << "\n\t\t\t\t\t------------------------------------------------------------\n";
                        return true;
                    }
                }
            }
            cerr << "\n\n\t\t\t\t\tError opening Profile file for reading." << endl;
            return false;
        }
        cerr << "\n\n\t\t\t\t\tError opening Profile file for reading." << endl;
        return false;
    }

    // Show all the jobs available in the application -> jobs.txt // done
    bool showJobs(string userId = "")
    {
        JobData itJob;
        vector<JobData> jobs;

        // read data from file -> jobs.txt
        ifstream jobFile;
        jobFile.open("jobs.txt");
        if (jobFile)
        {
            string line;
            while (getline(jobFile, line))
            {
                istringstream iss(line);
                if (iss >> itJob.jobid >> itJob.companyId >> itJob.companyName >> itJob.jobTitle >> itJob.requirements >> itJob.salary >> itJob.location >> itJob.issued_date >> itJob.end_date >> itJob.min_qualification >> itJob.vacancy)
                {
                    jobs.push_back(itJob);
                }
            }

            if (jobs.empty())
            {
                cout << "\n\t\t\t\t\tNo Jobs Available." << endl;
                return false;
            }

            // Check if the job already exists
            for (auto j : jobs)
            {
                if (userId.empty())
                {
                    cout << "\n\t\t\t\t\t--------------------------------------------------------------------------\n";
                    cout << "\n\t\t\t\t" << setw(30) << "Job Id: " << setw(40) << j.jobid
                         << "\n\t\t\t\t" << setw(30) << "Company Id: " << setw(40) << j.companyId
                         << "\n\t\t\t\t" << setw(30) << "Company Name: " << setw(40) << j.companyName
                         << "\n\t\t\t\t" << setw(30) << "Job Title: " << setw(40) << j.jobTitle
                         << "\n\t\t\t\t" << setw(30) << "Requirements: " << setw(40) << j.requirements
                         << "\n\t\t\t\t" << setw(30) << "Minimum Qualification: " << setw(40) << j.min_qualification
                         << "\n\t\t\t\t" << setw(30) << "Salary: " << setw(40) << j.salary
                         << "\n\t\t\t\t" << setw(30) << "Location: " << setw(40) << j.location
                         << "\n\t\t\t\t" << setw(30) << "Posted Date: " << setw(40) << j.issued_date
                         << "\n\t\t\t\t" << setw(30) << "End Date: " << setw(40) << j.end_date
                         << "\n\t\t\t\t" << setw(30) << "Vacancy: " << setw(40) << j.vacancy
                         << endl;
                    cout << "\n\t\t\t\t\t--------------------------------------------------------------------------\n";
                }
                else
                {
                    if (j.companyId == userId)
                    {
                        cout << "\n\t\t\t\t\t--------------------------------------------------------------------------\n";
                        cout << "\n\t\t\t\t" << setw(30) << "Job Id: " << setw(40) << j.jobid
                             << "\n\t\t\t\t" << setw(30) << "Company Id: " << setw(40) << j.companyId
                             << "\n\t\t\t\t" << setw(30) << "Company Name: " << setw(40) << j.companyName
                             << "\n\t\t\t\t" << setw(30) << "Job Title: " << setw(40) << j.jobTitle
                             << "\n\t\t\t\t" << setw(30) << "Requirements: " << setw(40) << j.requirements
                             << "\n\t\t\t\t" << setw(30) << "Minimum Qualification: " << setw(40) << j.min_qualification
                             << "\n\t\t\t\t" << setw(30) << "Salary: " << setw(40) << j.salary
                             << "\n\t\t\t\t" << setw(30) << "Location: " << setw(40) << j.location
                             << "\n\t\t\t\t" << setw(30) << "Posted Date: " << setw(40) << j.issued_date
                             << "\n\t\t\t\t" << setw(30) << "End Date: " << setw(40) << j.end_date
                             << "\n\t\t\t\t" << setw(30) << "Vacancy: " << setw(40) << j.vacancy
                             << endl;
                        cout << "\n\t\t\t\t\t--------------------------------------------------------------------------\n";
                    }
                }
            }
            return true;
        }
        cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
        return false;
    }

    // Show all the jobs available in the application -> jobs.txt // done
    bool showAppliedJobs(string userId)
    {
        JobData itJob;
        vector<JobData> jobs;

        // read data from file -> jobs.txt
        ifstream jobFile;
        string filename = userId + "_applications.txt";
        jobFile.open(filename);
        if (jobFile)
        {
            string line;
            while (getline(jobFile, line))
            {
                istringstream iss(line);
                if (iss >> itJob.jobid >> itJob.companyId >> itJob.companyName >> itJob.jobTitle >> itJob.requirements >> itJob.salary >> itJob.location >> itJob.issued_date >> itJob.end_date >> itJob.min_qualification)
                {
                    jobs.push_back(itJob);
                }
            }

            if (jobs.empty())
            {
                cout << "\n\t\t\t\t\tNo Jobs Available." << endl;
                return false;
            }

            // Check if the job already exists
            for (auto j : jobs)
            {
                    cout << "\n\t\t\t\t\t--------------------------------------------------------------------------\n";
                    cout << "\n\t\t\t\t" << setw(30) << "Job Id: " << setw(40) << j.jobid
                         << "\n\t\t\t\t" << setw(30) << "Company Id: " << setw(40) << j.companyId
                         << "\n\t\t\t\t" << setw(30) << "Company Name: " << setw(40) << j.companyName
                         << "\n\t\t\t\t" << setw(30) << "Job Title: " << setw(40) << j.jobTitle
                         << "\n\t\t\t\t" << setw(30) << "Requirements: " << setw(40) << j.requirements
                         << "\n\t\t\t\t" << setw(30) << "Minimum Qualification: " << setw(40) << j.min_qualification
                         << "\n\t\t\t\t" << setw(30) << "Salary: " << setw(40) << j.salary
                         << "\n\t\t\t\t" << setw(30) << "Location: " << setw(40) << j.location
                         << "\n\t\t\t\t" << setw(30) << "Posted Date: " << setw(40) << j.issued_date
                         << "\n\t\t\t\t" << setw(30) << "End Date: " << setw(40) << j.end_date
                         << endl;
                    cout << "\n\t\t\t\t\t--------------------------------------------------------------------------\n";
            }
            return true;
        }
        cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
        return false;
    }

    // update the Profile of the job seeker // done
    void updateProfile(const string filename)
    {
        string checkfilename = profileData.user_id + "_resume.txt";
        int ch;
        do
        {
            system("CLS");
            if (filename == checkfilename)
            {
                cout << endl
                     << endl
                     << "\t\t\t\t\t---------------------------------------" << endl
                     << "\t\t\t\t\t ::Update Job Seeker Profile::" << endl
                     << "\t\t\t\t\t---------------------------------------" << endl
                     << endl;
                cout << "\n\t\t\t\t\t1. Show Profile\n"
                     << "\n\t\t\t\t\t2. Update All\n"
                     << "\n\t\t\t\t\t3. Update Any Specific Data\n"
                     << "\n\t\t\t\t\t0. Exit\n"
                     << "\n\n\t\t\t\t\tEnter: ";
                cin >> ch;
                switch (ch)
                {
                case 1:
                    showProfile(filename); // done
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                    getch();
                    break;

                // 2. Update All
                case 2:
                    // addResume Function Initiated
                    addprofile(filename, 1); // done
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                    break;

                // update any specific data
                case 3:
                    int c;
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << "\t\t\t\t\t ::Update Job Seeker Profile::" << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << endl;
                    cout << "\n\t\t\t\t\t1. Update Contact No.\n"
                         << "\n\t\t\t\t\t2. Update Email\n"
                         << "\n\t\t\t\t\t3. Update D.O.B.(DD/MM/YYYY)\n"
                         << "\n\t\t\t\t\t4. Update Qualification\n"
                         << "\n\t\t\t\t\t5. Update Skills\n"
                         << "\n\t\t\t\t\t6. Update experience (months)\n"
                         << "\n\t\t\t\t\tEnter any other key to Exit\n"
                         << "\n\n\t\t\t\t\tEnter: ";
                    cin >> c;
                    switch (c)
                    {
                    // 3. Update Contact
                    case 1:
                        addprofile(filename, 2); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;

                    // 4. Update Email
                    case 2:
                        addprofile(filename, 3); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;

                    // 5. Update DOB
                    case 3:
                        addprofile(filename, 4); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;

                    // 6. Update Qualification
                    case 4:
                        addprofile(filename, 5); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;

                    // 7. Update Skills
                    case 5:
                        addprofile(filename, 6); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;

                    // 8. Update experience
                    case 6:
                        addprofile(filename, 7); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    default:
                        break;
                    }
                    break;

                default:
                    if (!ch == 0)
                    {
                        cout << "\n\t\t\t\t\tInvalid Input!! Please Try Again!!";
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                    }
                    break;
                }
            }
            else
            {
                cout << endl
                     << endl
                     << "\t\t\t\t\t---------------------------------------" << endl
                     << "\t\t\t\t\t ::Update Employers Profile::" << endl
                     << "\t\t\t\t\t---------------------------------------" << endl
                     << endl;
                cout << "\n\t\t\t\t\t1. Show Profile\n"
                     << "\n\t\t\t\t\t2. Update All\n"
                     << "\n\t\t\t\t\t3. Update Any Specific data\n"
                     << "\n\t\t\t\t\t0. Exit\n"
                     << "\n\n\t\t\t\t\tEnter: ";
                cin >> ch;
                switch (ch)
                {
                case 1:
                    showProfile(filename); // done
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                    getch();
                    break;

                // 2. Update All
                case 2:
                    // addResume Function Initiated
                    addprofile(filename, 1); // done
                    cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                    getch();
                    break;

                case 3:
                    system("CLS");
                    int c;
                    cout << endl
                         << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << "\t\t\t\t\t ::Update Employers Profile::" << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << endl;
                    cout << "\n\t\t\t\t\t1. Update Contact No.\n"
                         << "\n\t\t\t\t\t2. Update Email\n"
                         << "\n\t\t\t\t\t3. Update Location\n"
                         << "\n\t\t\t\t\tEnter any other key to Exit\n"
                         << "\n\n\t\t\t\t\tEnter: ";
                    cin >> c;
                    switch (c)
                    {
                    // 1. Update Contact
                    case 1:
                        addprofile(filename, 2); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;

                    // 2. Update Email
                    case 2:
                        addprofile(filename, 3); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;

                    // 3. Update Location
                    case 3:
                        addprofile(filename, 4); // done
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    default:
                        break;
                    }
                    break;

                default:
                    if (!ch == 0)
                    {
                        cout << "\n\t\t\t\t\tInvalid Input!! Please Try Again!!";
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                    }
                    break;
                }
            }
        } while (ch != 0);
    }

    // Remove or take back any job application //done
    bool removeJob(const string filename)
    {
        JobData itjob;
        vector<JobData> jobs, updatedJobs;
        ifstream rFile(filename);
        if (rFile.is_open())
        {
            string line;
            while (getline(rFile, line))
            {
                rFile >> itjob.jobid >> itjob.companyId >> itjob.companyName >> itjob.jobTitle >> itjob.requirements >> itjob.salary >> itjob.location >> itjob.issued_date >> itjob.end_date >> itjob.min_qualification >> itjob.vacancy;
                jobs.push_back(itjob);
            }

            if (jobs.empty())
            {
                cout << "\n\t\t\t\t\tNo Jobs Available" << endl;
                return false;
            }

            string del_id;
            cout << "\n\t\t\t\t\tEnter the job id that you want to delete: ";
            cin >> del_id;

            // delete the data
            for (auto j : jobs)
            {
                if (j.jobid != del_id)
                {
                    updatedJobs.push_back(j);
                }
            }

            ofstream wFile(filename);
            if (wFile.is_open())
            {
                for (auto j : updatedJobs)
                {
                    wFile << j.jobid << " " << j.companyId << " " << j.companyName << " " << j.jobTitle << " " << j.requirements << " " << j.salary << " " << j.location << " " << j.issued_date << " " << j.end_date << " " << j.min_qualification << " " << j.vacancy << endl;
                }
                cout << "\n\t\t\t\t\tThe Data has been deleted." << endl;
                return true;
            }
        }
        cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
        return false;
    }
};

// Job Seeker Class
class JobSeeker : private JobApplication
{
private:
    // apply for any job -> applications.txt  // to be solved
    bool applyForJob(string jobID)
    {
        JobData itjob, itjob1;
        vector<JobData> jobs, jobappled;
        string userid = profileData.user_id;
        string filename = userid + "_applications.txt";
        ifstream rFile(filename);
        if (rFile.is_open())
        {
            string line;
            while (getline(rFile, line))
            {
                istringstream iss(line);
                if (iss >> itjob1.jobid >> itjob1.companyId >> itjob1.companyName >> itjob1.jobTitle >> itjob1.requirements >> itjob1.salary >> itjob1.location >> itjob1.issued_date >> itjob1.end_date >> itjob1.min_qualification >> itjob1.vacancy)
                {
                    jobappled.push_back(itjob1);
                }
            }

            for (auto j : jobappled)
            {
                if (j.jobid == jobID)
                {
                    cout << "\n\t\t\t\t\tThe Job Is already applied\n";
                    return false;
                }
            }
        }

        ifstream jobFile("jobs.txt");
        if (jobFile.is_open())
        {
            string line;
            while (getline(jobFile, line))
            {
                istringstream iss(line);
                if (iss >> itjob.jobid >> itjob.companyId >> itjob.companyName >> itjob.jobTitle >> itjob.requirements >> itjob.salary >> itjob.location >> itjob.issued_date >> itjob.end_date >> itjob.min_qualification >> itjob.vacancy)
                {
                    jobs.push_back(itjob);
                }
            }
        }

        for (auto j : jobs)
        {
            if (jobID == j.jobid)
            {
                j.issued_date = getCurrentDate();
                jobappled.push_back(j);
                break;
            }
        }

        ofstream wFile(filename);
        if (wFile.is_open())
        {
            for (auto j : jobappled)
            {
                wFile << j.jobid << " " << j.companyId << " " << j.companyName << " " << j.jobTitle << " " << j.requirements << " " << j.salary << " " << j.location << " " << j.issued_date << " " << j.end_date << " " << j.min_qualification << endl;
            }
            cout << "\n\t\t\t\t\tThe Job has been Applied." << endl;
            return true;
        }
        cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
        return false;
    }

public:
    // Job seeker function call //done
    void jobSeeker_func_call(const string user, const string name)
    {
        int choice;
        char c;
        string jobId;
        profileData.user_id = user;
        profileData.name = name;
        string filename = user + "_resume.txt";
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
                // addResume Function Initiated
                addprofile(filename);
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;

            // 2. Show Resume
            case 2:
                showProfile(filename);
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;

            // 3. Update Resume
            case 3:
                // Update resume function initiated
                updateProfile(filename);
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;

            // 4. Search & Apply for Jobs Available
            case 4:
                do
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << "\t\t\t\t\t    ::Available Jobs::" << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << endl
                         << endl;
                    if (showJobs())
                    {
                        // apply for any job
                        cout << "\n\n\t\t\t\t\tDo You Want to Apply For Any Of The Available Jobs? (Y/y or N/n)"
                             << "\n\n\t\t\t\t\tEnter: ";
                        cin >> c;
                        if (c == 'Y' || c == 'y')
                        {
                            cout << "\n\n\t\t\t\t\tEnter the Job Id: ";
                            cin >> jobId;
                            applyForJob(jobId);
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

            case 5:
                system("CLS");
                cout << endl
                     << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << "\t\t\t\t\t    ::Applied Jobs::" << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << endl
                     << endl;
                showAppliedJobs(profileData.user_id);

                cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
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

// Employer Class
class Employer : private JobApplication
{
private:
    // add new job -> jobs.txt //done
    bool addNewJob()
    {
        JobData newJob;
        vector<JobData> jobs;
        newJob.companyId = profileData.user_id;
        newJob.companyName = profileData.name;
        cout << "\n\t\t\t\t\tEnter Job ID: ";
        cin >> newJob.jobid;

        // read data from file -> jobs.txt
        ifstream applicantfile;
        applicantfile.open("jobs.txt");
        if (applicantfile)
        {
            string line;
            while (getline(applicantfile, line))
            {
                istringstream iss(line);
                if (iss >> jobData.jobid >> jobData.companyId >> jobData.companyName >> jobData.jobTitle >> jobData.requirements >> jobData.salary >> jobData.location >> jobData.issued_date >> jobData.end_date >> jobData.min_qualification >> jobData.vacancy)
                {
                    jobs.push_back(jobData);
                }
            }

            // Check if the job already exists
            for (auto j : jobs)
            {
                if (j.jobid == newJob.jobid)
                {
                    cerr << "\n\t\t\t\t\tJob already Added With This Job Id." << endl
                         << endl;
                    return false;
                }
            }
        }

        cout << "\n\t\t\t\t\tEnter Job Title: ";
        cin.ignore();
        getline(cin, newJob.jobTitle);
        newJob.jobTitle = removeSpaces(newJob.jobTitle);
        cout << "\n\t\t\t\t\tEnter Job Description: ";
        getline(cin, newJob.requirements);
        newJob.requirements = removeSpaces(newJob.requirements);
        cout << "\n\t\t\t\t\tEnter Salary: ";
        cin >> newJob.salary;
        // validation of salary
        // newJob.salary =
        cout << "\n\t\t\t\t\tEnter Location: ";
        cin.ignore();
        getline(cin, newJob.location);
        newJob.location = removeSpaces(newJob.location);
        // set time of job posted
        newJob.issued_date = getCurrentDate();
        newJob.vacancy = "1";
        cout << "\n\t\t\t\t\tEnter Minimum Job Qualification: \n";
        int c;
        cout << "\n\n\t\t\t\t\t1. MCA\n"
             << "\n\t\t\t\t\t2. MBA\n"
             << "\n\t\t\t\t\t3. M.Com.\n"
             << "\n\t\t\t\t\t4. M.Sc.\n"
             << "\n\t\t\t\t\t5. BCA\n"
             << "\n\t\t\t\t\t6. BBA\n"
             << "\n\t\t\t\t\t7. B.Com.\n"
             << "\n\t\t\t\t\t8. B.Sc.\n"
             << "\n\t\t\t\t\tEnter: ";
        cin >> c;
        switch (c)
        {
        case 1:
            newJob.min_qualification = "MCA";
            break;
        case 2:
            newJob.min_qualification = "MBA";
            break;
        case 3:
            newJob.min_qualification = "M.Com.";
            break;
        case 4:
            newJob.min_qualification = "M.Sc.";
            break;
        case 5:
            newJob.min_qualification = "BCA";
            break;
        case 6:
            newJob.min_qualification = "BBA";
            break;
        case 7:
            newJob.min_qualification = "B.Com.";
            break;
        case 8:
            newJob.min_qualification = "B.Sc.";
            break;
        default:
            break;
        }
        cout << "\n\t\t\t\t\tEnter End date: ";
        cin >> newJob.end_date;

        // new job addition
        ofstream applicationFile("jobs.txt", ios::app);
        if (applicationFile.is_open())
        {
            applicationFile << newJob.jobid << " " << newJob.companyId << " " << newJob.companyName << " " << newJob.jobTitle << " " << newJob.requirements << " " << newJob.salary << " " << newJob.location << " " << newJob.issued_date << " " << newJob.end_date << " " << newJob.min_qualification << " " << newJob.vacancy << endl;
            cout << "\n\t\t\t\t\tJob successfully added!" << endl;
            return true;
        }
        cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
        return false;
    }

public:
    // Employer function call
    void employer_func_call(const string userid, const string name)
    {
        int choice;
        char c;
        string jobId;
        profileData.user_id = userid;
        profileData.name = name;
        string filename = userid + "_profile.txt";
        do
        {
            system("CLS");
            cout << endl
                 << endl
                 << "\t\t\t\t\t--------------------------------------" << endl
                 << "\t\t\t\t\t  ::Welcome to Employer Section!::" << endl
                 << "\t\t\t\t\t--------------------------------------" << endl
                 << endl
                 << endl
                 << "\t\t\t\t\t1. Add Employer Profile\n"
                 << "\t\t\t\t\t2. Show Employer Profile\n"
                 << "\t\t\t\t\t3. Update Employer Profile\n"
                 << "\t\t\t\t\t4. Add New Job\n"
                 << "\t\t\t\t\t5. Show All Jobs and Vacancies\n"
                 << "\t\t\t\t\t6. Remove Jobs\n"
                 << "\t\t\t\t\t0. Exit\n"
                 << "\n\t\t\t\t\tEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            // 1. Add Employer Profile
            case 1:
                // saveEmployerProfile Function Initiated
                addprofile(filename);
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;

            // 2. Update Employer Profile
            case 2:
                showProfile(filename);
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;

            // 2. Show Employer Profile
            case 3:
                updateProfile(filename);
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;

            // 3. Add New Job
            case 4:
                addNewJob();
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;

            // 4. Show All Jobs Available
            case 5:
                system("CLS");
                cout << endl
                     << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << "\t\t\t\t\t    ::Available Jobs::" << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << endl
                     << endl;
                showJobs(profileData.user_id);

                cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                getch();
                break;

            // 6. Remove Jobs
            case 6:
                do
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << "\t\t\t\t\t    ::Available Jobs::" << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << endl
                         << endl;
                    if (showJobs(profileData.user_id))
                    {
                        removeJob("jobs.txt");
                        cout << "\n\n\t\t\t\t\tDo You Want To Delete More Jobs? (Y/y or N/n)"
                             << "\n\n\t\t\t\t\tEnter: ";
                        cin >> c;
                    }
                    else
                    {
                        c = 'n';
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                } while (c == 'Y' || c == 'y');
                break;

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
};

// class admin functions //done
class Admin : private JobApplication
{
private:
    string username, password, name;

    bool show_users(const int &reg_type)
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

        default:
            break;
        }

        // Read existing user credentials from file
        ifstream userFile;
        userFile.open(filepath);

        if (userFile)
        {
            map<string, pair<string, string>> users;

            // Populate map with username-password pairs from the file
            string line;
            while (getline(userFile, line))
            {
                istringstream iss(line);
                string storedUsername, storedPassword, storedName;
                if (iss >> storedUsername >> storedPassword >> storedName)
                {
                    users[storedUsername] = make_pair(storedPassword, storedName);
                }
            }

            if (users.empty())
            {
                cout << "\n\t\t\t\t\tNo users Found." << endl;
                return false;
            }

            cout << "\n\t\t\t\t\t" << setw(20) << "UserId" << setw(20) << "Name" << setw(20) << "Password" << endl
                 << endl;

            for (const auto &entry : users)
            {
                cout << "\t\t\t\t\t" << setw(20) << entry.first << setw(20) << entry.second.second << setw(20) << entry.second.first << endl;
            }
            return true;
        }

        cerr << "\n\t\t\t\t\tError opening user file." << endl;
        return false;
    }

    string removeSpaces(string inputString)
    {
        for (char &character : inputString)
        {
            if (character == ' ')
            {
                character = '_';
            }
        }
        return inputString;
    }

    string lowerString(string s)
    {
        string l;
        for (auto x : s)
        {

            l = l + (char)tolower(x);
        }
        return l;
    }

    // edit the password of any user
    bool edit_password(const int &reg_type)
    {
        string filepath;
        string newPassword, newName;
        switch (reg_type)
        {
        case 1:
            filepath = "jobseekers_credentials.txt";
            break;

        case 2:
            filepath = "employers_credentials.txt";
            break;

        default:
            break;
        }

        // Read existing user credentials from file
        ifstream userFile;
        userFile.open(filepath);

        if (userFile)
        {
            map<string, pair<string, string>> users;

            // Populate map with username-password pairs from the file
            string line;
            while (getline(userFile, line))
            {
                istringstream iss(line);
                string storedUsername, storedPassword, storedName;
                if (iss >> storedUsername >> storedPassword >> storedName)
                {
                    users[storedUsername] = make_pair(storedPassword, storedName);
                }
            }

            // Check if the username exists
            auto it = users.find(username);
            if (it != users.end())
            {
                int c;
                cout << "\n\t\t\t\t\t1. Change both Password & Name." << endl
                     << "\n\t\t\t\t\t2. Change Password." << endl
                     << "\n\t\t\t\t\t3. Change Name." << endl
                     << "\n\t\t\t\t\tEnter: ";
                cin >> c;
                switch (c)
                {
                case 1:
                    // Enter the new password from the user
                    cout << "\n\t\t\t\t\tEnter the new name: ";
                    cin.ignore();
                    getline(cin, newName);
                    newName = removeSpaces(newName);
                    // Enter the new password from the user
                    cout << "\n\t\t\t\t\tEnter the new password: ";
                    cin >> newPassword;
                    newPassword = lowerString(newPassword);
                    // Update the user's password
                    it->second.first = newPassword;
                    // Update the user's password
                    it->second.second = newName;
                    break;

                case 2:
                    // Enter the new password from the user
                    cout << "\n\t\t\t\t\tEnter the new password: ";
                    cin >> newPassword;
                    newPassword = lowerString(newPassword);
                    // Update the user's password
                    it->second.first = newPassword;
                    break;

                case 3:
                    // Enter the new name from the user
                    cout << "\n\t\t\t\t\tEnter the new name: ";
                    cin.ignore();
                    getline(cin, newName);
                    newName = removeSpaces(newName);
                    // Update the user's password
                    it->second.second = newName;
                    break;

                default:
                    cout << "\n\t\t\t\t\tInvalid Input.";
                    return false;
                    break;
                }

                // Write the updated user credentials to the file
                ofstream outFile(filepath);
                if (!outFile.is_open())
                {
                    cerr << "\n\t\t\t\t\tError opening user file for writing." << endl;
                    return false;
                }

                for (const auto &entry : users)
                {
                    outFile << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
                }

                cout << "\n\t\t\t\t\tCredentials for user: " << username << " has been changed successfully." << endl;
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
    bool remove_user(const int &reg_type)
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

        default:
            break;
        }

        // Read existing user credentials from file
        ifstream userFile;
        userFile.open(filepath);
        if (userFile)
        {

            map<string, pair<string, string>> users;

            // Populate map with username-password pairs from the file
            string line;
            while (getline(userFile, line))
            {
                istringstream iss(line);
                string storedUsername, storedPassword, storedName;
                if (iss >> storedUsername >> storedPassword >> storedName)
                {
                    users[storedUsername] = make_pair(storedPassword, storedName);
                }
            }

            // Check if the username exists
            if (users.find(username) != users.end())
            {
                if (reg_type == 1)
                {
                    remove((username + "_resume.txt").c_str());
                    remove((username + "_applications.txt").c_str());
                }
                else
                {
                    remove((username + "_profile.txt").c_str());
                }

                // Remove the user & file
                users.erase(username);

                // Write the updated user credentials to the file
                ofstream outFile(filepath);
                if (!outFile.is_open())
                {
                    cerr << "\n\t\t\t\t\tError opening user file for writing." << endl;
                    return false;
                }

                for (const auto &entry : users)
                {
                    outFile << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
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
                 << "\t\t\t\t\t1. Show All Job Seekers" << endl
                 << "\t\t\t\t\t2. Show All Employers" << endl
                 << "\t\t\t\t\t3. Remove Job Seeker" << endl
                 << "\t\t\t\t\t4. Remove Employer" << endl
                 << "\t\t\t\t\t5. Change Job Seeker Name & Password" << endl
                 << "\t\t\t\t\t6. Change Employer Name & Password" << endl
                 << "\t\t\t\t\t7. Show All Jobs" << endl
                 << "\t\t\t\t\t8. Remove Any Job" << endl
                 << "\t\t\t\t\t0. Log Out" << endl
                 << endl
                 << "\t\t\t\t\tEnter: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                show_users(1);
                cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                getch();
                break;

            case 2:
                show_users(2);
                cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                getch();
                break;

            case 3:
                if (show_users(1))
                {
                    cout << "\n\t\t\t\t\tEnter username: ";
                    cin >> username;
                    if (remove_user(1))
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                    getch();
                }

                break;

            case 4:
                if (show_users(2))
                {
                    cout << "\n\t\t\t\t\tEnter username: ";
                    cin >> username;
                    if (remove_user(2))
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                    getch();
                }
                break;

            case 5:
                if (show_users(1))
                {
                    cout << "\n\t\t\t\t\tEnter username: ";
                    cin >> username;
                    if (edit_password(1))
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                    getch();
                }
                break;

            case 6:
                if (show_users(2))
                {
                    cout << "\n\t\t\t\t\tEnter username: ";
                    cin >> username;
                    if (edit_password(2))
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                }
                else
                {
                    cout << "\n\t\t\t\t\tPress Enter Key To Exit ";
                    getch();
                }
                break;

            case 7:
                system("CLS");
                cout << endl
                     << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << "\t\t\t\t\t    ::Available Jobs::" << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << endl
                     << endl;
                showJobs();
                cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                getch();
                break;

            case 8:
                char c;
                do
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << "\t\t\t\t\t    ::Available Jobs::" << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << endl
                         << endl;
                    if (showJobs())
                    {
                        removeJob("jobs.txt");
                        cout << "\n\n\t\t\t\t\tDo You Want To Delete More Jobs? (Y/y or N/n)"
                             << "\n\n\t\t\t\t\tEnter: ";
                        cin >> c;
                    }
                    else
                    {
                        c = 'n';
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                        getch();
                    }
                } while (c == 'Y' || c == 'y');
                break;
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

// login class // done
class Login
{
private:
    string user, pass, name;
    int choice;

    // Enumerator
    enum IN
    {
        IN_BACK = 8,
        IN_RET = 13
    };

    // authenticate a user
    bool authenticateUser(const int &reg_type)
    {
        string filepath;
        map<string, pair<string, string>> users;

        // select file path
        switch (reg_type)
        {
        case 1:
            filepath = "jobseekers_credentials.txt";
            break;

        case 2:
            filepath = "employers_credentials.txt";
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
                string storedUsername, storedPassword, storedName;
                if (iss >> storedUsername >> storedPassword >> storedName)
                {
                    users[storedUsername] = make_pair(storedPassword, storedName);
                }
            }

            // Check if the provided username exists and the password matches
            auto it = users.find(user);
            if (it != users.end() && it->second.first == pass)
            {
                user = it->first;
                name = it->second.second;
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

    // Function that accepts the password
    std::string takePasswdFromUser(
        char sp = '*')
    {
        string passwd = "";
        char ch_ipt;
        while (true)
        {

            ch_ipt = getch();
            if (ch_ipt == IN::IN_RET)
            {
                cout << endl;
                return passwd;
            }
            else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
            {
                passwd.pop_back();
                cout << "\b \b";

                continue;
            }
            else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
            {
                continue;
            }

            passwd.push_back(ch_ipt);
            cout << sp;
        }
    }

    string lowerString(string s)
    {
        string l;
        for (auto x : s)
        {

            l = l + (char)tolower(x);
        }
        return l;
    }

    string usernameTouserid(string inputString)
    {
        inputString = lowerString(inputString);
        int result = 0;
        string res;

        // Ensure that the string is not empty
        if (!inputString.empty())
        {
            // Iterate through the first 5 characters of the string
            for (int i = 0; i < inputString.length(); ++i)
            {
                // Add the ASCII code of each character to the result
                result += static_cast<int>(inputString[i]);

                // Shift the result left by 8 bits (equivalent to multiplying by 256)
                result <<= 8;
            }

            // Shift the result right by 8 bits to undo the last shift
            result >>= 8;
        }
        res = to_string(result);
        return res;
    }

    // take input (username & password) from the user
    bool user_login_input(int reg_type)
    {
        string user_type;
        char c;

        cout << "\t\t\t\t\tEnter username: ";
        cin >> user;
        user = usernameTouserid(user);

        cout << "\t\t\t\t\tEnter password: ";
        pass = takePasswdFromUser();
        pass = lowerString(pass);

        bool flag = authenticateUser(reg_type);

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
            cout << "\n\t\t\t\t\tPress Enter Key To Continue ";
            getch();
        }

        return flag;
    }

    // login as a job seeker
    void jobseeker_login(int reg_type)
    {
        JobSeeker js;
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
            js.jobSeeker_func_call(user, name);
        }
    }

    // login as an employer
    void employer_login(int reg_type)
    {
        Employer em;
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
            em.employer_func_call(user, name);
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

        cout << "\t\t\t\t\tEnter username: ";
        cin >> user;

        cout << "\t\t\t\t\tEnter password: ";
        pass = takePasswdFromUser();

        // authenticate the admin
        if (user == "admin" && pass == "admin")
        {
            Admin admin;
            system("CLS");
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
             << "\t\t\t\t\t2. Employer Login" << endl
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
            break;
        }
    }
};

// main function //done
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
            break;
        }

    } while (choice != 0);

    return 0;
}
