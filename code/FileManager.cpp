#include "FileManager.h"
#include <fstream>
#include <sstream>

const string filemanager::userfile = "users.txt";
const string filemanager::productfile = "products.txt";
const string filemanager::orderfile = "orders.txt";

filemanager::filemanager() {}

string filemanager::suser( User* user)  {   ostringstream oss;
    oss << user->getid() << ","
        << user->getUsername() << ","
        << user->getPassword() << ","
        << user->getEmail() << ","
        << static_cast<int>(user->gettype());
    return oss.str();
}

string filemanager::serialprod( Product* product)  {
    ostringstream oss;
    oss << product->getProductID() << ","
        << product->getName() << ","
        << product->getcategory() << ","
        << product->getPrice() << ","
        << product->getQuantity() << ","
        << product->getsid() << ","
        << product->checkapprov();
    return oss.str();
}

string filemanager::serialorder( Order* order)  {
    ostringstream oss;
    oss << order->getoid() << ","
        << "data";
    return oss.str();
}

User* filemanager::removeuser( string& data)  {
    istringstream iss(data);
    string token;
    string parts[5];
    int i = 0;

    while (getline(iss, token, ',')) {
        if (i < 5) parts[i++] = token;
    }

    int id = stoi(parts[0]);
    utype type = static_cast<utype>(stoi(parts[4]));

    User* user = nullptr;
    switch (type) {
    case utype::ADMIN:
        user = new Admin(id, parts[1], parts[2], parts[3]);
        break;
    case utype::SELLER:
        user = new Seller(id, parts[1], parts[2], parts[3], "");
        break;
    case utype::BUYER:
        user = new Buyer(id, parts[1], parts[2], parts[3], "");
        break;
    }
    return user;
}

bool filemanager::saveUsers(User* users[], int count) {
    ofstream outFile(userfile);
    if (!outFile) return false;

    for (int i = 0; i < count; i++) {
        outFile << suser(users[i]) << "\n";
    }
    return true;
}

int filemanager::getuserss(User* users[], int maxCount) {
    ifstream inFile(userfile);
    if (!inFile) return 0;

    string line;
    int count = 0;
    while (getline(inFile, line) && count < maxCount) {
        users[count++];
    }
    return count;
}

bool filemanager::saveProducts(Product* products[], int count) {
    ofstream outFile(productfile);
    if (!outFile) return false;

    for (int i = 0; i < count; i++) {
        outFile << serialprod(products[i]) << "\n";
    }
    return true;
}

int filemanager::loadProducts(Product* products[], int maxCount) {
    ifstream inFile(productfile);
    if (!inFile) return 0;

    string line;
    int count = 0;
    while (getline(inFile, line) && count < maxCount) {
        products[count++];
    }
    return count;
}

bool filemanager::saveOrders(Order* orders[], int count) {
    ofstream outFile(orderfile);
    if (!outFile) return false;

    for (int i = 0; i < count; i++) {
        outFile << serialorder(orders[i]) << "\n";
    }
    return true;
}

int filemanager::loadOrders(Order* orders[], int maxCount) {
    ifstream inFile(orderfile);
    if (!inFile) return 0;

    string line;
    int count = 0;
    while (getline(inFile, line) && count < maxCount) {
        orders[count++];
    }
    return count;
}
