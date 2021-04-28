#include "TemperatureReader.h"

TemperatureReader::TemperatureReader(QObject *parent) :
    QObject(parent)
{

}

QPair<double, double> TemperatureReader::fetchData()
{
    return qMakePair(0, 0);
}
