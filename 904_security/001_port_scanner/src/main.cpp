#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <omp.h>

bool scanPort(const char* ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    // Set a short timeout
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 200000; // 200 ms
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    int result = connect(sock, (sockaddr*)&addr, sizeof(addr));
    close(sock);

    return (result == 0);
}

int main() 
{
    const char* targetIP = "127.0.0.1";   // Change to your target IP
    int startPort = 1;
    int endPort = 1024;

    omp_set_num_threads(4);

    std::cout << "Scanning ports on " << targetIP << "...\n";

    #pragma omp parallel
    {

        #pragma omp for schedule(dynamic)
        for (int port = startPort; port <= endPort; ++port) 
        {
            if (scanPort(targetIP, port)) 
            {
                std::cout << omp_get_thread_num() << ":  Port " << port << " is OPEN\n";
            }
        }
    }

    std::cout << "Scan complete.\n";
    return 0;
}


#endif

