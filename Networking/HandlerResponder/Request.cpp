/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:22:53 by tfregni           #+#    #+#             */
/*   Updated: 2024/02/15 22:16:01 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

// Request example:
// GET / HTTP/1.1
// User-Agent: PostmanRuntime/7.32.1
// Accept: */*
// Cache-Control: no-cache
// Postman-Token: 2b5c6319-2359-44d1-b3e1-c12196c0164c
// Host: 192.168.1.19:8080
// Accept-Encoding: gzip, deflate, br
// Connection: keep-alive
// Content-Length: 12
// \r\n
// Hello World! (if body is present a header Content-Length: 12 is also present)

/****************************************************/
/* HELPER FUNCTIONS									*/
/****************************************************/

/**
 * @brief: Parse the method string into a t_method enum
 * @param method: string containing the method
*/
t_method parseMethod(std::string const method) {
	if (method == "GET")
		return GET;
	else if (method == "POST")
		return POST;
	else if (method == "DELETE")
		return DELETE;
	else
		return UNKNOWN;
}

std::string parseMethod(t_method method) {
	if (method == GET)
		return "GET";
	else if (method == POST)
		return "POST";
	else if (method == DELETE)
		return "DELETE";
	else
		return "UNKNOWN";
}

/**
 * @brief: Sanitize the path by adding a leading / if it's missing and removing trailing slashes
 * It truncates the path to MAX_PATH_LENGTH
 * @param iss: istringstream containing the path
*/
static std::string sanitizePath(std::istringstream &iss) {
	std::string uri;
	iss >> uri;
	if (uri[0] != '/')
		uri.insert(0, "/");
	size_t pos = uri.length() - 1;
	while (uri.at(pos) == '/' && pos > 1) {
		uri.erase(pos);
		pos--;
	}
	if (uri.length() > MAX_PATH_LENGTH)
		uri = uri.substr(0, MAX_PATH_LENGTH);
	return uri;
}

/****************************************************/
/* ORTHODOX CANONICAL                               */
/****************************************************/

Request::Request(const char *r):
_method(UNKNOWN), _path(""), _req_status(FAILURE) {
	std::istringstream iss(r);
	std::string attr;
	std::string headers;
	std::getline(iss, attr);
	if (!parseAttributes(attr) ||
		!parseHeaders(iss) ||
		!parseBody(iss)) {
		log_error("Bad request");
	}
	else
		_req_status = SUCCESS;
}

Request::~Request() {}

Request::Request(const Request &copy) {
	*this = copy;
}

Request &Request::operator=(const Request &copy) {
	if (this != &copy) {
		(void) copy;
	}
	return *this;
}


/****************************************************/
/* PUBLIC FUNCTIONS									*/
/****************************************************/

std::string Request::getProtocol() const {
	return (_protocol);
}

std::string Request::getMethod() const {
	return (parseMethod(_method));
}

std::string Request::getPath() const {
	return (_path);
}

std::map<std::string, std::string> Request::getHeaders() const {
	return (_headers);
}

std::string Request::getBody() const {
	return (_body);
}

std::map<std::string, std::string> Request::getQuery() const {
	return (_query);
}

t_req_error Request::getStatus() const {
	return (_req_status);
}

/****************************************************/
/* PRIVATE FUNCTIONS								*/
/****************************************************/

/**
 * @brief: Parse the request attributes
 * - turns the method into a t_method enum
 * - sanitizes the path
 * - parses the query if present
 * - checks the protocol
 * @param attr: string containing the request attributes
*/
bool Request::parseAttributes(std::string const attr) {
	std::istringstream iss(attr);
	std::string method;
	iss >> method;
	_method = parseMethod(method);
	if (_method == UNKNOWN) {
		_req_status = INVALID_METHOD;
		return (false);
	}
	_path = sanitizePath(iss);
	if (_path.find("?", 0) != std::string::npos) {
		// std::cout << "Found query" << std::endl;
		std::string query = _path.substr(_path.find("?", 0) + 1);
		_path = _path.substr(0, _path.find("?", 0));
		if (!parseQuery(query)) {
			_req_status = INVALID_QUERY;
			return (false);
		}
	}
	iss >> _protocol;
	if (iss.fail() || strncmp(_protocol.c_str(), "HTTP/", 5) != 0) {
		_req_status = INVALID_PROTOCOL;
		return false;
	}
	log(_path + " " + _protocol, method, YELLOW);
	return (true);
}

/**
 * @brief: Parse the query string
 * - splits the query into key-value pairs separated by '&'
 * - splits the key-value pairs by '='. A pair ending with = has a value of ""
 * while a pair without = is invalid
 * @param query: string containing the query
*/
bool Request::parseQuery(std::string const query) {
	std::istringstream iss(query);
	std::string pair;
	while (std::getline(iss, pair, '&')) {
		std::string key, value;
		std::istringstream key_value(pair);
		std::getline(key_value, key, '=');
		if (key_value.eof()) { // No equal sign found (Note that Postman strips the = if it's the last char)
			_req_status = INVALID_QUERY;
			return (false);
		}
		key_value >> value;
		_query[key] = value;
		// std::cout << "Query: " << key << " = " << _query[key] << std::endl;
	}
	return (true);
}

/**
 * @brief: Parse the request headers
 * - splits the headers into lines
 * - the \r is consumed by std::getline, so the empty line dividing the headers
 * from the body is consumed is == \r. But if iss.eof() is true, then there was
 * no \r at the end and that's an error
 * - splits the key-value pairs by ':'
*/
bool Request::parseHeaders(std::istringstream &iss) {
	std::string line;
	while (std::getline(iss, line)) {
		// std::cout << "Line: (" << line.length() << " chars): " << line << std::endl;
		if (line == "\r") {
			if (!iss.eof())
			// std::cout << "End of headers" << std::endl;
				break;
			_req_status = INVALID_HEADER;
			return (false); // No \r at the end of the headers
		}
		std::string key, value;
		std::istringstream header(line);
		std::getline(header, key, ':');
		if (header.eof()) { // No column found
			_req_status = INVALID_HEADER;
			return (false);
		}
		header >> value;
		_headers[key] = value;
		// std::cout << key << ": " << value << std::endl;
	}
	return (true);
}

/**
 * @brief: Parse the request body
 * - reads the body until the end of the istringstream
 * - checks that the Content-Length header is present and matches the body length
*/
bool Request::parseBody(std::istringstream &iss) {
	std::getline(iss, _body, '\0'); // Too crafty???
	// std::cout << "Body: " << _body << std::endl;
	/* Checking that Content-Length is set and matches the body length */
	if (_headers.find("Content-Length") != _headers.end()) {
		size_t length = ft_stoi(_headers["Content-Length"]);
		// std::cout << "Content-Length: " << length << std::endl;
		// std::cout << "Body length: " << _body.length() << std::endl;
		if (_body.length() != length) {
			_req_status = INVALID_BODY;
			return (false);
		}
	}
	return (true);
}