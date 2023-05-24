/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Dato in input un numero naturale n, restituire i primi n termini
			  della successione di Fibonacci.

 ********************************************************************************/


#include <stdio.h>

void main()
{
	//Variabili
	int n = 12;						//Numero di termini da restituire
	int successione[50];			//Vettore in cui mettere i primi n termini
									//della successione di Fibonacci

	//Blocco Assembler
	__asm
	{
		mov successione[0],	0
		cmp n, 0					;gestisco il caso n = 0
		jz fine
		mov successione[1*4], 1
		cmp n, 1					;gestisco il caso n = 1
		jz fine
		mov ecx,2					;indice di successione

	ciclo:
		mov ebx, ecx				;ebx è utizzato come indice dell posizioni precedenti
		dec ebx
		mov eax, successione[ebx*4]	;sposto nel registo di appoggio n-1
		mov successione[ecx*4], eax	;sposto nell inidce corrente di successione n-1
		dec ebx
		mov eax, successione[ebx*4]	;sposto nel registro di appoggio n-2
		add successione[ecx*4], eax	;aggiungo all indice corrente n-2
		inc ecx
		cmp ecx, n
		jna ciclo

	fine:
	}

	//Stampa su video
	{
		int i;
 		for (i = 0; i <= n; i++)
		{
			printf("%d\n", successione[i]);
		}
	}
}
