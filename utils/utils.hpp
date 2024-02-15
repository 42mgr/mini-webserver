#pragma once

#include "../webserver.hpp"
#include <netinet/in.h>

std::string	uint16_to_str(uint16_t n);
int			ft_stoi(std::string const &s);
std::string convertAddress(uint32_t address);
std::tm		*get_time();
void		log(std::string message, std::string component, const char *color);
void		log_error(std::string message);
std::ostringstream ft_inet_ipstr(sockaddr_in address_in);