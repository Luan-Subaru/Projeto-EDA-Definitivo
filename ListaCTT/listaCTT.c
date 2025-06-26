#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaCTT.h"

typedef struct elemento{
    CTT dados;
    struct elemento *prox;
}EL;

Lista *criaLista(){ //cria o espaco utilizado durante o programa
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

void abortaPrograma(){  //interrompe o programa para evitar erros
    printf("Erro! Lista nao alocada, ");
    printf("programa sera encerrado...\n\n\n");
    system("pause");
    exit(1);
}

int listaVazia(Lista * li){ //comprova que a lista esta vazia
    if(li == NULL){
        abortaPrograma();
    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}

int tamanhoLista(Lista *li){ //verifica o tamanho da lista
    if(li == NULL){
        abortaPrograma();
    }
    int ac = 0;
    EL *no = *li;
    while(no != NULL){
        ac++;
        no = no->prox;
    }
    return ac;
}

int verificarDuplicidade(Lista li, int id) { // impede a criação de dois codigos iguais
    EL *atual = li;
    while (atual != NULL && atual->dados.id <= id) {
        if (atual->dados.id == id) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int insereOrdenado(Lista *li, CTT ct){  //utilizado para inserir um usuario, com mudancas na parte de duplicidade e inserção
    if(li == NULL){
        abortaPrograma();
    }

    while (verificarDuplicidade(*li, ct.id)) {
        char confirma;
        printf("Codigo inserido ja existente, deseja inserir outro codigo? s/n\n");
        scanf(" %c", &confirma);
        getchar();

        if(confirma == 's' || confirma == 'S'){
            printf("Digite o codigo novo: ");
            scanf("%d", &ct.id);
        }else if(confirma == 'n' || confirma == 'N'){
            return 0;
        }

    }

    EL *no = (EL*) malloc(sizeof(EL));
    if(no == NULL){
        return 0;
    }
    no->dados = ct;
    if(listaVazia(li)){
        no->prox = (*li);
        *li = no;
        return ct.id;
    }else{
        EL *ant, *atual = *li;
        while(atual != NULL && atual->dados.id < ct.id){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = ant->prox;
            ant->prox = no;
        }
        return ct.id;
    }
}

int removeOrdenado(Lista *li, int cod){ //utilizado para remover um usuario
    int id;
    if(li == NULL){
        abortaPrograma();
    }
    EL *ant, *no = *li;
    while(no != NULL && no->dados.id != cod){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }
    if(no == *li){
        *li = no->prox;
    }else{
        ant->prox = no->prox;
    }
    id = no->dados.id;
    free(no);
    return id;
}

int consultaCod(Lista *li, int cod, CTT *ct){ //busca pelo codigo no sistema
    if(li == NULL){
        abortaPrograma();
    }
    EL *no = *li;
    while(no != NULL && no->dados.id != cod){
        no = no->prox;
    }
    if(no != NULL){
        *ct = no->dados;
        return 1;
    }
    return 0;
}

void printConsulta(int a, CTT *ct){ // utilizado na busca por codigo
        system("cls");
        printf("\n========== Cliente %d ==========", a);
        printf("\nCodigo: %d", ct->id);
        printf("\nNome: %s", ct->nome);
        printf("\nEmpresa: %s", ct->empresa);
        printf("\nDepartamento: %s", ct->departamento);
        printf("\nTelefone: %s", ct->telefone);
        printf("\nCelular: %s", ct->celular);
        printf("\nE-mail: %s", ct->email);
        printf("\n=================================");
}

void printConsulta2(int a, CTT *ct){ //foi criado para não apagar a repetição da função de buscar por nome
        printf("\n========== Cliente %d ==========", a);
        printf("\nCodigo: %d", ct->id);
        printf("\nNome: %s", ct->nome);
        printf("\nEmpresa: %s", ct->empresa);
        printf("\nDepartamento: %s", ct->departamento);
        printf("\nTelefone: %s", ct->telefone);
        printf("\nCelular: %s", ct->celular);
        printf("\nE-mail: %s", ct->email);
        printf("\n=================================");
}

CTT coletaDados(){  //utilizada na inserção de dados
    CTT c;
    int verificador = 0;    //0= falso, 1= verdadeiro
    char string[100];       //string usada para comparação

    while (!verificador) {  //Antes caso fosse escrito uma letra, aparecia um usuario de codigo 0
        printf("Codigo: "); // Com isso, agora forca a ser um numero inteiro
        if (fgets(string, sizeof(string), stdin) != NULL) {
            if (sscanf(string, "%d", &c.id) == 1) {
                verificador = 1;
            } else {
                printf("Entrada invalida! Insira um numero inteiro para o codigo.\n");
            }
        }
    }

    printf("Nome: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Empresa: ");
    fgets(c.empresa, sizeof(c.empresa), stdin);
    c.empresa[strcspn(c.empresa, "\n")] = '\0';

    printf("Departamento: ");
    fgets(c.departamento, sizeof(c.departamento), stdin);
    c.departamento[strcspn(c.departamento, "\n")] = '\0';

    printf("Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    printf("Celular: ");
    fgets(c.celular, sizeof(c.celular), stdin);
    c.celular[strcspn(c.celular, "\n")] = '\0';

    printf("Email: ");
    fgets(c.email, sizeof(c.email), stdin);
    c.email[strcspn(c.email, "\n")] = '\0';


    return c;
}

    // Apresentar a lista inteira
void mostraLista(Lista *li) {
    if (li == NULL) {
        abortaPrograma(); //em caso de erro
    }
    else if ((*li) == NULL) {
        printf("A lista esta vazia"); //em caso de lista vazia
    }
    else{
    EL *no = *li;
        printf("========== Lista de Contatos ==========\n");
    while (no != NULL) {
        printf("\nCodigo: %d\n", no->dados.id);
        printf("Nome: %s\n", no->dados.nome);
        printf("Empresa: %s\n", no->dados.empresa);
        printf("Departamento: %s\n", no->dados.departamento);
        printf("Telefone: %s\n", no->dados.telefone);
        printf("Celular: %s\n", no->dados.celular);
        printf("Email: %s\n\n", no->dados.email);
        printf("=======================================\n");

        no = no->prox;}// passar para o proximo struct
    }
}

    // Fechar e salvar a lista
void fecharLista(Lista *li) {
    FILE *arquivo = fopen("listasalva.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao salvar a lista\n");
        return;
    } // em caso de erro

    EL *no = *li;
    while (no != NULL) {
        fwrite(&no->dados, sizeof(CTT), 1, arquivo);// salvamento dos dados
        no = no->prox; // passar para o proximo
    }

    fclose(arquivo);
    printf("\nLista salva com sucesso!\n");
}

void reiniciaArquivo(){ //caso a lista for entregue vazia, ela será destruida e recomeçada na abertura do programa
    printf("Nenhum contato salvo.\n");
    printf("Excluindo possiveis contatos em outras sessoes...\n");
    if (remove("listasalva.dat") == 0) {
        printf("Antigos salvamentos excluidos com sucesso.\n");
    } else {
        printf("Falha na exclusao. Pode nao haver arquivo antigo.\n");
    }
}


    //Abrir a lista, puxando os dados salvos anteriormente
void abrirLista(Lista *li) {
    FILE *arquivo = fopen("listasalva.dat", "rb");
    if (arquivo == NULL) { //caso não exista arquivo, outro será gerado
        printf("Nenhum dado existente, gerando nova lista\n");
        FILE *arquivo = NULL;
        do {
        arquivo = fopen("listasalva.dat", "w");
        if (arquivo == NULL) {
            printf("Erro ao criar novo arquivo. Tentando novamente...\n");
        }
        } while (arquivo == NULL);//repetirá o processo até que seja criado corretamente
        printf("Nova lista criada com sucesso.\n");
        fclose(arquivo);
        return;
    }   //Caso a lista esteje vazia
    CTT carregar;
    while (fread(&carregar, sizeof(CTT), 1, arquivo)) {
        insereOrdenado(li, carregar);
    }// carregar os dados

    fclose(arquivo);
    printf("Lista carregada com sucesso!\n");

}


void altDados(Lista *li, int cod){  //Usada para alterar dados
    EL *no= *li;

    while (no != NULL && no->dados.id != cod){
        no=no->prox;
    }

    char string[100];   //string usada apenas para armazenamento momentaneo
    printf("Insira o novo nome (deixe em branco para permanecer igual): ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")]= '\0';
    if(strlen(string) > 0){ //caso seja entregue vazia, nao haverá alterações
        strcpy(no->dados.nome ,string);
        }

    printf("Insira o novo empresa (deixe em branco para permanecer igual): ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")]= '\0';
    if(strlen(string) > 0){
        strcpy(no->dados.empresa ,string);
        }

    printf("Insira o novo departamento (deixe em branco para permanecer igual): ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")]= '\0';
    if(strlen(string) > 0){
        strcpy(no->dados.departamento ,string);
        }

    printf("Insira o novo telefone (deixe em branco para permanecer igual): ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")]= '\0';
    if(strlen(string) > 0){
        strcpy(no->dados.telefone ,string);
        }

    printf("Insira o novo celular (deixe em branco para permanecer igual): ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")]= '\0';
        if(strlen(string) > 0){
                strcpy(no->dados.celular ,string);
        }

    printf("Insira o novo e-mail (deixe em branco para permanecer igual): ");
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")]= '\0';
        if(strlen(string) > 0){
        strcpy(no->dados.email ,string);
        }

    printf("Dados alterados com sucesso");
    printf("\nPressione ENTER para continuar...");
    getchar();
    system("cls");
}

char converteString(char c){    // deixa as letras minusculas para a comparação
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }

    return c;
}

int comparaString(const char *str1, const char *str2){  //compara duas strings
    int i, j;
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    for (i = 0; i <= len1 - len2; i++) {
        for (j = 0; j < len2; j++) {
            char c1 = converteString(str1[i + j]); //ignora letras maiusculas ou minusculas
            char c2 = converteString(str2[j]);

            if (c1 != c2) {
                break;
            }
        }
        if (j == len2) {
            return 1; // Encontrou substring
        }
    }

    return 0; // Não encontrou
}

void consultaNome(Lista *li, const char *nome){ //consulta a partir do nome

    if (li == NULL || *li == NULL) {
        printf("Lista vazia ou invalida.\n");
        return;
    }

    EL *no = *li;
    int encontrou = 0;

    while (no != NULL) {
        if (comparaString(no->dados.nome, nome)) {
            printConsulta2(no->dados.id, &(no->dados));
            printf("\n");
            encontrou = 1;
        }
        no = no->prox;
    }

    if (!encontrou) {
        printf("Não foi achado nenhum cliente com o nome que inseriu: %s\n", nome);
    }
}
