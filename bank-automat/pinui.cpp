#include "pinui.h"
#include "ui_pinui.h"


pinUI::pinUI(QWidget *parent,REST_API *rest) :
    QDialog(parent),
    ui(new Ui::pinUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    apiObject = rest;
    qDebug() << "rest_api olio luotu";
    QList<QPushButton*> list = {ui->button1,ui->button2,ui->button3,ui->button4,ui->button5,ui->button6,ui->button7,ui->button8,ui->button9,ui->button0};
    QList<QPushButton*> list2 = {ui->buttonClr,ui->buttonEnter,ui->buttonBck}; // QListit jokaiselle PinUI:n napille, jotta jokaiselle napille ei tarvitse tehdä omaa handleria.
    qDebug() << "pinUI käynnistetty";
    for(QPushButton *button:list) // Yhdistetään napit niiden handlereille yksi kerrallaan for-loopin avulla, QListejä käyttäen.
    {
        connect(button,SIGNAL(clicked()),this,SLOT(numberClickedHandler()));
    }
    for(QPushButton *button:list2)
    {
        connect(button,SIGNAL(clicked()),this,SLOT(clrEntBckClickedHandler()));
    }
    qDebug() << "QListit jokaiselle napille luotu";
    connect(apiObject,SIGNAL(loginSuccessful(bool)),this,SLOT(loginHandler(bool))); // Kytketään PinUI REST API:in.
    qDebug() << "rest_api kytketty";
}

pinUI::~pinUI()
{
    emit loginResultFromPinUI(false);
    qDebug() << "pinUI, sekä rest_api olio tuhottu";
    delete ui;
    ui=nullptr;
}

void pinUI::numberClickedHandler() // Jokaisen luvun napin toiminto.
{
    switchFontSize(24);
    if(number.size()<4) // QString-tyyppinen muuttuja number vastaa PIN-luvun ylläpitämisestä. If-lausekkeella varmistetaan tässä se,
    {                   // että number-muuttujan stringin pituus ei voi mennä neljää suuremmaksi.
        QPushButton *button = qobject_cast<QPushButton*>(sender());
        qDebug() << button->objectName();
        number+=button->objectName().at(6); // Tallennetaan number-lukuun käyttäjän syöttämä PIN-luku. objectName().at(6) ottaa jokaisen napin nimen viimeisen kirjaimen, joka on tässä tapauksessa luku.
        qDebug() << "syötetty PIN-luku : " << number << Qt::endl;   // Esim. objectName = button5. "5" on kuudes "kirjain" nappiobjektin nimessä, joten tämän perusteella luku 5 lisätään number-muuttujaan.
        starCount+="* "; // Luvun lisäyksen jälkeen starCount-nimiseen QStringiin lisätään tähti, joka lopulta siirtyy PinUI:n ruudulle, jotta käyttäjän syöttämä luku pysyy salaisena.
        qDebug() << "numeroita lisätty PIN-lukuun, lähetetään tähtiä näytölle";
        ui->infoScreen->setText(starCount); // Tässä lisätään lopulta tähti ruudulle.
    }
}

void pinUI::clrEntBckClickedHandler() // Luvun muuttamisen, ja Enterin toiminnot.
{
    QPushButton *button2 = qobject_cast<QPushButton*>(sender());

    if(button2->objectName() == "buttonClr" && number!="")
    {
        qDebug() << button2->objectName();
        number=NULL;
        starCount=NULL;
        qDebug() << "clearia painettu, ja numero on nollattu";
        ui->infoScreen->setText(""); // Käyttäjä voi nollata numeron tällä napilla. number, sekä starCount nollaantuvat, ja pinUI:n ruutu tyhjenee. Numeroa ei voi nollata, jos numeroa ei ole.
    }

    if(button2->objectName() == "buttonBck" && number!="")
    {
        qDebug() << button2->objectName();
        qDebug() << "vähennetään luvusta yksi numero"; // Tekee juurikin näin, ja tässäkään ei voi toimintoa suorittaa jos numeroa ei vielä ole.
        number.chop(1); // Otetaan number-muuttujasta yksi "kirjain" pois.
        starCount.chop(2); // Otetaan tässä starCount-muuttujasta kaksi "kirjainta" pois, sillä yksi lisäys starCountiin tuo *-tähden lisäksi myös välilyönnin, joka menee kahdesta kirjaimesta.
        qDebug() << "numero : " << number << Qt::endl;
        ui->infoScreen->setText(starCount); // Päivitetään vielä ruutu.
    }

    if(button2->objectName() == "buttonEnter")
    {
        qDebug() << "enteriä painettu";
        apiObject->requestLogin(number); // Käyttäjän painaessa enteriä kutsutaan REST API:n requestLogin-funktiota number-muuttujan avulla, joka lähetetään REST API:in verrattavaksi.
        qDebug() << "rest_apia kutsuttu"; // Tämä johtaa myös loginHandler-funktioon, joka on alempana.
    }
}

void pinUI::loginHandler(bool logResult) // Tapahtuu REST API:n vertaamisen jälkeen.
{
    if(logResult == false){
        qDebug() << "mönkään meni";
        switchFontSize(10);
        numOftries--;
        ui->infoScreen->setText(tr("Incorrect PIN number.\n Tries left : %1").arg(numOftries));
        number=NULL;
        starCount=NULL;
        qDebug() << "numero nollattu"; // Väärin mennessä yrityksiä vähennetään yhdellä, ja siitä ilmoitetaan ruudulla. Lisäksi luku, ja tähdet nollataan.
        lockHandler(); // Kutsutaan lockHandleria, mikäli yritykset ovat menneet nollaan.
    }
    else if(logResult == true)
    {
        qDebug() << "PIN-koodi on oikea";
        switchFontSize(10);
        isCorrect = true; // Asetetaan bool-tyyppinen isCorrect-muuttuja true-asentoon, jotta pinUI tietää käyttäjän onnistuneen.
        ui->infoScreen->setText("Correct PIN number. Logging in..."); // Päivitetään ruutu ilmoittamaan siitä.
        lockHandler(); // Kutsutaan lockHandleria tässäkin, jotta nappeja ei voida enää painella.
        QTimer::singleShot(2500, this, SLOT(reEnableOrClose())); // Käytetään QTimerin singleShot ominaisuutta. Ajan jälkeen reEnableOrClose-funktioslotti käynnistyy, jossa ohjelma lopulta päättyy.
    }
    logResult = NULL; //ehkä turha lol
}


void pinUI::lockHandler() // Toiminnolla lukitaan näppä
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

void pinUI::switchFontSize(short fontSize) // Yksinkertainen funktio ruudun fontin koon vaihtamiselle.
{
    QFont font;
    font.setPointSize(fontSize);
    ui->infoScreen->setFont(font);
    qDebug() << "fonttia muutettu";
}

