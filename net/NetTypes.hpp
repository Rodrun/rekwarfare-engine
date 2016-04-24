#pragma once

#ifdef _WIN32
#else
#   include <netdb.h>
#endif

/*
* Basic networking constants and typedefs
*/
namespace rekwarfare {

typedef int socketdsc;
typedef int protocol;

extern protocol PROTOCOL_TCP;
extern protocol PROTOCOL_UDP;

}
