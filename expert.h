#ifndef EXPERT_H
#define EXPERT_H

#include <QWidget>

namespace Ui {
class Expert;
}

class Expert : public QWidget
{
    Q_OBJECT

public:
    explicit Expert(QWidget *parent = 0);
    ~Expert();

private:
    Ui::Expert *ui;
};

#endif // EXPERT_H
