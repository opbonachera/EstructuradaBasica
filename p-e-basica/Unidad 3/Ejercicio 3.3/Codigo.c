#include <stdio.h>
#include <string.h>

struct PRODUCTO
{
    int   Codigo;
    float Precio;
    char  Descripcion[2];
};

int   ValidarEntero(int,int,int);
int   LeerArchivo(struct PRODUCTO[]);
int   Busqueda(struct PRODUCTO[], int, int);
float ValidarReal(float,float,float);
void  ValidarCadena(char[],int);
void  ActualizarDatos(struct PRODUCTO[],int);
void  GrabarArchivo(struct PRODUCTO[],int);

int main(){
    struct PRODUCTO P[50];
    int CantProductos;

    CantProductos = LeerArchivo(P);
    ActualizarDatos(P,CantProductos);
    GrabarArchivo(P,CantProductos);

    return 0;
}

void GrabarArchivo(struct PRODUCTO P[], int CantProd){
    int i=0;
    FILE *archivo;

    archivo = fopen("productosactualizados.dat","wb");

    printf("---GRABANDO ARCHIVO---\n");
    if(archivo==NULL){
        printf("Error al abrir el archivo. \n");
    }else{
        for(i=0;i<CantProd;i++){
            fwrite(&P[i],sizeof(struct PRODUCTO),1,archivo);
        }
    }

    fclose(archivo);
    printf("---ARCHIVO GRABADO CORRECTAMENTE---\n");
}


void ActualizarDatos(struct PRODUCTO P[], int CantProd){
    int Codigo, i=0, Pos;
    float Precio;

    printf("---ACTUALIZACION DE PRODUCTOS---\n");
    printf("Ingrese el codigo del producto que desea actualizar...\n");
    Codigo=ValidarEntero(1,100000,0);

    while(Codigo!=0){

        Pos = Busqueda(P,Codigo,CantProd);

        if(Pos!=-1){
            printf("Ingrese el nuevo precio del producto...\n");
            Precio=ValidarReal(1.,10000000000.,1.);

            P[Pos].Precio=Precio;
            i++;
        }else{
            printf("Articulo no encontrado. \n");
        }

        printf("Ingrese el codigo del producto o 0 para terminar...\n");
        Codigo=ValidarEntero(1,100000,0);
    }

    printf("---FIN DE ACTUALIZACION DE PRODUCTOS---\n");
    printf("Se actualizaron %d productos. \n",i);
}

int Busqueda(struct PRODUCTO P[], int Buscado, int Cant){
    int pos=-1, i=0;

    while(pos==-1 && i<Cant){
        if(P[i].Codigo==Buscado){
            pos=i;
        }else{
            i++;
        }
    }
    return pos;
}

int LeerArchivo(struct PRODUCTO P[]){
    int i=0, j;
    FILE *archivo;

    archivo = fopen("PRODUCTOS.dat","rb");

    printf("---LEYENDO ARCHIVO---\n");
    if(archivo==NULL){
        printf("Error al leer el archivo. \n");
    }else{
        while(!feof(archivo)){
            fread(&P[i],sizeof(struct PRODUCTO),1,archivo);
            i++;
    }
    }
    fclose(archivo);

    printf("---CONTENIDO DEL ARCHIVO---\n");

    for(j=0;j<i;j++){
        printf("CODIGO %d \nPRECIO %.2f \nDESCRIPCION %s \n-------\n",P[j].Codigo, P[j].Precio, P[j].Descripcion);
    }
    return i;
}

int ValidarEntero(int Li,int Ls,int Cf){
    int Entero;
    do{
        printf("");
        scanf("%d",&Entero);
    }while(!((Entero>=Li && Entero<=Ls)||(Entero==Cf)));
    return Entero;
}

float ValidarReal(float Li,float Ls,float Cf){
    float Real;
    do{
        printf("");
        scanf("%f",&Real);
    }while(!((Real>=Li && Real<=Ls)||(Real==Cf)));
    return Real;
}

void ValidarCadena(char Cadena[], int Largo){
    char CadenaTemp[100];
    do{
        printf("");
        fflush(stdin);
        fgets(CadenaTemp,100,stdin);

        if(CadenaTemp[strlen(CadenaTemp)-1] == '\n'){
            CadenaTemp[strlen(CadenaTemp)-1] = '\0';
        }
    }while(!(strlen(CadenaTemp)<Largo));
    strcpy(Cadena,Cadena);
}
