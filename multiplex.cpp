/*
Licencia GNU v3
Por: Alejandro Sacristan Leal & Juan Esteban Reyes Tausa
Administrador de Sala de Cine Multiplex
Fecha de Entrega 12/04/21 6:59 AM
**/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h> 
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string.h>


using namespace std;

//ESTRUCTURAS
struct Silla {
  short int code;
  char* identificacion; //Clase de Silla Diamante o Classic
  bool estado; //ACTIVA O ELIMINADA
  bool reservada; // LIBRE O RESERVADA
};

struct Pelicula {
  char* nombre;
  int codigo;
  tm fecha;
  Silla* silla;
};

struct SalaCine {
    short int id;
    bool estado;
    char* nombre;
    int cupoTotalSillas;
    Pelicula* pelicula;
    short int sillasTotalPreferencial;
    short int sillasTotalGenerales;
};

struct Actor{
  short int identificacion;
  char* nombre;
  char* apellido;
  SalaCine* sala;
  short int numSalas;
};

//Menu de Navegacion
void menuInicial(Actor* cine);
void menuAdministrador(Actor* cine);
void menuCliente(Actor* cine);
void menuTaquilla(Actor* cine);

// Requerimientos del Programa
Actor* cargarConfiguracionMultiplex();
void printTiquet(char* nombre, char* apellido, char* nombreSala ,char* nombrePelicula, int fecha, char* categoriaSillas,int numeroSilla, int totalDeuda);
void ventaTiquete(Actor* cliente);
void eliminarContenidoHTML();
void cartelera(Actor* cine);
Silla* Crear_Sillas(int sillas_general, int sillas_preferencial);
SalaCine* crear_Sala(int i, short int id, char* nombre, int cupoTotalSillas, char* nombrePelicula, int codigo, tm fecha, int sillas_general, int sillas_preferencial);
SalaCine* eliminar_Sala(int numeroSalaEliminar, SalaCine *sala);


int main(){

    system("clear");// Limpiar Consola
    
    
    

  return 0;
}

//ActorDos
//Menu con Acciones permitadas para las taquillas fisicas del Cine
void menuTaquilla(Actor* cine){
  system("clear");
  short int opcion = 0;

  cout<< "Menu Taquilla Fisica"<<endl;
  cout<< "1. Vender tiquetes"<<endl;
  cout<< "2. Salir"<<endl; 
  cout<< " "<< endl;
  cin>>opcion;
  cout<<" "<< endl;
  if(opcion == 1){ventaTiquete(cine);menuInicial(cine);}//Adquirir Tiquets
  if(opcion == 2){menuInicial(cine);}//Volver a menu Inicial

  system("clear");
}

//ActorUno
//Menu con Acciones permitadas para los Clientes del Cine
void menuCliente(Actor* cine){
  system("clear");
  short int opcion = 0;

    cout<<" Estimado Cliente que desea?:"<<endl;
    cout<< " " << endl;
    cout<<"1. Ver Cartelera"<<endl; 
    cout<<"2. Adquirir tiquetes"<<endl; 
    cout<<"3. Salir"<<endl;
    cin>>opcion;
    cout<<" "<< endl;
    if(opcion == 1){cartelera(cine); system("clear");menuCliente(cine);}
    if(opcion == 2){system("clear");ventaTiquete(cine);menuInicial(cine);}//Adquirir Tiquetes
    if(opcion == 3){system("clear");menuInicial(cine);}//Volver a menu Inicial


    system("clear");
}

//ActorTres
//Menu con Acciones permitadas para el Administrador del Cine
void menuAdministrador(Actor* cine){
  system("clear");
  short int opcion = 0;

    cout <<"        Menu Administrador"<< endl;
    cout<< " " << endl;

    cout<< " ¿Que desea hacer?"<<endl;
    cout<< " " << endl;
    cout<< "1. Configuracion General del Multiplex." <<endl;
    cout<< "2. Consulta Salas de Cines." <<endl;
    cout<< "---" << endl;
    cout<< "3. Adicionar Sala de Cine." <<endl;
    cout<< "4. Adicionar Sillas a una Sala de Cine." <<endl;
    cout<< "5. Adición de una película y su asociación con la sala(s) y hora(s) de presentacion." <<endl;
    cout<< "---" << endl;
    cout<< "6. Eliminar Sala de Cine." <<endl;
    cout<< "7. Eliminar Sillas a una Sala de Cine." <<endl;
    cout<< "---" << endl;

    cout<< "8. Salir." << endl;
    cin >> opcion;
    cout<< " " << endl;

    if(opcion == 1){}//Configuracion apartir del txt
    if(opcion == 2){cartelera(cine); cout<<"Ya se encuentra Publica en la Web"<<endl;}//Consultar Salas De Cine
    if(opcion == 3){}//Adicion De Sala de Cine
    if(opcion == 4){}//Adicion de Sillas a Sala de Cine
    if(opcion == 5){}//Adicion de una Pelicual
    if(opcion == 6){}//Eliminar Sala
    if(opcion == 7){}//Eliminar Silla
    if(opcion == 8){system("clear");menuInicial(cine);}//Volver a menu Inicial

    
    system("clear");
}

//Menu de Precentacion del Programa
void menuInicial(Actor* cine){
  system("clear");
    short int opcion=0;

    cout<<"Bienvenido a Cine Multiplex Global" << endl;
    cout<<" "<< endl;
    cout<<"Usted es:"<<endl;
    cout<<"1. Administrador"<<endl;
    cout<<"2. Cliente"<<endl;
    cout<<"3. Taquilla"<< endl;
    cout<<" "<< endl;
    cout<<"Si no desea continuar presione 4"<<endl;
    cin>>opcion;
    cout<<" "<< endl;
    if(opcion == 1){system("clear");menuAdministrador(cine);}// Menu Administrador
    if(opcion == 2){system("clear");menuCliente(cine);}// Menu Cliente
    if(opcion == 3){system("clear");menuTaquilla(cine);}//Menu Taquilla
    if(opcion == 4){system("clear");}// Salir
    
    system("clear"); 
}

Actor* cargarConfiguracionMultiplex(){

    ifstream leer("multiplex2020-4.txt", ios::in);
    char* auxiliar = new char[30];
    Actor* cine = new Actor;

    short int contadorSalas = 1;
    short int contadorPeliculas = 1;
    

    if(!leer.is_open()){ std::cout << "Error: File Open" << '\n';}

    while(!leer.eof()){// Mientras el Archivo este Abierto
      
      leer.getline(auxiliar, 30, '\n');//<Sala>
      cout<<auxiliar<<endl;
      while ((strcmp(auxiliar, "<Sala/>")) != 0){
        //cine[1].sala[contadorSalas].estado = true;

        leer.getline(auxiliar, 30, '\n');// <ID>
        cout<<auxiliar<<endl;

        if((strcmp(auxiliar, "<ID>")) == 0){
                leer.getline(auxiliar, 30, '\n');// Numero Id
                cout<<auxiliar<<endl;
                cine->sala[contadorSalas].id = atoi(auxiliar);
                
        }
        leer.getline(auxiliar, 30, '\n');//<ID/>
        leer.getline(auxiliar, 30, '\n');//<Nombre/>
        if((strcmp(auxiliar, "<Nombre>")) == 0){
            leer.getline(auxiliar, 30, '\n');
            cine->sala[contadorSalas].nombre = new char[30];
            strcpy(cine->sala[contadorSalas].nombre, auxiliar);
            cout<<auxiliar<<endl;
        }
        leer.getline(auxiliar, 30, '\n');//<Nombre/>
        leer.getline(auxiliar, 30, '\n');//<Cupo>
        if((strcmp(auxiliar, "<Cupo>")) == 0){
            leer.getline(auxiliar, 30, '\n');
            cine->sala[contadorSalas].cupoTotalSillas = atoi(auxiliar);
            cout<<auxiliar<<endl;
        }
        //Peliculas Dentro de una Sala
        leer.getline(auxiliar, 30, '\n');//<Cupo/>
        leer.getline(auxiliar, 30, '\n');//<Pelicula>
        while ((strcmp(auxiliar, "<Pelicula/>")) != 0){
          leer.getline(auxiliar, 30, '\n');//<Nombre/>
          cout<<auxiliar<<endl;
                
          if((strcmp(auxiliar, "<Nombre>")) == 0){
            leer.getline(auxiliar, 30, '\n');//Nombre Pelicula
            cine->sala[contadorSalas].pelicula[contadorPeliculas].nombre = new char[30];
            strcpy(cine->sala[contadorSalas].pelicula[contadorPeliculas].nombre, auxiliar);
          }
          leer.getline(auxiliar, 30, '\n');//<Nombre/>
          leer.getline(auxiliar, 30, '\n');//<ID>
          if((strcmp(auxiliar, "<ID>")) == 0){
            leer.getline(auxiliar, 30, '\n');//ID Pelicula
            cine->sala[contadorSalas].pelicula[contadorPeliculas].codigo= atoi(auxiliar);    
          }

          leer.getline(auxiliar, 30, '\n');//<ID/>
          leer.getline(auxiliar, 30, '\n');//<Fecha>
          if((strcmp(auxiliar, "<Fecha>")) == 0){

            leer.getline(auxiliar, 30, '/');//Dia Pelicula
            cine->sala[contadorSalas].pelicula[contadorPeliculas].fecha.tm_mday= atoi(auxiliar);
            leer.getline(auxiliar, 30, '/');//Mes Pelicula
            cine->sala[contadorSalas].pelicula[contadorPeliculas].fecha.tm_mon= atoi(auxiliar);
            leer.getline(auxiliar, 30, '\n');//Año Pelicula
            cine->sala[contadorSalas].pelicula[contadorPeliculas].fecha.tm_year= atoi(auxiliar);

                    
          }

          leer.getline(auxiliar, 30, '\n');//<Fecha/>
          leer.getline(auxiliar, 30, '\n');//<Hora>
          if((strcmp(auxiliar, "<Hora>")) == 0){

            leer.getline(auxiliar, 30, ':');//Hora Pelicula
            cine->sala[contadorSalas].pelicula[contadorPeliculas].fecha.tm_hour= atoi(auxiliar);
            leer.getline(auxiliar, 30, '\n');//Minuto Pelicula
            cine->sala[contadorSalas].pelicula[contadorPeliculas].fecha.tm_min= atoi(auxiliar);
                    
          }
          leer.getline(auxiliar, 30, '\n');//<Hora/>
          leer.getline(auxiliar, 30, '\n');//<Silla>
          if((strcmp(auxiliar, "<Sillas>")) == 0){

              leer.getline(auxiliar, 30, '\n');//<Preferencial>

                if((strcmp(auxiliar, "<Preferencial>")) == 0){
                    leer.getline(auxiliar, 30, '\n');//<Disponibles>

                    if((strcmp(auxiliar, "<Disponibles>")) == 0){
                        leer.getline(auxiliar, 30, '\n');//Sillas preferenciales disponibles
                        
                        cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].reservada = false;
                        
                        for(int i = 0; i <= atoi(auxiliar); i++ ){

                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].code = i;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].estado = true;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion = new char[30];
                            strcpy(cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion,"Preferencial" );
                        }
                    }

                    leer.getline(auxiliar, 30, '\n');//<Disponibles/>
                    leer.getline(auxiliar, 30, '\n');//<Reservadas>
                    if((strcmp(auxiliar, "<Reservadas>")) == 0){
                        leer.getline(auxiliar, 30, '\n');//Sillas reservadas
                        for(int i = 0; i <= atoi(auxiliar); i++ ){
                            
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].code = i;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].estado = false;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion = new char[30];
                            strcpy(cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion,"Preferencial" );
                            
                        }
                        
                    }
                }

                leer.getline(auxiliar, 30, '\n');//<Reservadas/>
                leer.getline(auxiliar, 30, '\n');//<General/>
                if((strcmp(auxiliar, "<General>")) == 0){
                      leer.getline(auxiliar, 30, '\n');

                      if((strcmp(auxiliar, "<Disponibles>")) == 0){
                        leer.getline(auxiliar, 30, '\n');//Sillas generales disponibles
                        for(int i = 0; i <= atoi(auxiliar); i++ ){
                            
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].code = i;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].estado = true;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion = new char[30];
                            strcpy(cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion,"General" );
                        }
                        
                      }
          
                      leer.getline(auxiliar, 30, '\n');//<Disponibles/>
                      leer.getline(auxiliar, 30, '\n');//<Reservadas>
                      if((strcmp(auxiliar, "<Reservadas>")) == 0){
                          leer.getline(auxiliar, 30, '\n');//Sillas generales reservada
                          for(int i = 0; i <= atoi(auxiliar); i++ ){
                            
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].code = i;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].estado = false;
                            cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion = new char[30];
                            strcpy(cine->sala[contadorSalas].pelicula[contadorPeliculas].silla[atoi(auxiliar)].identificacion,"General" );
                        }
                     }
                }
           }//sillas
        }// While 3 Fin  Peliculas  
      }// While Fin 2
      
      leer.getline(auxiliar, 30, '\n');
      if((strcmp(auxiliar, "<Sala>")) == 0){
           contadorSalas++;
          //cargarConfiguracionMultiplex();
      }
      
      leer.close(); 
    }//While Fin 1
    //leer.close(); 
return cine;
}

//Funcion que Imprime tiquete de cada silla reservada por el cliente
void printTiquet(char* nombre, char* apellido, char* nombreSala ,char* nombrePelicula, int fecha, char* categoriaSillas, int numeroSilla, int totalDeuda){

        fstream writing;
        string linea;
        writing.open("ticket.txt",ios::app);

        if(writing.fail()){
          cout<< "No se puede abrir el archivo" << endl;
        }

        time_t rawtime;
        struct tm * timeinfo;
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        //https://www.cplusplus.com/reference/ctime/localtime/
        
        writing
        <<" "<<endl
        <<"       Tiquet Multiplex "<<endl
        <<"Fecha: "<<asctime(timeinfo)<<endl
        <<"Cliente: "<<nombre<<" "<<apellido<<endl
        <<"Nombre Sala: "<<nombreSala<<endl
        <<"Nombre Pelicula: "<< nombrePelicula <<endl
        <<"Hora: "<<fecha<<endl
        <<"Numero de Silla: "<<numeroSilla<<endl
        <<"Categoria Silla: "<<categoriaSillas<<endl
        <<"Total a Pagar: $"<<totalDeuda<<endl;

        while (!writing.eof()) {
            getline(writing,linea);
            cout<<linea<<endl;
        }

        writing.close();
}


Silla* Crear_Sillas(int sillas_general, int sillas_preferencial) {

  int sillas_totales = sillas_general + sillas_preferencial;
  Silla* sillas = new Silla[sillas_totales];
  Silla auxiliar;

  for (int y = 0; y < sillas_totales; y ++) {

    if (y < sillas_general) {

        char* identificacion1 = new char[30];
        strcpy(identificacion1, "Preferencial");
        auxiliar.identificacion = identificacion1;
        (*(sillas + y)) = auxiliar;

    }
    else{
        if ((y >= sillas_general) && (y < sillas_totales)) {

            char* identificacion2 = new char[15];
            strcpy(identificacion2, "General");
            auxiliar.identificacion= identificacion2;
            (*(sillas + y)) = auxiliar;

        }
    }
  }

  return sillas;
}

//Adicion de Salas
SalaCine* crear_Sala(int i, short int id, char* nombre, int cupoTotalSillas, char* nombrePelicula, int codigo, tm fecha, int sillas_general, int sillas_preferencial){

  fstream writing2;
  string linea;
  writing2.open("multiplex2020-4.txt",ios::app);

  if(writing2.fail()){
    cout<< "No se puede abrir el archivo" << endl;
  }

  SalaCine* sala = new SalaCine[i];

  if(sala[i].estado==false){

    sala[i].estado = true;

    writing2
    <<"<Sala>"<<endl
    <<"<ID>"<<endl
    <<id<<endl
    <<"<Nombre>"<<endl
    <<nombre<<endl
    <<"<Nombre/>"<<endl
    <<"<Cupo>"<<endl
    <<cupoTotalSillas<<endl
    <<"<Cupo/>"<<endl
    <<"<Pelicula>"<<endl
    <<"<Nombre>"<<endl
    <<nombrePelicula<<endl
    <<"<Nombre/>"<<endl
    <<"<ID>"<<endl
    <<codigo<<endl
    <<"<ID/>"<<endl
    <<"<Fecha>"<<endl
    <<fecha.tm_mday<<endl
    <<"<Fecha/>"<<endl
    <<"<Hora>"<<endl
    <<fecha.tm_hour<<":"<<fecha.tm_min<<endl
    <<"<Hora/>"<<endl
    //Sillas
    <<"<Sillas>"<<endl
    <<"<Preferencial>"<<endl
    <<"<Disponibles>"<<endl
    //Sillas preferenciales disponibles
    <<"<Disponibles/>"<<endl
    <<"<Reservadas>"<<endl
    //Sillas preferenciales Reservadas
    <<"<Reservadas/>"<<endl
    <<"<Preferencial/>"<<endl
    <<"<General>"<<endl
    <<"<Disponibles>"<<endl
    //Sillas Generales Disponibles
    <<"<Disponibles/>"<<endl
    <<"<Reservadas>"<<endl
    //Sillas Generales Reservadas
    <<"<Reservadas/>"<<endl
    <<"<General/>"<<endl
    <<"<Pelicula/>"<<endl
    <<"<Sillas/>"<<endl;

    while (!writing2.eof()) {
            getline(writing2,linea);
            cout<<linea<<endl;
        }

    writing2.close();

  }else{std::cout<<"Esta sala Existe"<<endl;}

  return sala;
}

//Eliminar Sala
SalaCine* eliminar_Sala(int numeroSalaEliminar, SalaCine *sala){
  sala[numeroSalaEliminar].estado = false;

  return sala;
}


//Funcion Que permite que un usuario despues de ver la cartelera reserve Sala y sillas de la pelicula que desea ver en el horario correspondiente.
void ventaTiquete(Actor* cliente){
  short int codigoSeleccion;
  short int totalSillas = 0;

    cout<<"Buen dia estimado Usuario"<<endl;
    cout<<" "<<endl;

    cout<<"Ingresa el codigo de la pelicual: "<<endl;
    cin>>codigoSeleccion;
    //strcpy(usuario.pelicula[0].Codigo, codigoSeleccion);

    cout<<" "<<endl;
    cout<<"Salas Disponibles: "<<endl;
    cout<<" "<<endl;

    cout<<"Sala en la que desea ver la pelicula: "<<endl;
    cin>>codigoSeleccion;

    do{
      
        cout<<"Sillas Disponibles: "<<endl;
        cout<<" "<<endl;
        //Funcion Sillas Disponibles
        cout<<" "<<endl;
        cout<<"Indique Codigo de Silla: "<<endl;
        cin>>codigoSeleccion;
        cout<<" "<<endl;

        cout<<"Desea Reservar mas Sillas? (1->Si | 2->No): "<<endl;
        cin>>codigoSeleccion;
        cout<<" "<<endl;
        system("clear");
        totalSillas++;

    }while(codigoSeleccion==1);

  //Calculando precios




  //Imprimiendo Tiquet
  //Por Cada silla se genera un Tiquet
  for(int i = 0; i < totalSillas; i++){

    printTiquet("Aton","Leal","Grande","BobEsponja",10, "General",i,30.000);
    
  }
  cout<<"Ya se han impreso los tiquetes"<<endl;

}
//Esta funcion es utilizada para eliminar el contenido del HTML
void eliminarContenidoHTML(){
  std::ofstream flujo; flujo.open("cartelera.html", std::ofstream::out | std::ofstream::trunc);
  flujo.close();
  //http://www.cplusplus.com/reference/fstream/ofstream/open/
}

void cartelera(Actor* cine){

  //Se da uso a la función eliminar Contenido HTML para que no se escriba varias veces la pagina y no se repitan las tablas
  eliminarContenidoHTML();

  //se declara variable dinamica de tipo actor, para poder controlar asi los datos recogidos de la pelicula
  cine = new Actor[1];

  // Con el uso de una variable writing se da apertura/cración a cartelera.html
  fstream writing;
  string linea;

  writing.open("cartelera.html",ios::app);

  //En caso de que no pueda ser creada o abierta se dara el siguiente mensaje de error
  if(writing.fail()){
    cout<< "No se puede abrir el archivo" << endl;
  }

  //con Writing escribiremos de manra sencilla el codigo HTML en el archivo correspondiente
    writing

    //En este primer momento se trabaja la inicialización del HTML, su lenguaje, valores para que trabaje con el teclado en español
    <<"<!DOCTYPE html>"<<endl
    <<"<html lang='es'>"<<endl
    <<" "<<endl

    //Este es el head en el que se trabajan los datos mencionados anteriormente
    <<"<head>"<<endl
    <<"<meta charset='UTF-8'>"<<endl
    <<"<meta http-equiv='X-UA-Compatible' content='IE=edge'>"<<endl
    <<"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"<<endl
    //Este Title es crado para darle un nombre a la pestaña
    <<"<title>CARTELERA</title>"<<endl
    //Con este link unimos el HTML a un archivo.css, asi le daremos un mejor diseño
    <<"<link rel='stylesheet' href='EstiloCartelera.css'>"<<endl
    <<"</head>"<<endl
    <<" "<<endl

    //En el cuerpo crearemos la tabla
    <<"<body>"<<endl  


      //con estos div le daremos un orden a la pestaña n la que se visualizara la cartelera
      <<"<div id='General'>"<<endl

        //Agregamos el titulo
        <<"<div id='Titulo'>"<<endl

          <<"<h1>Peliculas en Nuestras Salas</h1>"<<endl
    
        <<"</div>"<<endl
    
        <<"<div id='BannerIzquierdo'>"<<endl
    
        <<"</div>"<<endl

        <<"<div id='BannerDerecho'>"<<endl
    
        <<"</div>"<<endl
    
        <<"<div>"<<endl
                    
          <<"<br><br><br><br>"<<endl


          //Creamos la tabla
          <<"<table>"<<endl

            //Esta primera parte define los titulos de cada columna de la tabla, Saka, Nombre, Hora, Poster
            <<"<tr>"<<endl
              <<"<th>"<<endl
                <<"Sala"<<endl
              <<"</th>"<<endl
              <<"<th>"<<endl
                <<"Nombre"<<endl
              <<"</th>"<<endl
              <<"<th>"<<endl
                <<"Hora"<<endl
              <<"</th>"<<endl
              <<"<th>"<<endl
                <<"Poster"<<endl
              <<"</th>"<<endl
            <<"</tr>"<<endl;

            

            //While utilizado para evitar que el archivo se siga escribiendo  en la linea en la que estaba y de un salto de lina
            //de esta manera de ebita un bucle infinito
            while (!writing.eof()) {
              getline(writing,linea);
              cout<<linea<<endl;
            }

            //Cerramos el archivo
            writing.close();

            
            //Se abre el archivo Cartelera
            writing.open("cartelera.html",ios::app);

            //En este char* nombre Pelicula guardaremos el nombre de las peliculas
            char* nombrePelicula = new char[30];
            //Este for sirve para agregar una tabla del tamaño de las salas disponibles
            for(int i= 0; i < cine[0].numSalas ; i++){//Hay que añadir la cantidad de salas
              //Se escribe en cartelera.html el siguiente codigo para imprimir la tabla

              //copiamos el nombre y lo guardamos en la variable anteriormente mencionada
              strcpy(cine[1].sala[i].pelicula[i].nombre, nombrePelicula);
              
              writing

              //Por cada fila de la tabla se va a escribir la sala en donde se ubica, el nombre de la pelicula y hora

              <<"<tr>"<<endl
              <<"<td>Sala "<<cine[0].sala[i].id<<"</td>"<<endl //añadir funcion de sala 
              <<"<td>"<<nombrePelicula<<"</td>"<<endl //añadir funcion de nombre
              <<"<td>"<<cine[1].sala[i].pelicula[i].fecha.tm_hour<<":"<<cine[0].sala[i].pelicula[i].fecha.tm_min<<"</td>"<<endl; //añadir funcion de horario

              while (!writing.eof()) {
                getline(writing,linea);
                cout<<linea<<endl;
              };

              //Se cierra el archivo para poder utilizar c++
              writing.close();


              //Con estos if compararemos el nombre de la pelicula en la sala con las 7 disponibles debido a las imagenes disponibles
              if((strcmp(nombrePelicula, "BobEsponja")) == 0){
                writing.open("cartelera.html",ios::app);
                writing
                //agregamos la imagen correspondiente
                <<"<td><img id='ImagenCentrada' src='Imagenes/BobEsponja.jpg' style='width:140px;height:240px;'></td>"<<endl;
                writing.close();
              }
              else if ((strcmp(nombrePelicula, "EndGame"))==0){
                writing.open("cartelera.html",ios::app);
                writing
                <<"<td><img id='ImagenCentrada' src='Imagenes/EndGame.jpg' style='width:140px;height:240px;'></td>"<<endl;
                writing.close();
              }
              else if((strcmp(nombrePelicula, "GrandesHeroes"))==0){
                writing.open("cartelera.html",ios::app);
                writing
                <<"<td><img id='ImagenCentrada' src='Imagenes/GrandesHeroes.jpg' style='width:140px;height:240px;'></td>"<<endl;
                writing.close();
              }
              else if((strcmp(nombrePelicula, "MyHeroAcademia"))==0){
                writing.open("cartelera.html",ios::app);
                writing
                <<"<td><img id='ImagenCentrada' src='Imagenes/MyHeroAcademia.jpg' style='width:140px;height:240px;'></td>"<<endl;
                writing.close();
              }
              else if((strcmp(nombrePelicula, "RapidosYFuriosos7"))==0){
                writing.open("cartelera.html",ios::app);
                writing
                <<"<td><img id='ImagenCentrada' src='Imagenes/RapidosYFuriosos7.jpg' style='width:140px;height:240px;'></td>"<<endl;
                writing.close();
              }
              else if((strcmp(nombrePelicula, "ReyLeon"))==0){
                writing.open("cartelera.html",ios::app);
                writing
                <<"<td><img id='ImagenCentrada' src='Imagenes/ReyLeon.jpg' style='width:140px;height:240px;'></td>"<<endl;
                writing.close();
              }
              else if((strcmp(nombrePelicula, "YourName"))==0){
                writing.open("cartelera.html",ios::app);
                writing
                <<"<td><img id='ImagenCentrada' src='Imagenes/YourName.jpg' style='width:140px;height:240px;'></td>"<<endl;
                writing.close();
              }
              writing.open("cartelera.html",ios::app);
              writing

              <<"</tr>"<<endl;

              writing.close();
            }
            
          //cerramos la tabla el div general, el body y el html
          writing.open("cartelera.html",ios::app);
          writing  
            
          <<"</table>"<<endl
    
        <<"</div>"<<endl
    
      <<"</div>"<<endl
    <<"</body>"<<endl

    <<"</html>"<<endl;

  
    while (!writing.eof()) {
            getline(writing,linea);
            cout<<linea<<endl;
    }

    //cerramos por completo el archivo
    writing.close();
}
