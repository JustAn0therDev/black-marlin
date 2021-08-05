#include "../BlackMarlin/black_marlin.hpp"
#include "../Logger/logger.hpp"
#include "../ServerConfigs/server_configs.hpp"
#include "../Util/util.hpp"
#include "../vendor/httplib.h"
#include "http_request_handler.hpp"
#include "status_code.hpp"
#include <string>

HttpRequestHandler::HttpRequestHandler() noexcept
{
    this->m_server_configs.LoadHeadersFromConfigFile();
}

void HttpRequestHandler::HandleGet(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) const noexcept
{
	try
	{
		if (!p_req.has_param("key"))
		{
			p_res.status = static_cast<int>(StatusCode::kBadRequest);
			return;
		}

		const auto& value = p_black_marlin.Get(p_req.get_param_value("key"));

		if (value == nullptr || *value == "")
		{
			p_res.status = static_cast<int>(StatusCode::kNoContent);
			return;
		}

		p_res.set_content(*value, this->m_content_type);
	}
	catch (std::exception& e)
	{
		const auto& key = p_req.get_param_value("key");
		Logger::Log("Get route. Key: " + key + " - Error: " + std::string(e.what()));
		p_res.status = static_cast<int>(StatusCode::kInternalServerError);
	}
}

void HttpRequestHandler::HandlePost(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) noexcept
{
	try
	{
        // Thought that "p_req.body" was a char* but its not.
		if (!p_req.has_param("key") || p_req.body == "")
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

        // Not sure if this works without a pointer when trying to delete the value in the hashtable.
		std::string* req_body_ptr = new std::string(p_req.body);

		if (p_req.has_param("expiresin"))
		{
			std::string expires_in_seconds = p_req.get_param_value("expiresin");

			if (!this->IsValidSecondsParam(expires_in_seconds))
			{
				p_res.status = static_cast<int>(StatusCode::kBadRequest);
				delete req_body_ptr;
				return;
			}

			const auto& seconds_to_expire = std::atoi(expires_in_seconds.c_str());

			p_black_marlin.SetToDeleteLater(key, req_body_ptr, seconds_to_expire);
		}
		else
		{
			p_black_marlin.Set(key, req_body_ptr);
		}

		p_res.status = static_cast<int>(StatusCode::kCreated);
	}
	catch (std::exception& e)
	{
		const auto& key = p_req.get_param_value("key");
		const auto& value = p_req.get_param_value("value");

		Logger::Log("Post route. Key: " + key + " - Value: " + value + " - Error: " + std::string(e.what()));
		p_res.status = static_cast<int>(StatusCode::kInternalServerError);
	}
}

bool HttpRequestHandler::IsValidSecondsParam(std::string p_expires_in_seconds_param) noexcept
{
    const int& seconds = std::atoi(p_expires_in_seconds_param.c_str());

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
		if (!p_req.has_param("key") || p_req.body == "")
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

		std::string* req_body_ptr = new std::string(p_req.body);
		p_black_marlin.Overwrite(key, req_body_ptr);
	}
	catch (std::exception& e)
	{
		Logger::Log("Patch and Put route. Error: " + std::string(e.what()));
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
		Logger::Log("Delete route. Key: " + key +" - Error: " + e.what());
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
		Logger::Log("Flush route. Error: " + std::string(e.what()));
		p_res.status = static_cast<int>(StatusCode::kInternalServerError);
	}
}

void HttpRequestHandler::HandleGetExists(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) const noexcept
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
		Logger::Log("Exists route. Key: " + key + " - Error: " + std::string(e.what()));
		p_res.status = static_cast<int>(StatusCode::kInternalServerError);
	}
}

void HttpRequestHandler::HandleGetCount(const BlackMarlin& p_black_marlin, httplib::Response& p_res) const noexcept
{
	try
	{
		p_res.set_content(std::to_string(p_black_marlin.Count()), this->m_content_type);
	}
	catch (std::exception& e)
	{
		Logger::Log("Count route. Error: " + std::string(e.what()));
		p_res.status = static_cast<int>(StatusCode::kInternalServerError);
	}
}

void HttpRequestHandler::SetResponseHeadersFromConfig(httplib::Response& p_res) const noexcept
{
	try
	{
		const auto& configs = this->m_server_configs.GetConfigs();

		auto it = configs.begin();

		while (it != configs.end())
		{
			p_res.set_header(it->first.c_str(), it->second);
			++it;
		}
	}
	catch (std::exception& e)
	{
		Logger::Log("Error setting custom response headers: " + std::string(e.what()));
	}
}
