#pragma once
#ifndef CART_H
#define CART_H
#include "Product.h"
#include <iostream>
using namespace std;
class cartexception
{
private:
    string message;
public:
    cartexception(const string& msg) : message(msg) {
    
    }
    string what() const {
        return message;
    }
};

template<typename T>
class CartItem {
public:
    T* product;
    int quantity;
    CartItem(T* prod, int qty) : product(prod), quantity(qty) {
    
    }
    double getTotalPrice() const {
        return product->getPrice() * quantity;
    }
};

template<typename T>
class Cart {
private:
    CartItem<T>* items[100];
    int itemCount;
    int buyerID;
    double totalAmount;
    void calculateTotal();
    int findindex(int productID) const;

public:
    Cart();
    Cart(int buyer);
    ~Cart();

    CartItem< T > ** getItems() {
        return items;
    }
    Cart& operator+=(T* product);
    Cart& operator-=(int productID);

    void addProduct(T* product, int quantity = 1);
    void removeProduct(int productID);
    void clearCart();
    bool empty() const {
        return itemCount == 0;
    }
    int getcount() const {
        return itemCount;
    }
    double totalamount() const {
        return totalAmount;
    }
    double finaltotal4() const;

    template<typename U>
    friend ostream& operator<<(ostream& os, const Cart<U>& cart);

};
template<typename T>
ostream& operator<<(ostream& os, const Cart<T>& cart) {
    os << "Cart Contents " << cart.itemCount << " items:\n";
    for (int i = 0; i < cart.itemCount; i++)
    {
        if (cart.items[i])
        {
            os << "  ";
            os << *cart.items[i]->product;
            os << "  Quantity: " << cart.items[i]->quantity
                << "  Total: rs" << cart.items[i]->getTotalPrice() << "\n";
        }
    }
    os << "cart total: rs" << cart.totalAmount << "\n";
    return os;
}
template<typename T>
Cart<T>::Cart() : itemCount(0), buyerID(0), totalAmount(0.0) {
    for (int i = 0; i < 100; i++) items[i] = nullptr;
}

template<typename T>
void Cart<T>::calculateTotal() {
    totalAmount = 0.0;
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i] != nullptr)
        {
            totalAmount += items[i]->getTotalPrice();
        }
    }
}

template<typename T>
double Cart<T>::finaltotal4() const {
    return totalAmount ;
}

#endif