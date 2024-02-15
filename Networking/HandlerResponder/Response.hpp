#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Request.hpp"
# include "../Sockets/ListeningSocket.hpp"
# include "../../webserver.hpp"

# define DEFAULT_ROOT "./www"
# define DEFAULT_INDEX "index.html"

class Response {
	public:
		Response(Request const & src);
		// Response(Socket const &s, Request const &req);
		~Response();
		const std::string createHTTPResponse(void);
		const std::string getText(void) const;
	protected:
	private:
		Response(Response const &src);
		Response(NTW::ListeningSocket const &s, Request const &src);
		Response & operator=(Response const & rhs);
		Request const _request;
		std::string _root;
		std::string _uri;
		std::string _url;
		std::string _path;
		std::string	_method;
		std::string _protocol;
		std::string _text;
		int			_status;
		std::map<int, std::string> _HTTPStatus;
		void initHTTPStatus(void);
		std::string const createHeader(void);
		std::string const createBody(void);
};

#endif