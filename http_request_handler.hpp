#pragma once

#include "httplib.h"
#include "black_marlin.hpp"

class HttpRequestHandler {
public:
    void HandleGet(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    void HandlePost(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    void HandlePutAndPatch(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    void HandleDelete(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    void HandleGetExists(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res);
    void HandleGetCount(BlackMarlin*& p_blackMarlin, httplib::Response& p_res);
    void HandleDeleteFlush(BlackMarlin*& p_blackMarlin, httplib::Response& p_res);
};
