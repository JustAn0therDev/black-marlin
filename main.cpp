#include <iostream>
#include <memory>
#include <string>
#include "httplib.h"
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
    std::cout << std::endl;

    httplib::Server server;
    const char* address = "127.0.0.1";
    int port = 6969;

    /*
    * THE MAIN COMMANDS WILL USE THE MAIN ROUTE "/"
        GET -> GET
        POST, PATCH, PUT -> SET
        DELETE -> DELETE
        COUNT -> GET "/count"
        EXISTS -> GET "/exists"
    */

    key = "some value";
    // testing json values formatting.
    std::string jsonValue = R"({"message": "Hello", "time": "02:11"})";
    std::string* value = &jsonValue;

    blackMarlin->Set(key, value);

    server.Get("/", [&blackMarlin, &key](const httplib::Request&, httplib::Response &res) {
        auto& keyRef = key;
        res.set_content(blackMarlin->Get(keyRef), "text/plain");
    });

    std::cout << "Listening at: " << address << ":" << port << std::endl;
    server.listen(address, port);
    
    return 0;
}
