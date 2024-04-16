#include "pinui.h"
#include "ui_pinui.h"

pinUI::pinUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinUI)
{
    ui->setupUi(this);
    QList<QPushButton*> list = {ui->button1,ui->button2,ui->button3,ui->button4,ui->button5,ui->button6,ui->button7,ui->button8,ui->button9,ui->button0};
    QList<QPushButton*> list2 = {ui->buttonClr,ui->buttonEnter,ui->buttonBck};
    this->setAttribute(Qt::WA_DeleteOnClose);
    for(QPushButton *button:list)
    {
        connect(button,SIGNAL(clicked()),this,SLOT(numberClickedHandler()));
    }
    for(QPushButton *button:list2)
    {
        connect(button,SIGNAL(clicked()),this,SLOT(clrEntBckClickedHandler()));
    }
}

pinUI::~pinUI()
{
    delete ui;
    ui=nullptr;
}

void pinUI::numberClickedHandler()
{
    switchFontSize(24);
    if(number.size()<4)
    {
        QPushButton *button = qobject_cast<QPushButton*>(sender());
        qDebug() << button->objectName();
        number+=button->objectName().at(6);
        qDebug() << "number : " << number << Qt::endl;
        starCount+="* ";
        ui->infoScreen->setText(starCount);
    }
}

void pinUI::clrEntBckClickedHandler()
{
    QPushButton *button2 = qobject_cast<QPushButton*>(sender());

    if(button2->objectName() == "buttonClr" && number!="")
    {
        qDebug() << button2->objectName();
        number=NULL;
        starCount=NULL;
        ui->infoScreen->setText("");
    }

    if(button2->objectName() == "buttonBck" && number!="")
    {
        qDebug() << button2->objectName();
        number.chop(1);
        starCount.chop(2);
        qDebug() << "number : " << number << Qt::endl;
        ui->infoScreen->setText(starCount);
    }

    if(button2->objectName() == "buttonEnter")
    {
        //TÄHÄN SIGNAALI
        emit sendPinNumToMain(number);
        if(number != testipinkoodi){
            qDebug() << "mönkään meni";
            switchFontSize(10);
            numOftries--;
            ui->infoScreen->setText(tr("Wrong PIN. Try again.\n Tries left : %1").arg(numOftries));
            number=NULL;
            starCount=NULL;
            lockHandler();
        }
        else if(number == testipinkoodi){
            qDebug() << "oikein?";
            isCorrect = true;
            ui->infoScreen->setText("Correct!");
            lockHandler();
            QTimer::singleShot(5000, this, SLOT(reEnableOrClose()));
        }
    }
}


void pinUI::lockHandler()
{
    QList<QPushButton*> list = {ui->button1,ui->button2,ui->button3,ui->button4,ui->button5,ui->button6,ui->button7,ui->button8,ui->button9,ui->button0,ui->buttonClr,ui->buttonEnter,ui->buttonBck};

    if(numOftries == 0)
    {
        switchFontSize(10);
        ui->infoScreen->setText("Out of tries, account locked");
        for(QPushButton *button:list)
        {
        button->setEnabled(false);
        }
        QTimer::singleShot(5000, this, SLOT(reEnableOrClose()));
    }
    if(isCorrect == true)
    {
        for(QPushButton *button:list)
        {
        button->setEnabled(false);
        }
    }
}

void pinUI::reEnableOrClose()
{
    QList<QPushButton*> list = {ui->button1,ui->button2,ui->button3,ui->button4,ui->button5,ui->button6,ui->button7,ui->button8,ui->button9,ui->button0,ui->buttonClr,ui->buttonEnter,ui->buttonBck};
    if(isCorrect == true)
    {
        this->close();
    }
    else
    {
        for(QPushButton *button:list)
        {
        button->setEnabled(true);
        }
        ui->infoScreen->setText("");
        numOftries=3;
    }
}

void pinUI::switchFontSize(short fontSize)
{
    QFont font;
    font.setPointSize(fontSize);
    ui->infoScreen->setFont(font);
}

