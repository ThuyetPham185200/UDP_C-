#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
//#include <unistd.h>
using namespace std;

#define PORT     8081
#define MAXLINE 1024
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int *i = new int{0};


private slots:
    void on_pushButton_clicked();
    void serverUDP(int sockfd);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
