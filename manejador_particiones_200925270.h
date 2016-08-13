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

inline void verificar_modificacion_particion ( char [], char [], int );
static inline void modificar_particion ( char [], char [], int );



//static inline int verificar_localidad_particion ( particion [] );
static inline int verificar_nombre_particion ( char [], particion [], char [] );
static inline int verificar_particion_extendida ( particion [] );
static inline int verificar_calcular_posicion_particion ( particion [], int, int, int );

/*
 *
 *
 *
 */

inline void verificar_creacion_particion ( char _arg_path[], char _arg_name[], int _arg_size, char _arg_type, char _arg_fit )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Manejador de Particiones)");
	printf("\n\tValidando Datos para la Creacion de la Particion.");

	if ( !existe_archivo ( _arg_path ) ) {
		printf( "\n\t[ERROR] : El archivo <<%s>> No exite.", _arg_path );
		return;
	}

	if ( _arg_type == 'L' )
		crear_logica ( _arg_path, _arg_name, _arg_size, _arg_type, _arg_fit );
	else
		crear_primaria_extendida ( _arg_path, _arg_name, _arg_size, _arg_type, _arg_fit );
}

inline void verificar_eliminacion_particion ( char _arg_path[], char _arg_name[], char _arg_type )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Manejador de Particiones)");
	printf("\n\tValidando Datos para la Eliminacion de la Particion.");

	if ( !existe_archivo ( _arg_path ) ) {
		printf( "\n\t[ERROR] : El archivo <<%s>> No exite.", _arg_path );
		return;
	}

	eliminar_primaria_extendida ( _arg_path, _arg_name, _arg_type );
}

inline void verificar_modificacion_particion ( char _arg_path[], char _arg_name[], int _arg_add )
{
	if(DEPURADOR)
		printf("\n\t(Entrada Del Manejador de Particiones)");
	printf("\n\tValidando Datos para la Modificacion de la Particion.");

	if ( !existe_archivo ( _arg_path ) ) {
		printf( "\n\t[ERROR] : El archivo <<%s>> No exite.", _arg_path );
		return;
	}

	modificar_particion ( _arg_path, _arg_name, _arg_add );
}

static inline void modificar_particion ( char _arg_path[], char _arg_name[], int _arg_size )
{

}

static inline void crear_primaria_extendida ( char _arg_path[], char _arg_name[], int _arg_size, char _arg_type, char _arg_fit )
{
	master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	if ( _arg_size >= TAMANO_DISCO_MBR( mbr ) ) {
		printf( "\n\t[ERROR] : El Tamano de la Particion es Mayor al Tamano del Disco.");
		free ( mbr );
		return;
	}

	if ( _arg_size < (2 * KiB) ) {
		printf( "\n\t[ERROR] : El Tamano Minimo de la Particion es de 2 KiB.");
		free ( mbr );
		return;
	}

	if ( _arg_type == 'E' ) {
		if(DEPURADOR)
			printf("\n\t(Validando si ya hay una particion extentida.)");

		if ( verificar_particion_extendida ( mbr->mbr_partition ) ) {
			printf( "\n\t[ERROR] : Ya Existe una Particion Extentida Asignada." );
			free ( mbr );
			return;
		}
	}

	if(DEPURADOR)
		printf("\n\t(Validando que no hay otra particion con el mismo nombre.)");

	if ( verificar_nombre_particion ( _arg_path, mbr->mbr_partition, _arg_name ) ) {
		printf( "\n\t[ERROR] : Ya Existe una Particion con el nombre <<%s>>.", _arg_name );
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

			if ( _arg_type == 'E' )
			{
				if(DEPURADOR)
					printf("\n\t(Asignando el EBR de la Particion Extendida.)");
				extend *ebr = nuevo_extend_boot_record ();
				almacenar_registro_posicion_n ( _arg_path, ebr, sizeof( struct extend ), posicion_inicial );
				free( ebr );
			}

			almacenar_registro_posicion_n ( _arg_path, mbr, sizeof( struct master ), 0 );
			free ( mbr );
			return;
		}

		posicion_inicial = POSICION_PARTICION( mbr->mbr_partition[i] ) + TAMANO_PARTICION( mbr->mbr_partition[i] );
	}

	printf( "\n\t[ERROR] : No Existe Suficiente Espacio para Asignar la Particion <<%s>>.", _arg_name );
	free ( mbr );
}

static inline void crear_logica ( char _arg_path[], char _arg_name[], int _arg_size, char _arg_type, char _arg_fit )
{
	master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	if ( _arg_size >= TAMANO_DISCO_MBR( mbr ) ) {
		printf( "\n\t[ERROR] : El Tamano de la Particion es Mayor al Tamano del Disco.");
		free ( mbr );
		return;
	}

	if ( _arg_size < (2 * KiB) ) {
		printf( "\n\t[ERROR] : El Tamano Minimo de la Particion es de 2 KiB.");
		free ( mbr );
		return;
	}

	if ( !verificar_particion_extendida ( mbr->mbr_partition ) ) {
		printf( "\n\t[ERROR] : No Existe una Particion Extentida Asignada." );
		free ( mbr );
		return;
	}

	int i = 0;
	for (; i < 4; ++i)
		if ( TIPO_PARTICION ( mbr->mbr_partition[i] ) == 'E' )
			break;

	int posicion = POSICION_PARTICION ( mbr->mbr_partition[i] );
	while ( posicion != -1 ) {
		extend *ebr = recuperar_registro ( _arg_path, sizeof( struct extend ), POSICION_PARTICION ( mbr->mbr_partition[i] ) );

		if(DEPURADOR)
			printf("\n\t(Posicion EBR: %d)", posicion);

		if ( ESTADO_EBR( ebr ) != '0' ) {
			posicion = SIGUIENTE_EBR( ebr );
			free ( ebr );
			continue;
		}

		int posicion_inicial = posicion + sizeof ( struct extend );
		int posicion_limite = POSICION_PARTICION ( mbr->mbr_partition[i] ) + TAMANO_PARTICION( mbr->mbr_partition[i] );

		if(DEPURADOR)
			printf("\n\t(Posicion Inicial + Tamano + ebr: %d)", ( posicion_inicial + _arg_size +  (int)(sizeof ( struct extend )) ) );

		if(DEPURADOR)
			printf("\n\t(Posicion limite: %d)", posicion_limite);	

		if ( ( posicion_inicial  + _arg_size + sizeof ( struct extend ) ) > posicion_limite ) {
			free ( ebr );
			break;
		}

		SIGUIENTE_EBR( ebr ) = posicion_inicial + _arg_size;
		POSICION_EBR( ebr ) = posicion_inicial;
		strcpy( NOMBRE_EBR( ebr ), _arg_name );
		TAMANO_EBR( ebr ) = _arg_size;
		AJUSTE_EBR( ebr ) = _arg_fit;
		ESTADO_EBR( ebr ) = '1';

		if(DEPURADOR)
			printf( "\n\t(Posicion EBR Siguiente: %d)", SIGUIENTE_EBR( ebr ) );

		extend *ebr_sig = nuevo_extend_boot_record ();
		almacenar_registro_posicion_n ( _arg_path, ebr_sig, sizeof( struct extend ), SIGUIENTE_EBR( ebr ) );
		free( ebr_sig );

		almacenar_registro_posicion_n ( _arg_path, ebr, sizeof( struct extend ), posicion );
		free ( ebr );

			if(DEPURADOR)
				printf("\n\t(Asignando la nueva particion logica.)");

		free ( mbr );
		return;
	}

	printf( "\n\t[ERROR] : No Existe Suficiente Espacio para Asignar la Particion <<%s>>.", _arg_name );
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

		if ( TIPO_PARTICION ( mbr->mbr_partition[i] ) == 'E' )
		{
			if( eliminar_logica ( _arg_path, _arg_name, 0, POSICION_PARTICION ( mbr->mbr_partition[i] ) ) ) {
				free ( mbr );
				return;
			}
		}
	}

	printf( "\n\t[ERROR] : No Existe la Particion con el nombre <<%s>>.", _arg_name );
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

static inline int verificar_nombre_particion ( char _arg_path[], particion _particion[], char _arg_name[] )
{
	int i = 0;
	for ( ; i < 4; ++i ) 
	{
		if ( strcmp ( NOMBRE_PARTICION( _particion[i] ), _arg_name ) == 0 )
			return true;

		if ( TIPO_PARTICION( _particion[i]) == 'E' )
		{
			int posicion = POSICION_PARTICION ( _particion[i] );
			while ( posicion != -1 )
			{
				extend *ebr = recuperar_registro ( _arg_path, sizeof( struct extend ), POSICION_PARTICION ( _particion[i] ) );

				if ( strcmp ( NOMBRE_EBR( ebr ), _arg_name ) == 0 ) {
					free ( ebr );
					return true;
				}
				posicion = SIGUIENTE_EBR( ebr );
				free ( ebr );
			}
		}
	}
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