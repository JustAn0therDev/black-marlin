#include <string>
#include "util.hpp"
#include "httplib.h"
#include "status_code.hpp"
#include "black_marlin.hpp"
#include "http_request_handler.hpp"

void HttpRequestHandler::HandleGet(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) const {
	if (!p_req.has_param("key")) {
		p_res.status = (int)StatusCode::kBadRequest;
		return;
	}

	auto value = p_black_marlin.Get(p_req.get_param_value("key"));

	if (value == nullptr || std::empty(*value)) {
		p_res.status = (int)StatusCode::kNoContent;
		return;
	}

	p_res.set_content(*value, this->m_content_type);
}

void HttpRequestHandler::HandlePost(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (!p_req.has_param("key") || p_req.body == "") {
		p_res.status = (int)StatusCode::kBadRequest;
		return;
	}

	const auto& key = p_req.get_param_value("key");

	if (p_black_marlin.Exists(key)) {
		p_res.status = (int)StatusCode::kBadRequest;
		return;
	}

    std::string* req_body_ptr = new std::string(p_req.body);

	if (p_req.has_param("s")) {
		const int seconds = Util::TryConvertStringToInt(p_req.get_param_value("s"));

		if (seconds == 0) {
			p_res.status = (int)StatusCode::kBadRequest;
			delete req_body_ptr;
			return;
		}

		p_black_marlin.SetWithTimer(key, req_body_ptr, seconds);
	} 
	else {
		p_black_marlin.Set(key, req_body_ptr);
	}

    p_res.status = (int)StatusCode::kCreated;
}

void HttpRequestHandler::HandlePutAndPatch(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (!p_req.has_param("key") || p_req.body == "") {
		p_res.status = (int)StatusCode::kBadRequest;
		return;
	}

	const auto& key = p_req.get_param_value("key");

	if (!p_black_marlin.Exists(key)) {
		p_res.status = (int)StatusCode::kBadRequest;
		return;
	}

    std::string* req_body_ptr = new std::string(p_req.body);
    p_black_marlin.Overwrite(key, req_body_ptr);
}

void HttpRequestHandler::HandleDelete(BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (!p_req.has_param("key")) {
		p_res.status = (int)StatusCode::kBadRequest;
		return;
	}

	p_black_marlin.Delete(p_req.get_param_value("key"));
}

void HttpRequestHandler::HandleDeleteFlush(BlackMarlin& p_black_marlin, httplib::Response& p_res) {
	p_black_marlin.Flush();
}

void HttpRequestHandler::HandleGetExists(const BlackMarlin& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) const {
	if (!p_req.has_param("key")) {
		p_res.status = (int)StatusCode::kBadRequest;
		return;
	}

	if (!p_black_marlin.Exists(p_req.get_param_value("key"))) {
		p_res.status = (int)StatusCode::kNoContent;
	}
}

void HttpRequestHandler::HandleGetCount(const BlackMarlin& p_black_marlin, httplib::Response& p_res) const {
	p_res.set_content(std::to_string(p_black_marlin.Count()), this->m_content_type);
}
