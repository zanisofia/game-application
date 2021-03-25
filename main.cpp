#include <QApplication>

#include <partita.h>
#include <mainwindow.h>
#include <popup.h>

int main(int argc, char *argv[])
{
    //oggetto che mi permette di creare un'applicazione
    QApplication a(argc, argv);

    //inizializzo la finestra di dialogo principale e la visualizzo
    MainWindow window;
    window.show();

    bool ris=false;
    do{
        //creo il tabellone di gioco e salvo il numero di caselle che ha il tabellone
        partita p(window.getThis(), window.getViewTabellone(), window.getViewGiocatori());

        p.gioca();

        ris = p.fine();

    } while (ris);

    return a.exec();
}
