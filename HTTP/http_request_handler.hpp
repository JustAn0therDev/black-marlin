#include "httplib.h"
#include "../BlackMarlin/black_marlin.hpp"
#include "../ServerConfigs/server_configs.hpp"

#ifndef HTTPREQUESTHANDLERCPP
#define HTTPREQUESTHANDLERCPP
class HttpRequestHandler 
{
public:
	// The object's constructor.
	HttpRequestHandler() noexcept;
	// Handles a Get request.
	void HandleGet(const BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) const noexcept;
	// Handles a Post request.
	void HandlePost(BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles Put and Patch requests.
	void HandlePutAndPatch(BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles a Delete request.
	void HandleDelete(BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles a Delete request in the "/flush" route.
	void HandleDeleteFlush(BlackMarlin& p_blackMarlin, httplib::Response& p_res) noexcept;
	// Handles a Get request in the "/exists" route.
	void HandleGetExists(const BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) const noexcept;
	// Handles a Get request in the "/count" route.
	void HandleGetCount(const BlackMarlin& p_blackMarlin, httplib::Response& p_res) const noexcept;
    // Sets the response headers.
    void SetResponseHeadersFromConfig(httplib::Response& p_res) const noexcept;
private:
	// Content-Type header value if needed.
	const char* m_content_type = "*/*; charset=utf-8";
	// Validates if the param value is valid.
	bool IsValidSecondsParam(std::string p_seconds_param) noexcept;
	// Internal ServerConfigs object.
	ServerConfigs m_server_configs;
};
#endif
