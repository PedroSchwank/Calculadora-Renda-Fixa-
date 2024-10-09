#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definição da struct que representa um produto de renda fixa
typedef struct {
    char nome[50];
    float valor_inicial;
    float taxa_juros; // em percentual
    int prazo;        // em meses
} RendaFixa;

#define MAX_INVESTIMENTOS 100

// Funções auxiliares
void cadastrarInvestimento(RendaFixa *investimentos, int *total);
void simularRendimento(RendaFixa *investimentos, int total);
void salvarSimulacoes(RendaFixa *investimentos, int total);
void carregarSimulacoes(RendaFixa *investimentos, int *total);
void gerarRelatorio(RendaFixa *investimentos, int total);

int main() {
    RendaFixa investimentos[MAX_INVESTIMENTOS];
    int totalInvestimentos = 0;
    int opcao;

    carregarSimulacoes(investimentos, &totalInvestimentos);

    do {
        printf("\n--- Calculadora de Rendimento de Renda Fixa ---\n");
        printf("1. Cadastrar produto de renda fixa\n");
        printf("2. Simular rendimento\n");
        printf("3. Salvar simulações\n");
        printf("4. Gerar relatório\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarInvestimento(investimentos, &totalInvestimentos);
                break;
            case 2:
                simularRendimento(investimentos, totalInvestimentos);
                break;
            case 3:
                salvarSimulacoes(investimentos, totalInvestimentos);
                break;
            case 4:
                gerarRelatorio(investimentos, totalInvestimentos);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// Função para cadastrar um novo produto de renda fixa
void cadastrarInvestimento(RendaFixa *investimentos, int *total) {
    if (*total >= MAX_INVESTIMENTOS) {
        printf("Limite de investimentos atingido.\n");
        return;
    }

    printf("Nome do produto de renda fixa: ");
    scanf("%s", investimentos[*total].nome);
    printf("Valor inicial: ");
    scanf("%f", &investimentos[*total].valor_inicial);
    printf("Taxa de juros anual (em %%): ");
    scanf("%f", &investimentos[*total].taxa_juros);
    printf("Prazo (em meses): ");
    scanf("%d", &investimentos[*total].prazo);

    (*total)++;
}

// Função para simular o rendimento com base na fórmula de juros compostos
void simularRendimento(RendaFixa *investimentos, int total) {
    if (total == 0) {
        printf("Nenhum investimento cadastrado.\n");
        return;
    }

    printf("\n--- Simulação de Rendimento ---\n");
    for (int i = 0; i < total; i++) {
        float rendimento = investimentos[i].valor_inicial * pow(1 + (investimentos[i].taxa_juros / 100.0) / 12, investimentos[i].prazo);
        printf("Produto: %s\n", investimentos[i].nome);
        printf("Valor Inicial: %.2f\n", investimentos[i].valor_inicial);
        printf("Valor Final (após %d meses): %.2f\n", investimentos[i].prazo, rendimento);
        printf("Rendimento Total: %.2f\n", rendimento - investimentos[i].valor_inicial);
        printf("-----------------------------------\n");
    }
}

// Função para salvar as simulações em um arquivo binário
void salvarSimulacoes(RendaFixa *investimentos, int total) {
    FILE *file = fopen("renda_fixa.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    fwrite(investimentos, sizeof(RendaFixa), total, file);
    fclose(file);

    printf("Simulações salvas com sucesso!\n");
}

// Função para carregar as simulações de um arquivo binário
void carregarSimulacoes(RendaFixa *investimentos, int *total) {
    FILE *file = fopen("renda_fixa.bin", "rb");
    if (file == NULL) {
        printf("Nenhum arquivo de simulações encontrado.\n");
        return;
    }

    *total = fread(investimentos, sizeof(RendaFixa), MAX_INVESTIMENTOS, file);
    fclose(file);

    printf("%d simulações carregadas com sucesso!\n", *total);
}

// Função para gerar um relatório em arquivo de texto
void gerarRelatorio(RendaFixa *investimentos, int total) {
    FILE *file = fopen("relatorio_renda_fixa.txt", "w");
    if (file == NULL) {
        printf("Erro ao criar relatório.\n");
        return;
    }

    fprintf(file, "--- Relatório de Simulações de Renda Fixa ---\n");
    for (int i = 0; i < total; i++) {
        float rendimento = investimentos[i].valor_inicial * pow(1 + (investimentos[i].taxa_juros / 100.0) / 12, investimentos[i].prazo);
        fprintf(file, "Produto: %s\n", investimentos[i].nome);
        fprintf(file, "Valor Inicial: %.2f\n", investimentos[i].valor_inicial);
        fprintf(file, "Valor Final (após %d meses): %.2f\n", investimentos[i].prazo, rendimento);
        fprintf(file, "Rendimento Total: %.2f\n", rendimento - investimentos[i].valor_inicial);
        fprintf(file, "-----------------------------------\n");
    }

    fclose(file);
    printf("Relatório gerado com sucesso!\n");
}
