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
#define TAMNRR 5
#define TAMREGISTRO TAMCODIGO + TAMNOMBRE + TAMDESCRIPCION + TAMPRECIO + TAMESPECIALIDAD

using namespace std;

int ultimoNRR;
void llenarCampo(char[], int);
void ordenarIndice();
int contarLineas();
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
        char NRR[TAMNRR];
    public:
        IndiceProducto();
        IndiceProducto(char[], char[]);
        char * getCodigo();
        char * getNRR();
        void setCodigo(char*);
        void setNRR(char*);
};

IndiceProducto::IndiceProducto() {}
IndiceProducto::IndiceProducto(char _codigo[], char _NRR[]){
    strcpy(this->codigo, _codigo);
    strcpy(this->NRR, _NRR);
}

char* IndiceProducto::getCodigo(){
    return this->codigo;
}
char* IndiceProducto::getNRR(){
    return this->NRR;
}
void IndiceProducto::setCodigo(char _codigo[]){
    strcpy(this->codigo, _codigo);
}
void IndiceProducto::setNRR(char _NRR[]){
    strcpy(this->NRR, _NRR);
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
                system("pause");
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
                cout<<"\nElige una opcion correcta"<<endl;
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

void ordenarIndice(){
    IndiceProducto indiceProducto[ultimoNRR + 1];
    ifstream archivoIndice;

    archivoIndice.open("INDICE.txt", ios::in);

    if(archivoIndice.fail()){
        cout<<"No se pudo abrir el archivo (INDICE)"<<endl;
        system("pause");
        exit(1);
    }

    // Obtener los registros del indice y pasarlos a un arreglo
    int counterArreglo = 0;
    while(!archivoIndice.eof()){
        /*  Mientras no sea el final del archivo
            obtiene los datos de cada registro */
        char codigo[TAMCODIGO];
        char NRR[TAMNRR];
        archivoIndice.getline(codigo, TAMCODIGO, '|');
        archivoIndice.getline(NRR, TAMNRR, '\n');
        
        //VERIFICA SI LA LECTURA CONTIENE UN VALOR O YA ES EL ULTIMO SALTO DE LINEA
        if (codigo && strlen(codigo) != 0){
            indiceProducto[counterArreglo].setCodigo(codigo);
            indiceProducto[counterArreglo].setNRR(NRR);
            counterArreglo++;
        }
    }
    archivoIndice.close();

    // Mostrar registros del indice (sin ordenar)
    // for(int i=0; i<ultimoNRR+1; i++){
    //     cout<<"codigo: "<<indiceProducto[i].getCodigo()<<endl;
    //     cout<<"NRR: "<<indiceProducto[i].getNRR()<<endl;
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
    //     cout<<"NRR ordenado: "<<indiceProducto[i].getNRR()<<endl;
    // }

    ofstream indiceOut;
    indiceOut.open("INDICE.txt", std::ofstream::out | std::ofstream::trunc);
    if(indiceOut.fail()){
        cout<<"No se pudo abrir el archivo (INDICE)"<<endl;
        system("pause");
        exit(1);
    }

    for(int i=0; i<ultimoNRR+1; i++){
        indiceOut<<indiceProducto[i].getCodigo()<<"|"<<indiceProducto[i].getNRR()<<endl;
    }
    indiceOut.close();
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

void insertarRegistro(){
    ofstream archivoMenu;
    ofstream archivoIndice;

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

    Producto producto(n, d, p, e);

    cout<<"\nProducto insertado"<<endl;
    producto.mostrar();

    archivoMenu.open("MENU.txt", ios::app);
    if(archivoMenu.fail()){
        cout<<"No se pudo abrir el archivo (MENU)"<<endl;
        system("pause");
        exit(1);
    }

    archivoIndice.open("INDICE.txt", ios::app);
    if(archivoIndice.fail()){
        cout<<"No se pudo abrir el archivo (INDICE)"<<endl;
        system("pause");
        exit(1);
    }

    // Se inserta el registro al archivo
    archivoMenu<<producto;

    //Una vez agregados los datos, va al archivo menu, cuenta la cantidad de lineas registradas (accede a la funcion contar lineas)
    ultimoNRR = contarLineas();
    archivoIndice<<producto.getCodigo()<<"|"<<ultimoNRR<<endl;

    archivoMenu.close();
    archivoIndice.close();
}

void leerRegistro(){
    ifstream archivoMenu;
    ifstream archivoIndice;
    char c[TAMCODIGO] = "";
    int NRREncontrado = 0;
    int distancia, encontrado = 0;

    archivoMenu.open("MENU.txt", ios::in);
    if(archivoMenu.fail()){
        cout<<"No se pudo abrir el archivo (MENU)"<<endl;
        system("pause");
        exit(1);
    }

    archivoIndice.open("INDICE.txt", ios::in);
    if(archivoIndice.fail()){
        cout<<"No se pudo abrir el archivo (INDICE)"<<endl;
        system("pause");
        exit(1);
    }

    // Pedir el código para buscar
    cout<<"Ingresa el codigo a buscar: ";
    cin.ignore();
    cin.getline(c, TAMCODIGO);
    llenarCampo(c, TAMCODIGO);

    // Obtener el NRR utilizando el código
    // Búsqueda secuencial
    while(!archivoIndice.eof() && !encontrado){
        char codigo[TAMCODIGO];
        char NRR[TAMNRR];
        archivoIndice.getline(codigo, TAMCODIGO, '|');
        archivoIndice.getline(NRR, TAMNRR, '\n');

        if(strcmp(c, codigo) == 0){
            encontrado = 1;
            NRREncontrado = stoi(NRR);
        }
    }

    // Buscar el registro con la distancia utilizando el NRR
    if(encontrado){
        distancia = NRREncontrado * (TAMREGISTRO + 1); // Se le suma 1 para pasar a la siguiente linea
        archivoMenu.seekg(distancia);

        // Obtener toda la información para mostrar
        char informacion[TAMREGISTRO];
        archivoMenu.getline(informacion, TAMREGISTRO, '\n');

        cout<<"\nProducto encontrado:"<<endl;
        cout<<informacion<<endl<<endl;
    } else {
        cout<<"\nProducto no encontrado\n"<<endl;
    }

    archivoMenu.close();
}