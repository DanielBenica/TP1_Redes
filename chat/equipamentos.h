#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXEQUIPAMENTOS 4
#define MAXSENSORES 4
#define BUFSIZE 1024

char *ConcatInteger(int *ids);

char *ConcatFloat(float *ids);

int VerifySensores(int *ids);

int removeSensor(int equipamento, int sensor);

float readSensor(int equipamento, int *sensor);

int readEquipamento(int i);

void print_equipamentos();

int addSensor(int equipamento, int sensor);

int handleMode(char *Input);

void handleAdd(char *Input);

void handleRemove(char *Input);

void handleRead(char *Input);

void handleList(char *Input);

const char *handleBuf(char *Input);