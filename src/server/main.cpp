#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;         // IPV4
    serverAddr.sin_port = htons(1234);       // Port: 1234
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Address: 127.0.0.1

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Error listening for connections" << std::endl;
        close(serverSocket);
        return -1;
    }

    sockaddr_in clientAddr;
    socklen_t client_len = sizeof(clientAddr);
    while (true)
    {
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &client_len);
        if (clientSocket == -1)
        {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }
        else
        {
            std::cout << "Connection accepted" << std::endl;
            break;
        }
    }

    close(serverSocket);
    return 0;
}
