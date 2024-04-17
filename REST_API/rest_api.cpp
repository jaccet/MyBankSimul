#include "rest_api.h"

REST_API::REST_API()
{
}

REST_API::~REST_API()
{
}

void REST_API::checkCard(QString cardnumber)
{
    setCard_no(cardnumber);
    qDebug() << "käydään täällä?";
    QString site_url=base_url+"login/"+card_no;

    QNetworkRequest request(site_url);

    loginManager = new QNetworkAccessManager(this);

    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(cardSlot(QNetworkReply*)));

    reply=loginManager->get(request);
}

void REST_API::requestLogin(QString pin)
{
    QJsonObject jsonObj;
    jsonObj.insert("card_no",card_no);
    jsonObj.insert("pin_no",pin);

    QString site_url=base_url+"login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void REST_API::cardSlot(QNetworkReply *reply)
{
    qDebug() << "card slotissa käydään.";
    responseData = reply->readAll();
    qDebug()<<responseData;
    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    } else {
        if (responseData == "false") {
            emit cardChecked(false);
        } else if (responseData.length()>5) {
            emit cardChecked(false);
        } else {
            emit cardChecked(true);
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

void REST_API::loginSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    qDebug() << "in Login";

    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit loginSuccessful(false);
    }
    else{
        if(responseData!="false"){
            //kirjautuminen onnistui
            webtoken=responseData;
            emit loginSuccessful(true);
            getAndSetAccountIBAN();
        }
        else{
            qDebug()<<"Wrong Card or Pin";
            emit loginSuccessful(false);
        }
    }

    reply->deleteLater();
    loginManager->deleteLater();
}

void REST_API::transactionSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    //qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
    QJsonObject json_obj = json_doc.object();
    qDebug()<<json_obj;
    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    }
    else {
        emit transactionInfoReceived(json_obj);
    }

    reply->deleteLater();
    infoManager->deleteLater();
}

void REST_API::accountLogisticSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    //qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
    QJsonObject json_obj = json_doc.object();
    qDebug()<<json_obj;
    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    } else {
        balance = json_obj["balance"].toDouble();
        emit accountLogisticsReceived(json_obj);
    }
    reply->deleteLater();
    infoManager->deleteLater();
}

void REST_API::withdrawalSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();

    qDebug()<<responseData;
}

void REST_API::IBANSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    } else {
        //qDebug()<<response_data;
        IBAN = responseData;
    }
    reply->deleteLater();
    infoManager->deleteLater();
}

void REST_API::getAndSetAccountIBAN()
{
    QString site_url=base_url+"card/IBAN/"+card_no;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray requestToken="Bearer "+webtoken;
    request.setRawHeader(QByteArray("Authorization"),(requestToken));
    //WEBTOKEN LOPPU
    infoManager = new QNetworkAccessManager(this);

    connect(infoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(IBANSlot(QNetworkReply*)));

    reply = infoManager->get(request);
}

void REST_API::setCard_no(const QString &newCard_no)
{
    card_no = newCard_no;
}

void REST_API::getTransactions()
{
    QString site_url=base_url+"transaction/"+card_no;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray requestToken="Bearer "+webtoken;
    request.setRawHeader(QByteArray("Authorization"),(requestToken));
    //WEBTOKEN LOPPU
    infoManager = new QNetworkAccessManager(this);

    connect(infoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transactionSlot(QNetworkReply*)));

    reply = infoManager->get(request);
}

void REST_API::getAccountLogistics()
{
    QString site_url=base_url+"account/"+card_no;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray requestToken="Bearer "+webtoken;
    request.setRawHeader(QByteArray("Authorization"),(requestToken));
    //WEBTOKEN LOPPU
    infoManager = new QNetworkAccessManager(this);

    connect(infoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(accountLogisticSlot(QNetworkReply*)));

    reply = infoManager->get(request);
}

void REST_API::withdrawalOperation(double amount)
{
    QJsonObject jsonObj;

    jsonObj.insert("IBAN_no",IBAN);
    jsonObj.insert("amount",amount);

    QString site_url=base_url+"transaction/withdrawal";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //WEBTOKEN ALKU
    QByteArray requestToken="Bearer "+webtoken;
    request.setRawHeader(QByteArray("Authorization"),(requestToken));
    //WEBTOKEN LOPPU
    infoManager = new QNetworkAccessManager(this);

    connect(infoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawalSlot(QNetworkReply*)));

    reply = infoManager->post(request,QJsonDocument(jsonObj).toJson());
}
