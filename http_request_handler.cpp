#include <string>
#include "util.hpp"
#include "httplib.h"
#include "status_code.hpp"
#include "black_marlin.hpp"
#include "http_request_handler.hpp"
#include "server_configs.hpp"

HttpRequestHandler::HttpRequestHandler()
{
	this->m_server_configs = ServerConfigs();
	this->m_server_configs.LoadHeadersFromConfigFile();
}

void HttpRequestHandler::HandleGet(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) const
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

void HttpRequestHandler::HandlePost(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res)
{
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

		const auto& seconds_to_expire = Util::TryCastStringToUnsignedShortInt(expires_in_seconds);

		p_black_marlin.SetToDeleteLater(key, req_body_ptr, seconds_to_expire);
	}
	else
	{
		p_black_marlin.Set(key, req_body_ptr);
	}

	p_res.status = static_cast<int>(StatusCode::kCreated);
}

bool HttpRequestHandler::IsValidSecondsParam(std::string p_expires_in_seconds_param)
{
	const int& seconds = Util::TryCastStringToInt(p_expires_in_seconds_param);

	if (seconds <= 0 || seconds > USHRT_MAX)
	{
		return false;
	}

	return true;
}

void HttpRequestHandler::HandlePutAndPatch(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res)
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

void HttpRequestHandler::HandleDelete(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res)
{
	if (!p_req.has_param("key")) {
		p_res.status = static_cast<int>(StatusCode::kBadRequest);
		return;
	}

	p_black_marlin.Delete(p_req.get_param_value("key"));
}

void HttpRequestHandler::HandleDeleteFlush(BlackMarlin& p_black_marlin, httplib::Response& p_res)
{
	p_black_marlin.Flush();
}

void HttpRequestHandler::HandleGetExists(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) const
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

void HttpRequestHandler::HandleGetCount(const BlackMarlin& p_black_marlin, httplib::Response& p_res) const
{
	p_res.set_content(std::to_string(p_black_marlin.Count()), this->m_content_type);
}

void HttpRequestHandler::SetResponseHeadersFromConfig(httplib::Response& p_res) const
{
	const auto& configs = this->m_server_configs.GetConfigs();

	auto it = configs.begin();

	while (it != configs.end())
	{
		p_res.set_header(it->first.c_str(), it->second);
		++it;
	}
}
