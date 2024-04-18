#include "pankkisivu.h"
#include "ui_pankkisivu.h"

pankkiSivu::pankkiSivu(QWidget *parent, REST_API *rest) :
    QMainWindow(parent),
    ui(new Ui::pankkiSivu)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: lightblue;");
    restPtr=rest;
}

pankkiSivu::~pankkiSivu()
{
    delete ui;
    ui=nullptr;
}
