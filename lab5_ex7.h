#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <compare>


bool ProductCmp(const void* a, const void* b);

class Product {
private:
    std::string name;
    unsigned int id;
    double weight;
    double price;
    unsigned int days;
public:
    Product(std::string nameC, unsigned int idC, double weightC, double priceC, unsigned int daysC);
    Product(const Product& second);
    Product& operator=(const Product& second);
    virtual ~Product();
    unsigned int getId() const;
    virtual double calculateStorageFee() const;
    virtual void displayInfo() const;
    virtual std::string getCategory() const;
    friend std::ostream& operator<<(std::ostream& os, const Product& product);
protected:
    virtual void toStream(std::ostream& os) const;

};

class PerishableProduct : public Product {
private:
    unsigned int daysToExpiration;
public:
    PerishableProduct(std::string nameC, unsigned int idC, double weightC, 
                    double priceC, unsigned int daysC, unsigned int daysToExpirationC);
    PerishableProduct(const PerishableProduct& second);
    PerishableProduct& operator=(const PerishableProduct& second);
    ~PerishableProduct() override;
    double calculateStorageFee() const override;
    std::string getCategory() const override;
    unsigned int getdayToExpiration();
protected:
    void toStream(std::ostream& os) const override;
};

class ElectronicProduct : public Product {
private:
    unsigned int warrantyPeriod;
    unsigned int powerRating;
public:
    ElectronicProduct(std::string nameC, unsigned int idC, double weightC, double priceC, 
                    unsigned int daysC, unsigned int warrantyPeriodC,unsigned int owerRatingC);
    ElectronicProduct(const ElectronicProduct& second);
    ~ElectronicProduct() override;
    ElectronicProduct& operator=(const ElectronicProduct& second);
    void displayInfo() const override;
    std::string getCategory() const override;
protected:
    void toStream(std::ostream& os) const override;
};

class BuildingMaterial : public Product {
private:
    bool flammability;
public:
    BuildingMaterial(std::string nameC, unsigned int idC, double weightC, double priceC, 
                    unsigned int daysC, bool flammabilityC);
    BuildingMaterial(const BuildingMaterial&);
    BuildingMaterial& operator=(const BuildingMaterial& second);
    ~BuildingMaterial() override;
    double calculateStorageFee() const override;
    std::string getCategory() const override;
protected:
    void toStream(std::ostream& os) const override;
};

class Warehouse final {
private:
    std::map<unsigned int, std::unique_ptr<Product>> storage;
public:
    Warehouse& operator+=(std::unique_ptr<Product>);
    Warehouse& operator-=(const unsigned int);
    Product* operator[](const unsigned int);
    std::vector<Product> findCategory(std::string);
    std::vector<Product> getExpiringProducts(unsigned int);
    void displayInfo();
    double totalFee();
    friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse);

};

