#ifndef TEMPERATUREREADER_H
#define TEMPERATUREREADER_H

#include <QObject>
#include <QPair>

class TemperatureReader : public QObject
{
    Q_OBJECT

public:
    explicit TemperatureReader(QObject *parent = nullptr);

    QPair<double, double> fetchData();
};

#endif // TEMPERATUREREADER_H
