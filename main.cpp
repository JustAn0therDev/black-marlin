#include <iostream>
#include <memory>
#include <string>
#include "black_marlin.hpp"

template<typename T>
void printLine(T value) {
    std::cout << value << std::endl;
}

template<typename T>
void printVector(T vector) {
    for (auto& current : vector) {
        std::cout << current << std::endl;
    }
}

int main() {
    std::string command;
    std::string key;

    auto blackMarlin = std::make_unique<BlackMarlin>();

    std::cout << "BLACK MARLIN v1.0" << std::endl;

    while (1) {
        std::getline(std::cin, command);

        if (command == "GET") {
            printLine("Insert a key: ");

            std::getline(std::cin, key);
            std::string& keyRef = key;
            
            printLine(blackMarlin->Get(keyRef));
        } else if (command == "SET") {
            // ok. A NEW POINTER should be created everytime a SET command is read.
            auto* valuePtr = new std::string();

            printLine("Insert a key: ");
            std::getline(std::cin, key);
            
            printLine("Insert a value: ");
            // does getline accept a ptr (it should since a string is jjust a char*)? 
            std::getline(std::cin, *valuePtr);

            blackMarlin->Set(key, valuePtr);

            printLine("OK");
            
        } else if (command == "DELETE") {
            printLine("Insert a key: ");
            std::getline(std::cin, key);

            std::string& keyRef = key;
            blackMarlin->Delete(keyRef);
            
            printLine("OK");
        } else if (command == "FLUSH") {
            blackMarlin->Flush();
            printLine("OK");
        } else if (command == "COUNT") {
            printLine(blackMarlin->Count());
        } else if (command == "GETALL") {
            printVector(blackMarlin->GetAll());
        } else if (command == "QUIT") {
            break;
        } else {
            std::cout << "Command not found" << std::endl;
        }
    }
    
    return 0;
}
