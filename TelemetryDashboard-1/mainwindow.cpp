#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataparser.h"

#include <QXmlStreamWriter>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    xCounter(0)
{
    ui->setupUi(this);

    // =========================
    // CONNECT EXPORT BUTTON
    // =========================
    connect(ui->exportButton, &QPushButton::clicked,
            this, &MainWindow::exportToXML);

    // =========================
    // CREATE CHART
    // =========================
    series = new QLineSeries();

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Live Altitude");

    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Time");
    axisX->setRange(0, 100);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Altitude");
    axisY->setRange(900, 1100);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // =========================
    // LAYOUT
    // =========================
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    layout->addWidget(ui->altitudeLabel);
    layout->addWidget(ui->voltageLabel);
    layout->addWidget(ui->exportButton);
    layout->addWidget(chartView);

    setCentralWidget(central);

    // =========================
    // START SERVER
    // =========================
    server = new TelemetryServer(this);
    server->startServer(5000);

    connect(server, &TelemetryServer::newTelemetryData,
            this, [=](QString rawData)
            {
                auto parsed = DataParser::parse(rawData);

                TelemetryData data;

                if(parsed.contains("ALT"))
                {
                    data.altitude = parsed["ALT"];
                    ui->altitudeLabel->setText("Altitude: " + QString::number(data.altitude));

                    series->append(xCounter++, data.altitude);

                    if(xCounter > 100)
                        axisX->setRange(xCounter - 100, xCounter);
                }

                if(parsed.contains("VOLT"))
                {
                    data.voltage = parsed["VOLT"];
                    ui->voltageLabel->setText("Voltage: " + QString::number(data.voltage));
                }

                if(parsed.contains("LAT"))
                    data.latitude = parsed["LAT"];

                if(parsed.contains("LON"))
                    data.longitude = parsed["LON"];

                // ✅ Store in memory for XML export
                telemetryDataList.append(data);

                // CSV Logging
                logToCSV(rawData);
            });

    // =========================
    // CSV FILE
    // =========================
    logFile.setFileName("telemetry_log.csv");
    logFile.open(QIODevice::Append | QIODevice::Text);
}

MainWindow::~MainWindow()
{
    logFile.close();
    delete ui;
}

// =========================
// CSV LOGGER
// =========================
void MainWindow::logToCSV(const QString &data)
{
    if(logFile.isOpen())
    {
        QTextStream out(&logFile);
        out << data << "\n";
    }
}

// =========================
// XML EXPORT
// =========================
void MainWindow::exportToXML()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Telemetry XML",
        "telemetry.xml",
        "XML Files (*.xml)"
        );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Error", "Unable to create file.");
        return;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("TelemetryData");

    for (const auto &entry : telemetryDataList)
    {
        xml.writeStartElement("DataPoint");

        xml.writeTextElement("Altitude", QString::number(entry.altitude));
        xml.writeTextElement("Voltage", QString::number(entry.voltage));
        xml.writeTextElement("Latitude", QString::number(entry.latitude));
        xml.writeTextElement("Longitude", QString::number(entry.longitude));

        xml.writeEndElement();
    }

    xml.writeEndElement();
    xml.writeEndDocument();

    file.close();

    QMessageBox::information(this, "Success",
                             "Telemetry exported successfully!");
}
