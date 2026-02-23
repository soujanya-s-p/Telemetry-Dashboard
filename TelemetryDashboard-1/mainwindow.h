#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include "telemetryserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void exportToXML();   // Slot for export button

private:
    Ui::MainWindow *ui;
    TelemetryServer *server;

    // ===== Telemetry Structure =====
    struct TelemetryData
    {
        double altitude = 0;
        double voltage = 0;
        double latitude = 0;
        double longitude = 0;
    };

    QVector<TelemetryData> telemetryDataList;  // ✅ ONLY here

    // ===== Chart Components =====
    QChart *chart;
    QLineSeries *series;
    int xCounter;

    // ===== CSV Logging =====
    QFile logFile;
    void logToCSV(const QString &data);
};

#endif // MAINWINDOW_H
