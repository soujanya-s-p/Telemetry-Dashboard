#ifndef TELEMETRYSERVER_H
#define TELEMETRYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class TelemetryServer : public QObject
{
    Q_OBJECT

public:
    explicit TelemetryServer(QObject *parent = nullptr);
    void startServer(quint16 port);

signals:
    void newTelemetryData(QString data);

private slots:
    void handleNewConnection();
    void readData();

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
};

#endif
