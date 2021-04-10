/*
Licencia GNU v3
Por: Alejandro Sacristan Leal & Juan Esteban Reyes Tausa
Administrador de Sala de Cine Multiplex
Fecha de Entrega 12/04/21 6:59 AM
**/

#include <iostream>
#include <fstream>
#include <stdio.h>
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

struct Calendario {
  tm fecha;
};

struct Pelicula {
  char* nombre;
  int codigo;
  Calendario* calendario;
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

struct Cliente{
  short int identificacion;
  char* nombre;
  char* apellido;
  Silla* sillas;
  SalaCine* sala;
  Pelicula* pelicula;
};

//FUNCIONES
//Menu de Precentacion del Programa
short int menuInicial(){
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
    system("clear");

    return opcion;
}

//ActorUno
//Menu con Acciones permitadas para los Clientes del Cine
short int menuCliente(){
  short int opcion = 0;

    cout<<" Estimado Cliente que desea?:"<<endl;
    cout<< " " << endl;
    cout<<"1. Ver Cartelera"<<endl; 
    cout<<"1. Adquirir tiquetes"<<endl; 
    cout<<"2. Salir"<<endl;
    cin>>opcion;
    cout<<" "<< endl;
    system("clear");

  return opcion;
}

//ActorDos
//Menu con Acciones permitadas para las taquillas fisicas del Cine
short int menuTaquilla(){
  short int opcion = 0;

  cout<< "Menu Taquilla Fisica"<<endl;
  cout<< "1. Vender tiquetes"<<endl; 
  cout<< " "<< endl;

  system("clear");
  return opcion;
}

//ActorTres
//Menu con Acciones permitadas para el Administrador del Cine
short int menuAdministrador(){
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
    system("clear");

    return opcion;
}

SalaCine* cargarConfiguracionMultiplex(SalaCine* cine){

    ifstream leer("multiplex2020-4.txt", ios::in);
    char* auxiliar = new char[30];

    short int contadorSalas = 0;
    short int contadorPeliculas = 0;
    

    if(!leer.is_open()){ std::cout << "Error: File Open" << '\n';}

    while(!leer.eof()){
      cine = new SalaCine[contadorSalas];

      leer.getline(auxiliar, 30, '\n');//<Sala>
      cout<<auxiliar<<endl;
      while ((strcmp(auxiliar, "<Sala/>")) != 0){

        leer.getline(auxiliar, 30, '\n');// <ID>
        cout<<auxiliar<<endl;

        /*
        if((strcmp(auxiliar, "<ID>")) == 0){
                leer.getline(auxiliar, 30, '\n');// Numero Id
                cine[contadorSalas].id = atoi(auxiliar);
        }

        leer.getline(auxiliar, 30, '\n');//<ID/>
        leer.getline(auxiliar, 30, '\n');//<Nombre/>
        if((strcmp(auxiliar, "<Nombre>")) == 0){
            leer.getline(auxiliar, 30, '\n');
            cine[contadorSalas].nombre = new char[30];
            strcpy(cine[contadorSalas].nombre, auxiliar);
        }

        leer.getline(auxiliar, 30, '\n');//<Nombre/>
        leer.getline(auxiliar, 30, '\n');//<Cupo>
        if((strcmp(auxiliar, "<Cupo>")) == 0){
            leer.getline(auxiliar, 30, '\n');
            cine[contadorSalas].cupoTotalSillas = atoi(auxiliar);
            cout<<auxiliar<<endl;
        }

        leer.getline(auxiliar, 30, '\n');//<Cupo/>
        leer.getline(auxiliar, 30, '\n');//<Pelicula>
        while ((strcmp(auxiliar, "<Pelicula>")) == 0){
          leer.getline(auxiliar, 30, '\n');//<Nombre/>
                
          if((strcmp(auxiliar, "<Nombre>")) == 0){
            leer.getline(auxiliar, 30, '\n');//Nombre Pelicula
            cine[contadorSalas].pelicula[contadorPeliculas].nombre = new char[30];
            strcpy(cine[contadorSalas].pelicula[contadorPeliculas].nombre, auxiliar);
          }

          leer.getline(auxiliar, 30, '\n');//<Nombre/>
          leer.getline(auxiliar, 30, '\n');//<ID>
          if((strcmp(auxiliar, "<ID>")) == 0){
            leer.getline(auxiliar, 30, '\n');//ID Pelicula
            cine[contadorSalas].pelicula[contadorPeliculas].codigo= atoi(auxiliar);    
          }
        }// While 3 Fin
        */
        
      }// While Fin 2
      /*
      leer.getline(auxiliar, 30, '\n');
      if((strcmp(auxiliar, "<Sala>")) == 0){
           contadorSalas++;
          //cargarConfiguracionMultiplex();
      }
      */
      leer.close(); 
    }//While Fin 1
return cine;
}

//Funcion que Imprime tiquete de cada silla reservada por el cliente
void printTiquet(string nombre, string apellido, string nombreSala ,string nombrePelicula, string hora, string categoriaSillas,string numeroSilla, string totalDeuda){

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
        <<"Hora: "<<hora<<endl
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
SalaCine* crear_Sala(int i, short int id, char* nombre, int cupoTotalSillas, char* nombrePelicula, int codigo, Calendario* calendario, tm hora, int sillas_general, int sillas_preferencial){

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
    //Nombre Sala
    <<"<Nombre/>"<<endl
    <<"<Cupo>"<<endl
    //Cupo
    <<"<Cupo/>"<<endl
    <<"<Pelicula>"<<endl
    <<"<Nombre>"<<endl
    //Nombre pelicula
    <<"<Nombre/>"<<endl
    <<"<ID>"<<endl
    //ID pelicula
    <<"<ID/>"<<endl
    <<"<Fecha>"<<endl
    //Fecha
    <<"<Fecha/>"<<endl
    <<"<Hora>"<<endl
    //Hora
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
void ventaTiquete(Cliente* cliente){
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
        cout<<" Indique Codigo de Silla: "<<endl;
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

    printTiquet("Nombre","Apellido","Sala","Nombre Pelicula","Horario", "TipoS Sillas","Numero Silla ","PrecioTotal");

  }
  

}
void eliminarContenidoHTML(){
  std::ofstream flujo; flujo.open("cartelera.html", std::ofstream::out | std::ofstream::trunc);
  flujo.close();
  //http://www.cplusplus.com/reference/fstream/ofstream/open/
}

void cartelera(){
  eliminarContenidoHTML();

  fstream writing;
  string linea,namep="YourName";//jmmm
  writing.open("cartelera.html",ios::app);

  if(writing.fail()){
    cout<< "No se puede abrir el archivo" << endl;
  }

    writing

    <<"<!DOCTYPE html>"<<endl
    <<"<html lang='es'>"<<endl
    <<" "<<endl
    <<"<head>"<<endl
    <<"<meta charset='UTF-8'>"<<endl
    <<"<meta http-equiv='X-UA-Compatible' content='IE=edge'>"<<endl
    <<"<meta name='viewport' content='width=device-width, initial-scale=1.0'>"<<endl
    <<"<title>CARTELERA</title>"<<endl
    <<"<link rel='stylesheet' href='EstiloCartelera.css'>"<<endl
    <<"</head>"<<endl
    <<" "<<endl

    <<"<body>"<<endl  

      <<"<div id='General'>"<<endl

        <<"<div id='Titulo'>"<<endl

          <<"<h1>Peliculas en nuestras salas</h1>"<<endl
    
        <<"</div>"<<endl
    
        <<"<div id='BannerIzquierdo'>"<<endl
    
        <<"</div>"<<endl

        <<"<div id='BannerDerecho'>"<<endl
    
        <<"</div>"<<endl
    
        <<"<div>"<<endl
                    
          <<"<br><br><br><br>"<<endl
    
          <<"<table>"<<endl
    
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
                <<"Img"<<endl
              <<"</th>"<<endl
            <<"</tr>"<<endl;

            while (!writing.eof()) {
              getline(writing,linea);
              cout<<linea<<endl;
            }

            writing.close();

            //Este for sirve para agregar una tabla del tamaño de las salas disponibles
            for(int i= 0; i < 3 ; i++){//Hay que añadir la cantidad de salas

              //Se abre el archivo Cartelera
              writing.open("cartelera.html",ios::app);

              //Se escribe en cartelera.html el siguiente codigo para imprimir la tabla
              writing

              <<"<tr>"<<endl
                <<"<td>Sala "<<i+1<<"</td>"<<endl //añadir funcion de sala 
                <<"<td>"<<namep<<"</td>"<<endl //añadir funcion de nombre
                <<"<td>Horarios</td>"<<endl; //añadir funcion de horario

                while (!writing.eof()) {
                  getline(writing,linea);
                  cout<<linea<<endl;
                };

                //Se cierra el archivo para poder utilizar c++
                writing.close();


                //Con estos if compararemos el nombre de la pelicula en la sala con las 7 disponibles por la imagen
                if(namep == "BobEsponja"){
                  writing.open("cartelera.html",ios::app);
                  writing
                  <<"<td><img id='ImagenCentrada' src='Imagenes/BobEsponja.jpg' style='width:416px;height:594px;'></td>"<<endl;
                  writing.close();
                }
                else if (namep == "EndGame"){
                  writing.open("cartelera.html",ios::app);
                  writing
                  <<"<td><img id='ImagenCentrada' src='Imagenes/EndGame.jpg' style='width:416px;height:594px;'></td>"<<endl;
                  writing.close();
                }
                else if(namep == "GrandesHeroes"){
                  writing.open("cartelera.html",ios::app);
                  writing
                  <<"<td><img id='ImagenCentrada' src='Imagenes/GrandesHeroes.jpg' style='width:416px;height:594px;'></td>"<<endl;
                  writing.close();
                }
                else if(namep == "MyHeroAcademia"){
                  writing.open("cartelera.html",ios::app);
                  writing
                  <<"<td><img id='ImagenCentrada' src='Imagenes/MyHeroAcademia.jpg' style='width:416px;height:594px;'></td>"<<endl;
                  writing.close();
                }
                else if(namep == "RapidosYFuriosos7"){
                  writing.open("cartelera.html",ios::app);
                  writing
                  <<"<td><img id='ImagenCentrada' src='Imagenes/RapidosYFuriosos7.jpg' style='width:416px;height:594px;'></td>"<<endl;
                  writing.close();
                }
                else if(namep == "ReyLeon"){
                  writing.open("cartelera.html",ios::app);
                  writing
                  <<"<td><img id='ImagenCentrada' src='Imagenes/ReyLeon.jpg' style='width:416px;height:594px;'></td>"<<endl;
                  writing.close();
                }
                else if(namep == "YourName"){
                  writing.open("cartelera.html",ios::app);
                  writing
                  <<"<td><img id='ImagenCentrada' src='Imagenes/YourName.jpg' style='width:70px;height:120px;'></td>"<<endl;
                  writing.close();
                }
              writing.open("cartelera.html",ios::app);
              writing

              <<"</tr>"<<endl;

              writing.close();
            }

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

    writing.close();
}

void menuConsolaActores(){
  short int opcionActores = menuInicial();
  if(opcionActores == 1){
    short int opcionAdmin = menuAdministrador();
  }
  if(opcionActores == 2){
    short int opcionCliente = menuCliente();
  }
  if(opcionActores == 3){
    short int opcionTaquilla = menuTaquilla();
  }
  if(opcionActores == 4){
    system("clear");
  }
}


int main(){

    system("clear");
    SalaCine* cine;

    cine = cargarConfiguracionMultiplex(cine);
    //cartelera();
    //menuConsolaActores();

  return 0;
}
