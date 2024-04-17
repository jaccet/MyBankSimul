#include "pinui.h"
#include "ui_pinui.h"


pinUI::pinUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    apiObject = new REST_API;
    //apiObject->setCard_no("1111222233334444");
    qDebug() << "rest_api olio luotu";
    QList<QPushButton*> list = {ui->button1,ui->button2,ui->button3,ui->button4,ui->button5,ui->button6,ui->button7,ui->button8,ui->button9,ui->button0};
    QList<QPushButton*> list2 = {ui->buttonClr,ui->buttonEnter,ui->buttonBck};
    qDebug() << "pinUI käynnistetty";
    for(QPushButton *button:list)
    {
        connect(button,SIGNAL(clicked()),this,SLOT(numberClickedHandler()));
    }
    for(QPushButton *button:list2)
    {
        connect(button,SIGNAL(clicked()),this,SLOT(clrEntBckClickedHandler()));
    }
    qDebug() << "QListit jokaiselle napille luotu";
    connect(apiObject,SIGNAL(loginSuccessful(bool)),this,SLOT(loginHandler(bool)));
    qDebug() << "rest_api kytketty";
}

pinUI::~pinUI()
{
    qDebug() << "pinUI, sekä rest_api olio tuhottu";
    delete ui;
    delete apiObject;
    apiObject=nullptr;
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
        qDebug() << "syötetty PIN-luku : " << number << Qt::endl;
        starCount+="* ";
        qDebug() << "numeroita lisätty PIN-lukuun, lähetetään tähtiä näytölle";
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
        qDebug() << "clearia painettu, ja numero on nollattu";
        ui->infoScreen->setText("");
    }

    if(button2->objectName() == "buttonBck" && number!="")
    {
        qDebug() << button2->objectName();
        qDebug() << "vähennetään luvusta yksi numero";
        number.chop(1);
        starCount.chop(2);
        qDebug() << "numero : " << number << Qt::endl;
        ui->infoScreen->setText(starCount);
    }

    if(button2->objectName() == "buttonEnter")
    {
        //TÄHÄN SIGNAALI
        //emit sendPinNumToMain(number);
        qDebug() << "enteriä painettu";
        apiObject->requestLogin(number);
        qDebug() << "rest_apia kutsuttu";
    }
}

void pinUI::loginHandler(bool logResult)
{
    if(logResult == false){
        qDebug() << "mönkään meni";
        switchFontSize(10);
        numOftries--;
        ui->infoScreen->setText(tr("Incorrect PIN number.\n Tries left : %1").arg(numOftries));
        number=NULL;
        starCount=NULL;
        qDebug() << "numero nollattu";
        lockHandler();
    }
    else if(logResult == true)
    {
        qDebug() << "PIN-koodi on oikea";
        switchFontSize(10);
        isCorrect = true;
        ui->infoScreen->setText("Correct PIN number. Logging in...");
        lockHandler();
        QTimer::singleShot(2500, this, SLOT(reEnableOrClose()));

    }
    logResult = NULL;
}


void pinUI::lockHandler()
{
    QList<QPushButton*> list = {ui->button1,ui->button2,ui->button3,ui->button4,ui->button5,ui->button6,ui->button7,ui->button8,ui->button9,ui->button0,ui->buttonClr,ui->buttonEnter,ui->buttonBck};

    if(numOftries == 0)
    {
        qDebug() << "yritykset nollassa";
        switchFontSize(10);
        ui->infoScreen->setText("Out of tries, please wait and try again.");
        for(QPushButton *button:list)
        {
        button->setEnabled(false);
        }
        qDebug() << "napit disabloitu";
        QTimer::singleShot(10000, this, SLOT(reEnableOrClose()));
        emit loginResultFromPinUI(false);
    }
    if(isCorrect == true)
    {
        for(QPushButton *button:list)
        {
        button->setEnabled(false);
        }
        qDebug() << "käyttäjän PIN-koodi syötettiin oikein. napit disabloitu.";
        emit loginResultFromPinUI(true);
    }
}

void pinUI::reEnableOrClose()
{
    QList<QPushButton*> list = {ui->button1,ui->button2,ui->button3,ui->button4,ui->button5,ui->button6,ui->button7,ui->button8,ui->button9,ui->button0,ui->buttonClr,ui->buttonEnter,ui->buttonBck};
    if(isCorrect == true)
    {
        this->close();
        qDebug() << "pinUI-ikkuna suljettu";
    }
    else
    {
        for(QPushButton *button:list)
        {
        button->setEnabled(true);
        }
        ui->infoScreen->setText("");
        numOftries=3;
        qDebug() << "yritykset, sekä näyttö resetoitu nollaan. napit enabloitu takaisin käytettäväksi.";
    }
}

void pinUI::switchFontSize(short fontSize)
{
    QFont font;
    font.setPointSize(fontSize);
    ui->infoScreen->setFont(font);
    qDebug() << "fonttia muutettu";
}

