/********************************************************************************
** Form generated from reading UI file 'pinui.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PINUI_H
#define UI_PINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_pinUI
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *infoScreen;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *button6;
    QPushButton *button0;
    QPushButton *button5;
    QPushButton *button3;
    QPushButton *button1;
    QPushButton *button4;
    QPushButton *button8;
    QPushButton *button7;
    QPushButton *button2;
    QPushButton *button9;
    QVBoxLayout *verticalLayout_2;
    QPushButton *buttonClr;
    QPushButton *buttonBck;
    QPushButton *buttonEnter;

    void setupUi(QDialog *pinUI)
    {
        if (pinUI->objectName().isEmpty())
            pinUI->setObjectName("pinUI");
        pinUI->resize(244, 226);
        gridLayout_2 = new QGridLayout(pinUI);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        infoScreen = new QLineEdit(pinUI);
        infoScreen->setObjectName("infoScreen");
        infoScreen->setMaximumSize(QSize(16777215, 70));
        QFont font;
        font.setPointSize(24);
        infoScreen->setFont(font);
        infoScreen->setAlignment(Qt::AlignCenter);
        infoScreen->setReadOnly(true);

        verticalLayout_3->addWidget(infoScreen);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        button6 = new QPushButton(pinUI);
        button6->setObjectName("button6");

        gridLayout->addWidget(button6, 1, 2, 1, 1);

        button0 = new QPushButton(pinUI);
        button0->setObjectName("button0");

        gridLayout->addWidget(button0, 3, 1, 1, 1);

        button5 = new QPushButton(pinUI);
        button5->setObjectName("button5");

        gridLayout->addWidget(button5, 1, 1, 1, 1);

        button3 = new QPushButton(pinUI);
        button3->setObjectName("button3");

        gridLayout->addWidget(button3, 0, 2, 1, 1);

        button1 = new QPushButton(pinUI);
        button1->setObjectName("button1");

        gridLayout->addWidget(button1, 0, 0, 1, 1);

        button4 = new QPushButton(pinUI);
        button4->setObjectName("button4");

        gridLayout->addWidget(button4, 1, 0, 1, 1);

        button8 = new QPushButton(pinUI);
        button8->setObjectName("button8");

        gridLayout->addWidget(button8, 2, 1, 1, 1);

        button7 = new QPushButton(pinUI);
        button7->setObjectName("button7");

        gridLayout->addWidget(button7, 2, 0, 1, 1);

        button2 = new QPushButton(pinUI);
        button2->setObjectName("button2");

        gridLayout->addWidget(button2, 0, 1, 1, 1);

        button9 = new QPushButton(pinUI);
        button9->setObjectName("button9");

        gridLayout->addWidget(button9, 2, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        buttonClr = new QPushButton(pinUI);
        buttonClr->setObjectName("buttonClr");

        verticalLayout_2->addWidget(buttonClr);

        buttonBck = new QPushButton(pinUI);
        buttonBck->setObjectName("buttonBck");

        verticalLayout_2->addWidget(buttonBck);

        buttonEnter = new QPushButton(pinUI);
        buttonEnter->setObjectName("buttonEnter");

        verticalLayout_2->addWidget(buttonEnter);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(pinUI);

        QMetaObject::connectSlotsByName(pinUI);
    } // setupUi

    void retranslateUi(QDialog *pinUI)
    {
        pinUI->setWindowTitle(QCoreApplication::translate("pinUI", "Dialog", nullptr));
        infoScreen->setPlaceholderText(QString());
        button6->setText(QCoreApplication::translate("pinUI", "6", nullptr));
        button0->setText(QCoreApplication::translate("pinUI", "0", nullptr));
        button5->setText(QCoreApplication::translate("pinUI", "5", nullptr));
        button3->setText(QCoreApplication::translate("pinUI", "3", nullptr));
        button1->setText(QCoreApplication::translate("pinUI", "1", nullptr));
        button4->setText(QCoreApplication::translate("pinUI", "4", nullptr));
        button8->setText(QCoreApplication::translate("pinUI", "8", nullptr));
        button7->setText(QCoreApplication::translate("pinUI", "7", nullptr));
        button2->setText(QCoreApplication::translate("pinUI", "2", nullptr));
        button9->setText(QCoreApplication::translate("pinUI", "9", nullptr));
        buttonClr->setText(QCoreApplication::translate("pinUI", "Clear", nullptr));
        buttonBck->setText(QCoreApplication::translate("pinUI", "<--", nullptr));
        buttonEnter->setText(QCoreApplication::translate("pinUI", "Enter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pinUI: public Ui_pinUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINUI_H
