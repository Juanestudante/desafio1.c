#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Enum para os tipos de investimento
typedef enum {
    PREFIXADO,
    IPCA,
    SELIC,
    CDI
} TipoInvestimento;

// Estrutura de Data
typedef struct {
    int day;
    int month;
    int year;
} Data;

// Estrutura de Investimento
typedef struct {
    Data dataAplicacao;
    float valorAplicado;
    float valorBruto;
    float imposto;
    float taxaJuros;
    TipoInvestimento tipo;
    char nome[50];
} Investimento;

// Estrutura de Titular
typedef struct {
    char nomeTitular[50];
    Investimento* investimentos;
    int qtdInvestimentos;
} Titular;

// Variável global para a data atual
Data dataAtual;

// Função para calcular o número de dias entre duas datas
int calcularDias(Data inicio, Data fim) {
    struct tm a = {0,0,0,inicio.day,inicio.month-1,inicio.year-1900};
    struct tm b = {0,0,0,fim.day,fim.month-1,fim.year-1900};
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    double difference = difftime(y, x) / (60 * 60 * 24);
    return (int)difference;
}

// Função para atualizar o investimento com base na taxa de juros e tempo
void atualizarInvestimento(Investimento* inv) {
    int dias = calcularDias(inv->dataAplicacao, dataAtual);
    float taxaDiaria = pow(1 + inv->taxaJuros / 100, 1.0 / 365) - 1;
    inv->valorBruto = inv->valorAplicado * pow(1 + taxaDiaria, dias);
    inv->imposto = inv->valorBruto * 0.15;  // Exemplo de cálculo de imposto
}

// Função para imprimir o valor bruto total de um titular
void imprimirValorBrutoTotal(Titular* titular) {
    float totalBruto = 0.0;
    for (int i = 0; i < titular->qtdInvestimentos; i++) {
        totalBruto += titular->investimentos[i].valorBruto;
    }
    printf("Valor Bruto Total de %s: R$ %.2f\n", titular->nomeTitular, totalBruto);
}

// Função para imprimir o valor líquido total de um titular
void imprimirValorLiquidoTotal(Titular* titular) {
    float totalLiquido = 0.0;
    for (int i = 0; i < titular->qtdInvestimentos; i++) {
        totalLiquido += titular->investimentos[i].valorBruto - titular->investimentos[i].imposto;
    }
    printf("Valor Líquido Total de %s: R$ %.2f\n", titular->nomeTitular, totalLiquido);
}

// Função para criar um investimento
Investimento criarInvestimento() {
    Investimento inv;
    
    printf("Dia da aplicação: ");
    scanf("%d", &inv.dataAplicacao.day);
    printf("Mês da aplicação: ");
    scanf("%d", &inv.dataAplicacao.month);
    printf("Ano da aplicação: ");
    scanf("%d", &inv.dataAplicacao.year);
    
    printf("Valor aplicado: ");
    scanf("%f", &inv.valorAplicado);
    
    printf("Tipo de investimento (0: Prefixado, 1: IPCA+, 2: Selic, 3: CDI): ");
    int tipo;
    scanf("%d", &tipo);
    inv.tipo = (TipoInvestimento)tipo;
    
    printf("Nome do investimento: ");
    scanf(" %[^\n]", inv.nome);
    
    printf("Taxa de juros anual (%%): ");
    scanf("%f", &inv.taxaJuros);
    
    atualizarInvestimento(&inv);
    
    return inv;
}

// Função para criar um titular e seus investimentos
Titular criarTitular() {
    Titular titular;
    
    printf("Nome do titular: ");
    scanf(" %[^\n]", titular.nomeTitular);
    
    printf("Quantidade de investimentos: ");
    scanf("%d", &titular.qtdInvestimentos);
    
    titular.investimentos = (Investimento*) malloc(titular.qtdInvestimentos * sizeof(Investimento));
    
    for (int i = 0; i < titular.qtdInvestimentos; i++) {
        printf("\nInvestimento %d:\n", i + 1);
        titular.investimentos[i] = criarInvestimento();
    }
    
    return titular;
}

// Função principal
int main() {
    // Definindo a data atual
    dataAtual.day = 6;
    dataAtual.month = 9;
    dataAtual.year = 2024;
    
    int numTitulares;
    printf("Quantos titulares? ");
    scanf("%d", &numTitulares);
    
    Titular* titulares = (Titular*) malloc(numTitulares * sizeof(Titular));
    
    for (int i = 0; i < numTitulares; i++) {
        printf("\nTitular %d:\n", i + 1);
        titulares[i] = criarTitular();
    }
    
    // Imprimindo os valores bruto e líquido totais
    for (int i = 0; i < numTitulares; i++) {
        imprimirValorBrutoTotal(&titulares[i]);
        imprimirValorLiquidoTotal(&titulares[i]);
    }
    
    // Liberando memória
    for (int i = 0; i < numTitulares; i++) {
        free(titulares[i].investimentos);
    }
    free(titulares);
    
    return 0;
}
         