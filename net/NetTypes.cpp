#include "NetTypes.hpp"

#ifdef _WIN32
#else
#   include <netdb.h>
#endif

namespace rekwarfare {

protocol PROTOCOL_TCP = SOCK_STREAM;
protocol PROTOCOL_UDP = SOCK_DGRAM;

}
