//interprete_200925270.h
#ifndef INTERPRETE_H
#define INTERPRETE_H

/*
 *
 *
 *
 */

inline int ejecutar_instrucciones ( accion ** );

 /*
  *
  *
  *
  */

inline int ejecutar_instrucciones ( accion **_instrucciones )
{
	accion *instrucciones = (*_instrucciones);
	if ( instrucciones == NULL )
		return true;

	if(DEPURADOR)
		printf("\n\t(Entrada Del Interprete)");

	parametro *errores = NULL;
	switch (instrucciones->tipo)
	{
		case MKDISK: { //mKdisk -path::"/home/wxqzsvtyk/Plantillas/disk.dk" -size::2 +unit::M
			validar_creacion_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		case RMDISK: { //RmDisk -path::"/home/wxqzsvtyk/Plantillas/disk.dk"
			validar_eliminacion_disco ( &(*_instrucciones)->parametros, &errores );
		} break;
		case FDISK: { //fdisk -path::
			validar_accion_particion ( &(*_instrucciones)->parametros, &errores );
		} break;
		// case MOUNT: {} break;
		// case UNMOUNT: {} break;
		case EXIT: {
			return false;
		} break;
		// case 6: {} break;
		// case 7: {} break;
		default: {} break;
	}

	return true; //ejecutar_instrucciones ( &obtener_siguiente_instruccion ( _instrucciones ) );
}

static inline void ejecutar_archivo_entrada () {}
static inline void cargar_archivo_entrada () {}

#endif // INTERPRETE_H