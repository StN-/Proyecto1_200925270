//instruccion_200925270.h
#ifndef INSTRUCCION_H
#define INSTRUCCION_H

struct accion {
	struct parametro *parametros;
	struct accion *siguiente;
	int tipo;
};

typedef struct accion accion;

enum TIPO_ACCION {
	MKDISK = 0,
	RMDISK,
	EXEC,
	FDISK,
	MOUNT,
	UNMOUNT,
	REP,
	EXIT
};

typedef enum TIPO_ACCION TIPO_ACCION;

/*
 *
 *
 *
 */

void agregar_accion ( accion **, int );
void agregar_instruccion ( accion **, int, parametro ** );
inline void insertar_instruccion ( accion **, accion * );

inline accion *obtener_siguiente_instruccion ( accion ** );
static inline accion *pop_instruccion ( accion ** );

static inline accion *nueva_instruccion ( int, parametro ** );
inline int cantidad_instrucciones ( accion * );
static inline accion *nueva_accion ( int );

inline void imprimir_instrucciones ( accion * );
static inline void imprimir_lista_instrucciones ( accion * );

/*
 *
 *
 *
 */

void agregar_instruccion ( accion **_lista, int _tipo, parametro **_lista_parametros ) {
	insertar_instruccion ( _lista, nueva_instruccion ( _tipo, _lista_parametros ) );
}

void agregar_accion ( accion **_lista, int _tipo ) {
	insertar_instruccion ( _lista, nueva_accion ( _tipo ) );
}

inline void insertar_instruccion ( accion **_lista, accion *_instruccion ) {
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

inline void imprimir_instrucciones ( accion *_lista ) {
	printf("\n");
	printf("\n\t(Instrucciones:)");
	if ( _lista == NULL ) {
		printf("\n\t  (Lista Vacia)");
		return;
	}
	imprimir_lista_instrucciones ( _lista );
	printf("\n");
}

static inline void imprimir_lista_instrucciones ( accion *_lista ) {
	if (_lista == NULL) return;
	printf("\n\t  (Instruccion -> tipo: %d)", _lista->tipo );
	imprimir_lista_parametros ( _lista->parametros );
	imprimir_lista_instrucciones ( _lista->siguiente );
}

inline int cantidad_instrucciones ( accion *_lista ) {
	return ( _lista == NULL ) ? 0 : 1 + cantidad_instrucciones ( _lista->siguiente );
}

inline accion *nueva_accion ( int _tipo ) {
   accion *nueva = malloc ( sizeof( struct accion ) );
   nueva->parametros = NULL;
   nueva->siguiente = NULL;
   nueva->tipo = _tipo;
   return nueva;
}

inline accion *nueva_instruccion ( int _tipo, parametro **_lista ) {
   accion *nueva = malloc ( sizeof( struct accion ) );
   nueva->parametros = (*_lista);
   nueva->siguiente = NULL;
   nueva->tipo = _tipo;
   return nueva;
}

#endif // INSTRUCCION_H