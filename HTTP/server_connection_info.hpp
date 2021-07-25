#include <string>
#ifndef SERVERCONNECTIONINFO
#define SERVERCONNECTIONINFO
struct connection {
	// Connection port
	int port;
	// The server's IP address (127.0.0.1)
	std::string ip;
} typedef ServerConnectionInfo;
#endif /* SERVERCONNECTIONINFO */