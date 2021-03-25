#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->pushButton, SIGNAL(clicked()), graphic, SLOT(visualizza()));
}

/*--RITORNO THIS: ritorno la finestra (da utilizzare per i popup)--*/
QWidget* MainWindow::getThis(){
    return this;
}

/*--RITORNO BOTTONE INIZIO: ritorno il bottone di inizio (da utilizzare per creare una nuova partita)--*/
/*QPushButton* MainWindow::getBottoneInizio(){
    return ui->bottoneInizio;
}*/

/*--RITORNO VIEW GIOCATORI: ritorno la view dei giocatori (da utilizzare per visualizzare i dati dei giocatori)--*/
QGraphicsView* MainWindow::getViewGiocatori(){
    return ui->viewGiocatori;
}

/*--RITORNO VIEW TABELLONE: ritorno la view del tabellone (da utilizzare per visualizzare le caselle del tabellone e le pedine su di esso)--*/
QGraphicsView* MainWindow::getViewTabellone(){
    return ui->viewTabellone;
}

MainWindow::~MainWindow()
{
    delete ui;
}
