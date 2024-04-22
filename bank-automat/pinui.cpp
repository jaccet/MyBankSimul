#include "pinui.h"
#include "ui_pinui.h"

// Täytyy korjata kun pinui tuhoutuu että RFID portti ei aukea uudelleen.
pinUI::pinUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinUI)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
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
    qDebug() << "QListit jokaiselle napille luotu";;
}

pinUI::~pinUI()
{
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
        emit PINFromPinUI(number);
        this->close();        // Käyttäjän painaessa enteriä kutsutaan REST API:n requestLogin-funktiota number-muuttujan avulla, joka lähetetään REST API:in verrattavaksi. // Tämä johtaa myös loginHandler-funktioon, joka on alempana.
    }
}

void pinUI::switchFontSize(short fontSize) // Yksinkertainen funktio ruudun fontin koon vaihtamiselle.
{
    QFont font;
    font.setPointSize(fontSize);
    ui->infoScreen->setFont(font);
    qDebug() << "fonttia muutettu";
}

