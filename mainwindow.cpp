#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete i;
    i = nullptr;
}

void MainWindow::on_pushButton_clicked()
{
/*    if (*this->i % 2 == 0)
    {
        ui->label->setText("Hello world: " + QString::number(*this->i));
        *this->i += 1;
    }
    else
    {
        ui->label->setText("Text label" + QString::number(*this->i));
        *this->i += 1;
    }
*/
    int sockfd;
    char buffer[MAXLINE];
    char *hello = new char('s');
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
    //std::string s(1024, buffer);
    ui->label->setText(buffer);

    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &_cliaddr,
            len);
    //cout <<"Hello message sent.\n";
}

void MainWindow::serverUDP(int sockfd)
{
    char buffer[MAXLINE];
    char *hello = new char('s');
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
    //std::string s(1024, buffer);
    ui->label->setText(buffer);

    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &_cliaddr,
            len);
    //cout <<"Hello message sent.\n";

}
