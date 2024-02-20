#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

#define MAX_LINE 100
#define MAX_DATA 20
#define MAX 50


int data_comp(datatype * left, datatype * right) {
    if (left->ano != right->ano) return (left->ano > right->ano) * 2 - 1;
    else if (left->mes != right->mes) return (left->mes > right->mes) * 2 - 1;
    else if (left->dia != right->dia) return (left->dia > right->dia) * 2 - 1;
    else if (left->horas != right->horas) return (left->horas > right->horas) * 2 - 1;
    else if (left->minutos != right->minutos) return (left->minutos > right->minutos) * 2 - 1;
    return 0;
}

void criaFila(tipoRes * fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int vaziaFila(tipoRes * fila) {
    return fila->inicio == NULL;
}

int insereFila(tipoRes * fila, noRes * no) {
    noRes * ptr;
    ptr = (noRes *) malloc(sizeof(noRes));
    if (ptr != NULL) { //caso não haja erro
        //cópia dos valores passados pelo segundo parâmetro
        strcpy(ptr->nome, no->nome);
        ptr->id_pessoa = no->id_pessoa;
        ptr->tipoServiço = no->tipoServiço;
        ptr->data = (datatype *) malloc(sizeof(datatype));
        ptr->data->ano = no->data->ano;
        ptr->data->mes = no->data->mes;
        ptr->data->dia = no->data->dia;
        ptr->data->horas = no->data->horas;
        ptr->data->minutos = no->data->minutos;
        ptr->prox = NULL;

        //caso a fla esteja vazia ou a data seja mais antiga que a do início -> colocar no início
        if (vaziaFila(fila) || data_comp(ptr->data, fila->inicio->data) < 0) {
            ptr->prox = fila->inicio;
            fila->inicio = ptr;
        }
        //caso contrário, deve ser colocada antes da próxima data ser maior
        else {
            noRes * atual = fila->inicio;
            //para descobrir quando a próxima data é maior, percorrer a fila e atualizar o ponteiro atual enquanto este é menor
            while (atual->prox != NULL && data_comp(ptr->data, atual->prox->data) > 0) {
                atual = atual->prox;
            }
            ptr->prox = atual->prox;
            atual->prox = ptr;
        }
        return 0;
    }
    else return 1;
}

int valRes(noRes * no, tipoRes * fila) {
    noRes * ptr = fila->inicio;
    while (ptr != NULL) { //percorrer a fila
        if (!data_comp(no->data, ptr->data)) return 0; //caso haja uma marcação na mesma hora, data inválida
        ptr = ptr->prox;
    }
    datatype dataAux; //data auxiliar com +30 minutos para verificar se existe uma marcação nessa hora
    dataAux.ano = no->data->ano; dataAux.mes = no->data->mes; dataAux.dia = no->data->dia;
    //operações para somar 30 minutos
    if (no->data->minutos == 30) {
        dataAux.minutos = 0; dataAux.horas = no->data->horas + 1;
    }
    else {dataAux.minutos = 30; dataAux.horas = no->data->horas;}
    if (no->tipoServiço == 2) { //caso seja o serviço de 1 hora temos de ver se temos 1 hora livre
        if (no->data->horas == 17 && no->data->minutos == 30) return 0; //17h30, data inválida
        //percorrer fila
        ptr = fila->inicio;
        while (ptr != NULL) {
            if (!data_comp(&dataAux, ptr->data)) return 0; //caso haja uma marcação 30 minutos depois -> data inválida
            ptr = ptr->prox;
        }
    }
    //é necessário verificar ainda se existe um serviço de 1 hora, 30 minutos antes do serviço a ser marcado
    dataAux.horas -= 1; //como já se somou 30 minutos, agora basta subtrair 1 hora
    ptr = fila->inicio;
    while (ptr != NULL) {
        //caso haja uma marcação de 1 hora, 30 minutos antes -> data inválida
        if ((!data_comp(&dataAux, ptr->data)) && ptr->tipoServiço == 2) return 0;
        ptr = ptr->prox;
    }
    return 1;
}

void atualiza(tipoRes * reservas, tipoRes * preReservas) {
    noRes *ptr = preReservas->inicio;
	int cont = 1; //"índice para a função elimina_no"
	while(ptr != NULL){ //percorrer prereservas
		if (valRes(ptr,reservas)){ //caso a pré-reserva seja valida para entrar
			insereFila(reservas,ptr);
			elimina_no(preReservas,cont);
			cont--; //como se retirou um elemento, o índice tem de se manter
		}
		ptr = ptr->prox;
		cont++;
	}	
}

int fazRes(tipoRes * reservas, tipoRes * prereservas, int modo) {
    //recolha de dados
    noRes noAux; //nó auxiliar para ser introduzido.

    int check; //var auxiliar para possíveis erros
    //tipo de serviço
    printf("Selecione o tipo de serviço.\n[1]: Lavagem\n[2]: Manutenção\n\n-> ");
    while (scanf("%d", &noAux.tipoServiço) != 1 || (noAux.tipoServiço != 1 && noAux.tipoServiço != 2)) {
        if (modo) system("clear");
        printf("Valores introduzidos inválidos.\n");
        while ((check = getchar()) != '\n' && check != EOF);
        printf("\nSelecione o tipo de serviço.\n[1]: Lavagem\n[2]: Manutenção\n\n-> ");
    }
    //data
    noAux.data = (datatype *) malloc(sizeof(datatype));
    check = 0;
    while (!check) {
        printf("\nHoras (d/m/a - hh:mm)\nObs: Serviços são marcados de 30 em 30 minutos das 8h às 18h.\n\n-> ");
        while (scanf("%d/%d/%d - %d:%d", &(noAux.data->dia), &(noAux.data->mes), &(noAux.data->ano), &(noAux.data->horas), &(noAux.data->minutos)) != 5
        || (noAux.data->minutos != 30 && noAux.data->minutos != 0) || noAux.data->horas < 8 || noAux.data->horas >= 18
        || noAux.data->dia > 31 || noAux.data->dia < 1 || noAux.data->mes > 12 || noAux.data->mes < 1) {
            if (modo) system("clear");
            printf("\nValores introduzidos inválidos.\n");
            if (noAux.data->minutos != 30 && noAux.data->minutos != 0) printf("Erro: As horas têm de ser do género 'hh:00' ou 'hh':30.\n ");
            if (noAux.data->horas < 8 || noAux.data->horas > 18) printf("Erro: Marcações apenas das 8h às 18h.\n");
            if (noAux.data->dia > 31 || noAux.data->dia < 1 || noAux.data->mes > 12 || noAux.data->mes < 1) printf("Erro: Data Inválida.\n");
            while ((check = getchar()) != '\n' && check != EOF);
            printf("\nHoras (d/m/a - hh:mm)\nObs: Serviços são marcados de 30 em 30 minutos das 8h às 18h.\n\n-> ");
        }
        check = valRes(&noAux, reservas);
        if (!check) {
            if (modo) system("clear");
            printf("Já existe marcação nessa hora. Deseja tentar com outra hora ou fazer uma pré-reserva?\n");
            printf("[1]: Outra hora.\n[2]: Fazer pré-reserva.\n\n-> ");
            int op = 0;
            while (scanf("%d", &op) != 1 || (op != 1 && op != 2)) {
                if (modo) system("clear");
                printf("Valores introduzidos inválidos.\n");
                while ((check = getchar()) != '\n' && check != EOF);
                printf("[1]: Outra hora.\n[2]: Fazer pré-reserva.\n\n-> ");
            }
            check = 0;
            if (op == 2) {
                free(noAux.data);
                return 1;
            }
        }
    }  
    //nome cliente
    printf("\nNome do cliente: ");
    getchar(); //recolher o \n da resposta anterior para não entrar no próximo fgets
    fgets(noAux.nome, MAX, stdin);
    for (int i = 0; noAux.nome[i] != '\0'; i++) {
        if (noAux.nome[i] == '\n') {
            noAux.nome[i] = '\0';
            break;
        }
    }
    //id cliente
    int id;
    //verificar se o cliente já existe nos registos
    int flag = 0;
    for (noRes * ptr = reservas->inicio; ptr != NULL; ptr = ptr->prox) {
        if (!strcmp(ptr->nome, noAux.nome)) { //caso o nome seja encontrado
            flag = 1;
            id = ptr->id_pessoa;
            break;
        }
    }
    if (!flag) { //se ainda não foi encontrado, procurar na outra lista
        for (noRes * ptr = prereservas->inicio; ptr != NULL; ptr = ptr->prox) {
            if (!strcmp(ptr->nome, noAux.nome)) { //caso o nome seja encontrado
                flag = 1;
                id = ptr->id_pessoa;
                break;
            }
        }
    }
    if (!flag) id = createID(reservas, prereservas); //caso não seja encontrado, gerar um id novo
    noAux.id_pessoa = id;

    insereFila(reservas, &noAux);

    free(noAux.data);

    return 0;
}

void fazPreRes(tipoRes * reservas, tipoRes * prereservas, int modo) {
    //recolha de dados
    noRes noAux; //nó auxiliar para ser introduzido.

    int check; //var auxiliar para possíveis erros
    //tipo de serviço
    printf("Selecione o tipo de serviço.\n[1]: Lavagem\n[2]: Manutenção\n\n-> ");
    while (scanf("%d", &noAux.tipoServiço) != 1 || (noAux.tipoServiço != 1 && noAux.tipoServiço != 2)) {
        if (modo) system("clear");
        printf("Valores introduzidos inválidos.\n");
        while ((check = getchar()) != '\n' && check != EOF);
        printf("\nSelecione o tipo de serviço.\n[1]: Lavagem\n[2]: Manutenção\n\n-> ");
    }
    //data
    noAux.data = (datatype *) malloc(sizeof(datatype));
    check = 0;
    
    printf("\nHoras (d/m/a - hh:mm)\nObs: Serviços são marcados de 30 em 30 minutos das 8h às 18h.\n-> ");
    while (scanf("%d/%d/%d - %d:%d", &(noAux.data->dia), &(noAux.data->mes), &(noAux.data->ano), &(noAux.data->horas), &(noAux.data->minutos)) != 5
    || (noAux.data->minutos != 30 && noAux.data->minutos != 0) || noAux.data->horas < 8 || noAux.data->horas >= 18
    || noAux.data->dia > 31 || noAux.data->dia < 1 || noAux.data->mes > 12 || noAux.data->mes < 1) {
        if (modo) system("clear");
        printf("\nValores introduzidos inválidos.\n");
        if (noAux.data->minutos != 30 && noAux.data->minutos != 0) printf("Erro: As horas têm de ser do género 'hh:00' ou 'hh':30.\n ");
        if (noAux.data->horas < 8 || noAux.data->horas > 18) printf("Erro: Marcações apenas das 8h às 18h.\n");
        if (noAux.data->dia > 31 || noAux.data->dia < 1 || noAux.data->mes > 12 || noAux.data->mes < 1) printf("Erro: Data Inválida.\n");
        while ((check = getchar()) != '\n' && check != EOF);
        printf("\nHoras (d/m/a - hh:mm)\nObs: Serviços são marcados de 30 em 30 minutos das 8h às 18h.\n-> ");
    }
    //nome cliente
    printf("\nNome do cliente: ");
    getchar(); //recolher o \n da resposta anterior para não entrar no próximo fgets
    fgets(noAux.nome, MAX, stdin);
    for (int i = 0; noAux.nome[i] != '\0'; i++) {
        if (noAux.nome[i] == '\n') {
            noAux.nome[i] = '\0';
            break;
        }
    }
    //id cliente
    int id;
    //verificar se o cliente já existe nos registos
    int flag = 0;
    for (noRes * ptr = reservas->inicio; ptr != NULL; ptr = ptr->prox) {
        if (!strcmp(ptr->nome, noAux.nome)) { //caso o nome seja encontrado
            flag = 1;
            id = ptr->id_pessoa;
            break;
        }
    }
    if (!flag) { //se ainda não foi encontrado, procurar na outra lista
        for (noRes * ptr = prereservas->inicio; ptr != NULL; ptr = ptr->prox) {
            if (!strcmp(ptr->nome, noAux.nome)) { //caso o nome seja encontrado
                flag = 1;
                id = ptr->id_pessoa;
                break;
            }
        }
    }
    if (!flag) id = createID(reservas, prereservas); //caso não seja encontrado, gerar um id novo
    noAux.id_pessoa = id;
    insereFila(prereservas, &noAux);

    free(noAux.data);
}

void printRes(tipoRes * fila) {
    noRes * ptr;
	int i = 1;
    for (ptr = fila->inicio; ptr != NULL; ptr = ptr->prox) {
        printf("[%d]: Cliente: %s  ID: %d || ",i, ptr->nome,ptr->id_pessoa);
        printf("Data: %02d:%02d - %d/%d/%d\n", ptr->data->horas, ptr->data->minutos, ptr->data->dia, ptr->data->mes, ptr->data->ano);
		
        printf("-------------------------------------------------------------------\n");
		i++;
    }
}

void freeRes(tipoRes * fila) {
    noRes * ptr = fila->inicio;
    while (ptr != NULL) {
        noRes * temp = ptr;
        ptr = ptr->prox;
        free(temp->data);
        free(temp);
    }
    fila->inicio = NULL;
    fila->fim = NULL;
}

void procura(tipoRes *fila, datatype *data, noRes **ant, noRes **atual) {
    *ant = NULL;
    *atual = fila->inicio;

    while ((*atual) != NULL) { //percorrer a fila
        if (!data_comp((*atual)->data, data)) { //caso encontre data igual
            return;
        }
        *ant = *atual; //atualiza os ponteiros para os nós seguintes
        *atual = (*atual)->prox;
    }
    //caso não encontre
    *ant = NULL;
    *atual = NULL;
}

void ver_cliente(tipoRes  * reservas, tipoRes  * prereservas, int id){
	noRes * res = reservas->inicio;
	noRes * preres = prereservas->inicio;
	printf("\nReservas: \n");
    int flag = 0; //flag para saber se foram encontradas reservas/pre-reservas
    while (res != NULL) { //percorrer reservas
        if (res->id_pessoa == id){ //caso a reserva seja do id desejado -> printar
			printf("Data: %02d:%02d - %d/%d/%d\n", res->data->horas, res->data->minutos, res->data->dia, res->data->mes, res->data->ano);  
			printf("-------------------------------------------------------------------\n");
            flag = 1;
		}
		res = res->prox;
	}
    if (!flag) printf("Não há reservas para este cliente.\n");

    //processo análogo para as pré-reservas....
	printf("\nPre Reservas: \n");
    flag = 0;
    while (preres != NULL) { 
        if (preres->id_pessoa == id){
			printf("Data: %02d:%02d - %d/%d/%d\n", preres->data->horas, preres->data->minutos, preres->data->dia, preres->data->mes, preres->data->ano);  
			printf("-------------------------------------------------------\n");
            flag = 1;
		}	
		preres = preres->prox;
    }
    if (!flag) printf("Não há pre reservas para este cliente.\n");
}

int elimina_no(tipoRes *fila, int n) {
    noRes *ant = NULL;
    noRes *atual = NULL;
	noRes *aux = fila->inicio;
    //procurar o nó de indice "n"
	for (int i = 0; i < n - 1 && aux != NULL; i++){
		aux = aux->prox;
	}
	if (aux == NULL) return 1; //não foi encontrado

    procura(fila, aux->data, &ant, &atual);
    if (ant == NULL) { //está no início
        fila->inicio = atual->prox; //atualizar inicio da fila
    } else {
        ant->prox = atual->prox; //o anterior agora aponta para o próximo do atual
    }
    free(atual);

	return 0;
}

void cancela_res(tipoRes *reservas, tipoRes *prereservas, int n) { 
	elimina_no(reservas,n);
	atualiza(reservas, prereservas);
}


int realiza_servico(tipoRes *reservas, tipoRes *prereservas, int n){
	noRes *aux = reservas->inicio;
	for (int i = 0; i < n - 1 && aux != NULL; i++){ //procurar reserva de índice "n"
		aux = aux->prox;
	}
	if (aux == NULL) return 1; //não foi encontrado
	
	datatype *data = aux->data;
	
    //eliminar reservas que estejam no passado (semelhante à função atualiza)
	aux = prereservas->inicio;
	int cont = 1;
	while(aux != NULL){ //percorrer fila
		if (data_comp(aux->data,data) < 1){ //data está no passado -> eliminar
			elimina_no(prereservas,cont);
			cont--;
		}
		aux = aux->prox;
		cont++;
	}
	
    //processo análogo para as reservas
	aux = reservas->inicio;
	cont = 1;
	while(aux != NULL){
		if (data_comp(aux->data,data) < 1){
			cancela_res(reservas,prereservas, cont);
			cont--;
		}
		aux = aux->prox;
		cont++;
	}
	return 0;	
}

int selectMode() {
    char input[10];

    printf("Prima ENTER para iniciar o programa ou escreva \"dev\" para começar em modo desenvolvedor.\n");
    printf("(O modo desenvolvedor faz com que a interface deixe de ser estática, facilitando o uso de ferramentas como o Valgrind.)\n\n");
    fgets(input, sizeof(input), stdin);
    //remover os "\n" da string
    input[strcspn(input, "\n")] = '\0'; //coloca "\0" na posição do primeiro "\n"

    if (strcmp(input, "") == 0) { //-> ENTER (normal)
        system("clear");
        printf("Programa iniciado.\n");
        return 1;
    }
    if (strcmp(input, "dev") == 0) { //-> dev
        printf("\nPrograma iniciado em modo desenvolvedor.\n");
        return 0;
    }
    //-> input inválido
    printf("Input inválido.\n");
    return -1;
}

int stringToInt(char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

FILE * open_file(char * file) {
    FILE * ptr = fopen(file, "r+");
    if (ptr == NULL) { //Caso o ficheiro não exista
        ptr = fopen(file,"w"); //cria o ficheiro
        fclose(ptr);
        ptr = fopen(file, "r+"); //e abre-o
    }
    return ptr;
}

int load(tipoRes * fila, FILE * file_ptr) {
    char linha[MAX_LINE] = {"\0"};
    while (fgets(linha, MAX_LINE, file_ptr)) { // percorrer cada linha
        //extração da informação de cada linha
        char * aux = strtok(linha, "#"); //aux -> nome
        char nome[MAX_LINE] = {"\0"};
        strcpy(nome, aux);
        
        aux = strtok(NULL, "#"); //aux -> id pessoal
        int idP = stringToInt(aux);

        aux = strtok(NULL, "#"); //aux -> tipo de serviço
        int tipoServ = stringToInt(aux);

        aux = strtok(NULL, "#"); //aux -> data
        
        char * auxData= strtok(aux, "/"); //auxData -> ano
        int ano = stringToInt(auxData);

        auxData = strtok(NULL, "/"); //auxData -> mes
        int mes = stringToInt(auxData);

        auxData = strtok(NULL, "/"); //auxData -> dia
        int dia = stringToInt(auxData);

        auxData = strtok(NULL, "/"); //auxData -> hora (string)
        char * auxHora = strtok(auxData, ":"); //auxHora -> horas
        int h = stringToInt(auxHora);

        auxHora = strtok(NULL, "\n\r \0"); //auxHora -> minutos

        int min = stringToInt(auxHora);

        //armazenar a informação numa struct aux
        noRes noAux;
        strcpy(noAux.nome, nome); noAux.id_pessoa = idP; noAux.tipoServiço = tipoServ;
        datatype dataAux;
        dataAux.ano = ano; dataAux.mes = mes; dataAux.dia = dia; dataAux.horas = h; dataAux.minutos = min;
        noAux.data = &dataAux;
        //introduzir a struct auxiliar na fila das reservas
        int erro = insereFila(fila, &noAux);
        if (erro) return 1;
    }
    return 0;
}

void menu() {
    printf("\nEscolha a operação a realizar:\n\n");
	printf("0: Realizar um serviço.\n");
    printf("1: Reservar um serviço.\n");
    printf("2: Pré-reservar serviço.\n");
    printf("3: Cancelar uma reserva.\n");
    printf("4: Cancelar uma pré-reserva.\n");
    printf("5: Ver todas as reservas.\n");
    printf("6: Ver todas as pré-reservas.\n");
    printf("7: Ver as reservas e pre-reservas de um cliente.\n");
    printf("8: Sair da aplicação.\n\n");
    printf("-> ");
}

int createID(tipoRes * reservas, tipoRes * prereservas) {
    int id = 1, flag = 0;
    while (1) {
        flag = 0; //flag para saber se encontrou um ID igual
        for (noRes * ptrRes = reservas->inicio; ptrRes != NULL; ptrRes = ptrRes->prox) { //percorrer reservas
            if (ptrRes->id_pessoa == id) { //encontrou um id igual
                flag = 1;
                break;
            }
        }
        if (flag) { //caso tenha encontrado id igual
            id++; //próximo id
            continue; //começar nova iteração do while
        }
        for (noRes * ptrPreRes = prereservas->inicio; ptrPreRes != NULL; ptrPreRes = ptrPreRes->prox) { //percorrer prereservas
            if (ptrPreRes->id_pessoa == id) { //encontrou um id igual
                flag = 1;
                break;
            }
        }
        if (flag) { //caso tenha encontrado id igual
            id++; //próximo id
            continue; //começar nova iteração do while
        }
        //se chegou aqui, não foi encontrado id igual -> id é único, parar a procura.
        break;
    }
    return id;
}

void save(char * resFile, char * preresFile, tipoRes * filaRes, tipoRes * filaPreres) {
    FILE * resptr = fopen(resFile, "w");
    FILE * preresptr = fopen(preresFile, "w");
    if (resptr == NULL || preresptr == NULL) {
        printf("Falha ao abrir ficheiros.");
        return;
    }
    //guardar reservas
    noRes * ptr = filaRes->inicio;
    while (ptr != NULL) {
        fprintf(resptr, "%s#", ptr->nome);
        fprintf(resptr, "%d#%d#", ptr->id_pessoa, ptr->tipoServiço);
        fprintf(resptr, "%d/%d/%d/", ptr->data->ano, ptr->data->mes, ptr->data->dia);   
        fprintf(resptr, "%d:%d\n", ptr->data->horas, ptr->data->minutos);
        ptr = ptr->prox;
    }
    //guardar prereservas
    ptr = filaPreres->inicio;
    while (ptr != NULL) {
        fprintf(preresptr, "%s#", ptr->nome);
        fprintf(preresptr, "%d#%d#", ptr->id_pessoa, ptr->tipoServiço);
        fprintf(preresptr, "%d/%d/%d/", ptr->data->ano, ptr->data->mes, ptr->data->dia);   
        fprintf(preresptr, "%d:%d\n", ptr->data->horas, ptr->data->minutos);
        ptr = ptr->prox;
    }
    //fechar ficheiros
    fclose(resptr);
    fclose(preresptr);
}



