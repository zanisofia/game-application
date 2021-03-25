#ifndef GRAFICA_H
#define GRAFICA_H

#include <QObject>
#include <QtWidgets>
#include <QGraphicsView>

#include <giocatore.h>
#include <casella.h>

class grafica : public QObject{
    Q_OBJECT

public:
    grafica();

    int inizializzaTabellone(QGraphicsView *tabellone, QGraphicsView *giocatori);
    int disegnaTabellone(casella tab[]);
    void scegliCasella(casella tab[]);

    void visualizzaDatiGiocatori(giocatore giocatori[], int nG);
    void visualizzaPedine(giocatore giocatori[], int nG);

private:
    QGraphicsView* viewTabellone;
    QGraphicsScene* sceneTabellone;
    QGraphicsView* viewGiocatori;
    QGraphicsScene* sceneGiocatori;
    QGraphicsPixmapItem* pedine[9];
    int nR;
    int misure;
    int nElementi;

    int xCasella(int nCasella);
    int yCasella(int nCasella);
};

#endif // GRAFICA_H
