#include "Server.hpp"

#include "Client.hpp"
#include "NetTypes.hpp"

#include <string>
#include <algorithm>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <iostream>

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

#define MAX_LISTEN_CONNECTIONS 5

namespace rekwarfare {

Server::Server(ServerConfiguration sconfig)
    : m_sconfig(sconfig), m_name(sconfig.name), m_port(sconfig.port),
    m_protocol(sconfig.prot), m_timeout_time(sconfig.timeout),
    m_buffer_limit(sconfig.buffer_limit) {
    std::cout << ("Initializing server...\nGetting address info...");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    if (m_protocol == PROTOCOL_TCP)
        hints.ai_socktype = PROTOCOL_TCP;
    else
        hints.ai_socktype = PROTOCOL_UDP;

    struct addrinfo* serverinfo = nullptr;
    int gaistatus = getaddrinfo("localhost", m_port.c_str(), &hints,
        &serverinfo);
    if (gaistatus != 0) {
        std::cout << "getaddrinfo(): " << gai_strerror(gaistatus) << std::endl;
        return;
    }

//  std::cout << "Server to run on: " << serverinfo->ai_canonname) << std::endl;

    std::cout << "Initializing socket..." << std::endl;
    m_socket = socket(serverinfo->ai_family, serverinfo->ai_socktype,
        serverinfo->ai_protocol);
    if (m_socket == -1) {
        std::cout << "socket(): " << strerror(errno) << std::endl;
    }

    int trueval = 1;
    setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &trueval, sizeof(int));

    std::cout << "Binding to port " << m_port << std::endl;
    int bindstatus = bind(m_socket, serverinfo->ai_addr,
        serverinfo->ai_addrlen);
    if (bindstatus == -1) {
        std::cout << "Error: bind(): " << strerror(errno) << std::endl;
    }

    std::cout << "Listening on port " << m_port << std::endl;
    int listenstatus = listen(m_socket, MAX_LISTEN_CONNECTIONS);
    if (listenstatus == -1) {
        std::cout << "Error: listen(): " << strerror(errno) << std::endl;
    }

    freeaddrinfo(serverinfo);

}

Server::~Server() {
    destroy();
}

void Server::run(int (* loop)(RecievedData)) {
    m_timeout.tv_sec = m_sconfig.timeout;
    m_timeout.tv_usec = m_sconfig.mstimeout;
    std::cout << "Server now running!" << std::endl;
    int status = 0;
    RecievedData recieved;

    // Setup for select()
    int max_sockets = 0;
    FD_ZERO(&m_masterset);
    for (auto set : m_operationdsc)
        FD_ZERO(&set);
    // Add the listening socket
    FD_SET(m_socket, &m_masterset);
    m_clients.push_back(new Client(m_socket));

    while (status == 0) {

        m_operationdsc[0] = m_masterset;

        // Find max socket ID
        std::vector<socketdsc> sockets;
        for (auto c : m_clients)
            sockets.push_back(c->socket);
        max_sockets = *std::max_element(sockets.data(), sockets.data() +
            sockets.size());

        if (select(max_sockets + 1, &m_operationdsc[0],
            &m_operationdsc[1], &m_operationdsc[2], &m_timeout) == -1
            /*&& errno != EBADF*/) {
            std::cout << "Error: select(): " << strerror(errno) << std::endl;
        } else {
            // reset
            recieved.message = "";
            recieved.sender = nullptr;
            recieved.from_stdin = false;

            for (auto dsc : m_clients) {
                if (FD_ISSET(m_socket, &m_operationdsc[0])) { // incoming
                    if (dsc->socket == m_socket) {
                        acceptConnections(max_sockets);
                    }
                } else if (FD_ISSET(0, &m_operationdsc[0])) {
                    char* get = nullptr;
                    std::fgets(get, 60, stdin);
                    recieved.message = std::string(get);
                    recieved.from_stdin = true;
                    delete get;
                } else { // client
                    recieved.message = getRecievedData(dsc->socket);
                    for (auto s : m_clients)
                        if (s->socket == dsc->socket)
                            recieved.sender = s;
                }
            }
        }
        status = loop(recieved);
    }
}

void Server::destroy(std::string em) {
    std::cout << "Closing server..." << std::endl;
    m_clients.empty();
    close(m_socket);
}

void Server::acceptConnections(int& max_socket_id) {
    struct sockaddr_storage incomingaddress;

    socklen_t length = sizeof(incomingaddress);
    // status = their socket descriptor
    socketdsc status = accept(m_socket, (struct sockaddr*)&incomingaddress,
        &length);
    if (status == -1 && (errno != EAGAIN || errno != EWOULDBLOCK)) {
        std::cout << "Error: accept(): {}" << strerror(errno) << std::endl;
    } else if (errno != EAGAIN || errno != EWOULDBLOCK){
        m_clients.push_back(new Client(status));
        FD_SET(m_clients.back()->socket, &m_masterset);

        std::cout << "A player has joined." << std::endl;
    }
}

std::string Server::getRecievedData(socketdsc s) {
    for (auto i = CLIENT_BEGIN_POS; i < m_clients.size(); i++) {
        auto c = m_clients[i];
        if (c->socket == s) {
            std::string data;
            char* raw_data = static_cast<char*>(malloc(m_buffer_limit));
            int res = recv(c->socket, raw_data, m_buffer_limit, 0);
            data = raw_data;
            delete[] raw_data;
            if (res <= 0) {
                FD_CLR(c->socket, &m_masterset);
                m_clients.erase(m_clients.begin() + i);
                std::cout << "A player has left." << std::endl;
            } else {
                return data;
            }
        }
    }
    return "";
}

}
