
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main( int argc, char ** argv ) {
    int id, st, veces;

    struct msgbuf {
        long mtype;
        int veces;
        char etiqueta[ 32 ];
    } mensaje;

    memset(mensaje.etiqueta, '\0', sizeof(mensaje.etiqueta));

    id = msgget( 0xB32135, IPC_CREAT | 0600 );
    if ( -1 == id ) {
        perror( "Recibir sin clases, creando el buzon" );
        exit( 1 );
    }

    while ( (st = msgrcv( id, (void *) & mensaje, sizeof( mensaje ), 2020, IPC_NOWAIT ) ) > 0 ) {
        printf( "Label: %s, veces %d, status %d \n", mensaje.etiqueta, mensaje.veces, st);
    }

    //st = msgctl( id, IPC_RMID, NULL );
    if ( -1 == msgctl( id, IPC_RMID, NULL ) ) {
        perror( "Recibir sin clases, borrando el buzon" );
        exit( 2 );
    }
    exit(0);
}

