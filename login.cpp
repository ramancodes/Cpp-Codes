#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

bool authenticateUser(const string& username, const string& password) {
       
    // Read user credentials from file
    ifstream userFile("users.txt");
    if (userFile.is_open()) {
        cerr << "Error opening user file." << endl;
        return false;
    }
    

    map<string, string> users;

    // Populate map with username-password pairs from the file
    string line;
    while (getline(userFile, line)) {
        istringstream iss(line);
        string storedUsername, storedPassword;
        if (iss >> storedUsername >> storedPassword) {
            users[storedUsername] = storedPassword;
        }
    }

    // Check if the provided username exists and the password matches
    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        cout << "Authentication successful!" << endl;
        return true;
    } else {
        cout << "Authentication failed. Invalid username or password." << endl;
        return false;
    }
}

int main() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    authenticateUser(username, password);

    return 0;
}