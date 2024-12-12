#include "lab5_ex7_classes.cpp"

int main() {
    ElectronicProduct a("fen", 123, 1.23, 103.7, 2, 120, 200);
    Product &b = a;
    //b.displayInfo();
    Warehouse warehouse;

    warehouse += std::make_unique<PerishableProduct>("Cheese", 2, 2.0, 5.0, 15, 3);
    warehouse += std::make_unique<ElectronicProduct>("Laptop", 3, 3.0, 1200.0, 30, 120, 200);
    warehouse += std::make_unique<PerishableProduct>("Milk", 1, 1.5, 2.5, 10, 2);
    warehouse += std::make_unique<ElectronicProduct>("Phone", 4, 1.0, 800.0, 20, 365, 30);
    warehouse += std::make_unique<BuildingMaterial>("Cement", 5, 50.0, 300.0, 60, false);
    warehouse += std::make_unique<BuildingMaterial>("Paint", 6, 10.0, 50.0, 20, true);
    std::cout << warehouse;
}