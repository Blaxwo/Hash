#include <iostream>
#include <string>

class HashTable {
private:
    int tableSize;

    struct Node {
        int key;
        std::string value;
        bool isDeleted;
    };

    Node** table;

    int divisionHash(int key, int i) {
        return ((key % tableSize)+i);
    }

public:
    HashTable(int size) : tableSize(size) {
        table = new Node*[tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    void add(int key, const std::string& value) {
        int i = 0;
        Node* newNode = new Node{key, value};
        while(i!=tableSize){
            int index = divisionHash(key, i);
            if (table[index] == nullptr&&index<=tableSize-1) {
                table[index] = newNode;
                return;
            } else {
                if(index<=tableSize-1){
                    if (table[index]->isDeleted) {
                        delete table[index];
                        table[index] = newNode;
                        return;
                    }
                    else {
                        i = i + 1;
                    }
                }
                else{
                    std::cout << "Hash table is full"<<std::endl;
                    return;
                }
            }
        }
        std::cout << "Hash table is full"<<std::endl;
    }

    std::string search(int key) {
        int i = 0;
        int index=divisionHash(key,i);
        while(i!=tableSize&&table[index]!= nullptr&&index<=tableSize-1){
            if (table[index]->key == key && !table[index]->isDeleted) {
                return table[index]->value;
            } else {
                index = divisionHash(key, ++i);
            }
        }
        return "";
    }

    void remove(int key) {
        int i=0;
        int index = divisionHash(key,i);

        while (table[index] != nullptr  && index<=tableSize-1) {
            if (table[index]->key == key && !table[index]->isDeleted) {
                table[index]->isDeleted = true;
                return;//remove return if need to delete all elements with such key
            }
            index = divisionHash(key,++i);
        }
    }

    void print() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            std::cout << i << ": ";
            if (current != nullptr && !current->isDeleted) {
                std::cout << "(" << current->key << ", " << current->value << ") ";
            }
            std::cout << std::endl;
        }
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            Node* current = table[i];
            if (current != nullptr) {
                delete current; // Only delete non-null nodes
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
