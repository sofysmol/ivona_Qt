#ifndef IVONACLIENT_H
#define IVONACLIENT_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QEventLoop>
#include <QUrlQuery>
#include <QDebug>
#include <QTimer>
#include <QCryptographicHash>
#include <QMessageAuthenticationCode>
#include <QDateTime>
class IvonaClient : public QObject
{
    Q_OBJECT

public:
    explicit IvonaClient(QNetworkAccessManager* manager);

    QString getAudio(QString text,QString lang);
private:
    QNetworkAccessManager* networkManager;
    QByteArray accessKey="GDNAIZWUUS5YZJX7Y6QA";
    QByteArray secretKey="dV6tCuj8KnsuQMGBfeeHKTnKQx4ohKsLCBKlEC6+";
    //QByteArray accessKey="GDNAJZYBNDFMZ6YXIRFQ";
    //QByteArray secretKey="ndnMMljy/BwrvSFuDY8+7qk7EA/ZAII5jxwQc7OV";

    QString region="eu-west-1";
    QString Host="https://tts." + region + ".ivonacloud.com";
    QString CreateSpeech="/CreateSpeech";
    QByteArray Get(QUrl url);

    QUrl getUrl(QString text,QString lang);
    QByteArray CreateSignature(QUrlQuery query,QString xAmzDate,QString date);
    QByteArray CreateStringToSing(QString canonicalRequest,QString xAmzDate,QString date);
    QString CreateCanonicalRequest(QUrlQuery query);
    QByteArray HMAC_SH256(QByteArray key,QByteArray data);
};

#endif
