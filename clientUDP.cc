#include<cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <unistd.h>
#include<vector>
using namespace std;

#define PORT     8081
#define MAXLINE 1024

class UDP_Client
{
    private:
        int sockfd;
        char *buffer = nullptr;
        socklen_t serverLen;
        int port;
        int maxlenBuf;
        struct sockaddr_in servaddr; 

    public:
        UDP_Client(int port_ = 0, int maxlenBuf_ = 0)
        {            
            this->port = port_;
            this->maxlenBuf = maxlenBuf_;
            this->buffer = new char[maxlenBuf];
            //*this->serverLen = sizeof(this->servaddr);  //len is value/result
            memset(&servaddr, 0, sizeof(this->servaddr));  
        }

        ~UDP_Client()
        {
            cout << "Destruct client" << endl;
            delete[] this->buffer;
            //delete this->serverLen;
            this->buffer = nullptr;
            //this->serverLen = nullptr;
        }


        // Filling server information 
        void fill_SerInfo()
        {
            this->servaddr.sin_family    = AF_INET; // IPv4 
            this->servaddr.sin_addr.s_addr = INADDR_ANY; // This field contains the IP address of the host. For server code, this will always be the IP address of the machine on which the server is running, and there is a symbolic constant INADDR_ANY which gets this address.
            this->servaddr.sin_port = htons(this->port);   
        }
        // Creating socket file descriptor
        void creSocketDescr()
        {
            if ( (this->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
                perror("socket creation failed"); 
                exit(EXIT_FAILURE); 
            }
        }

        // Receive a message from the socket.
        void recvSocket()
        {
            int n; 
            socklen_t len = sizeof(servaddr) ;
            n = recvfrom(this->sockfd, (char *)this->buffer, MAXLINE,  
            MSG_WAITALL, ( struct sockaddr *) &servaddr, &len); 
            buffer[n] = '\0'; 
            cout << "n: " << n << endl;
           
            cout <<  buffer << endl;
        
            
        }
        // Send Messages to client on the socket
        void sendMes(char hello[])
        {
            socklen_t len = sizeof(servaddr);
            sendto(this->sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, len); 
        }
};

int main()
{
    // Trying to access non-existent memory or memory which is being used by other process also causes the Segmentation Fault (core dumped).
    char hello[100] = "hello from client";

    UDP_Client client(8081, 1024);
    client.fill_SerInfo();
    client.creSocketDescr();
    client.sendMes(hello);
    client.recvSocket();
    return 0;
}
// Driver code 
/*int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *temp = new char[100];

    char hello[100] = "hello from client";
    for (int i = 0; i < 100; i++)
    {
        *(temp + i) = hello[i];
    } 
    
    struct sockaddr_in     servaddr; 
    
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
        
    int n;
    socklen_t len = sizeof(servaddr);  
        
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    cout << "Hello message sent.\n"; 
            
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[n] = '\0'; 
    cout << "Server: " << buffer << endl; 
    
    close(sockfd); 
    return 0; 
}*/