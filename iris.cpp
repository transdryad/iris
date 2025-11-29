#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>

#define PROJECT_NAME "iris"

void error(std::string note) {
    perror(note.c_str());
    exit(1);
}

void isend(int sock, std::string message) {
    message += "\r\n";
    std::cout << "Client - " << message;
    if ((send(sock, message.c_str(), strlen(message.c_str()), 0)) == -1) {
        error("Error while sending \"" + message + "\":");
        exit(1);
    }
}

int main(int argc, char **argv) {
    if (argc != 6) {
        std::cout << argv[0] << " takes four arguments: iris <address> <port> <name> <nickname> <pass>\n";
        return 1;
    }
    std::cout << "This is project " << PROJECT_NAME << ".\n";

    struct addrinfo hints;
    struct addrinfo *servinfo; //set up data
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(argv[1], argv[2], &hints, &servinfo); //get addrinfo into servinfo
    if (status != 0) {
        std::cerr << "Error in getaddrinfo: " << gai_strerror(status) << std::endl;
        return 1;
    }

    int sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (sock == -1) error("Failed getting socket: ");

    //fcntl(sock, F_SETFL, O_NONBLOCK);
    struct pollfd pfds[1];
    pfds[0].fd = sock;
    pfds[0].events = POLLIN;

    if (connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) == -1) error("Error connecting to socket: ");

    std::string pass = "PASS "; pass += argv[5];
    std::string nick = "NICK "; nick += argv[4];
    std::string name = "USER guest 0 * :"; name += argv[3];
    
    //isend(sock, "CAP LS 302"); capabillity negotiation not supported at this time.
    isend(sock, pass);
    isend(sock, nick);
    isend(sock, name);

    char buffer[1024];
    std::vector[char] bytes;
    std::vector[char] message;
    
    while (true) {
        char buffer[1024];
        recv(sock, buffer, 1024, 0);
        std::cout << "Server - " << buffer << std::endl;
    }

    while (true) {
        while (true) {
            recv(sock, buffer, 1024, 0);
            for (int i = 0; i < 1024; i++) {
                bytes.puch_back(buffer[i]);
                buffer[i] = 0;
            }
            if (std::count(bytes.begin(), bytes.end(), "\r") && std::count(bytes.begin(), bytes.end(), "\n")) break;
        }
        for (int i = 0; i < bytes.size(); i++) {
            if (bytes[i] != "\r") {
                message.push_back(bytes[i]);
            } else {
                if (bytes[i + 1] == "\n") break;
            }
        }

    }
    freeaddrinfo(servinfo);

    return 0;
}
