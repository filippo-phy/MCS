//LEZIONE DEL 02/10/2024

/*override: dice che il metodo viene sovrascritto
  Basta che un metodo sia messo a virtual per ...?*/ 

CC = g++ 

all: Main

Main: main.cpp

/*(vedi foto, da scrivere in un file chiamato Makefile
____________________________________________________


COMANDI DI SHELL
la shell serve a dare comandi al sistema operativo, i comandi che vedremo valgono per linux, non per windows

se devo leggere un file di testo posso implementare un programma c++ oppure usare dei comandi di shell

comandi base(vedi slides)

"|" tra due comandi li concatena.

§GREP: filtro, ricerca una parola in un file, se aggiungo -v funziona come anti-filtro;
§SED: manipolazione e filtraggio testo, di base stampa solo la modifica sul terminale senza sovrascrivere, per farlo si ridirige l'output
     con l'operatore ">";
§SCRIPT: prendo una serie di comandi e li metto in un file .sh che posso implementare come eseguibile "source ----" permette di dare visibilità 
         alle variabili (?), posso passare parametri;
§IF: if[] then, elif[] then, else then;
§FOR: */

in fit.sh:
#!/bin/bash

for pl in $*
do
ls directory/$pl.(txt)
done

/*
§AWK: analizza i dati in colonna in parallelo, {print $0} stampa tutto, sotto $ posso selezionare la colonna, anche non in ordine
*/

  grep SOE -A3 nomefile | tail -2 /*e se uso -B2?*/ | sed 's/=/ /g' | Awk '{print $2" "$4" "$6}'; /* " " è lo spazio nella stampa*/

//trasferisco i comandi su uno script

in filter.sh:
#!/bin/bash
echo " ">fileinput.dat //sovrascrive il file, viene eseguito una volta sola, per pulire il file (?)
for pl in $* 
do
/* eventuale nome del pianeta*/  echo "$pl" >> fileinput.dat
/*aggiungere GM*/ grep PHYSICAL -A7 ephemerides/$pl.txt | tail -1 | awk '{print $4}' >> fileinput.dat
grep SOE -A3 ephemerides/$pl.txt | tail -2 | sed 's/=/ /g' | awk '{print $2" "$4" "$6}' >> fileinput.dat
echo " " >>fileinput.dat
 
done







  

  
