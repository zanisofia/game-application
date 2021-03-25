#ifndef PARTITA_H
#define PARTITA_H

#include <QWidget>
#include <QGraphicsView>
#include <grafica.h>
#include <giocatore.h>
#include <carta.h>
#include <casella.h>


class partita
{
public:
    partita(QWidget* thisW, QGraphicsView* viewT, QGraphicsView* viewG);
    void gioca();
    bool fine();
private:
    //variabili utilizzate dal gioco
    QGraphicsView* viewTabellone;
    QGraphicsView* viewGiocatori;
    QWidget* thisWindos;
    grafica g;
    casella* caselle;
    int nCaselle;
    giocatore* giocatori;
    int nGiocatori;
    carta* carte;
    int nCarte;
    int iCarte;

    QString imgBase = "../immagini/base.jpg";

    //inizializzazione
    void creaMazzo();
    void inputNGiocatori();
    void inputGiocatori();

    //gestione eventi turni
    int tiraDado(QString nome);
    void azioneCarta(carta car, int i);
    void azioneCasella(casella cas, int i);
    int nPrimoGiocatore();
};

#endif // PARTITA_H
