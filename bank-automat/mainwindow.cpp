#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->transactionCheckButton,SIGNAL(clicked(bool)),this,SLOT(transactionCheckPressed()));
    connect(ui->accountCheckButton,SIGNAL(clicked(bool)),this,SLOT(accountCheckPressed()));
    connect(ui->userCheckButton,SIGNAL(clicked(bool)),this,SLOT(userCheckPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;
}

////////////////////////////////////////

void MainWindow::transactionCheckPressed()
{
    REST_API *test= new REST_API();
    QString idtransaction=ui->cardline->text();
    connect(test,SIGNAL(transactionChecked(bool)),this,SLOT(transactionCheckResult(bool)));
    test->checkTransaction(idtransaction);
}

void MainWindow::transactionCheckResult(bool result)
{
    if (result == false){
        qDebug()->"Oops";
    } else {
        qDebug()->"Pro";
    }
}

////////////////////////////////////////

void MainWindow::accountCheckPressed()
{
    REST_API *test= new REST_API();
    QString IBAN_no=ui->cardline->text();
    connect(test,SIGNAL(accountChecked(bool)),this,SLOT(accountCheckResult(bool)));
    test->checkAccount(IBAN_no);
}

void MainWindow::accountCheckResult(bool result)
{
    if (result == false){
        qDebug()->"Oops";
    } else {
        qDebug()->"Pro";
    }
}

////////////////////////////////////////

void MainWindow::userCheckPressed()
{
    REST_API *test= new REST_API();
    QString username=ui->cardline->text();
    connect(test,SIGNAL(userChecked(bool)),this,SLOT(userCheckResult(bool)));
    test->checkUser(username);
}

void MainWindow::userCheckResult(bool result)
{
    if (result == false){
        qDebug()->"Oops";
    } else {
        qDebug()->"Pro";
    }
}

