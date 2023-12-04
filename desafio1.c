#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned char uchar;

void ocuparArmario(uchar *armarios) {
    
    if (*armarios == 0xFF) {
        printf("Todos os armários estão ocupados!\n");
        return;
    }

    int pos;
    do {
        pos = rand() % 8;  
    } while ((*armarios & (1 << pos)) != 0);  

    *armarios |= (1 << pos);  // Ocupa o armário
    printf("Armário %d foi ocupado.\n", pos + 1);
}

void liberarArmario(uchar *armarios) {
    int pos;

    printf("Digite a posição do armário (1-8) para ser liberado: ");
    if (scanf("%d", &pos) != 1 || pos < 1 || pos > 8) {
        printf("Entrada inválida. Por favor, digite um número entre 1 e 8.\n");
        
        while (getchar() != '\n');
        return;
    }

    
    pos--;

    if ((*armarios & (1 << pos)) == 0) {
        printf("O armário %d já está desocupado!\n", pos + 1);
        return;
    }

    *armarios &= ~(1 << pos);  
    printf("Armário %d foi liberado.\n", pos + 1);
}

int main() {
    uchar armarios = 0;  
    int opcao;

    srand(time(NULL));  

    do {
        printf("\nMenu:\n");
        printf("1. Ocupar armário.\n");
        printf("2. Liberar armário.\n");
        printf("3. Sair.\n");

        printf("Escolha uma opção (1-3): ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                ocuparArmario(&armarios);
                break;
            case 2:
                liberarArmario(&armarios);
                break;
            case 3:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }

    } while (opcao != 3);

    return 0;
}
