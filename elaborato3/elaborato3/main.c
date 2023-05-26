/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione: Dato un array di BYTE, invertire l’ordine dei bit all’interno
			  dell’array.

 ********************************************************************************/


#include <stdio.h>

void main()
{
#define MAX_LEN	100

	// Input
	unsigned char vet[]={0x01,0x02,0x03};			//Array di BYTE
	unsigned int len=sizeof(vet)/sizeof(vet[0]);	// numero di byte in vet	
// Output
	unsigned char res[MAX_LEN];						//Array di BYTE contenente il risultato 

// Blocco assembler
	__asm
	{
		xor eax, eax
		mov edx, len

	ciclo:
		xor ebx, ebx
		mov ecx, 0		;contatore utilizzato nel ciclo interno (i nei seguenti commenti)

		ciclo_interno:
			mov bl, vet[edx-1]	;byte attuale da trasformare
			shr bl, cl			;sposto il bit 8-i alla fine del byte (considero il primo bit in posizione 1)
			shl bl, 7			;sposto il bit 8-i all inizio del byte
			shr bl, cl			;sposto il bit 8-i in posizione i+1 all interno del byte
			add bh, bl			;aggiungo il bit al risultato parziale bh
			inc cl
			cmp cl, 7
			jna ciclo_interno

		mov res[eax], bh;sposto il risultato della trasformazione nella poszione opposta rispetto al byte attuale(ultimo => primo, penultimo => secondo, ...)
		inc eax
		dec edx
		cmp eax, len 
		jnz ciclo
	}

	// Stampa su video
	{
		unsigned int i;
		for (i=0;i<len;i++)
			printf("res[%2d] = %10d (%08X)\n",i,res[i],res[i]);
	}
}

