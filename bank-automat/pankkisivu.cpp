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
    qDebug() << "rest_api luotu pankkisivulle";
    QList<QPushButton*> list3 = {ui->TAKAISIN_BT,ui->LOPETA_BT};
    QList<QPushButton*> list4 = {ui->OTTO_BT,ui->TALLETUS_BT,ui->TILITAPAHTUMAT_BT,ui->SALDO_BT};

    for(QPushButton *button:list3)
    {
        connect(button,SIGNAL(clicked()),this,SLOT(takaisinJaLopetaHandler()));
    }
    for(QPushButton *button:list4){
        connect(button,SIGNAL(clicked()),this,SLOT(tiliHallintaHandler()));
    }
    qDebug() << "Qlistit luotu pankkisivun painikkeille.";
}

pankkiSivu::~pankkiSivu()
{
    qDebug() << "pankkisivu tuhottu";
    emit testSignal();
    delete ui;
    ui=nullptr;
}

void pankkiSivu::takaisinJaLopetaHandler()
{
    QPushButton *bButton1 = qobject_cast<QPushButton*>(sender());

    if (bButton1->objectName() == "TAKAISIN_BT"){

        qDebug() << bButton1->objectName();
        qDebug() << "Takaisin painallus pankkisivulla.";
    }

    if (bButton1->objectName() == "LOPETA_BT"){
        qDebug() << bButton1->objectName();
        qDebug() << "Lopetus painiketta painettu, suljetaan pankkisivu";
        this->close();
    }
}

void pankkiSivu::tiliHallintaHandler()
{
    QPushButton *bButton2 = qobject_cast<QPushButton*>(sender());

    //Lisää loput tarvittavat.
    if(bButton2->objectName() == "OTTO_BT"){
        qDebug() << bButton2->objectName();
    }
    if(bButton2->objectName() == "TALLETUS_BT"){
        qDebug() << bButton2->objectName();
    }
    if(bButton2->objectName() == "TILITAPAHTUMAT_BT"){
        qDebug() << bButton2->objectName();
    }
    if(bButton2->objectName() == "SALDO_BT"){
        qDebug() << bButton2->objectName();
    }


}
