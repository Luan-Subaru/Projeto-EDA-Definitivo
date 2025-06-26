#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaCTT.h"

int main()
{
    //MENU
    int opcao, x, codB;
    char r;
    CTT ct_consulta;
    char nomeConsulta[100];

    Lista *li = NULL;
    if ((li = criaLista()) == NULL) {
        abortaPrograma();
    }
    abrirLista(li);
    x = tamanhoLista(li);
    if(x){
        printf("Carregado %d contatos", x);
    } else {
        printf("A lista esta vazia");
    }
    printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
    getchar();
    system("cls");


    do{
        printf("========== Lista de contatos ACME S.A ==========\n\n");
        printf("MENU: \n\n");
        printf("1 - Inserir novo contato.\n");
        printf("2 - Exibir lista de contatos.\n");
        printf("3 - Buscar contato por codigo.\n");
        printf("4 - Buscar contato por nome.\n");
        printf("5 - Editar contato.\n");
        printf("6 - Remover contato.\n");
        printf("7 - Encerrar programa.\n");

        printf("\nSelecione uma opcao: ");
        scanf(" %d", &opcao);
        fflush(stdin);
        system("cls");

    switch (opcao){
    case 1: //inserir elemento
        x = insereOrdenado(li, coletaDados());
        system("cls");
            if (x) {
                printf("Contato %d inserido com sucesso!", x);
            } else { //em caso de problemas em algum dado da inserção
                printf("Nao foi possivel inserir...");
            }
        printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
        getchar();
        system("cls");

        break;

    case 2: //exibir lista de contatos
        mostraLista(li);
        printf("\nPressione ENTER para continuar...");
        getchar();
        system("cls");
        break;

    case 3: //buscar contato por codigo
        printf("Digite o codigo do cliente que deseja consultar: ");
        scanf("%d", &codB);
        getchar();
        x = consultaCod(li, codB, &ct_consulta);
        if(x){
            printConsulta(codB, &ct_consulta);
        }else{ //em caso de codigos inexistentes na lista
            printf("Cliente nao localizado...");
        }
        printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
        getchar();
        system("cls");

        break;

    case 4: //buscar por nome
        printf("Digite o nome/sobrenome do cliente: ");
        fgets(nomeConsulta, sizeof(nomeConsulta), stdin);
        nomeConsulta[strcspn(nomeConsulta, "\n")] = '\0';

        consultaNome(li, nomeConsulta);

        printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
        getchar();
        system("cls");
        break;

    case 5: //editar contato
        printf("Digite o codigo do cliente que deseja editar: ");
        scanf("%d", &codB);
        getchar();
        x = consultaCod(li, codB, &ct_consulta);
        if(x){
            printConsulta(codB, &ct_consulta);
        }else{ //em caso de codigos inexistentes na lista
            printf("Cliente nao localizado...\n");
            printf("Retornando ao menu...");
            printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
            getchar();
            system("cls");
            break;
        }
        printf("\n\n");
        printf("Deseja mesmo editar esse cliente? s/n\n");
        scanf(" %c", &r);
        getchar();

        if(r == 's' || r == 'S'){
            altDados(li, codB);
        }
        else if(r == 'n' || r == 'N'){
            printf("\nCliente nao editado...\n\n");
            printf("Retornando ao menu...");
            printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
            getchar();
            system("cls");
        }else{ //caso seja escrito algo diferente de n ou s
            printf("Opcao invalida!");
            printf("Retornando ao menu...");
            printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
            getchar();
            system("cls");
        }
        break;

    case 6: //remover contato
        printf("Digite o codigo do cliente que deseja remover: ");
        scanf("%d", &codB);
        getchar();

        x = consultaCod(li, codB, &ct_consulta);
        if(x){
            printConsulta(codB, &ct_consulta);
        }else{ //Em caso de codigo inexistente na lista
            printf("Cliente nao localizado...\n");
            printf("Retornando ao menu...");
            printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
            getchar();
            system("cls");
            break;
        }
        printf("\n\n");
        printf("Deseja mesmo remover esse cliente? s/n\n");
        scanf(" %c", &r);
        getchar();

        if(r == 's' || r == 'S'){
            x = removeOrdenado(li, codB);
            if (x) {
                printf("\nCliente %d removido!", codB);
            } else {
                printf("\nNao foi possivel remover");
            }
        }else if(r == 'n' || r == 'N'){
            printf("\nCliente nao removido...\n");
            printf("Retornando ao menu...");
        }else{ //caso seja escrito algo diferente de n ou s
            printf("Opcao invalida!\n");
            printf("Retornando ao menu...");
        }

        printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
        getchar();
        system("cls");

        break;
//
    case 7: //encerrar
        x=tamanhoLista(li);
        if(x==0){
            reiniciaArquivo(); //evita erros caso o arquivo estiver corrompido ou vazio
            }
        else{
            printf("Salvando %d contatos", x);
            fecharLista(li);
        }
        exit (0);
    default:
        printf("Opcao invalida!!");
        printf("\n\n\n\n\n\n\n\n\nPressione ENTER para continuar...");
        getchar();
        system("cls");
        break;

    }

    }while(opcao != 7);
}
