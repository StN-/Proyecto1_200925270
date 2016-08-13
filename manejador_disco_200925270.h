//manejador_disco_200925270.h
#ifndef MANEJADOR_DISCO_H
#define MANEJADOR_DISCO_H

/*
 *
 *
 *
 */

inline void verificar_creacion_disco_virtual ( char [], int, int );
inline void verificar_eliminacion_disco_virtual ( char [] );
extern festplatte *festplatten;

 /*
 *
 *
 *
 */

inline void verificar_creacion_disco_virtual ( char _arg_path[], int _arg_size, int _tipo )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Manejador de Disco)");
	printf("\n\tValidando Datos para la creacion de Disco.");

	if ( existe_archivo ( _arg_path ) ) {
		printf( "\n\t[ERROR] : El archivo <<%s>> Ya exite.", _arg_path );
		return;
	}

	creacion_disco_virtual ( _arg_path, (_arg_size * _tipo) );
	generar_master_boot_record ( _arg_path, (_arg_size * _tipo) );
	if(DEPURADOR)
		imprimir_mbr ( _arg_path );
}

inline void verificar_eliminacion_disco_virtual ( char _arg_path[] )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Manejador de Disco)");
	printf("\n\tValidando Datos para la eliminacion de Disco.");

	if ( !existe_archivo ( _arg_path ) ) {
		printf( "\n\t[ERROR] : El archivo <<%s>> No exite.", _arg_path );
		return;
	}

	eliminacion_disco_virtual ( _arg_path );
}

inline void verificar_montar_disco ( char _arg_path[], char _arg_name[] )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Manejador de Disco)");
	printf("\n\tValidando Datos para montar particion.");

	if ( !existe_archivo ( _arg_path ) ) {
		printf( "\n\t[ERROR] : El archivo <<%s>> No exite.", _arg_path );
		return;
	}

	master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	if ( !verificar_nombre_particion ( _arg_path, mbr->mbr_partition, _arg_name ) ) {
		printf( "\n\t[ERROR] : No existe la particion con el nombre <<%s>>.", _arg_name );
		free ( mbr );
		return;
	}

	free ( mbr );

	montar_particion ( &festplatten, _arg_path, _arg_name );

	if(DEPURADOR)
		imprimir_particiones_montadas ( festplatten );
}

// inline void verificar_desmontar_disco ( char _arg_id[] )
// {
// 	if ( !buscar_disco_virtual_montado ( lista_discos, _arg_id ) ) {
// 		printf( "   -Error : El id <<%s>> No exite.\n", _arg_id );
// 	}

// 	//desmontarlo....
// }


#endif // MANEJADOR_DISCO_H