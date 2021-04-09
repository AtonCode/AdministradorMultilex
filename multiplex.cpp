/*
Licencia GNU v3
Por: Alejandro Sacristan Leal
Administrador de Sala de Cine Multiplex
Fecha de Entrega 12/04/21 6:59
**/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h> 
#include <ctime>
#include <iomanip>
#include <sstream>


using namespace std;

//ESTRUCTURAS
struct Silla {
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
};

struct SalaCine {
    short int id;
    bool estado;
    char* nombre;
    int cupoTotalSillas;
    Pelicula* pelicula;
    Silla* silla;
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

void cargarConfiguracionMultiplex(SalaCine* cine){

    ifstream leer("multiplex2020-4.txt", ios::in);
    char* auxiliar = new char[30];
    short int contadorSalas = 0;
    if(!leer.is_open()){ std::cout << "Error: File Open" << '\n';}

    while(!leer.eof()){

        cine = new SalaCine[1];
      
        leer.getline(auxiliar, 30, '\n');//<Sala>
        while ((strcmp(auxiliar, "<Sala/>")) != 0){

            leer.getline(auxiliar, 30, '\n');
            cout<<auxiliar<<endl;

            if((strcmp(auxiliar, "<ID>")) == 0){
                leer.getline(auxiliar, 30, '\n');// Numero Id
                cine[1].id = atoi(auxiliar);
            }

            leer.getline(auxiliar, 30, '\n');//<ID/>
            leer.getline(auxiliar, 30, '\n');//<Nombre/>
            if((strcmp(auxiliar, "<Nombre>")) == 0){
                leer.getline(auxiliar, 30, '\n');
                cine[1].nombre = new char[30];
                strcpy(cine[1].nombre, auxiliar);
            }

            leer.getline(auxiliar, 30, '\n');//<Nombre/>
            leer.getline(auxiliar, 30, '\n');//Cupo
            if((strcmp(auxiliar, "<Cupo>")) == 0){
                leer.getline(auxiliar, 30, '\n');
                cine[1].cupoTotalSillas = atoi(auxiliar);
            }

            leer.getline(auxiliar, 30, '\n');//<Cupo/>
            leer.getline(auxiliar, 30, '\n');//<Pelicula/>
            if((strcmp(auxiliar, "<Pelicula>")) == 0){

                leer.getline(auxiliar, 30, '\n');//<Nombre/>
                
                if((strcmp(auxiliar, "<Nombre>")) == 0){
                    leer.getline(auxiliar, 30, '\n');//Nombre Pelicula
                    cine[1].pelicula[1].nombre = new char[30];
                    strcpy(cine[1].pelicula[1].nombre, auxiliar);

                }

                leer.getline(auxiliar, 30, '\n');//<Nombre/>
                leer.getline(auxiliar, 30, '\n');//<ID>
                if((strcmp(auxiliar, "<ID>")) == 0){
                    leer.getline(auxiliar, 30, '\n');//ID Pelicula
                    cine[1].pelicula[1].codigo= atoi(auxiliar);
                    
                }

                leer.getline(auxiliar, 30, '\n');//<ID/>
                leer.getline(auxiliar, 30, '\n');//<Fecha>
                if((strcmp(auxiliar, "<Fecha>")) == 0){

                    leer.getline(auxiliar, 30, '/');//Dia Pelicula
                    cine[1].pelicula[1].calendario[1].fecha.tm_mday= atoi(auxiliar);
                    leer.getline(auxiliar, 30, '/');//Mes Pelicula
                    cine[1].pelicula[1].calendario[1].fecha.tm_mon= atoi(auxiliar);
                    leer.getline(auxiliar, 30, '\n');//Año Pelicula
                    cine[1].pelicula[1].calendario[1].fecha.tm_year= atoi(auxiliar);

                    
                }

                leer.getline(auxiliar, 30, '\n');//<Fecha/>
                leer.getline(auxiliar, 30, '\n');//<Hora>
                if((strcmp(auxiliar, "<Hora>")) == 0){

                    leer.getline(auxiliar, 30, ':');//Hora Pelicula
                    cine[1].pelicula[1].calendario[1].fecha.tm_hour= atoi(auxiliar);
                    leer.getline(auxiliar, 30, '\n');//Minuto Pelicula
                    cine[1].pelicula[1].calendario[1].fecha.tm_min= atoi(auxiliar);
                    
                }
                leer.getline(auxiliar, 30, '\n');//<Hora/>
                leer.getline(auxiliar, 30, '\n');//<Pelicula/>
            }

            leer.getline(auxiliar, 30, '\n');//<Silla>
            if((strcmp(auxiliar, "<Sillas>")) == 0){

                leer.getline(auxiliar, 30, '\n');//<Preferencial>

                if((strcmp(auxiliar, "<Preferencial>")) == 0){
                    leer.getline(auxiliar, 30, '\n');//<Disponibles>

                    if((strcmp(auxiliar, "<Disponibles>")) == 0){
                        leer.getline(auxiliar, 30, '\n');//Sillas preferenciales disponibles
                        
                        cine[1].sillasTotalPreferencial = atoi(auxiliar);
                        cine[1].silla[atoi(auxiliar)].identificacion = new char[30];
                        for(int i = 0; i <= atoi(auxiliar); i++ ){
                            strcpy(cine[1].silla[i].identificacion, "Preferencial");
                            cine[1].silla[i].estado = true;
                            cine[1].silla[i].reservada= false;
                            
                        }

                    }

                    leer.getline(auxiliar, 30, '\n');//<Disponibles/>
                    leer.getline(auxiliar, 30, '\n');//<Reservadas>
                    if((strcmp(auxiliar, "<Reservadas>")) == 0){
                        leer.getline(auxiliar, 30, '\n');//Sillas preferenciales reservadas
                        leer.getline(auxiliar, 30, '\n');//<Reservadas/>
                    }
                }

                if((strcmp(auxiliar, "<General>")) == 0){
                      leer.getline(auxiliar, 30, '\n');

                      if((strcmp(auxiliar, "<Disponibles>")) == 0){
                        leer.getline(auxiliar, 30, '\n');//Sillas generales disponibles
                        leer.getline(auxiliar, 30, '\n');//<Disponibles/>
                      }
          
                      leer.getline(auxiliar, 30, '\n');//<Reservadas>
                      if((strcmp(auxiliar, "<Reservadas>")) == 0){
                          leer.getline(auxiliar, 30, '\n');//Sillas generales reservadas
                          leer.getline(auxiliar, 30, '\n');//<Reservadas/>
                      }
                }
            }
      }
    
        leer.getline(auxiliar, 30, '\n');
        if((strcmp(auxiliar, "<Sala>")) == 0){
                //cargarConfiguracionMultiplex();
            }
        leer.close();
        
    }

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
        strcpy(identificacion1, "Clasic");
        auxiliar.identificacion = identificacion1;
        (*(sillas + y)) = auxiliar;

    }
    else{
        if ((y >= sillas_general) && (y < sillas_totales)) {

            char* identificacion2 = new char[15];
            strcpy(identificacion2, "Diamont");
            auxiliar.identificacion= identificacion2;
            (*(sillas + y)) = auxiliar;

        }
    }
  }

  return sillas;
}

//Adicion de Salas
SalaCine* crear_Sala(int i, int sillas_general, int sillas_preferencial){

  SalaCine* sala = new SalaCine[i];

  if(sala[i].estado==false){

    sala[i].estado = true;
    
    //sala[i].Horarios =

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

int main(){
    system("clear");
    SalaCine* cine;
    printTiquet("Nombre","Apellido","Sala","Nombre Pelicula","Horario", "TipoS Sillas","Numero Silla ","PrecioTotal");
    cargarConfiguracionMultiplex(cine);

    
  return 0;
}
