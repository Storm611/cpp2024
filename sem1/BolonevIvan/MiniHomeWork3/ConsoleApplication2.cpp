#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;


class item
{
public:
	std::string name;
	double price;
	double weight;

	item(const std::string& name, double price, double weight) : name(name), price(price), weight(weight) {}
};
class Shopbase
{
public:
	virtual std::string getName() const = 0;
	virtual void addName(const std::string& name) = 0;
	virtual double getAvgPrice() const = 0;
	virtual double getAvgWeight() const = 0;
	virtual void addItem(const item& item) = 0;
};
class Customshop : public Shopbase
{
private:
	std::vector<item> items;
	std::string name;

public:
	std::string getName() const override {
		return this->name;
	}
	void addName(const string& name) override {
		this->name = name;
	}


	void addItem(const item& item) override {
		items.push_back(item);
	}

	double getAvgPrice() const override {
		if (items.empty()) return 0.0;

		double totalPrice = 0.0;
		for (const auto& item : items)
		{
			totalPrice += item.price;
		}
		return totalPrice / items.size();
	}

	double getAvgWeight() const override {

		double totalWeight = 0.0;
		for (const auto& item : items)
		{
			totalWeight += item.weight;
		}
		return totalWeight / items.size();
	}
};
void readShopsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Shop") == 0) {
            std::string shopName = line.substr(5); // Отступаем 5 символов
            std::getline(file, line); 
            int itemCount = std::stoi(line.substr(5)); 

            Customshop shop;

            for (int i = 0; i < itemCount; ++i) {
                std::getline(file, line);
                std::istringstream iss(line);
                std::string itemName;
                double price, weight;
                iss >> itemName >> price >> weight;
                shop.addItem(item(itemName, price, weight));
            }

            std::cout << "Магазин " << shopName << " имеет " << itemCount
                << " предметов, средняя цена и вес которых соответственно "
                << shop.getAvgPrice() << " / " << shop.getAvgWeight() << std::endl;
        }
    }
    file.close();
}

int main()
{
	setlocale(LC_ALL, "ru");
	system("chcp 1251");

	readShopsFromFile("mhw3.txt");
	return 0;
}