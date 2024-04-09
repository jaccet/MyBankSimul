#include "rest_api.h"

REST_API::REST_API()
{
}

REST_API::~REST_API()
{
}

void REST_API::loginHandler(QString cardnumber, QString pin)
{
    card_no = cardnumber;

    QJsonObject jsonObj;

    jsonObj.insert("card_no",card_no);
    jsonObj.insert("pin_no",pin);

    QString site_url = base_url+"login";
    QNetworkRequest request;
    request.setUrl(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager();
    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(loginEvent(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}



bool REST_API::loginEvent(QNetworkReply *reply)
{
    responseData=reply->readAll();
    //QMessageBox msgBox;
    qDebug()<<responseData;
    if(responseData=="-4078" || responseData.length()==0){
        //msgBox.setText("Virhe tietoyhteydessä");
        //msgBox.exec();

    } else {
        if(responseData!="false"){
            //kirjautuminen onnistui
            webtoken = responseData;
            qDebug()<<responseData;
            ui->pushButton->setEnabled(true);
        }
        else{
            msgBox.setText("Tunnus/salasana ei täsmää");
            msgBox.exec();
            //ui->textUsername->clear();
            //ui->pin_noLine->clear();
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}
