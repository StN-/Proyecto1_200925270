//funciones_200925270.h
#ifndef FUNCION_H
#define FUNCION_H

/*
 *
 *
 *
 */

// inline int validar_directorio ( char [] );
// inline int validar_archivo ( char [] );

void concatenar ( char *, int _cantidad, ... );

// inline void tiempo_actual( char *, int );

// void imprimir_v1 ( const char *, ... );
// void imprimir_v2 ( int, ... );

void leer_entrada_formato_cadena ( char *, const char * );
int leer_entrada_formato_decimal ( const char *, int );

// int validar_formato_numerico ( int *, char [] );
void convertir_minusculas ( char *, char [] );

inline void reemplazar ( char *, char [], char [], int );

/*
 *
 *
 *
 */

// void imprimir_v1 ( const char *_contenido, ... ) {
// 	va_list listado;	
//     va_start( listado, _contenido );
// 	vprintf( _contenido, listado );
//     va_end( listado );
// }

// void imprimir_v2 ( int _cantidad, ... ) {
// 	int i =	 0;
// 	va_list vl;
// 	char entrada[256];
// 	va_start(vl,_cantidad);
// 	for ( ;i < _cantidad; ++i ) {
// 		strcpy( entrada, va_arg( vl, char * ) );
// 		printf( "\n\t%s", entrada );
// 	}
// 	va_end(vl);
// }

void concatenar ( char *_buffer, int _cantidad, ... ) {
	int i =	 0;
	va_list vl;
	char cadena[128];
	va_start(vl,_cantidad);
	for (;i < _cantidad; ++i) {
		strcpy( cadena, va_arg( vl, char * ) );
		strcat( _buffer, cadena );
	}
	va_end(vl);
}

inline void reemplazar ( char *_buffer, char _sub_cadena[], char _contenido[], int _espacio ) {
	char *buffer = strstr( _buffer, _sub_cadena );
	strncpy ( buffer, _contenido, _espacio );
}

// inline int validar_directorio ( char _ruta[] ) {
// 	struct stat st = {0};
// 	return (stat ( _ruta, &st )==-1)?0:1;
// }

// inline int validar_archivo ( char _ruta[] ) {
// 	return (access( _ruta, F_OK )==-1)?0:1;
// }

// inline void tiempo_actual( char *_fecha, int _tamano )
// {
//     time_t ahorita;
//     time( &ahorita );
//     strncpy( _fecha, ctime(&ahorita), _tamano -1 );
//     _fecha[_tamano-1] = '\0';
// }

int leer_entrada_formato_decimal ( const char *_info, int _valor ) {
	char entrada[5];
	printf("%s", _info);
	if( fgets( entrada, sizeof( entrada ), stdin ) )
		sscanf( entrada, "%d", &_valor );
	return _valor;
}

void leer_entrada_formato_cadena ( char *_buffer, const char *_info ) {
	printf("%s", _info);
	char entrada[128];
	if( fgets( entrada, sizeof( entrada ), stdin ) )
		sscanf( entrada, "%[^\n]", _buffer );
}

// int validar_formato_numerico ( int *_valor, char _cadena[] )
// {
// 	int i = 0; 
// 	for ( ; i < strlen( _cadena ); ++i ) {
// 		if ( _cadena[i] != '-' && _cadena[i] != '+' )
// 			if ( !isdigit(_cadena[i]) )
// 				return 0;
// 	}

// 	sscanf( _cadena, "%d", _valor );
// 	return 1;
// }

void convertir_minusculas ( char *_cadena_min, char _cadena_may[] )
{
	int i = 0;
	char buffer[128] = "";
	for ( ; i < strlen ( _cadena_may ); ++i )
		buffer[i] = (char) tolower ( _cadena_may[i] );
  strcpy ( _cadena_min, buffer );
}

#endif // FUNCION_H