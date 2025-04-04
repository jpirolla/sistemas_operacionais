#include <stdio.h>
#include <math.h>

#define N 65  

unsigned long long fatorialModificado(int n) {
    unsigned long long resultado = 1;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
        // modificando o fatorial para incluir operações adicionais
        double extra_calc = pow(i, 1.5) + log(i + 1) * sin(i) + sqrt(i);
        resultado += (unsigned long long)extra_calc;  
    }
    return resultado;
}

int main() {
    for (int i = 1; i <= N; i++) {
        printf("Fatorial modificado de %d = %llu\n", i, fatorialModificado(i));
    }
    
    printf("\nFim teste CPU-bound\n\n");
    return 0;
}
