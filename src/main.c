#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validar_login(char *login, int senha);
void entrarNoSistema();
void fazerLogin();
void fazerCadastro();
void criarConta(char *cpf);

int main(){

    entrarNoSistema();
}


void entrarNoSistema(){

    int escolha;
    printf("===== Bem Vindo !!! =====\n");
    printf("Digite:\n 1 para login \n 2 para cadastro \n 0 para sair\n");
    printf("=========================\n");
    scanf("%d", &escolha);


    switch(escolha){
        case 1:
            fazerLogin();
            break;

        case 2:
            fazerCadastro();
            break;

        case 3:
            exit(0);
    }
}

void fazerLogin(){

    char login[12];
    int senha, validacao;

    printf("Insira seu CPF e Senha\n");
    printf("CPF: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%d", &senha);
    printf("=========================\n");
    validacao = validar_login(login, senha);

    if (validacao == 1)
        printf("Usuario encontrado\n"); // Aqui deve ser inserida a função que vai abrir o menu de opções
    else
        printf("Login Invalido! Tente Novamente :(\n");
}


int validar_login(char *login, int senha){

    FILE *arquivo_login;
    char linha[23], str_senha[10], login_space[25];
    arquivo_login = fopen("public/arquivo_login.txt", "r");
    while(!feof(arquivo_login)){
        fgets(linha, 23, arquivo_login);
        sprintf(str_senha, "%d", senha);
        strcpy(login_space, login);
        strcat(login_space, " ");
        strcat(login_space, str_senha);
        if (strcmp(linha, login_space) == 0){
            return 1;
        }
    }
    return 0;
}

void fazerCadastro(){

    FILE *arquivo_login;
    char linha[12], cpf[12], senha[100];

    printf("\nDigite seu cpf:\n");
    scanf("%s", cpf);
    getchar();

    arquivo_login = fopen("public/arquivo_login.txt", "r");
    while(!feof(arquivo_login)){
        fgets(linha, 12, arquivo_login);

        if (strcmp(linha, cpf) == 0){
        printf("CPF já cadastrado\n\n");
        entrarNoSistema();
        }
    }
    fclose(arquivo_login);

    if(strcmp(linha, cpf) != 0){
        arquivo_login = fopen("public/arquivo_login.txt", "a+");
        printf("\nDigite sua senha:\n");
        scanf("%s", senha);
        getchar();
        fprintf(arquivo_login, "\n%s %s", cpf, senha);
        fclose(arquivo_login);
        criarConta(cpf);
    }
}

void criarConta(char *cpf){
    FILE *conta;
    char caminho[25] = "public/";
    strcat(cpf, ".txt");
    strcat(caminho, cpf);
    conta = fopen(caminho, "w");
    fprintf(conta, "%s", "0");
    fclose(conta);
}


