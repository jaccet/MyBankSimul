#ifndef PINREADER_H
#define PINREADER_H

#include <QDialog>

namespace Ui {
class pinReader;
}

class pinReader : public QDialog
{
    Q_OBJECT

public:
    explicit pinReader(QWidget *parent = nullptr);
    ~pinReader();

private slots:
    void handleClick();

signals:
    void sendPinNumToMain(short);

private:
    Ui::pinReader *ui;
};

#endif // PINREADER_H
