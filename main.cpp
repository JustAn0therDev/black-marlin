#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include "httplib.h"
#include "black_marlin.hpp"
#include "status_codes.hpp"

int main() {
	httplib::Server server;

	auto blackMarlin = new BlackMarlin();

	std::cout << "BLACK MARLIN v1.0" << std::endl;
	std::cout << std::endl;

	server.Get("/", [&blackMarlin](const httplib::Request& req, httplib::Response& res) {
		std::string value;

		if (req.has_param("key")) {
			value = blackMarlin->Get(req.get_param_value("key"));

			if (std::empty(value)) {
				res.status = (int)StatusCodes::NOT_FOUND;
			}
		}
		else {
			res.status = (int)StatusCodes::BAD_REQUEST;
		}

		res.set_content(value, "*/*");
	});

	server.Post("/", [&blackMarlin](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("key")) {
			std::string key = req.get_param_value("key");
			std::string* body = new std::string(req.body);
			std::string& keyRef = key;

			blackMarlin->Set(keyRef, body);
			res.status = (int)StatusCodes::CREATED;
		}
		else {
			res.status = (int)StatusCodes::BAD_REQUEST;
		}

		res.set_content("", "*/*");
	});

	server.Put("/", [&blackMarlin](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("key")) {
			std::string key = req.get_param_value("key");
			std::string* body = new std::string(req.body);
			std::string& keyRef = key;

			blackMarlin->Set(keyRef, body);
			res.status = (int)StatusCodes::CREATED;
		}
		else {
			res.status = (int)StatusCodes::BAD_REQUEST;
		}

		res.set_content("", "*/*");
	});

	server.Patch("/", [&blackMarlin](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("key")) {
			std::string key = req.get_param_value("key");
			std::string* body = new std::string(req.body);
			std::string& keyRef = key;

			blackMarlin->Set(keyRef, body);
			res.status = (int)StatusCodes::CREATED;
		}
		else {
			res.status = (int)StatusCodes::BAD_REQUEST;
		}

		res.set_content("", "*/*");
	});

	server.Delete("/", [&blackMarlin](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("key")) {
			std::string& keyRef = req.get_param_value("key");

			blackMarlin->Delete(keyRef);
		}
		else {
			res.status = (int)StatusCodes::BAD_REQUEST;
		}

		res.set_content("", "*/*");
	});

	server.Get("/exists", [&blackMarlin](const httplib::Request& req, httplib::Response& res) {
		if (req.has_param("key")) {
			std::string& keyRef = req.get_param_value("key");

			bool exists = blackMarlin->Exists(keyRef);

			if (!exists) {
				res.status = (int)StatusCodes::NOT_FOUND;
			}
		}
		else {
			res.status = (int)StatusCodes::BAD_REQUEST;
		}

		res.set_content("", "*/*");
	});

	server.Get("/count", [&blackMarlin](const httplib::Request&, httplib::Response& res) {
		res.set_content(std::to_string(blackMarlin->Count()), "*/*");
	});

	server.Get("/kill", [&blackMarlin](const httplib::Request&, httplib::Response& res) {
		delete blackMarlin;
		exit(0);
	});

	const char* address = "127.0.0.1";
	int port = 6969;

	std::cout << "Listening at: " << address << ":" << port << std::endl;
	server.listen(address, port);

	return EXIT_SUCCESS;
}
