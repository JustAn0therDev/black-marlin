#ifndef HTTPREQUESTHANDLERCPP
#define HTTPREQUESTHANDLERCPP

#include "../vendor/httplib.h"
#include "../BlackMarlin/black_marlin.hpp"
#include "../ServerConfigs/server_configs.hpp"
#include "../Logger/logger.hpp"

class HttpRequestHandler 
{
public:
	HttpRequestHandler() noexcept;
	// Handles a Get request.
	void HandleGet(const BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles a Post request.
	void HandlePost(BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles Put and Patch requests.
	void HandlePutAndPatch(BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles a Delete request.
	void HandleDelete(BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles a Delete request in the "/flush" route.
	void HandleDeleteFlush(BlackMarlin& p_blackMarlin, httplib::Response& p_res) noexcept;
	// Handles a Get request in the "/exists" route.
	void HandleGetExists(const BlackMarlin& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept;
	// Handles a Get request in the "/count" route.
	void HandleGetCount(const BlackMarlin& p_blackMarlin, httplib::Response& p_res) noexcept;
    // Sets the response headers.
    void SetResponseHeadersFromConfig(httplib::Response& p_res) noexcept;
private:
	// Content-Type header value if needed.
	const char* m_content_type = "*/*; charset=utf-8";
	// Validates if the param value is valid.
	static bool IsValidSecondsParam(const std::string& p_seconds_param);
	// Internal ServerConfigs object.
	ServerConfigs m_server_configs;
    // The object's internal logger.
    Logger m_logger;
};

#endif /* HTTPREQUESTHANDLERCPP */
