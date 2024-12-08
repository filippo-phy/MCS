#include <TApplication.h>

using namespace std;

int main() {
   /* ATTENZIONE: l'istruzione che segue serve per far funzionare i grafici
    *             di ROOT e deve essere la prima istruzione del programma.
    *             Non aggiungete codice prima di questa istruzione
    */
   TApplication app("app", 0, 0);

   
   
   /* ATTENZIONE: l'istruzione che segue serve per far funzionare i grafici
    *             di ROOT e deve essere l'ultima istruzione del programma.
    *             Non aggiungete codice dopo questa istruzione
    */
   app.Run();
   return 0;
}
