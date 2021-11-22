#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

int validar_login(char *login, int senha);
void entrarNoSistema();
void fazerLogin();
void fazerCadastro();
void criarConta(char *cpf);
void menuSistema(char *login);
void verificarSaldo(char *login);
void realizarDeposito(char *login);
void sacarDinheiro(char *login);
void transferirDinheiro(char *login);
void excluirConta(char *login);
int checkIfFileExists(const char *filename);
void excluirCadastro(char *cpf, int senha);
int encontrarLinha(char *login, int senha);

void clrscr()
{
    system("@cls||clear");
}

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

        case 0:
            exit(0);
    }
}

void fazerLogin(){

    int condicao = 0;
    char login[15];
    int senha, validacao;

    printf("Insira seu CPF e Senha\n");
    while(condicao !=1){
        printf("CPF: ");
        scanf("%s", login);
        printf("Senha: ");
        scanf("%d", &senha);
        printf("=========================\n");
        validacao = validar_login(login, senha);

        if (validacao == 1){
            condicao = 1;
            clrscr();
            printf("Login com sucesso!\n");
            menuSistema(login);
        }
        else
            clrscr();
            printf("Login Invalido! Tente Novamente :(\n");
    }
}


int validar_login(char *login, int senha){

    FILE *arquivo_login;
    char linha[23], str_senha[10], login_space[25];
    arquivo_login = fopen("public/arquivo_login.txt", "r");
    while(!feof(arquivo_login)){
        fgets(linha, 23, arquivo_login);
        if(linha[strlen(linha)-1] == '\n') linha[strlen(linha)-1] = '\0';
        sprintf(str_senha, "%d", senha);
        strcpy(login_space, login);
        strcat(login_space, " ");
        strcat(login_space, str_senha);
        if (strcmp(linha, login_space) == 0){
        fclose(arquivo_login);
            return 1;
        }
    }
    fclose(arquivo_login);
    return 0;
}

void fazerCadastro(){

    FILE *arquivo_login;
    char linha[12], cpf[12], senha[100];
    int condicao = 0;
    int condicaoCPF = 0;
    int lenght = 0;
    int i;

    printf("\nDigite seu cpf:\n");
    while(condicaoCPF!=1){
        scanf("%s", cpf);
        getchar();
        lenght = strlen(cpf);
        for (i = 0; i < lenght; i++){
            if((isalpha(cpf[i])) && cpf[i] != '\0'){
                printf("\nDigite o cpf corretamente:\n");
                break;
            }
        }
        if(cpf[i] == '\0') condicaoCPF = 1;
    }

    arquivo_login = fopen("public/arquivo_login.txt", "r");
    while(!feof(arquivo_login)){
        fgets(linha, 12, arquivo_login);

        if (strcmp(linha, cpf) == 0){
        printf("CPF já cadastrado\n\n");
        fclose(arquivo_login);
        entrarNoSistema();
        }
    }
    fclose(arquivo_login);

    if(strcmp(linha, cpf) != 0){
        arquivo_login = fopen("public/arquivo_login.txt", "a+");
        while(condicao!=1){
            printf("\nDigite sua senha de 4 digitos:\n");
            scanf("%s", senha);
            getchar();
            if(strlen(senha) == 4){
            condicao = 1;
            fprintf(arquivo_login, "\n%s %s", cpf, senha);
            fclose(arquivo_login);
            criarConta(cpf);
            } else printf("\nErro\n");
        }
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
    printf("Conta criada com sucesso\n");
    clrscr();
    entrarNoSistema();
}

void menuSistema(char *login){

    int menu;
    printf("===== Menu de opções !!! =====\n");
    printf("Digite:\n 1 para Verificar Saldo \n 2 para Realizar Depósito Bancário \n 3 para Sacar dinheiro \n 4 para Transferência bancária \n 5 para Excluir sua conta \n 0 para Sair\n");
    printf("=========================\n");
    scanf("%d", &menu);

    switch(menu){
        case 1:
            verificarSaldo(login);
            break;

        case 2:
            realizarDeposito(login);
            break;

        case 3:
            sacarDinheiro(login);
            break;

        case 4:
            transferirDinheiro(login);
            break;

        case 5:
            excluirConta(login);
            break;

        case 0:
            exit(0);
    }
}

void verificarSaldo(char *login){

    FILE *arquivo;
    char caminho[100] = "public/";
    char saldo[20];
    char textoArquivo[18];
    strcpy(textoArquivo, login);
    strcat(textoArquivo, ".txt");
    strcat(caminho, textoArquivo);

    arquivo = fopen(caminho, "r");
    while(!feof(arquivo)){
        fscanf(arquivo, "%s", saldo);
        printf("\n Seu Saldo é de: %s reais!\n", saldo);
    }
    fclose(arquivo);
    sleep(2);
    clrscr();
    menuSistema(login);
}

void realizarDeposito(char *login){

    FILE *arquivo;
    char textoArquivo[18];
    strcpy(textoArquivo, login);
    strcat(textoArquivo, ".txt");
    char caminho[100] = "public/";
    char saldo[20];
    float quantia;
    strcat(caminho, textoArquivo);

    printf("\n Quanto você deseja adicionar?\n");
    scanf("%f", &quantia);

    arquivo = fopen(caminho, "r");
    fscanf(arquivo, "%s", saldo);
    fclose(arquivo);

    quantia+=atof(saldo);
    arquivo = fopen(caminho, "w");
    fprintf(arquivo, "%.2f", quantia);
    fclose(arquivo);

    printf("\n Depósito realizado!\n");
    sleep(2);
    clrscr();
    menuSistema(login);
}

void sacarDinheiro(char *login){

    FILE *arquivo;
    char textoArquivo[18];
    strcpy(textoArquivo, login);
    strcat(textoArquivo, ".txt");
    char caminho[100] = "public/";
    char saldo[20];
    float quantia;
    int condicao = 0;
    strcat(caminho, textoArquivo);

    printf("\n Digite a quantia que deseja sacar\n");
    while(condicao==0){
    scanf("%f", &quantia);

    arquivo = fopen(caminho, "r");
    fscanf(arquivo, "%s", saldo);
    fclose(arquivo);

    if(quantia > atof(saldo)) printf("\nVocê não possui saldo suficiente, tente novamente:\n");
    else condicao = 1;
    }
    quantia = atof(saldo) - quantia;
    arquivo = fopen(caminho, "w");
    fprintf(arquivo, "%.2f", quantia);
    fclose(arquivo);

    printf("\n Saque realizado!\n");
    sleep(2);
    clrscr();
    menuSistema(login);
}

void transferirDinheiro(char *login){

    FILE *arquivo;
    char textoArquivo[18];
    char contaDestino[18];
    strcpy(textoArquivo, login);
    strcat(textoArquivo, ".txt");
    char caminho[100] = "public/";
    char caminhoDestino[100] = "public/";
    char saldo[20];
    char saldoDestino[20];
    float quantia;
    float quantiaDestino;
    int condicao = 0;
    int contaExiste = 0;
    int certeza = 0;
    strcat(caminho, textoArquivo);


    printf("\n Digite o numero do CPF para quem você quer transferir\n");
    while(contaExiste == 0){
        scanf("%s", contaDestino);
        strcat(contaDestino, ".txt");
        strcat(caminhoDestino, contaDestino);
        if(checkIfFileExists(caminhoDestino)) contaExiste = 1;
        else{
            printf("\n Conta inexistente, tente novamente!\n");
            strcpy(caminhoDestino, "public/");
            getchar();
        }
    }
    printf("\n Digite a quantia que deseja transferir\n");
    while(condicao==0){
    scanf("%f", &quantia);

    arquivo = fopen(caminho, "r");
    fscanf(arquivo, "%s", saldo);
    fclose(arquivo);

    if(quantia > atof(saldo)) printf("\nVocê não possui saldo suficiente, tente novamente:\n");
    else condicao = 1;
    }
    printf("\n Digite 1 se tiver certeza que deseja transferir\n");
    scanf("%d", &certeza);
    if(certeza!=1){
        clrscr();
        menuSistema(login);
    }
    quantiaDestino = quantia;
    quantia = atof(saldo) - quantia;
    arquivo = fopen(caminho, "w");
    fprintf(arquivo, "%.2f", quantia);
    fclose(arquivo);


    //transferência
    arquivo = fopen(caminhoDestino, "r");
    fscanf(arquivo, "%s", saldoDestino);
    fclose(arquivo);

    quantiaDestino = atof(saldoDestino) + quantiaDestino;
    arquivo = fopen(caminhoDestino, "w");
    fprintf(arquivo, "%.2f", quantiaDestino);
    fclose(arquivo);

    printf("\n Transferência realizada!\n");
    sleep(2);
    clrscr();
    menuSistema(login);
}

int checkIfFileExists(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else
        return 0;
}

void excluirConta(char *login){

    int validacao;
    char cpf[12];
    int senha;
    int condicao = 0;
    int decisao = 0;
    char textoArquivo[18];
    char caminho[100] = "public/";
    strcpy(textoArquivo, login);
    strcat(textoArquivo, ".txt");
    strcat(caminho, textoArquivo);

    printf("Digite novamente seu CPF e Senha\n");

    while(condicao == 0){
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Senha: ");
    scanf("%d", &senha);
    printf("=========================\n");
    validacao = validar_login(cpf, senha);

    if (validacao == 1){
        condicao = 1;
        clrscr();
        printf("Digite 1 se deseja mesmo excluir a conta!\n");
        scanf("%d", &decisao);

        if(decisao!=1){
        menuSistema(login);
        }

        remove(caminho);
        excluirCadastro(cpf, senha);

        sleep(2);
        clrscr();
        entrarNoSistema();
    }
    else
    clrscr();
        printf("Login Invalido! Tente Novamente :(\n");
    }
}

void excluirCadastro(char *cpf, int senha){

    FILE *input = fopen("public/arquivo_login.txt", "r");
    FILE *output = fopen("transferindo.txt", "w");
    char texto[1001] = "";
    unsigned int linha_selecionada = encontrarLinha(cpf, senha);
    unsigned int linha_atual = 1;
    while(fgets(texto, 1001, input) != NULL){
            if(linha_atual != linha_selecionada){
                fputs(texto, output);
            }
            memset(texto, 0, sizeof(char) * 1001);
            linha_atual += 1;
        }
        fclose(input);
        fclose(output);
        remove("public/arquivo_login.txt");
        rename("transferindo.txt", "public/arquivo_login.txt");
        printf("\nConta excluida com sucesso!\n");
}

int encontrarLinha(char *login, int senha){

    FILE *arquivo_login;
    int linhaLogin = 1;
    char linha[23], str_senha[10], login_space[25];
    arquivo_login = fopen("public/arquivo_login.txt", "r");
    while(!feof(arquivo_login)){
        fgets(linha, 23, arquivo_login);
        if(linha[strlen(linha)-1] == '\n') linha[strlen(linha)-1] = '\0';
        sprintf(str_senha, "%d", senha);
        strcpy(login_space, login);
        strcat(login_space, " ");
        strcat(login_space, str_senha);
        if (strcmp(linha, login_space) == 0){
        fclose(arquivo_login);
            return linhaLogin;
        }
        linhaLogin++;
    }
    fclose(arquivo_login);
    return 0;
}