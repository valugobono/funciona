#include "libreria.h"


void PelisxUsuarioArchivoToADL(stCelda*arregloUsu, int posicion, nodoArbolPelicula * ArbolPelis) //Carga de peliculas vistas a arreglo de listas de peliculas
{

    FILE*archi;
    archi=fopen(ARCHIPELISUSU, "rb");

    if(archi)
    {
        stPelisVistas aux;
        while(fread(&aux, sizeof(stPelisVistas), 1, archi)>0)
        {
//            printf("idPelicula: %i", aux.idPelicula);
//            printf("idUsuario: %i", aux.idUsuario);
//            printf("idPeliVista: %i", aux.idPeliVista);
//            system("pause");
            if(aux.idUsuario==arregloUsu[posicion].usr.idUsuario)
            {
                stPelicula auxPeli=buscarPeliculaID(ArbolPelis, aux.idPelicula);
                nodoListaPelicula*auxNodo=crearNodoPeli(auxPeli);
                arregloUsu[posicion].listaPelis=agregarNodoPpio(arregloUsu[posicion].listaPelis, auxNodo);
            }
//                fread(&aux, sizeof(stPelisVistas), 1, archi);

        }
        fclose(archi);
    }
    else
    {
        printf("No hay peliculas Vistas");
    }
}

void actualizarPelisVistas(stCelda*arregloUsuActivos, int validos) //Pasaje de peliculas vistas a archivo
{
    FILE*archi;
    archi=fopen(ARCHIPELISUSU, "ab");
    int i=0,  idLocal=0, flag=1; // cantPelisVistas=0, pelisNuevas=0, j=0,;
//    cantPelisVistas=PelisVistasTotales(arregloUsuActivos, validos);
//    printf("%i", cantPelisVistas);
//    system("pause");
//    stPelisVistas arregloPelisVistas[cantPelisVistas]; // Genera un arreglo de Peliculas vistas para posteriormente persistir las nuevas peliculas vistas en el archivo
    if(archi)
    {
        stPelisVistas aux;
        idLocal=cantRegistrosTotales()+1; //Leemos la cantidad de registros en el archivo para saber el id
        printf("%i", idLocal);
        system("pause");
        for(i=0; i<validos; i++) //Recorremos el arreglo de usuarios activos para buscar peliculas que no esten grabadas
        {

//            printf("%s", arregloUsuActivos[i].usr.nombreUsuario);
//            system("pause");
            nodoListaPelicula*auxLista=arregloUsuActivos[i].listaPelis;
            while(auxLista)
            {
                flag=validarIdUsuAndPeli(arregloUsuActivos[i].usr.idUsuario,auxLista->p.idPelicula);
                if(!flag)
                {
                    aux.idPelicula=auxLista->p.idPelicula;
                    aux.idUsuario=arregloUsuActivos[i].usr.idUsuario;
                    aux.idPeliVista=idLocal;
//                    printf("idPelicula: %i", aux.idPelicula);
//                    printf("idUsuario: %i", aux.idUsuario);
//                    printf("idPeliVista: %i", aux.idPeliVista);
//                    system("pause");
                    fwrite(&aux, sizeof(stPelisVistas), 1, archi);


//                    arregloPelisVistas[j].idUsuario=arregloUsuActivos[i].usr.idUsuario;
//                    arregloPelisVistas[j].idPelicula=auxLista->p.idPelicula;
//                    arregloPelisVistas[j].idPeliVista=idLocal;
                    idLocal++;
                }
                auxLista=auxLista->sig;//se pasa a la siguiente pelicula del mismo usuario
            }
        }

//        fseek(archi, 0, 2);
//        for(j=0; j<pelisNuevas; j++)//pasa las nuevas peliculas vistas del arreglo al archivo
//        {
//            aux=arregloPelisVistas[j];
//            fwrite(&aux, sizeof(stPelisVistas), 1, archi);
//        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de Pelis vistas x usuarios");
    }
}


int validarIdUsuAndPeli(int idUsr, int idPeli) // Valida si el id de la pelicula ingresada actualmente ya existe en el archivo
{
    stPelisVistas aux;

    int flag=0;

    FILE * archi;

    archi=fopen(ARCHIPELISUSU, "rb"); // Abre al archivo en modo s�lo lectura para chequear acceso

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si la pelicula ya existe");
        exit(1);
    }

    else
    {
        while((fread(&aux, sizeof(stPelisVistas), 1, archi)>0) && (!flag))  // Realiza el proceso mientras haya registros en el archivo
        {
            if(aux.idUsuario==idUsr&&aux.idPelicula==idPeli)
            {
                flag=1; // Si ambos ids son iguales, asigno valor 0 a flag como negativo
            }
        }
        fclose(archi); // Cierra el archivo
    }

    return flag; // Devuelve el valor de flag para su proceso en la funci�n que la invoca
}

void borrarPeliVistaArchivo(int idUsr, int idPeli) // Valida si el id de la pelicula ingresada actualmente ya existe en el archivo
{
    stPelisVistas aux;

    FILE * archi;

    int flag=0;
    archi=fopen(ARCHIPELISUSU, "rb"); // Abre al archivo en modo s�lo lectura para chequear acceso

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si la pelicula ya existe");
        exit(1);
    }

    else
    {
        while((!flag)&&(fread(&aux, sizeof(stPelisVistas), 1, archi)>0))  // Realiza el proceso mientras haya registros en el archivo
        {
            if(aux.idUsuario==idUsr&&aux.idPelicula==idPeli) // Si ambos ids son iguales, asigno valor 0 a flag como negativo
            {
                aux.idPelicula=-1;
                aux.idUsuario=-1;
                flag=1;
                fseek(archi, -1*sizeof(stPelicula), SEEK_CUR);
                fwrite(&aux, sizeof(stPelisVistas), 1, archi);
            }
        }
        fclose(archi); // Cierra el archivo
    }

}

int cantRegistrosTotales() // Funci�n utilizada para contar la cantidad total de registros guardados en el archivo
{

    int cantRegistros=0; // Variable a retornar

    FILE*archi; //Reserva de espacio en buffer

    archi=fopen(ARCHIPELISUSU, "rb"); //Apertura de archivo como solo lectura

    if(archi) // Si se pudo abrir el archivo
    {

        fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ah� el peso del mismo

        if(ftell(archi)==0) // Si el tama�o del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
        {
            cantRegistros=0; // Se le asigna el valor 1 al primer registro
        }
        else
        {
            cantRegistros=(ftell(archi)/sizeof(stPelisVistas)); // Se calcula cuantos registros hay dividiendo el tama�o del archivo por el tama�o de la estructura

        }
        fclose(archi); // Se cierra el archivo
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios"); // Si no se pudo abrir el archivo se devuelve mensaje de error
    }

    return cantRegistros; // Se devuelve la cantidad de registros totales contados
}

nodoListaPelicula* borrarPelisVistas(nodoListaPelicula*lista)  // Funci�n que borra toda una lista de peliculas - Invocar antes de Borrar arreglo
{

    nodoListaPelicula*aux;

    while(lista)
    {
        aux=lista;
        lista=lista->sig;
        free(aux);
    }

    return lista; //Retorna NULL
}

/////////////////////VALE ////////////////////// recomendaciones


int buscarPosString(char arregloNombres[][20], char nombre[], int validos) // Reusar
{

    int i=0;
    int pos=-1;

    while(i<validos && (strcmp(nombre, arregloNombres[i])!=0))
    {
            i++;
    }
    if (strcmp(nombre, arregloNombres[i])==0)
        pos=i;

    return pos;
}

int agregarString(char arregloNombres[][20], char nombre[], int validos) //Reusar
{
    strcpy(arregloNombres[validos], nombre);
    validos++;
    return validos;
}


int buscarMayorOcurrencia(int ocurrencias[], int validos) //Reusar
{

    int mayor=0;
    for (int i=1; i< validos; i++)
    {
        if (ocurrencias[i] > ocurrencias[mayor])
            mayor=i;
    }

    return mayor;
}

void generoMasVisto(nodoListaPelicula*lista, char MasVisto[20])
{

    char generos[20][20];
    int ocurrencias[20];
    int pos;
    int validos=0;

    for (int i=0; i < 20; i++)
    {
        ocurrencias[i]=0;
    }
    while(lista)
    {
        pos=buscarPosString(generos, lista->p.genero, validos);
        if(pos<0)
        {
            validos=agregarString(generos, lista->p.genero, validos);
            pos=validos-1;
        }

        ocurrencias[pos]=ocurrencias[pos]+1;
        lista=lista->sig;
    }

    pos= buscarMayorOcurrencia(ocurrencias,validos);
        strcpy(MasVisto,generos[pos]);

}


void directorMasVisto(nodoListaPelicula*lista, char MasVisto[20])
{

    char directores[20][20];
    int ocurrencias[20];
    int pos;
    int validos=0;

    for (int i=0; i < 20; i++)
    {
        ocurrencias[i]=0;
    }
    while(lista)
    {
        pos=buscarPosString(directores, lista->p.director, validos);
        if(pos<0)
        {
            validos=agregarString(directores, lista->p.director, validos);
            pos=validos-1;
        }

        ocurrencias[pos]=ocurrencias[pos]+1;
        lista=lista->sig;
    }

    pos= buscarMayorOcurrencia(ocurrencias,validos);
        strcpy(MasVisto,directores[pos]);

}

void recomendarPelis(nodoArbolPelicula*ArbolPelis, nodoListaPelicula*PelisVistas){

char genero[20];
char director[20];
generoMasVisto(PelisVistas,genero);
directorMasVisto(PelisVistas,director);
system("cls");
printf("El genero mas recomendado para usted es %s\n", genero);
printf("%s\n",director);
Sleep(2000);
listarPelisRecomendadasxGeneroDirector(PelisVistas,ArbolPelis,genero,director);

}

int peliVista(int idPelicula,nodoListaPelicula *PelisVistas)
{
    int flag=0;
    while (PelisVistas && !flag) {
        if (idPelicula==PelisVistas->p.idPelicula)
          flag=1;
        PelisVistas=PelisVistas->sig;
    }
    return flag;
}

void listarPelisRecomendadasxGeneroDirector(nodoListaPelicula *PelisVistas,nodoArbolPelicula *ArbolPelis, char * genero,char *director)
{
    if (ArbolPelis)
    {
        if ((strcmp(ArbolPelis->p.genero,genero) == 0) || (strcmp(ArbolPelis->p.director,director)==0)) {
            if (!peliVista(ArbolPelis->p.idPelicula,PelisVistas))
                imprimirNodoPelis(ArbolPelis->p);
        }
        listarPelisRecomendadasxGeneroDirector(PelisVistas,ArbolPelis->izq,genero,director);
        listarPelisRecomendadasxGeneroDirector(PelisVistas,ArbolPelis->der,genero,director);
    }
}
