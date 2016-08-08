//io_200925270.h
#ifndef IO_H
#define IO_H

void almacenar_registro_posicion_n ( char [], void *, int, int );
void almacenar_registro_posicion_final ( char [], void *, int );

void almacenar_registro( char [], void *, int, int );
void *recuperar_registro( char [], int, int );

static inline void escribir_registro_posicion ( FILE **, void *, int, int );
static inline void escribir_registro_final ( FILE **, void *, int );
static inline void *leer_registro ( FILE **, int, int );

/*
 *
 *
 *
 */

void almacenar_registro_posicion_final ( char _ruta_disco[], void *_objeto, int _tamano )
{
    FILE *discoVirtual = fopen ( _ruta_disco, "ab" );

    if (!discoVirtual) {
        return;
    }

    escribir_registro_final ( &discoVirtual, _objeto, _tamano );
    fclose( discoVirtual );
}

void almacenar_registro_posicion_n ( char _ruta_disco[], void *_objeto, int _tamano, int _posicion )
{
	FILE *discoVirtual = fopen ( _ruta_disco, "r+b" );

	if (!discoVirtual) {
	    return;
	}

	escribir_registro_posicion ( &discoVirtual, _objeto, _tamano, _posicion );
    fclose( discoVirtual );
}

void *recuperar_registro( char _ruta_disco[], int _tamano, int _posicion )
{
    FILE *discoVirtual = fopen ( _ruta_disco, "rb" );

    if (!discoVirtual) {
        return NULL;
    }

    void *registro = leer_registro ( &discoVirtual, _tamano, _posicion );
    fclose( discoVirtual );
    return registro;
}

static inline void escribir_registro_final ( FILE **_discoVirtual, void *_objeto, int _tamano )
{
    fseek ( *_discoVirtual, 0, SEEK_END );
    fwrite ( _objeto, _tamano, 1, *_discoVirtual );
}

static inline void escribir_registro_posicion ( FILE **_discoVirtual, void *_objeto, int _tamano, int _posicion )
{
	fseek ( *_discoVirtual, _posicion, SEEK_SET );
	fwrite ( _objeto, _tamano, 1, *_discoVirtual );
}

static inline void *leer_registro ( FILE **_discoVirtual, int _tamano, int _posicion )
{
    void *registro = malloc( _tamano );

    fseek ( *_discoVirtual, _posicion, SEEK_SET );
    fread( registro, _tamano, 1, *_discoVirtual );

    return registro; 
}

#endif // IO_H