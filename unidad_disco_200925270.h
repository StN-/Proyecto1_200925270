//unidad_disco_200925270.h
#ifndef UNIDAD_DISCO_H
#define UNIDAD_DISCO_H

/*
 *
 *
 *
 */

inline void creacion_disco_virtual ( char [], int );
inline void eliminacion_disco_virtual ( char [] );

/*
 *
 *
 *
 */

inline void creacion_disco_virtual ( char _arg_path[], int _arg_size )
{
	FILE *disco_virtual = fopen ( _arg_path, "w+b" );

	if (!disco_virtual) {
	    return;
	}

	char bloque[1024] = "\0";
	register unsigned int i = 0;

	for ( ; i < _arg_size; i+=1024 )
        fwrite ( &bloque, sizeof( bloque ), 1, disco_virtual );

    fclose( disco_virtual );
    printf( "\n\tEl Disco <<%s>>, se ha Creado Exitosamente.", _arg_path );
}

inline void eliminacion_disco_virtual ( char _arg_path[] ) {
	( remove( _arg_path ) == 0 ) ? printf( "\n\tEl Disco <<%s>>, se ha Eliminado Exitosamente.", _arg_path ) :
		printf( "\n\t[ERROR] : El archivo <<%s>> No se pudo Eliminar Correctamente.", _arg_path );
}

#endif // UNIDAD_DISCO_H