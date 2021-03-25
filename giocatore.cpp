#include "giocatore.h"

/*--COSTRUTTORI--*/
giocatore::giocatore(){
    this->accumultatoreTurni=0;
    this->bloccoPosizione=false;
    this->bonus=false;
    this->colore="";
    this->immunita=false;
    this->nome="";
    this->posizione=0;
}

giocatore::giocatore(QString nome, QString colore){
    this->accumultatoreTurni=0;
    this->bloccoPosizione=false;
    this->bonus=false;
    this->colore=colore;
    this->pedina=QPixmap("../immagini/pedine/"+colore+".png");
    this->immunita=false;
    this->nome=nome;
    this->posizione=0;
}

/*--MODIFICA VARIABILI CON CONTROLLO SUGLI INPUT--*/
void giocatore::modAccumultatoreTurni(int val){
    if (val>=0){
        this->accumultatoreTurni = val;
    }
}

void giocatore::modBloccoPosizione(bool val){
    this->bloccoPosizione = val;
}

void giocatore::modBonus(int val){
    if (val>=0){
        this->bonus = val;
    }
}

void giocatore::modImmunita(bool val){
    this->immunita = val;
}

void giocatore::modPosizione(int val){
    if (val>=0){
        this->posizione = val;
    }
}


/*--OUTPUT VARIABILI--*/
int giocatore::getAccumultatoreTurni(){
    return this->accumultatoreTurni;
}

bool giocatore::hasBloccoPosizione(){
    return this->bloccoPosizione;
}

int giocatore::getBonus(){
    return this->bonus;
}

QString giocatore::getColore(){
    return this->colore;
}

bool giocatore::hasImmunita(){
    return this->immunita;
}

QString giocatore::getNome(){
    return this->nome;
}

int giocatore::getPosizione(){
    return this->posizione;
}
