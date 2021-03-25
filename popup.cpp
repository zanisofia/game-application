#include "popup.h"

//costruttore per popup di avviso o scelta si/no
popup::popup(QWidget *parent, const QString titoloPopup, QString messaggio, QString indirizzoImmagine, bool siNo)
    : QDialog(parent)
{
    //inizializzo la griglia di layout del popup
    QGridLayout *mainLayout = new QGridLayout;

    //carico l'immagine e la posizione della griglia
    img = new QLabel();
    img->setPixmap(QPixmap (indirizzoImmagine).scaledToHeight(200));
    mainLayout->addWidget(img, 0, 0, 2, 1, Qt::AlignCenter);

    //inserisco il messaggio da far vedere all'utente e lo posiziono anch'esso
    testo = new QLabel(messaggio);
    mainLayout->addWidget(testo, 0, 1, Qt::AlignCenter);

    //visualizzo il pulsante di proseguimento e inserisco il collegamento alla funzione che deve essere eseguito quando è stato premuto
    if (siNo){
        buttonBox = new QDialogButtonBox(QDialogButtonBox::Yes
                                             | QDialogButtonBox::No);
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    }
    else{
        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    }
    mainLayout->addWidget(buttonBox, 3, 0, 1, 3);

    //visualizzo il layout appena creato
    setLayout(mainLayout);

    //inserisco il titolo che dovrà avere la finestra
    setWindowTitle(titoloPopup);
}

/*--- COSTRUTTORE - per popup con un menù a tendina, più l'opzione di inserire o meno l'input testuale ---*/
popup::popup(QWidget *parent, const QString titoloPopup, QString messaggio, QString indirizzoImmagine, bool setTextInput, QString campi[], int lunghezza)
    : QDialog(parent)
{
    //inizializzo la griglia di layout del popup
    QGridLayout *mainLayout = new QGridLayout;
    QGridLayout *rightLayout = new QGridLayout;

    //carico l'immagine e la posizione della griglia
    img = new QLabel();
    img->setPixmap(QPixmap (indirizzoImmagine).scaledToHeight(200));
    mainLayout->addWidget(img, 0, 0, Qt::AlignCenter);

    //inserisco il messaggio da far vedere all'utente e lo posiziono anch'esso
    testo = new QLabel(messaggio);
    testo->setWordWrap(true);
    rightLayout->addWidget(testo, 0, 0, Qt::AlignCenter);

    rightLayout->addWidget(new QLabel(" "), 1, 0, Qt::AlignCenter);


    //visualizzo l'inserimento di testo libero e lo posiziono, ma solo se setLineEdit è vero
    if (setTextInput){
        input = new QLineEdit;
        rightLayout->addWidget(input, 2, 0, Qt::AlignCenter);
        isSet=true;
    }

    //visualizzo un menù di scelta multipla contenente i valori passati
    sceltaMult = new QComboBox();
    for (int i=0; i<lunghezza; i++){
        sceltaMult->addItem(campi[i]);
    }
    rightLayout->addWidget(sceltaMult, 3, 0, Qt::AlignCenter);

    mainLayout->addLayout(rightLayout, 0, 1, Qt::AlignCenter);

    //visualizzo il pulsante di proseguimento e inserisco il collegamento alla funzione che deve essere eseguito quando è stato premuto
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(controlloInput()));
    mainLayout->addWidget(buttonBox, 4, 0, 1, 3, Qt::AlignCenter);

    //visualizzo il layout appena creato
    setLayout(mainLayout);

    //inserisco il titolo che dovrà avere la finestra
    setWindowTitle(titoloPopup);
}

/*---CONTROLLO DEGLI INPUT---*/
void popup::controlloInput(){
    //controllo che vi sia l'inserimento testuale
    if (input != NULL){
        //se ha del testo al suo interno proseguo
        if (!input->text().isEmpty())
            accept();
        //altrimenti appare un messaggio di errore
        else{
            QMessageBox msgBox;
            msgBox.setWindowTitle("ERRORE");
            msgBox.setText("ATTENTO non hai scritto nulla nel campo apposito, mi dispiace ma fin quando non compili tutto non potremo andare avanti :_(");
            msgBox.exec();
        }
    }
    else {
        accept();
    }
}

/*---RITORNO INPUT TEXT---*/
QString popup::getInputText() const
{
    if (input != NULL){
        return input->text();
    }
    else {
        return NULL;
    }
}

/*---RITORNO INPUT CON SCELTA MULTIPLA---*/
QString popup::getSceltaMultipla() const
{
    if (sceltaMult != NULL){
        return sceltaMult->currentText();
    }
    else {
        return NULL;
    }
}

