#include "NetTypes.hpp"

#ifdef _WIN32
#	define SOCK_STREAM 0
#	define SOCK_DGRAM 0
#else
#   include <netdb.h>
#endif

namespace rekwarfare {

protocol PROTOCOL_TCP = SOCK_STREAM;
protocol PROTOCOL_UDP = SOCK_DGRAM;

}
