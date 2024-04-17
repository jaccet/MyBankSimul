#ifndef REST_API_H
#define REST_API_H

#include "REST_API_global.h"
#include <QtNetwork/QtNetwork>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>

class REST_API_EXPORT REST_API : public QObject
{
    Q_OBJECT
public:
    REST_API();
    ~REST_API();
    void checkCard(QString cardnumber);
    void requestLogin(QString pin);
    void setCard_no(const QString &newCard_no);
    void getTransactions();
    void getAccountLogistics();
    void withdrawalOperation(double amount);
public slots:
private slots:
    void cardSlot(QNetworkReply *reply);
    void loginSlot(QNetworkReply *reply);
    void transactionSlot(QNetworkReply *reply);
    void accountLogisticSlot(QNetworkReply *reply);
    void withdrawalSlot(QNetworkReply *reply);
    void IBANSlot(QNetworkReply *reply);
signals:
    void connectionError();
    bool cardChecked(bool);
    void loginSuccessful(bool);
    QJsonObject transactionInfoReceived(QJsonObject);
    QJsonObject accountLogisticsReceived(QJsonObject);
private:
    QString base_url="http://localhost:3000/";
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *infoManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString card_no;
    QString IBAN;
    QByteArray webtoken;
    double balance;

    void getAndSetAccountIBAN();
};

#endif // REST_API_H
