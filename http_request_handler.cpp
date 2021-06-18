#include "http_request_handler.hpp"
#include "httplib.h"
#include "black_marlin.hpp"
#include "status_codes.hpp"

void HttpRequestHandler::HandleGet(BlackMarlin*& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	std::string value;

	if (!p_req.has_param("key")) {
		p_res.status = (int)StatusCodes::kBadRequest;
		return;
	}

	value = p_black_marlin->Get(p_req.get_param_value("key"));

	if (std::empty(value)) {
		p_res.status = (int)StatusCodes::kNoContent;
		return;
	}

	p_res.set_content(value, this->m_content_type);
}

void HttpRequestHandler::HandlePost(BlackMarlin*& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (!p_req.has_param("key") || p_req.body == "") {
		p_res.status = (int)StatusCodes::kBadRequest;
		return;
	}

	std::string* req_body_ptr = new std::string(p_req.body);
	p_black_marlin->Set(p_req.get_param_value("key"), req_body_ptr);
	p_res.status = (int)StatusCodes::kCreated;
}

void HttpRequestHandler::HandlePutAndPatch(BlackMarlin*& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (!p_req.has_param("key") || p_req.body == "") {
		p_res.status = (int)StatusCodes::kBadRequest;
		return;
	}

	std::string key = p_req.get_param_value("key");
	std::string* body = new std::string(p_req.body);
	std::string& keyRef = key;

	if (!p_black_marlin->Exists(keyRef)) {
		p_res.status = (int)StatusCodes::kBadRequest;
		return;
	}

	p_black_marlin->Overwrite(keyRef, body);

	p_res.set_content("", this->m_content_type);
}

void HttpRequestHandler::HandleDelete(BlackMarlin*& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (!p_req.has_param("key")) {
		p_res.status = (int)StatusCodes::kBadRequest;
		return;
	}

	p_black_marlin->Delete(p_req.get_param_value("key"));
}

void HttpRequestHandler::HandleDeleteFlush(BlackMarlin*& p_black_marlin, httplib::Response& p_res) {
	p_black_marlin->Flush();
	p_res.status = (int)StatusCodes::kNoContent;
}

void HttpRequestHandler::HandleGetExists(BlackMarlin*& p_black_marlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (!p_req.has_param("key")) {
		p_res.status = (int)StatusCodes::kBadRequest;
		return;
	}

	if (!p_black_marlin->Exists(p_req.get_param_value("key"))) {
		p_res.status = (int)StatusCodes::kNoContent;
	}
}

void HttpRequestHandler::HandleGetCount(BlackMarlin*& p_black_marlin, httplib::Response& p_res) {
	p_res.set_content(std::to_string(p_black_marlin->Count()), this->m_content_type);
}
