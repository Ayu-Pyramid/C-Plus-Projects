#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int stockQuantity;
    int reorderThreshold;
    int unitsSold;

public:
    Product(int i, string n, double p, int quantity, int reorder) :
        id(i), name(n), price(p), stockQuantity(quantity), reorderThreshold(reorder), unitsSold(0) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    int getReorderThreshold() const { return reorderThreshold; }
    int getUnitsSold() const { return unitsSold; }

    bool hasEnoughStock(int quantity) const {
        return stockQuantity >= quantity;
    }

    void reduceStock(int quantity) {
        stockQuantity -= quantity;
        unitsSold += quantity;
    }
    void restock(int quantity) {
        stockQuantity += quantity;
    }
};

class InventorySystem {
private:
    vector<Product> catalog;
    double totalRevenue;

public:
    InventorySystem() : totalRevenue(0.0) {}

    void addProduct(Product p) {
        catalog.push_back(p);
        cout << "[System] Added: " << p.getName() << " to inventory." << endl;
    }

    void processSale(int productId, int qty) {
        for (auto& p : catalog) {
            if (p.getId() == productId) {
                if (p.hasEnoughStock(qty)) {
                    p.reduceStock(qty);
                    double saleAmount = p.getPrice() * qty;
                    totalRevenue += saleAmount;

                    cout << fixed << setprecision(2);
                    cout << "[SALE] Sold " << qty << "x " << p.getName()
                         << " | Subtotal: $" << saleAmount << endl;
                    return;
                } else {
                    cout << "[ERROR] Insufficient stock for " << p.getName() << endl;
                    return;
                }
            }
        }
        cout << "[ERROR] Product ID " << productId << " not found." << endl;
    }

    void showTopSellers() {
        vector<Product> sortedCatalog = catalog;
        sort(sortedCatalog.begin(), sortedCatalog.end(), [](const Product& a, const Product& b) {
            return a.getUnitsSold() > b.getUnitsSold();
        });

        cout << "\n--- TOP SELLING PRODUCTS ---" << endl;
        for (const auto& p : sortedCatalog) {
            if (p.getUnitsSold() > 0) {
                cout << p.getName() << " | Units Sold: " << p.getUnitsSold() << endl;
            }
        }
    }

    void showLowStockReport() {
        cout << "\n--- CRITICAL LOW STOCK REPORT ---" << endl;
        bool foundAny = false;
        for (const auto& p : catalog) {
            if (p.getStockQuantity() <= p.getReorderThreshold()) {
                cout << "ALERT: " << p.getName() << " (ID: " << p.getId() << ")"
                     << " | Stock: " << p.getStockQuantity()
                     << " | Threshold: " << p.getReorderThreshold() << endl;
                foundAny = true;
            }
        }
        if (!foundAny) cout << "All stock levels are healthy." << endl;
        cout << "---------------------------------" << endl;
    }

    void showInventory() {
        cout << "\n" << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Stock" << "Sold" << endl;
        cout << string(45, '-') << endl;
        for (const auto& p : catalog) {
            cout << left << setw(5) << p.getId()
                 << setw(15) << p.getName()
                 << "$" << setw(9) << fixed << setprecision(2) << p.getPrice()
                 << setw(10) << p.getStockQuantity()
                 << p.getUnitsSold() << endl;
        }
        cout << "\nTotal Store Revenue: $" << totalRevenue << endl;
    }

    void saveReport() {
        ofstream outFile("inventory_status.txt");
        if (outFile.is_open()) {
            outFile << "--- INVENTORY STATUS REPORT ---\n";
            for (const auto& p : catalog) {
                outFile << p.getName() << " | Stock: " << p.getStockQuantity() << " | Sold: " << p.getUnitsSold() << "\n";
            }
            outFile.close();
            cout << "[System] Report saved to inventory_status.txt" << endl;
        }
    }
};

int main() {
    InventorySystem store;

    store.addProduct(Product(101, "MacBook Pro", 1999.99, 10, 2));
    store.addProduct(Product(102, "iPhone 15", 999.00, 3, 2));
    store.addProduct(Product(103, "AirPods", 150.00, 20, 5));

    store.processSale(101, 1);
    store.processSale(102, 2);
    store.processSale(103, 5);

    store.showInventory();
    store.showTopSellers();
    store.showLowStockReport();
    store.saveReport();

    return 0;
}