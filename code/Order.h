#pragma once
#ifndef ORDER_H
#define ORDER_H
#include <string>
using namespace std;
class orderitem {
public:
    int productID;
    string productName;
    double price;
    int quantity;
    int sellerID;
    orderitem();
    orderitem(int prodID, const string& name, double pr, int qty, int seller);

    double getTotalPrice()  {
        return price * quantity;
    }
};

enum ostatus {
    PENDING,
    PROCESSING,
    SHIPPED,
    DELIVERED
};

class Order {
private:
    int orderID;
    int buyerID;
    orderitem items[50];
    int itemCount;
    double totalAmount;
    string orderDate;
    string shippingAddress;
    ostatus status;

public:
    Order(int ordID, int buyer, const string& date, const string& address);

    void addItem( orderitem& item);
    void updateStatus(ostatus newStatus);
    int getBuyerID()  {
        return buyerID;
    }
    int getoid()  {
        return orderID;
    }
    double gettital()  {
        return totalAmount * 1.08;
    }
    string getStatusString() ;
    void orderdisplay() ;
};

#endif