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

signals:
    void PINFromPinUI(QString);


private:
    Ui::pinUI *ui;
    QString starCount,number;
    void switchFontSize(short);
};

#endif // PINUI_H
