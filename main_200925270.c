//main_200925270.c
#include "librerias_200925270.h"

static inline void ciclo_programa ();

int main ( int argc, char **argv )
{
 	ciclo_programa ();
	return 0;
}

static inline void ciclo_programa ()
{
	int opcion = 0;
	do {
		char cadena[256];
		accion *lista;
		if( !leer_entrada_consola ( cadena ) ) {
			printf("\n\t Error: La cadena es demasiado grande para procesar.");
			continue;
		}

		analizar_entrada ( cadena, &lista );
		//analizar_entrada(cadena,lista_acciones,lista_errores);
		//ejecutar_acciones(opcion,lista_acciones,lista_errores);
	} while (opcion != 0);
	printf("\n");
}