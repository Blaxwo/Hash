#include <iostream>
#include <string>
#include <math.h>

const int TABLE_SIZE = 3;

class HashTable {
public:
    HashTable();

    int divisionHash(int key);
    int multiplicationHash(int key);
    int stringHash(const std::string& key);
};

HashTable::HashTable() {
}

int HashTable::divisionHash(int key) {
    return key % TABLE_SIZE;
}

int HashTable::multiplicationHash(int key) {
    const double A = 0.61803398875; // Золоте число
    return static_cast<int>(TABLE_SIZE * (key * A - static_cast<int>(key * A)));
}

int HashTable::stringHash(const std::string& key) {
    int hash = 0;
    int n = key.length();

    for (int i = 0; i < n; i++) {
        // Додавання ASCII-коду символу, піднятого до степеня i
        hash += static_cast<int>(key[i]) * static_cast<int>(std::pow(31, n - i - 1));
    }

    return hash % TABLE_SIZE;
}

int main() {
    HashTable hashtable;

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Calculate Division Hash" << std::endl;
        std::cout << "2. Calculate Multiplication Hash" << std::endl;
        std::cout << "3. Calculate String Hash" << std::endl;
        std::cout << "4. Stop" << std::endl;
        int choice;
        std::cin >> choice;

        if (choice == 1 || choice == 2 || choice == 3) {
            if (choice != 3) {
                int key;
                std::cout << "Enter the key: ";
                std::cin >> key;
                int hash;
                if (choice == 1) {
                    hash = hashtable.divisionHash(key);
                } else if (choice == 2) {
                    hash = hashtable.multiplicationHash(key);
                }
                std::cout << "Hash result: " << hash << std::endl;
            } else {
                std::string key;
                std::cout << "Enter the key (string): ";
                std::cin >> key;
                int hash = hashtable.stringHash(key);
                std::cout << "Hash result: " << hash << std::endl;
            }
        } else if (choice == 4) {
            break;
        }
    }

    return 0;
}
