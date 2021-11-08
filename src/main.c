#include <stdio.h>

int main(){
    char login[6];
    int senha;
    printf("===== Bem Vindo !!! =====\n");
    printf("Insira seu Login e Senha\n");
    printf("Login: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%d", &senha);
    printf("=========================\n");
    return 0;
}
