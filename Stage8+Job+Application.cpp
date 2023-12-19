#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

class JobApplication
{
protected:
    struct Profile
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

    struct Application
    {
        string jobId;
        string user_id;
    };

    // Add Profile of job seeker
    bool add(const Profile &Profile, const string filename)
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
                if (id == Profile.user_id)
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
            if (filename == "resumes.txt")
            {
                ProfileFile << Profile.user_id << "|" << Profile.name << "|" << Profile.contact << "|" << Profile.email << "|" << Profile.dob << "|" << Profile.qualification << "|" << Profile.skills << "|" << Profile.experience << endl;
            }
            else
            {
                ProfileFile << Profile.user_id << "|" << Profile.name << "|" << Profile.contact << "|" << Profile.email << "|" << Profile.location << endl;
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
    bool showProfile(const string user_id, const string filename)
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
                if (id == user_id)
                {
                    cout << "\n\n\t\t\t\t\tProfile for " << id << ": " << line.substr(pos + 1) << endl;
                    return true;
                }
            }
            cout << "\n\n\t\t\t\t\tProfile not found for " << user_id << "." << endl;
            return false;
        }
        cerr << "\n\n\t\t\t\t\tError opening Profile file for reading." << endl;
        return false;
    }

    // update the Profile of the job seeker
    void updateProfile(const string user_id, const Profile &newProfile, const string filename)
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
                if (id == user_id)
                {
                    if (filename == "resumes.txt")
                    {
                        lines.push_back(newProfile.user_id + "|" + newProfile.name + "|" + newProfile.contact + "|" + newProfile.email + "|" + newProfile.dob + "|" + newProfile.qualification + "|" + newProfile.skills + "|" + newProfile.experience);
                    }
                    else
                    {
                        lines.push_back(newProfile.user_id + "|" + newProfile.name + "|" + newProfile.contact + "|" + newProfile.email + "|" + newProfile.location);
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
                else if (userId.empty())
                {
                    pos = jobId.find("/");
                    string jid = jobId.substr(0, pos);
                    string compId = jobId.substr(pos + 1);
                    string newJobId = applicantjobId + "/" + compId;
                    if (jobId == newJobId)
                    {
                        cout << "\n\n\t\t\t\t\tJob ID: " << jobId << endl;
                        cout << "\n\t\t\t\t\tJob Details: " << jobDetails << endl;
                    }
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
    bool viewAppliedJobs(const string user_id, const string user_type)
    {
        ifstream applicationFile("applications.txt");
        if (applicationFile.is_open())
        {
            string line;
            while (getline(applicationFile, line))
            {
                size_t pos = line.find("|");
                string userId = line.substr(0, pos);
                if (userId == user_id && user_type == "js")
                {
                    string jobId = line.substr(pos + 1);
                    showJobs("", jobId);
                }
                else if (userId == user_id && user_type == "em")
                {
                    showJobs(user_id, "");
                }
                else
                {
                    cout << "\n\t\t\t\t\tYou have not applied for any job.";
                    return false;
                }
            }
            return true;
        }
        cerr << "\n\t\t\t\t\tError opening application file for reading." << endl;
        return false;
    }

    // Remove or take back any job application
    bool removeJob(const string userId, const string jobId, const string filename)
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
                    if (!(ID == userId && joId == jobId))
                    {
                        lines.push_back(line);
                    }
                }
                else
                {
                    string newjobId = jobId + "/" + userId;
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
    bool applyForJob(const Application &application)
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
                if (jobId == application.jobId && userId == application.user_id)
                {
                    cout << "\n\t\t\t\t\tAlready Applied." << endl
                         << endl;
                    return false;
                }
            }
        }

        // new application of a job
        string applicationId = application.user_id + "|" + application.jobId;
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
    void jobSeeker_func_call(const string username)
    {
        int choice;
        char c;
        string jobId;
        size_t pos;
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t--------------------------------------" << endl
             << "\t\t\t\t\t  ::Welcome to Job Seeker Section!::" << endl
             << "\t\t\t\t\t--------------------------------------" << endl
             << endl
             << endl;
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
                Profile resume;
                cin.ignore(); // Ignore newline character left in the buffer
                resume.user_id = username;
                cout << "\n\n\t\t\t\t\tEnter Your Name: ";
                getline(cin, resume.name);
                // Enter contact
                cout << "\t\t\t\t\tEnter Contact No: ";
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
                add(resume, "resumes.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 2. Show Resume
            case 2:
            {
                showProfile(username, "resumes.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 3. Update Resume
            case 3:
            {
                Profile newResume;
                cin.ignore(); // Ignore newline character left in the buffer
                newResume.user_id = username;
                cout << "\n\n\t\t\t\t\tEnter Your Name: ";
                getline(cin, newResume.name);
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
                updateProfile(username, newResume, "resumes.txt");
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
                            application.user_id = username;
                            cout << "\n\t\t\t\t\tEnter the Job Id you want to apply for: ";
                            getline(cin, jobId);
                            pos = jobId.find("/");
                            jobId = jobId.substr(0, pos);
                            application.jobId = jobId;
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
                viewAppliedJobs(username, "js");
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

                    if (viewAppliedJobs(username, "js"))
                    {
                        cin.ignore();
                        cout << "\n\t\t\t\t\tEnter The Job ID You Want To Delete: ";
                        getline(cin, jobId);
                        pos = jobId.find("/");
                        jobId = jobId.substr(0, pos);
                        removeJob(username, jobId, "applications.txt");
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

class Employer : private JobApplication
{
private:
    struct Job
    {
        string jobid;
        string companyId;
        string employerName;
        string jobTitle;
        string description;
        string requirements;
        string salary;
        string location;
    };

    // add new job -> jobs.txt
    void addNewJob(const Job &job)
    {
        ofstream jobFile("jobs.txt", ios::app);
        if (jobFile.is_open())
        {
            jobFile << job.jobid << "/" << job.companyId << "|" << job.jobTitle << "|" << job.description << "|" << job.requirements << "|" << job.location << "|" << job.salary << "|" << job.employerName << endl;
            cout << "\n\n\t\t\t\t\tJob saved successfully!" << endl;
        }
        else
        {
            cerr << "\n\n\t\t\t\t\tError opening job file for writing." << endl;
        }
    }

public:
    // Employer function call
    void employer_func_call(const string username)
    {
        int choice;
        char c;
        string jobId;
        system("CLS");
        cout << endl
             << endl
             << "\t\t\t\t\t--------------------------------------" << endl
             << "\t\t\t\t\t  ::Welcome to Employer Section!::" << endl
             << "\t\t\t\t\t--------------------------------------" << endl
             << endl
             << endl;

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
                 << "\t\t\t\t\t6. View Jobs Applied by Job Seekers\n"
                 << "\t\t\t\t\t7. Remove Jobs\n"
                 << "\t\t\t\t\t0. Exit\n"
                 << "\n\t\t\t\t\tEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            // 1. Add Employer Profile
            case 1:
            {
                Profile employerProfile;
                cin.ignore(); // Ignore newline character left in the buffer
                employerProfile.user_id = username;
                // Enter contact
                cout << "\n\n\t\t\t\t\tEnter Employer Name: ";
                getline(cin, employerProfile.name);
                // Enter contact
                cout << "\n\n\t\t\t\t\tEnter Contact No: ";
                getline(cin, employerProfile.contact);
                // Enter email
                cout << "\t\t\t\t\tEnter email: ";
                getline(cin, employerProfile.email);
                // Enter dob
                cout << "\t\t\t\t\tEnter Location: ";
                getline(cin, employerProfile.location);

                // saveEmployerProfile Function Initiated
                add(employerProfile, "employers.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 2. Update Employer Profile
            case 2:
            {
                Profile newProfile;
                cin.ignore(); // Ignore newline character left in the buffer
                newProfile.user_id = username;
                // Enter contact
                cout << "\n\n\t\t\t\t\tEnter Employer Name: ";
                getline(cin, newProfile.name);
                // Enter contact
                cout << "\n\n\t\t\t\t\tEnter Contact No: ";
                getline(cin, newProfile.contact);
                // Enter email
                cout << "\t\t\t\t\tEnter email: ";
                getline(cin, newProfile.email);
                // Enter dob
                cout << "\t\t\t\t\tEnter Location: ";
                getline(cin, newProfile.location);

                // Update Employer function initiated
                updateProfile(username, newProfile, "employers.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 2. Show Employer Profile
            case 3:
            {
                showProfile(username, "employers.txt");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 3. Add New Job
            case 4:
            {
                Job job;
                job.companyId = username;
                cin.ignore();
                cout << "\n\t\t\t\t\tEnter job ID: ";
                getline(cin, job.jobid);
                cout << "\n\t\t\t\t\tEnter job title: ";
                getline(cin, job.jobTitle);
                cout << "\n\t\t\t\t\tEnter Employer Name: ";
                getline(cin, job.employerName);
                cout << "\n\t\t\t\t\tEnter job description: ";
                getline(cin, job.description);
                cout << "\n\t\t\t\t\tEnter job requirements: ";
                getline(cin, job.requirements);
                cout << "\n\t\t\t\t\tEnter job salary: ";
                getline(cin, job.salary);
                cout << "\n\t\t\t\t\tEnter job location: ";
                getline(cin, job.location);
                addNewJob(job);
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
                showJobs(username);

                cout << "\n\n\t\t\t\t\tPress Enter Key To Continue ";
                getch();
                break;
            }

            // 5. View Applied Jobs By the users
            case 6:
            {
                system("CLS");
                cout << endl
                     << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << "\t\t\t\t\t     ::Applied Jobs::" << endl
                     << "\t\t\t\t\t-------------------------------" << endl
                     << endl
                     << endl;
                viewAppliedJobs(username, "em");
                cout << "\n\n\t\t\t\t\tPress Enter Key To Exit ";
                getch();
                break;
            }

            // 7. Remove Jobs
            case 7:
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

                    if (showJobs(username))
                    {
                        cin.ignore();
                        cout << "\n\t\t\t\t\tEnter The Job ID You Want To Delete: ";
                        getline(cin, jobId);
                        size_t pos = jobId.find("/");
                        jobId = jobId.substr(0, pos);
                        removeJob(username, jobId, "jobs.txt");
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

int main()
{
    JobSeeker jobseeker;
    Employer employer;
    string username;
    int choice;
    cout << "Enter Username: ";
    cin >> username;
    cout<<"\n1. Employer \n2. Job Seeker"<<endl;
    cin>>choice;
    if(choice==1){
        employer.employer_func_call(username);
    }
    else{
        jobseeker.jobSeeker_func_call(username);
    }
    return 0;
}