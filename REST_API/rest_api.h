#ifndef REST_API_H
#define REST_API_H

#include "REST_API_global.h"
#include <QtNetwork/QtNetwork>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QJsonDocument>
//#include <QMessageBox>

class REST_API_EXPORT REST_API : public QObject
{
    Q_OBJECT
public:
    REST_API();
    ~REST_API();
    void checkCard(QString cardnumber);
    void checkTransaction(QString transaction);
    void checkAccount(QString account);
    void checkUser(QString user);
public slots:
    void cardSlot(QNetworkReply *reply);
    void transactionSlot(QNetworkReply *reply);
    void accountSlot(QNetworkReply *reply);
    void userSlot(QNetworkReply *reply);
private slots:

signals:
    bool cardChecked(bool);
    bool transactionChecked(bool);
    bool accountChecked(bool);
    bool userChecked(bool);
private:
    QString base_url="http://localhost:3000/";
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *transactionManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString card_no;
    QString idtransaction;
    QString IBAN_no;
    QString username;
    QByteArray webtoken;
};

#endif // REST_API_H
