#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <QWidget>

class giocatore
{
public:
    giocatore();
    giocatore(QString nome, QString colore);

    //modifica variabili con il controllo degli input (il nome e il colore non sono modificabili)
    void modAccumultatoreTurni(int val);
    void modBloccoPosizione(bool val);
    void modBonus(int val);
    void modImmunita(bool val);
    void modPosizione(int val);

    //output variabili
    int getAccumultatoreTurni();
    bool hasBloccoPosizione();
    int getBonus();
    QString getColore();
    bool hasImmunita();
    QString getNome();
    int getPosizione();

    //pedina da visualizzare sul tabellone
    QPixmap pedina;

private:
    //dichiarazione variabili
    int accumultatoreTurni;
    bool bloccoPosizione;
    int bonus;
    QString colore;
    bool immunita;
    QString nome;
    int posizione;
};

#endif // GIOCATORE_H
