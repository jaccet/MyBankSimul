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
    explicit pinUI(QWidget *parent = nullptr, REST_API *rest=nullptr);
    ~pinUI();

private slots:

    void numberClickedHandler();
    void clrEntBckClickedHandler();
    void reEnableOrClose();
    void loginHandler(bool);

signals:
    void loginResultFromPinUI(bool);


private:
    REST_API *apiObject;
    Ui::pinUI *ui;
    QString starCount,number;
    int numOftries = 3;
    void switchFontSize(short);
    void lockHandler();
    bool isCorrect;
};

#endif // PINUI_H
