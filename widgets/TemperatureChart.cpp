#include "TemperatureChart.h"

#include <QVBoxLayout>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>

#include <QDateTime>

TemperatureChart::TemperatureChart(QWidget *parent) :
    QWidget(parent),
    chart(new QChart),
    series(new QLineSeries),
    axisX(new QDateTimeAxis),
    axisY(new QValueAxis)
{
    createLayout();
}

void TemperatureChart::append(double time, double temperature)
{
    QDateTime datetime = QDateTime::currentDateTime();
    series->append(datetime.toMSecsSinceEpoch(), temperature);

    if(datetime > axisX->max())
        axisX->setMax(datetime);

    if(temperature > axisY->max())
        axisY->setMax(temperature);
    if(temperature < axisY->min())
        axisY->setMin(temperature);

    chart->setTitle(QString("Current temperature: %1°C").arg(temperature));
}

void TemperatureChart::createLayout()
{
    QChartView *chartView = new QChartView(chart);
    chartView->setMinimumSize(800, 600);
    chart->addSeries(series);

    axisX->setTickCount(1);
    axisX->setRange(QDateTime::currentDateTime(),
                    QDateTime::currentDateTime().addSecs(60));
    axisX->setFormat("HH:mm:ss");
    axisX->setTitleText("Time");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY->setRange(-20, 40);
    axisY->setTitleText("Temperature");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->hide();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);

}
