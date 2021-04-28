#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <QDoubleSpinBox>

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

    connect(ui->cityName, &QLineEdit::editingFinished,
            this, &MainWindow::updateLocation);

    connect(ui->countryCode, &QLineEdit::editingFinished,
            this, &MainWindow::updateLocation);

    connect(ui->refreshTime, &QDoubleSpinBox::editingFinished,
            this, &MainWindow::updateRefreshTime);

    reader->fetchData();
    updater->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertNewData(const QPair<double, double> &data)
{
    if(!reader->hasError()) {
        ui->temperatureChart->append(data.first, data.second);
        ui->errorLabel->setText("");
    }
    else {
        ui->errorLabel->setText("Error! Invalid parameters.");
    }
}

void MainWindow::updateLocation()
{
    reader->setLocation(ui->cityName->text(), ui->countryCode->text());
}

void MainWindow::updateRefreshTime()
{
    updater->setInterval(ui->refreshTime->value() * 1000);
}

