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

 /*
 *
 *
 *
 */

inline void verificar_creacion_disco_virtual ( char _arg_path[], int _arg_size, int _tipo )
{
	// char arg_path[128] = "";
	// strcpy ( arg_path, _arg_path );

	//char *sub_string = strrchr ( arg_path_dir, '/' );

	// if ( !validar_directorio ( arg_path_dir ) ) {
	// 	int status = mkdir( arg_path_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
	// }

	// if ( validar_archivo ( _arg_path ) ) {
	// 	printf( "   -Error : El archivo <<%s>> Ya exite.\n", _arg_path );
	// 	return;
	// }

	creacion_disco_virtual ( _arg_path, (_arg_size * _tipo) );
	//crear_master_boot_record_disco_virtual ( _arg_path, (_arg_size * _tipo) );
}

inline void verificar_eliminacion_disco_virtual ( char _arg_path[] )
{
	// char arg_path_dir[128] = "";
	// strcpy ( arg_path_dir, _arg_path );
	
	// char *sub_string = strrchr ( arg_path_dir, '/' );

	// if ( !validar_directorio ( arg_path_dir ) ) {
	// 	printf( "   -Error : El direcotrio <<%s>> No exite.\n", arg_path_dir );
	// 	return;
	// }

	// if ( !validar_archivo ( _arg_path ) ) {
	// 	printf( "   -Error : El archivo <<%s>> No exite.\n", _arg_path );
	// 	return;
	// }

	eliminacion_disco_virtual ( _arg_path );
}

// inline void verificar_montar_disco ( char _arg_path[], char _arg_name[] )
// {
// 	char arg_path_dir[128] = "";
// 	strcpy ( arg_path_dir, _arg_path );
// 	char *sub_string = strrchr ( arg_path_dir, '/' );
// 	reemplazar ( arg_path_dir, sub_string, "", strlen(sub_string) );
// 	if ( !validar_directorio ( arg_path_dir ) ) {
// 		printf( "   -Error : El direcotrio <<%s>> No exite.\n", arg_path_dir );
// 		return;
// 	}

// 	if ( !validar_archivo ( _arg_path ) ) {
// 		printf( "   -Error : El archivo <<%s>> No exite.\n", _arg_path );
// 		return;
// 	}

// 	if ( !existe_nombre_particion_disco_virtual ( _arg_path, _arg_name ) ) {
// 		printf( "   -Error : La particion <<%s>> No exite dentro del archivo <<%s>>.\n", _arg_name, _arg_path );
// 		return;
// 	}

// 	if( existe_particion_disco_montado ( lista_discos, _arg_path, _arg_name ) ) {
// 		printf( "   -Advertencia : La particion <<%s>> Ya esta montada.\n", _arg_name );
// 		return;
// 	}

// 	montar ( &lista_discos, _arg_path, _arg_name );
// 	imprimir_discos_montados ( lista_discos );
// }

// inline void verificar_desmontar_disco ( char _arg_id[] )
// {
// 	if ( !buscar_disco_virtual_montado ( lista_discos, _arg_id ) ) {
// 		printf( "   -Error : El id <<%s>> No exite.\n", _arg_id );
// 	}

// 	//desmontarlo....
// }


#endif // MANEJADOR_DISCO_H