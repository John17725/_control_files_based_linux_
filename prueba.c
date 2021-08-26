#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLeng 100
#define MAxWords 2000 //TAMANO DE ARREGLO PARA PALABRAS

char name_file[20];
char name_file_out[20];
char Word[MAxWords][MaxLeng];

typedef struct nodo{
  char *charter_name;
  struct nodo *sig;
}charter;

charter *listCharter(charter *list){
  list = NULL;
  return list;
}

FILE *OpenFile();
void CloseFile(FILE *ptr_Fich, char*name_file);
int Val_exist(int argc, char *argv[]);
int CreateWriteFile(char *name_file_create, int count);
charter *addCharter(charter *list, char *charter_name);
void ShowListCharter(charter *list);
void ShowWord(int count);
void BubbleSort(int count);
void ChargerList(charter *list, int count);
void ChargeDataDat(FILE *ptr_file_Dat, int count);

int main(int argc, char *argv[]) {
  system("sudo chmod +x welcome.sh bye.sh");
  system("./welcome.sh");
  int exist_file = 0, count;
  FILE *ptr_Fich = NULL;
  charter *list = listCharter(list);
  exist_file = Val_exist(argc, argv);
  if (exist_file == 0 ) {
    ptr_Fich = OpenFile();
    if (ptr_Fich != NULL) {
      printf("\tEl fichero [ %s ] Existe y se abrio exitosamente\n", name_file);
      printf("\tSE COMENZARA A LEER EL CONTENIDO DEL FICHERO POR FAVOR ESPERE\n");
      system("sleep 2s");
      count=0;
      while (feof(ptr_Fich) == 0) {
        fscanf(ptr_Fich, "%s", Word[count]);
        count++;
      }
      printf("\tCONTENIDO DESORDENADO\n");
      ShowWord(count);
      printf("\tORDENANDO PALABRAS POR FAVOR ESPERE\n");
      system("sleep  3s");
      BubbleSort(count);
      printf("\tPALABRAS ORDENADAS\n");
      ShowWord(count);
      printf("\tCARGADO CONTENIDO A LA LISTA ENLAZADA\n");
      system("sleep 3s");
      ChargerList(list, count);
      printf("\tCREANDO FICHERO %s PARA GUARDAR DATA\n",name_file_out);
      CreateWriteFile(name_file_out, count);
      CloseFile(ptr_Fich,name_file);
    }else{
      printf("\tEl fichero [ %s ] No existe\n", name_file);
    }
  }
  system("./bye.sh");
  return 0;
}

int Val_exist(int argc, char *argv[]){
  int error = 0;
  if (argc == 1) {
    printf("FALTAN ARGUMENTOS DE ENTRADA(name_file.txt) Y SALIDA(name_file.dat)\nPor favor ejecute nuevamente\n");
    error = 1;
  }else if(argc == 2){
    printf("FALTAN ARGUMENTOS DE SALIDA(name_file.dat)\n");
    error = 2;
  }else{
    printf("OK ARGUMENTOS VALIDOS\n");
    strcpy(name_file,argv[1]);
    strcpy(name_file_out,argv[2]);
    error = 0;
  }
  return error;
}


FILE *OpenFile(){
  printf("\tEl nombre del fichero a leer es [%s]\n",name_file );
  FILE *file = fopen(name_file,"r");
  return file;
}

void CloseFile(FILE *ptr_Fich, char *name_file){
  fclose(ptr_Fich);
  printf("\tEl fichero [ %s ] Se ha cerrado exitosamente\n",name_file);
}

charter *addCharter(charter *list, char *charter_name){
  charter *newCharter, *aux;
  newCharter=(charter*)malloc(sizeof(charter));
  newCharter->charter_name = charter_name;
  newCharter->sig = NULL;
  if (list == NULL) {
    list = newCharter;
  }else{
    aux = list;
    while (aux-> sig!= NULL) {
      aux = aux->sig;
    }
    aux->sig = newCharter;
  }
  return list;
}

void ShowListCharter(charter *list){
  while (list != NULL) {
    printf("[ %s ]\n",list->charter_name);
    list=list->sig;
  }
}

void BubbleSort(int count){
  char aux_word[MaxLeng];
	for(int i = 0; i < count-1; i++){
		for(int j = 0; j < count-1; j++){
			if(Word[j][0] > Word[j+1][0]){
        strcpy(aux_word, Word[j]);
        strcpy(Word[j],Word[j+1]);
        strcpy(Word[j+1],aux_word);
			}
    }
	}
}

void ShowWord(int count){
  for (int i = 0; i < count; i++) {
    printf("[ %s ]\n",Word[i]);
  }
}

void ChargerList(charter *list, int count){
  for (int i = 0; i < count; i++) {
    list = addCharter(list, Word[i]);
  }
  printf("\tCONTENIDO DE LISTA\n");
  ShowListCharter(list);
}

int CreateWriteFile(char *name_file_create, int count){
  int StatusCreate = 0;
  FILE *ptr_Fich_Create;
  ptr_Fich_Create = fopen(name_file_create,"w");
  if ( ptr_Fich_Create == NULL) {
    printf("\tEl archivo [ %s ] No pudo ser creado\n",name_file_create);
  }else{
    printf("\tEl archivo [ %s ] Fue creado exitosamente\n",name_file_create);
    StatusCreate = 1;
    printf("\tSe cargaran los datos en el fichero %s\n",name_file_create);
    ChargeDataDat(ptr_Fich_Create, count);
    CloseFile(ptr_Fich_Create,name_file_out);
  }
  return StatusCreate;
}

void ChargeDataDat(FILE *ptr_file_Dat, int count){
  for (int i = 0; i < count; i++) {
    fputs(Word[i],ptr_file_Dat);
    fputs("\n",ptr_file_Dat);
  }
}