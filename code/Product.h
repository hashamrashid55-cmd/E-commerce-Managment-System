#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;
class Product {
protected:
    int productID;
    string name;
    string category;
    double price;
    int quantity;
    int sellerID;
    bool approved;

public:
    Product();
    Product(int id, const string& pname, const string& cat,
        double pr, int qty, int seller);
    virtual ~Product() = default;

    virtual void details() ;

    int getProductID()  {
        return productID;
    }
    string getName()  {
        return name;
    }
    string getcategory()  {
        return category;
    }
    double getPrice()  {
        return price;
    }
    int getQuantity()  {
        return quantity;
    }
    int getsid()  {
        return sellerID;
    }
    bool checkapprov()  {
        return approved;
    }

    void setProdid(int id) {
        productID = id;
    }
    void setName( string& pname);
    void setcat( string& cat);

    void setPrice(double pr) {
        price = pr;
    }
    void setQuantity(int qty) {
        quantity = qty;
    }
    void setSellerid(int seller) {
        sellerID = seller;
    }
    void changeapprov(bool status) {
        approved = status;
    }

    bool operator<(const Product& other) ;

    void updateStock(int sold);
    bool isInStock() const {
        return quantity > 0;
    }

    friend std::ostream& operator<<(ostream& os, const Product& product);
};

class electronic : public Product {
private:
    string brand;
    int warrantyPeriod;

public:
    electronic();
    electronic(int id, const string& pname, double pr, int qty, int seller, const string& br, int warranty);

    void details()  override;

    string getBrand()  {
        return brand;
    }
    int getwarranty()  {
        return warrantyPeriod;
    }

    void setBrand(const string& br);
    void setwarranty(int warranty) {
        warrantyPeriod = warranty;
    }

    friend ostream& operator<<(ostream& os, const electronic& product);
};

class clothing : public Product {
private:
    string size;
    string color;

public:
    clothing();
    clothing(int id, const string& pname, double pr, int qty, int seller, const string& sz, const string& col);

    void details()  override;

    string getSize()  {
        return size;
    }
    string getColor()  {
        return color;
    }

    void setsize(const string& sz);
    void setColor(const string& col);

    friend ostream& operator<<(ostream& os, const clothing& product);
};

#endif