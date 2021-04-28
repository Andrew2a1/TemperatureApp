#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QDateTime datetime = QDateTime::currentDateTime();
    auto time = datetime.toMSecsSinceEpoch();
    ui->temperatureChart->setStartTime(time);

    updater = new QTimer(this);
    updater->setSingleShot(false);
    updater->setInterval(200);

    connect(updater, &QTimer::timeout,
            this, [=]() {
        const QDateTime datetime = QDateTime::currentDateTime();
        auto time = datetime.toMSecsSinceEpoch();
        ui->temperatureChart->append(time, 40*sin(time/1000.0));
    });

    updater->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

