#include <iostream>
#include <string>
#include <cstring>
#include "User.h"
#include "Product.h"
#include "Cart.h"
#include "Order.h"
#include "AuthSystem.h"
#include "FileManager.h"

using namespace std;

const int maxuser = 15;
const int maxprod = 56;
const int maxorder = 7;
User* users[maxuser];
Product* products[maxprod];
Order* orders[maxorder];
int userCount = 0;
int pcount = 0;
int orderCount = 0;

void mainmenu();

void adminMenu(AuthSystem& auth, FileManager& fileManager);
void sellerMenu(AuthSystem& auth, FileManager& fileManager, int sellerId);
void buyerMenu(AuthSystem& auth, FileManager& fileManager, int buyerId);

void start(FileManager& fileManager);

void allprod();

void displayorders(int userId);


void displaysellerprod(int sellerId);

int main() {

    AuthSystem as;
    FileManager fm;

    start(fm);

    int choice;
    string username, password;

    do {
        mainmenu();
        cout << " your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: { 
            cout << " username: ";
            getline(cin, username);
            cout << " password: ";
            getline(cin, password);

            try {
                if (as.login(username, password)) {
                    User* currentUser = as.currentuser();
                    cout << "\n Login successful Welcome " << currentUser->getUsername();

                    if (as.currentype() == utype::ADMIN) {
                        adminMenu(as, fm);
                    }
                    else if (as.currentype() == utype::SELLER) {
                        sellerMenu(as, fm, currentUser->getid());
                    }
                    else {
                        buyerMenu(as, fm, currentUser->getid());
                    }
                }
            }
            catch (const AuthException& e) {
                cerr << "Login failed: " << e.what() << endl;
            }
            break;
        }
        case 2: { 
            int userType;
            string email, businessName, address;

            cout << "1. Buyer\n2. Seller\n";
            cout << "Choice: ";
            cin >> userType;
            cin.ignore();

            cout << " username: ";
            getline(cin, username);
            cout << " password: ";
            getline(cin, password);
            cout << " email: ";
            getline(cin, email);

            try {
                if (userType == 1) { // Buyer
                    cout << "input shipping address: ";
                    getline(cin, address);
                    if (as.registerUser(username, password, email, utype::BUYER)) {
                        users[userCount++] = new Buyer(userCount, username, password, email, address);
                        cout << " successful\n";
                    }
                }
                else if (userType == 2) { // Seller
                    cout << " business name: ";
                    getline(cin, businessName);
                    if (as.registerUser(username, password, email, utype::SELLER)) {
                        users[userCount++] = new Seller(userCount, username, password, email, businessName);
                        cout << " successful!\n";
                    }
                }
               
            }
            catch (const AuthException& e) {
                cerr << "Registration failed: " << e.what() << endl;
            }
            break;
        }
        case 3: 
            fm.saveUsers(users, userCount);
            fm.saveProducts(products, pcount);
            fm.saveOrders(orders, orderCount);
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 3);

    // freeing dynamically allocated memory
    for (int i = 0; i < userCount; i++) delete users[i];
    for (int i = 0; i < pcount; i++) delete products[i];
    for (int i = 0; i < orderCount; i++) delete orders[i];

    return 0;
}

void start(FileManager& fm) {

    userCount = fm.getuserss(users, maxuser);
   
    // creating a default admin qnad there will be only one 
    users[userCount++] = new Admin(1, "admin", "admin123", "admin@fast.com");
    

    pcount = fm.loadProducts(products, maxprod);
    if (pcount == 0) {
        // Create sample products if none exist
        products[pcount++] = new electronic(1, "Laptop", 999.99, 10, 1, "Dell", 12);
        products[pcount++] = new clothing(2, "T-Shirt", 15.36, 50, 1, "M", "Blue");
    }

    // Load orders
    orderCount = fm.loadOrders(orders, maxorder);
}

void mainmenu() {
    cout << "\n===== E-Commerce Management System =====\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
    cout << "======================================\n";
}

void adminMenu(AuthSystem& auth, FileManager& fileManager) {
    int choice;
    do {
        cout << "\n===== ADMIN MENU =====\n";
        cout << "1. View All Users\n";
        cout << "2. Manage Users\n";
        cout << "3. View Reports\n";
        cout << "4. Approve Products\n";
        cout << "5. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "\n=== Users ===\n";
            for (int i = 0; i < userCount; i++) {
                users[i]->display();
                cout << endl;
            }
            break;
        case 2: {
            cout << "\n=== Manage Users ===\n";
            string username;
            cout << "Enter username to manage: ";
            getline(cin, username);

            bool found = false;
            for (int i = 0; i < userCount; i++) {
                if (users[i]->getUsername() == username) {
                    found = true;
                    break;
                }
            }
            if (!found) cout << " not found.\n";
            break;
        }
        case 3:
            cout << "\n=== Report ===\n";
            cout << "Total Products: " << pcount;
            cout << "Total Users: " << userCount << endl;
            cout << "Total Orders: " << orderCount << endl;
            break;
        case 4:
            cout << "\n=== Product Approval ===\n";
            for (int i = 0; i < pcount; i++) {
                if (!products[i]->isApproved()) {
                    products[i]->details();

                    cout << "\nApprove this product? (y/n): ";
                    char approve;
                    cin >> approve;
                    if (approve == 'y' || approve == 'Y') {
                        products[i]->setApproved(true);
                        cout << "Product approved!\n";
                    }
                }
            }
            break;
        case 5:
            auth.logout();
            cout << "Logged out.\n";
            break;
        default:
            cout << "Invalid.\n";
        }
    } while (choice != 5);
}

void sellerMenu(AuthSystem& auth, FileManager& fileManager, int sellerId) {
    int choice;
    do {
        cout << "\n===== seller menue =====\n";
        cout << "1. Add Product\n";
        cout << "2. View My Products\n";
        cout << "3. View Orders\n";
        cout << "4. View Sales Report\n";
        cout << "5. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            if (pcount >= maxprod) {
                cout << "error\n";
                break;
            }

            string name, category, brand, size, color;
            double price;
            int quantity, warranty=0;
            int typeChoice;

            cout << "\n=== Add New Product ===\n";
            cout << "Product name: ";
            getline(cin, name);
            cout << "Price: ";
            cin >> price;
            cout << "Quantity: ";
            cin >> quantity;
            cin.ignore();

            cout << "Product type:\n1. electronic\n2. clothing \nChoice: ";
            cin >> typeChoice;
            cin.ignore();

            if (typeChoice == 1) {
                cout << "Brand: ";
                getline(cin, brand);
               
                products[pcount++] = new electronic(
                    pcount + 1, name, price, quantity, sellerId, brand, warranty
                );
            }
            else if (typeChoice == 2) {
                cout << "Size: ";
                getline(cin, size);
                cout << "Color: ";
                getline(cin, color);
                products[pcount++] = new clothing(
                    pcount + 1, name, price, quantity, sellerId, size, color
                );
            }
            else {
                cout << "invalid\n";
                break;
            }

            cout << " added \n";
            break;
        }
        case 2:
            displaysellerprod(sellerId);
            break;
        case 3:
            cout << "\n=== Orders  ===\n";
            for (int i = 0; i < orderCount; i++) {

                orders[i]->displayOrder();
            }
            break;
        case 4: {
            double totalSales = 0;
            int itemsSold = 0;


            for (int i = 0; i < pcount; i++) {
                if (products[i]->getsid() == sellerId) {
                    totalSales += (products[i]->getPrice() * (products[i]->getQuantity() - 10)); // Assuming 10 is initial quantity
                    itemsSold += (products[i]->getQuantity() - 10);
                }
            }

            cout << "\n===  Report ===\n";
            cout << " Items Sold: " << itemsSold << endl;
            cout << " Revenue: rs" << totalSales << endl;
            break;
        }
        case 5:
            auth.logout();
            cout << "Logged out .\n";
            break;
        default:
            cout << "Invalid .\n";
        }
    } while (choice != 5);
}

void buyerMenu(AuthSystem& auth, FileManager& fileManager, int buyerId) {
    int choice;
    Cart<Product> cart(buyerId);

    do {
        cout << "\n===== BUYER MENU =====\n";
        cout << "1. Browse Products\n";
        cout << "2. Search Products\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. View Orders\n";
        cout << "6. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            allprod();

            cout << "\n product ID to add to cart (0 to cancel): ";
            int productId, quantity;
            cin >> productId;
            if (productId == 0) break;

            cout << "Enter quantity: ";
            cin >> quantity;
            cin.ignore();

            bool found = false;
            for (int i = 0; i < pcount; i++) {
                if (products[i]->getProductID() == productId) {
                    found = true;
                    try {
                        cart.addProduct(products[i], quantity);
                        cout << "Added to cart: " << products[i]->getName() << endl;
                    }
                    catch (const cartexception& e) {
                        cout << "Error: " << e.what() << endl;
                    }
                    break;
                }
            }
            if (!found) cout << "Product not found.\n";
            break;
        }
        case 2: {
            string searchTerm;
            cout << "Enter search term: ";
            getline(cin, searchTerm);

            cout << "\n=== Search Results ===\n";
            bool found = false;
            for (int i = 0; i < pcount; i++) {
                if (products[i]->getName().find(searchTerm) != string::npos) {
                    products[i]->details();
                    cout << endl;
                    found = true;
                }
            }
            if (!found) cout << "no product founf " << searchTerm << "'\n";
            break;
        }
        case 3:
            cout << cart;
            break;
        case 4: {
            if (cart.isEmpty()) {
                cout << " empty\n";
                break;
            }

            // Create new order
            if (orderCount >= maxorder) {
                cout << "max reached.\n";
                break;
            }

            string address;
            for (int i = 0; i < userCount; i++) {
                if (users[i]->getid() == buyerId && users[i]->gettype() == utype::BUYER) {
                    Buyer* buyer = (Buyer*)users[i];
                    address = buyer->getAddress();
                    break;
                }
            }

            Order* newOrder = new Order(orderCount + 1, buyerId, "2023-11-15", address);

            // Add cart items to order
            for (int i = 0; i < cart.getcount(); i++) {
                Product* p = cart.getItems()[i]->product;
                orderitem item(p->getProductID(), p->getName(), p->getPrice(), 1, p->getsid());
                newOrder->addItem(item);
            }

            orders[orderCount++] = newOrder;
            cout << "Order placed Order ID: " << newOrder->getoid() << endl;
            cart.clearCart();
            break;
        }
        case 5:
            displayorders(buyerId);
            break;
        case 6:
            auth.logout();
            cout << "Logged out .\n";
            break;
        default:
            cout << "Invalid \n";
        }
    } while (choice != 6);
}

void allprod() {
    cout << "\n=== Products ===\n";
    for (int i = 0; i < pcount; i++) {
        if (products[i]->isApproved()) {
            cout << "ID: " << products[i]->getProductID() << " - ";
            products[i]->details();
            cout << endl;
        }
    }
}

void displayorders(int userId) {
    cout << "\n=== Orders ===\n";
    bool found = false;
    for (int i = 0; i < orderCount; i++) {
        if (orders[i]->getBuyerID() == userId) {
            orders[i]->displayOrder();
            cout << endl;
            found = true;
        }
    }
    if (!found) cout << "No  found\n";
}

void displaysellerprod(int sellerId) {
    cout << "\n=== Products ===\n";
    bool found = false;
    for (int i = 0; i < pcount; i++) {
        if (products[i]->getsid() == sellerId) {
            products[i]->details();
            cout << " | Approved: " << (products[i]->isApproved() ? "Yes" : "No") << endl;
            found = true;
        }
    }
    if (!found) cout << "No found.\n";
}