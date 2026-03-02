#include "AuthSystem.h"
#include <fstream>
#include <cstring>

authsystem::authsystem() : count(0) {
    for (int i = 0; i < maxusers; i++) {
        users[i] = nullptr;
    }
    loadAllUsers();
}

authsystem::~authsystem() {
    saveallusers();
    for (int i = 0; i < count; i++) {
        delete users[i];
    }
}

// checl for the email validationn
// the email should have the @ 
// also the .

bool authsystem::checkmail(string& email) {
    bool found1 = false;
    bool found2 = false;

    int at_pos = -1;
    for (int i = 0; i < email.length(); ++i) {
        if (email[i] == '@' && !found1) {
            at_pos = i;
            found1 = true;
        }
        if (found1 && email[i] == '.' && i > at_pos) {
            found2 = true;
            break;
        }
    }

    return found1 && found2;
}

// pass great than 8
bool authsystem::checkpass( string& password) {
    return password.length() >= 8;
}

bool authsystem::checkavail( string& username) {
    for (int i = 0; i < count; i++) {
        if (users[i]->getUsername() == username) {
            return false;
        }
    }
    return true;
}

User* authsystem::finduser( std::string& username) {
    for (int i = 0; i < count; i++) {
        if (users[i]->getUsername() == username) {
            return users[i];
        }
    }
    return nullptr;
}

User* authsystem::createUser( string& username,  string& password,   string& email, utype userType) {

    if (count >= maxusers) {
        throw authexception("khatam ho gai space");
    }

    User* newUser = nullptr;
    switch (userType) {
    case utype::ADMIN:
        newUser = new Admin(count + 1, username, password, email);
        break;
    case utype::SELLER:
        newUser = new Seller(count + 1, username, password, email, "");
        break;
    case utype::BUYER:
        newUser = new Buyer(count + 1, username, password, email, "");
        break;
    }

    users[count++] = newUser;
    return newUser;
}

bool authsystem::login( string& username,  string& password) {

    User* user = finduser(username);

    if (user && user->login(username, password)) {
        // the if statement will be true if the credential are correct 
        // and it will let you login into the program
        // otherwise exception will be thrown
        currentSession.startSession(user);
        return true;
    }
    throw authexception("invalid username or password");
}
// function to check for everything 
bool authsystem::registerUser( string& username,  string& password,
     string& email, utype userType) {
    if (!checkavail(username)) {
        throw authexception("user already exists");
    }
    if (!checkmail(email)) {
        throw authexception("Invalid email format");
    }
    if (!checkpass(password)) {
        throw authexception(" at least 8 characters");
    }

    createUser(username, password, email, userType);
    return true;
}

utype authsystem::currentype()  {
    if (currentSession.logged()) {
        return currentSession.getcurrent()->gettype();
    }
    throw authexception("No user");
}