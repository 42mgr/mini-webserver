#include "Response.hpp"

// Response::Response(Socket const &s, Request const &req) {
// 	/* TODO add root to socket */
// }

Response::Response(Request const &req):
_request(req),
_root(DEFAULT_ROOT),
_uri(req.getPath()),
_url("http:/" + req.getPath()),
_method(req.getMethod()),
_protocol(req.getProtocol()),
_status(-1) {
	initHTTPStatus();
	// std::cout << "Response:: protocol: " << req.getProtocol() << std::endl;
	if (req.getStatus() != SUCCESS) {
		_status = 400;
		return;
	}
	if (_uri == "/")
		_uri.append(DEFAULT_INDEX);
	_path = _root + _uri;
	// std::cout << "Response::_uri: " << _uri << std::endl;
	std::ifstream file(_path.c_str());
	if (file.is_open()) {
		_status = 200;
		while (file) {
			std::string line;
			std::getline(file, line);
			_text.append(line);
		}
		file.close();
	}
	else {
		_status = 404;
		log_error("Could not open the file");
	}
	std::cout << "_uri: " << _uri << std::endl;
	std::cout << "_url: " << _url << std::endl;
	std::cout << "_path: " << _path << std::endl;
	std::cout << "_status: " << _status << std::endl;
	std::cout << "_text: " << _text << std::endl;
}

Response::~Response() {
}

Response::Response(Response const &src):
_request(src._request) {
	*this = src;
}

Response &Response::operator=(Response const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const std::string Response::getText(void) const {
	return _text;
}

const std::string Response::createHeader(void) {
	std::ostringstream oss;
	if (_HTTPStatus.find(_status) == _HTTPStatus.end()) {
		_status = 500;
	}
	oss <<  _protocol << " " << _status << " " << _HTTPStatus[_status] << "\r\n";
	if (_status == 200) {
		oss << "Content-Length: " << _text.length() << "\r\n";
		oss << "Content-Type: text/html\r\n";
		oss << "\r\n";
	}
	oss << _text + "\r\n";
	return (oss.str());
}

const std::string Response::createHTTPResponse(void) {
	std::string header = createHeader();
	std::string body = "";
	std::cout << "Response::createHTTPResponse: " << std::endl << header << body << std::endl;
	return (header + body);
}

void Response::initHTTPStatus(void) {
	_HTTPStatus[200] = "OK";
	_HTTPStatus[400] = "Bad Request";
	_HTTPStatus[404] = "Not Found";
	_HTTPStatus[500] = "Internal Server Error";
}