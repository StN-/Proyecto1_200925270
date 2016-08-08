//parametro_200925270.h
#ifndef INSTRUCCION_H
#define INSTRUCCION_H

struct parametro {
	struct parametro *siguiente;
	char valor[128];
	int tipo;
};

typedef struct parametro parametro;

/*
 *
 *
 *
 */

void agregar_parametro ( parametro **, int, char [] );
static inline void insertar_parametro ( parametro **, parametro * );

int cantidad_parametros ( parametro * );
int buscar_parametro ( parametro **, int, char * );

static inline int obtener_parametro ( parametro **, char * );
static inline parametro *nuevo_parametro ( int, char [] );

/*
 *
 *
 *
 */

void agregar_parametro ( parametro **_lista, int _tipo, char _valor[] ) {
	insertar_parametro ( _lista, nuevo_parametro ( _tipo, _valor ) );
}

static inline void insertar_parametro ( parametro **_lista, parametro *_parametro ) {
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

static inline int obtener_parametro ( parametro **_lista, char *_buffer ) {
	parametro *eliminar = (*_lista);
	strcpy ( _buffer, (*_lista)->valor );
	(*_lista) = (*_lista)->siguiente;
	free ( eliminar );
	return 1;
}

static inline parametro *nuevo_parametro ( int _tipo, char _valor[] ) {
   parametro *nuevo = malloc ( sizeof( struct parametro ) );
   strcpy( nuevo->valor, _valor );
   nuevo->siguiente = NULL;
   nuevo->tipo = _tipo;
   return nuevo;
}

#endif // INSTRUCCION_H