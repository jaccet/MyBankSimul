/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *INSERT_CARD_BT;
    QLabel *Current_CARD_NumberLB;
    QLineEdit *Current_CARD_NumberLE;
    QLabel *Current_PIN_NumberLB;
    QLineEdit *Current_PIN_NumberLE;
    QPushButton *LoginBT;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(786, 215);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        INSERT_CARD_BT = new QPushButton(centralwidget);
        INSERT_CARD_BT->setObjectName("INSERT_CARD_BT");
        INSERT_CARD_BT->setEnabled(true);
        QPalette palette;
        QBrush brush(QColor(85, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        INSERT_CARD_BT->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Source Code Pro")});
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        INSERT_CARD_BT->setFont(font);
        INSERT_CARD_BT->setCursor(QCursor(Qt::OpenHandCursor));
        INSERT_CARD_BT->setMouseTracking(true);
        INSERT_CARD_BT->setAutoFillBackground(true);

        horizontalLayout->addWidget(INSERT_CARD_BT);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        Current_CARD_NumberLB = new QLabel(centralwidget);
        Current_CARD_NumberLB->setObjectName("Current_CARD_NumberLB");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Yu Gothic UI Semibold")});
        font1.setPointSize(10);
        font1.setBold(true);
        Current_CARD_NumberLB->setFont(font1);
        Current_CARD_NumberLB->setAutoFillBackground(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, Current_CARD_NumberLB);

        Current_CARD_NumberLE = new QLineEdit(centralwidget);
        Current_CARD_NumberLE->setObjectName("Current_CARD_NumberLE");
        Current_CARD_NumberLE->setAutoFillBackground(true);
        Current_CARD_NumberLE->setCursorPosition(0);
        Current_CARD_NumberLE->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, Current_CARD_NumberLE);

        Current_PIN_NumberLB = new QLabel(centralwidget);
        Current_PIN_NumberLB->setObjectName("Current_PIN_NumberLB");
        Current_PIN_NumberLB->setFont(font1);
        Current_PIN_NumberLB->setAutoFillBackground(true);

        formLayout->setWidget(3, QFormLayout::LabelRole, Current_PIN_NumberLB);

        Current_PIN_NumberLE = new QLineEdit(centralwidget);
        Current_PIN_NumberLE->setObjectName("Current_PIN_NumberLE");
        Current_PIN_NumberLE->setAutoFillBackground(true);
        Current_PIN_NumberLE->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, Current_PIN_NumberLE);

        LoginBT = new QPushButton(centralwidget);
        LoginBT->setObjectName("LoginBT");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Source Code Pro")});
        font2.setPointSize(12);
        font2.setBold(true);
        LoginBT->setFont(font2);
        LoginBT->setCursor(QCursor(Qt::OpenHandCursor));
        LoginBT->setFocusPolicy(Qt::ClickFocus);
        LoginBT->setAutoFillBackground(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, LoginBT);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 786, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        INSERT_CARD_BT->setText(QCoreApplication::translate("MainWindow", "INSERT CARD INFORMATION", nullptr));
        Current_CARD_NumberLB->setText(QCoreApplication::translate("MainWindow", "Current CARD Number:", nullptr));
        Current_CARD_NumberLE->setInputMask(QString());
        Current_CARD_NumberLE->setText(QString());
        Current_PIN_NumberLB->setText(QCoreApplication::translate("MainWindow", "Current PIN Number:", nullptr));
        Current_PIN_NumberLE->setInputMask(QString());
        Current_PIN_NumberLE->setPlaceholderText(QCoreApplication::translate("MainWindow", "****", nullptr));
        LoginBT->setText(QCoreApplication::translate("MainWindow", "LOGIN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
