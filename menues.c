#include "libreria.h"

/// OJO PASAR POR PARAMETRO TODAS LAS VARIABLES NECESARIAS


void menuPrincipal()
{

    stCelda* arregloUsuActivos=NULL; // Se manejan con punteros por ser estructura din�mica
    nodoArbolPelicula* ArbolPelis=inicArbol(); // Se manejan con punteros por ser estructura din�mica
    int validos=0;  // Variable utilizada para los usuarios ACTIVOS
    ArbolPelis=PasaPeliculasDeArchivoToArbol(ArbolPelis);
    arregloUsuActivos=cargarArchiUsuToArreglo(arregloUsuActivos, &validos, ArbolPelis);
//    system("pause");
    if(ArbolPelis)
    {

        int opcion=0, repetir=1;
        do
        {
            system("cls");
            printf("\n");
            printf("\n*****************************************************");
            printf("\n***\t	MENU PRINCIPAL  \t\t  ***");
            printf("\n*****************************************************");
            printf("\n");
            printf("\n\t 1) REGISTRO DE NUEVO USUARIO");
            printf("\n\t 2) INICIAR SESION DE USUARIO");
            printf("\n\t 3) INICIAR SESION DE ADMINISTRADOR");
            printf("\n\t 0) SALIR DEL PROGRAMA");
            printf("\n\n\t INGRESE SU OPCION: ");
            scanf("%i", &opcion);
            switch(opcion)
            {
            case 0:
                exit(1);
            case 1:
                altaUsuarios(arregloUsuActivos, &validos);
                break;
            case 2:
                loginUser(arregloUsuActivos, validos, ArbolPelis);
                break;
            case 3:
                loguinadm(arregloUsuActivos, &validos, ArbolPelis);
                break;
            default:
                exit(1);
            }
        }
        while(repetir==1);
    }

    else
        printf("Error en la carga inicial de archivos");
}


////***********************************************************************************************************************************//
////                                                  FUNCIONES DE SUBMENUES / LOGIN
////***********************************************************************************************************************************//
//
void loguinadm(stCelda*arregloUsuActivos, int * validos, nodoArbolPelicula*ArbolPelis)
{
    int login=0;
    char passaux[11];
    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tLOGIN DE ADMINISTRADOR");
    printf("\n*****************************************************");
    printf("\n");
    printf("\n\tINGRESE EL PASSWORD DE ADMINISTRADOR\n\n");
    fflush(stdin);
    gets(passaux);
    login=validacionPassAdmin(passaux);
    if(login==1)
    {
        menuAdmin(arregloUsuActivos,validos,ArbolPelis);
    }
    else
    {
        printf("Login incorrecto \n");
        system("pause");
    }
}


void loginUser(stCelda*arregloUsuActivos, int validos, nodoArbolPelicula * ArbolPelis)
{
    int login=0;
    char nombreaux[30];
    char passaux[11];
    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tLOGIN DE USUARIO");
    printf("\n*****************************************************");
    printf("\n");
    printf("\n\tINGRESE SU NOMBRE DE USUARIO\n\n");

    fflush(stdin);
    gets(nombreaux);
    if(validarUsuExisteNombre(nombreaux, arregloUsuActivos, validos))
    {
        printf("\n\tINGRESE SU PASSWORD\n\n");
        fflush(stdin);
        gets(passaux);
        login=validacionPass(arregloUsuActivos, validos, nombreaux, passaux);
        int pos=buscarPosicionUsuario(nombreaux, arregloUsuActivos, validos);
        if(login==1)
        {
            imprimirUsuarioConPass(arregloUsuActivos[pos].usr);
            system("pause");
            menuUsuario(arregloUsuActivos, validos, arregloUsuActivos[pos].usr, ArbolPelis);
        }
        else
        {
            printf("Login incorrecto \n");
        }
    }
    else
    {
        printf("Nombre de usuario incorrecto\n");
        system("pause");
    }

}


void menuUsuario(stCelda * arregloUsuActivos, int validos, stUsuario usr, nodoArbolPelicula * ArbolPelis)
{


    int opcion=0, repetir=1, pos;

    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tMENU DE USUARIO");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) VER PERFIL");
        printf("\n\t 2) LISTADOS DE PELICULAS");
        printf("\n\t 3) BUSCAR PELICULA");
        printf("\n\t 4) VER PELICULAS RECOMENDADAS");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            imprimirUsuarioConPass(usr);
            system("pause");
            repetir=1;
            break;

        case 2:
            subMenuListados(ArbolPelis);
            repetir=1;
            break;

        case 3:
            verPelicula(usr.nombreUsuario, arregloUsuActivos, validos, ArbolPelis);
            actualizarPelisVistas(arregloUsuActivos, validos);
            repetir=1;
            break;

        case 4:
            pos=buscarPosUsuarioPorId(usr.idUsuario,arregloUsuActivos,validos);
            recomendarPelis(ArbolPelis, arregloUsuActivos[pos].listaPelis);
            system("pause");
            repetir=1;
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdmin(stCelda* arregloUsuActivos, int * validos, nodoArbolPelicula*ArbolPelis)
{

    int opcion=0,repetir=1;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tMENU DE ADMINISTRADOR\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) GESTIONAR PELICULAS");
        printf("\n\t 2) GESTIONAR USUARIOS");
        printf("\n\t 3) VACIAR ESTRUCTURAS ACTUALES");
        printf("\n\t 4) REINICIAR SISTEMA");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            menuAdminPelis(ArbolPelis);
            break;

        case 2:
            menuAdminUsuarios(arregloUsuActivos, validos);
            break;

        case 3:
            if(!(ArbolPelis=borrarArbol(ArbolPelis)))
            {
                printf("\nEl arbol se borro correctamente");
                system("pause");
            }
            else
            {
                printf("\nHubo un error al borrar el arbol");
            }
//            arregloUsuActivos=borrarArregloUsu(arregloUsuActivos, validos);
            break;

        case 4:
            ArbolPelis=PasaPeliculasDeArchivoToArbol(ArbolPelis); // Pasa las pel�culas del archivo al �rbol
//            arregloUsuActivos=cargarArchiUsuToArreglo(arregloUsuActivos, validos, ArbolPelis); // Pasa los usuarios del archivo al arreglo de listas de usuarios/peliculas vistas
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdminPelis(nodoArbolPelicula * ArbolPelis)
{

    int opcion=0,repetir=0;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMENU DE GESTION DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ALTA DE PELICULAS");
        printf("\n\t 2) BAJA DE PELICULAS");
        printf("\n\t 3) MODIFICACION DE PELICULAS");
        printf("\n\t 4) CONSULTA DE PELICULAS");
        printf("\n\t 5) LISTADOS DE PELICULAS");
        printf("\n\t 0) SALIR DEL PROGRAMA");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            ArbolPelis=altaPelicula(ArbolPelis);
            repetir=1;
            break;

        case 2:
            ArbolPelis=bajaPelicula(ArbolPelis);
            repetir=1;
            break;

        case 3:
            ArbolPelis=mostrarPeliParaModif(ArbolPelis);
            repetir=1;
            break;

        case 4:
            consultaPeliAdmin();
            repetir=1;
            break;

        case 5:
            subMenuListados(ArbolPelis);
            repetir=1;
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}

void menuAdminUsuarios(stCelda*arregloUsuActivos, int * validos)
{

    int opcion=0, repetir=1;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMENU DE GESTION DE USUARIOS\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ALTA DE USUARIOS");
        printf("\n\t 2) BAJA DE USUARIOS");
        printf("\n\t 3) MODIFICACION DE USUARIOS");
        printf("\n\t 4) CONSULTA DE USUARIOS");
        printf("\n\t 5) LISTADOS DE USUARIOS");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            altaUsuarios(arregloUsuActivos, validos);
            break;

        case 2:
            bajaUsuario(arregloUsuActivos, validos);
            break;

        case 3:
            menumodif(arregloUsuActivos, *validos);
            break;

        case 4:
            consultarUsuario(arregloUsuActivos,validos);
            break;

        case 5:
            mostrarUsuariosActivos(arregloUsuActivos, *validos);
            system("pause");
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void subMenuListados(nodoArbolPelicula*ArbolPelis)
{
    int opcionlistados=0, repetir=0;
    char control='s';

    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t L I S T A D O S\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ORDENADOS POR TITULO");
        printf("\n\t 2) ORDENADOS POR GENERO");
        printf("\n\t 3) MOSTRAR LISTADO ENTERO");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcionlistados);

        switch(opcionlistados)
        {

        case 0:
            repetir=0;
            break;

        case 1:

            ordenarTitulo();
            printf("\n\t Desea ver otro listado? s/n : \n");
            scanf("%c", &control);
            if(control=='s')
                repetir=1;
            break;

        case 2:

            ordenarGenero();
            printf("\n\t Desea ver otro listado? s/n : \n");
            scanf("%c", &control);
            if(control=='s')
                repetir=1;
            break;

        case 3:

            subMenuMostrarArbol(ArbolPelis);
            printf("\n\t Desea ver otro listado? s/n : \n");
            scanf("%c", &control);
            if(control=='s')
                repetir=1;
            break;

        }

    }
    while(repetir==1);
}

void subMenuMostrarArbol(nodoArbolPelicula * ArbolPelis)
{
    int opcionlistados=0;
    char control='s';
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t M O S T R A R  A R B O L\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) IN ORDER");
        printf("\n\t 2) POST ORDER");
        printf("\n\t 2) PRE ORDER");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcionlistados);

        switch(opcionlistados)
        {

        case 1:

            inOrder(ArbolPelis);
            printf("\n\t Desea ver el arbol nuevamente? s/n : \n");
            scanf("%c", &control);
            break;

        case 2:

            preOrder(ArbolPelis);
            printf("\n\t Desea ver el arbol nuevamente? s/n : \n");
            scanf("%c", &control);
            break;

        case 3:

            postOrder(ArbolPelis);
            printf("\n\t Desea ver el arbol nuevamente? s/n : \n");
            scanf("%c", &control);
            break;

        }

    }
    while(control=='s');
}


/// MODIFICADO VALE - NO tocar por favor
void menumodif(stCelda*arregloUsuActivos, int validos)//Menu para administrador para seleccion de campo a modificar
{
    int id=modificarUsuario(arregloUsuActivos, validos);
    int pos=buscarPosUsuarioPorId(id, arregloUsuActivos, validos);


    int resp, continuar;

    do
    {
        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Password:\n\t");
        printf("[3]- Anio Nacimiento:\n\t[4]- Genero:\n\t[5]- Pais:\n\t[6]- Estado en la base:\n\t[7]- Nivel de permisos:\n\t[0]- Salir\n\t");
        fflush(stdin);
        scanf("%i", &resp);
    }
    while (0>resp && resp <6);

    do
    {
        switch (resp)
        {

        case 0:
            menuAdminUsuarios(arregloUsuActivos, &validos);
            break;
        case 1:
            continuar=cambiarNombreUsu(id, pos, arregloUsuActivos);
            break;
        case 2:
            continuar=cambiarPassUsu(id, pos, arregloUsuActivos);
            break;
        case 3:
            continuar=cambiarAnioUsu(id, pos, arregloUsuActivos);
            break;
        case 4:
            continuar=cambiarGeneroUsu(id, pos, arregloUsuActivos);
            break;
        case 5:
            continuar=cambiarPaisUsu(id, pos, arregloUsuActivos);
            break;
        case 6:
            continuar=cambiarEstadoUsu(id, pos, arregloUsuActivos);
            break;
        case 7:
            continuar=cambiarPermisosUsu(id, pos, arregloUsuActivos);
            break;
        default:
            exit(1);
            break;
        }

    }
    while(resp!=0&&continuar==1);
}



int menuModifPelis(nodoArbolPelicula*ArbolPelis)//Menu para administrador para seleccion de campo a modificar
{
    int resp;

    do
    {

        system("CLS");
        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Director:\n\t");
        printf("[3]- Anio de Filmacion:\n\t[4]- Genero:\n\t[5]- Pais de origen:\n\t[6]- Valoracion:\n\t[7]- Clasificacion:\n\t[8]- Estado en catalogo:\n\t[0]- Salir\n\t");
        scanf("%i", &resp);

    }
    while (0>resp && resp <6);

    return resp;
}


