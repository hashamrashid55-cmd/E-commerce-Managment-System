#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
enum class utype {
    ADMIN,
    SELLER,
    BUYER
};

class User {
protected:
    int id;
    string username;
    string password;
    string email;
    utype userType;

public:
    User();
    User(int id, const string& uname, const string& pass, const string& mail, utype type);
    virtual ~User() = default;

    virtual void display() ;
    virtual bool login(const string& uname, const string& pass);

    int getid()  {
        return id;
    }
    string getUsername()  {
        return username;
    }
    utype gettype()  {
        return userType;
    }
    string getEmail()  {
        return email;
    }
    string getPassword()  {
        return password;
    }

    void setid(int i) {
        id = i;
    }
    void setname( string& uname);
    void setpass( string& pass);
    void setemail( string& mail);
    void settype(utype type) {
        userType = type;
    }
};

class Admin : public User {
public:
    Admin();
    Admin(int id, const string& uname, const string& pass, const string& mail);

    void display()  override;
    void manageUsers();
    void viewReports();
};

class Seller : public User {
private:
    string businessName;
    double revenue;

public:
    Seller();
    Seller(int id, const string& uname, const string& pass, const string& mail, const string& business);

    void display()  override;
    void addProduct();
    void viewMyOrders();

    string businessname()  {
        return businessName;
    }
    double getrevenue()  {
        return revenue;
    }

    void setBusinessName( string& business);
    void addSale(double amount) {
        revenue += amount;
    }
};

class Buyer : public User {
private:
    string address;
    double totalSpent;

public:
    Buyer();
    Buyer(int id, const string& uname, const string& pass, const string& mail, const string& addr);

    void display()  override;
    void viewCart();
    void checkout();

    string getAddress()  {
        return address;
    }
    double getTotalSpent()  {
        return totalSpent;
    }

    void setAddress( string& addr);

    void addOrder(double amount) {
        totalSpent += amount;
    }
};

#endif