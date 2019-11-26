#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class Server: public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);
    bool start();
    ~Server();

public slots:
    void newConnection();
    void disconnection();
    void readFromClient();

private:
    QTcpServer *tcpServer = nullptr;
    QTcpSocket *socket = nullptr;
};

#endif // SERVER_H
