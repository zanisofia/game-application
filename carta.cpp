#include "carta.h"

carta::carta(){}

carta::carta(int t){
    type = t;
    switch (type) {
        case 1:{
            img = "../immagini/carte/spada.png";
            msg = "Che fortuna! Hai trovato la spada di Finn! Con questa sarai immune da Re Ghiaccio: ti sarà utile conoscendo il suo caratterino!";
        }
        break;

        case 2:{
            img = "../immagini/carte/chitarra.png";
            msg = "Meraviglia delle meraviglie! La chitarra di Marceline: avanzerai del doppio se tiri subito il dado! Ma sbrigati perchè se lei ti vede sono guai!";
        }
        break;

        case 3:{
            img = "../immagini/carte/bimo.png";
            msg = "";
        }
        break;

        case 4:{
            img = "../immagini/carte/corona.png";
            msg = "";
        }
        break;

        case 5:{
            img = "../immagini/carte/candy.png";
            msg = "";
        }
        break;

        case 6:{
            img = "../immagini/carte/cappelloFiona.png";
            msg = "";
        }
        break;

        case 7:{
            img = "../immagini/carte/pinguino.png";
            msg = "";
        }
        break;

        default:{
            img = "../immagini/carte/nuvola.png";
            msg = "";
        }
        break;
    }
}

int carta::getType(){
    return type;
}

int carta::getImg(){
    return img;
}

int carta::getMsg(){
    return msg;
}
