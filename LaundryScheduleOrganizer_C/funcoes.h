#ifndef FUNCOES_H
#define FUNCOES_H
#define MAX 50


typedef struct {
    int dia, mes, ano;
    int horas, minutos;
} datatype;

typedef struct noReserva {
    char nome[MAX];
    int id_pessoa, tipoServiço;
    datatype * data;
    struct noReserva * prox;
} noRes;

typedef struct {
    noRes * inicio;
    noRes * fim;
} tipoRes;

//data

int data_comp(datatype * left, datatype * right);

//estruturas

void criaFila(tipoRes * fila);

int vaziaFila(tipoRes * fila);

int insereFila(tipoRes * fila, noRes * no);

int valRes(noRes * no, tipoRes * fila);

void atualiza(tipoRes * reservas, tipoRes * preReservas);

int fazRes(tipoRes * reservas, tipoRes * prereservas, int modo);

void fazPreRes(tipoRes * reservas, tipoRes * prereservas, int modo);

void printRes(tipoRes * fila);

void freeRes(tipoRes * fila);

void procura(tipoRes * fila, datatype *data, noRes **ant, noRes **atual);

void ver_cliente(tipoRes  * reservas, tipoRes * prereservas, int id);

int elimina_no(tipoRes *fila, int n);

void cancela_res(tipoRes * reservas,tipoRes *prereservas, int n);

int realiza_servico(tipoRes *reservas, tipoRes *prereservas, int id);

//outras funcoes

int selectMode();

int stringToInt(char *str);

FILE * open_file(char * file);

int load(tipoRes * fila, FILE * file_ptr);

void menu();

int createID(tipoRes * reservas, tipoRes * prereservas);

void save(char * resFile, char * preresFile, tipoRes * filaRes, tipoRes * filaPreres);



#endif