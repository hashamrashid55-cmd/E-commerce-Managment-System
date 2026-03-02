#include "Order.h"
#include <iostream>
#include <ctime>
#include<string>
using namespace std;
orderitem::orderitem(int prodID, const string& name, double pr, int qty, int seller)
    : productID(prodID), productName(name), price(pr), quantity(qty), sellerID(seller) {
}

orderitem::orderitem()
    : productID(0), productName(""), price(0.0), quantity(0), sellerID(0) {
}
Order::Order(int ordID, int buyer, const string& date, const string& address)
    : orderID(ordID), buyerID(buyer), itemCount(0), totalAmount(0.0),
    orderDate(date), shippingAddress(address), status(PENDING) {
}

void Order::addItem( orderitem& item) {
    if (itemCount >= 50) {
        throw "or order nahi an :(";
    }
    items[itemCount++] = item;
    totalAmount += item.getTotalPrice();
}

void Order::updateStatus(ostatus newStatus) {
    status = newStatus;
}

string Order::getStatusString()  {
    switch (status) {
    case PENDING:
        return "Pending";
    case PROCESSING:
        return "Processing";
    case SHIPPED:
        return "Shipped";
    case DELIVERED:
        return "Delivered";
    default:
        return "Unknown";
    }
}

void Order::orderdisplay()  {
    cout << "Order " << orderID << "\n";
    cout << "Date " << orderDate << "\n";
    cout << "Status " << getStatusString() << "\n";
    cout << "Items\n";

    for (int i = 0; i < itemCount; i++) {
        cout << "  " << items[i].productName << " x" << items[i].quantity
            << " rs" << items[i].price << "\n";
    }

    cout << "Total: rs" << totalAmount << "\n";
}