#pragma once

# define LOG_SPACING "  "
# define LOG_FIELD_WIDTH 10

/* GENERAL */
# include <unistd.h>
# include <cstdlib>
# include <algorithm>
# include <stdint.h>
# include <ctime>

/* CONVERSIONS */
# include <arpa/inet.h>

/* STREAM */
# include <iostream>
# include <sstream>
# include <fstream>
# include <iomanip>

/* STRING */
# include <cstring>

/* SIGNAL */
# include <csignal>

/* STL CONTAINERS */
# include <vector>
# include <map>

/* ERRORS */
# include <exception>
# include <cerrno>

/* COSMETIC */
#include "utils/colors.hpp"
#include "utils/utils.hpp"
#include <stdio.h>
#include <arpa/inet.h>

#include <vector>
#include <map>
#include <deque>
#include <poll.h>