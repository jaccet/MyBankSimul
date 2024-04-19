#include "pankkisivu.h"
#include "ui_pankkisivu.h"

pankkiSivu::pankkiSivu(QWidget *parent, REST_API *rest) :
    QMainWindow(parent),
    ui(new Ui::pankkiSivu)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    this->setStyleSheet("background-color: lightblue;");
    restPtr=rest;
}

pankkiSivu::~pankkiSivu()
{
    qDebug() << "pankkisivu tuhottu";
    emit testSignal();
    delete ui;
    ui=nullptr;
}
