#include <iostream>
#include <memory>
#include <string>
#include <stdlib.h>
#include "httplib.h"
#include "black_marlin.hpp"
#include "http_request_handler.hpp"

constexpr short DEFAULT_PORT = 7000;

struct portip {
	int port;
	std::string ip;
} typedef Connection;

Connection GetIPAndPortFromArgs(int& argc, char **argv);
void SetRoutes(httplib::Server& server, BlackMarlin& black_marlin, HttpRequestHandler& http_request_handler);

int main(int argc, char **argv)
{
	httplib::Server server;
	BlackMarlin black_marlin;
	HttpRequestHandler http_request_handler;

	Connection conn = GetIPAndPortFromArgs(argc, argv);
	
	SetRoutes(server, black_marlin, http_request_handler);

	std::cout << "Listening at: " << conn.ip << ":" << conn.port << "\n";
    server.listen(conn.ip.c_str(), conn.port);

	return EXIT_SUCCESS;
}

Connection GetIPAndPortFromArgs(int& argc, char **argv)
{
	Connection conn = Connection{};

	if (argc != 2)
	{
		conn.port = DEFAULT_PORT;
	}
	else
	{
		conn.port = std::atoi(argv[1]);
	}

    conn.ip = "127.0.0.1";

	return conn;
}

void SetRoutes(httplib::Server& server, BlackMarlin& black_marlin, HttpRequestHandler& http_request_handler)
{
	server.Get("/exit", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		exit(1);
	});

	/* 
	server.Get("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res) {
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleGet(black_marlin, req, res);
	});
	*/

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
