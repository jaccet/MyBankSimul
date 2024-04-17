/********************************************************************************
** Form generated from reading UI file 'pankkisivu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANKKISIVU_H
#define UI_PANKKISIVU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pankkiSivu
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pankkiSivu)
    {
        if (pankkiSivu->objectName().isEmpty())
            pankkiSivu->setObjectName("pankkiSivu");
        pankkiSivu->resize(797, 357);
        centralwidget = new QWidget(pankkiSivu);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(28);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        pankkiSivu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pankkiSivu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 797, 22));
        pankkiSivu->setMenuBar(menubar);
        statusbar = new QStatusBar(pankkiSivu);
        statusbar->setObjectName("statusbar");
        pankkiSivu->setStatusBar(statusbar);

        retranslateUi(pankkiSivu);

        QMetaObject::connectSlotsByName(pankkiSivu);
    } // setupUi

    void retranslateUi(QMainWindow *pankkiSivu)
    {
        pankkiSivu->setWindowTitle(QCoreApplication::translate("pankkiSivu", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("pankkiSivu", "Pankkisivu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pankkiSivu: public Ui_pankkiSivu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANKKISIVU_H
