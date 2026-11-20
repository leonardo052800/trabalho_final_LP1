#include <stdio.h>
#include <stdlib.h>

#define MAX_LOTES 150

typedef struct {
    int id;
    int peso;
} Lote;

typedef struct {
    int cargaAtual;
    int qtdLotes;
    int lotes[MAX_LOTES];
} Conteiner;

int comparar(const void *a, const void *b) {
    Lote *l1 = (Lote *)a;
    Lote *l2 = (Lote *)b;

    return l2->peso - l1->peso;
}

int obterPesoPorId(Lote lotes[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (lotes[i].id == id)
            return lotes[i].peso;
    }
    return 0;
}

int main() {

    FILE *arquivo = fopen("lotes_7.txt", "r");//copiar o caminho do arquivo de entrada aqui

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int n;
    int capacidade;

    fscanf(arquivo, "%d %d", &n, &capacidade);

    Lote lotes[MAX_LOTES];
    Lote originais[MAX_LOTES];

    for (int i = 0; i < n; i++) {
        fscanf(arquivo, "%d %d",
               &lotes[i].id,
               &lotes[i].peso);

        originais[i] = lotes[i];
    }

    fclose(arquivo);

    qsort(lotes, n, sizeof(Lote), comparar);

    Conteiner conteineres[MAX_LOTES];

    int qtdConteineres = 0;

    for (int i = 0; i < n; i++) {

        int colocado = 0;

        for (int j = 0; j < qtdConteineres; j++) {

            if (conteineres[j].cargaAtual + lotes[i].peso
                <= capacidade) {

                conteineres[j].lotes[
                    conteineres[j].qtdLotes
                ] = lotes[i].id;

                conteineres[j].qtdLotes++;

                conteineres[j].cargaAtual +=
                    lotes[i].peso;

                colocado = 1;
                break;
            }
        }

        if (!colocado) {

            conteineres[qtdConteineres].cargaAtual =
                lotes[i].peso;

            conteineres[qtdConteineres].qtdLotes = 1;

            conteineres[qtdConteineres].lotes[0] =
                lotes[i].id;

            qtdConteineres++;
        }
    }

    int usados[MAX_LOTES] = {0};
    int solucaoValida = 1;

    for (int i = 0; i < qtdConteineres; i++) {

        int soma = 0;

        for (int j = 0; j < conteineres[i].qtdLotes; j++) {

            int id = conteineres[i].lotes[j];

            usados[id]++;

            soma += obterPesoPorId(
                originais,
                n,
                id
            );
        }

        if (soma > capacidade) {
            solucaoValida = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (usados[i] != 1) {
            solucaoValida = 0;
        }
    }

    if (solucaoValida)
        printf("Solucao valida!\n\n");
    else
        printf("Solucao invalida!\n\n");

    FILE *saida = fopen("C:\\Users\\LEONA\\Downloads\\saida_lotes_7.txt", "w");//copiar o caminho do arquivo aqui

    for (int i = 0; i < qtdConteineres; i++) {

        int carga = 0;

        printf("Conteiner %d: ", i + 1);
        fprintf(saida, "Conteiner %d: ", i + 1);

        for (int j = 0; j < conteineres[i].qtdLotes; j++) {

            int id = conteineres[i].lotes[j];

            printf("%d ", id);
            fprintf(saida, "%d ", id);

            carga += obterPesoPorId(
                originais,
                n,
                id
            );
        }

        printf("(%d/%d)\n",
               carga,
               capacidade);

        fprintf(saida,
                "(%d/%d)\n",
                carga,
                capacidade);
    }

    printf("\nTotal de conteineres: %d\n",
           qtdConteineres);

    fprintf(saida,
            "\nTotal de conteineres: %d\n",
            qtdConteineres);

    fclose(saida);

    return 0;
}