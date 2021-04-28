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
    generateAppid();
}

void TemperatureReader::setLocation(const QString &city,
                                    const QString &countryCode)
{
    location = city + "," + countryCode;
}

void TemperatureReader::fetchData()
{
    const QString urlString = "http://api.openweathermap.org/data/"
                              "2.5/weather?q=%1&"
                              "appid=%2";

    QUrl url(urlString.arg(location, appid));
    manager->get(QNetworkRequest(url));
}

void TemperatureReader::generateAppid()
{
    QString id = "9K7X\\OFWJJ";
    appid = "Z)\x04""9dz~4,z\x0b*U98~vc+|\n(T9?\x7fr4y{[}";

    for(int i = 0; i < appid.size(); ++i)
        appid[i] = appid[i].toLatin1() ^
                    id[i % id.size()].toLatin1();
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
