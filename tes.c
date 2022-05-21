#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXEQUIPAMENTOS 4
#define MAXSENSORES 4
#define BUFSIZE 1024

//Matriz da industria
int Equipamento[MAXEQUIPAMENTOS][MAXSENSORES];

char *ConcatInteger(int *ids){
    //count the number of ids diferrent from 0
    int count = 0;
    for(int i = 0; i < MAXEQUIPAMENTOS; i++){
        if(ids[i] != 0){
            count++;
        }
    }

    //create a string with the ids
    char *str = malloc(sizeof(char) * BUFSIZE);
    
    switch(count){
        case 1:
            sprintf(str, "0%d", ids[0]);
            break;
        case 2:
            sprintf(str, "0%d 0%d", ids[0], ids[1]);
            break;
        case 3:
            sprintf(str, "0%d 0%d 0%d", ids[0], ids[1], ids[2]);
            break;
        case 4:
            sprintf(str, "0%d 0%d 0%d 0%d", ids[0], ids[1], ids[2], ids[3]);
            break;
    }
    return str;

}

char *ConcatFloat(float *ids){
    //count the number of ids diferrent from 0
    int count = 0;
    for(int i = 0; i < MAXEQUIPAMENTOS; i++){
        if(ids[i] != 0){
            count++;
        }
    }

    //create a string with the ids
    char *str = malloc(sizeof(char) * BUFSIZE);
    
    switch(count){
        case 1:
            sprintf(str, "%.2f", ids[0]);
            break;
        case 2:
            sprintf(str, "%.2f %.2f", ids[0], ids[1]);
            break;
        case 3:
            sprintf(str, "%.2f %.2f %.2f", ids[0], ids[1], ids[2]);
            break;
        case 4:
            sprintf(str, "%.2f %.2f %.2f %.2f", ids[0], ids[1], ids[2], ids[3]);
            break;
    }
    return str;

}


int removeSensor(int equipamento, int sensor){
    --equipamento;
    int index = sensor -1;
    if(Equipamento[equipamento][index] != 0){
        Equipamento[equipamento][index] = 0;
        printf("sensor %d removed\n", sensor);
        return 1;
    }
    else if (sensor!=0){
        printf("sensor 0%d does not exist in 0%d\n", sensor, equipamento+1);
    }
    return 0;
}

float *readSensor(int equipamento, int *sensor){
    printf("dasdsadasdas\n");
    float sensorList[MAXSENSORES] = {0,0,0,0};
    int i=0;
    for(i=0; i<MAXSENSORES; i++){
     if(Equipamento[equipamento][sensor[i]] != 0){
        sensorList[i]=(float)rand()/(float)(RAND_MAX/50);
    }
    else if(sensor[i]!=0){
        printf("sensor 0%d does not exist in 0%d\n", sensor[i], equipamento);
        return 0;
    }
        }
   // return sensorList;
}

int readEquipamento(int i){
    --i;
    int ListaSensores[MAXSENSORES] = {0,0,0,0};
    char *response = malloc(sizeof(char)*BUFSIZE);
    for(int j = 0; j < MAXSENSORES; j++){
        if(Equipamento[i][j] != 0){
            ListaSensores[j] = Equipamento[i][j];
        }
    }

    if(ListaSensores[0]==0){
        printf("No sensors in 0%d", i+1);
    }

    response = ConcatInteger(ListaSensores);
    printf("%s\n", response);
    return 1;
}

void print_equipamentos(){
    int i,j;
    for(i=0;i<MAXEQUIPAMENTOS;i++){
        for(j=0;j<MAXSENSORES;j++){
            printf("%d ", Equipamento[i][j]);
        }
        printf("\n");
    }
}

int addSensor(int equipamento, int sensor){
    int addedSens[4]={0,0,0,0};
    --equipamento;
    int index = sensor -1;
    if(Equipamento[equipamento][index] == 0 && sensor!=0){
        Equipamento[equipamento][index] = sensor;
        return sensor;
    }
    else if(sensor != 0){
        printf("sensor 0%d already exists in 0%d\n", sensor, equipamento+1);
        return 0;
    }

}

int handleMode(char *Input){
    char *token;
    char *command;
    token = strtok(Input, " ");
    
    if(strcmp(token,"add") == 0){
        return 1;
    }
    else if(strcmp(token,"remove") == 0){
        return 2;
    }
    else if(strcmp(token,"read") == 0){
        return 3;
    }
    else if(strcmp(token,"list") == 0){
        return 4;
    }
    else{
        return -1;
    }

    

}

void handleAdd(char *Input){
    char *token;
    int ids[4] = {0,0,0,0};
    int addedSensors[4]={0,0,0,0};
    char *response = malloc(sizeof(char)*BUFSIZE);

    int i=0;
    token = strtok(Input, " ");
    token = strtok(NULL, " "); // para pular o comando
    while(strcmp(token,"in")!=0){
        token = strtok(NULL, " ");
        ids[i] = atoi(token);
        i++;
    }
    //verifica se temos menos de 4 sensores
    int size = sizeof ids / sizeof ids[0];
    if(size>4){
        printf("Não é possivel adicionar mais de 4 sensores\n");
    }

    //extraçao do nr de equipamento da sttring de entrada
    token = strtok(NULL, " ");
    int NrEquipamento = atoi(token);
    //verifica se o equipamento existe
    if(NrEquipamento>MAXEQUIPAMENTOS){
        printf("Equipamento não existe\n");
    }
    else{
        for(int j=0;j<size;j++){
            addedSensors[j]=addSensor(NrEquipamento,ids[j]);
        }
    }

    response = ConcatInteger(addedSensors);
    if(addedSensors[0]!=0){
        printf("sensor %s added\n", response);	
    }

}

void handleRemove(char *Input){
    char *token;
    int ids[4] = {0,0,0,0};
    int i=0;
    token = strtok(Input, " ");
    token = strtok(NULL, " "); // para pular o comando
    while(strcmp(token,"in")!=0){
        token = strtok(NULL, " ");
        ids[i] = atoi(token);
        i++;
    }
    //extraçao do nr de equipamento da sttring de entrada
    token = strtok(NULL, " ");
    int NrEquipamento = atoi(token);
    //verifica se o equipamento existe
    if(NrEquipamento>MAXEQUIPAMENTOS){
        printf("sensor %d does not exist in %d\n",ids[0],NrEquipamento);
    }
    else{
        for(i=0;i<4;i++){
            removeSensor(NrEquipamento,ids[i]);
        }
    }
}

void handleRead(char *Input){
    char *token;
    int ids[4] = {0,0,0,0};
    int i=0;
    float *ListValues = malloc(sizeof(int)*4);
    char *response = malloc(sizeof(char)*BUFSIZE);
    token = strtok(Input, " ");
    token = strtok(NULL, " "); // para pular o comando
    while(strcmp(token,"in")!=0){
        token = strtok(NULL, " ");
        ids[i] = atoi(token);
        i++;
    }
    //extraçao do nr de equipamento da sttring de entrada
    token = strtok(NULL, " ");
    int NrEquipamento = atoi(token);
    //verifica se o equipamento existe
    if(NrEquipamento>MAXEQUIPAMENTOS){
        printf("sensor %d does not exist in %d\n",ids[0],NrEquipamento);
    }
    else{
        ListValues = readSensor(NrEquipamento,ids);
    }
    response = ConcatFloat(ListValues);
    printf("%s\n", response);
    //print response
   
}

void handleList(char *Input){
    char *token;
    int i =0;
    token = strtok(Input, " ");
    token = strtok(NULL, " "); // para pular o comando

    //extraçao do nr de equipamento da sttring de entrada
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    int NrEquipamento = atoi(token);

    if(NrEquipamento>MAXEQUIPAMENTOS){
        printf("Equipamento não existe\n");
    }
    else{
        readEquipamento(NrEquipamento);
    }

}


int main(int argc, char **argv){
    int a;
    int mode;
    int contador = 0;

    //esvazia a matriz
    memset(Equipamento,0,sizeof(Equipamento));

    
    //Cria o vetor para armazenar a leitura do cliente
    char buf[BUFSIZE];
    char buf2[BUFSIZE];

    while(contador<3){
    memset(buf, 0, BUFSIZE);
    fgets(buf, BUFSIZE, stdin);
    strcpy(buf2,buf);
    mode = handleMode(buf);
 
    switch (mode) {
        case 1:
            handleAdd(buf2);
            break;
        case 2:
            handleRemove(buf2);
            break;
        case 3:
            handleRead(buf2);
            break;
        case 4:
            handleList(buf2);
            break;
        default:
            printf("Invalid command\n");
            break;
    }
  contador++;
  print_equipamentos();
}

return 1;
}

