#include <cstdint>
#include <cstdlib>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>

class easy_tcp{
private: 
    const static int gbacklog = 20; 
public:
    static int easy_socket()
    {
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(socket_fd == -1)
        {
            std::cerr << "socket";
            exit(EXIT_FAILURE);
        }
        int opt = 1;
        setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        return socket_fd;
    }

    static void Bind(int sock, uint16_t port, std::string ip = "0.0.0.0")
    {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &local.sin_addr);
        if(bind(sock, (struct sockaddr*) &local, sizeof(local)) == -1)
        {
            std::cerr << "bind";
            exit(EXIT_FAILURE);
        }
    }

    static void Listen(int sock)
    {
        if(listen(sock, gbacklog) <  0)
        {
            std::cerr << "listen";
            exit(EXIT_FAILURE);
        }
    }

    static int Accept(int listensock, std::string *ip, uint16_t *port)
    {
        struct sockaddr_in src;
        socklen_t len = sizeof(src);
        int servicesock = accept(listensock, (struct sockaddr*) &src, &len);
        if(servicesock == -1)
        {
            std::cerr << "accept";
            exit(EXIT_FAILURE);
        }

        if(port) *port = ntohs(src.sin_port);
        if(ip) *ip = inet_ntoa(src.sin_addr);
        return servicesock;
    }

    static bool Connect(int sock, const std::string &server_ip, const uint16_t &server_port)
    {
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(server_port);
        server.sin_addr.s_addr = inet_addr(server_ip.c_str());
        if(connect(sock, (struct sockaddr*) &server, sizeof(server)) == 0) return true;
        else return false;
    }

    ~easy_tcp(){}
};

