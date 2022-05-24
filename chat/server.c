#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#define MAXEQUIPAMENTOS 4
#define MAXSENSORES 4
#define BUFSZ 1024
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

int VerifySensores(int *ids){
    int count = 0;
    for(int i = 0; i < MAXEQUIPAMENTOS; i++){
        if(ids[i] != 0){
            count++;
        }
    }
    return count;
}

char * removeSensor(int equipamento, int sensor){
    --equipamento;
    char *responseRemove = malloc(sizeof(char) * BUFSIZE);
    int i = 0;
    int flag = 0;
    for(i = 0; i < MAXSENSORES; i++){
        if(Equipamento[equipamento][i] != 0 && Equipamento[equipamento][i] == sensor){
            Equipamento[equipamento][i] = 0;
            sprintf(responseRemove,"sensor 0%d removed", sensor);
            flag = 1;
    }
    }
    if (flag == 0){
        sprintf(responseRemove,"sensor 0%d does not exist in 0%d", sensor, equipamento+1);
    }
    return responseRemove;
}

char * readSensor(int equipamento, int *sensor){
    --equipamento;
    int i=0,j=0,k=0,l=0,m=0;
    int NonExistent[MAXSENSORES]={0,0,0,0};
    int flag = 0;
    float ValorSensores[MAXSENSORES]={0,0,0,0};
    char *response = malloc(sizeof(char) * BUFSIZE);
    char *response2 = malloc(sizeof(char) * BUFSIZE);
    char *failedSensors = malloc(sizeof(char) * BUFSIZE);

    //imprime sensor

    for(i = 0; i < MAXSENSORES; i++){
        for(j=0;j< MAXSENSORES;j++){
            if(Equipamento[equipamento][j] == sensor[i] && sensor[i]!=0){
                ValorSensores[k] = (float)rand()/(float)(RAND_MAX/10);
                k++;
                m++;
            }
        }
        if(m == 0){
            flag = 1;
            NonExistent[l] = sensor[i];
            l++;
        }
        m=0;
    }

    //verificamos se houve erros ou não
    if(NonExistent[0]!=0){
        response = ConcatInteger(NonExistent);
        sprintf(response2, "sensor %s does not exist in 0%d", response, equipamento+1);
        return response2;
    }
    else if(ValorSensores[0]!=0){
        response = ConcatFloat(ValorSensores);
        return response;
    }

}


char * readEquipamento(int i){
    --i;
    int ListaSensores[MAXSENSORES] = {0,0,0,0};
    char *response = malloc(sizeof(char)*BUFSIZE);
    for(int j = 0; j < MAXSENSORES; j++){
        if(Equipamento[i][j] != 0){
            ListaSensores[j] = Equipamento[i][j];
        }
    }

    if(ListaSensores[0]==0){
        sprintf(response,"No sensors in 0%d", i+1);
    }
    else{
        response = ConcatInteger(ListaSensores);
    }
    
    return response;
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

char * addSensor(int equipamento, int *sensor){
    int addedSens[4]={0,0,0,0};
    int failedSens[4] = {0,0,0,0};
    char *response2 = malloc(sizeof(char) * BUFSIZE);
    char *response = malloc(sizeof(char) * BUFSIZE);
    --equipamento;
    int j = 0,k=0;
    for(int i=0;i<MAXSENSORES;i++){
        if(Equipamento[equipamento][i] == 0 && sensor!=0){
            Equipamento[equipamento][i] = sensor[i];
            addedSens[k] = sensor[i];
            k++;
        }
        else if(sensor[i]!=0 && Equipamento[equipamento][i]==sensor[i]){
            failedSens[j] = sensor[i];
            j++;
        }
    }

    //verificamos se houve erros ou não
    if(failedSens[0]!=0){
        response = ConcatInteger(failedSens);
        sprintf(response2, "sensor %s already exists in 0%d", response, equipamento+1);
        return response2;
    }
    else if(addedSens[0]!=0){
        response = ConcatInteger(addedSens);
        sprintf(response2, "sensor %s added", response);
        return response2;
    }



}

int handleMode(char *Input){
    char *token;
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

char * handleAdd(char *Input){
    char *token;
    int ids[4] = {0,0,0,0};
    char *addedSensors = malloc(sizeof(char) * BUFSIZE);
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
        response=addSensor(NrEquipamento,ids);
    }

    return response;

}

char * handleRemove(char *Input){
    char *token;
    int ids[4] = {0,0,0,0};
    int i=0;
    char * response = malloc(sizeof(char)*BUFSIZE);
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
        printf("Equipamento não existe\n");	
    }

    response = removeSensor(NrEquipamento,ids[0]);
    printf("[Log] ResponseHanlde: %s\n", response);
    return response;
}

char * handleRead(char *Input){
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
    response = readSensor(NrEquipamento,ids);
    return response;
    
    // response = ConcatFloat(ListValues);
    // printf("%s\n", response);
    //print response
   
}

char * handleList(char *Input){
    char *token;
    int i =0;
    char *response = malloc(sizeof(char)*BUFSIZE);
    token = strtok(Input, " ");
    token = strtok(NULL, " "); // para pular o comando

    //extraçao do nr de equipamento da sttring de entrada
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    int NrEquipamento = atoi(token);

    if(NrEquipamento>MAXEQUIPAMENTOS){
        printf("Equipamento não existe\n");
    }

    response = readEquipamento(NrEquipamento);
    return response;

}

char* handleBuf(char *Input){
    int a;
    int mode;

    
    //Cria o vetor para armazenar a leitura do cliente
    char buf[BUFSIZE];
    char buf2[BUFSIZE];
    char *response = malloc(sizeof(char)*BUFSIZE);
   
    memset(buf, 0, BUFSIZE);
    memset(buf2, 0, BUFSIZE);
    strcpy(buf, Input);
    strcpy(buf2,buf);
    mode = handleMode(buf);
    switch (mode) {
        case 1:
            strcpy(response,handleAdd(buf2));
            break;
        case 2:
            strcpy(response,handleRemove(buf2));
            break;
        case 3:
           strcpy(response,handleRead(buf2));
            break;
        case 4:
            strcpy(response,handleList(buf2));
            break;
        default:
            strcpy(response,"Invalid command");
            break;
    }

    
return response;
}


void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }
    //esvazia a matriz
    memset(Equipamento,0,sizeof(Equipamento));



    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        logexit("bind");
    }

    if (0 != listen(s, 10)) {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);
        printf("[log] connection from %s\n", caddrstr);

        
    while (1) {
        char buf[BUFSZ];
        char *response = malloc(sizeof(char)*BUFSIZE);
        memset(buf, 0, BUFSZ);
        //recebe a mensagem e guarda no buf para tratarmos
        size_t count = recv(csock, buf, BUFSZ - 1, 0);
        printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf);
        //strcpy(response,handleBuf(buf));
        printf("[log] buff: %s\n", buf);
        if(strcmp(buf,"kill\n")==0){
            fflush(stdout);
            printf("[Log] entrou no kill\n");
            break;
        }
        response = handleBuf(buf);
        if(strcmp(response,"Invalid command")==0){
            printf("[Log] Invalid command\n");
            break;
        }
        printf("[Log] response : %s\n",response);
        sprintf(buf, "remote endpoint: %.1000s\n", caddrstr);

        //enviamos a mensagem de retorno
        count = send(csock, response, strlen(response), 0);
        if (count != strlen(response)) {
            logexit("send");
        }
    }
        close(csock);

    exit(EXIT_SUCCESS);
}