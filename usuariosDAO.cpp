#include <iostream>
using namespace std;
#include <cstdio>
#include <cstring>
#include "datos.h"


//Calcular Cantidad de Usuarios
int calcularCantUsuarios(){
    FILE *archi;
    int numRegs;
    archi=fopen("usuarios.txt","a");
    fseek(archi,0,SEEK_END);
    numRegs = ftell(archi) / sizeof(Usuario);
    fclose(archi);
    return numRegs;
}

//Buscar Usuario
bool buscarUsuario(char* nombre){
    FILE *usuarios;
    Usuario temp;

    usuarios = fopen("usuarios.txt","r");

    while(feof(usuarios)==0){
        fread(&temp,sizeof(Usuario),1,usuarios);
        if(!feof(usuarios)){
            if(strcmp(temp.nombre,nombre)==0){
                fclose(usuarios);
                return true;
            }
        }
    }
    fclose(usuarios);
    return false;
}

//Agregar Usuario
void agregarUsuario(int& cantUsuario){
    FILE *archi; 
    archi = fopen("usuarios.txt","a");
    Usuario nuevoUsuario;
    cout<<"-----*******************-----"<<endl;
    cout<<"-----Registro de Usuario-----"<<endl;
    cout<<"Digite el nombre de usuario"<<endl;
    cin>>nuevoUsuario.nombre;

    if(buscarUsuario(nuevoUsuario.nombre)){
        cout<<"------------------------------------------------"<<endl;
        cout<<"El nombre ya existe, intenta nuevamente con otro"<<endl;
        cout<<"------------------------------------------------"<<endl;
        agregarUsuario(cantUsuario);
    }else{
        cout<<"Digite la password"<<endl;
        cin>>nuevoUsuario.pass;
        cin.ignore();
        cout<<"Digite tu edad"<<endl;
        cin>>nuevoUsuario.edad;
        cin.ignore();
        fwrite(&nuevoUsuario, sizeof(Usuario),1,archi);
        fflush(stdin);
        fclose(archi);  
        cantUsuario++;
    }
}

//Editar Usuario
void editarUsuario(){
    char nombre[30];
    cout<<"-----**************-----"<<endl;
    cout<<"-----Editar Usuario-----"<<endl;
    cout<<"Que usuario deseas editar?"<<endl;
    cin>>nombre;

    if(buscarUsuario(nombre)){
        FILE *usuarios, *temporalUsuario;
        Usuario temp;

        usuarios = fopen("usuarios.txt","r");
        temporalUsuario = fopen ("temporalUsuario.txt","a");

        while(feof(usuarios)==0){
            fread(&temp,sizeof(Usuario),1,usuarios);
            if(!feof(usuarios)){
                if(strcmp(temp.nombre,nombre)!=0){
                    fwrite(&temp,sizeof(Usuario),1,temporalUsuario);
                    fflush(stdin);
                }
                else{
                    Usuario usuarioEditado;
                    bool bandera;
                    do{
                        cout<<"Escribe su nuevo nombre. Actual:("<<temp.nombre<<")"<<endl;
                        cin>>usuarioEditado.nombre;
                
                        bandera = buscarUsuario(usuarioEditado.nombre);
                        if(!bandera){
                            cout<<"Escriba su nueva password. Actual:("<<temp.pass<<")"<<endl;
                            cin>>usuarioEditado.pass;
                            cout<<"Escriba su nueva edad. Actual:("<<temp.edad<<")"<<endl;
                            cin>>usuarioEditado.edad;
                    
                            fwrite(&usuarioEditado,sizeof(Usuario),1,temporalUsuario);
                            cout<<"Usuario modificado"<<endl;
                            break;
                        }
                    }while(bandera);
                }
            }
        }   

        fclose(usuarios);
        fclose(temporalUsuario);

        remove("usuarios.txt");
        rename("temporalUsuario.txt","usuarios.txt");
    }else{
        cout<<"No se encontro el usuario"<<endl;
    } 
}

//Ver todos los usuarios
void verUsuarios(int cantUsuarios){
    cout<<"-----*****************-----"<<endl;
    cout<<"-----Lista de Usuarios-----"<<endl;
    if(cantUsuarios==0){
        cout<<"-!Aun no existen usuarios!-"<<endl;
        cout<<endl;
    }else{
        FILE *file;
        file = fopen("usuarios.txt","r");
        Usuario usuarioActual;
        while(feof(file)==0){
            fread(&usuarioActual,sizeof(Usuario),1,file);
            if(!feof(file)){ // Verifica si no se ha llegado al final del archivo
                cout<<"-------------------"<<endl;
                cout<<"Nombre"<<endl;
                cout<<usuarioActual.nombre<<endl;
                cout<<"Password"<<endl;
                cout<<usuarioActual.pass<<endl;
                cout<<"Edad"<<endl;
                cout<<usuarioActual.edad<<endl;
                cout<<endl;
            }
        }
        fflush(stdin);
        fclose(file);
    }
}

//Eliminar Usuario
void eliminarUsuario(int& cantUsuarios){


    if(cantUsuarios==0){
        cout<<"-!Aun no existen usuarios!-"<<endl;
        cout<<endl;
    }else{
        cout<<"-----****************-----"<<endl;
        cout<<"-----Eliminar usuario-----"<<endl;
        char nombre[30];
        cout<<"Que usuario deseas eliminar?"<<endl;
        cin>>nombre;

        if(buscarUsuario(nombre)){
            FILE *usuarios, *temporal;
            Usuario temp;

            usuarios = fopen("usuarios.txt","r");
            temporal = fopen ("temporalUsuarios.txt","a");

            while(feof(usuarios)==0){
                fread(&temp,sizeof(Usuario),1,usuarios);
                if(!feof(usuarios)){
                    if(strcmp(temp.nombre,nombre)!=0){
                        fwrite(&temp,sizeof(Usuario),1,temporal);
                    }
                }
            }

            cout<<"Usuario eliminado con exito"<<endl;
            cantUsuarios--;

            fclose(usuarios);
            fclose(temporal);

            remove("usuarios.txt");
            rename("temporalUsuarios.txt","usuarios.txt");
        }else{
            cout<<"No se encontro el usuario"<<endl;
        }
    }

    
}

