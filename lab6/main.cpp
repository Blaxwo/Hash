#include <iostream>
#include <string>

class HashTable {
private:
    int tableSize;

    struct Node {
        int key;
        std::string value;
        Node* next;
    };

    Node** table;

    int divisionHash(int key) {
        return key % tableSize;
    }

public:
    HashTable(int size) : tableSize(size) {
        table = new Node*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    void add(int key, const std::string& value) {
        int index = divisionHash(key);
        Node* newNode = new Node{key, value, nullptr};

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr) {
                if (current->key == key) {
                    std::cout << "Key already exists in the table." << std::endl;
                    delete newNode;
                    return;
                }
                current = current->next;
            }
            if (current->key == key) {
                std::cout << "Key already exists in the table." << std::endl;
                delete newNode;
                return;
            }
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    std::string search(int key) {
        int index = divisionHash(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return "";
    }

    void remove(int key) {
        int index = divisionHash(key);
        Node* current = table[index];
        Node* previous = nullptr;

        while (current != nullptr && current->key != key) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        if (previous == nullptr) {
            table[index] = current->next;
        } else {
            previous->next = current->next;
        }

        delete current;
    }

    void print() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            std::cout << i << ": ";
            while (current != nullptr) {
                std::cout << "(" << current->key << ", " << current->value << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] table;
    }
};

int main() {
    int tableSize;
    std::cout << "Enter the table size: ";
    std::cin >> tableSize;

    HashTable hashTable(tableSize);
    int choice;

    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add" << std::endl;
        std::cout << "2. Search" << std::endl;
        std::cout << "3. Remove" << std::endl;
        std::cout << "4. Print" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int key;
                std::string value;
                std::cout << "Enter key: ";
                std::cin >> key;
                std::cout << "Enter value: ";
                std::cin >> value;
                hashTable.add(key, value);
                break;
            }
            case 2: {
                int key;
                std::cout << "Enter key to search: ";
                std::cin >> key;
                std::string result = hashTable.search(key);
                if (!result.empty()) {
                    std::cout << "Found: " << result << std::endl;
                } else {
                    std::cout << "Not found" << std::endl;
                }
                break;
            }
            case 3: {
                int key;
                std::cout << "Enter key to remove: ";
                std::cin >> key;
                hashTable.remove(key);
                break;
            }
            case 4: {
                hashTable.print();
                break;
            }
            case 5:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}
