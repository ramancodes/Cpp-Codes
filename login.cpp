#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

// Function to hash the password using SHA-256
string hashPassword(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.length());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}

bool registerUser(const string& username, const string& password) {
    // Read existing user credentials from file
    ifstream userFile("users.txt");
    if (!userFile.is_open()) {
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

    // Check if the username already exists
    if (users.find(username) != users.end()) {
        cout << "Registration failed. Username already exists." << endl;
        return false;
    }

    // Hash the password before storing it
    string hashedPassword = hashPassword(password);

    // Register the new user
    users[username] = hashedPassword;

    // Write the updated user credentials to the file
    ofstream outFile("users.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening user file for writing." << endl;
        return false;
    }

    for (const auto& entry : users) {
        outFile << entry.first << " " << entry.second << endl;
    }

    cout << "Registration successful!" << endl;
    return true;
}

bool authenticateUser(const string& username, const string& password) {
    // Read user credentials from file
    ifstream userFile("users.txt");
    if (!userFile.is_open()) {
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
    if (it != users.end() && it->second == hashPassword(password)) {
        cout << "Authentication successful!" << endl;
        return true;
    } else {
        cout << "Authentication failed. Invalid username or password." << endl;
        return false;
    }
}

int main() {
    int choice;
    string username, password;

    cout << "1. Register\n2. Authenticate\nEnter choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        registerUser(username, password);
    } else if (choice == 2) {
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        authenticateUser(username, password);
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
