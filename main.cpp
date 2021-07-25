#include <iostream>
#include <memory>
#include <string>
#include <regex>
#include <stdlib.h>
#include "httplib.h"
#include "black_marlin.hpp"
#include "http_request_handler.hpp"
#include "server_connection_info.hpp"

constexpr short DEFAULT_PORT = 7000;

ServerConnectionInfo GetIPAndPortFromArgs(int& argc, char** argv);
void SetRoutes(httplib::Server& server, BlackMarlin& black_marlin, HttpRequestHandler& http_request_handler);

int main(int argc, char** argv)
{
	httplib::Server server;
	BlackMarlin black_marlin;
	HttpRequestHandler http_request_handler;

	ServerConnectionInfo conn = GetIPAndPortFromArgs(argc, argv);

	SetRoutes(server, black_marlin, http_request_handler);

	std::cout << "Listening at: " << conn.ip << ":" << conn.port << "\n";
	server.listen(conn.ip.c_str(), conn.port);

	return EXIT_SUCCESS;
}

ServerConnectionInfo GetIPAndPortFromArgs(int& argc, char** argv)
{
	ServerConnectionInfo conn = ServerConnectionInfo{};

	const char* port_arg = argv[1];
	std::regex only_numbers_pattern("[0-9]+");

	if (argc != 2)
	{
		conn.port = DEFAULT_PORT;
	}
	else
	{
		if (regex_match(port_arg, only_numbers_pattern))
		{
			conn.port = std::atoi(port_arg);
		}
		else
		{
			std::cout << "Expected only numbers for port argument. Got: " << port_arg << "\n";
			exit(1);
		}
	}

	conn.ip = "127.0.0.1";

	return conn;
}

void SetRoutes(httplib::Server& server, BlackMarlin& black_marlin, HttpRequestHandler& http_request_handler)
{
	server.Get("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleGet(black_marlin, req, res);
	});

	server.Post("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandlePost(black_marlin, req, res);
	});

	server.Put("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandlePutAndPatch(black_marlin, req, res);
	});

	server.Patch("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandlePutAndPatch(black_marlin, req, res);
	});

	server.Delete("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleDelete(black_marlin, req, res);
	});

	server.Delete("/flush", [&black_marlin, &http_request_handler](const httplib::Request&, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleDeleteFlush(black_marlin, res);
	});

	server.Get("/exists", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleGetExists(black_marlin, req, res);
	});

	server.Get("/count", [&black_marlin, &http_request_handler](const httplib::Request&, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleGetCount(black_marlin, res);
	});
}
