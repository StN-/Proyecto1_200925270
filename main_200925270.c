//main_200925270.c
#include "librerias_200925270.h"

/*
 *
 *
 *
 */

festplatte *festplatten;
static inline void ciclo_programa ();

/*
 *
 *
 *
 */


int main ( int argc, char **argv )
{
 	ciclo_programa ();
	return 0;
}

static inline void ciclo_programa ()
{
	int opcion = 1;
	festplatten = NULL;
	do {
		printf("\n");
		char cadena[256];
		accion *lista = NULL;
		if( !leer_entrada_consola ( cadena ) ) {
			printf("\n\t Error: La cadena es demasiado grande para procesar.");
			continue;
		}

		analizar_entrada ( cadena, &lista );
		opcion = ejecutar_instrucciones ( &lista );
	} while (opcion != 0);
	printf("\n");
}