#include <stdio.h>

int main() {
    float numero1, numero2, resultado;
    char operacao;

    printf("Calculadora\n");
    printf("Digite o primeiro numero: ");
    scanf("%f", &numero1);

    printf("Digite a operacao (+, -, *, /): ");
    scanf(" %c", &operacao);

    printf("Digite o segundo numero: ");
    scanf("%f", &numero2);

    switch (operacao) {
        case '+':
            resultado = numero1 + numero2;
            printf("Resultado: %.2f\n", resultado);
            break;
        case '-':
            resultado = numero1 - numero2;
            printf("Resultado: %.2f\n", resultado);
            break;
        case '*':
            resultado = numero1 * numero2;
            printf("Resultado: %.2f\n", resultado);
            break;
        case '/':
            if (numero2 == 0) {
                printf("Erro: divisao por zero!\n");
            } else {
                resultado = numero1 / numero2;
                printf("Resultado: %.2f\n", resultado);
            }
            break;
        default:
            printf("Operacao invalida!\n");
            break;
    }

    return 0;
}
