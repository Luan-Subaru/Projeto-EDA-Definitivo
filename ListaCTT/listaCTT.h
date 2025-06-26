typedef struct Cliente{
    int id;
    char nome[100];
    char empresa[50];
    char departamento[50];
    char telefone[15];
    char celular[15];
    char email[50];
}CTT;

//funcoes lista dinamica



typedef struct elemento* Lista;

Lista *criaLista();
//PONTO

void reiniciaArquivo();

void abrirLista(Lista *li);

void fecharLista(Lista *li);

void mostraLista(Lista *li);

void abortaPrograma();

int tamanhoLista(Lista *li);

int listaVazia(Lista *li);

int insereOrdenado(Lista *li, CTT ct);

int removeOrdenado(Lista *li, int cod);

int consultaCod(Lista *li, int mat, CTT *ct);

void printConsulta(int a, CTT *ct);

CTT coletaDados();

void altDados(Lista *li, int cod);

//

//funçoes suplementares

int verificarDuplicidade(Lista li, int id);

char converteString(char c);

int comparaString(const char *str1, const char *str2);

void consultaNome(Lista *li, const char *nome);

