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
    void checkCard(QString);
private slots:

signals:

private:
    QString base_url="http://localhost:3000/";
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *transactionManager;
    QNetworkReply *reply;
    QByteArray responseData;
    QString card_no;
    QByteArray webtoken;
};

#endif // REST_API_H
