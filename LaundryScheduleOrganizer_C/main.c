#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main() {
    //seleção do modo (normal ou desenvolvedor)
    int modo = - 1;
    while (modo == -1) modo = selectMode();

    tipoRes reservas, preReservas;
    criaFila(&reservas);
    criaFila(&preReservas);

    //abertura e carregamento dos .txt nas filas
    FILE * fileRes = open_file("reservas.txt");
    FILE * filePreRes = open_file("prereservas.txt");
    if (load(&reservas, fileRes) || load(&preReservas, filePreRes)) {//se a leitura falhar acaba o programa retornando 1
        printf("Falha ao carregar os ficheiros txt.\nPrograma encerrado.\n");
        return 1;
    }

    int option = -1;
    while (1) {
        atualiza(&reservas, &preReservas);
        if (option == -1 ) {
            menu();
			while (scanf("%d", &option) != 1){
				if (modo) system("clear");
				printf("Valor introduzido Invalido.\n");
				int aux;
				while((aux = getchar()) != '\n' && aux != EOF);
				menu();
			}
        }

        if (modo) system("clear");

        switch(option) {
			case 0:
				if (reservas.inicio == NULL) {
					printf("Não existem serviços.\n");
					printf("\nEnter para voltar ao menu.");
					getchar(); getchar();
					break;
				}
				printf("Reservas: \n\n");
				printRes(&reservas);
				printf("\n");
				int num;
				printf("Escolha o serviço a realizar: ");
				scanf("%d", &num);
				realiza_servico(&reservas,&preReservas,num);
				break;
            case 1:
                if (fazRes(&reservas, &preReservas, modo)) {
                    option = 2;
                    if (modo) system("clear");
                }
                if (option != 2) break;
            case 2:
                fazPreRes(&reservas, &preReservas, modo);
                break;
            case 3:
				printRes(&reservas);
				printf("Escolha qual reserva eliminar: ");
				int n = 0;
				scanf("%d",&n);
				cancela_res(&reservas,&preReservas,n); 
				printf("\nEnter para voltar ao menu.");
				getchar(); getchar();
                break;
            case 4:
				printRes(&preReservas);
				printf("Escolha qual pre reserva eliminar: ");
				int m = 0;
				scanf("%d",&m);
				elimina_no(&preReservas,m); 
				printf("\nEnter para voltar ao menu.");
				getchar(); getchar();
                break;
            case 5:
				if (reservas.inicio == NULL) {
					printf("Não existem reservas.\n");
					printf("\nEnter para voltar ao menu.");
					getchar(); getchar();
					break;
				}
                printRes(&reservas);
                printf("\nEnter para voltar ao menu.");
                getchar(); getchar();
                break;
            case 6:
				if (preReservas.inicio == NULL) {
					printf("Não existem pre reservas.\n");
					printf("\nEnter para voltar ao menu.");
					getchar(); getchar();
					break;
				}
                printRes(&preReservas);
                printf("\nEnter para voltar ao menu.");
                getchar(); getchar();
                break;
            case 7:
				int aux_id;
				printf("Indique o ID do Cliente: ");
				scanf("%d", &aux_id);		
				ver_cliente(&reservas, &preReservas, aux_id);
				printf("\nEnter para voltar ao menu.");
                getchar(); getchar();
                break;
            case 8:
                //fechar ficheiros abertos em modo leitura
                fclose(fileRes);
                fclose(filePreRes);
                //guardar os dados alterados durante o programa nos respetivos txt's
                save("reservas.txt", "prereservas.txt", &reservas, &preReservas);
                //libertar estruturas
                freeRes(&reservas);
                freeRes(&preReservas);
                printf("Programa terminado.\n");
                return 0;
            default:
                printf("Valor Inválido.\n\nENTER para continuar.");
                getchar(); getchar();
                break;
        }
        option = -1;
        if (modo) system("clear");
    }
}