#include "lab5_ex7.h"

Product::Product(std::string nameC, unsigned int idC, double weightC, double priceC, unsigned int daysC)
    : id(idC), days(daysC) {
        if (nameC == "") {
            throw std::logic_error("name is empty");
        }
        if (weightC < 0) {
            throw std::logic_error("weight is negative");
        }
        if (priceC < 0) {
            throw std::logic_error("price is negative");
        }
        name = nameC;
        weight = weightC;
        price = priceC;
}

Product::Product(const Product& second) : name(second.name), id(second.id), weight(second.weight),
                                            price(second.price), days(second.days) {}

Product& Product::operator=(const Product& second) {
    name = second.name;
    id = second.id;
    weight = second.weight;
    price = second.price;
    days = second.days;
    return *this;
}

void Product::toStream(std::ostream& os) const {
    os << "Name: " << name << "\n" 
        << "ID: " << id << "\n"
        << "Weight: " << weight << "\n"
        << "Price: " << price << "\n"
        << "Day: " << days << "\n";
}

Product::~Product() {}

std::string Product::getCategory() const {
    return "Product";
}

double Product::calculateStorageFee() const {
        return weight;
}

unsigned int Product::getId() const {
    return id;
}

void Product::displayInfo() const {
    std::cout << "Name: " << name << "\n" 
            << "ID: " << id << "\n"
            << "Weight: " << weight << "\n"
            << "Price: " << price << "\n"
            << "Day: " << days << "\n";
}

PerishableProduct::PerishableProduct(std::string nameC, unsigned int idC, double weightC, 
                    double priceC, unsigned int daysC, unsigned int daysToExpirationC) 
                    : Product::Product(nameC, idC, weightC, priceC, daysC), 
                    daysToExpiration(daysToExpirationC) {}

PerishableProduct::PerishableProduct(const PerishableProduct& second) 
    : Product(second), 
    daysToExpiration(second.daysToExpiration) {}

PerishableProduct& PerishableProduct::operator=(const PerishableProduct& second) {
    Product::operator=(second);
    daysToExpiration = second.daysToExpiration;
    return *this;
}

void PerishableProduct::toStream(std::ostream& os) const {
    Product::toStream(os);
    os << "Days to expiration: " << daysToExpiration << "\n";

}

PerishableProduct::~PerishableProduct() {}

std::string PerishableProduct::getCategory() const {
    return "PerishableProduct";
}

unsigned int PerishableProduct::getdayToExpiration() {
    return daysToExpiration;
}

double PerishableProduct::calculateStorageFee() const {
        return Product::calculateStorageFee() * (10 - daysToExpiration);
}

ElectronicProduct::ElectronicProduct(std::string nameC, unsigned int idC, double weightC, 
                    double priceC, unsigned int daysC, unsigned int warrantyPeriodC,
                    unsigned int powerRatingC) 
                    : Product(nameC, idC, weightC, priceC, daysC), 
                    warrantyPeriod(warrantyPeriodC), powerRating(powerRatingC)  {}

ElectronicProduct::ElectronicProduct(const ElectronicProduct& second) : Product(second),
                                                                        warrantyPeriod(second.warrantyPeriod),
                                                                        powerRating(second.powerRating) {}

ElectronicProduct& ElectronicProduct::operator=(const ElectronicProduct& second) {
    Product::operator=(second);
    warrantyPeriod = second.warrantyPeriod;
    powerRating = second.powerRating;
    return *this;
}

void ElectronicProduct::toStream(std::ostream& os) const {
    Product::toStream(os);
    os << "Warranty period: " << warrantyPeriod << "\n"
        << "Power rating: " << powerRating << "\n";
}

ElectronicProduct::~ElectronicProduct() {}

std::string ElectronicProduct::getCategory() const {
    return "ElectronicProduct";
}

void ElectronicProduct::displayInfo() const {
        Product::displayInfo();
        std::cout <<"Warranty period: " << warrantyPeriod << "\n"
        << "Power rating: " << powerRating << "\n";
}

BuildingMaterial::BuildingMaterial(std::string nameC, unsigned int idC, double weightC, double priceC, 
                                    unsigned int daysC, bool flammabilityC) 
                                    : Product(nameC, idC, weightC, priceC, daysC),
                                    flammability(flammabilityC) {}

BuildingMaterial::BuildingMaterial(const BuildingMaterial& second) : Product(second), 
                                                                flammability(second.flammability) {}
                                                            
BuildingMaterial& BuildingMaterial::operator=(const BuildingMaterial& second) {
    Product::operator=(second);
    flammability = second.flammability;
    return *this;
}

void BuildingMaterial::toStream(std::ostream& os) const {
    Product::toStream(os);
    os << "Flammability: " << flammability << "\n";

}

BuildingMaterial::~BuildingMaterial() {}

std::string BuildingMaterial::getCategory() const {
    return "BuildingMaterial";
}

double BuildingMaterial::calculateStorageFee() const {
    return (flammability) ? 3 * Product::calculateStorageFee() : Product::calculateStorageFee();
}

Warehouse& Warehouse::operator+=(std::unique_ptr<Product> product) {
    if (storage.find(product->getId()) != storage.end()) {
        throw std::logic_error("product already exist");
    }
    storage[product->getId()] = std::move(product);
    return *this;
}

Warehouse& Warehouse::operator-=(const unsigned int id) {
    storage.erase(id);
    return *this;
}

Product* Warehouse::operator[](const unsigned int id) {
    if (storage.find(id) == storage.end()) {
        return nullptr;
    }
    return storage[id].get();
}

std::vector<Product> Warehouse::findCategory(std::string category) {
    std::vector<Product> ans;
    // при итерации ключ константен
    for (const std::pair<const unsigned int, std::unique_ptr<Product>>& pair : storage) {
        if (pair.second.get()->getCategory() == category) {
            ans.push_back(*(pair.second.get()));
        }
    }
    return ans;

}

std::vector<Product> Warehouse::getExpiringProducts(unsigned int days) {
    std::vector<Product> ans;
    for (const std::pair<const unsigned int, std::unique_ptr<Product>>& pair : storage) {
        if (pair.second.get()->getCategory() == "PerishableProduct") {
            PerishableProduct* product = dynamic_cast<PerishableProduct*> (pair.second.get());
            if (product->getdayToExpiration() <= days) {
                ans.push_back(*(pair.second.get()));
            }
        }
    }
    return ans;
}

bool ProductCmp(const void* a, const void* b) {
    const Product* first = static_cast<const Product*>(a);
    const Product* second = static_cast<const Product*>(b);
    return first->getCategory() < second->getCategory(); 
}


void Warehouse::displayInfo() {
    std::vector<Product*> ans;
    for (const std::pair<const unsigned int, std::unique_ptr<Product>>& pair : storage) {
        ans.push_back((pair.second.get()));
    }
    std::sort(ans.begin(), ans.end(), ProductCmp);
    std::string flag = "";
    for (const Product* product : ans) {
        if (product->getCategory() != flag) {
            flag = product->getCategory();
            std::cout << "\n" << product->getCategory() << "\n" 
            << "--------------------" << "\n";
        }
        product->displayInfo();
    }

}

double Warehouse::totalFee() {
    double ans = 0;
    for (const std::pair<const unsigned int, std::unique_ptr<Product>>& pair : storage) {
        ans += pair.second.get()->calculateStorageFee();
    }
    return ans;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    product.toStream(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse) {
    for (const std::pair<const unsigned int, std::unique_ptr<Product>>& pair : warehouse.storage) {
        os << *(pair.second) << "--------------------\n";
    }
    return os;
}


