/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:26:02 by tfregni           #+#    #+#             */
/*   Updated: 2024/02/09 00:19:36 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"

/**
 * @brief Convert a uint16_t to a string
 * @returns: the string representation of the uint16_t
 * @note: it doesn't return a char * to avoid allocations
*/
std::string uint16_to_str(uint16_t n) {
	std::string res;
	do {
		char digit = '0' + n % 10;
		res.insert(res.begin(), digit);
		n /= 10;
	} while (n > 0);
	return res;
}

/**
 * @brief: Convert a string to an int
*/
int ft_stoi(std::string const &s) {
	int i = 0;
	std::istringstream iss(s);
	iss >> i;
	return i;
}

std::tm *get_time() {
	std::time_t t = std::time(NULL);
	return std::localtime(&t);
}

std::string convertAddress(uint32_t address) {
    std::ostringstream oss;
    oss
        << (address & 0xFF) << '.'
        << ((address >> 8) & 0xFF) << '.'
        << ((address >> 16) & 0xFF) << '.'
		<< ((address >> 24) & 0xFF);
    return oss.str();
}

void log(std::string message, std::string component, const char *color) {
	#ifndef TEST
	char dateTime[22];
	std::strftime(dateTime, sizeof(dateTime), "[%Y-%m-%d %H:%M:%S]", get_time());
	std::cout << color << dateTime << LOG_SPACING
	<< std::left << std::setw(LOG_FIELD_WIDTH) << component << message << RESET << std::endl;
	#else
	(void) message;
	(void) component;
	(void) color;
	#endif
}

void log_error(std::string message) {
	char dateTime[22];
	std::strftime(dateTime, sizeof(dateTime), "[%Y-%m-%d %H:%M:%S]", get_time());
	std::cerr << RED << dateTime << LOG_SPACING
	<< std::left << std::setw(LOG_FIELD_WIDTH) << "ERROR" << message << RESET << std::endl;
}

std::ostringstream ft_inet_ipstr(sockaddr_in address_in) {
    char ipstr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(address_in.sin_addr), ipstr, sizeof(ipstr));
    std::ostringstream oss;
    oss.write(ipstr, 16);
    return oss;
}