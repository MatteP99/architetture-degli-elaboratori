/*********************************************************************************
 *                                                                               *
 *                   Architetture dei sistemi di Elaborazione                    *
 *                                                                               *
 *********************************************************************************

 Elaborato 1
 Descrizione:	Data una stringa C (terminata dal carattere nullo), contenente una
			frase (ossia parole separate da spazi e/o segni di punteggiatura),
			trovare la parola più lunga e la parola più corta. In caso di parole
			di uguale lunghezza, considerare la prima da sinistra.
			Le due parole vanno copiate in due array di caratteri come stringhe
			C (terminate dal carattere nullo).
			I segni di punteggiatura da considerare sono: ".,;:'?!"

 **********************************************************************************/


#include <stdio.h>


void main()
{
	// Variabili
#define MAX_LEN	100
	char frase[MAX_LEN] = "Cantami, o Diva, del Pelide Achille l'ira funesta che \
												infiniti addusse lutti agli Achei";
	char parolaMax[MAX_LEN + 1];
	char parolaMin[MAX_LEN + 1];

	// Blocco assembler
	__asm
	{
		jmp inizio

	copia_parola:
		xor ebx, ebx

	ciclo_di_copia:
		mov dl, frase[eax]
		mov [esi][ebx], dl	;inserisco nella locazione di memoria precedentemente caricata in esi(con un certo offset ebx) la lettera da copiare
		inc eax				;tiene traccia della posizione delle lettera corrente all interno della frase
		inc ebx
		loop ciclo_di_copia
		mov [esi][ebx], 0	;inserisco il carattere di terminazione per le stringhe
		ret

	inizio:
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx			;contatore per scorrere la frase
		mov parolaMin[1], 127	;valore impostato per non copiare parole inesistenti dentro a separatore:
		mov parolaMax[1], 0		;valore impostato per non copiare parole inesistenti dentro a separatore:

	ciclo:
		mov al, frase[ecx]
		cmp al, 65			;verifico che il carattere non sia un segno di punteggiatura
		jb separatore
		inc bl				;bl contiene la lunghezza della parola corrente
		cmp bl,1
		jz cambia_offset	;se sto analizzando una nuova parola devo cambiare la posizione della parola corrente
		jmp fine_ciclo

	cambia_offset:
		mov bh, cl			;dh contiene la posizione di inzio della parola corrente
		jmp fine_ciclo

	separatore:
		cmp bl, 0			;controllo utilizzato per più di un carattere di punteggiatura di fila
		jz fine_ciclo
		cmp bl,parolaMin[1]			;parolaMin[1] contiene la lunghezza della parola più corta
		jb nuova_parola_corta
		cmp bl,parolaMax[1]			;parolaMax[1] contiene la lunghezza della parola più lunga
		ja nuova_parola_lunga
		mov bl, 0
		jmp fine_ciclo

	nuova_parola_corta:
		mov parolaMin[1], bl
		mov parolaMin[0], bh			;parolaMin[0] contiene la posizione della parola più corta all interno della frase
		jmp separatore

	nuova_parola_lunga:
		mov parolaMax[1], bl
		mov parolaMax[0], bh			;parolaMax[0] contiene la posizione della parola più lunga all interno della frase
		jmp separatore

	fine_ciclo:		
		inc ecx
		cmp ecx, MAX_LEN
		jnz ciclo
		
		xor eax, eax
		xor ecx, ecx
		mov cl, parolaMax[1]	;quanti caratteri devo copiare
		mov al, parolaMax[0]	;da che punto della frase devo partire
		lea esi, parolaMax		;dove devo copiare i caratteri
		call copia_parola

		xor eax, eax
		xor ecx, ecx
		mov cl, parolaMin[1]
		mov al, parolaMin[0]
		lea esi, parolaMin
		call copia_parola
	}

	// Stampa su video
	printf("%s\n%s\n%s\n", frase, parolaMax, parolaMin);

}

