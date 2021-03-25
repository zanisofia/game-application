#include "casella.h"

casella::casella(){}

int casella::getType(){
    return type;
}

int casella::getImg(){
    return img;
}

int casella::getMsg(){
    return msg;
}

void casella::modType(int t){
    type = t;
    switch (type) {
        case 1:{
            img = "../immagini/caselle/unicorno.png";
            msg = "Ciao, io sono Lady Unicorno; non so se ti ricordi di me, ma ho aiutato Finn e Jake in uno dei loro viaggi. Visto che mi hanno parlato così bene di te voglio darti una mano! \n Lancia il dado e potrai avanzare del numero uscito quando vorrai durante la gara!";
        }
        break;

        case 2:{
            img = "../immagini/caselle/vampira.png";
            msg = "Ciao, io sono una vampira e adoro suonare la mia chitarra elettrica. Se non vuoi che ti morda dovrai rimanere qui con me a provare la mia nuova canzone fin quando non arriverà qualcun altro a sostituirti";
        }
        break;

        case 3:{
            img = "../immagini/caselle/jake.png";
            msg = "Ehy ciao, visto che sei riuscito a scovare la mia tana e mi stai molto simpatico ti farò un grosso favore: verrai scambiato di posto con il primo giocatore";
        }
        break;

        case 4:{
            img = "../immagini/caselle/gommarosa.png";
            msg = "Ciao, non so se mi riconosci sono Gommarosa; è da un bel po' che non ci vediamo: ti devo raccontare tutto quello che è successo nel frattempo. Non prendere impegni per i prossimi 2 turni perchè dovrai rimanere qui a chiacchierare con me!";
        }
        break;

        case 5:{
            img = "../immagini/caselle/elefante.png";
            msg = "Ciao, io sono Melaverde. ehm... mi stai mettendo troppa pressione e io sono troppo timido per rimanere qui con te: perchè non tiri il dado e avanzi ancora un po'?";
        }
        break;

        case 6:{
            img = "../immagini/caselle/reGhiaccio.png";
            msg = "Sai chi sono io? Come no? IO SONO RE GHIACCHIO!!! per la tua impertinenza dovrai tornare all'inizio del percorso, magari così impari a capire chi è che comanda qui!";
        }
        break;

        case 7:{
            img = "../immagini/caselle/finn.png";
            msg = "Che fortuna! sei arrivato proprio nel momento giusto! Pesca una carta e vediamo cos'ha in serbo per te il futuro!";
        }
        break;

        case 8:{
            img = "../immagini/caselle/unicornoNero.png";
            msg = "Io ti conosco! Ti ho visto prima metre cercavi di rubare terreno agli altri giocatori! Lord Monochromicorn non te la farà passare liscia: tira il dado e dimmi di quante caselle dovrò farti indietreggiare!";
        }
        break;

        default:{
            img = "../immagini/base.png";
            msg = "Ci dispiace ma qui non c'è nessuno, magari nel prossimo turno potrai conoscere un nostro nuovo compagno di avventure";
        }
        break;
    }
}
