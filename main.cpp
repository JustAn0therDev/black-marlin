#include <iostream>
#include "vendor/httplib.h"
#include "BlackMarlin/black_marlin.hpp"
#include "HTTP/http_request_handler.hpp"
#include "Util/util.hpp"
#include "Logger/logger.hpp"
#include "ArgParser/arg_parser.hpp"

constexpr short DEFAULT_PORT = 7000;

void IgnoreSIGPIPEWritingToSTDOUT(int sig_number);
long GetPortFromArgs(Util& util, int& argc, char** argv) noexcept;
void SetRoutes(httplib::SSLServer& server, BlackMarlin& black_marlin, HttpRequestHandler& http_request_handler) noexcept;

int main(int argc, char** argv)
{
	httplib::SSLServer server("./localhost.crt", "./localhost.key");
	BlackMarlin black_marlin;
    Logger logger;
    Util util;
	HttpRequestHandler http_request_handler;

	long port = GetPortFromArgs(util, argc, argv);

	SetRoutes(server, black_marlin, http_request_handler);
    signal(SIGPIPE, IgnoreSIGPIPEWritingToSTDOUT);

	std::cout << "Listening at port " << port << "\n";
    server.listen("127.0.0.1", (int)port);

	return EXIT_SUCCESS;
}

void IgnoreSIGPIPEWritingToSTDOUT(int sig_number) 
{
    std::cout << "Identified SIGPIPE error. Signal number:" << sig_number << "\n";
}

long GetPortFromArgs(Util& util, int& argc, char** argv) noexcept
{
	if (argc != 2)
		return DEFAULT_PORT;

	const auto port = ArgParser::GetPortFromArg(argv[1]);

    if (port == 0 || port > USHRT_MAX) {
        util.Panic("The port argument was given an invalid value. Expected a port number within valid range; got: " + std::string(argv[1]));
    }

    return port;
}

void SetRoutes(httplib::SSLServer& server, BlackMarlin& black_marlin, HttpRequestHandler& http_request_handler) noexcept
{
	server.Get("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleGet(black_marlin, req, res);
	});

	server.Post("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandlePost(black_marlin, req, res);
	});

	server.Put("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandlePutAndPatch(black_marlin, req, res);
	});

	server.Patch("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandlePutAndPatch(black_marlin, req, res);
	});

	server.Delete("/", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleDelete(black_marlin, req, res);
	});

	server.Delete("/flush", [&black_marlin, &http_request_handler](const httplib::Request&, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleDeleteFlush(black_marlin, res);
	});

	server.Get("/exists", [&black_marlin, &http_request_handler](const httplib::Request& req, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleGetExists(black_marlin, req, res);
	});

	server.Get("/count", [&black_marlin, &http_request_handler](const httplib::Request&, httplib::Response& res)
	{
		http_request_handler.SetResponseHeadersFromConfig(res);
		http_request_handler.HandleGetCount(black_marlin, res);
	});
}
