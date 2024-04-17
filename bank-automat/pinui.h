#ifndef PINUI_H
#define PINUI_H

#include <QDialog>
#include <QTimer>
#include "rest_api.h"

namespace Ui {
class pinUI;
}

class pinUI : public QDialog
{
    Q_OBJECT

public:
    explicit pinUI(QWidget *parent = nullptr);
    ~pinUI();

private slots:

    void numberClickedHandler();
    void clrEntBckClickedHandler();
    void reEnableOrClose();
    void loginHandler(bool);

signals:
    void sendPinNumToMain(QString);

private:
<<<<<<< HEAD
    //void openSerialPort();
    REST_API *apiObject;
=======
>>>>>>> main
    Ui::pinUI *ui;
    QString starCount,number;
    QString testipinkoodi="6262";
    int numOftries = 3;
    void switchFontSize(short);
    void lockHandler();
    bool isCorrect;
};

#endif // PINUI_H
