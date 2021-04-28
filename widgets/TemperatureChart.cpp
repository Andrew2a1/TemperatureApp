#include "TemperatureChart.h"

#include <QVBoxLayout>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

TemperatureChart::TemperatureChart(QWidget *parent) :
    QWidget(parent),
    chart(new QChart),
    series(new QLineSeries),
    axisX(new QValueAxis),
    axisY(new QValueAxis)
{
    createLayout();
}

void TemperatureChart::append(double time, double temperature)
{
    series->append(time, temperature);

    if(time > axisX->max())
        axisX->setMax(time);
    if(temperature > axisY->max())
        axisY->setMax(temperature);
}

void TemperatureChart::setStartTime(double time)
{
    axisX->setMin(time);
}

void TemperatureChart::createLayout()
{
    QChartView *chartView = new QChartView(chart);
    chartView->setMinimumSize(800, 600);
    chart->addSeries(series);

    axisX->setRange(0, 100);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Time");

    axisY->setRange(-80, 80);
    axisY->setTitleText("Temperature");

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->hide();
    chart->setTitle("Temperature in Warsaw");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);

}
