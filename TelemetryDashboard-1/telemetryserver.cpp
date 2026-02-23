#include "telemetryserver.h"
#include <QDebug>

TelemetryServer::TelemetryServer(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);
    clientSocket = nullptr;

    connect(server, &QTcpServer::newConnection,
            this, &TelemetryServer::handleNewConnection);
}

void TelemetryServer::startServer(quint16 port)
{
    if(server->listen(QHostAddress::Any, port))
        qDebug() << "Server started on port" << port;
    else
        qDebug() << "Server failed to start";
}

void TelemetryServer::handleNewConnection()
{
    clientSocket = server->nextPendingConnection();
    qDebug() << "Client connected!";

    connect(clientSocket, &QTcpSocket::readyRead,
            this, &TelemetryServer::readData);

    connect(clientSocket, &QTcpSocket::disconnected,
            this, [=]() {
                qDebug() << "Client disconnected";
                clientSocket->deleteLater();
                clientSocket = nullptr;
            });
}

void TelemetryServer::readData()
{
    while(clientSocket && clientSocket->canReadLine())
    {
        QByteArray line = clientSocket->readLine().trimmed();
        emit newTelemetryData(QString(line));
    }
}
