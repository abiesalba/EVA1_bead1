#ifndef TRAVELLER_H
#define TRAVELLER_H

#include <QPushButton>

class Traveller : public QPushButton
{
    Q_OBJECT

public:
    void setVal(int poz)
    {
        setText(QString::number(poz));
        val=poz;
    }

    Traveller() : QPushButton(), val(0)
    {
        setFixedSize(60,60);
        setFont(QFont("Tahoma", 20));
        left = right = top = bottom = NULL;

    }

    int getVal(){
        return val;
    }

    Traveller *left, *right, *top, *bottom;

private:
    int val;
};

#endif // TRAVELLER_H

