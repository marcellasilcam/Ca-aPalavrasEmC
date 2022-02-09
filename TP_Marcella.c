//Marcella Silveira Campos - 21.1.4008

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "Example.h"

int **aloca_matriz (int n, int m){
    int **matriz = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matriz[i] = malloc(m * sizeof(int));
    return matriz;
}

void desaloca_matriz (int **matriz, int n){
    for(int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void desaloca_matriz_3 (char ***matriz, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            free(matriz[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free (matriz);
}

char **aloca_matriz_char (int n, int m){
    char **matriz = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
        matriz[i] = malloc(m * sizeof(char));
    return matriz;
}

char ***aloca_matriz_3 (int n, int m){
    char ***matriz = malloc(n * sizeof(char**));
    for (int i = 0; i < n; i++){
        matriz[i] = malloc(m * sizeof(char*));
        for (int j = 0; j < m; j++){
            matriz[i][j] = malloc(2 * sizeof(char));
            matriz[i][j][1] = 'b';
        }
    }
    return matriz;
}

void desaloca_matriz_char (char **matriz, int n){
    for(int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

void zera_vetor (char *vetor, int n){
    for (int i = 0; i < n; i++)
        vetor[i] = '\0';
}

void zera_vetor_int (int *vetor, int n){
    for (int i = 0; i < n; i++)
        vetor[i] = '\0';
}

void escolha1_facil (char nome[]);
void escolha1_medio (char nome[]);
void escolha1_dificil (char nome[]);

void escolha1 (){
    char nome[50]; int opcao = 0, funciona;
    do {
        funciona = 0;
        printf("Ok, vamos comecar um novo jogo. Qual o nome do arquivo que contem as palavras?\n");
        getchar();
        fgets(nome, 50, stdin);
        int n = strlen(nome);
        for (int i = 0; i < n; i++)
            if (nome[i] == '\n')
                nome [i] = '\0';
        printf("Qual nivel de dificuldade voce deseja? (digite apenas o numero da escolha)\n");
        printf("1- facil;\n");
        printf("2- medio;\n");
        printf("3- dificil.\n");
        scanf("%d", &opcao);
        switch (opcao){
            case 1:
                escolha1_facil(nome);
                break;
            case 2:
                escolha1_medio(nome);
                break;
            case 3: 
                escolha1_dificil(nome);
                break;
            default: 
                printf("Opcao invalida. Favor digitar apenas o numero de sua escolha.\n");
                funciona = 1;
        }
    } while (funciona != 0);
    printf("Obrigada por jogar e volte sempre!\n");
}

int jogadas (int acabou, int **inicio, int **fim, int vetor[], char ****matriz, char **palavras, int tamanho[]){
    int correto = 0; char escolha[10], posicao1[3], posicao2[3], responder[30];
    
    //zerando os vetores para evitar lixo de memoria
    for (int i = 0; i < 30; i++)
        responder[i] = '\0';
    for (int i = 0; i < 10; i++)
        escolha[i] = '\0';
    for (int i = 0; i < 3; i++)
        posicao1[i] = '\0';
    for (int i = 0; i < 3; i++)
        posicao2[i] = '\0';
    
    printf("Qual posicao tem uma palavra escondida?\n");
    fgets(responder, 30, stdin);
    int n = strlen(responder), cat = 0, dog = 0, fish = 0, bird = 0;
    for (cat = 0; cat < n; cat++){ //armazenando a escolha do usuario
        while (responder[cat] != ' ' && responder[cat] != '\n'){
            escolha[fish] = responder[cat];
            cat++; fish++;
        }
        break;
    }
    escolha[fish] = '\0';
    
    if (strcmp(escolha, "marcar") == 0){ //conferindo a escolha do usuario
        fish = 0; //armazenando as posições que o usuário digitar
        for (dog = cat + 1; dog < n; dog++){
            while (responder[dog] != ' ' && responder[dog] != '\n'){
                posicao1[fish] = responder[dog];
                dog++; fish++;
            }
            break;
        } 
        // posicao1[2] = '\0';
        fish = 0;
        for (bird = dog + 1; bird < n; bird++){
            while (responder[bird] != ' ' && responder[bird] != '\n'){
                posicao2[fish] = responder[bird];
                bird++; fish++;
            }
            break;
        }
        // posicao2[2] = '\0';
        
        if ((posicao1[0] - 'A') >= vetor[0] || (posicao1[1]  - 'A') >= vetor[1] || (posicao2[0] - 'A') >= vetor[0] || (posicao2[1] - 'A') >= vetor[1]){
            printf("OPA! Esse indice sequer existe no jogo. Vai com calma e tente novamente.\n");
        }
        else {
            for (int i = 0; i < vetor[2]; i++){ //checando se a posição digitada está certa no jogo
                if ((posicao1[0] - 'A') == inicio[i][0] && (posicao1[1]  - 'A') == inicio[i][1] && (posicao2[0] - 'A') == fim[i][0] && (posicao2[1] - 'A') == fim [i][1]){
                    if (inicio[i][0] == fim[i][0]){ //estara na horizontal ou vertical
                        if (inicio[i][1] < fim[i][1]){
                            for (int j = inicio[i][0]; j <= fim[i][0]; j++){
                                for (int k = inicio[i][1]; k <= fim[i][1]; k++){
                                    (*matriz)[j][k][1] = 'v';
                                }
                            }
                        }
                        else { //invertida
                            for (int j = fim[i][0]; j <= inicio[i][0]; j++){
                                for (int k = fim[i][1]; k <= inicio[i][1]; k++){
                                    (*matriz)[j][k][1] = 'v';
                                }
                            }
                        }
                    }
                    else if (inicio[i][1] == fim[i][1]){
                        if (inicio[i][0] < fim[i][0]){
                            for (int j = inicio[i][0]; j <= fim[i][0]; j++){
                                for (int k = inicio[i][1]; k <= fim[i][1]; k++){
                                    (*matriz)[j][k][1] = 'v';
                                }
                            }
                        }
                        else { //invertida
                            for (int j = fim[i][0]; j <= inicio[i][0]; j++){
                                for (int k = fim[i][1]; k <= inicio[i][1]; k++){
                                    (*matriz)[j][k][1] = 'v';
                                }
                            }
                        }
                    }
                    else { //estara na diagonal
                        if (inicio[i][0] < fim[i][0]){
                            for (int a = 0; a < tamanho[i]; a++)
                                (*matriz)[inicio[i][0] + a][inicio[i][1] + a][1] = 'v';
                        }
                        else { //invertida
                            for (int a = tamanho[i] - 1; a >= 0; a--)
                                (*matriz)[fim[i][0] + a][fim[i][1] + a][1] = 'v';
                        }
                    }
                    acabou++;
                    correto = 1;
                }
            }
            if (correto == 0)
                printf("Nao ha nenhuma palavra do jogo nessa posicao. Tente novamente!\n");
            else if (correto == 1)
                printf("Mandou bem! Voce achou uma palavra!\n");
        }
    }
    else if (strcmp(escolha, "resolver") == 0){
        printf("Eu em... que sem graca...\n");
        acabou = vetor[2];
        for (int i = 0; i < vetor[2]; i++){
            if (inicio[i][0] == fim[i][0]){ //estara na horizontal ou vertical
                if (inicio[i][1] < fim[i][1]){
                    for (int j = inicio[i][0]; j <= fim[i][0]; j++){
                        for (int k = inicio[i][1]; k <= fim[i][1]; k++){
                            (*matriz)[j][k][1] = 'v';
                        }
                    }
                }
                else { //invertida
                    for (int j = fim[i][0]; j <= inicio[i][0]; j++){
                        for (int k = fim[i][1]; k <= inicio[i][1]; k++){
                            (*matriz)[j][k][1] = 'v';
                        }
                    }
                }
            }
            else if (inicio[i][1] == fim[i][1]){
                if (inicio[i][0] < fim[i][0]){
                    for (int j = inicio[i][0]; j <= fim[i][0]; j++){
                        for (int k = inicio[i][1]; k <= fim[i][1]; k++){
                            (*matriz)[j][k][1] = 'v';
                        }
                    }
                }
                else { //invertida
                    for (int j = fim[i][0]; j <= inicio[i][0]; j++){
                        for (int k = fim[i][1]; k <= inicio[i][1]; k++){
                            (*matriz)[j][k][1] = 'v';
                        }
                    }
                }
            }
            else { //estara na diagonal
                if (inicio[i][0] < fim[i][0]){
                    for (int a = 0; a < tamanho[i]; a++)
                        (*matriz)[inicio[i][0] + a][inicio[i][1] + a][1] = 'v';
                }
                else { //invertida
                    for (int a = tamanho[i] - 1; a >= 0; a--)
                        (*matriz)[fim[i][0] + a][fim[i][1] + a][1] = 'v';
                }
            }
        }
    }
    else if (strcmp(escolha, "sair") == 0){
        int sim_nao;
        do {
            sim_nao = 0;
            printf("Certeza que deseja sair? Desse jeito, o jogo nao sera salvo com nenhuma das alteracoes feitas.\n");
            printf("1- Sim, tenho certeza.\n");
            printf("2- Nao, vou voltar a jogar.\n");
            scanf("%d", &sim_nao);
            if (sim_nao == 1)
                exit(0);
            else if (sim_nao == 2) 
                continue;
            else 
                printf("Comando invalido. Favor digitar apenas o numero de sua escolha.\n");
        } while (sim_nao != 1 && sim_nao != 2);
    }
    else if (strcmp(escolha, "salvar") == 0){
        char alterado[27];
        zera_vetor(alterado, 27);
        char **posicao_inicio = aloca_matriz_char(vetor[2], 3), **posicao_fim = aloca_matriz_char(vetor[2], 3);
        
        for (int i = 0; i < vetor[2]; i++){ //armazenando as posicoes com seus caracteres correspondentes
            posicao_inicio[i][0] = inicio[i][0] + 'a';
            posicao_inicio[i][1] = inicio[i][1] + 'a';
            posicao_inicio[i][2] = '\0';
            posicao_fim[i][0] = fim[i][0] + 'a';
            posicao_fim[i][1] = fim[i][1] + 'a';
            posicao_fim[i][2] = '\0';
        } 

        for (int i = 0; i < vetor[2]; i++){ //deixando os caracteres das palavras minusculos novamente
            for (int j = 0; j < tamanho[i]; j++){
                palavras[i][j] = tolower(palavras[i][j]);
            }
        }

        fish = 0; //armazenando o nome do arquivo em que o jogo sera salvo
        for (dog = cat + 1; dog < n; dog++){
            while (responder[dog] != ' ' && responder[dog] != '\n'){
                alterado[fish] = responder[dog];
                dog++; fish++;
            }
            break;
        } 
        alterado[dog] = '\0';
        printf("nome = %s \n", alterado);

        FILE *save = fopen(alterado, "w");
        fprintf(save, "%d %d\n", vetor[0], vetor[1]);
        for(int i = 0; i < vetor[0]; i ++){
            for (int j = 0; j < vetor[1]; j++){
                fprintf(save, "%c ", (*matriz)[i][j][0]);
            }
            fprintf(save, "\n");
        }
        fprintf(save, "%d\n", vetor[2]);
        for (int i = 0; i < vetor[2]; i ++){
            fprintf(save, "%s ", palavras[i]);
            if ((*matriz)[inicio[i][0]][inicio[i][1]][1] == 'v'){
                fprintf(save, "%s %s\n", posicao_inicio[i], posicao_fim[i]);
            }
            else {
                fprintf(save, "-- --\n");
            }
        }
        // fprintf(save, "%c%c %c%c\n", posicao_inicio[i][0], posicao_inicio[i][1], posicao_fim[i][0], posicao_fim[i][1]);

        fclose(save);
        desaloca_matriz_char(posicao_inicio, vetor[2]);
        desaloca_matriz_char(posicao_fim, vetor[2]);
    }
    else {
        printf("Comando invalido. Os unicos comandos possiveis sao:\n");
        printf("marcar\n");
        printf("resolver\n");
        printf("sair\n");
        printf("salvar\n");
    }
    return acabou;
}

void imprime_matriz (char ***matriz, int vetor[]){
    printf("    ");
    for (int i = 0; i < vetor[1]; i++){ //imprimindo cabecalho da matriz
        printf(BG_YELLOW(BLACK("%c")), i+65);
        printf("   ");
    }
    printf("\n");
    printf("  ");
    printf(TAB_TJ);
    for (int i = 0; i < vetor[1]; i++)
        printf(TAB_HOR TAB_HOR TAB_HOR TAB_TJ);
    printf("\n");
    
    for(int i = 0; i < vetor[0]; i++){ //imprimindo a matriz
        printf(BG_YELLOW(BLACK("%c")), i+65);
        printf(" ");
        printf(TAB_VER " ");
        for(int j = 0; j < vetor[1]; j++){
            if (matriz[i][j][1] == 'b'){
                printf("%c ", matriz[i][j][0]);
                printf(TAB_VER " "); 
            } 
            else {
                printf(BOLD(BG_RED("%c")), matriz[i][j][0]);
                printf(" "TAB_VER " ");
            }
        }
        printf("\n");
        printf("  ");
        printf(TAB_ML);
        for (int i = 0; i < vetor[1]; i++)
            printf(TAB_HOR TAB_HOR TAB_HOR TAB_MR);
        printf("\n");
    }
}

void escolha1_facil (char nome[]){
    srand(time(NULL));
    FILE *arquivo = fopen(nome, "r");
    int vetor[3], troca_maior = 0, l = 0; 

    for (int i = 0; i < 3; i++) //zerando o vetor para evitar lixo de memoria sempre q o jogo for executado
        vetor[i] = 0;

    for (int i = 0; i < 3; i++) //armazenando as informações de dimensoes da matriz e quantidade de palavras
        fscanf(arquivo, "%d", &vetor[i]);

    char ***matriz = aloca_matriz_3(vetor[0], vetor[1]);

    if ( vetor[1] > vetor[0]) //descobrindo a maior dimensao possivel para a matriz das palavras do arquivo
        troca_maior = vetor[1];
    else 
        troca_maior = vetor[0];
    
    char **palavras = aloca_matriz_char(vetor[2], troca_maior);
    int *tamanho = malloc(vetor[2] * sizeof(int)), *sorteio_linha = malloc(vetor[2] * sizeof(int)), *sorteio_coluna = malloc(vetor[2] * sizeof(int));
    
    for (int i = 0; i < vetor[2]; i++) //armazenando as palavras do jogo em cada linha da matriz palavras
        fscanf(arquivo, "%s", palavras[i]);

    for (int i = 0; i < vetor[2]; i++){ //trocando letras minusculas por maiusculas de cada palavra do jogo
        for (int j = 0; j < troca_maior; j++){
            palavras[i][j] = toupper(palavras[i][j]);
        }
    }

    for (int i = 0; i < vetor[2]; i++) //armazenando o tamanho de cada uma das palavras do jogo
        tamanho[i] = strlen(palavras[i]);
    
    int *l_c = malloc(vetor[2] * sizeof(int)), funciona = 0;
    int aux[vetor[2]]; int m = 0, mm = 0;
    
    for (int i = 0; i < vetor[2]; i++) //zerando o vetor para evitar lixo de memoria ao rodar o codigo
        aux[i] = 0;
    
    int **inicio = aloca_matriz(vetor[2], 3), **fim = aloca_matriz(vetor[2], 3); /* alocando os vetores de inicio
    e fim apenas para que possam ser desalocados toda vez inicialmente que o do-while repetir */
    
    do { //fazendo as posicoes da matriz serem validas
        int tem_que_mudar; int deixar_tudo_igual = 0;
        desaloca_matriz(inicio, vetor[2]); desaloca_matriz(fim, vetor[2]);
        inicio = aloca_matriz(vetor[2], 3); fim = aloca_matriz(vetor[2], 3);
        funciona = 0; m = 0; mm = 0; 
        
        for (int i = 0; i < vetor[2]; i++) //sorteando se sera posicionado na horizontal ou vertical
            l_c[i] = rand() % 2;


        for (int i = 0; i < vetor[2]; i++){ //sorteando a linha e a coluna de cada palavra
            if (l_c[i] == 0){
                sorteio_linha[m] = rand() % vetor[0];
                m++;
                }
            else {
                sorteio_coluna[mm] = rand() % vetor[1];
                mm++;
            }
        }

        for (int i = 0; i < m; i++){ //excluindo a possibilidade de uma palavra ser sorteada para a mesma linha
            for (int j = i + 1; j < m; j++){
                if (sorteio_linha[i] == sorteio_linha[j])
                    sorteio_linha[j] = rand() % vetor[0];
            }
        }
        for (int i = 0; i < mm; i++){ //excluindo a possibilidade de uma palavra ser sorteada para a mesma coluna
            for (int j = i + 1; j < mm; j++){
                if (sorteio_coluna[i] == sorteio_coluna[j])
                    sorteio_coluna[j] = rand() % vetor[1];
            }
        }
        
        for (int i = 0; i < vetor[0]; i++){ //zerando a matriz com caracteres maiusculos
            for (int j = 0; j < vetor[1]; j++){
                matriz[i][j][0] = (rand() % 25) + 65;
            }
        }

        m = 0; mm = 0;
        for (int i = 0; i < vetor[2]; i++){ //preenchendo a matriz com os caracteres das palavras
            if (l_c[i] == 0){ //se for horizontal
                aux[i] = 1 + (vetor[1] - tamanho[i]);
                aux[i] = rand() % aux[i]; //decidindo a posição de início de cada palavra
                l = 0;
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    matriz[sorteio_linha[m]][k][0] = palavras[i][l];
                    l++;
                }
                m++; //quantidade de palavras na horizontal
                //armazenando suas posições de início e fim
                inicio[i][0] = sorteio_linha[i];
                inicio[i][1] = aux[i];
                fim[i][0] = sorteio_linha[i];
                fim[i][1] = (aux[i] + tamanho[i]) - 1;
            }
            else { //se for vertical
                aux[i] = 1 + (vetor[0] - tamanho[i]);
                aux[i] = rand() % aux[i]; //decidindo a posição de início de cada palavra
                l = 0;
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    matriz[k][sorteio_coluna[mm]][0] = palavras[i][l];
                    l++;
                }
                mm++; //quantidade de palavras na vertical
                //armazenando suas posições de início e fim
                inicio[i][0] = aux[i];
                inicio[i][1] = sorteio_coluna[i];
                fim[i][0] = (aux[i] + tamanho[i]) - 1;
                fim[i][1] = sorteio_coluna[i];
            }
        }

        m = 0; mm = 0;
        for (int i = 0; i < vetor[2]; i++){ //checando se as palavras estao corretas na matriz
            if (l_c[i] == 0){ //se for horizontal
                l = 0;
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    if (palavras[i][l] != matriz[sorteio_linha[m]][k][0])
                        funciona = 1;
                    l++;
                }
                m++;
            }
            else { //se for vertical
                l = 0; 
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    if (palavras[i][k] != matriz[k][sorteio_coluna[i]][0])
                        funciona = 1;
                    l++;
                }
                mm++;
            }
        }

        deixar_tudo_igual = rand() % 2; /* a chance de todas as palavras estarem só na horizontal ou só na vertical
        será por sorteio */
        tem_que_mudar = 0;

        if (deixar_tudo_igual == 0){
            for (int i = 0; i < vetor[2]; i++){
                for (int j = i + 1; j < vetor[2]; j++){
                    if (l_c[i] == l_c[j]){
                        tem_que_mudar++;
                    }
                }
            }
        }

        if (tem_que_mudar == vetor[2] || tem_que_mudar == 10) //não poderão estar só na horizontal ou vertical
            funciona = 1;

    } while (funciona != 0);

    getchar();
    
    imprime_matriz(matriz, vetor);

    int acabou = 0;
    
    do {
        acabou = jogadas(acabou, inicio, fim, vetor, &matriz, palavras, tamanho);

        imprime_matriz(matriz, vetor);

    } while (acabou != vetor[2]);

    free(sorteio_coluna);
    free(sorteio_linha);
    desaloca_matriz(inicio, vetor[2]); desaloca_matriz(fim, vetor[2]);
    free(l_c);
    free(tamanho);
    desaloca_matriz_char(palavras, vetor[2]);
    fclose(arquivo);
}

void escolha1_medio (char nome[]){
    srand(time(NULL));
    FILE *arquivo = fopen(nome, "r");
    int vetor[3], troca_maior = 0, l = 0;

    for (int i = 0; i < 3; i++) //zerando o vetor q armazenara dados da matriz
        vetor[i] = 0;

    for (int i = 0; i < 3; i++) //passando dados da matriz pro vetor
        fscanf(arquivo, "%d", &vetor[i]);

    
    char ***matriz = aloca_matriz_3(vetor[0], vetor[1]);

    if ( vetor[1] > vetor[0]) //definindo a maior dimensao da matriz palavras
        troca_maior = vetor[1];
    else 
        troca_maior = vetor[0];
    
    char **palavras = aloca_matriz_char(vetor[2], troca_maior); //matriz q armazenara as palavras do arquivo
    int *tamanho = malloc(vetor[2] * sizeof(int)), *sorteio_linha = malloc(vetor[2] * sizeof(int)), *sorteio_coluna = malloc(vetor[2] * sizeof(int)), **sorteio_diagonal = aloca_matriz(vetor[2], 2);
    
    for (int i = 0; i < vetor[2]; i++) //armazenando as palavras para usar no jogo
        fscanf(arquivo, "%s", palavras[i]);

    for (int i = 0; i < vetor[2]; i++){ //deixando as letras das palavras maiusculas
        for (int j = 0; j < troca_maior; j++){
            palavras[i][j] = toupper(palavras[i][j]);
        }
    }

    for (int i = 0; i < vetor[2]; i++) //armazenando o tamanho de cada palavra
        tamanho[i] = strlen(palavras[i]);

    
    int *l_c_d = malloc(vetor[2] * sizeof(int)), funciona = 0;
    int *aux = malloc (vetor[2] * sizeof(int)); int m, mm, mmm;

    for (int i = 0; i < vetor[2]; i++) //zerando o vetor q sera usado pra armazenar um numero aleatorio da linha ou coluna
        aux[i] = 0;

    int **inicio = aloca_matriz(vetor[2], 3), **fim = aloca_matriz(vetor[2], 3); //matrizes q armazenarao as posicoes iniciais e finais de cada palavra
    
    do { //fazendo as posicoes da matriz serem validas
        int tem_que_mudar; 
        int deixar_tudo_igual = 0;
        desaloca_matriz(inicio, vetor[2]); desaloca_matriz(fim, vetor[2]); //desalocando para q isso se repita dentro do do-while
        inicio = aloca_matriz(vetor[2], 3); fim = aloca_matriz(vetor[2], 3); //alocando novamente para armazenarem outros valores
        funciona = 0; m = 0; mm = 0; mmm = 0; 
        for (int i = 0; i < vetor[2]; i++) //sorteando se sera posicionado na horizontal, vertical ou diagonal
            l_c_d[i] = rand() % 3;

        for (int i = 0; i < vetor[2]; i++){ //sorteando a linha, a coluna e a diagonal de cada palavra
            if (l_c_d[i] == 0){
                sorteio_linha[m] = rand() % vetor[0];
                m++;
                }
            else if (l_c_d[i] == 1) {
                sorteio_coluna[mm] = rand() % vetor[1];
                mm++;
            }
            else {
                if (tamanho[i] == vetor[1]){
                    sorteio_diagonal[mmm][0] = rand() % (vetor[0] - tamanho[i] + 1);
                    sorteio_diagonal[mmm][1] = 0;
                }
                else if (tamanho[i] == vetor[0]){
                
                    sorteio_diagonal[mmm][0] = 0;
                    sorteio_diagonal[mmm][1] = rand() % (vetor[1] - tamanho[i] + 1);
                }
                else if (tamanho[i] == vetor[0] && tamanho[i] == vetor[1]){
                    sorteio_diagonal[mmm][0] = 0;
                    sorteio_diagonal[mmm][1] = 0;
                }
                else {
                    sorteio_diagonal[mmm][0] = rand() % ((vetor[0] - tamanho[i]) + 1);
                    sorteio_diagonal[mmm][1] = rand() % ((vetor[1] - tamanho[i]) + 1);
                }               
                mmm++;
            }
        }
        for (int i = 0; i < m; i++){ //nao deixando nenhuma palavra pertencer a mesma linha pro jogo nao ficar bobo
            for (int j = i + 1; j < m; j++){
                if (sorteio_linha[i] == sorteio_linha[j])
                    sorteio_linha[j] = rand() % vetor[0];
            }
        }
        for (int i = 0; i < mm; i++){//nao deixando nenhuma palavra pertencer a mesma coluna pro jogo nao ficar bobo
            for (int j = i + 1; j < mm; j++){
                if (sorteio_coluna[i] == sorteio_coluna[j])
                    sorteio_coluna[j] = rand() % vetor[1];
            }
        }

        int *indice = malloc (mmm * sizeof(int)); mmm = 0; 
        for (int i = 0; i < vetor[2]; i++){ //armazenando o indice da palavra que estara na diagonal
            if (l_c_d[i] == 2){
                indice[mmm] = i;
                mmm++;
            }
        }

        for (int i = 0; i < mmm; i++){//nao deixando nenhuma palavra pertencer a mesma diagonal
            for (int j = i + 1; j < mmm; j++){
                if (sorteio_diagonal[i][0] == sorteio_diagonal[j][0] && sorteio_diagonal[i][1] == sorteio_diagonal[j][1]){
                    if (tamanho[indice[j]] == vetor[1]){
                        sorteio_diagonal[mmm][0] = rand() % (vetor[0] - tamanho[indice[j]] + 1);
                        sorteio_diagonal[mmm][1] = 0;
                    }
                    else if (tamanho[indice[j]] == vetor[0]){
                        sorteio_diagonal[mmm][0] = 0;
                        sorteio_diagonal[mmm][1] = rand() % (vetor[1] - tamanho[indice[j]] + 1);
                    }
                    else if (tamanho[indice[j]] == vetor[0] && tamanho[indice[j]] == vetor[1]){
                        sorteio_diagonal[mmm][0] = 0;
                        sorteio_diagonal[mmm][1] = 0;
                    }
                    else {
                        sorteio_diagonal[mmm][0] = rand() % (vetor[0] - tamanho[indice[j]] + 1);
                        sorteio_diagonal[mmm][1] = rand() % (vetor[1] - tamanho[indice[j]] + 1);
                    }
                
                }
            }
        }

        for (int i = 0; i < vetor[0]; i++){ //zerando a matriz
            for (int j = 0; j < vetor[1]; j++){
                matriz[i][j][0] = (rand() % 26) + 65;
            }
        }

        m = 0; mm = 0; mmm = 0;
        for (int i = 0; i < vetor[2]; i++){ //preenchendo a matriz com os caracteres
            if (l_c_d[i] == 0){ //se for horizontal
                aux[i] = 1 + (vetor[1] - tamanho[i]);
                aux[i] = rand() % aux[i];
                l = 0;
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    matriz[sorteio_linha[m]][k][0] = palavras[i][l];
                    l++;
                }
                inicio[i][0] = sorteio_linha[m];
                inicio[i][1] = aux[i];
                fim[i][0] = sorteio_linha[m];
                fim[i][1] = (aux[i] + tamanho[i]) - 1;
                m++;
            }
            else if (l_c_d[i] == 1) { //se for vertical
                aux[i] = 1 + (vetor[0] - tamanho[i]);
                aux[i] = rand() % aux[i];
                l = 0;
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    matriz[k][sorteio_coluna[mm]][0] = palavras[i][l];
                    l++;
                }
                inicio[i][0] = aux[i];
                inicio[i][1] = sorteio_coluna[mm];
                fim[i][0] = (aux[i] + tamanho[i]) - 1;
                fim[i][1] = sorteio_coluna[mm];
                mm++;
            }
            else {
                l = 0; 

                for (int j = 0; j < tamanho[i]; j++){
                    matriz[sorteio_diagonal[mmm][0] + j][sorteio_diagonal[mmm][1] + j][0] = palavras[i][l];
                    l++;
                }
                inicio[i][0] = sorteio_diagonal[mmm][0];
                inicio[i][1] = sorteio_diagonal[mmm][1];
                fim[i][0] = (inicio[i][0] + tamanho[i]) - 1;
                fim[i][1] = (inicio[i][1] + tamanho[i]) - 1;
                mmm++;
            }
        }

        m = 0; mm = 0; mmm = 0;
        for (int i = 0; i < vetor[2]; i++){ //checando se as palavras estao corretas na matriz
            if (l_c_d[i] == 0){ //se for horizontal
                l = 0;
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    if (palavras[i][l] != matriz[sorteio_linha[m]][k][0])
                        funciona = 1;
                    l++;
                }
                m++;
            }
            else if (l_c_d[i] == 1){ //se for vertical
                l = 0; 
                for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                    if (palavras[i][k] != matriz[k][sorteio_coluna[mm]][0])
                        funciona = 1;
                    l++;
                }
                mm++;
            }
            else {
                l = 0;
                for (int j = sorteio_diagonal[mmm][0], k = sorteio_diagonal[mmm][1]; j < sorteio_diagonal[mmm][0] + tamanho[i]; j++, k++){
                    if (matriz[j][k][0] != palavras[i][l])
                        funciona = 1;
                    l++;
                }
                mmm++;
            }
        }

        tem_que_mudar = 0;

        if (deixar_tudo_igual == 0){ //sorteando se as palavras poderao estar na mesma direção
            for (int j = 1; j < vetor[2]; j++){
                if (l_c_d[0] == l_c_d[j]){
                    tem_que_mudar++;

                }
            }
        }
        if (tem_que_mudar == vetor[2] - 1){
            funciona = 1;
        }
        zera_vetor_int(aux, vetor[2]);
        free(indice);
    } while (funciona != 0);

    getchar();

    imprime_matriz(matriz, vetor);

    int acabou = 0;

    do {

        acabou = jogadas(acabou, inicio, fim, vetor, &matriz, palavras, tamanho);

        imprime_matriz(matriz, vetor);

    } while (acabou != vetor[2]);


    desaloca_matriz(sorteio_diagonal, mmm);
    free(sorteio_coluna);
    free(sorteio_linha);
    desaloca_matriz(inicio, vetor[2]); desaloca_matriz(fim, vetor[2]);
    free(l_c_d);
    free(tamanho);
    desaloca_matriz_3(matriz, vetor[0], vetor[1]);
    desaloca_matriz_char(palavras, vetor[2]);
    fclose(arquivo);
}

void escolha1_dificil (char nome[]){
    srand(time(NULL));
    FILE *arquivo = fopen(nome, "r");
    int vetor[3], troca_maior = 0, l = 0;

    for (int i = 0; i < 3; i++) //zerando o vetor q armazenara dados da matriz
        vetor[i] = 0;

    for (int i = 0; i < 3; i++) //passando dados da matriz pro vetor
        fscanf(arquivo, "%d", &vetor[i]);

    
    char ***matriz = aloca_matriz_3(vetor[0], vetor[1]);

    if ( vetor[1] > vetor[0]) //achando a maior dimensao da matriz palavras
        troca_maior = vetor[1];
    else 
        troca_maior = vetor[0];
    
    char **palavras = aloca_matriz_char(vetor[2], troca_maior); //matriz q armazenara as palavras do arquivo
    int *tamanho = malloc(vetor[2] * sizeof(int)), *sorteio_linha = malloc(vetor[2] * sizeof(int)), *sorteio_coluna = malloc(vetor[2] * sizeof(int)), **sorteio_diagonal = aloca_matriz(vetor[2], 2);
    
    for (int i = 0; i < vetor[2]; i++) //armazenando as palavras para usar no jogo
        fscanf(arquivo, "%s", palavras[i]);

    for (int i = 0; i < vetor[2]; i++){ //deixando as letras das palavras maiusculas
        for (int j = 0; j < troca_maior; j++){
            palavras[i][j] = toupper(palavras[i][j]);
        }
    }

    for (int i = 0; i < vetor[2]; i++) //armazenando o tamanho de cada palavra
        tamanho[i] = strlen(palavras[i]);

    
    int *l_c_d = malloc(vetor[2] * sizeof(int)), funciona = 0, aux[vetor[2]], m, mm, mmm;
    int *frente_costa = malloc(vetor[2] * sizeof(int));

    int **inicio = aloca_matriz(vetor[2], 3), **fim = aloca_matriz(vetor[2], 3); //matrizes q armazenarao as posicoes iniciais e finais de cada palavra
    
    do { //fazendo as posicoes da matriz serem validas
        int tem_que_mudar; 
        int deixar_tudo_igual = 0;
        desaloca_matriz(inicio, vetor[2]); desaloca_matriz(fim, vetor[2]); //desalocando para q isso se repita dentro do do-while
        inicio = aloca_matriz(vetor[2], 3); fim = aloca_matriz(vetor[2], 3); //alocando novamente para armazenarem outros valores
        funciona = 0; m = 0; mm = 0; mmm = 0; 
        for (int i = 0; i < vetor[2]; i++) //sorteando se sera posicionado na horizontal, vertical ou diagonal
            l_c_d[i] = rand() % 3;

        for (int i = 0; i < vetor[2]; i++) //sorteando se sera lido de esquerda pra direita ou direita pra esquerda
            frente_costa[i] = rand() % 2;

        for (int i = 0; i < vetor[2]; i++){ //sorteando a linha, a coluna e a diagonal de cada palavra
            if (l_c_d[i] == 0){
                sorteio_linha[m] = rand() % vetor[0];
                m++;
                }
            else if (l_c_d[i] == 1) {
                sorteio_coluna[mm] = rand() % vetor[1];
                mm++;
            }
            else {
                if (tamanho[i] == vetor[1]){
                    sorteio_diagonal[mmm][0] = rand() % (vetor[0] - tamanho[i] + 1);
                    sorteio_diagonal[mmm][1] = 0;
                }
                else if (tamanho[i] == vetor[0]){
                
                    sorteio_diagonal[mmm][0] = 0;
                    sorteio_diagonal[mmm][1] = rand() % (vetor[1] - tamanho[i] + 1);
                }
                else if (tamanho[i] == vetor[0] && tamanho[i] == vetor[1]){
                    sorteio_diagonal[mmm][0] = 0;
                    sorteio_diagonal[mmm][1] = 0;
                }
                else {
                    sorteio_diagonal[mmm][0] = rand() % ((vetor[0] - tamanho[i]) + 1);
                    sorteio_diagonal[mmm][1] = rand() % ((vetor[1] - tamanho[i]) + 1);
                }            
                mmm++;
            }
        }

        int *indice = malloc (mmm * sizeof(int)); mmm = 0; //armazenando o indice das palavras que estarao na diagonal
        for (int i = 0; i < vetor[2]; i++){
            if (l_c_d[i] == 2){
                indice[mmm] = i;
                mmm++;
            }
        }

        for (int i = 0; i < m; i++){ //nao deixando nenhuma palavra pertencer a mesma linha pro jogo nao ficar bobo
            for (int j = i + 1; j < m; j++){
                if (sorteio_linha[i] == sorteio_linha[j])
                    sorteio_linha[j] = rand() % vetor[0];
            }
        }

        for (int i = 0; i < mm; i++){//nao deixando nenhuma palavra pertencer a mesma coluna pro jogo nao ficar bobo
            for (int j = i + 1; j < mm; j++){
                if (sorteio_coluna[i] == sorteio_coluna[j])
                    sorteio_coluna[j] = rand() % vetor[1];
            }
        }

        for (int i = 0; i < mmm; i++){//nao deixando nenhuma palavra pertencer a mesma diagonal
            for (int j = i + 1; j < mmm; j++){
                if (sorteio_diagonal[i][0] == sorteio_diagonal[j][0] && sorteio_diagonal[i][1] == sorteio_diagonal[j][1]){
                    if (tamanho[indice[j]] == vetor[0] && tamanho[indice[j]] == vetor[1]){
                        sorteio_diagonal[j][0] = 0;
                        sorteio_diagonal[j][1] = 0;
                    }
                    else if (tamanho[indice[j]] == vetor[0]){
                        sorteio_diagonal[j][0] = 0;
                        sorteio_diagonal[j][1] = rand() % (vetor[1] - tamanho[indice[j]] + 1);
                    }
                    else if (tamanho[indice[j]] == vetor[1]){
                        sorteio_diagonal[j][0] = rand() % (vetor[0] - tamanho[indice[j]] + 1);
                        sorteio_diagonal[j][1] = 0;
                        
                    }
                    else {
                        sorteio_diagonal[j][0] = rand() % (vetor[0] - tamanho[indice[j]] + 1);
                        sorteio_diagonal[j][1] = rand() % (vetor[1] - tamanho[indice[j]] + 1);
                    }
                }
            }
        }

        for (int i = 0; i < vetor[0]; i++){ //zerando a matriz
            for (int j = 0; j < vetor[1]; j++){
                matriz[i][j][0] = (rand() % 26) + 65;
            }
        }

        m = 0; mm = 0; mmm = 0;
        for (int i = 0; i < vetor[2]; i++){ //preenchendo a matriz com os caracteres
            if (l_c_d[i] == 0){ //se for horizontal
                if (frente_costa == 0){
                    aux[i] = 1 + (vetor[1] - tamanho[i]);
                    aux[i] = rand() % aux[i];
                    l = 0;
                    for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                        matriz[sorteio_linha[m]][k][0] = palavras[i][l];
                        l++;
                    }
                    inicio[i][0] = sorteio_linha[m];
                    inicio[i][1] = aux[i];
                    fim[i][0] = sorteio_linha[m];
                    fim[i][1] = (aux[i] + tamanho[i]) - 1;
                    m++;
                }
                else { //frente_costa == 1
                    aux[i] = 1 + (vetor[1] - tamanho[i]);
                    aux[i] = rand() % aux[i];
                    l = 0;
                    for (int k = aux[i] + tamanho[i] - 1; k >= aux[i]; k--){
                        matriz[sorteio_linha[m]][k][0] = palavras[i][l];
                        l++;
                    }
                    inicio[i][0] = sorteio_linha[m];
                    inicio[i][1] = (aux[i] + tamanho[i]) - 1;
                    fim[i][0] = sorteio_linha[m];
                    fim[i][1] = aux[i];
                    m++;
                }
            }
            else if (l_c_d[i] == 1) { //se for vertical
                if (frente_costa == 0){
                    aux[i] = 1 + (vetor[0] - tamanho[i]);
                    aux[i] = rand() % aux[i];
                    l = 0;
                    for (int k = aux[i]; k <= aux[i] + tamanho[i]; k++){
                        matriz[k][sorteio_coluna[mm]][0] = palavras[i][l];
                        l++;
                    }
                    inicio[i][0] = aux[i];
                    inicio[i][1] = sorteio_coluna[mm];
                    fim[i][0] = (aux[i] + tamanho[i]) - 1;
                    fim[i][1] = sorteio_coluna[mm];
                    mm++;
                }
                else { //frente_costa == 1
                    aux[i] = 1 + (vetor[0] - tamanho[i]);
                    aux[i] = rand() % aux[i];
                    l = 0;
                    for (int k = aux[i] + (tamanho[i] - 1); k >= aux[i]; k--){
                        matriz[k][sorteio_coluna[mm]][0] = palavras[i][l];
                        l++;
                    }
                    inicio[i][0] = aux[i];
                    inicio[i][1] = sorteio_coluna[mm];
                    fim[i][0] = (aux[i] + tamanho[i]) - 1;
                    fim[i][1] = sorteio_coluna[mm];
                    mm++;
                }
            }
            else { //se for na diagonal
                if (frente_costa == 0){
                    l = 0;
                    for (int j = 0; j < tamanho[i]; j++){
                        matriz[sorteio_diagonal[mmm][0] + j][sorteio_diagonal[mmm][1] + j][0] = palavras[i][l];
                        l++;
                    }
                    inicio[i][0] = sorteio_diagonal[mmm][0];
                    inicio[i][1] = sorteio_diagonal[mmm][1];
                    fim[i][0] = (inicio[i][0] + tamanho[i]) - 1;
                    fim[i][1] = (inicio[i][1] + tamanho[i]) - 1;
                    mmm++;
                }
                else { //frente_costa == 1
                    l = 0; 
                    for (int j = tamanho[i] - 1; j >= 0; j--){
                        matriz[sorteio_diagonal[mmm][0] + j][sorteio_diagonal[mmm][1] + j][0] = palavras[i][l];
                        l++;
                    }
                    fim[i][0] = sorteio_diagonal[mmm][0];
                    fim[i][1] = sorteio_diagonal[mmm][1];
                    inicio[i][0] = (fim[i][0] + tamanho[i]) - 1;
                    inicio[i][1] = (fim[i][1] + tamanho[i]) - 1;
                    mmm++;
                }
            }
        }

        m = 0; mm = 0; mmm = 0;
        for (int i = 0; i < vetor[2]; i++){ //checando se as palavras estao corretas na matriz
            if (l_c_d[i] == 0){ //se for horizontal
                if (frente_costa[i] == 0){
                    l = 0;
                    for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                        if (palavras[i][l] != matriz[sorteio_linha[m]][k][0]){
                            funciona = 1;
                            break;
                        }
                        l++;
                    }
                    m++;
                }
                else { //frente_costa == 1
                    l = 0;
                    for (int k = aux[i] + (tamanho[i] - 1); k >= aux[i]; k--){
                        if (palavras[i][l] != matriz[sorteio_linha[m]][k][0])
                            funciona = 1;
                        l++;
                    }
                    m++;
                }
            }
            else if (l_c_d[i] == 1){ //se for vertical
                if (frente_costa[i] == 0){
                    l = 0; 
                    for (int k = aux[i]; k < aux[i] + tamanho[i]; k++){
                        if (palavras[i][k] != matriz[k][sorteio_coluna[mm]][0])
                            funciona = 1;
                        l++;
                    }
                    mm++;
                }
                else { //frente_costa == 1
                    l = 0; 
                    for (int k = aux[i] + tamanho[i] - 1; k >= aux[i]; k--){
                        if (palavras[i][k] != matriz[k][sorteio_coluna[mm]][0])
                            funciona = 1;
                        l++;
                    }
                    mm++;
                }
            }
            else { //se for na diagonal
                if (frente_costa[i] == 0){
                    l = 0;
                    for (int a = 0; a < tamanho[i]; a++){
                        if (matriz[sorteio_diagonal[mmm][0] + a][sorteio_diagonal[mmm][1] + a][0] != palavras[i][l])
                            funciona = 1;
                        l++;
                    }
                    mmm++;
                }
                else { //frente_costa == 1
                    l = 0;
                    for (int a = tamanho[i] - 1; a >= 0; a--){
                        if (matriz[sorteio_diagonal[mmm][0] + a][sorteio_diagonal[mmm][1] + a][0] != palavras[i][l])
                            funciona = 1;
                        l++;
                    }
                    mmm++;
                }
            }
        }

        tem_que_mudar = 0;
        deixar_tudo_igual = rand() % 2;

        if (deixar_tudo_igual == 0){
            for (int j = 1; j < vetor[2]; j++){
                if (l_c_d[0] == l_c_d[j]){
                    tem_que_mudar++;

                }
            }
        }
    
        if (tem_que_mudar == vetor[2]){
            funciona = 1;
        }
        
        free(indice);
        zera_vetor_int(aux, vetor[2]);
    } while (funciona != 0);

    getchar();

    imprime_matriz(matriz, vetor);

    int acabou = 0;

    do {

        acabou = jogadas(acabou, inicio, fim, vetor, &matriz, palavras, tamanho);

        imprime_matriz(matriz, vetor);

    } while (acabou != vetor[2]);

    desaloca_matriz(sorteio_diagonal, mmm);
    free(sorteio_coluna);
    free(sorteio_linha); 
    free(frente_costa);
    desaloca_matriz(inicio, vetor[2]); desaloca_matriz(fim, vetor[2]);
    free(l_c_d);
    desaloca_matriz_3(matriz, vetor[0], vetor[1]);
    free(tamanho);
    desaloca_matriz_char(palavras, vetor[2]);
    fclose(arquivo);
}

void escolha2 (){
    char antigo[50];
    printf("De onde paramos? Digite o nome do arquivo que usamos:\n");
    getchar();
    fgets(antigo, 50, stdin);
    int n = strlen(antigo);
    for (int i = 0; i < n; i++)
        if (antigo[i] == '\n')
            antigo[i] = '\0';
    
    FILE *arquivo = fopen(antigo, "r");
    int vetor[3], troca_maior = 0, l = 0, acabou = 0;

    for (int i = 0; i < 3; i++)
        vetor[i] = 0;

    for (int i = 0; i < 2; i++)
        fscanf(arquivo, "%d", &vetor[i]);

    char ***matriz = aloca_matriz_3(vetor[0], vetor[1]), t;

    
    fscanf(arquivo, "%c", &t);
    getc(arquivo);

    for (int i = 0; i < vetor[0]; i++){ //armazenando o caça palavras
        for (int j = 0; j < vetor[1]; j++){
            fscanf(arquivo, "%c ", &t);
            if (t != 8){
                matriz[i][j][0] = t;
            }
        }
    }

    fscanf(arquivo, "%d", &vetor[2]);
    
    if ( vetor[1] > vetor[0])
        troca_maior = vetor[1];
    else 
        troca_maior = vetor[0];
    
    char **palavras = aloca_matriz_char(vetor[2], troca_maior);
    int *tamanho = malloc(vetor[2] * sizeof(int));
    int **posicao_inicio = aloca_matriz(vetor[2], 3), **posicao_fim = aloca_matriz(vetor[2], 3);
    char **inicio = aloca_matriz_char(vetor[2], 3), **fim = aloca_matriz_char(vetor[2], 3);
    int indice[vetor[2]];

    for (int i = 0; i < vetor[2]; i++)
        fscanf(arquivo, "%s %s %s", palavras[i], inicio[i], fim[i]);
    

    for (int i = 0; i < vetor[2]; i++)
        tamanho[i] = strlen(palavras[i]);

    for (int i = 0; i < vetor[2]; i++){
        if (inicio [i][0] != '-'){
            if (inicio[i][0] == fim[i][0] || inicio[i][1] == fim[i][1]){
                for (int j = (inicio[i][0] - 'a'); j <= (fim[i][0] - 'a'); j++){
                    for (int k = (inicio[i][1] - 'a'); (k <= fim[i][1] - 'a'); k++){
                        matriz[j][k][1] = 'v';
                    }
                }
            }
            else {
                indice[l] = i;
                if ((inicio[i][0] - 'a') < (fim[i][0] - 'a')){
                    for (int a = 0; a < tamanho[indice[l]]; a++)
                        matriz[(inicio[i][0] - 'a') + a][(inicio[i][1] - 'a') + a][1] = 'v';
                    l++;
                }
                else {
                    for (int a = tamanho[indice[l]] - 1; a >= 0; a--)
                        matriz[(fim[i][0] - 'a') + a][(fim[i][1] - 'a') + a][1] = 'v';
                    l++;
                }
            }
            acabou++;
        }
    }

    int horizontal, funciona;
    for (int k = 0; k < vetor[2]; k++){
        horizontal = 0;
        l = 0; funciona = 0;
        if (inicio[k][0] == '-'){
            for (int i = 0; i < vetor[0]; i++){
                for (int j = 0; j < vetor[1]; j++){
                    if (matriz[i][j][0] == toupper(palavras[k][l])){ //percorrendo horizontal
                        funciona = 1;
                        if (j <= vetor[1] - tamanho[k]){
                            for (int n = j + 1; n < tamanho[k] + j; n++){
                                l++; 
                                if (matriz[i][n][0] == toupper(palavras[k][l])){
                                    funciona++;
                                    if (funciona == tamanho[k]){
                                        inicio[k][0] = i + 'a';
                                        inicio[k][1] = j + 'a';
                                        horizontal = 1;
                                    }
                                }
                                else {
                                    funciona = 0; l = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else if (matriz[i][j][0] == toupper(palavras[k][(tamanho[k] - 1) - l])){ //percorrendo horizontal
                        funciona = 1;
                        if (j <= vetor[1] - tamanho[k]){
                            for (int n = j + 1; n < tamanho[k] + j; n++){
                                l++; 
                                if (matriz[i][n][0] == toupper(palavras[k][(tamanho[k] - 1) - l])){
                                    funciona++;
                                    if (funciona == tamanho[k]){
                                        fim[k][0] = i + 'a';
                                        fim[k][1] = j + 'a';
                                        horizontal = 2;
                                    }
                                }
                                else {
                                    funciona = 0; l = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else {
                        l = 0; funciona = 0;
                    }

                }
            }
            if (horizontal == 1){
                fim[k][0] = inicio[k][0];
                fim[k][1] = inicio[k][1] + (tamanho[k] - 1); 
            }
            else if (horizontal == 2) {
                inicio[k][0] = fim[k][0];
                inicio[k][1] = fim[k][1] + (tamanho[k] - 1);
            }
        }
    }

    int vertical;
    for (int k = 0; k < vetor[2]; k++){
        vertical = 0;
        l = 0; funciona = 0;
        if (inicio[k][0] == '-'){
            for (int i = 0; i < vetor[1]; i++){
                for (int j = 0; j < vetor[0]; j++){
                    if (matriz[j][i][0] == toupper(palavras[k][l])){ //percorrendo vertical
                        funciona = 1;
                        if (j <= vetor[0] - tamanho[k]){
                            for (int n = j + 1; n < tamanho[k] + j; n++){
                                l++; 
                                if (matriz[n][i][0] == toupper(palavras[k][l])){
                                    funciona++;
                                    if (funciona == tamanho[k]){
                                        inicio[k][0] = i + 'a';
                                        inicio[k][1] = j + 'a';
                                        vertical = 1;
                                    }
                                }
                                else {
                                    funciona = 0; l = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else if (matriz[j][i][0] == toupper(palavras[k][(tamanho[k] - 1) - l])){
                        funciona = 1;
                        if (j <= vetor[0] - tamanho[k]){
                            for (int n = j + 1; n < tamanho[k] + j; n++){
                                l++; 
                                if (matriz[n][i][0] == toupper(palavras[k][(tamanho[k] - 1) - l])){
                                    funciona++;
                                    if (funciona == tamanho[k]){
                                        fim[k][0] = i + 'a';
                                        fim[k][1] = j + 'a';
                                        vertical = 2;
                                    }
                                }
                                else {
                                    funciona = 0; l = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else {
                        l = 0; funciona = 0;
                    }

                }
            }
            if (vertical == 1){
                fim[k][0] = inicio[k][1] + (tamanho[k] - 1);
                fim[k][1] = inicio[k][0];
            }
            else if (vertical == 2){
                inicio[k][0] = fim[k][1] + (tamanho[k] - 1);
                inicio[k][1] = fim[k][0];
            }
        }
    }

    int diagonal;
    for (int k = 0; k < vetor[2]; k++){
        diagonal = 0;
        l = 0; funciona = 0;
        if (inicio[k][0] == '-'){
            for (int i = 0; i < vetor[0]; i++){
                for (int j = 0; j < vetor[1]; j++){
                    if (matriz[i][j][0] == toupper(palavras[k][l])){ //percorrendo diagonal
                        funciona = 1;
                        for (int n = 1; n < tamanho[k]; n++){
                            l++; 
                            if (i <= vetor[0] - tamanho[k] && j <= vetor[1] - tamanho[k]){
                                if (matriz[i + n][j + n][0] == toupper(palavras[k][l])){
                                    funciona++;
                                    if (funciona == tamanho[k]){
                                        inicio[k][0] = i + 'a';
                                        inicio[k][1] = j + 'a';
                                        diagonal = 1;
                                    }
                                }
                                else {
                                    funciona = 0; l = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else if (matriz[i][j][0] == toupper(palavras[k][(tamanho[k] - 1) - l])){
                        funciona = 1;
                        for (int n = 1; n < tamanho[k]; n++){
                            l++; 
                            if (i <= vetor[0] - tamanho[k] && j <= vetor[1] - tamanho[k]){
                                if (matriz[i + n][j + n][0] == toupper(palavras[k][(tamanho[k] - 1) - l])){
                                    funciona++;
                                    if (funciona == tamanho[k]){
                                        fim[k][0] = i + 'a';
                                        fim[k][1] = j + 'a';
                                        diagonal = 2;
                                    }
                                }
                                else {
                                    funciona = 0; l = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else {
                        l = 0; funciona = 0;
                    }

                }
            }
            if (diagonal == 1){
                fim[k][0] = inicio[k][0] + (tamanho[k] - 1);
                fim[k][1] = inicio[k][1] + (tamanho[k] - 1);
            }
            else if (diagonal == 2){
                inicio[k][0] = fim[k][0] + (tamanho[k] - 1);
                inicio[k][1] = fim[k][1] + (tamanho[k] - 1);
            }
        }
    }

    for(int i = 0; i < vetor[2]; i++){
        posicao_inicio[i][0] = inicio[i][0] - 'a';
        posicao_inicio[i][1] = inicio[i][1] - 'a';
        posicao_fim[i][0] = fim[i][0] - 'a';
        posicao_fim[i][1] = fim[i][1] - 'a';
    }

    imprime_matriz(matriz, vetor);

    do {
        
        acabou = jogadas (acabou, posicao_inicio, posicao_fim, vetor, &matriz, palavras, tamanho);
        
        imprime_matriz(matriz, vetor);

    } while (acabou != vetor[2]);

    desaloca_matriz(posicao_fim, vetor[2]);
    desaloca_matriz(posicao_inicio, vetor[2]);
    desaloca_matriz_char(fim, vetor[2]);
    desaloca_matriz_char(inicio, vetor[2]);
    free(tamanho);
    desaloca_matriz_char(palavras, vetor[2]);
    desaloca_matriz_3(matriz, vetor[0], vetor[1]);
    fclose(arquivo);
    printf("Obrigada por jogar e volte sempre!\n");
}

int escolha3 (){
    printf("Para jogar, deve-se fornecer quais palavras o jogo usara (o nome do arquivo + .txt). A partir dai,\nsera mostrado o caca palavras e todas as palavras que estao escondidas nele estarao na tela. Para informar a\nposicao de uma palavra, eh necessario digitar 'marcar' e informar em qual posicao ela comeca e qual posicao\nela termina. Exemplo: marcar A2 A8 ('A' corresponde a linha e '2' e '8' correspondem a coluna).\n\n");
    printf("Se a palavra estiver correta, ela sera destacada de vermelho, ja se nao estiver correta, nada ocorrera no tabuleiro.\nCaso contrario, nao ocorrera nada com o jogo e voce deve digitar a posicao de outra palavra.\n\n");
    printf("Se quiser sair do jogo e salva-lo, digite 'salvar' + 'nomedoarquivo.txt'. (Exemplo: salvar teste.txt)\nCaso queira que todas as palavras sejam destacadas, digite 'resolver', mas isso ira finalizar o jogo \nsem salvar alteracoes. Se seu desejo for abandonar o jogo sem salva-lo, digite 'sair'. Todos esses comandos \nfuncionam a qualquer momento.\n\n");
    return 1;
}

int main (){
    int escolha = 0, funciona;
    do {
        funciona = 0;
        printf("Vamos jogar caca palavras!\n\n");
        printf("O que deseja fazer? (digite apenas o numero da escolha)\n");
        printf("1- comecar um novo jogo;\n");
        printf("2- continuar um jogo existente;\n");
        printf("3- ver as instrucoes.\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                escolha1();
                break;
            case 2:
                escolha2();
                break;
            case 3: 
                funciona = escolha3();
                break;
            default: 
                printf("Opcao invalida. Favor digitar apenas o numero de sua escolha.\n");
                funciona = 1;

        }
    } while (funciona != 0);
    return 0;
}