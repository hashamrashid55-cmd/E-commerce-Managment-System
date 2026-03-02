#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H
#include "User.h"
#include "FileManager.h"  
#include <exception>
using namespace std;

class authexception : public exception {
private:
    const char* message;

public:
    authexception(const char* msg) : message(msg) {
    }

    const char* what() const {
        return message;
    }
};

class UserSession {
private:
    User* currentUser;
    bool loggedIn;
public:

    UserSession() : currentUser(nullptr), loggedIn(false) {
    }

    void startSession(User* user) {
        currentUser = user;
        loggedIn = true;
    }

    void endSession() {
        currentUser = nullptr;
        loggedIn = false;
    }

    bool logged()  {
        return loggedIn;
    }

    User* getcurrent()  {
        return currentUser;
    }

    bool isAdmin()  {
        // if a user is logged in ait will check the type of user by calling the gettypr function
        return loggedIn && currentUser->gettype() == utype::ADMIN;
    }

    bool isSeller()  {
        return loggedIn && currentUser->gettype() == utype::SELLER;
    }

    bool isBuyer()  {
        return loggedIn && currentUser->gettype() == utype::BUYER;
    }
};

class authsystem {
private:
    static const int maxusers = 1000;
    User* users[maxusers];
    int count;
    filemanager fileManager;
    UserSession currentSession;

    // definations are in.cpp
    bool checkmail( string& email);

      bool checkpass( string& password);

    bool checkavail( string& username);

    User* finduser( string& username);
    User* createUser( string& username,  string& password,  string& email, utype userType);

public:
    authsystem();
    ~authsystem();

    bool login( string& username,  string& password);
    void logout() {
        currentSession.endSession();
    }
    bool registerUser( string& username,  string& password,  string& email, utype userType);
    bool userlogin()  {
        return currentSession.logged();
    }

    utype currentype() ;


    User* currentuser()  {
        return currentSession.getcurrent();
    }

    bool saveallusers() {
        return fileManager.saveUsers(users, count);
    }

    bool loadAllUsers() {
        count = fileManager.getuserss(users, maxusers);
        return count > 0;
    }
};

#endif
