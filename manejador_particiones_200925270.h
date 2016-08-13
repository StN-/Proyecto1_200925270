//manejador_particiones_200925270.h
#ifndef MANEJADOR_PARTICIONES_H
#define MANEJADOR_PARTICIONES_H

/*
 *
 *
 *
 */

inline void verificar_creacion_particion ( char [], char [], int, char, char );
static inline void crear_logica ( char [], char [], int, char, char );
static inline void crear_primaria_extendida ( char [], char [], int, char, char );

inline void verificar_eliminacion_particion ( char [], char [], char );
static inline void eliminar_primaria_extendida ( char [], char [], char );
static inline int eliminar_logica ( char [], char [], int, int );
// inline void verificar_modificacion_particion ( char [], char [], int );



//static inline int verificar_localidad_particion ( particion [] );
static inline int verificar_nombre_particion ( particion [], char [] );
static inline int verificar_particion_extendida ( particion [] );
static inline int verificar_calcular_posicion_particion ( particion [], int, int, int );

/*
 *
 *
 *
 */

inline void verificar_creacion_particion ( char _arg_path[], char _arg_name[], int _arg_size, char _arg_type, char _arg_fit )
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

	if ( _arg_type == 'L' )
		crear_logica ( _arg_path, _arg_name, _arg_size, _arg_type, _arg_fit );
	else
		crear_primaria_extendida ( _arg_path, _arg_name, _arg_size, _arg_type, _arg_fit );

	// int validar_asignacion = 0;
	// int espacio_disponible = 0;
	// espacio_disponible = validar_asignar_nueva_particion ( &validar_asignacion, _arg_path, _arg_size, _arg_name, _arg_type, _arg_fit );
	// if ( !validar_asignacion ) {
	// 	printf( "   -Error : No hay espacio suficiente para asignar la partida: <<%d>>.\n", espacio_disponible );
	// 	return;
	// }
}

inline void verificar_eliminacion_particion ( char _arg_path[], char _arg_name[], char _arg_type )
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

	eliminar_primaria_extendida ( _arg_path, _arg_name, _arg_type );
}

inline void verificar_modificacion_particion ( char _arg_path[], char _arg_name[], int _arg_add )
{

}

static inline void crear_primaria_extendida ( char _arg_path[], char _arg_name[], int _arg_size, char _arg_type, char _arg_fit )
{
	master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	if(DEPURADOR)
		printf("\n\t(Validando tamano de la particion menor al disco.)");

	if ( _arg_size >= TAMANO_DISCO_MBR( mbr ) ) {
		printf("\n\tla particion es mayor al tamano del disco.");
		return;
	}

	if ( _arg_type == 'E' ) {
		if(DEPURADOR)
			printf("\n\t(Validando si ya hay una particion extentida.)");

		if ( verificar_particion_extendida ( mbr->mbr_partition ) ) {
			printf("\n\tya exite particion extendida.");
			free ( mbr );
			return;
		}
	}

	if(DEPURADOR)
		printf("\n\t(Validando que no hay otra particion con el mismo nombre.)");

	if ( verificar_nombre_particion ( mbr->mbr_partition, _arg_name ) ) {
		printf("\n\tya exite particion con ese nombre.");
		if(DEPURADOR)
			printf("\n\t(7.3)");
		free ( mbr );
		return;
	}

	if(DEPURADOR)
		printf("\n\t(Validando la ubicacion y posicion de la particion.)");

	int i = 0;
	int posicion_inicial = sizeof ( struct master );
	for (; i < 4; ++i)
	{
		if(DEPURADOR)
			printf("\n\t(Particion: %d)", i);

		if(DEPURADOR)
			printf("\n\t(Posicion Inicial: %d)", posicion_inicial );

		if ( ESTADO_PARTICION( mbr->mbr_partition[i] ) != '0' ) {
			posicion_inicial = POSICION_PARTICION( mbr->mbr_partition[i] ) + TAMANO_PARTICION( mbr->mbr_partition[i] );
			continue;
		}

		int posicion_limite = verificar_calcular_posicion_particion ( mbr->mbr_partition, _arg_size, i + 1, TAMANO_DISCO_MBR( mbr ) );

		if(DEPURADOR)
			printf("\n\t(Posicion Inicial + Tamano: %d)", (posicion_inicial + _arg_size) );

		if(DEPURADOR)
			printf("\n\t(Posicion limite: %d)", posicion_limite);		

		if ( posicion_inicial + _arg_size <= posicion_limite )
		{
			if(DEPURADOR)
				printf("\n\t(Asignando la nueva particion.)");

			POSICION_PARTICION ( mbr->mbr_partition[i] ) = posicion_inicial;
			strcpy( NOMBRE_PARTICION ( mbr->mbr_partition[i] ), _arg_name );			
			TIPO_AJUSTE_PARTICION ( mbr->mbr_partition[i] ) = _arg_fit;
			TAMANO_PARTICION ( mbr->mbr_partition[i] ) = _arg_size;
			TIPO_PARTICION ( mbr->mbr_partition[i] ) = _arg_type;
			ESTADO_PARTICION ( mbr->mbr_partition[i] ) = '1';

			if ( _arg_type == 'E' ) {
				if(DEPURADOR)
					printf("\n\t(Asignar el ebr.(PENDIENTE))");
			}

			almacenar_registro_posicion_n ( _arg_path, mbr, sizeof( struct master ), 0 );
			free ( mbr );
			return;
		}

		posicion_inicial = POSICION_PARTICION( mbr->mbr_partition[i] ) + TAMANO_PARTICION( mbr->mbr_partition[i] );
	}

	if ( i == 4 ) {
		printf("\n\tno exite espacio para la particion.");
	}

	free ( mbr );
}

static inline void eliminar_primaria_extendida ( char _arg_path[], char _arg_name[], char _arg_type )
{
	master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	if(DEPURADOR)
		printf("\n\t(Validando que haya una particion con el nombre indicado.)");

	int i = 0;
	for (; i < 4; ++i)
	{
		if ( strcmp ( NOMBRE_PARTICION( mbr->mbr_partition[i] ), _arg_name ) == 0 )
		{
			if(DEPURADOR)
				printf("\n\t(Borrando Datos de la particion.)");

			if ( _arg_type == 'C' ) {
				if(DEPURADOR)
					printf("\n\t(Buscar la posicion y agregar los bloques.(PENDIENTE))");
			}

			strcpy( NOMBRE_PARTICION ( mbr->mbr_partition[i] ), "" );			
			TIPO_AJUSTE_PARTICION ( mbr->mbr_partition[i] ) = '0';
			POSICION_PARTICION ( mbr->mbr_partition[i] ) = 0;
			ESTADO_PARTICION ( mbr->mbr_partition[i] ) = '0';
			TAMANO_PARTICION ( mbr->mbr_partition[i] ) = 0;
			TIPO_PARTICION ( mbr->mbr_partition[i] ) = '0';
			
			almacenar_registro_posicion_n ( _arg_path, mbr, sizeof( struct master ), 0 );
			free ( mbr );
			return;
		}

		if ( TIPO_PARTICION ( mbr->mbr_partition[i] ) == 'E' ) {
			if( eliminar_logica ( _arg_path, _arg_name, 0, POSICION_PARTICION ( mbr->mbr_partition[i] ) ) ) {
				free ( mbr );
				return;
			}
		}
	}

	if ( i == 4 ) {
		printf("\n\tno exite la particion a eliminar.");
	}

	free ( mbr );
}

static inline int eliminar_logica ( char _arg_path[], char _arg_name[], int _indice, int _arg_pos )
{
	// if ( _arg_pos == -1 )
	// 	return false;

	// extend *ebr = recuperar_registro( _arg_path, sizeof( struct extend ), _arg_pos );
	// if ( strcmp( NOMBRE_EBR( ebr ), _arg_name ) == 0 )
	// {
	// 	// preguntar si desea eliminar la particion...
	// 	printf("   La particion <<%s>>, ha sido eliminada exitosamente.\n", _arg_name );
	// 	_arg_pos = SIGUIENTE_EBR ( ebr );
	// } 
	// else 
	// {
	// 	eliminar_logica ( _arg_path, _arg_name, SIGUIENTE_EBR( ebr ) );
	// 	almacenar_registro_posicion_n ( _arg_path, ebr, sizeof( struct extend ), _arg_pos );
	// } 

	// free ( ebr );
}

static inline void crear_logica ( char _arg_path[], char _arg_name[], int _arg_size, char _arg_type, char _arg_fit )
{

}


static inline int verificar_nombre_particion ( particion _particion[], char _arg_name[] )
{
	int i = 0;
	for ( ; i < 4; ++i )
		if ( strcmp ( NOMBRE_PARTICION( _particion[i] ), _arg_name ) == 0 )
			return true;
	return false;
}

static inline int verificar_particion_extendida ( particion _particion[] )
{
	int i = 0;
	for ( ; i < 4; ++i )
		if ( TIPO_PARTICION( _particion[i] ) == 'E' )
			return true;
	return false;
}

static inline int verificar_calcular_posicion_particion ( particion _particion[], int _arg_size, int _posicion, int _size_disk )
{
	int i = _posicion;
	for ( ; i < 4; ++i ) {
		if ( ESTADO_PARTICION( _particion[i] ) != '0' )
			return POSICION_PARTICION( _particion[i] );
	}
	return _size_disk;
}

#endif // MANEJADOR_PARTICIONES_H