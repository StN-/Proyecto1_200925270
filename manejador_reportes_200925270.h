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
	printf("\n\tValidando Datos para la Creacion de Reportes.");

	char arg_path[32] = "";
	char arg_name[32] = "";
	if ( !buscar_id ( festplatten, _arg_id, arg_path, arg_name ) ) {
		printf( "\n\t[ERROR] : Error no existe el disco o la particion a montar.");
		return;
	}

	if ( !existe_archivo ( arg_path ) ) {
		printf( "\n\t[ERROR] : El archivo <<%s>> No exite.", arg_path );
		return;
	}

	switch(_arg_name) {
		case 1: {
			crear_reporte_mbr ( arg_path );

			int estado;
			char ejecutar[256] = "";
			concatenar ( ejecutar, 3, "dot -Tpng mbr.dot -o ", _arg_file, ".png" );
			system( ejecutar );
			wait(estado);

		} break;
		case 2: {
			crear_reporte_disk ( arg_path );

			int estado;
			char ejecutar[256] = "";
			concatenar ( ejecutar, 3, "dot -Tpng disk.dot -o ", _arg_file, ".png" );
			system( ejecutar );
			wait(estado);
		} break;
		default: {
		} break;
	}
}

#endif // MANEJADOR_REPORTES_H