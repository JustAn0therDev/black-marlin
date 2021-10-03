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

        char* log_message = static_cast<char *>(malloc(sizeof(char) * 200));

        log_message = strcpy(log_message, "Get route. Key: ");

        log_message = strcat(log_message, p_req.get_param_value("key").c_str());

        log_message = strcat(log_message, " - Error: ");

        log_message = strcat(log_message, "New testing OK.");

        this->m_logger.Log(log_message);

        free(log_message);

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

        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Get route. Key: ");

        log_message = strcat(log_message, key.c_str());

        log_message = strcat(log_message, " - Error: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);

        p_res.status = static_cast<int>(StatusCode::kInternalServerError);

        free(log_message);
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

        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Post route. Key: ");

        log_message = strcat(log_message, key.c_str());

        log_message = strcat(log_message, " - Error: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);

        free(log_message);
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
        const auto& key = p_req.get_param_value("key");

        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Patch and Put route. Key: ");

        log_message = strcat(log_message, key.c_str());

        log_message = strcat(log_message, " - Error: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);

        free(log_message);
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

        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Delete route. Key: ");

        log_message = strcat(log_message, key.c_str());

        log_message = strcat(log_message, " - Error: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);

        free(log_message);
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
        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Flush route. Error: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);

        free(log_message);
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

        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Exists route. Key: ");

        log_message = strcat(log_message, key.c_str());

        log_message = strcat(log_message, " - Error: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);
        p_res.status = static_cast<int>(StatusCode::kInternalServerError);

        free(log_message);
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
        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Count route. Error: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);

        p_res.status = static_cast<int>(StatusCode::kInternalServerError);

        free(log_message);
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
        char* log_message = static_cast<char *>(malloc(sizeof(char) * LOG_MESSAGE_SIZE));

        log_message = strcpy(log_message, "Error setting custom response headers: ");

        log_message = strcat(log_message, e.what());

        this->m_logger.Log(log_message);

        free(log_message);
    }
}
