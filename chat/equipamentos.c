#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXEQUIPAMENTOS 4
#define MAXSENSORES 4
#define BUFSIZE 1024

//Matriz da industria
int Equipamento[MAXEQUIPAMENTOS][MAXSENSORES];
//sensorList[i]=(float)rand()/(float)(RAND_MAX/50);

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

int VerifySensores(int *ids){
    int count = 0;
    for(int i = 0; i < MAXEQUIPAMENTOS; i++){
        if(ids[i] != 0){
            count++;
        }
    }
    return count;
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

float readSensor(int equipamento, int *sensor){
    --equipamento;
    int i=0,j=0,k=0,l=0;
    int NonExistent[MAXSENSORES]={0,0,0,0};
    int flag = 0;
    float ValorSensores[MAXSENSORES]={0,0,0,0};
    char *response = malloc(sizeof(char) * BUFSIZE);
    char *failedSensors = malloc(sizeof(char) * BUFSIZE);

    for(i = 0; i < MAXSENSORES; i++){
        for(j=0;j< MAXSENSORES;j++){
            if(Equipamento[equipamento][j] == sensor[i] && sensor[i]!=0){
                ValorSensores[k] = (float)rand()/(float)(RAND_MAX/50);
                k++;
            }
        }
        if(k == 0){
            flag = 1;
            NonExistent[l] = sensor[i];
            l++;
        }
        k=0;
    }

    //imprime valores dos sensores
    for(i = 0; i < MAXSENSORES; i++){
        if(ValorSensores[i] != 0){
            printf("sensor %d: %.2f\n", i+1, ValorSensores[i]);
        }
    }

    //imprime sensores nao existentes
    for(i = 0; i < MAXSENSORES; i++){
        if(NonExistent[i] != 0){
            printf("sensor 0%d does not exist \n", NonExistent[i]);
        }
    }

    if(flag==1 && NonExistent[0]!=0){
        //chamar funçao para imprimir os erros
        failedSensors = ConcatInteger(NonExistent);
        sprintf(response, "sensor %s does not exist in 0%d", failedSensors, equipamento+1);
        printf("%s\n", response);
    }
    else{
        response = ConcatFloat(ValorSensores);
        printf("sensor %s in 0%d = %s\n", ConcatInteger(sensor), equipamento+1, response);
    }


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
    float *ListValues[MAXSENSORES];
    char *response = malloc(sizeof(char)*BUFSIZE);
    token = strtok(Input, " ");
    token = strtok(NULL, " "); // para pular o comando
    while(strcmp(token,"in")!=0){
        token = strtok(NULL, " ");
        ids[i] = atoi(token);
        i++;
    }
    //extraçao do nr de equipamento da sttring de entrada
    //imprime ids

    token = strtok(NULL, " ");
    int NrEquipamento = atoi(token);
    //verifica se o equipamento existe
    if(NrEquipamento>MAXEQUIPAMENTOS){
        printf("Equipamento não existe\n");
    }
    readSensor(NrEquipamento,ids);
    
    // response = ConcatFloat(ListValues);
    // printf("%s\n", response);
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


const char *handleBuf(char *Input){
    int a;
    int mode;

    
    //Cria o vetor para armazenar a leitura do cliente
    char buf[BUFSIZE];
    char buf2[BUFSIZE];

   
    memset(buf, 0, BUFSIZE);
    memset(buf2, 0, BUFSIZE);
    strcpy(buf, Input);
    strcpy(buf2,buf);
    mode = handleMode(buf);
 
    // switch (mode) {
    //     case 1:
    //         handleAdd(buf2);
    //         break;
    //     case 2:
    //         handleRemove(buf2);
    //         break;
    //     case 3:
    //         handleRead(buf2);
    //         break;
    //     case 4:
    //         handleList(buf2);
    //         break;
    //     default:
    //         printf("Invalid command\n");
    //         break;
    // }

memset(buf, 0, BUFSIZE);
sprintf(buf,"Deu certo :%d",mode);
return buf;
}

