#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reader = new TemperatureReader(this);

    updater = new QTimer(this);
    updater->setSingleShot(false);
    updater->setInterval(5000);

    connect(updater, &QTimer::timeout,
            reader, &TemperatureReader::fetchData);

    connect(reader, &TemperatureReader::dataFetched,
            this, &MainWindow::insertNewData);

    reader->fetchData();
    updater->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertNewData(const QPair<double, double> &data)
{
    ui->temperatureChart->append(data.first, data.second);
    qDebug() << data.first << ": " << data.second;
}

