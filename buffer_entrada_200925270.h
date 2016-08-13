//buffer_entrada_200925270.h
#ifndef BUFFER_ENTRADA_H
#define BUFFER_ENTRADA_H

/*
 *
 *
 *
 */

inline int leer_entrada_consola ( char * );
static inline int validar_final_linea ( char [] );
static inline void analizar_entrada_archivo ( char [], char [] );


inline int leer_archivo_entrada ( int, char *, char [] );

/*
 *
 *
 *
 */

inline int leer_entrada_consola ( char *_cadena )
{
	char entrada[256] = "";
	leer_entrada_formato_cadena( entrada, "\t > " );

	int longitud = strlen( entrada );
	while ( validar_final_linea ( entrada ) && longitud < 256 )
	{
		char buffer[164];
		leer_entrada_formato_cadena( buffer, "\t   " );
		longitud += strlen ( buffer ) + 1;
		if( longitud < 255 )
			concatenar ( entrada, 1, buffer );
		else
			return false;
	}

	if(DEPURADOR)
		printf("\n\t(Salida Del Buffer: %s)", entrada);
	strcpy( _cadena, entrada );
	return true;
}

inline int leer_archivo_entrada ( FILE **_archivo )
{
	int numero_linea = 0;
	char buffer[128] = "";
	char cadena[256] = ""
	
	accion *instrucciones = NULL;

	while ( fgets ( buffer, sizeof(buffer), *_archivo ) ) }
	{
		//printf("  Linea No: %d :", numero_linea );
		//parsear_entrada ( buffer, strlen(buffer) );
		//++numero_linea;
		//printf("\n");

		if ( !validar_final_linea ( buffer ) ) {
			strcpy ( cadena, "" );
		}

		

		char cadena[256];
		accion *lista = NULL;
		if( !leer_entrada_consola ( cadena ) ) {
			printf("\n\t Error: La cadena es demasiado grande para procesar.");
			continue;
		}

		analizar_entrada ( cadena, &lista );
		opcion = 

	}
}

inline int validar_final_linea ( char _cadena[] )
{
	int longitud = strlen ( _cadena );
	--longitud;
	while ( longitud != 0 )
	{
		switch(_cadena[longitud])
		{
			case '\n': case ' ': {
				--longitud;
			} break;
			case '/': {
				_cadena[longitud] = ' ';
				return true;
			} default: {
				return false;
			}
		}
	}
	return false;
}

#endif // BUFFER_ENTRADA_H