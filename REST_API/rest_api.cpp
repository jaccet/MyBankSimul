#include "rest_api.h"

REST_API::REST_API()
{
}

REST_API::~REST_API()
{
}

void REST_API::checkCard(QString cardnumber)
{
    card_no=cardnumber;

    QString site_url=base_url+"login/"+card_no;

    QNetworkRequest request(site_url);

    loginManager = new QNetworkAccessManager(this);

    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(cardSlot(QNetworkReply*)));

    reply=loginManager->get(request);
}

void REST_API::cardSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();

    if (responseData == "false") {
        emit cardChecked(false);
    } else {
        emit cardChecked(true);
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

/////////////////////////////////////////////

void REST_API::checkTransaction(QString transaction)
{
    idtransaction=transaction;

    QString site_url=base_url+"login/"+idtransaction;

    QNetworkRequest request(site_url);

    loginManager = new QNetworkAccessManager(this);

    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(transactionSlot(QNetworkReply*)));

    reply=loginManager->get(request);
}

void REST_API::transactionSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();

    if (responseData == "false") {
        emit transactionChecked(false);
    } else {
        emit transactionChecked(true);
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

//////////////////////////////////////////

void REST_API::checkAccount(QString account)
{
    IBAN_no=account;

    QString site_url=base_url+"login/"+IBAN_no;

    QNetworkRequest request(site_url);

    loginManager = new QNetworkAccessManager(this);

    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(accountSlot(QNetworkReply*)));

    reply=loginManager->get(request);
}

void REST_API::accountSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();

    if (responseData == "false") {
        emit accountChecked(false);
    } else {
        emit accountChecked(true);
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

//////////////////////////////////////////

void REST_API::checkUser(QString user)
{
    username=user;

    QString site_url=base_url+"login/"+username;

    QNetworkRequest request(site_url);

    loginManager = new QNetworkAccessManager(this);

    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(userSlot(QNetworkReply*)));

    reply=loginManager->get(request);
}

void REST_API::userSlot(QNetworkReply *reply)
{
    responseData = reply->readAll();

    if (responseData == "false") {
        emit userChecked(false);
    } else {
        emit userChecked(true);
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

