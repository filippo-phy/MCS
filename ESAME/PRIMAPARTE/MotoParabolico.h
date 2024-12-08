/*
 * Classe per la descrizione del moto parabolico in due dimensioni di un punto
 * materiale soggetto all'accelerazione gravitale terrestre.
 * Il punto materiale considerato si muove nel piano xy, il campo
 * gravitazionale terrestre e' rivolto nel verso negativo dell'asse y e
 * il piano di atterraggio e' identificato da y = 0.
 *
 * Date posizione e velocita' iniziali, impostabili con il costruttore
 * o mediante i metodi SetR0() e SetV0(), il metodo xAtterraggio() calcola
 * la coordinata x del punto di atterraggio.
 * E' accettabile qualsiasi coordinata iniziale e qualsiasi velocita'
 * iniziale, purche' la quota iniziale y0 sia non negativa.
 *
 * Tutti i parametri in ingresso e le grandezze ritornate dai metodi della
 * classe sono in unita' SI.
 */
class MotoParabolico
{
 public:
   // costruttore senza argomenti: il punto materiale e' creato nell'origine
   // e con velocita' iniziale nulla
   MotoParabolico();
   // costruttore con posizione e velocita' iniziali impostate dall'utente.
   // Tutte le grandezze sono in unita' SI.
   MotoParabolico(double x, double y, double vx, double vy);
   
   // Impostazione della posizione iniziale del punto materiale in unita' SI
   void SetR0(double x0, double y0);
   
   // Impostazione della velocita' iniziale del punto materiale in unita' SI
   void SetV0(double v0x, double v0y);
   
   // Calcola e ritorna la coordinata x del punto di atterraggio un unita' SI.
   // Se la quota di partenza y0 e' negativa, questo metodo stampa un
   // messaggio d'errore e ritorna la quota di partenza y0.
   double xAtterraggio();

 private:
   double _x0; // coordinata x della posizione iniziale
   double _y0; // coordinata y della posizione iniziale
   double _v0x; // componente x della velocita' iniziale
   double _v0y; // componente y della velocita' iniziale
};
