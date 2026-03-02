#include "Product.h"
#include <iostream>
#include <stdexcept>
#include<iomanip>
Product::Product() : productID(0), price(0.0), quantity(0), sellerID(0), approved(false) {}

Product::Product(int id, const std::string& pname, const std::string& cat,
    double pr, int qty, int seller)
    : productID(id), name(pname), category(cat), price(pr),
    quantity(qty), sellerID(seller), approved(false) {
}

void Product::details()  {
    std::cout << "ID: " << productID << " | " << name
        << " | Category: " << category << " | Price: $" << price
        << " | Qty: " << quantity;
}


bool Product::operator<(const Product& other)  {
    return price < other.price;
}

void Product::updateStock(int sold) {
    if (sold > quantity) {
        throw runtime_error("Not enough stock available");
    }
    quantity -= sold;
}

void Product::setName( string& pname) {
    if (pname.empty()) throw invalid_argument("Name cannot be empty");
    name = pname;
}

void Product::setcat( string& cat) {
    if (cat.empty()) throw invalid_argument("Category cannot be empty");
    category = cat;
}

// ElectronicsProduct Implementation
electronic::electronic() : Product(), warrantyPeriod(0) {}

electronic::electronic(int id, const std::string& pname, double pr, int qty,
    int seller, const std::string& br, int warranty)
    : Product(id, pname, "Electronics", pr, qty, seller),
    brand(br), warrantyPeriod(warranty) {
}

void electronic::details()  {
    Product::details();
    cout << " | Brand: " << brand << " | Warranty: " << warrantyPeriod << " months";
}


void electronic::setBrand(const std::string& br) {
    if (br.empty()) throw invalid_argument("Brand cannot be empty");
    brand = br;
}

// ClothingProduct Implementation
clothing::clothing() : Product() {}

clothing::clothing(int id, const std::string& pname, double pr, int qty,
    int seller, const std::string& sz, const std::string& col)
    : Product(id, pname, "Clothing", pr, qty, seller), size(sz), color(col) {
}

void clothing::details()  {
    Product::details();
    cout << " | Size: " << size << " | Color: " << color;
}



void clothing::setsize(const std::string& sz) {
    if (sz.empty()) throw invalid_argument("Size cannot be empty");
    size = sz;
}

void clothing::setColor(const std::string& col) {
    if (col.empty()) throw invalid_argument("Color cannot be empty");
    color = col;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << "ID: " << product.productID << " | " << product.name
        << " | Category: " << product.category
        << " | Price: $" << std::fixed << std::setprecision(2) << product.price
        << " | Qty: " << product.quantity
        << " | Seller ID: " << product.sellerID
        << " | Approved: " << (product.approved ? "Yes" : "No");
    return os;
}

std::ostream& operator<<(std::ostream& os, const electronic& product) {
    os << static_cast<const Product&>(product) // Output base Product parts
        << " | Type: Electronics"
        << " | Brand: " << product.brand
        << " | Warranty: " << product.warrantyPeriod << " months";
    return os;
}

std::ostream& operator<<(std::ostream& os, const clothing& product) {
    os << static_cast<const Product&>(product) // Output base Product parts
        << " | Type: Clothing"
        << " | Size: " << product.size
        << " | Color: " << product.color;
    return os;
}