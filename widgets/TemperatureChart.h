#ifndef TEMPERATURECHART_H
#define TEMPERATURECHART_H

#include <QWidget>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
class QValueAxis;
class QDateTimeAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class TemperatureChart : public QWidget
{
    Q_OBJECT

private:
    QChart *chart;
    QLineSeries *series;

    QDateTimeAxis *axisX;
    QValueAxis *axisY;

public:
    explicit TemperatureChart(QWidget *parent = nullptr);
    void append(double time, double temperature);

private:
    void createLayout();
};

#endif // TEMPERATURECHART_H
