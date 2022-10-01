/*
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream> // Creación, escritura y lectura de archivos

using namespace std;

void escribir();
void leer();
void agregar();

int main(){
    escribir();

    leer();

    // agregar();

    // leer();

    system("pause");
    return 0;
}

void escribir(){
    ofstream archivo;

    archivo.open("empleados.txt", ios::out); // ios::out Abrir archivo output

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }

    archivo<<"Manuel|19|Estudiante\n";
    archivo<<"Fernando|18|Empresario\n";
    archivo<<"Itzel|17|Cocinera\n";

    archivo.close();
}

void leer(){
    ifstream archivo;
    string texto;

    archivo.open("empleados.txt", ios::in);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }

    while(!archivo.eof()){ // Mientras no sea el final del archivo
        string nombre, edad, ocupacion;

        getline(archivo, nombre, '|'); // Obtiene el nombre
        getline(archivo, edad, '|'); // Obtiene el nombre
        getline(archivo, ocupacion, '\n'); // Obtiene la ocupacion

        // Si existen los datos
        if(nombre != "" && edad != "" && ocupacion != ""){
            cout<<"Nombre: "<<nombre<<" - Edad: "<<edad<<" - Ocupacion: "<<ocupacion<<endl;
        }
    }

    archivo.close();
}

void agregar(){
    ofstream archivo;

    archivo.open("empleados.txt", ios::app);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }

    archivo<<"Berenice|16|Arquitecta"<<endl;

    archivo.close();
}
*/

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void llenarCampo(char[], int);
void insertarRegistro();
void leerRegistro();

class Producto{
    private:
        char codigo[20];
        char nombre[30];
        char descripcion[100];
        char precio[10];
    public:
        Producto(char[], char[], char[], char[]);
        void mostrar();

        friend ostream& operator <<(ostream &out, const Producto &p){
            out<<p.codigo<<"|"<<p.nombre<<"|"<<p.descripcion<<"|"<<p.precio<<endl;
            return out;
        }

        friend istream& operator >>(istream &in, Producto &p){
            
            return in;
        }
};

Producto::Producto(char _codigo[], char _nombre[], char _desc[], char _precio[]){
    strcpy(codigo, _codigo);
    strcpy(nombre, _nombre);
    strcpy(descripcion, _desc);
    strcpy(precio, _precio);
}

void Producto::mostrar(){
    cout<<codigo<<"|"<<nombre<<"|"<<descripcion<<"|"<<precio<<endl;
}

int main(){
    char op;
    do{
        cout<<"1) Insertar"<<endl;
        cout<<"2) Consultar por codigo"<<endl;
        cout<<"3) Salir"<<endl;
        cout<<"Elige una opcion: ";
        cin>>op;

        switch(op){
            case '1':
                cout<<"Insertando"<<endl;
                insertarRegistro();
                break;
            case '2':
                cout<<"Consultando por codigo"<<endl;
                leerRegistro();
                break;
            case '3': break;
            default:
                cout<<"Elige una opcion correcta"<<endl;
                system("pause");
                break;
        }
    } while(op != '3');

    return 0;
}

void llenarCampo(char cadena[], int tam){
    // Si el caracter actual no contiene nada, se sustituye por un espacio
    // El último caracter no se sustituye porque es \0
    for(int i = 0; i < tam - 1; i++){
        if(!cadena[i]) cadena[i] = ' ';
    }
}

void insertarRegistro(){
    ofstream archivo;

    char c[20] = "";
    char n[30] = "";
    char d[100] = "";
    char p[10] = "";

    cout<<"Ingresa el codigo: ";
    cin.ignore();
    cin.getline(c, 20, '\n');
    cout<<"Ingresa el nombre: ";
    cin.getline(n, 30, '\n');
    cout<<"Ingresa la descripcion: ";
    cin.getline(d, 100, '\n');
    cout<<"Ingresa el precio: ";
    cin.getline(p, 10, '\n');

    // Rellenar con espacios
    llenarCampo(c, 20);
    llenarCampo(n, 30);
    llenarCampo(d, 100);
    llenarCampo(p, 10);

    Producto a(c, n, d, p);

    a.mostrar();

    archivo.open("Productos.txt", ios::app);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo"<<endl;
    }

    // Se inserta el registro al archivo
    archivo<<a;

    archivo.close();
}

void leerRegistro(){
    //! POR AHORA LEE TODOS LOS REGISTROS
    ifstream archivo;

    archivo.open("Productos.txt", ios::in);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo"<<endl;
        exit(1);
    }

    while(!archivo.eof()){
        /*  Mientras no sea el final del archivo
            obtiene los datos de cada registro
        */
        char codigo[20];
        char nombre[30];
        char descripcion[100];
        char precio[10];

        archivo.getline(codigo, 20, '|');
        archivo.getline(nombre, 30, '|');
        archivo.getline(descripcion, 100, '|');
        archivo.getline(precio, 10, '\n');

        // Si existen los datos se muestran
        if(codigo != "" && nombre != "" && descripcion != "" && precio != ""){
            cout<<codigo<<"|"<<nombre<<"|"<<descripcion<<"|"<<precio<<endl;
        }
    }

    archivo.close();
}