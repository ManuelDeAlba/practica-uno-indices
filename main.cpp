#include <iostream>
#include <cstring>
#include <fstream>
#include <random> // Generador de numeros aleatorios
#include <chrono> // Para la semilla de numeros aleatorios

#define TAMCODIGO 20
#define TAMNOMBRE 30
#define TAMDESCRIPCION 200
#define TAMPRECIO 10
#define TAMESPECIALIDAD 25

using namespace std;

void llenarCampo(char[], int);
void insertarRegistro();
void leerRegistro();

class Producto{
    private:
        char codigo[TAMCODIGO];
        char nombre[TAMNOMBRE];
        char descripcion[TAMDESCRIPCION];
        char precio[TAMPRECIO];
        char especialidad[TAMESPECIALIDAD];
    public:
        Producto(char[], char[], char[], char[]);
        void mostrar();
        void crearCodigo();

        friend ostream& operator <<(ostream &out, const Producto &p){
            out<<p.codigo<<"|"<<p.nombre<<"|"<<p.descripcion<<"|"<<p.precio<<"|"<<p.especialidad<<endl;
            return out;
        }
};

Producto::Producto(char _nombre[], char _desc[], char _precio[], char _especialidad[]){
    strcpy(nombre, _nombre);
    strcpy(descripcion, _desc);
    strcpy(precio, _precio);
    strcpy(especialidad, _especialidad);

    crearCodigo();
}

void Producto::mostrar(){
    cout<<codigo<<"|"<<nombre<<"|"<<descripcion<<"|"<<precio<<"|"<<especialidad<<endl;
}

void Producto::crearCodigo(){
    //! FORMA CANÓNICA
    /*
        1) Número aleatorio de dos dígitos
        2) Concatenar la primera letra de la especialidad (P, PI, H, B)
        3) Concatenar las 3 primeras letras del nombre de producto
    */

    // Se crea un generador de números aleatorios
    std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(00, 99);
   
    // Variables para obtener las partes de la forma canónica
    char especial[TAMESPECIALIDAD] = "PICAR Y COMPARTIR"; // Cadena para comparar con la especialidad
    llenarCampo(especial, TAMESPECIALIDAD);

    char c[20] = "";
    int aleatorio = distribution(generator);
    char cEspecialidad[3] = "";
    char cNombre[4] = {nombre[0], nombre[1], nombre[2]};

    // Tomar las 2 primeras letras si la especialidad es "PICAR Y COMPARTIR"
    if(strcmp(especialidad, especial) == 0){
        // Si es picar y compartir
        cEspecialidad[0] = especialidad[0];
        cEspecialidad[1] = especialidad[1];
    } else {
        cEspecialidad[0] = especialidad[0];
    }

    // Concatenar las partes a la variable temporal
    sprintf(c, "%02d", aleatorio);
    strcat(c, cEspecialidad);
    strcat(c, cNombre);

    // Rellenar con espacios
    llenarCampo(c, 20);

    // Copiar la cadena temporal en el código
    strcpy(codigo, c);
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

    char n[TAMNOMBRE] = "";
    char d[TAMDESCRIPCION] = "";
    char p[TAMPRECIO] = "";
    char e[TAMESPECIALIDAD] = "";

    cout<<"Ingresa el nombre: ";
    cin.ignore();
    cin.getline(n, TAMNOMBRE, '\n');
    cout<<"Ingresa la descripcion: ";
    cin.getline(d, TAMDESCRIPCION, '\n');
    cout<<"Ingresa el precio: ";
    cin.getline(p, TAMPRECIO, '\n');
    cout<<"Ingresa la especialidad: ";
    cin.getline(e, TAMESPECIALIDAD, '\n');

    //!--------------------PARA ELEGIR ESPECIALIDAD, HACER UN MENU CON LAS 3 OPCIONES---------------------

    // Rellenar con espacios
    llenarCampo(n, TAMNOMBRE);
    llenarCampo(d, TAMDESCRIPCION);
    llenarCampo(p, TAMPRECIO);
    llenarCampo(e, TAMESPECIALIDAD);

    Producto a(n, d, p, e);

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
        char codigo[TAMCODIGO];
        char nombre[TAMNOMBRE];
        char descripcion[TAMDESCRIPCION];
        char precio[TAMPRECIO];
        char especialidad[TAMESPECIALIDAD];

        archivo.getline(codigo, TAMCODIGO, '|');
        archivo.getline(nombre, TAMNOMBRE, '|');
        archivo.getline(descripcion, TAMDESCRIPCION, '|');
        archivo.getline(precio, TAMPRECIO, '|');
        archivo.getline(especialidad, TAMESPECIALIDAD, '\n');

        // Si existen los datos se muestran
        if(codigo != "" && nombre != "" && descripcion != "" && precio != "" && especialidad != ""){
            cout<<codigo<<"|"<<nombre<<"|"<<descripcion<<"|"<<precio<<"|"<<especialidad<<endl;
        }
    }

    archivo.close();
}