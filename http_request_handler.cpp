#include "http_request_handler.hpp"
#include "httplib.h"
#include "black_marlin.hpp"
#include "status_codes.hpp"

void HttpRequestHandler::HandleGet(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) {
	std::string value;

	if (p_req.has_param("key")) {
		value = p_blackMarlin->Get(p_req.get_param_value("key"));

		if (std::empty(value)) {
			p_res.status = (int)StatusCodes::kNoContent;
		}
	}
	else {
		p_res.status = (int)StatusCodes::kBadRequest;
	}

	p_res.set_content(value, "*/*");
}

void HttpRequestHandler::HandlePost(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (p_req.has_param("key")) {
		std::string key = p_req.get_param_value("key");
		std::string* body = new std::string(p_req.body);
		std::string& keyRef = key;

		p_blackMarlin->Set(keyRef, body);

		p_res.status = (int)StatusCodes::kCreated;
	}
	else {
		p_res.status = (int)StatusCodes::kBadRequest;
	}

	p_res.set_content("", "*/*");
}

void HttpRequestHandler::HandlePutAndPatch(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (p_req.has_param("key")) {
		std::string key = p_req.get_param_value("key");
		std::string* body = new std::string(p_req.body);
		std::string& keyRef = key;

		p_blackMarlin->Set(keyRef, body);

		p_res.status = (int)StatusCodes::kCreated;
	}
	else {
		p_res.status = (int)StatusCodes::kBadRequest;
	}

	p_res.set_content("", "*/*");
}

void HttpRequestHandler::HandleDelete(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (p_req.has_param("key")) {
		std::string& keyRef = p_req.get_param_value("key");

		p_blackMarlin->Delete(keyRef);
	}
	else {
		p_res.status = (int)StatusCodes::kBadRequest;
	}

	p_res.set_content("", "*/*");
}

void HttpRequestHandler::HandleDeleteFlush(BlackMarlin*& p_blackMarlin, httplib::Response& p_res) {
	p_blackMarlin->Flush();
	p_res.status = (int)StatusCodes::kNoContent;
	p_res.set_content("", "*/*");
}

void HttpRequestHandler::HandleGetExists(BlackMarlin*& p_blackMarlin, const httplib::Request& p_req, httplib::Response& p_res) {
	if (p_req.has_param("key")) {
		std::string& keyRef = p_req.get_param_value("key");

		bool exists = p_blackMarlin->Exists(keyRef);

		if (!exists) {
			p_res.status = (int)StatusCodes::kNoContent;
		}
	}
	else {
		p_res.status = (int)StatusCodes::kBadRequest;
	}

	p_res.set_content("", "*/*");
}

void HttpRequestHandler::HandleGetCount(BlackMarlin*& p_blackMarlin, httplib::Response& p_res) {
	p_res.set_content(std::to_string(p_blackMarlin->Count()), "*/*");
}
