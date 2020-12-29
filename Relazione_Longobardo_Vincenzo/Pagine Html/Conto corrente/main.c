/* Traccia N°2: Si supponga di voler gestire i conti correnti di n utenti. Ogni utente è identificato dal
Cognome, Nome, numero del conto, lista movimenti.
Gestire i conti correnti e gestire le seguenti operazioni

• Inserire un nuovo correntista a cui viene assegnato un codice univoco.
• Visualizzare la lista movimenti di un dato correntista (dato il numero del conto o
  Cognome/Nome) in una fissata data. */

#include "header.h"


/* Ripulisce lo stdin da eventuale sporcizia rimasta nel buffer */

void flush_stdin()
{
	char c;
	while ((c=getchar()) != '\n' && c != EOF);    /* Legge fino a \n o fino a end-of-file.*/
}

/* Ritorna il numero di caratteri inseriti nella
   riga (che possono essere anche di più di quelli letti) */

int get_line(char *buffer, int size)
{
	int c,len;

	fgets(buffer, size, stdin);     /* Legge una riga in input o al max. size caratteri */

	len = strlen(buffer);
	if (buffer[len-1] == '\n')     /* fgets non toglie il \n finale */
		buffer[len-1] = '\0';
	else
		while ((c = getchar()) != '\n' && c != EOF) /* Pulizia stdin */
			len++;                               /* Conto anche i caratteri di troppo */

	return len - 1;                 /* -1 in quanto l'ultimo carattere è \n */
}

int get_uint(unsigned int *num)
{
	char buffer[10];
	char *garbage = NULL;
	long value = 0;

	if (get_line(buffer, 10) >= 10)
		return -1;

	errno = 0;                              /* Se strtol ha un errore, questa variabile viene settata */
	value = strtol(buffer, &garbage, 0);    /* E' un funzione per passare un intero dato in stringa */

	if (errno || (garbage && *garbage != '\0'))
		return -1;

	/* Se garbage contiene qualcosa, vuol dire che l'utente ha immesso  altro oltre che a un semplice numero come input */

	*num = (unsigned int)value;
	return 0;
}

void inserisci(unsigned int id, const char *nome, const char *cognome)
{
	strncpy(utenti[id].nome, nome, MAX_NAME_SIZE);  /*strncpy viene usata quando bisogna copiare max n cartteri*/
	strncpy(utenti[id].cognome, cognome, MAX_NAME_SIZE);
	utenti[id].num_mov = 0;
}

void inserisci_movimento(unsigned int mittente, unsigned int destinatario,int quantita,int giorno,int mese,int anno)
{
	int x, y;

	x = utenti[mittente].num_mov;
 	y = utenti[destinatario].num_mov;
	if (x >= MAX_MOVIMENTI || y >= MAX_MOVIMENTI) {
		puts("Troppi movimenti");
		return;
	}
	/*Salvo i dati nell'array*/

	utenti[mittente].movimenti[x].quantita= -quantita; /* cambio segno */
	utenti[mittente].movimenti[x].utente=destinatario;
	utenti[mittente].num_mov++;
	utenti[destinatario].movimenti[y].quantita=quantita;
	utenti[destinatario].movimenti[y].utente=mittente;
	utenti[destinatario].num_mov++;

/* stdout, ossia il buffer dove scrive la funzione printf, è bufferizzato a linea: vuol dire che non viene stampato nulla 
finché non stampo anche un \n.*/
        fflush(stdout);

	/*Salvo i dati nell'array*/

        utenti[mittente].movimenti[x].giorno=giorno;
	utenti[destinatario].movimenti[y].giorno=giorno;
	utenti[mittente].movimenti[x].mese=mese;
	utenti[destinatario].movimenti[y].mese=mese;
	utenti[mittente].movimenti[x].anno=anno;
	utenti[destinatario].movimenti[y].anno=anno;
}

void ricerca_movimento(int uid,int i,int j,int g,int m,int a,int trovato)
{
	for (i = 0, trovato = 0; i < utenti[uid].num_mov; i++)
	{
		if ((utenti[uid].movimenti[i].giorno==g) && (utenti[uid].movimenti[i].mese==m) && (utenti[uid].movimenti[i].anno==a))
		{
			printf("Movimento trovato: %d\n", utenti[uid].movimenti[i].quantita);
			trovato += 1; /* Indica quanti movimenti ha trovato */
		}
	}
	if (trovato == 0)
		printf("Non ci sono movimenti\n\n");
	else
		printf("Sono stati trovati %d movimenti\n\n",trovato);
}

int main()
{
	unsigned int i;
	char c;
	char nome[MAX_NAME_SIZE];
	char cognome[MAX_NAME_SIZE];
	unsigned int id_mittente, id_destinatario, q;
	int giorno, mese, anno; /* Sono variabili locali, non argomenti */
        int uid;        //ID da ricercare
        int j;
        int g,m,a;      //Data da ricercare
	int trovato;
	i = 0;
	for (;;) /*CICLO FOR INFINITO*/
                {
		puts(   "1) Inserisci nuovo utente\n"
                        "2) Effettua nuovo movimento\n"
			"3) Elenca movimenti di un utente\n"
			"9) Esci\n");
		printf("Scelta: ");

		c = getchar(); /* Legge un solo carattere seguito da invio */
		flush_stdin(); /* Toglie dal buffer il \n finale e pulisce da eventuale altra sporcizia */

		switch(c)
		{
		case '1':
			if (i==MAX_UTENTI)
				puts("Numero massimo utenti raggiunto");
			printf("Nome: ");
			fflush(stdout);
			if (get_line(nome, MAX_NAME_SIZE) > MAX_NAME_LENGTH) {
				puts("Nome troppo lungo");
				continue;
			}
			printf("Cognome: ");
			fflush(stdout);
			if (get_line(cognome, MAX_NAME_SIZE)> MAX_NAME_LENGTH)
                        {
				puts("Cognome troppo lungo");
				continue;
			}
			inserisci(i, nome, cognome);
			printf("Utente creato [ID %d]\n\n",i);
			i++;
			break;
		case '2':
			printf("ID mittente: ");
			fflush(stdout);
			if (get_uint(&id_mittente) == -1 || id_mittente >= i)
                        {
				puts("ID non valido");
				continue;
                        }
			printf("ID destinatario: ");
			fflush(stdout);
			if (get_uint(&id_destinatario) == -1 || id_destinatario >= i)
			{
				puts("ID non valido");
				continue;
			}
			printf("Quanto vuoi inviare ?: ");
			fflush(stdout);
			if (get_uint(&q) == -1 || q == 0)
                        {
				puts("Quantita non valida");
				continue;
			}
			printf("In che data?\n");
			printf("Giorno:");
			fflush(stdout);
			if(get_uint(&giorno) == -1 || giorno==0 || giorno>=32)
			{
			        puts("Data non valida");
                                continue;
			}
			printf("Mese:");
			fflush(stdout);
			if(get_uint(&mese) == -1 || mese==0 || mese>=13)
			{
			        puts("Data non valida");
                                continue;
			}
			printf("Anno:");
			fflush(stdout);
			if(get_uint(&anno)== -1 || anno <=1929 || anno>=2100)
			{
			        puts("Data non valida");
                                continue;
			}
                        inserisci_movimento(id_mittente, id_destinatario,q,giorno,mese,anno);
			break;
		case '3':

                        printf("Ricerca movimento, inserisci l'ID:");
                        fflush(stdout);
                        if (get_uint(&uid) == -1 || uid >= i)
                        {
				puts("ID non valido");
				continue;
                        }
                        printf("Giorno :");
                        fflush(stdout);
                        if(get_uint(&g) == -1 || g == 0 || g>=32)
                        {
                                printf("Data errata");
                                continue;
                        }
                        printf("Mese :");
                        fflush(stdout);
                        if(get_uint(&m) == -1 || m == 0 || m>=13)
                        {
                                printf("Data errata");
                                continue;
                        }
                        printf("Anno :");
                        fflush(stdout);
                        if(get_uint(&a) == -1 || a <= 1929 || a>=2100)
                        {
                        printf("Data errata");
                        continue;
                        }
                        printf("\n");
		        ricerca_movimento(uid,i,j,g,m,a,trovato);
			break;
		case '9':
			exit(EXIT_SUCCESS); /* Termina il programma */
		default:
			puts("Comando non riconosciuto");
		}
	}
	return 0;
}
