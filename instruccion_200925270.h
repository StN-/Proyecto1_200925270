//instruccion_200925270.h
#ifndef INSTRUCCION_H
#define INSTRUCCION_H

struct accion {
	struct parametro *parametros;
	struct accion *siguiente;
	int tipo;
};

typedef struct accion accion;

/*
 *
 *
 *
 */

void agregar_instruccion ( accion **, int, parametro ** );
static inline void insertar_instruccion ( accion **, accion * );

inline accion *obtener_siguiente_instruccion ( accion ** );
static inline accion *pop_instruccion ( accion ** );

static inline accion *nueva_instruccion ( int, parametro ** );
inline int cantidad_instrucciones ( accion * );

/*
 *
 *
 *
 */

void agregar_instruccion ( accion **_lista, int _tipo, parametro **_lista_parametros ) {
	insertar_instruccion ( accion **_lista, nueva_instruccion ( _tipo, _lista_parametros ) );
}

static inline void insertar_instruccion ( accion **_lista, accion *_instruccion ) {
	( (*_lista) == NULL ) ? (*_lista) = _instruccion : insertar_instruccion ( &(*_lista)->siguiente, _instruccion );
}

inline accion *obtener_siguiente_instruccion ( accion **_lista ) { 
	return ( *_lista == NULL ) ? NULL : pop_instruccion ( _lista );
}

static inline accion *pop_instruccion ( accion **_lista ) { 
	accion *temp = *_lista;
	(*_lista) = (*_lista)->siguiente;
	return temp;
}

// inline void imprimir_instrucciones ( accion *_lista ) {
// 	printf("   Lista De Particiones Montadas.\n");
// 	if ( _lista == NULL ) {
// 		printf("    -Vacia\n");
// 		return;
// 	}

// 	imprimir_lista_discos ( _lista );
// }

inline int cantidad_instrucciones ( accion *_lista ) {
	return ( _lista == NULL ) ? 0 : 1 + cantidad_instrucciones ( _lista->siguiente );
}

static inline accion *nueva_instruccion ( int _tipo, parametro **_lista ) {
   accion *nueva = malloc ( sizeof( struct accion ) );
   nueva->parametros = (*_lista);
   nueva->siguiente = NULL;
   nueva->tipo = _tipo;
   return nueva;
}

#endif // INSTRUCCION_H