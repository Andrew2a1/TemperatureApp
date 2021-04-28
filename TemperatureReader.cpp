#include "TemperatureReader.h"

#include <QtDebug>

#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include <QJsonObject>
#include <QJsonDocument>

TemperatureReader::TemperatureReader(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &TemperatureReader::replyFinished);

    setLocation("Warsaw", "PL");
}

void TemperatureReader::setLocation(const QString &city,
                                    const QString &countryCode)
{
    location = city + "," + countryCode;
}

void TemperatureReader::fetchData()
{
    static const QString API_KEY = "cb3a858cf02abad104a63ccac04c31b6";
    const QString urlString = "http://api.openweathermap.org/data/"
                              "2.5/weather?q=%1&"
                              "appid=%2";

    QUrl url(urlString.arg(location, API_KEY));
    manager->get(QNetworkRequest(url));
}

bool TemperatureReader::hasError()
{
    return errorFlag;
}

void TemperatureReader::replyFinished(QNetworkReply *reply)
{
    QJsonDocument jsonReply = QJsonDocument::fromJson(reply->readAll());
    QJsonObject rootObject = jsonReply.object();
    QJsonObject mainInfo = rootObject["main"].toObject();

    int code = rootObject["cod"].toInt();

    if(code != 200)
        errorFlag = true;
    else
        errorFlag = false;

    double time = rootObject["dt"].toDouble();
    double temp = mainInfo["temp"].toDouble() - 273.0;

    emit dataFetched(qMakePair(time, temp));
}
