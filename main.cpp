#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include "httplib.h"
#include "black_marlin.hpp"
#include "http_request_handler.hpp"

int main() {
	httplib::Server server;

	auto black_marlin = BlackMarlin();
	HttpRequestHandler http_request_handler = HttpRequestHandler();

	server.Get("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.HandleGet(black_marlin, req, res);
	});

	server.Post("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.HandlePost(black_marlin, req, res);
	});

	server.Put("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.HandlePutAndPatch(black_marlin, req, res);
	});

	server.Patch("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.HandlePutAndPatch(black_marlin, req, res);
	});

	server.Delete("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.HandleDelete(black_marlin, req, res);
	});

	server.Delete("/flush", [&black_marlin, &http_request_handler](const httplib::Request&, httplib::Response& res) {
		http_request_handler.HandleDeleteFlush(black_marlin, res);
	});

	server.Get("/exists", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.HandleGetExists(black_marlin, req, res);
	});

	server.Get("/count", [&black_marlin, &http_request_handler](const httplib::Request&, httplib::Response& res) {
		http_request_handler.HandleGetCount(black_marlin, res);
	});

	std::cout << "Listening at: " << http_request_handler.m_ip_address << ":" << http_request_handler.m_port << "\n";
    server.listen(http_request_handler.m_ip_address, http_request_handler.m_port);

	return EXIT_SUCCESS;
}
