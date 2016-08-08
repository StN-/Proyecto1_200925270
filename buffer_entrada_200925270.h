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
		printf("\n\t(Todo Concatenado: %s)\n", entrada);
	return true;
}

static inline int validar_final_linea ( char _cadena[] )
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