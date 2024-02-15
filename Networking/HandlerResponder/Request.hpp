/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:22:56 by tfregni           #+#    #+#             */
/*   Updated: 2024/02/15 22:14:58 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP
# include "../../webserver.hpp"

# define MAX_PATH_LENGTH 2048
typedef enum e_method
{
	GET,
	POST,
	DELETE,
	UNKNOWN,
}			t_method;

typedef enum e_req_error {
	SUCCESS,
	INVALID_METHOD,
	INVALID_PATH,
	INVALID_QUERY,
	INVALID_PROTOCOL,
	INVALID_HEADER,
	INVALID_BODY,
	FAILURE, // generic failure to use as init value
}			t_req_error;

class Request {
	public:
		Request(const char *r);
		Request(const Request &copy);
		~Request();
		Request &operator=(const Request &copy);
		std::string getProtocol() const;
		std::string getMethod() const;
		std::string getPath() const;
		std::map<std::string, std::string> getQuery() const;
		std::map<std::string, std::string> getHeaders() const;
		std::string getBody() const;
		t_req_error getStatus() const;
	protected:
	private:
		bool	parseAttributes(std::string const attr);
		bool	parseQuery(std::string const query);
		bool	parseHeaders(std::istringstream &iss);
		bool	parseBody(std::istringstream &iss);
		std::string							_protocol;
		t_method							_method;
		std::string							_path;
		std::map<std::string, std::string>	_query;
		std::map<std::string, std::string>	_headers;
		std::string							_body;
		t_req_error							_req_status;
};

t_method parseMethod(std::string const method);

#endif