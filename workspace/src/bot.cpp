#include "DatosMemCompartida.h"

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>

using namespace std;

int main()
{
    // ABRIR EL FICHERO DE MEMORIA COMPARTIDA
    int fd = open("/tmp/tenis_memoria", O_RDWR);

    if (fd == -1)
    {
        perror("Error al abrir el fichero");
        exit(1);
    }

    // PROYECTAR EL FICHERO EN MEMORIA
    void *direccion = mmap(NULL, sizeof(DatosMemCompartida),
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED, fd, 0);

    close(fd);

    if (direccion == MAP_FAILED)
    {
        perror("Error en mmap");
        exit(1);
    }

    DatosMemCompartida *datos = (DatosMemCompartida *)direccion;

    // BUCLE PRINCIPAL DEL BOT
    while (true)
    {
        if (datos->esfera.centro.y > datos->raqueta1.y1)
            datos->accion = 1;
        else if (datos->esfera.centro.y < datos->raqueta1.y1)
            datos->accion = -1;
        else
            datos->accion = 0;

        usleep(25000);
    }

    return 0;
}
