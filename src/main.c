#include <stdio.h>
#include <string.h>

int validar_login(char *login, int senha);

int main(){
    char login[6];
    int senha, validacao;
    printf("===== Bem Vindo !!! =====\n");
    printf("Insira seu Login e Senha\n");
    printf("Login: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%d", &senha);
    printf("=========================\n");
    validacao = validar_login(login, senha);
    if (validacao == 1)
        printf("Usuario encontrado\n"); // Aqui deve ser inserida a função que vai abrir o menu de opções
    else
        printf("Login Invalido! Tente Novamente :(\n");
    return 0;
}

int validar_login(char *login, int senha){
    FILE *arquivo_login;
    char linha[20], str_senha[6], login_space[7];
    arquivo_login = fopen("public/arquivo_login.txt", "r");
    while(!feof(arquivo_login)){
        fgets(linha, 20, arquivo_login);
        sprintf(str_senha, "%d", senha);
        strcpy(login_space, login);
        strcat(login_space, " ");
        if (linha == strcat(login_space, str_senha)){
            return 1;
        }
    }
    return 0;
}
