#include "pinuitest.h"
#include "ui_pinuitest.h"
#include "mainwindow.h"



Pinuitest::Pinuitest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pinuitest)
{
    ui->setupUi(this);
}

Pinuitest::~Pinuitest()
{
    delete ui;
}

