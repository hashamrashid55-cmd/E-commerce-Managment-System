#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "User.h"
#include "Product.h"
#include "Order.h"
#include <string>
using namespace std;

class FileException : public exception {
private:
    const char* message;

public:
    FileException(const char* msg) : message(msg) {}

    const char* what() const {
        return message; 
    }
};


class filemanager {
private:
    static const string userfile;
    static const string productfile;
    static const string orderfile;

    static const int maxrecords= 804;



    string suser( User* user) ;
    string serialprod( Product* product) ;
    string serialorder( Order* order) ;
    User* removeuser( string& data) ;

public:
    filemanager();

    bool saveUsers(User* users[], int count);
    int getuserss(User* users[], int maxCount);

    bool saveProducts(Product* products[], int count);
    int loadProducts(Product* products[], int maxCount);

    bool saveOrders(Order* orders[], int count);
    int loadOrders(Order* orders[], int maxCount);



};

#endif