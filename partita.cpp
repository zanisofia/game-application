#include "partita.h"
#include "popup.h"
#include "funzioniutili.h"

partita::partita(QWidget* thisW, QGraphicsView *viewT, QGraphicsView *viewG){
    //inizializzo tutte le variabili statiche che mi serviranno durante la partita, che non dipendono dagli utenti (variabili grafiche e mazzo di carte)
    thisWindos = thisW;
    viewTabellone = viewT;
    viewGiocatori = viewG;

    //creo il tabellone di partita e scelgo le varie caselle (ad ognuna a seconda del tipo è assegnato un colore)
    nCaselle = g.inizializzaTabellone(viewTabellone, viewGiocatori);
    caselle = new casella[nCaselle];
    g.disegnaTabellone(caselle);
    g.scegliCasella(caselle);

    //inizializzo i dati dei giocatori
    inputNGiocatori();
    inputGiocatori();

    //creo il mazzo di carte
    creaMazzo();
    iCarte=0;

    //visualizzo i dati dei giocatori
    g.visualizzaDatiGiocatori(giocatori, nGiocatori);
    g.visualizzaPedine(giocatori, nGiocatori);
}

void partita::azioneCarta(carta car, int i){

    popup tipoCarta(thisWindos, "Carta", car.msg, car.img, false);
    if (tipoCarta.exec() == QDialog::Accepted) {
        return;
    }

    switch (car.type) {
        case 1:
            // ATTIVA IL FLAG IMMUNITA DA RE GHIACCIO
            giocatori[i].modImmunita(true);
        break;


        case 2:{
            // RITIRA IL DADO E VALE DOPPIO
            giocatori[i].modPosizione(giocatori[i].getPosizione()+(tiraDado(giocatori[i].getNome())*2));
            if (giocatori[i].getPosizione()>=(nCaselle-1)) {return;}
            azioneCasella(caselle[giocatori[i].getPosizione()], i);
        }
        break;

        case 3:{
            //FA STAR FERMO TE E UN ALTRO A TUA SCELTA PER N TURNI
            QString nom[nGiocatori-1];
            int j=0;
            for (int k=0; k<nGiocatori-1; k++){
                if (k!=i){
                    nom[j]=giocatori[k].getNome();
                    j++;
                }
            }
            popup nomeG(thisWindos, "Scegli il giocatore", "Scegli il giocatore che vuoi far star fermo con te n turni", imgBase, false, nom, nGiocatori-1);

            QString nome;
            if (nomeG.exec() == QDialog::Accepted) {
                nome = nomeG.getSceltaMultipla();
            }
            else{
                nome = giocatori[i].getNome();
            }

            int n = tiraDado(giocatori[i].getNome());
            giocatori[i].modAccumultatoreTurni(n);
            for (int j=0; j<nGiocatori; j++){
                if (giocatori[j].getNome()==nome){
                    giocatori[j].modAccumultatoreTurni(n);
                }
            }
        }
        break;

        case 4:
            //FA ANDARE AL PRIMO POSTO + 1
            giocatori[i].modPosizione(giocatori[nPrimoGiocatore()].getPosizione()+1);
        break;

        case 5:{
            //FA ANDARE INDIETRO UN AVVERSARIO A SCELTA DI N POSIZIONI
            QString nom[nGiocatori-1];
            int j=0;
            for (int k=0; k<nGiocatori-1; k++){
                if (k!=i){
                    nom[j]=giocatori[k].getNome();
                    j++;
                }
            }
            popup nomeG(thisWindos, "Scegli il giocatore", "Scegli il giocatore che vuoi far indietreggiare", imgBase, false, nom, nGiocatori-1);

            QString nome;
            if (nomeG.exec() == QDialog::Accepted) {
                nome = nomeG.getSceltaMultipla();
            }
            else{
                nome = giocatori[i].getNome();
            }

            int n = tiraDado(giocatori[i].getNome());
            for (int j=0; j<nGiocatori; j++){
                if (giocatori[j].getNome()==nome){
                    giocatori[j].modPosizione(n);
                }
            }
        }
        break;

        case 6:{
            //FA AVANZARE DELL'N-esimo NUMERO DI FIBONACCI
            int nF = nFibonacci(tiraDado(giocatori[i].getNome()));
            giocatori[i].modPosizione(giocatori[i].getPosizione()+nF);
            if (giocatori[i].getPosizione()>=(nCaselle-1)) {return;}
            azioneCasella(caselle[giocatori[i].getPosizione()], i);
        }
        break;

        case 7:{
            //FA AVANZARE DI UN NUMERO A SCELTA DI CASELLE TRA 0 E N
            int nD = tiraDado(giocatori[i].getNome());
            int n;

            QString num[nD+1];
            for (int i=0; i<nD+1; i++){
                num[i]=QString::number(i);
            }

            popup nG(thisWindos, "Avanza n caselle", "Di quante caselle vuoi avanzare?", imgBase, false, num, nD+1);

            if (nG.exec() == QDialog::Accepted) {
                bool t;
                n = nG.getSceltaMultipla().toInt(&t, 10);
            }
            else{
                n = 0;
            }

            giocatori[i].modPosizione(giocatori[i].getPosizione()+n);
            if (giocatori[i].getPosizione()>=(nCaselle-1)) {return;}
            azioneCasella(caselle[giocatori[i].getPosizione()], i);
        }
        break;

        case 8:{
            //PORTA UN CONCORRENTE A TUA SCELTA NELLA TUA POSIZIONE
            QString nom[nGiocatori-1];
            int j=0;
            for (int k=0; k<nGiocatori-1; k++){
                if (k!=i){
                    nom[j]=giocatori[k].getNome();
                    j++;
                }
            }
            popup nomeG(thisWindos, "Scegli il giocatore", "Scegli il giocatore che vuoi far venire nella tua posizione", imgBase, false, nom, nGiocatori-1);

            QString nome;
            if (nomeG.exec() == QDialog::Accepted) {
                nome = nomeG.getSceltaMultipla();
            }
            else{
                nome = giocatori[i].getNome();
            }

            for (int j=0; j<nGiocatori; j++){
                if (giocatori[j].getNome()==nome){
                    giocatori[j].modPosizione(giocatori[i].getPosizione());
                }
            }
        }
        break;
    }


}

void partita::azioneCasella(casella cas, int i){
    switch (cas.getType()) {
        case 1:
            //RITIRA IL DADO E ACCUMULI UN NUMERO CHE POTRAI UTILIZZARE PER AVANZARE NEI TURNI SUCCESSIVI
            giocatori[i].modBonus(tiraDado(giocatori[i].getNome()));
        break;

        case 2:{
            //FERMO NELLA CASELLA SINO A CHE NON ARRIVA UN ALTRO GIOCATORE NELLA STESSA CASELLA
            giocatori[i].modBloccoPosizione(true);

            //sblocco gli altri giocatori se già presenti nella casella
            for (int j=0; j<nGiocatori; j++){
                if ((giocatori[j].getPosizione() == giocatori[i].getPosizione()) && (i!=j)){
                    giocatori[j].modBloccoPosizione(false);
                }
            }
         }
         break;

        case 3:{
            // SCAMBIO DI POSTO COL PRIMO GIOCATORE
            int pos = giocatori[i].getPosizione();
            int nPrimo = nPrimoGiocatore();

            giocatori[i].modPosizione(giocatori[nPrimo].getPosizione());
            giocatori[nPrimo].modPosizione(pos);
        }
        break;

        case 4:
            //FERMO DUE TURNI
            giocatori[i].modAccumultatoreTurni(2);
        break;

        case 5:{
            //RITIRA IL DADO E AVANZA ANCORA
            giocatori[i].modPosizione(giocatori[i].getPosizione()+tiraDado(giocatori[i].getNome()));
            if (giocatori[i].getPosizione()>=(nCaselle-1)) {return;}
            azioneCasella(caselle[giocatori[i].getPosizione()], i);
        }
        break;

        case 6:{
            //RITORNA ALL'INIZIO
            giocatori[i].modPosizione(0);
        }
        break;

        case 7:{
            //PESCA UNA CARTA
            azioneCarta(carte[iCarte], i);

            iCarte++;
            if (iCarte >= nCarte) {
                creaMazzo();
                iCarte=0;
            }
        }
        break;

        case 8:{
            //TIRA IL DADO E RETROCEDI
            giocatori[i].modPosizione(giocatori[i].getPosizione()-tiraDado(giocatori[i].getNome()));
            if (giocatori[i].getPosizione()>=(nCaselle-1)) {return;}
            azioneCasella(caselle[giocatori[i].getPosizione()], i);
        }
        break;

    }

    popup tipoCasella(thisWindos, "Casella", cas.msg, cas.img, false);
    if (tipoCasella.exec() == QDialog::Accepted) {
        return;
    }
}

void partita::creaMazzo(){
    srand (time(0));
    nCarte = (rand() % 100) + 40;
    carte = new carta[nCarte];
    for (int i=0; i<nCarte; i++) {
        carte[i] = carta((rand() % 8) + 1);
    }
}

void partita::gioca(){
    for (int i=0; i<nGiocatori; i++){ //faccio fare un turno ad ogni giocatore
        //inizio turno n-esimo giocatore
        if ((giocatori[i].getAccumultatoreTurni()==0)&&(!giocatori[i].hasBloccoPosizione())){//controllo che il giocatore non sia costretto a stare fermo(sia per n turni o fin quando qualcuno non raggiunge la sua casella)
            if (giocatori[i].getBonus()>0){//se il giocatore ha delle caselle bonus da poter utilizzare, gli chiedo se vuole utilizzarlo
                QString messaggio = "Ciao "+giocatori[i].getNome()+", ho notato che hai un bonus di "+QString::number(giocatori[i].getBonus())+" caselle da utilizzare, vuoi utilizzarlo? ";

                popup utilizzaBonus(thisWindos, "Bonus", messaggio, imgBase, true); //creo un popoup yes/no
                if (utilizzaBonus.exec() == QDialog::Accepted) {
                    giocatori[i].modPosizione(giocatori[i].getPosizione()+giocatori[i].getBonus());
                    giocatori[i].modPosizione(0);
                    if (giocatori[i].getPosizione()>=(nCaselle-1)) {
                        popup vittoria(thisWindos, "Fine Partita", "CONGRATURAZIONI! "+giocatori[i].getNome()+" hai vinto la partita!", imgBase, false);
                        return;
                    }
                }
                else{
                    popup rimastoBonus(thisWindos, "Bonus", "Nessun problema lo potrai utilizzare nel tuo prossimo turno", imgBase, false);
                }
            }

            giocatori[i].modPosizione(giocatori[i].getPosizione()+tiraDado(giocatori[i].getNome()));
            if (giocatori[i].getPosizione()>=(nCaselle-1)) {
                popup vittoria(thisWindos, "Fine Partita", "CONGRATURAZIONI! "+giocatori[i].getNome()+" hai vinto la partita!", imgBase, false);
                return;
            }
            azioneCasella(caselle[giocatori[i].getPosizione()], i);
            //controllo che con i bonus delle carte/caselle non sia arrivato alla fine
            if (giocatori[i].getPosizione()>=(nCaselle-1)) {
                popup vittoria(thisWindos, "Fine Partita", "CONGRATURAZIONI! "+giocatori[i].getNome()+" hai vinto la partita!", imgBase, false);
                return;
            }
        }
        else{
            if (giocatori[i].hasBloccoPosizione()){
                popup immobilita(thisWindos, "Immobilità", "Mi dispiace "+giocatori[i].getNome()+" non ti puoi muovere per questo turno, devi rimanere a provare il nuovo duetto di chitarre elettriche con Vampira fin quando non arriverà qualcun'altro al tuo posto, buona fortuna...", imgBase, false);
            }
            else{
                giocatori[i].modAccumultatoreTurni(giocatori[i].getAccumultatoreTurni()-1);
                popup immobilita(thisWindos, "Immobilità", "Mi dispiace "+giocatori[i].getNome()+" devi rimanere altri "+QString::number(giocatori[i].getAccumultatoreTurni())+" turni a chiacchierare con Gommarosa, ci vediamo dopo", imgBase, false);
            }
        }
        //visualizzo i dati dei giocatori aggiornati
        g.visualizzaDatiGiocatori(giocatori, nGiocatori);
        g.visualizzaPedine(giocatori, nGiocatori);
    }
    gioca();
}

/*--INPUT DEL NUMERO DI GIOCATORI--*/
void partita::inputNGiocatori(){
    QString messaggio = "Ciao, io sono Finn e lui è il mio migliore amico Jake. Vi diamo il benvenuto in questa nuova puntata di \"Adventure Time e il partita dell'Oca Pazza\" i cui vi faremo conoscere tutti i nostri amici e nemici. E' tutto pronto mancate solo voi! In quanti sarete oggi nella corsa per aggiudicarsi la vittoria?";

    QString num[8];
    for (int i=0; i<8; i++){
        num[i]=QString::number(i+2);
    }

    popup nG(thisWindos, "Benvenuto", messaggio, imgBase, false, num, 8);

    if (nG.exec() == QDialog::Accepted) {
        bool t;
        nGiocatori = nG.getSceltaMultipla().toInt(&t, 10);
    }
    else{
        nGiocatori = 0;
    }
    giocatori = new giocatore[nGiocatori];
}

/*--INPUT DATI GIOCATORI(nome e colore)--*/
void partita::inputGiocatori(){

    int n=9;
    QString num[n];
    num[0]="rosso";
    num[1]="arancio";
    num[2]="giallo";
    num[3]="verde";
    num[4]="blu";
    num[5]="viola";
    num[6]="rosa";
    num[7]="bianco";
    num[8]="nero";


    for (int i=0; i<nGiocatori; i++){
        QString msg = "Benvenuto, tu sei il "+QString::number(i+1)+"° giocatore: inserisci il tuo nickName e scegli il colore della tua pedina per poter iniziare questa nuova avventura con noi!";
        popup player(thisWindos, QString::number(i+1)+"° Giocatore ", msg, imgBase, true, num, n);
        if (player.exec() == QDialog::Accepted) {
            giocatori[i] = giocatore(player.getInputText(), player.getSceltaMultipla());
            eliminaElementoArray(num, 9, giocatori[i].getColore());
            n--;
        }
    }
}

int partita::nPrimoGiocatore(){
    int nPrimo=0;
    int posMax=giocatori[0].getPosizione();
    for (int i=1; i<nGiocatori; i++){
        if (giocatori[i].getPosizione() > posMax){
            nPrimo = i;
            posMax = giocatori[i].getPosizione();
        }
    }
    return nPrimo;
}

bool partita::fine(){
   popup fine(thisWindos, "FINE PARTITA", "Il nostro viaggio è finito. Ma non ti preoccupare ho la sensazione che ci rivedremo molto presto. Vuoi iniziare una nuova avventura con noi?", imgBase, true);
    if (fine.exec() == QDialog::Accepted) {
       return true;
    }
    else{
        return false;
    }
}

int partita::tiraDado(QString nome){
     srand (time(0));
     int d = (rand() % 12 + 1);
     popup dado(thisWindos, "Risultato Dado", "Bravo "+nome+" lanciando i dadi hai fatto "+QString::number(d), imgBase, false);
     if (dado.exec() == QDialog::Accepted) {
        return d;
     }
     else{
         return d;
     }
}
