//particion_200925270.h
#ifndef PARTICION_H
#define PARTICION_H

/*
 *
 *
 *
 */

#define TIPO_AJUSTE_PARTICION(s) ((s)->part_fit)
#define POSICION_PARTICION(s) ((s)->part_start)
#define ESTADO_PARTICION(s) ((s)->part_status)
#define NOMBRE_PARTICION(s) ((s)->part_name)
#define TAMANO_PARTICION(s) ((s)->part_size)
#define TIPO_PARTICION(s) ((s)->part_type)

struct particion {
	unsigned int part_start;
	unsigned int part_size;
	char part_name[16];
	char part_status;
	char part_type;
	char part_fit;
};

typedef struct particion particion;

/*
 *
 *
 *
 */

inline particion *nueva_particion_vacia ();
inline particion *nueva_particion ( char [], char, char );


/*
 *
 *  METODO PARA IMPRIMIR LA PARTICION...
 *
 */


inline particion *nueva_particion_vacia () {
	particion *nueva = malloc ( sizeof( struct particion ) );
	strcpy ( NOMBRE_PARTICION( nueva ), "" );
	TIPO_AJUSTE_PARTICION( nueva ) = '0';
	POSICION_PARTICION( nueva )  = 0;
	ESTADO_PARTICION ( nueva ) = '0';
	TIPO_PARTICION( nueva ) = '0';
	TAMANO_PARTICION( nueva ) = 0;
	return nueva;
}

inline particion *nueva_particion ( char _nombre[], char _tipo, char _ajuste ) {
	particion *nueva = malloc ( sizeof( struct particion ) );
	strcpy ( NOMBRE_PARTICION ( nueva ), _nombre );
	TIPO_AJUSTE_PARTICION ( nueva ) = _ajuste;
	POSICION_PARTICION ( nueva )  = 0;
	ESTADO_PARTICION ( nueva ) = '0';
	TIPO_PARTICION ( nueva ) = _tipo;
	TAMANO_PARTICION ( nueva ) = 0;
	return nueva;
}

#endif // PARTICION_H