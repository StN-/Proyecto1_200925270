//mbr_200925270.h
//librerias_200925270.h
#ifndef MBR_H
#define MBR_H

#define FECHA_CREACION_MBR(s) ((s)->mbr_fecha_creacion)
#define NUMERO_MAGICO_MBR(s) ((s)->mbr_disk_signature)
#define PARTICION_MBR(s,i) ((s)->particion[i])
#define TAMANO_DISCO_MBR(s) ((s)->mbr_tamano)

struct master {
	unsigned int mbr_disk_signature;
	char mbr_fecha_creacion[24];
	unsigned int particion[4];
	unsigned int mbr_tamano;
};

typedef struct master master;

/*
 *
 *
 *
 */


/*
 *
 *
 *
 */

inline void generar_master_boot_record ( char _arg_path[], int _size )
{
	register int i = 0;
	unsigned int posicionamiento = 0;
	master *mbr = nuevo_master_boot_record ( _size );

	posicionamiento = sizeof( struct master);
	particion *nparticion = nueva_particion ();
	for ( ; i < 4; ++i ) {
		almacenar_registro_posicion_n ( _arg_path, nparticion, sizeof( struct particion ), posicionamiento );
		PARTICION_MBR( mbr, i ) = posicionamiento;
		posicionamiento += sizeof ( struct particion );
	}

	almacenar_registro_posicion_n ( _arg_path, mbr, sizeof( struct master ), 0 );
	free ( nparticion );
	free ( mbr );
}

static inline master *nuevo_master_boot_record ( int _tamano )
{
	master *nuevo = malloc ( sizeof( struct master) );
	PARTICION_MBR( nuevo, 0 ) = 0;
	PARTICION_MBR( nuevo, 1 ) = 0;
	PARTICION_MBR( nuevo, 2 ) = 0;
	PARTICION_MBR( nuevo, 3 ) = 0;
	TAMANO_DISCO_MBR( nuevo ) = _tamano;
	NUMERO_MAGICO_MBR( nuevo ) = 200925270;
	tiempo_actual( FECHA_CREACION_MBR ( nuevo ), 24 );
	return nuevo;
}


#endif // MBR_H