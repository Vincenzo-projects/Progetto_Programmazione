#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <errno.h> /* Libreria per la gestione degli errori(serve in get_uint) */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_UTENTI	20
#define MAX_MOVIMENTI	10
#define	MAX_NAME_LENGTH	10
#define	MAX_NAME_SIZE	MAX_NAME_LENGTH+1 /* Il char in più servirà a contenere il terminatore di carattere.*/

struct movimento {
	unsigned int giorno;
	unsigned int mese;
	unsigned int anno;
	int quantita;
	unsigned int utente;             /* Identifica l'utente con il quale è avvenuto il movimento */
};

struct utente {
	char nome[MAX_NAME_SIZE];
	char cognome[MAX_NAME_SIZE];
	struct movimento movimenti[MAX_MOVIMENTI];
	unsigned int num_mov;             /* Per sapere dove andrà inserito il prossimo movimento */
};
struct utente utenti[MAX_UTENTI];



#endif // HEADER_H_INCLUDED
