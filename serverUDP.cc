#include<cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
using namespace std;

#define PORT     8081
#define MAXLINE 1024

class UDP_Server
{
    private:
        int sockfd;
        char *buffer = nullptr;
        int port;
        int maxlenBuf;
        socklen_t clientLen; 
        struct sockaddr_in servaddr, cliaddr; 

    public:
        UDP_Server(int port_ = 0, int maxlenBuf_ = 0)
        {
            cout << "constructor \n";
            this->port = port_;
            this->maxlenBuf = maxlenBuf_;
            buffer = new char[this->maxlenBuf];
            this->clientLen = sizeof(this->cliaddr);  //len is value/result
            memset(&servaddr, 0, sizeof(this->servaddr)); 
            memset(&cliaddr, 0, sizeof(this->cliaddr)); 
        }

        ~UDP_Server()
        {
            cout << "Destruct server" << endl;
            delete[] this->buffer;
            //delete this->clientLen;
            this->buffer = nullptr;
            //this->clientLen = nullptr;
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
        // Bind the socket with the server address 
        void bindSocket()
        {
            if ( bind(this->sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
            { 
                perror("bind failsed"); 
                exit(EXIT_FAILURE); 
            } 
        }
        // Receive a message from the socket.
        char recvSocket()
        {
            int n; 
            //socklen_t len = sizeof(this->cliaddr);
            n = recvfrom(this->sockfd, (char *)this->buffer, this->maxlenBuf,  
            MSG_WAITALL, ( struct sockaddr *) &cliaddr, &clientLen); 
            buffer[n] = '\0';
            cout << "n: " << n << endl;
            cout << buffer << endl;

        }
        /*string recvSocket()
        {
            int n, i; 
            string s = "";
            //socklen_t len = sizeof(this->cliaddr);
            n = recvfrom(this->sockfd, (char *)this->buffer, this->maxlenBuf,  
            MSG_WAITALL, ( struct sockaddr *) &cliaddr, &clientLen); 
            buffer[n] = '\0';
            //cout << buffer << endl;
            for (i = 0; i < n; i++) {
                s = s + buffer[i];
            }
            cout << s << typeid(s).name() << endl;
            return s;
            //cout << "n: " << n << endl;
        }*/
        
        // Send Messages to client on the socket
        void sendMes(char hello[])
        {
            //socklen_t len = sizeof(this->cliaddr);
            sendto(this->sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, clientLen); 
        }
};

int main()
{
    // Trying to access non-existent memory or memory which is being used by other process also causes the Segmentation Fault (core dumped).
    char hello[100] = "hello from server";
    char *demo = new char[20];
    demo = hello;
    cout << demo << endl;
    
    UDP_Server server(8081, 1024);
    server.fill_SerInfo();
    server.creSocketDescr();
    //server.fill_SerInfo();
    server.bindSocket();
    server.recvSocket();
    server.sendMes(hello);
   
    return 0;
}


// Driver code 
/*int main() { 
    //sockfd and newsockfd are file descriptors, i.e. array subscripts into the file descriptor table . 
    //These two variables store the values returned by the socket system call and the accept system call. 
    //A file descriptor is a number that uniquely identifies an open file in a computer's operating system. 
    //It describes a data resource, and how that resource may be accessed.
    int sockfd; 

    char buffer[MAXLINE]; 
    char hello[100] = "hello from server";
    struct sockaddr_in _servaddr, _cliaddr; 


    // Creating socket file descriptor. if the fuction is fails, it displays a message about the error on stderr and then aborts the program. 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    memset(&_servaddr, 0, sizeof(_servaddr)); 
    memset(&_cliaddr, 0, sizeof(_cliaddr)); 
        
    // Filling server information 
    _servaddr.sin_family    = AF_INET; // IPv4 
    _servaddr.sin_addr.s_addr = INADDR_ANY; // This field contains the IP address of the host. For server code, this will always be the IP address of the machine on which the server is running, and there is a symbolic constant INADDR_ANY which gets this address.
    _servaddr.sin_port = htons(PORT); 
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&_servaddr,  
            sizeof(_servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
        
    int  n; 
    
    socklen_t len = sizeof(_cliaddr);  //len is value/result 
    
    // Receive a message from the socket.
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &_cliaddr, 
                &len); 

    buffer[n] = '\0'; 

    cout << "Client:" << buffer << endl; 

    sendto(sockfd, (const char *)hello, strlen(hello),  
        MSG_CONFIRM, (const struct sockaddr *) &_cliaddr, 
            len); 
    cout <<"Hello message sent.\n";  
    
    return 0; 
}*/