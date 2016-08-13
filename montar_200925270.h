//mountar_200925270.h
#ifndef MONTAR_H
#define MONTAR_H

/*
 *
 *
 *
 */

struct partition {
	struct partition *siguiente;
	char nombre[16];
	char id[5];
};

typedef struct partition partition;

struct festplatte {
	struct festplatte *siguiente;
	partition *partitionen;
	char ruta[128];
	int id;
};

typedef struct festplatte festplatte;

 /*
  *
  *
  *
  */

inline void montar_particion ( festplatte **, char [], char [] );
static inline void montar_partition ( partition **, char [], int, char );
static inline void montar_festplatte ( festplatte **, char [], char [], int, char );
static inline festplatte *neu_festplatte ( char [], int );
static inline partition *neu_partition ( char [], char [] );


inline void imprimir_particiones_montadas ( festplatte * );
static inline void imprimir_festplatten_montados ( festplatte * );
static inline void imprimir_partitionen_montadas ( partition * );


inline int buscar_id ( festplatte *, char [], char *, char * );
static inline int buscar_id_festplatte ( festplatte *, char [], char *, char * );
static inline int buscar_id_partition ( partition *, char [], char *, char * );

 /*
  *
  *
  *
  */


inline void montar_particion ( festplatte **_festplatten, char _arg_path[], char _arg_name[] ) {
	montar_festplatte ( _festplatten, _arg_path, _arg_name, 1, 'a' );
}
static inline void montar_festplatte ( festplatte **_festplatten, char _arg_path[], char _arg_name[], int _numero, char _letra )
{
	if ( (*_festplatten) == NULL ) {
		(*_festplatten) = neu_festplatte ( _arg_path, _numero );
		montar_partition ( &(*_festplatten)->partitionen, _arg_name, _numero, _letra );
	} else {
		if( strcmp((*_festplatten)->ruta, _arg_path ) == 0 )
			montar_partition ( &(*_festplatten)->partitionen, _arg_name, (*_festplatten)->id, _letra );
		else
			montar_festplatte ( &(*_festplatten)->siguiente, _arg_path, _arg_name, (*_festplatten)->id+1, _letra );
	}
}
static inline void montar_partition ( partition **_partitionen, char _arg_name[], int _numero, char _letra )
{
	if ( (*_partitionen) == NULL ) {
		char id[5] = "";
		sprintf( id, "vd%c%d", _letra, _numero );
		(*_partitionen) = neu_partition ( _arg_name, id );
	} else {
		if( strcmp((*_partitionen)->nombre, _arg_name ) != 0 )
			montar_partition ( &(*_partitionen)->siguiente, _arg_name, _numero, ++_letra );
		else
			printf("\n\tla particion ya esta montada.");
	}
}



inline int buscar_id ( festplatte *_festplatten, char _id[], char *_arg_path, char *_arg_name ) {
	return ( _festplatten == NULL ) ? false : buscar_id_festplatte ( _festplatten, _id, _arg_path, _arg_name );
}

static inline int buscar_id_festplatte ( festplatte *_festplatten, char _id[], char *_arg_path, char *_arg_name ) {
	if (_festplatten == NULL )
		return false;

	if ( buscar_id_partition ( _festplatten->partitionen, _id, _arg_path, _arg_name ) ) {
		strcpy ( _arg_path, _festplatten->ruta );
		return true;
	}

	return buscar_id_festplatte ( _festplatten->siguiente, _id, _arg_path, _arg_name );
}

static inline int buscar_id_partition ( partition *_partitionen, char _id[], char *_arg_path, char *_arg_name ) {
	if ( _partitionen == NULL )
		return false;

	if ( strcmp ( _partitionen->id, _id ) == 0 ) {
		strcpy ( _arg_name, _partitionen->id );
		return true;
	}

	return buscar_id_partition ( _partitionen->siguiente, _id, _arg_path, _arg_name );
}



inline void imprimir_particiones_montadas ( festplatte *_festplatten ) {
	printf("\n\t(Discos Montados:)");
	if ( _festplatten == NULL ) {
		printf("\n\t  (Lista Vacia)");
		return;
	}
	imprimir_festplatten_montados ( _festplatten );
}
static inline void imprimir_festplatten_montados ( festplatte *_festplatten ) {
	if ( _festplatten == NULL ) return;
	printf("\n\t  (Disco (%d) : %s)", _festplatten->id, _festplatten->ruta );
	imprimir_partitionen_montadas ( _festplatten->partitionen );
	imprimir_festplatten_montados ( _festplatten->siguiente );
}
static inline void imprimir_partitionen_montadas ( partition *_partitionen ) {
	if ( _partitionen == NULL )
		return;
	printf("\n\t    (Particion (%s) : %s)", _partitionen->id, _partitionen->nombre );
	imprimir_partitionen_montadas ( _partitionen->siguiente );
}



static inline festplatte *neu_festplatte ( char _arg_path[], int _numero ) {
   festplatte *neu = malloc ( sizeof( struct festplatte ) );
   strcpy( neu->ruta, _arg_path );
   neu->siguiente = NULL;
   neu->partitionen = NULL;
   neu->id = _numero;
   return neu;
}

static inline partition *neu_partition ( char _arg_name[], char _id[] ) {
   partition *neu = malloc ( sizeof( struct partition ) );
   strcpy( neu->nombre, _arg_name );
   strcpy( neu->id, _id );
   neu->siguiente = NULL;
   return neu;
}

#endif // MONTAR_H