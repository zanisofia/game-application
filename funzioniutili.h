#ifndef FUNZIONIUTILI_H
#define FUNZIONIUTILI_H

/*--ELIMINA ELEMENTO - elimina dall'array il valore passato dall'ultima posizione in cui è stato trovato --*/
void eliminaElementoArray(QString array[], int n, QString val){
    int pos=n;
    for (int i=0; i<n; i++){
        if (array[i]==val){
            pos = i;
        }
    }
    for (int i=pos; i<n-1; i++){
        QString a=array[i+1];
        array[i+1]=array[i];
        array[i]=a;
    }
    n--;
}

/*--N° NUMERO DI FIBONACCI - calcola l'n-esimo numero della successione di Fibonacci--*/
int nFibonacci(int n){
    int fib;
    if ((n==0)||(n==1)){
        fib = 1;
    }
    else{
        int fib1=1;
        int fib2=1;
        int i=1;
        while(i<n){
            fib=fib1+fib2;
            i++;
            fib2=fib1;
            fib1=fib;
        }
    }
    return fib;
}

#endif // FUNZIONIUTILI_H
