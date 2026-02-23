#include <QCoreApplication>
#include <QTcpSocket>
#include <QThread>
#include <QRandomGenerator>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 5000);

    if (!socket.waitForConnected(3000))
    {
        qDebug() << "Connection failed!";
        return -1;
    }

    qDebug() << "Connected to Telemetry Dashboard!";

    double altitude = 1000.0;
    double voltage = 12.5;
    double latitude = 12.9716;
    double longitude = 77.5946;

    while (true)
    {
        // Simulate realistic variation
        altitude += (QRandomGenerator::global()->bounded(10.0) - 5.0);
        voltage += (QRandomGenerator::global()->bounded(0.1) - 0.05);
        latitude += (QRandomGenerator::global()->bounded(0.0002) - 0.0001);
        longitude += (QRandomGenerator::global()->bounded(0.0002) - 0.0001);
        QString data = QString("ALT:%1,VOLT:%2,LAT:%3,LON:%4")
                           .arg(altitude, 0, 'f', 2)
                           .arg(voltage, 0, 'f', 2)
                           .arg(latitude, 0, 'f', 6)
                           .arg(longitude, 0, 'f', 6);

        socket.write((data + "\n").toUtf8());
        socket.flush();

        qDebug() << "Sent:" << data;

        QThread::sleep(1);
    }

    return a.exec();
}
