#ifndef TEMPERATUREREADER_H
#define TEMPERATUREREADER_H

#include <QObject>
#include <QPair>

#include <QtNetwork/QNetworkAccessManager>

class TemperatureReader : public QObject
{
    Q_OBJECT

private:
    bool errorFlag = false;

    QString appid;
    QString location;
    QNetworkAccessManager *manager;

public:
    explicit TemperatureReader(QObject *parent = nullptr);

    void setLocation(const QString &city,
                     const QString &countryCode);
    bool hasError();

signals:
    void dataFetched(const QPair<double, double> &data);

public slots:
    void fetchData();

private:
    void generateAppid();

private slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // TEMPERATUREREADER_H
