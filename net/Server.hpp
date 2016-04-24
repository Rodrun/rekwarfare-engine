#pragma once

#include "Client.hpp"
#include "NetTypes.hpp"

#include <string>
#include <vector>

#include <sys/time.h>
#include <netdb.h>

namespace rekwarfare {

/*
* The position of the first actual client in m_clients
*  0 is reserved for the server's listening socket.
*/
const size_t CLIENT_BEGIN_POS = 1;

typedef struct {
    std::string name;
    std::string port;
    unsigned int maxplayers;
    protocol prot = PROTOCOL_TCP;
    int timeout; // in seconds
    int mstimeout; // microseconds
    int buffer_limit;
} ServerConfiguration;

/*
* Structure that holds data from a specific client. This
*  allows you to  do RecievedData.sender->message(...) to
*  reply to the sender of the message.
* Data is from stdin if from_stdin = true & sender = nullptr.
*/
typedef struct {
    std::string message;
    Client* sender = nullptr;
    bool from_stdin = false;
} RecievedData;

class Server {
public:
    Server(ServerConfiguration);
    /*
    * Equivalent to destroy()
    */
    ~Server();
    /*
    * Run the server in a loop, taking care of
    *  listening for connections and recieving
    *  input, so you can handle what to do with
    *  the input.
    *
    * int (* loop)(RecievedData&):
    *  RecievedData - recieved input; see the struct's doc.
    *  Should return 0 if no errors occur, returning
    *  any other integer will stop the server.
    */
    void run(int (* loop)(RecievedData));
    /*
    * Close the server with an optional exit message to
    *  connected clients.
    */
    void destroy(std::string em="Server closing");
    std::string getName() const { return m_name; }

private:
    void acceptConnections(int& max_socket_id);
    /*
    * Recieve data from a specific socket.
    * returns: Data from the socket
    */
    std::string getRecievedData(socketdsc);

    ServerConfiguration m_sconfig;
    std::string m_name;
    std::string m_port;
    protocol m_protocol;
    int m_timeout_time;
    int m_buffer_limit;
    socketdsc m_socket;
    fd_set m_masterset;
    // Descriptors for read/writing/exception operations
    fd_set m_operationdsc[3];
    struct timeval m_timeout;
    std::vector<Client*> m_clients;
};

}
