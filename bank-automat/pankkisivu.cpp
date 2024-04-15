#include "pankkisivu.h"
#include "ui_pankkisivu.h"

pankkiSivu::pankkiSivu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pankkiSivu)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: lightblue;");
}

pankkiSivu::~pankkiSivu()
{
    delete ui;
}
