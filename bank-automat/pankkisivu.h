#ifndef PANKKISIVU_H
#define PANKKISIVU_H

#include <QMainWindow>

namespace Ui {
class pankkiSivu;
}

class pankkiSivu : public QMainWindow
{
    Q_OBJECT

public:
    explicit pankkiSivu(QWidget *parent = nullptr);
    ~pankkiSivu();

private:
    Ui::pankkiSivu *ui;
};

#endif // PANKKISIVU_H
