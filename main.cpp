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
#define TAMNNR 5
#define TAMREGISTRO TAMCODIGO + TAMNOMBRE + TAMDESCRIPCION + TAMPRECIO + TAMESPECIALIDAD + 5

using namespace std;

int ultimoNRR;
void llenarCampo(char[], int);
void insertarRegistro();
void leerRegistro();
void ordenarIndice();
int contarLineas();

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
        char* getCodigo();

        friend ostream& operator <<(ostream &out, const Producto &p)
        {
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

char* Producto::getCodigo(){
    return this->codigo;
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

class IndiceProducto{
    private:
        char codigo[TAMCODIGO];
        char nrr[TAMNNR];
    public:
        IndiceProducto();
        IndiceProducto(char[], char[]);
        char * getCodigo();
        char * getNrr();
        void setCodigo(char*);
        void setNrr(char*);
};

IndiceProducto::IndiceProducto() {}
IndiceProducto::IndiceProducto(char _codigo[], char _nrr[]){
    strcpy(this->codigo, _codigo);
    strcpy(this->nrr, _nrr);
}

char* IndiceProducto::getCodigo(){
    return this->codigo;
}
char* IndiceProducto::getNrr(){
    return this->nrr;
}
void IndiceProducto::setCodigo(char _codigo[]){
    strcpy(this->codigo, _codigo);
}
void IndiceProducto::setNrr(char _nrr[]){
    strcpy(this->nrr, _nrr);
}

int main(){
    char op;
    do{
        system("cls");
        cout<<"1) Insertar"<<endl;
        cout<<"2) Consultar por codigo"<<endl;
        cout<<"3) Salir"<<endl;
        cout<<"Elige una opcion: ";
        cin>>op;

        switch(op){
            case '1':
                system("cls");
                insertarRegistro();
                ordenarIndice();
                break;
            case '2':
                system("cls");
                cout<<"Consulta por codigo:"<<endl;
                leerRegistro();
                system("pause");
                break;
            case '3':
                break;
            default:
                system("cls");
                cout<<"Elige una opcion correcta"<<endl;
                system("pause");
                break;
        }
    } while(op != '3');

    return 0;
}

void ordenarIndice(){
    IndiceProducto indiceProducto[ultimoNRR + 1];
    ifstream indiceArchivo;

    indiceArchivo.open("INDICE.txt", ios::in);

    if(indiceArchivo.fail()){
        cout<<"No se pudo abrir el archivo (INDICE)"<<endl;
        system("pause");
        exit(1);
    }

    int counterArreglo = 0;
    while(!indiceArchivo.eof()){
        /*  Mientras no sea el final del archivo
            obtiene los datos de cada registro */
        char codigo[TAMCODIGO];
        char nnr[TAMNNR];
        indiceArchivo.getline(codigo, TAMCODIGO, '|');
        indiceArchivo.getline(nnr, TAMNNR, '\n');
        
        //VERIFICA SI LA LECTURA CONTIENE UN VALOR O YA ES EL ULTIMO SALDO DE LINEA
        if (codigo && strlen(codigo) != 0){
            indiceProducto[counterArreglo].setCodigo(codigo);
            indiceProducto[counterArreglo].setNrr(nnr);
            counterArreglo++;
        }
    }
    indiceArchivo.close();

    // Mostrar registros del indice (sin ordenar)
    // for(int i=0; i<ultimoNRR+1; i++){
    //     cout<<"codigo: "<<indiceProducto[i].getCodigo()<<endl;
    //     cout<<"nnr: "<<indiceProducto[i].getNrr()<<endl;
    // }

    //VERIFICA LA ULTIMA POSICION PARA COLOCAR LA POSICION CORRESPONDIENTE
    IndiceProducto auxIndice;
    if((ultimoNRR+1)>1){
        for(int i =1; i<ultimoNRR+1; i++){
            for(int j =0; j<(ultimoNRR+1)-i; j++){
                if(strcmp(indiceProducto[j].getCodigo(),indiceProducto[j+1].getCodigo()) > 0){
                    auxIndice=indiceProducto[j];
                    indiceProducto[j]=indiceProducto[j+1];
                    indiceProducto[j+1]=auxIndice;
                }
            }
        }
    }

    // Mostrar registros del indice (ordenados)
    // for(int i=0; i<ultimoNRR+1; i++){
    //     cout<<"codigo ordenado: "<<indiceProducto[i].getCodigo()<<endl;
    //     cout<<"nnr ordenado: "<<indiceProducto[i].getNrr()<<endl;
    // }

    ofstream indiceOut;
    indiceOut.open("INDICE.txt", std::ofstream::out | std::ofstream::trunc);
    if(indiceOut.fail()){
        cout<<"No se pudo abrir el archivo (INDICE)"<<endl;
        system("pause");
        exit(1);
    }

    for(int i=0; i<ultimoNRR+1; i++){
        indiceOut<<indiceProducto[i].getCodigo()<<"|"<<indiceProducto[i].getNrr()<<endl;
    }
    indiceOut.close();
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
    ofstream indice;

    // Se piden todos los datos del producto
    char n[TAMNOMBRE] = "";
    char d[TAMDESCRIPCION] = "";
    char p[TAMPRECIO] = "";
    char e[TAMESPECIALIDAD] = "";

    cout<<"INGRESA LOS DATOS EN MAYUSCULAS"<<endl;
    cout<<"Ingresa el nombre: ";
    cin.ignore();
    cin.getline(n, TAMNOMBRE, '\n');
    cout<<"Ingresa la descripcion: ";
    cin.getline(d, TAMDESCRIPCION, '\n');
    cout<<"Ingresa el precio: ";
    cin.getline(p, TAMPRECIO, '\n');

    char op;
    do{
        cout<<"1) PIZZAS"<<endl;
        cout<<"2) PICAR Y COMPARTIR"<<endl;
        cout<<"3) HELADOS"<<endl;
        cout<<"4) BEBIDAS"<<endl;
        cout<<"Ingresa la especialidad: ";
        cin>>op;

        switch(op){
            case '1':
                strcpy(e, "PIZZAS");
                break;
            case '2':
                strcpy(e, "PICAR Y COMPARTIR");
                break;
            case '3':
                strcpy(e, "HELADOS");
                break;
            case '4':
                strcpy(e, "BEBIDAS");
                break;
            default:
                cout<<"Elige una opcion correcta"<<endl;
                system("pause");
                break;
        }
    } while(op != '1' && op != '2' && op != '3' && op != '4');

    // Rellenar con espacios
    llenarCampo(n, TAMNOMBRE);
    llenarCampo(d, TAMDESCRIPCION);
    llenarCampo(p, TAMPRECIO);
    llenarCampo(e, TAMESPECIALIDAD);

    Producto a(n, d, p, e);

    cout<<"\nProducto insertado"<<endl;
    a.mostrar();

    archivo.open("MENU.txt", ios::app);
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo (MENU)"<<endl;
        system("pause");
        exit(1);
    }

    indice.open("INDICE.txt", ios::app);
    if(indice.fail()){
        cout<<"No se pudo abrir el archivo (INDICE)"<<endl;
        system("pause");
        exit(1);
    }

    // Se inserta el registro al archivo
    archivo<<a;

    //Una vez agregados los datos, va al archivo menu, cuenta la cantidad de lineas registradas (accede a la funcion contar lineas)
    ultimoNRR = contarLineas();
    indice<<a.getCodigo()<<"|"<<ultimoNRR<<endl;

    archivo.close();
    indice.close();

    system("pause");
}

void leerRegistro(){
    //! POR AHORA LEE TODOS LOS REGISTROS (CAMBIAR)
    //! UTILIZAR EL INDICE
    ifstream archivo;

    archivo.open("MENU.txt", ios::in);

    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo (MENU)"<<endl;
        system("pause");
        exit(1);
    }

    while(!archivo.eof()){
        /*  Mientras no sea el final del archivo
            obtiene los datos de cada registro */
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

//Revisa el archivo menu para determinar cuantos registros se encuentran guardados y saber el ultimo NRR
int contarLineas(){
    int lineas = 0;
    ifstream in("MENU.txt");
    char unused[TAMREGISTRO] = "";
    while (in.getline(unused, TAMREGISTRO))
        ++lineas;
    return lineas-1;
}