#include "Cart.h"
#include <iostream>
template class Cart<Product>;
template<typename T>
Cart<T>::Cart(int buyer) : itemCount(0), buyerID(buyer), totalAmount(0) {
    for (int i = 0; i < 100; i++) items[i] = nullptr;
}

template<typename T>
Cart<T>::~Cart() {
    clearCart();
}

template<typename T>
int Cart<T>::findindex(int productID) const {
    for (int i = 0; i < itemCount; i++) {
        if (items[i] && items[i]->product->getProductID() == productID) {
            return i;
        }
    }
    return -1;
}

template<typename T>
Cart<T>& Cart<T>::operator+=(T* product) {
    addProduct(product);
    return *this;
}

template<typename T>
Cart<T>& Cart<T>::operator-=(int productID) {
    removeProduct(productID);
    return *this;
}

template<typename T>
void Cart<T>::addProduct(T* product, int quantity) {
    if (!product || quantity <= 0)
        throw cartexception("Invalid product or quantity");
    if (!product->isInStock())
        throw cartexception("Product out of stock");
    if (itemCount >= 100)
        throw cartexception("Cart is full");

    int existingIndex = findindex(product->getProductID());
    if (existingIndex != -1) {
        items[existingIndex]->quantity += quantity;
    }
    else {
        items[itemCount++] = new CartItem<T>(product, quantity);
    }
    calculateTotal();
}

template<typename T>
void Cart<T>::removeProduct(int productID) {
    int index = findindex(productID);
    if (index == -1) throw cartexception("Product not found");

    delete items[index];
    for (int i = index; i < itemCount - 1; i++) {
        items[i] = items[i + 1];
    }
    items[--itemCount] = nullptr;
    calculateTotal();
}

template<typename T>
void Cart<T>::clearCart() {
    for (int i = 0; i < itemCount; i++) {
        delete items[i];
        items[i] = nullptr;
    }
    itemCount = 0;
    totalAmount = 0.0;
}
