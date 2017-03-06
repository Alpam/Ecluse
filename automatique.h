#ifndef AUTOMATIQUE_H
#define AUTOMATIQUE_H

#include <QWidget>

namespace Ui {
class Automatique;
}

class Automatique : public QWidget
{
    Q_OBJECT

public:
    explicit Automatique(QWidget *parent = 0);
    ~Automatique();

private slots:
    void on_boutonModeExp_released();

private:
    Ui::Automatique *ui;
};

#endif // AUTOMATIQUE_H
