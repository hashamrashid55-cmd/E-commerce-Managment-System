#include "User.h"
#include <iostream>
#include <stdexcept>
#include<string>
using namespace std;
User::User() : id(0), userType(utype::BUYER) {
}

User::User(int id, const string& uname, const string& pass,
    const string& mail, utype type)
    : id(id), username(uname), password(pass), email(mail), userType(type) {
}

void User::display()  {
    cout << "ID: " << id << " | Username: " << username
        << " | Email: " << email << " | Type: ";

    switch (userType) {
    case utype::ADMIN:
        cout << "Admin";
        break;
    case utype::SELLER:
        cout << "Seller";
        break;
    case utype::BUYER:
        cout << "Buyer";
        break;
    }
}

bool User::login(const string& uname, const std::string& pass) {
    return (username == uname && password == pass);
}

void User::setname( string& uname) {
    if (uname.empty()) throw invalid_argument("give user");
    username = uname;
}

void User::setpass( string& pass) {
    if (pass.empty()) throw invalid_argument("give pass");
    password = pass;
}

void User::setemail( string& mail) {
    if (mail.empty()) throw invalid_argument("give email");
    email = mail;
}

Admin::Admin() : User() {
    userType = utype::ADMIN;
}

Admin::Admin(int id, const string& uname, const string& pass, const string& mail)
    : User(id, uname, pass, mail, utype::ADMIN) {
}

void Admin::display()  {
    cout << "admin ";
    User::display();
}

void Admin::manageUsers() {
    cout << "Admin managing \n";
}

void Admin::viewReports() {
    cout << "Admin reports\n";
}

Seller::Seller() : User(), revenue(0.0) {
    userType = utype::SELLER;
}

Seller::Seller(int id, const string& uname, const string& pass,
    const string& mail, const string& business)
    : User(id, uname, pass, mail, utype::SELLER),
    businessName(business), revenue(0.0) {
}

void Seller::display()  {
    cout << "seller ";
    User::display();
    cout << " // Business: " << businessName
        << " // Revenue: rs" << revenue;
}

void Seller::addProduct() {
    cout << "Seller adding new product...\n";
}

void Seller::viewMyOrders() {
    cout << "Seller viewing orders...\n";
}

void Seller::setBusinessName( string& business) {
    if (business.empty()) throw invalid_argument(" cannot be empty");
    businessName = business;
}

Buyer::Buyer() : User(), totalSpent(0.0) {
    userType = utype::BUYER;
}

Buyer::Buyer(int id, const string& uname, const string& pass,
    const string& mail, const string& addr)
    : User(id, uname, pass, mail, utype::BUYER),
    address(addr), totalSpent(0.0) {
}

void Buyer::display()  {
    cout << "buyer";
    User::display();
    cout << " | Address: " << address
        << " | Total Spent: rs" << totalSpent;
}

void Buyer::viewCart() {
    cout << "Buyer  cart";
}

void Buyer::checkout() {
    cout << "Buyer checkout";
}

void Buyer::setAddress( string& addr) {
    if (addr.empty()) throw invalid_argument("cannot beempty");
    address = addr;
}