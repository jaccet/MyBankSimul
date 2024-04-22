#include "rest_api.h"

REST_API::REST_API()
{
}

REST_API::~REST_API()
{
}

void REST_API::checkCard(QString cardnumber)
{
    setcard_no(cardnumber);
    qDebug() << card_no;
    QString site_url=base_url+"login/"+card_no;

    QNetworkRequest request(site_url);

    loginManager = new QNetworkAccessManager(this);

    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(cardSlot(QNetworkReply*)));

    reply=loginManager->get(request);
}

void REST_API::requestLogin(QString pin)
{
    QJsonObject jsonObj;
    jsonObj.insert("card_no",getcard_no());
    jsonObj.insert("pin_no",pin);
    qDebug()<<jsonObj;
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
            getAndSetAccountIBAN();
            emit loginSuccessful(true);
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
    QJsonArray json_array = json_doc.array();
    QString transactions = "Tyyppi | Pvm | Määrä\n";
    foreach(const QJsonValue &value,json_array){
        QJsonObject json_obj = value.toObject();
        transactions+=json_obj["type"].toString()+" | ";
        transactions+=json_obj["date"].toString()+" | ";
        transactions+=json_obj["amount"].toString();
        transactions+="\n";
    }
    qDebug()<<json_doc;
    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    }
    else {
        emit transactionInfoReceived(transactions);
    }

    reply->deleteLater();
    infoManager->deleteLater();
}

void REST_API::accountLogisticSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    qDebug()<<responseData;
    QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj;
    foreach(const QJsonValue &value,json_array){
        json_obj = value.toObject();
    }
    QString logistics = "Tilin saldo: "+json_obj["balance"].toString()+"\nTilin korko: "+json_obj["interest"].toString()+"\nLuottoraja: "+json_obj["credit_limit"].toString();
    qDebug()<<logistics;
    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    } else {
        emit accountLogisticsReceived(logistics);
    }
    reply->deleteLater();
    infoManager->deleteLater();
}

void REST_API::withdrawalSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();

    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    } else {
        qDebug()<<responseData;
    }
}

void REST_API::IBANSlot(QNetworkReply *reply)
{
    responseData=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(responseData);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj;
    foreach(const QJsonValue &value,json_array){
        json_obj = value.toObject();
    }
    if(responseData=="-4078" || responseData.length()==0){
        qDebug()<<"Connection Error!";
        emit connectionError();
    } else {
        //qDebug()<<response_data;
        IBAN = json_obj["IBAN_no"].toString();
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

void REST_API::setcard_no(QString cardnumber)
{
    card_no = cardnumber;
}

QString REST_API::getcard_no()
{
    return card_no;
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
    QString site_url=base_url+"account/info/"+card_no;
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

    jsonObj.insert("amount",amount);
    qDebug()<<jsonObj;

    qDebug()<<IBAN;
    QString site_url=base_url+"transaction/withdrawal/"+IBAN;
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

void REST_API::resetAll()
{
    card_no=NULL;
    IBAN=NULL;
    webtoken=NULL;
}
