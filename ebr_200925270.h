//ebr_200925270.h
#ifndef EBR_H
#define EBR_H

/*
 *
 *
 *
 */

#define SIGUIENTE_EBR(s) ((s)->part_next)
#define AJUSTE_EBR(s) ((s)->part_fit)
#define POSICION_EBR(s) ((s)->part_start)
#define ESTADO_EBR(s) ((s)->part_status)
#define NOMBRE_EBR(s) ((s)->part_name)
#define TAMANO_EBR(s) ((s)->part_size)

struct extend {
	unsigned int part_start;
	unsigned int part_size;
	char part_name[16];
	char part_status;
	char part_fit;
	int part_next;
};

typedef struct extend extend;

/*
 *
 *
 *
 */

static inline extend *nuevo_extend_boot_record ();

 /*
 *
 *
 *
 */

static inline extend *nuevo_extend_boot_record () {
	extend *nueva = malloc ( sizeof( struct extend ) );
	strcpy ( NOMBRE_EBR( nueva ), "" );
	AJUSTE_EBR( nueva ) = '0';
	SIGUIENTE_EBR( nueva ) = -1;
	POSICION_EBR( nueva )  = 0;
	ESTADO_EBR( nueva ) = '0';
	TAMANO_EBR( nueva ) = 0;
	return nueva;
}

#endif // EBR_H