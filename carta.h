#ifndef CARTA_H
#define CARTA_H

#include <QWidget>
#include <giocatore.h>

class carta
{
public:
    carta();
    carta(int t);
    int getType();
    int getImg();
    int getMsg();

private:
    int type;
    QString img;
    QString msg;
};

#endif // CARTA_H
