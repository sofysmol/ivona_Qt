#include "ivonaclient.h"

IvonaClient::IvonaClient(QNetworkAccessManager* manager)
{
    networkManager=manager;

}
QByteArray IvonaClient::Get(QUrl url)
{
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = networkManager->get(QNetworkRequest(request));
    QEventLoop wait;
    connect(networkManager,SIGNAL(finished(QNetworkReply*)),&wait,SLOT(quit()));
    QTimer::singleShot(10000,&wait,SLOT(quit()));
    wait.exec();

     //Получаю ответ

    QByteArray answer = (QByteArray)reply->readAll();
    reply->deleteLater();
    return answer;
}

QString IvonaClient::getAudio(QString text,QString lang){
    QUrl url=getUrl(text,lang);
    QByteArray answer=Get(url);
    qDebug()<<QString::fromUtf8(answer);

    return "yy";
}
QUrl IvonaClient::getUrl(QString text,QString lang)
{
    QString xAmzDate=QDateTime::currentDateTimeUtc().toString("yyyyMMddTHHmmssZ");//date+"T"+time+"Z";
    QString date=QDateTime::currentDateTimeUtc().toString("yyyyMMdd");
    QUrl url(Host+CreateSpeech);
    QUrlQuery query;
    query.addQueryItem("Input.Data",QUrl::toPercentEncoding(text));
    query.addQueryItem("Input.Type",QUrl::toPercentEncoding("text/plain"));
    query.addQueryItem("OutputFormat.Codec","MP3");
    query.addQueryItem("OutputFormat.SampleRate","22050");
    query.addQueryItem("Parameters.Rate","slow");
    query.addQueryItem("Voice.Name","Amy");
    query.addQueryItem("Voice.Language",lang);
    query.addQueryItem("X-Amz-Date",xAmzDate);
    query.addQueryItem("X-Amz-Algorithm","AWS4-HMAC-SHA256");
    query.addQueryItem("X-Amz-Credential",QUrl::toPercentEncoding("GDNAIZWUUS5YZJX7Y6QA/"+date+"/"+region+"/tts/aws4_request"));
    query.addQueryItem("X-Amz-SignedHeaders","host");
    QString Signature=CreateSignature(query,xAmzDate, date);
    query.addQueryItem("X-Amz-Signature",Signature);
    url.setQuery(query);
    qDebug()<<url.toString();
    return url;
}

QByteArray IvonaClient::CreateSignature(QUrlQuery query,QString xAmzDate,QString date)
{
    QString caninicalRequest=CreateCanonicalRequest(query);
    QByteArray DateKey=HMAC_SH256("AWS4dV6tCuj8KnsuQMGBfeeHKTnKQx4ohKsLCBKlEC6+",QDate::currentDate().toString("yyyyMMdd").toUtf8());
    QByteArray DateRegionKey =HMAC_SH256(DateKey,"eu-west-1");//region.toUtf8());
    QByteArray DateRegionServiceKey = HMAC_SH256(DateRegionKey,"tts");
    QByteArray SigningKey= HMAC_SH256(DateRegionServiceKey,"aws4_request");
    return HMAC_SH256(SigningKey, CreateStringToSing(caninicalRequest,xAmzDate,date)).toHex();
}
QByteArray IvonaClient::CreateStringToSing(QString canonicalRequest,QString xAmzDate,QString date)
{
  /* qDebug()<<"AWS4-HMAC-SHA256\n"+
             xAmzDate.toUtf8()+"\n"+
             date.toUtf8()+"/"+region.toUtf8()+"/tts/aws4_request\n"+
             QCryptographicHash::hash(canonicalRequest.toUtf8(),QCryptographicHash::Sha256).toHex();*/

    return"AWS4-HMAC-SHA256\n"+
                          xAmzDate.toUtf8()+"\n"+
                          date.toUtf8()+"/"+region.toUtf8()+"/tts/aws4_request\n"+
                          QCryptographicHash::hash(canonicalRequest.toUtf8(),QCryptographicHash::Sha256).toHex();

}
QString IvonaClient::CreateCanonicalRequest(QUrlQuery query)
{
    /*qDebug()<<"Get\n"
              "/CreateSpeech\n"+
              query.toString()+'\n'+
              "host"+Host+'\n'+
              '\n'+
              "host"+
              +"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";*/
    return "Get\n/CreateSpeech\n"+
            query.toString()+'\n'+
            "host"+Host+'\n'+
            '\n'+
            "host"+
            +"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
}

QByteArray IvonaClient::HMAC_SH256(QByteArray key,QByteArray data)
{
    QMessageAuthenticationCode code(QCryptographicHash::Sha256);
    code.setKey(data);
    code.addData(key);
    return code.hash(data,key,QCryptographicHash::Sha256);
}
/*QString tt="POST\n"
        "/CreateSpeech\n"
        "\n"
        "content-type:application/json\n"
        "host:tts.eu-west-1.ivonacloud.com\n"
        "x-amz-content-sha256:f43e25253839f2c3feae433c5e477d79f7dfafdc0e4af19a952adb44a60265ba\n"
        "x-amz-date:20130913T092054Z\n"
        "\n"
        "content-type;host;x-amz-content-sha256;x-amz-date\n"
        "f43e25253839f2c3feae433c5e477d79f7dfafdc0e4af19a952adb44a60265ba";*/
/*QByteArray tt="AWS4-HMAC-SHA256\n"
        "20130913T092054Z\n"
        "20130913/eu-west-1/tts/aws4_request\n"
        "73ff17c0bf9da707afb02bbceb77d359ab945a460b5ac9fff7a0a61cfaab95e6";
//qDebug()<<tt;
QByteArray DateKey = HMAC_SH256("AWS467890", "20130913");
QByteArray DateRegionKey = HMAC_SH256(DateKey, "eu-west-1");
QByteArray DateRegionServiceKey = HMAC_SH256(DateRegionKey, "tts");
QByteArray SigningKey = HMAC_SH256(DateRegionServiceKey, "aws4_request");
QByteArray Signature = HMAC_SH256(SigningKey, tt);
qDebug()<<Signature.toHex();*/
