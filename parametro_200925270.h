//parametro_200925270.h
#ifndef PARAMETRO_H
#define PARAMETRO_H

struct parametro {
	struct parametro *siguiente;
	char valor[128];
	int tipo;
};

typedef struct parametro parametro;

enum TIPO_PARAMETRO {
	SIZE = 0,
	UNIT,
	PATH,
	NAME,
	TYPE,
	FIT,
	DELETE,
	ADD,
	ID,
	K,
	M,
	H,
	I,
	N,
	S,
	LINK
};

typedef enum TIPO_PARAMETRO TIPO_PARAMETRO;

/*
 *
 *
 *
 */

void agregar_parametro ( parametro **, int, char [] );
inline void insertar_parametro ( parametro **, parametro * );

int cantidad_parametros ( parametro * );
int buscar_parametro ( parametro **, int, char * );

static inline int obtener_parametro ( parametro **, char * );
inline parametro *nuevo_parametro ( int, char [] );

/*
 *
 *
 *
 */

void agregar_parametro ( parametro **_lista, int _tipo, char _valor[] ) {
	insertar_parametro ( _lista, nuevo_parametro ( _tipo, _valor ) );
}

inline void insertar_parametro ( parametro **_lista, parametro *_parametro ) {
	( (*_lista) == NULL ) ? (*_lista) = _parametro : insertar_parametro ( &(*_lista)->siguiente, _parametro );
}

int cantidad_parametros ( parametro *_lista ) {
	return ( _lista == NULL ) ? 0 : 1 + cantidad_parametros ( _lista->siguiente );
}

int buscar_parametro ( parametro **_lista, int _tipo, char *_buffer ) {
	return ( *_lista == NULL ) ? 0 : ( (*_lista)->tipo == _tipo ) ? 
		obtener_parametro ( _lista, _buffer ) : buscar_parametro ( &(*_lista)->siguiente, _tipo, _buffer );
}

// inline void imprimir_parametros ( accion *_lista ) {
// 	printf("   Lista De Particiones Montadas.\n");
// 	if ( _lista == NULL ) {
// 		printf("    -Vacia\n");
// 		return;
// 	}

// 	imprimir_lista_discos ( _lista );
// }

inline parametro *nuevo_parametro ( int _tipo, char _valor[] ) {
   parametro *nuevo = malloc ( sizeof( struct parametro ) );
   strcpy( nuevo->valor, _valor );
   nuevo->siguiente = NULL;
   nuevo->tipo = _tipo;
   return nuevo;
}

static inline int obtener_parametro ( parametro **_lista, char *_buffer ) {
	parametro *eliminar = (*_lista);
	strcpy ( _buffer, (*_lista)->valor );
	(*_lista) = (*_lista)->siguiente;
	free ( eliminar );
	return 1;
}

#endif // PARAMETRO_H