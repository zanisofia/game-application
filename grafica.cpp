#include "grafica.h"

grafica::grafica(){}

/*--DISEGNO IL TABELLONE DI GIOCO--*/
int grafica::disegnaTabellone(casella tab[]){
    int i=0; //indice per scorrere l'array
    int x=0;
    int y=0;

    //disegno la casella di inizio
    tab[i].bordo = new QGraphicsRectItem(x,y,misure,misure);
    sceneTabellone->addItem(tab[i].bordo);
    i++;
    x+=misure;

    //disegno la spirale di caselle
    for (int j=1; j<nR; j++){
        tab[i].bordo = new QGraphicsRectItem(x,y,misure,misure);
        sceneTabellone->addItem(tab[i].bordo);
        i++;
        x+=misure;
    }
    while (nR>0){
        for (int j=0; j<nR-1; j++){
            tab[i].bordo = new QGraphicsRectItem(x,y,misure,misure);
            sceneTabellone->addItem(tab[i].bordo);
            i++;
            y+=misure;
        }
        for (int j=0; j<nR-1; j++){
            tab[i].bordo = new QGraphicsRectItem(x,y,misure,misure);
            sceneTabellone->addItem(tab[i].bordo);
            i++;
            x-=misure;
        }
        for (int j=0; j<nR-3; j++){
            tab[i].bordo = new QGraphicsRectItem(x,y,misure,misure);
            sceneTabellone->addItem(tab[i].bordo);
            i++;
            y-=misure;
        }
        for (int j=0; j<nR-3; j++){
            tab[i].bordo = new QGraphicsRectItem(x,y,misure,misure);
            sceneTabellone->addItem(tab[i].bordo);
            i++;
            x+=misure;
        }
        nR=nR-4;
    }

    //disegno la casella di fine
    tab[i].bordo = new QGraphicsRectItem(x,y,misure,misure);
    sceneTabellone->addItem(tab[i].bordo);
    i++;
    return i;
}

/*--INIZIALIZZAZIONE DEL TABELLONE - calcolo quante e quali caselle avrà e disegno tutte le scene che mi serviranno--*/
int grafica::inizializzaTabellone(QGraphicsView* tabellone, QGraphicsView* giocatori){
    viewTabellone = tabellone;

    //numero random per il numero di caselle del tabellone (estraggo il numero della prima riga in alto - un numero tra 9 e 21, solo dispari - 8 possibili tabelloni di diverse dimensioni in tot)
    srand (time(NULL));
    nR = (rand() % 7) *2+9;

    int h = viewTabellone->height();
    int w = viewTabellone->width();

    misure = (h-10)/nR; //calcolo la dimensione che deve avere ogni casella

    //assegno le dimensioni della scena in base alle dimensioni della view
    int c = (w-h-misure)/2; //mi serve per far in modo che la scena sia centrata rispetto alla view
    sceneTabellone = new QGraphicsScene(-c, 0, w-10, h-10, viewTabellone);
    viewTabellone->setScene(sceneTabellone);

    nElementi=(((nR-1)*(nR-1))/2)+(nR*2-1)+1; //calcolo le caselle che avrà il tabellone (tra 50 e 242 caselle)
    qDebug() << nElementi;

    viewTabellone->show();

    for (int i=0; i<9; i++){
        pedine[i]=NULL;
    }

    viewGiocatori = giocatori;

    h = viewGiocatori->height();
    w = viewGiocatori->width();

    //assegno le dimensioni della scena in base alle dimensioni della view
    sceneGiocatori = new QGraphicsScene(0, 0, w-10, h-10, viewGiocatori);
    viewGiocatori->setScene(sceneGiocatori);

    viewGiocatori->show();

    return nElementi;
}

/*--DENOMINO IN MODO CASUALE OGNI CASELLA DEL TABELLONE--*/
void grafica::scegliCasella(casella tab[]) {
    for (int i=0; i<nElementi-1; i++){
        int j=i+rand();
        srand(j) ;
        tab[i].modType((rand() % 15) + 1);
        QBrush tmpBrush(Qt::SolidPattern);
        switch (tab[i].type) {
        case 1:
            tmpBrush.setColor(QColor(251, 230, 208)); //arancio
            tab[i].bordo->setBrush(tmpBrush);
            break;
        case 2:
            tmpBrush.setColor(QColor(251, 208, 208)); //rosso
            tab[i].bordo->setBrush(tmpBrush);
            break;
        case 3:
            tmpBrush.setColor(QColor(251, 251, 208)); //giallo
            tab[i].bordo->setBrush(tmpBrush);
            break;
        case 4:
            tmpBrush.setColor(QColor(251, 208, 240)); //rosa
            tab[i].bordo->setBrush(tmpBrush);
            break;
        case 5:
            tmpBrush.setColor(QColor(219, 251, 208)); //verde
            tab[i].bordo->setBrush(tmpBrush);
            break;
        case 6:
            tmpBrush.setColor(QColor(230, 255, 255)); //ghiaccio
            tab[i].bordo->setBrush(tmpBrush);
            break;
        case 7:
            tmpBrush.setColor(QColor(208, 208, 251)); //blu/azzurro
            tab[i].bordo->setBrush(tmpBrush);
            break;
        case 8:
            tmpBrush.setColor(QColor(220, 220, 220)); //grigio
            tab[i].bordo->setBrush(tmpBrush);
            break;
        default:
            tmpBrush.setColor(QColor(255, 255, 255)); //bianco
            tab[i].bordo->setBrush(tmpBrush);
            break;
        }
    }
    QBrush tmpBrush(Qt::SolidPattern);
    tmpBrush.setColor(QColor(255, 255, 255)); //bianco
    tab[0].bordo->setBrush(tmpBrush);
    tab[nElementi-1].bordo->setBrush(tmpBrush);
}

/*--VISUALIZZAZIONE DATI GIOCATORI - visualizzo i dati dei giocatori nella finestra a dx riportando tutte le informazioni(nome, colore, posizione, penalità e immunità)--*/
void grafica::visualizzaDatiGiocatori(giocatore giocatori[], int nG){
    QString text = "";

    for (int i=0; i<nG; i++){
        text += "\nNome: "+giocatori[i].getNome();
        text += "\nN° casella: "+QString::number(giocatori[i].getPosizione());
        text += "\nColore pedina: "+giocatori[i].getColore();
        if (giocatori[i].getBonus()>0){
            text += "\nHa "+QString::number(giocatori[i].getBonus())+" caselle di cui puoi avanzare quando vuoi";
        }
        if (giocatori[i].hasImmunita()){
            text += "\nE' immune da Re Ghiaccio";
        }
        if (giocatori[i].getAccumultatoreTurni()>0){
            text += "\nPrima di poter tornare a giocare dovrà aspettare "+QString::number(giocatori[i].getAccumultatoreTurni())+" turni";
        }
        text += "\n";
    }

    sceneGiocatori->clear();
    sceneGiocatori->addText(text);

    viewGiocatori->show();
}

/*--VISUALIZZAZIONE PEDINE - visualizzo le pedine sul tabellone di tutti i giocatori--*/
void grafica::visualizzaPedine(giocatore giocatori[], int nG){
    for (int i=0; i<nG; i++){
        int x=0, y=0;
        QString colore = giocatori[i].getColore();
        if (colore == "rosso"){
            x=1; y=1;
        }
        else if (colore == "arancio"){
            x=4; y=1;
        }
        else if (colore == "giallo"){
            x=8; y=1;
        }
        else if (colore == "verde"){
            x=12; y=1;
        }
        else if (colore == "blu"){
            x=16; y=1;
        }
        else if (colore == "viola"){
            x=1; y=9;
        }
        else if (colore == "rosa"){
            x=4; y=9;
        }
        else if (colore == "nero"){
            x=8; y=9;
        }
        else{
            x=12; y=9;
        }

        x=xCasella(giocatori[i].getPosizione())+(misure/20)*x;
        y=yCasella(giocatori[i].getPosizione())+(misure/20)*y;
        if (pedine[i]!=NULL){
            sceneTabellone->removeItem(pedine[i]);
        }
        pedine[i]=sceneTabellone->addPixmap(giocatori[i].pedina.scaledToHeight((misure/10)*6));
        pedine[i]->setPos(x,y);
    }
}

/*--COORDINATE X Nesima CASELLA - calcolo le coordinare sull'asse X dell'angolo in altro a sx della casella data--*/
int grafica::xCasella(int nCasella){
    int r=0;
    if (nCasella<nR){
        r=misure*nCasella;
    }
    else {
        nCasella=nCasella-nR;
        if (nCasella<nR-1){
            r=misure*nR;
        }
        else{
            nCasella=nCasella-nR+1;
            if (nCasella<nR-1){
                r=misure*(nR-nCasella);
            }
            else{
                nCasella=nCasella-nR+1;
                if (nCasella<nR-3){
                    r=misure;
                }
                else{
                    nCasella=nCasella-nR+3;
                    if (nCasella<nR-3){
                        r=misure*(nCasella+1);
                    }
                    else{
                        nCasella=nCasella-nR+3;
                        if (nCasella<nR-5){
                            r=misure*(nR-2);
                        }
                        else{
                            nCasella=nCasella-nR+5;
                            if (nCasella<nR-5){
                                r=misure*(nR-nCasella-2);
                            }
                            else{
                                nCasella=nCasella-nR+5;
                                if (nCasella<nR-7){
                                    r=misure*3;
                                }
                                else{
                                    nCasella=nCasella-nR+7;
                                    if (nCasella<nR-7){
                                        r=misure*(nCasella+3);
                                    }
                                    else{
                                        nCasella=nCasella-nR+7;
                                        if (nCasella<nR-9){
                                            r=misure*(nR-4);
                                        }
                                        else{
                                            nCasella=nCasella-nR+9;
                                            if (nCasella<nR-9){
                                                r=misure*(nR-nCasella-4);
                                            }
                                            else{
                                                nCasella=nCasella-nR+9;
                                                if (nCasella<nR-11){
                                                    r=misure*5;
                                                }
                                                else{
                                                    nCasella=nCasella-nR+11;
                                                    if (nCasella<nR-11){
                                                        r=misure*(nCasella+5);
                                                    }
                                                    else{
                                                        nCasella=nCasella-nR+11;
                                                        if (nCasella<nR-13){
                                                            r=misure*(nR-6);
                                                        }
                                                        else{
                                                            nCasella=nCasella-nR+13;
                                                            if (nCasella<nR-13){
                                                                r=misure*(nR-nCasella-6);
                                                            }
                                                            else{
                                                                nCasella=nCasella-nR+13;
                                                                if (nCasella<nR-15){
                                                                    r=misure*7;
                                                                }
                                                                else{
                                                                    nCasella=nCasella-nR+15;
                                                                    if (nCasella<nR-15){
                                                                        r=misure*(nCasella+7);
                                                                    }
                                                                    else{
                                                                        r=0;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return r;
}

/*--COORDINATE Y Nesima CASELLA - calcolo le coordinare sull'asse Y dell'angolo in altro a sx della casella data--*/
int grafica::yCasella(int nCasella){
    int r=0;
    if (nCasella<nR){
        r=0;
    }
    else {
        nCasella=nCasella-nR;
        if (nCasella<nR-1){
            r=misure*nCasella;
        }
        else{
            nCasella=nCasella-nR+1;
            if (nCasella<nR-1){
                r=misure*(nR-1);
            }
            else{
                nCasella=nCasella-nR+1;
                if (nCasella<nR-3){
                    r=misure*(nR-nCasella-1);
                }
                else{
                    nCasella=nCasella-nR+3;
                    if (nCasella<nR-3){
                        r=misure*2;
                    }
                    else{
                        nCasella=nCasella-nR+3;
                        if (nCasella<nR-5){
                            r=misure*(nCasella+2);
                        }
                        else{
                            nCasella=nCasella-nR+5;
                            if (nCasella<nR-5){
                                r=misure*(nR-3);
                            }
                            else{
                                nCasella=nCasella-nR+5;
                                if (nCasella<nR-7){
                                    r=misure*(nR-nCasella-3);
                                }
                                else{
                                    nCasella=nCasella-nR+7;
                                    if (nCasella<nR-7){
                                        r=misure*4;
                                    }
                                    else{
                                        nCasella=nCasella-nR+7;
                                        if (nCasella<nR-9){
                                            r=misure*(nCasella+4);
                                        }
                                        else{
                                            nCasella=nCasella-nR+9;
                                            if (nCasella<nR-9){
                                                r=misure*(nR-5);
                                            }
                                            else{
                                                nCasella=nCasella-nR+9;
                                                if (nCasella<nR-11){
                                                    r=misure*(nR-nCasella-5);
                                                }
                                                else{
                                                    nCasella=nCasella-nR+11;
                                                    if (nCasella<nR-11){
                                                        r=misure*6;
                                                    }
                                                    else{
                                                        nCasella=nCasella-nR+11;
                                                        if (nCasella<nR-13){
                                                            r=misure*(nCasella+6);
                                                        }
                                                        else{
                                                            nCasella=nCasella-nR+13;
                                                            if (nCasella<nR-13){
                                                                r=misure*(nR-7);
                                                            }
                                                            else{
                                                                nCasella=nCasella-nR+13;
                                                                if (nCasella<nR-15){
                                                                    r=misure*(nR-nCasella-7);
                                                                }
                                                                else{
                                                                    nCasella=nCasella-nR+15;
                                                                    if (nCasella<nR-15){
                                                                        r=misure*8;
                                                                    }
                                                                    else{
                                                                        r=0;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return r;
}
