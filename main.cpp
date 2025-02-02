#include <iostream> // Para utilizar cout & cin
using namespace std; // Para no estar utilizando std::cout cada vez
#include <cstdio> //Para usar ficheros


void menu(int cantUsuarios); //Defino la función para poderla usar
bool buscarUsuario(char* nombre);
int calcularCantUsuarios();
void agregarUsuario(int& cantUsuario);
void editarUsuario();
void verUsuarios(int cantUsuarios);
void eliminarUsuario(int& cantUsuario);



int main(){
    int cantUsuarios = calcularCantUsuarios();
    menu(cantUsuarios);
}

void menu(int cantUsuarios){
    int opcion = 0;
    do{
        cout<<"!---Hola, bienvenido---!"<<endl;
        cout<<"1. Agregar Usuarios"<<endl;
        cout<<"2. Ver Usuarios"<<endl;
        cout<<"3. Editar Usuarios"<<endl;
        cout<<"4. Eliminar Usuarios"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Elige una opcion"<<endl;
        cin>>opcion;

        switch (opcion)
        {
        case 1:
            agregarUsuario(cantUsuarios);
            break;
        case 2:
            verUsuarios(cantUsuarios);
            break;
        case 3:
            editarUsuario();
            break;
        case 4:
            eliminarUsuario(cantUsuarios);
            break;
        case 5:
            cout<<"Chao, chao!!!"<<endl;
            cout<<"-------------"<<endl;
            break;
        
        default:
            cout<<"Equivocado, intente de nuevo"<<endl;
            cout<<"----------------------------"<<endl;
            break;
        }
    }while(opcion != 5);
}