//manejador_reportes_200925270.h
#ifndef MANEJADOR_REPORTES_H
#define MANEJADOR_REPORTES_H

/*
 *
 *
 *
 */

inline void verificar_creacion_particion ( char [], char [], int, char, char );

 /*
  *
  *
  *
  */

inline void verificar_creacion_reporte ( char _arg_file[], int _arg_name, char _arg_id[] )
{
	// char arg_path_dir[128] = "";
	// strcpy ( arg_path_dir, _arg_path );
	// char *sub_string = strrchr ( arg_path_dir, '/' );
	// reemplazar ( arg_path_dir, sub_string, "", strlen(sub_string) );
	// if ( !validar_directorio ( arg_path_dir ) ) {
	// 	printf( "   -Error : El direcotrio <<%s>> No exite.\n", arg_path_dir );
	// 	return;
	// }

	// if ( !validar_archivo ( _arg_path ) ) {
	// 	printf( "   -Error : El archivo <<%s>> No exite.\n", _arg_path );
	// 	return;
	// }

	// if ( existe_nombre_particion_disco_virtual ( _arg_path, _arg_name ) ) {
	// 	printf( "   -Error : Ya existe una particion con el nombre: <<%s>>.\n", _arg_name );
	// 	return;
	// }

	char arg_path[32] = "";
	char arg_name[32] = "";
	if ( !buscar_id ( festplatten, _arg_id, arg_path, arg_name ) ) {
		printf("\n\tError no existe el disco o la particion a montar.");
		return;
	}


	switch(_arg_name) {
		case 1: {
			crear_reporte_mbr ( arg_path, _arg_file );
			//verificar_creacion_reporte_mbr ( arg_path, _arg_file );
		} break;
		case 2: {
			//verificar_creacion_reporte_disk ( arg_path, arg_id );
		} break;
		default: {
			printf("\n\tError no existe el reporte.");
		} break;
		// case REPORTE_TIPO_TREE: {
		// 	verificar_creacion_reporte_tree ( arg_path, arg_id );
		// } break;
		// case REPORTE_TIPO_INODE: {
		// 	verificar_creacion_reporte_inode ( arg_path, arg_id );
		// } break;
		// case REPORTE_TIPO_BLOCK: {
		// 	verificar_creacion_reporte_block ( arg_path, arg_id );
		// } break;
		// case REPORTE_TIPO_SUPER: {
		// 	verificar_creacion_reporte_super ( arg_path, arg_id );
		// } break;
		// case REPORTE_TIPO_BM_INODE: {
		// 	verificar_creacion_reporte_bitmap ( arg_path, arg_id, 0 );
		// } break;
		// case REPORTE_TIPO_BM_BLOCK: {
		// 	verificar_creacion_reporte_bitmap ( arg_path, arg_id, 1 );
		// } break;
	}

	int estado;
	char ejecutar[256] = "";
	//crear_reporte_master_boot_record ( _arg_path );
	concatenar ( ejecutar, 2, "dot -Tpng mbr.dot -o ", "mbr.png" );
	system( ejecutar );
	wait(estado);
}

#endif // MANEJADOR_REPORTES_H