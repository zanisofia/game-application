#ifndef CASELLA_H
#define CASELLA_H

#include <QWidget>
#include <QGraphicsItem>

class casella
{
public:
    casella();
    QGraphicsRectItem* bordo;
    int getType();
    int getImg();
    int getMsg();
    void modType(int t);

private:
    int type;
    QString img;
    QString msg;
};

#endif // CASELLA_H
