#ifndef POPUP_H
#define POPUP_H

//includo la classe di inputDialog per poter estenderla inmodo che sia più consono alle nostre esigenze
#include <QInputDialog>

//le classi che servono per gestire gli oggetti grafici utilizzati
#include <QWidget>
#include <QtWidgets>
#include <QPixmap>


class popup : public QDialog
{
    Q_OBJECT //servere per permettere alla classe di avere slots (funzioni da eseguire in modo asincrono quando succede un determinato evento)

public:
    //creo due costruttori in modo che a seconda delle esigenze si possa usare quello più consono
    popup(QWidget *parent, const QString titoloPopup, QString messaggio, QString indirizzoImmagine, bool siNo);
    popup(QWidget *parent, const QString titoloPopup, QString messaggio, QString indirizzoImmagine, bool setLineEdit, QString campi[], int lunghezza);

    //metodo di espostazione delle informazioni (creo delle classi e non vi faccio direttamente accedere per questioni di sicurezza e autorizzazioni)
    QString getInputText() const;
    QString getSceltaMultipla() const;

private slots:
    void controlloInput(); //controllo l'input sia corretto

private:
    //variabili private per la gestione degli oggetti grafici
    QLabel *testo, *img;
    QLineEdit *input=NULL;
    QComboBox *sceltaMult=NULL;
    bool isSet;
    QDialogButtonBox *buttonBox;

};

#endif // POPUP_H
