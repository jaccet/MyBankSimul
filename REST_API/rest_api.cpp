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

