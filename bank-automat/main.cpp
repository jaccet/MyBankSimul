#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // QFile file("C:\SPL_Group4\bank-automat\styles");
    //file.open(QFile::ReadOnly);
   // QString styleSheet = QLatin1String(file.readAll());

   // a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
