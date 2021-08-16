#include "../BlackMarlin/black_marlin.hpp"
#include "../Logger/logger.hpp"
#include "../ServerConfigs/server_configs.hpp"
#include "../vendor/httplib.h"
#include "http_request_handler.hpp"
#include "status_code.hpp"
#include <string>

HttpRequestHandler::HttpRequestHandler() noexcept
{
    this->m_server_configs.LoadHeadersFromConfigFile();
    this->m_logger = Logger();
}

void HttpRequestHandler::HandleGet(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept
{
    try
    {
        if (!p_req.has_param("key"))
        {
            p_res.status = static_cast<int>(StatusCode::kBadRequest);
            return;
        }

        const auto& value = p_black_marlin.Get(p_req.get_param_value("key"));

        if (std::empty(value))
        {
            p_res.status = static_cast<int>(StatusCode::kNoContent);
            return;
        }

        p_res.set_content(value, this->m_content_type);
    }
    catch (std::exception& e)
    {
        const auto& key = p_req.get_param_value("key");
        this->m_logger.Log("Get route. Key: " + key + " - Error: " + std::string(e.what()));
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);
    }
}

void HttpRequestHandler::HandlePost(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept
{
    try
    {
        if (!p_req.has_param("key") || std::empty(p_req.body))
        {
            p_res.status = static_cast<int>(StatusCode::kBadRequest);
            return;
        }

        const auto& key = p_req.get_param_value("key");

        if (p_black_marlin.Exists(key))
        {
            p_res.status = static_cast<int>(StatusCode::kBadRequest);
            return;
        }

        const auto& req_body = p_req.body;

        if (p_req.has_param("expiresin"))
        {
            std::string expires_in_seconds = p_req.get_param_value("expiresin");

            if (!IsValidSecondsParam(expires_in_seconds))
            {
                p_res.status = static_cast<int>(StatusCode::kBadRequest);
                return;
            }

            char* buffer;

            const auto& seconds_to_expire = std::strtol(expires_in_seconds.c_str(), &buffer, 10);

            p_black_marlin.SetToDeleteLater(key, req_body, seconds_to_expire);
        }
        else
        {
            p_black_marlin.Set(key, req_body);
        }

        p_res.status = static_cast<int>(StatusCode::kCreated);
    }
    catch (std::exception& e)
    {
        const auto& key = p_req.get_param_value("key");
        const auto& value = p_req.get_param_value("value");

        this->m_logger.Log("Post route. Key: " + key + " - Value: " + value + " - Error: " + std::string(e.what()));
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);
    }
}

bool HttpRequestHandler::IsValidSecondsParam(const std::string& p_expires_in_seconds_param) noexcept
{
    char* buf;
    const auto seconds = std::strtol(p_expires_in_seconds_param.c_str(), &buf, 10);

    if (seconds <= 0 || seconds > USHRT_MAX)
    {
        return false;
    }

    return true;
}

void HttpRequestHandler::HandlePutAndPatch(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept
{
    try
    {
        if (!p_req.has_param("key") || std::empty(p_req.body))
        {
            p_res.status = static_cast<int>(StatusCode::kBadRequest);
            return;
        }

        const auto& key = p_req.get_param_value("key");

        if (!p_black_marlin.Exists(key))
        {
            p_res.status = static_cast<int>(StatusCode::kBadRequest);
            return;
        }

        const auto& req_body = p_req.body;
        p_black_marlin.Overwrite(key, req_body);
    }
    catch (std::exception& e)
    {
        this->m_logger.Log("Patch and Put route. Error: " + std::string(e.what()));
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);
    }
}

void HttpRequestHandler::HandleDelete(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept
{
    try
    {
        if (!p_req.has_param("key"))
        {
            p_res.status = static_cast<int>(StatusCode::kBadRequest);
            return;
        }

        p_black_marlin.Delete(p_req.get_param_value("key"));
    }
    catch (std::exception& e)
    {
        const auto& key = p_req.get_param_value("key");
        this->m_logger.Log("Delete route. Key: " + key +" - Error: " + e.what());
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);
    }
}

void HttpRequestHandler::HandleDeleteFlush(BlackMarlin& p_black_marlin, httplib::Response& p_res) noexcept
{
    try
    {
        p_black_marlin.Flush();
    }
    catch (std::exception& e)
    {
        this->m_logger.Log("Flush route. Error: " + std::string(e.what()));
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);
    }
}

void HttpRequestHandler::HandleGetExists(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept
{
    try
    {
        if (!p_req.has_param("key"))
        {
            p_res.status = static_cast<int>(StatusCode::kBadRequest);
            return;
        }

        if (!p_black_marlin.Exists(p_req.get_param_value("key")))
        {
            p_res.status = static_cast<int>(StatusCode::kNoContent);
        }
    }
    catch (std::exception& e)
    {
        const auto& key = p_req.get_param_value("key");
        this->m_logger.Log("Exists route. Key: " + key + " - Error: " + std::string(e.what()));
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);
    }
}

void HttpRequestHandler::HandleGetCount(const BlackMarlin& p_black_marlin, httplib::Response& p_res) noexcept
{
    try
    {
        p_res.set_content(std::to_string(p_black_marlin.Count()), this->m_content_type);
    }
    catch (std::exception& e)
    {
        this->m_logger.Log("Count route. Error: " + std::string(e.what()));
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);
    }
}

void HttpRequestHandler::SetResponseHeadersFromConfig(httplib::Response& p_res) noexcept
{
    try
    {
        const auto& configs = this->m_server_configs.GetConfigs();

        for (auto &[header_key, header_value] : configs)
        {
            p_res.set_header(header_key.c_str(), header_value);
        }
    }
    catch (std::exception& e)
    {
        this->m_logger.Log("Error setting custom response headers: " + std::string(e.what()));
    }
}
