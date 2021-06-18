#pragma once

#include "httplib.h"
#include "black_marlin.hpp"

class HttpRequestHandler {
public:
    // Handles a Get request.
    void HandleGet(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    // Handles a Post request.
    void HandlePost(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    // Handles Put and Patch requests.
    void HandlePutAndPatch(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    // Handles a Delete request.
    void HandleDelete(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    // Handles a Get request in the "/exists" route.
    void HandleGetExists(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    // Handles a Get request in the "/count" route.
    void HandleGetCount(BlackMarlin*& p_blackMarlin, httplib::Response& p_res);
    // Handles a Delete request in the "/flush" route.
    void HandleDeleteFlush(BlackMarlin*& p_blackMarlin, httplib::Response& p_res);
private:
    // Content-Type header value if needed.
    const char* m_content_type = "*/*; charset=utf-8";
};
