#ifndef PINUITEST_H
#define PINUITEST_H


#include <QWidget>

namespace Ui {
class Pinuitest;
}

class Pinuitest : public QWidget
{
    Q_OBJECT

public:
    explicit Pinuitest(QWidget *parent = nullptr);
    ~Pinuitest();

private:
    Ui::Pinuitest *ui;
};

#endif // PINUITEST_H

