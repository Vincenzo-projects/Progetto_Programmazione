/* TRACCIA N∞ 1 : Si vuole sviluppare un programma per la simulazione del gioco del Forza 4ù. Si
suppone di avere 2 giocatori identificati dal loro nome o da un personaggio.
L'obiettivo di ogni giocatore Ë quello di mettere in fila quattro proprie pedine. La
scacchiera rettangolare Ë posta in verticale fra i giocatori, e le pedine vengono fatte
cadere lungo una griglia verticale, in modo tale che una pedina inserita in una certa
colonna va sempre a occupare la posizione libera situata pi˘ in basso nella colonna
stessa. Il gioco termina automaticamente (il programma effettua il controllo) quando
uno dei giocatori ha messo in fila quattro delle sue pedine. */

/* Il programma al momento dell'esecuzione consente di scegliere la modalit‡† di gioco, composta da 3 modalit‡†: Utente vs Utente (1), Utente vs Computer (2),
Computer vs Computer (3), la scelta viene effettuata inserendo un numero compreso tra 1-3. Prima di iniziare la partita viene chiesto il nome dei due giocatori,
in questo modo si viene identificati nella gestione del turno. Le pedine vengono fatte cadere verticalmente in un griglia, in cui vanno ad occupare
la posizione libera della colonna scelta. Vince chi riesce a mettere in fila quattro pedine di seguito, ovviamente il programma comprende anche un eventuale
pareggio, dopo aver individuato il vincitore lo visualizzer‡ a schermo e verr‡ chiesto se si vuole iniziare una nuova partita o terminare (s/n)  */



#include "header.h"



void gioca(char n1[CN], char n2[CN], int tg1, int tg2){
 int m[R][C], t=1, f, nt=0, r, c, g=g2I ;

 f=FGioca;
 azzera(m);

 do{
   CLS;
   stampaTitolo();
   g=giocatoreP(g);
   printf("Mossa numero: %d\n",++nt); // ++nt, indice numero di mosse viene incrementato
   if(t)
     printf("E' il turno di %s (%c)\n\n", n1,g1);
   else
     printf("E' il turno di %s (%c)\n\n", n2,g2);
   stampa(m);

   //Se gioca l'utente
   if( (g==1 && tg1==User) || (g==2 && tg2==User)){
     while(1){
       printf("In che colonna vuoi mettere il gettone?  ");
       scanf("%d", &c); //questa istruzione consente di scegliere in quale colonna inserire il gettone
       fflush(stdin); //fflush serve a pulire il buffer
       c--;
       if(c<0 || c>=C)
         continue;
       r=inserisci(m,c);
       if(r!=-1)
         break;
     }
   }else{ // Se gioca il computer
           c=mossaPC(m, g, giocatoreP(g));
           r=inserisci(m,c); //mossaPc ritorna una colonna valida e con spazio
           m[r][c]=g;
     printf("\nc = %d \n", c+1);
     //getchar();
   }
  
   m[r][c]=g;
   if (controllaF (m,g,r,c,1)){
       f=g;
   }
   else {
    f=f;
   }
   if(nt==R*C && f==0){
     f=FPareggio;
     break;
   }
 }while(!f);

 CLS; // pulisce lo schermo su windows
 stampaTitolo();
 stampa(m);
 switch(f){ //stampa chi ha vinto la partita
   case 1:
     printf("\n\nHa vinto %s (%c)", n1, g1);
     break;
   case 2:
     printf("\n\nHa vinto %s (%c)", n2, g2);
     break;
   case 3:
     printf("\n\nPareggio");
     break;
 }
}


int mossaPC(int m[R][C], int gp, int ga){
       int r,c,m2[R][C],cas,g,i;
      
       //Riempio la matrice di supporto
       for(r=0; r<R ;r++)
         for(c=0; c<C; c++)
           m2[r][c]=m[r][c];
      
       printf("mossaPC ( m, %d, %d )",gp,ga);
      
       // 1∞ ciclo Controlla se puÚ vincere
       // 2∞ ciclo controlla se l'avversario puÚ vincere
       for(i=0; i<2; i++){
           if (i){
               g=ga;
           }
           else {
               g=gp;
           }
         for(c=0;c<C;c++){
               r=inserisci(m2,c);
               m2[r][c]=g;
               printf("\n  c=%d  r=%d controllaF( m, %d, %d, %d, 0)=%d", c,r,g,r,c,controllaF(m2, g, r, c, 0));
           if(r!=-1 && controllaF(m2, g, r, c, 0))
             return c;
     m2[r][c]=vuotoI;
   }
 }

 while(1)   //Controlla se nella colonna casuale c'Ë spazio
   if(inserisci(m2,cas=rand()%C)!=-1)
     return cas;
}


int giocatoreP(int g){
       if (g==g1I)
       g=g2I;
       else
       g=g1I;
      return g;
       
}



int inserisci(int m[R][C], int c){
 int i;
 for(i=R-1; i>=0; i--)
   if(m[i][c]==vuotoI)
     return i;
 return -1;
}


int controllaF(int m[R][C], const int g, const int r, const int c, const int e){
       int r2, c2, x, ret=0, i, ok;
      
       //Controllo diagonale \ ___
       if(esiste(r-1,c-1) && m[r-1][c-1]==g)
         if(x=controllaF(m,g,r-1,c-1,e)!=0)
           ret=ret||x;
 if(r<R-(NGV-1) && c<C-(NGV-1)){
       ok=1;
   for(i=0; i<NGV && (ok*=(m[r][c]==m[r+i][c+i] || m[r+i][c+i]==vI)); i++) ;
   if(ok){
       if(e)
       for(i=0; esiste(r+i, c+i) && m[r+i][c+i]==g; i++)
         m[r+i][c+i]=vI;
     ret=1;
   }
 }

 //Controllo diagonale /  ___
       if(esiste(r+1,c-1) && m[r+1][c-1]==g)
         if(x=controllaF(m,g,r+1,c-1,e)!=0)
           ret=ret||x;
 if(r>(NGV-2) && c<C-(NGV-2)){
       ok=1;
   for(i=0; i<NGV && (ok*=(m[r][c]==m[r-i][c+i]) || m[r-i][c+i]==vI); i++) ;
   if(ok){
       if(e)
       for(i=0; esiste(r-i, c+i) && m[r-i][c+i]==g; i++)
         m[r-i][c+i]=vI;
     ret=1;
   }
 }

       //Controllo riga
       if(esiste(r,c-1) && m[r][c-1]==g)
         if(x=controllaF(m,g,r,c-1,e)!=0)
           ret=ret||x;
 if(c<C-(NGV-1)){
       ok=1;
   for(i=0; i<NGV && (ok*=(m[r][c]==m[r][c+i] || m[r][c+i]==vI)); i++) ;
   if(ok){
       if(e)
       for(i=0; esiste(r, c+i) && m[r][c+i]==g; i++)
         m[r][c+i]=vI;
     ret=1;
   }
 }
      
       //Controllo colonna
       if(r<R-(NGV-1)){
       ok=1;
       for(i=0; i<NGV && (ok*=(m[r][c]==m[r+i][c] || m[r+i][c]==vI)); i++) ;
       if(ok){
       if(e)
       for(i=0; i<NGV; i++) //Non serve controllare se sono pi√π di 4
         m[r+i][c]=vI;
     ret=1;
               }
       }
      
 return ret;
}



int esiste(int r, int c){
       if(r>=0&&r<R && c>=0&&c<C)
         return 1;
       return 0;
}



void azzera(int m[R][C]){
 int i,j;
 for(i=0; i<R; i++)
   for(j=0; j<C; j++)
     m[i][j]=0;
}



void stampa(int m[R][C]){
 int i,j;
 printf("\n");
 stampaRigaPiena();  //Stampo prima riga |---|---|--...

 for(i=0; i<R; i++){ //Stampo le righe centrali
   printf("   |");
   for(j=0; j<C; j++)
     printf(" %c |",stampaCasella(m[i][j]));
   printf("\n");
   stampaRigaPiena();
 }
 stampaRigaPiena();  //Stampo prima riga |---|---|--...
 printf("   |");
 for(j=1; j<=C; j++)
   printf(" %d |", j);
 printf("\n");
 stampaRigaPiena();  //Stampo prima riga |---|---|--...
 printf("\n");
}
void stampaRigaPiena(){
 int i,j;
 printf("   |");
 for(j=1; j<=C; j++)
   printf("---|");
 printf("\n");
}
char stampaCasella(int x){
       char c;
       switch(x){
               case 0:
           c=vuoto; break;
   case 1:
       c=g1; break;
       case 2:
       c=g2; break;
       case 3:
               c=CVitt; break;
       }
       return c;
}
void stampaTitolo(void){
 printf("\n\n\t ### Forza quattro ###\n\n");
}


//Corpi delle funzioni
int main(int argc, char *argv[]){
  char n1[CN]="Giocatore A", n2[CN]="Giocatore B", r, k=0; //CN Ë la dimesnione dell'array di char , Max 15
  int m[R][C], tipoGioco=0, tg1, tg2;
  srand(time(NULL));   /* L'istruzione srand (time(NULL)) inizializza la generazione di numeri casuali che verr‡† usato dalla funzione rand()
                          in modo che a ogni esecuzione generi numeri diversi.*/
 do {
 
  do{
        CLS;
        stampaTitolo();
        printf("\n\t 1. User vs User");
                printf("\n\t 2. User contro Computer");
                printf("\n\t 3. Computer contro Computer");
        printf("\n\n   Scegli la modalita' di gioco: ");
        scanf("%d", &tipoGioco); // con questa istruzione viene scelta la modalit√† di gioco
        fflush(stdin);
  }while(tipoGioco<1||tipoGioco>3); //Termina il ciclo Do-While
 
  if(tipoGioco!=CvsC){  //Questa istruzione identifica la modalit√† computer vs Computer
        printf("Inserisci il nome del giocatore:\n   ");
    scanf("%s", n1);
    fflush(stdin);
    if(tipoGioco==UvsU){
        printf("Inserisci il nome del secondo giocatore:\n   ");
      scanf("%s", n2);
      fflush(stdin);
    }else
        strcpy(n2, "CPU1");
  }else{
          strcpy(n1, "CPU1");
    strcpy(n2, "CPU2");
  }
 
    if(tipoGioco==UvsU) //Questa istruzione identifica la modalit‡† User vs User
      tg1=tg2=User;
    else if(tipoGioco==UvsC){  //Questa istruzione identifica la modalit‡† User vs Computer
        tg1=User; tg2=CPU;
    }else
      tg1=tg2=CPU;
   
                gioca(n1, n2, tg1, tg2);
    printf("\n\nVuoi fare una nuova partita? (s/n)");
    scanf("%c", &r);
    fflush(stdin);
  }while(r=='s' || r=='S'); // Termina il ciclo Do-While, identificato il vincitore scegli se rigiocare o terminare (return 0)
  return 0;
}
