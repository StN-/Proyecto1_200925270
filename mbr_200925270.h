//mbr_200925270.h
#ifndef MBR_H
#define MBR_H

/*
 *
 *
 *
 */

#define PARTICION_MBR(s,i) ((s)->mbr_partition[i])
#define FECHA_CREACION_MBR(s) ((s)->mbr_fecha_creacion)
#define NUMERO_MAGICO_MBR(s) ((s)->mbr_disk_signature)
#define TAMANO_DISCO_MBR(s) ((s)->mbr_tamano)

struct master {
	unsigned int mbr_disk_signature;
	char mbr_fecha_creacion[24];
	particion mbr_partition[4];
	unsigned int mbr_tamano;
};

typedef struct master master;

/*
 *
 *
 *
 */

inline void generar_master_boot_record ( char [], int );
static inline master *nuevo_master_boot_record ( int );

/*
 *
 *
 *
 */

inline void generar_master_boot_record ( char _arg_path[], int _size )
{
	register int i = 0;
	master *mbr = nuevo_master_boot_record ( _size );

	for ( ; i < 4; ++i )
		PARTICION_MBR( mbr, i) = nueva_particion_vacia ();

	almacenar_registro_posicion_n ( _arg_path, mbr, sizeof( struct master ), 0 );
	free ( mbr );
}

inline void imprimir_mbr ( char _arg_path[] )
{
	master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	printf("\n\t(Tamano: %d)", TAMANO_DISCO_MBR ( mbr ) );
	printf("\n\t(Fecha: %s)", FECHA_CREACION_MBR ( mbr ) );
	printf("\n\t(Numero Magico: %d)", NUMERO_MAGICO_MBR ( mbr ) );

	int i = 0;
	for ( ; i < 4; ++i)
	{
		printf("\n\t (Localidad: %d)", i );
		printf("\n\t (Posicion: %d)", POSICION_PARTICION ( PARTICION_MBR( mbr, i) ) );
		printf("\n\t (Tipo Particion: %c)", TIPO_PARTICION ( PARTICION_MBR( mbr, i) ) );
		printf("\n\t (Status Particion: %c)", ESTADO_PARTICION ( PARTICION_MBR( mbr, i) ) );
		printf("\n\t (Tamano Particion: %d)", TAMANO_PARTICION ( PARTICION_MBR( mbr, i) ) );
		printf("\n\t (Nombre Particion: %s)", NOMBRE_PARTICION ( PARTICION_MBR( mbr, i) ) );
		printf("\n\t (Tipo Ajuste Particion: %c)", TIPO_AJUSTE_PARTICION ( PARTICION_MBR( mbr, i) ) );
		printf("\n");

		if ( TIPO_PARTICION( PARTICION_MBR( mbr, i) ) == 'E' )
		{
			// int posicion_logica = POSICION_PARTICION( nparticion );
			// extend *ebr = recuperar_registro( _arg_path, sizeof( struct extend ), posicion_logica );
			// do {

			// 	printf("       Ubicacion: %d\n", posicion_logica );
			// 	printf("       Posicion de la particion en el disco: %d\n", POSICION_PARTICION ( ebr ) );
			// 	printf("       Siguiente Particion: %d\n", SIGUIENTE_PARTICION ( ebr ) );
			// 	printf("       Status Particion: %c\n", STATUS_PARTICION ( ebr ) );
			// 	printf("       Tamano Particion: %d\n", TAMANO_PARTICION ( ebr ) );
			// 	printf("       Nombre Particion: %s\n", NOMBRE_PARTICION ( ebr ) );
			// 	printf("       Tipo Ajuste Particion: %c\n", TIPO_AJUSTE_PARTICION ( ebr ) );

			// 	posicion_logica = SIGUIENTE_PARTICION ( ebr);
			// 	free( ebr );
			// 	ebr = ( posicion_logica == -1 ) ? NULL :
			// 		recuperar_registro( _arg_path, sizeof( struct extend ), posicion_logica );
			// } while ( ebr != NULL );
		}
	}
	free ( mbr );
}

inline void crear_reporte_mbr ( char _arg_path[], char _arg_file[] )
{
	FILE *archivoReporte = fopen ( "mbr.dot", "w" );

	if(!archivoReporte) {
		printf( "   -Error : El archivo <<mbr.dot>> No tiene permisos de escritura.\n" );
		return;
	}

    fprintf( archivoReporte, "\ndigraph G" );
    fprintf( archivoReporte, "\n{" );
    fprintf( archivoReporte, "\n\tnode [shape=plaintext];" );
    fprintf( archivoReporte, "\n\tsplines=ortho;" );

	int i = 0;
	master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	fprintf( archivoReporte, "\n\tnodeA[label=<" );
	fprintf( archivoReporte, "\n\t\t<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"2\" CELLPADDING=\"10\">" );
	fprintf( archivoReporte, "\n\t\t\t<TR>" );
	fprintf( archivoReporte, "\n\t\t\t\t<TD COLSPAN=\"1\" BGCOLOR=\"cadetblue1\">MASTER BOOT RECORDING <BR/> %s</TD>", _arg_path );
	fprintf( archivoReporte, "\n\t\t\t</TR>" );
	fprintf( archivoReporte, "\n\t\t\t<TR><TD>TAMANO_DISCO_MBR <BR/> %d Bytes</TD></TR>", TAMANO_DISCO_MBR ( mbr ) );
	fprintf( archivoReporte, "\n\t\t\t<TR><TD>FECHA_CREACION_PARTICION <BR/> %s</TD></TR>", FECHA_CREACION_MBR ( mbr ) );
	fprintf( archivoReporte, "\n\t\t\t<TR><TD>NUMERO_MAGICO_MBR <BR/> %d</TD></TR>", NUMERO_MAGICO_MBR ( mbr ) );

	for ( ; i < 4; ++i)
	{
		fprintf( archivoReporte, "\n\t\t\t<TR>" );
		fprintf( archivoReporte, "\n\t\t\t\t<TD COLSPAN=\"1\" BGCOLOR=\"cyan\">PARTICION<BR/>(%d)</TD>", i );
		fprintf( archivoReporte, "\n\t\t\t</TR>" );
		fprintf( archivoReporte, "\n\t\t\t<TR><TD>NOMBRE_PARTICION <BR/> %s </TD></TR>", NOMBRE_PARTICION ( PARTICION_MBR( mbr, i) ) );
		fprintf( archivoReporte, "\n\t\t\t<TR><TD>POSICION_PARTICION <BR/> %d Bytes</TD></TR>", POSICION_PARTICION ( PARTICION_MBR( mbr, i) ) );
		fprintf( archivoReporte, "\n\t\t\t<TR><TD>TIPO_PARTICION <BR/> %c </TD></TR>", TIPO_PARTICION ( PARTICION_MBR( mbr, i) ) );
		fprintf( archivoReporte, "\n\t\t\t<TR><TD>STATUS_PARTICION <BR/> %c </TD></TR>", ESTADO_PARTICION ( PARTICION_MBR( mbr, i) ) );
		fprintf( archivoReporte, "\n\t\t\t<TR><TD>TAMANO_PARTICION <BR/> %d </TD></TR>", TAMANO_PARTICION ( PARTICION_MBR( mbr, i) ) );
		fprintf( archivoReporte, "\n\t\t\t<TR><TD>TIPO_AJUSTE_PARTICION <BR/> %c </TD></TR>", TIPO_AJUSTE_PARTICION ( PARTICION_MBR( mbr, i) ) );

		if ( TIPO_PARTICION ( PARTICION_MBR( mbr, i) ) == 'E' )
		{
			// extend *ebr = recuperar_registro( _arg_path, sizeof( struct extend ), POSICION_PARTICION( nparticion ) );
			// do {

			// 	fprintf( archivoReporte, "\n\t\t\t<TR>" );
			// 	fprintf( archivoReporte, "\n\t\t\t\t<TD COLSPAN=\"1\" BGCOLOR=\"lawngreen\">PARTICION LOGICA</TD>" );
			// 	fprintf( archivoReporte, "\n\t\t\t</TR>" );
			// 	fprintf( archivoReporte, "\n\t\t\t<TR><TD>NOMBRE_PARTICION <BR/> %s </TD></TR>", NOMBRE_PARTICION ( ebr ) );
			// 	fprintf( archivoReporte, "\n\t\t\t<TR><TD>POSICION_PARTICION <BR/> %d Bytes</TD></TR>", POSICION_PARTICION ( ebr ) );
			// 	fprintf( archivoReporte, "\n\t\t\t<TR><TD>SIGUIENTE_PARTICION <BR/> %d </TD></TR>", SIGUIENTE_PARTICION ( ebr ) );
			// 	fprintf( archivoReporte, "\n\t\t\t<TR><TD>STATUS_PARTICION <BR/> %c </TD></TR>", STATUS_PARTICION ( ebr ) );
			// 	fprintf( archivoReporte, "\n\t\t\t<TR><TD>TAMANO_PARTICION <BR/> %d </TD></TR>", TAMANO_PARTICION ( ebr ) );
			// 	fprintf( archivoReporte, "\n\t\t\t<TR><TD>TIPO_AJUSTE_PARTICION <BR/> %c </TD></TR>", TIPO_AJUSTE_PARTICION ( ebr ) );

			// 	int siguiente = SIGUIENTE_PARTICION ( ebr);
			// 	free( ebr );
			// 	ebr = ( siguiente == -1 ) ? NULL :
			// 		recuperar_registro( _arg_path, sizeof( struct extend ), siguiente );
			// } while ( ebr != NULL );
		}
	}

	fprintf( archivoReporte, "\n\t\t</TABLE>>" );
	fprintf( archivoReporte, "\n\t];" );

	free (mbr);

    fprintf( archivoReporte, "\n}" );
    fclose( archivoReporte );
}

inline void crear_reporte_disk ( char _arg_path[], char _arg_file[] )
{
	// FILE *archivoReporte = fopen ( "disk.dot", "w" );

 //    fprintf( archivoReporte, "\ndigraph G" );
 //    fprintf( archivoReporte, "\n{" );
 //    fprintf( archivoReporte, "\n\tnode [shape=plaintext];" );
 //    fprintf( archivoReporte, "\n\tsplines=ortho;" );

	// int i = 0;
	// master *mbr = recuperar_registro( _arg_path, sizeof( struct master ), 0 );

	// fprintf( archivoReporte, "\n\tnodeA[label=<" );
	// fprintf( archivoReporte, "\n\t\t<TABLE BORDER=\"0\" CELLBORDER=\"2\" CELLSPACING=\"10\" >" );
	// fprintf( archivoReporte, "\n\t\t\t<TR>" );
	// int tamano_mbr = sizeof( mbr ) + 4 * sizeof( struct particion );

	// int cantidad_filas = 1 + cantidad_particiones_extendidas ( _arg_path, &mbr );
	// fprintf( archivoReporte, "\n\t\t\t\t<TD ROWSPAN=\"%d\" BGCOLOR=\"cadetblue1\">MBR<BR/>%d Bytes</TD>", cantidad_filas, tamano_mbr );

	// int posicion_part_ext = 0;
	// int cantidad_columnas_ebr = 0;
	
	// for ( ; i < 4; ++i) {
	// 	particion *nparticion = recuperar_registro ( _arg_path, sizeof( struct particion ), PARTICION_MBR( mbr, i ) );

	// 	if ( TIPO_PARTICION ( nparticion ) == '0' ) {
	// 		fprintf( archivoReporte, "\n\t\t\t\t<TD ROWSPAN=\"%d\" BGCOLOR=\"cadetblue1\">%s<BR/>%d Bytes</TD>", cantidad_filas,
	// 				NOMBRE_PARTICION ( nparticion ), TAMANO_PARTICION ( nparticion ) );
	// 	} else {
	// 		if ( TIPO_PARTICION( nparticion ) == 'E' ) {
	// 			posicion_part_ext = POSICION_PARTICION ( nparticion );
	// 			cantidad_columnas_ebr = cantidad_particiones_logicas ( _arg_path, POSICION_PARTICION ( nparticion ), TAMANO_PARTICION ( nparticion ) );
	// 			fprintf( archivoReporte, "\n\t\t\t\t<TD COLSPAN=\"%d\" BGCOLOR=\"cadetblue1\">%s<BR/>%d Bytes</TD>", cantidad_columnas_ebr,
	// 				NOMBRE_PARTICION ( nparticion ), TAMANO_PARTICION ( nparticion ) );
	// 		} else {
	// 			fprintf( archivoReporte, "\n\t\t\t\t<TD ROWSPAN=\"%d\" BGCOLOR=\"cadetblue1\">%s<BR/>%d Bytes</TD>", cantidad_filas,
	// 				NOMBRE_PARTICION ( nparticion ), TAMANO_PARTICION ( nparticion ) );
	// 		}
	// 	}

	// 	free ( nparticion );
	// }

	// fprintf( archivoReporte, "\n\t\t\t</TR>" );
	// fprintf( archivoReporte, "\n\t\t</TABLE>>" );
	// fprintf( archivoReporte, "\n\t];" );

	// free (mbr);

 //    fprintf( archivoReporte, "\n}" );
 //    fclose( archivoReporte );
}

	// 	nodeA[label=<
	// 		<TABLE BORDER="0" CELLBORDER="1" CELLSPACING="2" CELLPADDING="10">
	// 			<TR>
	// 				<TD ROWSPAN="2" BGCOLOR="cadetblue1">MBR</TD>
	// 				<TD ROWSPAN="2" BGCOLOR="cadetblue1">PARTICION 1</TD>
	// 				<TD COLSPAN="4" BGCOLOR="cadetblue1">PARTICION 2<BR/>EXTENDIDA</TD>
	// 				<TD ROWSPAN="2" BGCOLOR="cadetblue1">PARTICION 3</TD>
	// 				<TD ROWSPAN="2" BGCOLOR="cadetblue1">PARTICION 4</TD>
	// 			</TR>
	// 			<TR>
	// 				<TD>EBR</TD>
	// 				<TD>LOGICA 1</TD>
	// 				<TD>EBR</TD>
	// 				<TD>LOGICA 2</TD>
	// 			</TR>
	// 		</TABLE>>

static inline master *nuevo_master_boot_record ( int _tamano )
{
	master *nuevo = malloc ( sizeof( struct master) );
	// PARTICION_MBR( nuevo, 0 ) = 0;
	// PARTICION_MBR( nuevo, 1 ) = 0;
	// PARTICION_MBR( nuevo, 2 ) = 0;
	// PARTICION_MBR( nuevo, 3 ) = 0;
	TAMANO_DISCO_MBR( nuevo ) = _tamano;
	NUMERO_MAGICO_MBR( nuevo ) = 200925270;
	tiempo_actual( FECHA_CREACION_MBR ( nuevo ), 24 );
	return nuevo;
}


#endif // MBR_H