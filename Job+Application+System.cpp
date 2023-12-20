#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <ctime>
#include <limits> // For numeric_limits
#include <sstream>
#include <iomanip>
#include <algorithm> // For count

using namespace std;

class Credentials
{
    string username;
    string password = "";
    string name;

public:
    string getUsername() const
    {
        return username;
    }

    string getPassword() const
    {
        return password;
    }

    string getName() const
    {
        return name;
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

    void userInput(int i = 0)
    {
        char ch;
        if (i != 0)
        {
            cout << "\t\t\t\t\tEnter Your Name: ";
            cin.ignore();
            getline(cin, name);
            int count = 0;
            for (int i = 0; i < name.length(); i++)
                if (name[i] != ' ')
                    name[count++] = name[i];
            name[count] = '\0';
        }

        cout << "\t\t\t\t\tEnter username: ";
        cin >> username;
        username = lowerString(username);

        cout << "\t\t\t\t\tEnter password: ";
        ch = getch();
        while (ch != 13)
        { // character 13 is enter
            password.push_back(ch);
            cout << '*';
            ch = getch();
        }
        password = lowerString(password);
    }

    void setName(string name)
    {
        this->name = name;
    }
};

class Data
{
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
    };

    struct ApplicationData
    {
        string jobId;
        string user_id;
    };

    struct JobData
    {
        string jobid;
        string companyId;
        string companyName;
        string jobTitle;
        string description;
        string requirements;
        string salary;
        string location;
        string posted_date;
    };

    bool isValidDateFormat(const string &dateStr)
    {
        tm tm = {};
        istringstream ss(dateStr);
        ss >> get_time(&tm, "%d/%m/%Y");
        return !ss.fail();
    }

    bool isValidEmail(const string &email)
    {
        // Check if there is exactly one '@' character and at least one '.' character
        size_t atSymbolCount = count(email.begin(), email.end(), '@');
        size_t dotCount = count(email.begin(), email.end(), '.');

        return (atSymbolCount == 1) && (dotCount >= 1);
    }

public:
    void setJobsekerData()
    {
        ProfileData resume;
        Credentials cred;
        cin.ignore(); // Ignore newline character left in the buffer
        resume.user_id = cred.getUsername();
        resume.name = cred.getName();
        // Enter contact
        setContact(resume);
        // Enter email
        setEmail(resume);
        // Enter dob
        setDOB(resume);
        // Enter Qualification
        setQualification(resume);
        // Enter skills
        setSkills(resume);
        // Enter Experience
        setExprience(resume);
    }

    void setEmployerData()
    {
        ProfileData empProfile;
        Credentials cred;
        cin.ignore(); // Ignore newline character left in the buffer
        empProfile.user_id = cred.getUsername();
        empProfile.name = cred.getName();
        // Enter contact
        setContact(empProfile);
        // Enter email
        setEmail(empProfile);
        // Enter location
        setLocation(empProfile);
    }

    void setJobData()
    {
        JobData jobData;
        Credentials cred;
        cin.ignore(); // Ignore newline character left in the buffer
        jobData.companyId = cred.getUsername();
        jobData.companyName = cred.getName();
        // Enter job id
        cout << "\n\n\t\t\t\t\tEnter Job ID: ";
        getline(cin, jobData.jobid);
        // Enter job title
        cout << "\n\n\t\t\t\t\tEnter Job Title: ";
        getline(cin, jobData.jobTitle);
        // Enter description
        cout << "\t\t\t\t\tEnter job descriptoin: ";
        getline(cin, jobData.description);
        // Enter requirents
        cout << "\t\t\t\t\tEnter Location: ";
        getline(cin, jobData.requirements);
        // Enter salary
        cout << "\t\t\t\t\tEnter Salary: ";
        // Input validation loop
        while (!(cin >> jobData.salary) || cin.peek() != '\n')
        {
            cin.clear();                                         // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\n\t\t\t\t\tInvalid input. \n\t\t\t\t\tPlease enter valid salary: ";
        }
        // Enter location
        cout << "\t\t\t\t\tEnter Location: ";
        getline(cin, jobData.location);

        // set time of job posted
        time_t t = time(0);
        tm *now = localtime(&t);
        int y = now->tm_year + 1900;
        int m = 1 + now->tm_mon;
        int d = now->tm_mday;
        string date = to_string(d) + "/" + to_string(m) + "/" + to_string(y);
        jobData.posted_date = date;
    }

    void setApplcationData(string jobID)
    {
        ApplicationData appData;
        ProfileData profData;
        appData.user_id = profData.user_id;
        appData.jobId = jobID;
    }

    void setContact(ProfileData d)
    {
        cout << "\n\t\t\t\t\tEnter Contact: ";
        while (!(cin >> d.contact) || cin.peek() != '\n')
        {
            cin.clear();                                         // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\n\t\t\t\t\tInvalid input. \n\t\t\t\t\tPlease enter a valid contact: ";
        }
    }

    void setEmail(ProfileData d)
    {
        cout << "\n\t\t\t\t\tEnter Email: ";
        cin.ignore();
        // Input validation loop
        while (true)
        {
            getline(cin, d.email);

            if (isValidEmail(d.email))
            {
                break; // Exit loop if the email is valid
            }
            else
            {
                cout << "\t\t\t\t\tInvalid email address. \n\t\t\t\t\tPlease enter a valid email: ";
            }
        }
    }

    void setDOB(ProfileData d)
    {
        cout << "\n\t\t\t\t\tEnter D.O.B.(DD/MM/YYYY): ";
        cin.ignore();
        // Input validation loop
        while (true)
        {
            getline(cin, d.dob);

            if (isValidDateFormat(d.dob))
            {
                break; // Exit loop if the date is valid
            }
            else
            {
                cout << "\n\t\t\t\t\tInvalid date format. \n\t\t\t\t\tPlease enter a valid date in the format DD/MM/YYYY: ";
            }
        }
    }

    void setQualification(ProfileData d)
    {
        int c;
        cout << "\n\t\t\t\t\tEnter Qualification: ";
        cout << "\n\t\t\t\t\t1. MCA\n"
             << "\n\t\t\t\t\t2. MBA\n"
             << "\n\t\t\t\t\t3. M.Com.\n"
             << "\n\t\t\t\t\t4. M.Sc.\n"
             << "\n\t\t\t\t\t5. BCA\n"
             << "\n\t\t\t\t\t6. BBA\n"
             << "\n\t\t\t\t\t7. B.Com.\n"
             << "\n\t\t\t\t\t8. B.Sc.\n"
             << "\nEnter: ";
        cin >> c;
        switch (c)
        {
        case 1:
            d.qualification = "MCA";
            break;
        case 2:
            d.qualification = "MBA";
            break;
        case 3:
            d.qualification = "M.Com.";
            break;
        case 4:
            d.qualification = "M.Sc.";
            break;
        case 5:
            d.qualification = "BCA";
            break;
        case 6:
            d.qualification = "BBA";
            break;
        case 7:
            d.qualification = "B.Com.";
            break;
        case 8:
            d.qualification = "B.Sc.";
            break;
        default:
            break;
        }
    }

    void setSkills(ProfileData d)
    {
        cout << "\n\t\t\t\t\tEnter Skills: ";
        cin.ignore();
        getline(cin, d.skills);
    }

    void setExprience(ProfileData d)
    {
        cout << "\n\t\t\t\t\tEnter Experience: ";
        cin.ignore();
        getline(cin, d.experience);
    }

    void setLocation(ProfileData d)
    {
        cout << "\n\t\t\t\t\tEnter Location: ";
        cin.ignore();
        getline(cin, d.location);
    }

    ProfileData getProfile()
    {
        ProfileData profile;
        return profile;
    }

    JobData getJobData()
    {
        JobData jobData;
        return jobData;
    }

    ApplicationData getApplicationData()
    {
        ApplicationData appData;
        return appData;
    }
};

// registration class
class Registration
{
private:
    int choice;

    // register new user
    bool registerUser(const Credentials cred, const int &reg_type)
    {
        string filepath;
        string user, user_name;
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
        // check if the exists or not
        if (file)
        {
            user = cred.getUsername() + "|" + cred.getPassword();
            string line;
            while (getline(file, line))
            {
                // Check if the provided username exists and the password matches
                if (user == line)
                {
                    cout << "\n\t\t\t\t\tUsernaame Already exists" << endl;
                    file.close();
                    return false;
                }
            }
        }

        // Register the new user mapping
        user = cred.getUsername() + "|" + cred.getPassword() + "\n";
        user_name = cred.getUsername() + "|" + cred.getName() + "\n";

        ofstream outFile(filepath, ios::app);
        ofstream outNameFile("names.txt", ios::app);
        if (outFile.is_open())
        {
            outFile.write(user.c_str(), user.size());
            outNameFile.write(user_name.c_str(), user.size());
            cout << "\n\t\t\t\t\tProfile saved successfully!" << endl;
            return true;
        }

        cerr << "\n\t\t\t\t\tError opening user file for writing." << endl
             << endl;
        return false;
    }

    // take input (username & password) from the user
    void user_registration_input(int reg_type)
    {
        Credentials cred;
        cred.userInput(1);

        if (registerUser(cred, reg_type))
        {
            char c;
            cout << "\n\t\t\t\t\tRegistration successful!" << endl
                 << endl;
            cout << "\t\t\t\t\tLogin To Continue." << endl
                 << endl;
            // redirect to the login screen
            cout << "\n\t\t\t\t\tNow You Can Login To the Application";
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

class JobApplication
{
protected:
    Credentials cred;
    Data data;

    // Add Profile of job seeker
    bool add(const string filename)
    {
        ifstream userFile;
        userFile.open(filename);
        if (!userFile)
        {
            cerr << "\n\t\t\t\t\tProfile File Unavailable." << endl;
            return false;
        }
        else
        {
            string userProfile;
            while (getline(userFile, userProfile))
            {
                size_t pos = userProfile.find("|");
                string id = userProfile.substr(0, pos);
                if (id == data.getProfile().user_id)
                {
                    cout << "\n\t\t\t\t\tProfile already exists." << endl
                         << endl;
                    return false;
                }
            }
        }

        ofstream ProfileFile(filename, ios::app);
        if (ProfileFile.is_open())
        {
            string prof;
            if (filename == "resumes.txt")
            {
                prof = data.getProfile().user_id + "|" + data.getProfile().name + "|" + data.getProfile().contact + "|" + data.getProfile().email + "|" + data.getProfile().dob + "|" + data.getProfile().qualification + "|" + data.getProfile().skills + "|" + data.getProfile().experience + "\n";
                ProfileFile.write(prof.c_str(), prof.size());
            }
            else
            {
                prof = data.getProfile().user_id + "|" + data.getProfile().name + "|" + data.getProfile().contact + "|" + data.getProfile().email + "|" + data.getProfile().location + "\n";
                ProfileFile.write(prof.c_str(), prof.size());
            }
            cout << "\n\t\t\t\t\tProfile saved successfully!" << endl;
            return true;
        }
        else
        {
            cerr << "\n\t\t\t\t\tError opening Profile file for writing." << endl;
            return false;
        }
    }

    // show the Profile of current job seeker
    bool showProfile(const string filename)
    {
        ifstream ProfileFile;
        ProfileFile.open(filename);
        if (ProfileFile)
        {
            string line;
            while (getline(ProfileFile, line))
            {
                size_t pos = line.find("|");
                string id = line.substr(0, pos);
                if (id == data.getApplicationData().user_id)
                {
                    if (filename == "resumes.txt")
                    {
                        cout << "\n\n\t\t\t\t\tProfile for " << id << ": "
                             << "\n\t\t\t\t\tName: " << data.getProfile().name
                             << "\n\t\t\t\t\tContact: " << data.getProfile().contact
                             << "\n\t\t\t\t\tEmail: " << data.getProfile().email
                             << "\n\t\t\t\t\tDOB: " << data.getProfile().dob
                             << "\n\t\t\t\t\tQualification: " << data.getProfile().qualification
                             << "\n\t\t\t\t\tSkills: " << data.getProfile().skills
                             << "\n\t\t\t\t\tExprience: " << data.getProfile().experience;
                        return true;
                    }
                    else
                    {
                        cout << "\n\n\t\t\t\t\tProfile for " << id << ": "
                             << "\n\t\t\t\t\tName: " << data.getProfile().name
                             << "\n\t\t\t\t\tContact: " << data.getProfile().contact
                             << "\n\t\t\t\t\tEmail: " << data.getProfile().email
                             << "\n\t\t\t\t\tDOB: " << data.getProfile().location;
                        return true;
                    }
                }
            }
            cout << "\n\n\t\t\t\t\tProfile not found for " << data.getApplicationData().user_id << "." << endl;
            return false;
        }
        cerr << "\n\n\t\t\t\t\tError opening Profile file for reading." << endl;
        return false;
    }

    // update the Profile of the job seeker
    void updateProfile(const string filename)
    {
        ifstream ProfileFile(filename);
        if (ProfileFile.is_open())
        {
            vector<string> lines;
            string line;
            while (getline(ProfileFile, line))
            {
                size_t pos = line.find("|");
                string id = line.substr(0, pos);
                if (id == data.getProfile().user_id)
                {
                    if (filename == "resumes.txt")
                    {
                        lines.push_back(data.getProfile().user_id + "|" + data.getProfile().name + "|" + data.getProfile().contact + "|" + data.getProfile().email + "|" + data.getProfile().dob + "|" + data.getProfile().qualification + "|" + data.getProfile().skills + "|" + data.getProfile().experience);
                    }
                    else
                    {
                        lines.push_back(data.getProfile().user_id + "|" + data.getProfile().name + "|" + data.getProfile().contact + "|" + data.getProfile().email + "|" + data.getProfile().location);
                    }
                }
                else
                {
                    lines.push_back(line);
                }
            }

            // Write the updated Profiles back to the file
            ofstream outFile(filename);
            if (outFile.is_open())
            {
                for (const auto &updatedLine : lines)
                {
                    outFile << updatedLine << endl;
                }
                cout << "\n\t\t\t\t\tProfile updated successfully!" << endl;
            }
            else
            {
                cerr << "\n\t\t\t\t\tNo Profile available. Please add your Profile." << endl;
            }
        }
        else
        {
            cerr << "\n\t\t\t\t\tError opening Profile file for reading." << endl;
        }
    }

    // Show all the jobs available in the application -> jobs.txt
    bool showJobs(string userId = "", string applicantjobId = "")
    {
        ifstream jobFile;
        jobFile.open("jobs.txt");
        if (jobFile)
        {
            string line;
            while (getline(jobFile, line))
            {
                size_t pos = line.find("|");
                string jobId = line.substr(0, pos);
                string jobDetails = line.substr(pos + 1);
                if (userId.empty() && applicantjobId.empty())
                {
                    cout << "\n\n\t\t\t\t\tJob ID: " << jobId << endl;
                    cout << "\n\t\t\t\t\tJob Details: " << jobDetails << endl;
                }
                else
                {
                    pos = jobId.find("/");
                    string jid = jobId.substr(0, pos);
                    string compId = jobId.substr(pos + 1);
                    string newjobId = jid + "/" + userId;
                    if (jobId == newjobId)
                    {
                        cout << "\n\n\t\t\t\t\tJob ID: " << jobId << endl;
                        cout << "\n\t\t\t\t\tJob Details: " << jobDetails << endl;
                    }
                }
            }
            return true;
        }
        cout << "\n\t\t\t\t\tNo Jobs Available" << endl;
        return false;
    }

    // show all the applied jobs -> applications.txt
    bool viewAppliedJobs()
    {
        ifstream applicationFile("applications.txt");
        if (applicationFile.is_open())
        {
            string line;
            while (getline(applicationFile, line))
            {
                size_t pos = line.find("|");
                string userId = line.substr(0, pos);
                if (userId == data.getApplicationData().user_id)
                {
                    string jobId = line.substr(pos + 1);
                    showJobs("", jobId);
                }
                else
                {
                    cout << "\n\t\t\t\t\tNo jobs applied.";
                    return false;
                }
            }
            return true;
        }
        cerr << "\n\t\t\t\t\tError opening application file for reading." << endl;
        return false;
    }

    // Remove or take back any job application
    bool removeJob(const string jobId, const string filename)
    {
        ifstream file;
        file.open(filename);
        if (!file)
        {
            cerr << "\n\t\t\t\t\tYou don't have any job.";
            return false;
        }
        else
        {
            vector<string> lines;
            string line;
            while (getline(file, line))
            {
                size_t pos = line.find("|");
                string ID = line.substr(0, pos);
                if (filename == "applications.txt")
                {
                    string joId = line.substr(pos + 1);
                    if (!(ID == data.getApplicationData().user_id && joId == jobId))
                    {
                        lines.push_back(line);
                    }
                }
                else
                {
                    string newjobId = jobId + "/" + data.getProfile().user_id;
                    if (!(newjobId == ID))
                    {
                        lines.push_back(line);
                    }
                }
            }

            // Write the updated jobs back to the file
            ofstream outFile(filename);
            if (outFile.is_open())
            {
                for (const auto &updatedLine : lines)
                {
                    outFile << updatedLine << endl;
                }
                cout << "\n\t\t\t\t\tJob removed successfully!" << endl;
                return true;
            }
        }
        cerr << "\n\t\t\t\t\tError opening job file." << endl;
        return false;
    }
};

// Job Seeker Class
class JobSeeker : private JobApplication
{
private:
    // apply for any job -> applications.txt
    bool applyForJob()
    {
        // check if the job is already applied
        ifstream applicantfile;
        applicantfile.open("applications.txt");
        if (!applicantfile)
        {
            cerr << "\n\t\t\t\t\tJob Applications File Unavailable." << endl;
            return false;
        }
        else
        {
            string appliedJobs;
            while (getline(applicantfile, appliedJobs))
            {
                size_t pos = appliedJobs.find("|");
                string userId = appliedJobs.substr(0, pos);
                string jobId = appliedJobs.substr(pos + 1);
                if (jobId == data.getApplicationData().jobId && userId == data.getApplicationData().user_id)
                {
                    cout << "\n\t\t\t\t\tAlready Applied." << endl
                         << endl;
                    return false;
                }
            }
        }

        // new application of a job
        string applicationId = data.getApplicationData().user_id + "|" + data.getApplicationData().jobId;
        ofstream applicationFile("applications.txt", ios::app);
        if (applicationFile.is_open())
        {
            applicationFile << applicationId << endl;
            cout << "\n\t\t\t\t\tApplication submitted successfully!" << endl;
            return true;
        }
        cerr << "\n\t\t\t\t\tError opening application file for writing." << endl;
        return false;
    }

public:
    // Job seeker function call
    void jobSeeker_func_call(const Credentials cred)
    {
        int choice;
        char c;
        string jobId;
        size_t pos;
        data.getProfile().user_id = cred.getUsername();
        data.getProfile().name = cred.getName();
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
                 << "\t\t\t\t\t6. Remove Applied Jobs\n"
                 << "\t\t\t\t\t0. Exit\n"
                 << "\n\t\t\t\t\tEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            // 1. Add Resume
            case 1:
            {
                data.setJobsekerData();
                // addResume Function Initiated
                add("resumes.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 2. Show Resume
            case 2:
            {
                showProfile("resumes.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 3. Update Resume
            case 3:
            {
                char ch;
                do
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << "\t\t\t\t\t ::Update Job Seeker Profile::" << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << endl;
                    cout << "\n\t\t\t\t\t1. Update All\n"
                         << "\n\t\t\t\t\t2. Update Contact No.\n"
                         << "\n\t\t\t\t\t3. Update Email\n"
                         << "\n\t\t\t\t\t4. Update D.O.B.(DD/MM/YYYY)\n"
                         << "\n\t\t\t\t\t5. Update Qualification\n"
                         << "\n\t\t\t\t\t6. Update Skills\n"
                         << "\n\t\t\t\t\t7. Update experience (months)\n"
                         << "\n\t\t\t\t\t0. Exit\n"
                         << "\n\n\t\t\t\t\tEnter: ";
                    cin >> ch;
                    switch (choice)
                    {
                    // 1. Update All
                    case 1:
                    {
                        data.setJobsekerData();
                        // addResume Function Initiated
                        add("resumes.txt");
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 2. Update Contact
                    case 2:
                    {
                        data.setContact(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 3. Update Email
                    case 3:
                    {
                        data.setEmail(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 4. Update DOB
                    case 4:
                    {
                        data.setDOB(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 5. Update Qualification
                    case 5:
                    {
                        data.setQualification(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 6. Update Skills
                    case 6:
                    {
                        data.setSkills(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 7. Update experience
                    case 7:
                    {
                        data.setExprience(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
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
                } while (ch != 0);
                // Update resume function initiated
                updateProfile("resumes.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 4. Search & Apply for Jobs Available
            case 4:
            {
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
                            cin.ignore();
                            cout << "\n\t\t\t\t\tEnter the Job Id you want to apply for: ";
                            getline(cin, jobId);
                            pos = jobId.find("/");
                            jobId = jobId.substr(0, pos);
                            data.setApplcationData(jobId);
                            applyForJob();
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
                viewAppliedJobs();
                cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                getch();
                break;
            }

            // 6. Remove Applied Jobs
            case 6:
            {
                do
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << "\t\t\t\t\t    ::Applied Jobs::" << endl
                         << "\t\t\t\t\t-------------------------------" << endl
                         << endl
                         << endl;

                    if (viewAppliedJobs())
                    {
                        cin.ignore();
                        cout << "\n\t\t\t\t\tEnter The Job ID You Want To Delete: ";
                        getline(cin, jobId);
                        pos = jobId.find("/");
                        jobId = jobId.substr(0, pos);
                        removeJob(jobId, "applications.txt");
                        cout << "\n\n\t\t\t\t\tDo You Want More Applied Jobs Jobs? (Y/y or N/n)"
                             << "\n\n\t\t\t\t\tEnter: ";
                        cin >> c;
                    }
                    else
                    {
                        c = 'n';
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                    }
                } while (c == 'Y' || c == 'y');
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
};

// Employer Class
class Employer : private JobApplication
{
private:
    // add new job -> jobs.txt
    void addNewJob()
    {
        string job;
        ofstream jobFile("jobs.txt", ios::app);
        if (jobFile.is_open())
        {
            job = data.getJobData().jobid + "|" + data.getJobData().companyId + "|" + data.getJobData().jobTitle + "|" + data.getJobData().description + "|" + data.getJobData().requirements + "|" + data.getJobData().location + "|" + data.getJobData().salary + "|" + data.getJobData().companyName + "\n";
            jobFile.write(job.c_str(), job.size());
            cout << "\n\n\t\t\t\t\tJob saved successfully!" << endl;
        }
        else
        {
            cerr << "\n\n\t\t\t\t\tError opening job file for writing." << endl;
        }
    }

public:
    // Employer function call
    void employer_func_call(const Credentials cred)
    {
        int choice;
        char c;
        string jobId;
        data.getProfile().user_id = cred.getUsername();
        data.getProfile().name = cred.getName();
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
                 << "\t\t\t\t\t2. Update Employer Profile\n"
                 << "\t\t\t\t\t3. Show Employer Profile\n"
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
            {
                data.setEmployerData();

                // saveEmployerProfile Function Initiated
                add("employers.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 2. Update Employer Profile
            case 2:
            {
                char ch;
                do
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << "\t\t\t\t\t ::Update Job Seeker Profile::" << endl
                         << "\t\t\t\t\t---------------------------------------" << endl
                         << endl;
                    cout << "\n\t\t\t\t\t1. Update All\n"
                         << "\n\t\t\t\t\t2. Update Contact No.\n"
                         << "\n\t\t\t\t\t3. Update Email\n"
                         << "\n\t\t\t\t\t4. Update Location\n"
                         << "\n\t\t\t\t\t0. Exit\n"
                         << "\n\n\t\t\t\t\tEnter: ";
                    cin >> ch;
                    switch (choice)
                    {
                    // 1. Update All
                    case 1:
                    {
                        data.setJobsekerData();
                        // addResume Function Initiated
                        add("resumes.txt");
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 2. Update Contact
                    case 2:
                    {
                        data.setContact(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 3. Update Email
                    case 3:
                    {
                        data.setEmail(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                        break;
                    }

                    // 4. Update DOB
                    case 4:
                    {
                        data.setLocation(data.getProfile());
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
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
                } while (ch != 0);
                // Update resume function initiated
                updateProfile("resumes.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 2. Show Employer Profile
            case 3:
            {
                showProfile("employers.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 3. Add New Job
            case 4:
            {
                data.setJobData();
                addNewJob();
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 4. Show All Jobs Available
            case 5:
            {
                system("CLS");
                cout << endl
                     << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << "\t\t\t\t\t    ::Available Jobs::" << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << endl
                     << endl;
                showJobs(data.getProfile().user_id);

                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 6. Remove Jobs
            case 6:
            {
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

                    if (showJobs(data.getProfile().user_id))
                    {
                        cin.ignore();
                        cout << "\n\t\t\t\t\tEnter The Job ID You Want To Delete: ";
                        getline(cin, jobId);
                        size_t pos = jobId.find("/");
                        jobId = jobId.substr(0, pos);
                        removeJob(jobId, "jobs.txt");
                        cout << "\n\n\t\t\t\t\tDo You Want To Delete More Jobs? (Y/y or N/n)"
                             << "\n\n\t\t\t\t\tEnter: ";
                        cin >> c;
                    }
                    else
                    {
                        c = 'n';
                        cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                        getch();
                    }
                } while (c == 'Y' || c == 'y');
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
};

// login class
class Login
{
private:
    int choice;
    Credentials cred;

    // authenticate a user
    bool authenticateUser(const int &reg_type)
    {
        string filepath, user, name;

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
            user = cred.getUsername() + "|" + cred.getPassword();
            string line;
            while (getline(userFile, line))
            {
                // Check if the provided username exists and the password matches
                if (user == line)
                {
                    userFile.close();

                    // check for name
                    ifstream file;
                    file.open("names.txt");

                    // check if the exists or not
                    if (file)
                    {
                        while (getline(file, line))
                        {
                            size_t pos = line.find("|");
                            user = line.substr(0, pos);
                            name = line.substr(pos + 1);
                            if (user == cred.getUsername())
                            {
                                cred.setName(name);
                                file.close();
                                return true;
                            }
                        }
                        file.close();
                        cout << "\n\t\t\t\t\tInvalid username or password." << endl;
                        return false;
                    }
                }
            }
            userFile.close();
            cout << "\n\t\t\t\t\tInvalid username or password." << endl;
            return false;
        }

        cerr << "\n\t\t\t\t\tError opening file." << endl;
        return false;
    }

    // take input (username & password) from the user
    bool user_login_input(int reg_type)
    {

        string user_type;
        char c;

        cred.userInput();

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
        JobSeeker jobseeker;
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
            jobseeker.jobSeeker_func_call(cred);
            cout << "Continue" << endl;
            getch();
        }
    }

    // login as an employer
    void employer_login(int reg_type)
    {
        Employer employer;
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
            employer.employer_func_call(cred);
            cout << "Continue" << endl;
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
             << "\t\t\t\t\t2. Employer Login" << endl
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

        default:
            break;
        }
    }
};

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
