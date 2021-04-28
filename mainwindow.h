#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPair>

#include "TemperatureReader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QTimer *updater;

    TemperatureReader *reader;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void insertNewData(const QPair<double, double> &data);
    void updateLocation();
    void updateRefreshTime();

};

#endif // MAINWINDOW_H
