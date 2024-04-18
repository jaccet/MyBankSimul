#ifndef PANKKISIVU_H
#define PANKKISIVU_H

#include <QMainWindow>
#include <rest_api.h>

namespace Ui {
class pankkiSivu;
}

class pankkiSivu : public QMainWindow
{
    Q_OBJECT

public:
    explicit pankkiSivu(QWidget *parent = nullptr, REST_API *rest=nullptr);
    ~pankkiSivu();

private:
    Ui::pankkiSivu *ui;
    REST_API *restPtr;
};

#endif // PANKKISIVU_H
