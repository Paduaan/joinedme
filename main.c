/*
*ARRUMAR
*FUNCAO lerTurma if(esc == 2) LOOP INFINITO
*FUNCAO imprimirTurma FORMATACAO DE TEXTO E PUTS
*FUNCAO cadasEstudante LOOP INFINITO AO COLOCAR MATRICULA
*FUNCAO editaEstudante LOOP INFINITO AO LER NOME PARA VALIDACAO
*FUNCAO editaEstudante PROGRAMA PARA DE RODAR AO LER NOME PARA ALTERACAO
*FUNCAO relerTurma E PRA LER A STRUCT OU O ARQUIVO?
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Estudante {
    char nome[51];
    char matricula[12];
    int nota1;
    int nota2;
    int nota3;
    int notatrab1;
    int notatrab2;
    int faltas;
    int notafin;
    char sitfinal;
};

int leiaDados() {
    int esc = 0;
    scanf("%d", &esc);
    while (esc < 0) {
        printf("Digite uma opcao valida: ");
        scanf("%d\n", &esc);
    }
    return esc;
}

void lerTurma(char filename[], struct Estudante est[]) {
    char op;
    FILE *fp;
    int esc = 0;
    char arquivo[50];
    while (esc <= 3) {
        printf("\n=========================================\n"
               "Ler Turma\n"
               "=========================================\n\n"
               "Opcoes:\n\n"
               "1 - Ler turma existente\n"
               "2 - Criar nova turma\n"
               "3 - Voltar ao menu principal\n\n");
        do {
            printf("Digite uma opcao: ");
            esc = leiaDados();
        } while (esc > 3);
        int i = 0;
        switch (esc) {
            case 1:
                printf("Digite o nome do arquivo com a turma: ");
                scanf("%s", arquivo);
                fp = fopen(arquivo, "r");
                if (fp == NULL) {//Se o arquivo nao existir;
                    printf("\n\nArquivo turma1.txt nao existe!\n");
                    return;
                } else {//Se existir armazena na struct;
                    printf("\n\nArquivo turma1.txt lido com sucesso!\n");
                    while (!feof(fp)) {
                        fscanf(fp, "%[^\n]%*c", est[i].nome);
                        fscanf(fp, "%s\n", est[i].matricula);
                        fscanf(fp, "%d\n", &est[i].nota1);
                        fscanf(fp, "%d\n", &est[i].nota2);
                        fscanf(fp, "%d\n", &est[i].nota3);
                        fscanf(fp, "%d\n", &est[i].notatrab1);
                        fscanf(fp, "%d\n", &est[i].notatrab2);
                        fscanf(fp, "%d\n", &est[i].faltas);
                        fscanf(fp, "%d\n", &est[i].notafin);
                        fscanf(fp, "%c\n", &est[i].sitfinal);
                        i++;
                    }
                    strcpy(filename, arquivo);
                }
                fclose(fp);
                break;
            case 2:
                printf("Digite o nome do arquivo para a nova turma: ");
                scanf("%s", arquivo);
                fp = fopen(arquivo, "r");
                if (fp == NULL) {
                    printf("\n\nArquivo turma2.txt criado com sucesso.\n");
                    fp = fopen(arquivo, "w");
                    strcpy(filename, arquivo);
                } else {
                    printf("\n\nArquivo turma2.txt ja existe. Deseja sobrescreve-lo? (S/N)\n");
                    getchar();
                    scanf("%c", &op);
                    if (op == 'S' || op == 's') {
                        fp = fopen(arquivo, "w"); // PRECISA ABRIR PRA MODIFICAR O ARQUIVO? OU SO ISSO
                    } else {
                        return; // LOOP INFINITO NO MENU QUE QUER ABRIR
                    }
                }
                //fclose(fp);
                break;
            case 3:
                return;
        }
    }
}

void imprimirTurma(char filename[], struct Estudante est[]) {
    int i = 0;
    if (filename[0] == '\0') {
        printf("\nNao ha turma carregada!\n\n");
    } else {
        printf("----------------------------------------------------------------------------------------------------------\n");
        printf("                                              Turma de Estudantes\n");
        printf("----------------------------------------------------------------------------------------------------------\n");
        printf("Nome           |  Matricula  | Nota 1 | Nota 2 | Nota 3 | Trab 1 | Trab 2 | Faltas | Nota Final | Situacao\n");
        for (i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
            printf("%d - %s  ", i, est[i].nome);
            printf("%s  ", est[i].matricula);
            printf("\t");
            printf("%d\t", est[i].nota1);
            printf("%d\t", est[i].nota2);
            printf("%d\t", est[i].nota3);
            printf("%d\t", est[i].notatrab1);
            printf("%d\t", est[i].notatrab2);
            printf("%d\t", est[i].faltas);
            printf("%d\t", est[i].notafin);
            printf("%c\n", est[i].sitfinal);
        }
    }
    return;
}

void estatisTurma(char filename[], struct Estudante est[]) {
    int maiorprova1 = 0, menorprova1 = 99, maiortrab1 = 0, menortrab1 = 99, i;
    int maiorprova2 = 0, menorprova2 = 99, maiortrab2 = 0, menortrab2 = 99;
    int maiorprova3 = 0, menorprova3 = 99, finalmaior = 0, finalmenor = 99;
    float median1 = 0.0, median2 = 0.0, median3 = 0.0, mediat1 = 0.0, mediat2 = 0.0, finalmedia = 0.0;
    int a = 0, r = 0, rf = 0, qtAl = 0;
    float pa, pr, prf;
    if (filename[1] == '\0') {
        printf("\nNao ha turma carregada!\n\n");
    } else {
        for (i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
            if (est[i].nota1 > maiorprova1) {//comparacao maior prova 1
                maiorprova1 = est[i].nota1;
            }
            if (est[i].nota1 < menorprova1) {//comparacao menor prova 1
                menorprova1 = est[i].nota1;
            }
            if (est[i].nota2 > maiorprova2) {//comparacao maior prova 2
                maiorprova2 = est[i].nota2;
            }
            if (est[i].nota2 < menorprova2) {//comparacao menor prova 2
                menorprova2 = est[i].nota2;
            }
            if (est[i].nota3 > maiorprova3) {//comparacao maior prova 3
                maiorprova3 = est[i].nota3;
            }
            if (est[i].nota3 < menorprova3) {//comparacao menor prova 3
                menorprova3 = est[i].nota3;
            }
            if (est[i].notatrab1 > maiortrab1) {//comparacao maior trabalho 1
                maiortrab1 = est[i].notatrab1;
            }
            if (est[i].notatrab1 < menortrab1) {//comparacao menor trabalho 1
                menortrab1 = est[i].notatrab1;
            }
            if (est[i].notatrab2 > maiortrab2) {//comparacao maior trabalho 1
                maiortrab2 = est[i].notatrab2;
            }
            if (est[i].notatrab2 < menortrab2) {//comparacao menor trabalho 1
                menortrab2 = est[i].notatrab2;
            }
        }
        finalmaior = maiorprova1 + maiorprova2 + maiorprova3 + maiortrab1 + maiortrab2;//soma maiores notas
        finalmenor = menorprova1 + menorprova2 + menorprova3 + menortrab1 + menortrab2;//soma menores notas

        for (i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
            median1 += est[i].nota1;
            median2 += est[i].nota2;
            median3 += est[i].nota3;
            mediat1 += est[i].notatrab1;
            mediat2 += est[i].notatrab2;
            qtAl++;
        }
        median1 = median1 / qtAl;
        median2 = median2 / qtAl;
        median3 = median3 / qtAl;
        mediat1 = mediat1 / qtAl;
        mediat2 = mediat2 / qtAl;
        finalmedia = median1 + median2 + median3 + mediat1 + mediat2;

        for (i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
            if (est[i].sitfinal == 'a' || est[i].sitfinal == 'A') {
                a++;
            } else if (est[i].sitfinal == 'r' || est[i].sitfinal == 'R') {
                r++;
            } else if (est[i].sitfinal == 'f' || est[i].sitfinal == 'F') {
                rf++;
            }
        }
        pa = ((double) a / (double) qtAl) * 100;
        pr = ((double) r / (double) qtAl) * 100;
        prf = ((double) rf / (double) qtAl) * 100;

        printf("\n                       Estatisticas\n---------------------------------------------------------\n");
        printf("                         N1   N2   N3   T1   T2  FINAL\n");
        printf("---------------------------------------------------------\n");
        printf("Maiores notas da turma: %*d  %*d  %*d  %*d  %*d  %*d\n",
               3, maiorprova1, 3, maiorprova2, 3, maiorprova3, 3, maiortrab1, 3, maiortrab2, 3, finalmaior);
        printf("Menores notas da turma: %*d  %*d  %*d  %*d  %*d  %*d\n",
               3, menorprova1, 3, menorprova2, 3, menorprova3, 3, menortrab1, 3, menortrab2, 3, finalmenor);
        printf("Notas medias da turma:  %*.1f  %*.1f  %*.1f  %*.1f  %*.1f  %*.1f\n",
               1, median1, 1, median2, 1, median3, 1, mediat1, 1, mediat2, 1, finalmedia);
        printf("---------------------------------------------------------\n\n");
        printf("Numero de estudantes aprovados:            %*d (%.1f)\n", 2, a, pa);
        printf("Numero de estudantes reprovados:           %*d (%.1f)\n", 2, r, pr);
        printf("Numero de estudantes reprovados por falta: %*d (%.1f)\n", 2, rf, prf);
        printf("---------------------------------------------------------\n\n");
    }
    return;
}

void cadasEstudante(char filename[], struct Estudante est[]) {
    int i = 0, quantAlunos = 0;
    if (filename[0] == '\0') {
        printf("\nNao ha turma carregada!\n\n");
    } else {
        for (i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
            quantAlunos++;
        }
        printf("=========================================\n"
               "Cadastrar Novo Estudante\n"
               "=========================================\n\n");
        printf("Digite o nome: ");
        getchar();
        scanf("%[^\n]%*c", est[quantAlunos].nome);
        printf("Digite a matricula: ");
        scanf("%s", est[quantAlunos].matricula);
        printf("Digite as tres notas da prova: ");
        scanf("%d %d %d", &est[quantAlunos].nota1, &est[quantAlunos].nota2, &est[quantAlunos].nota3);
        printf("Digite as notas dos trabalhos: ");
        scanf("%d %d", &est[quantAlunos].notatrab1, &est[quantAlunos].notatrab2);
        printf("Digite o numero de faltas: ");
        scanf("%d", &est[quantAlunos].faltas);

        est[quantAlunos].notafin =
                est[quantAlunos].nota1 + est[quantAlunos].nota2 + est[quantAlunos].nota3 + est[quantAlunos].notatrab1 +
                est[quantAlunos].notatrab2;
        printf("\nNota final calculada: %d", est[quantAlunos].notafin);

        if (est[quantAlunos].faltas > 18) {
            est[quantAlunos].sitfinal = 'F';
            printf("\nSituacao final: Reprovado por faltas\n\n");
        } else if (est[quantAlunos].notafin < 60) {
            est[quantAlunos].sitfinal = 'R';
            printf("\nSituacao final: Reprovado\n\n");
        } else if (est[quantAlunos].notafin >= 60 && est[quantAlunos].faltas <= 18) {
            est[quantAlunos].sitfinal = 'A';
            printf("\nSituacao final: Aprovado\n\n");
        }
    };
    return;
}

char *alteraNomeEst() {
    char *novoNome = malloc(50);
    printf("\nDigite o nome: ");
    getchar();
    scanf("%[^\n]%*c", novoNome);
    return novoNome;
}

char *alteraMatriEst() {
    char *novaMatri = malloc(12);
    printf("\nDigite a matricula: ");
    scanf("%s", novaMatri);
    return novaMatri;
}

int alteraNota1Est() {
    int novaNota1;
    printf("Digite a nota da prova 1: ");
    scanf("%d", &novaNota1);
    return novaNota1;
}

int alteraNota2Est() {
    int novaNota2;
    printf("Digite a nota da prova 2: ");
    scanf("%d", &novaNota2);
    return novaNota2;
}

int alteraNota3Est() {
    int novaNota3;
    printf("Digite a nota da prova 3: ");
    scanf("%d", &novaNota3);
    return novaNota3;
}

int alteraNotaT1Est() {
    int novaNotaT1;
    printf("Digite a nota do trabalho 1: ");
    scanf("%d", &novaNotaT1);
    return novaNotaT1;
}

int alteraNotaT2Est() {
    int novaNotaT2;
    printf("Digite a nota do trabalho 2: ");
    scanf("%d", &novaNotaT2);
    return novaNotaT2;
}

int alteraFaltasEst() {
    int novaFaltas;
    printf("Digite o numero de faltas: ");
    scanf("%d", &novaFaltas);
    return novaFaltas;
}

void editaEstudante(char filename[], struct Estudante est[]) {
    int esc = 0, i = 0;
    char verifMatricula[12];
    char verifNome[50];
    if (filename[0] == '\0') {
        printf("\nNao ha turma carregada!\n\n");
        return;
    }
    while (esc <= 3) {
        printf("\n=========================================\n"
               "Editar Informacoes do Estudante\n"
               "=========================================\n"
               "Opcoes:\n"
               "1 - Selecionar por numero de matricula\n"
               "2 - Selecionar por nome\n"
               "3 - Voltar ao menu principal\n\n"
               "Digite uma opcao: ");
        esc = leiaDados();
        if (esc == 1) {
            printf("\nDigite o numero de matricula: ");
            scanf("%s", verifMatricula);
            for (i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
                if (strcmp(verifMatricula, est[i].matricula) == 0) {
                    printf("Encontrado %s", est[i].nome);
                    while (esc <= 9) {
                        printf("\n=========================================\n"
                               "Editar Informacoes do Estudante\n"
                               "=========================================\n"
                               "Opcoes:\n"
                               "1 - Alterar nome\n"
                               "2 - Alterar matricula\n"
                               "3 - Alterar nota da prova 1\n"
                               "4 - Alterar nota da prova 2\n"
                               "5 - Alterar nota da prova 3\n"
                               "6 - Alterar nota do trabalho 1\n"
                               "7 - Alterar nota do trabalho 2\n"
                               "8 - Alterar numero de faltas\n"
                               "9 - Voltar ao menu anterior\n\n"
                               "Digite uma opcao: ");
                        esc = leiaDados();
                        if (esc == 1) {
                            char nome[50];
                            strcpy(nome, alteraNomeEst());
                            printf("Nome escolhido: \"%s\"", nome);
                            strcpy(est[i].nome, nome);
                        }
                        if (esc == 2) {
                            strcpy(est[i].matricula, alteraMatriEst());
                        }
                        if (esc == 3) {
                            est[i].nota1 = alteraNota1Est();;
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 4) {
                            est[i].nota2 = alteraNota2Est();;
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 5) {
                            est[i].nota3 = alteraNota3Est();;
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 6) {
                            est[i].notatrab1 = alteraNotaT1Est();
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 7) {
                            est[i].notatrab2 = alteraNotaT2Est();
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 8) {
                            est[i].faltas = alteraFaltasEst();
                            if (est[i].faltas <= 18) {
                                est[i].sitfinal = 'A';
                            } else {
                                est[i].sitfinal = 'F';
                            }
                        }
                        if (esc == 9) {
                            return;
                        }

                        while (esc > 9) {
                            printf("Digite uma opcao valida: ");
                            esc = leiaDados();
                        }
                    }
                }
            }
        }

        if (esc == 2) {
            printf("\nDigite o nome: ");
            getchar();
            scanf("%[^\n]%*c", verifNome);
            for (i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
                if (strcmp(verifNome, est[i].nome) == 0) {
                    while (esc <= 9) {
                        printf("\n=========================================\n"
                               "Editar Informacoes do Estudante\n"
                               "=========================================\n"
                               "Opcoes:\n"
                               "1 - Alterar nome\n"
                               "2 - Alterar matricula\n"
                               "3 - Alterar nota da prova 1\n"
                               "4 - Alterar nota da prova 2\n"
                               "5 - Alterar nota da prova 3\n"
                               "6 - Alterar nota do trabalho 1\n"
                               "7 - Alterar nota do trabalho 2\n"
                               "8 - Alterar numero de faltas\n"
                               "9 - Voltar ao menu anterior\n\n"
                               "Digite uma opcao: ");
                        esc = leiaDados();

                        if (esc == 1) {
                            strcpy(est[i].nome, alteraNomeEst());
                        }
                        if (esc == 2) {
                            strcpy(est[i].matricula, alteraMatriEst());
                        }
                        if (esc == 3) {
                            est[i].nota1 = alteraNota1Est();;
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 4) {
                            est[i].nota2 = alteraNota2Est();;
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 5) {
                            est[i].nota3 = alteraNota3Est();;
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 6) {
                            est[i].notatrab1 = alteraNotaT1Est();
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 7) {
                            est[i].notatrab2 = alteraNotaT2Est();
                            est[i].notafin =
                                    est[i].nota1 + est[i].nota2 + est[i].nota3 + est[i].notatrab1 + est[i].notatrab2;
                            if (est[i].notafin < 60) {
                                est[i].sitfinal = 'R';
                            } else {
                                est[i].sitfinal = 'A';
                            }
                        }
                        if (esc == 8) {
                            est[i].faltas = alteraFaltasEst();
                            if (est[i].faltas <= 18) {
                                est[i].sitfinal = 'A';
                            } else {
                                est[i].sitfinal = 'F';
                            }
                        }
                        if (esc == 9) {
                            return;
                        }

                        while (esc > 9) {
                            printf("Digite uma opcao valida: ");
                            esc = leiaDados();
                        }
                    }
                }
            }
        }
        if (esc == 3) {
            return;
        }

        while (esc > 3) {
            printf("Digite uma opcao valida: ");
            esc = leiaDados();
        }
    }
    return;
}

void relerTurma(char filename[], struct Estudante est[]) {
    FILE *fp = fopen(filename, "r");
    int i = 0;
    if (filename[0] == '\0') {
        printf("\nArquivo turma1.txt nao existe!\n\n");
        return;
    }
    printf("\nArquivo turma1.txt lido com sucesso!\n\n");
    while (!feof(fp)) {
        fscanf(fp, "%[^\n]%*c", est[i].nome);
        fscanf(fp, "%s\n", est[i].matricula);
        fscanf(fp, "%d\n", &est[i].nota1);
        fscanf(fp, "%d\n", &est[i].nota2);
        fscanf(fp, "%d\n", &est[i].nota3);
        fscanf(fp, "%d\n", &est[i].notatrab1);
        fscanf(fp, "%d\n", &est[i].notatrab2);
        fscanf(fp, "%d\n", &est[i].faltas);
        fscanf(fp, "%d\n", &est[i].notafin);
        fscanf(fp, "%c\n", &est[i].sitfinal);
        i++;
    }
    est[i].nome[0] = '\0';
    fclose(fp);
    return;
}

void salvarSair(char filename[], struct Estudante est[]) {
    char esc;
    FILE *fp;
    fp = fopen(filename, "r");
    if (filename[0] == '\0') {
        printf("Não ha turma carregada!");
        return;
    }
    if (fp == NULL) {
        printf("O arquivo turma1.txt nao existe. Deseja criar um novo? (S/n)");
        getchar();
        scanf("%c", &esc);
        if (esc == 'N' || esc == 'n') {
            printf("Ate a proxima.");
            return;
        }
    } else {
        printf("O arquivo turma1.txt ja existe. Deseja sobrescreve-lo? (S/n)");
        getchar();
        scanf("%c", &esc);
        if (esc == 'N' || esc == 'n') {
            printf("Ate a proxima.");
            return;
        }
    }
    fp = fopen(filename, "w");
    for (int i = 0; i < 80 && est[i].nome[0] != '\0'; i++) {
        fprintf(fp, "%s\n", est[i].nome);
        fprintf(fp, "%s\n", est[i].matricula);
        fprintf(fp, "%d\n", est[i].nota1);
        fprintf(fp, "%d\n", est[i].nota2);
        fprintf(fp, "%d\n", est[i].nota3);
        fprintf(fp, "%d\n", est[i].notatrab1);
        fprintf(fp, "%d\n", est[i].notatrab2);
        fprintf(fp, "%d\n", est[i].faltas);
        fprintf(fp, "%d\n", est[i].notafin);
        fprintf(fp, "%c\n", est[i].sitfinal);
    }
    fclose(fp);
    printf("Ate a proxima.");
}

void menuPrincipal(char filename[], struct Estudante est[]) {
    int esc = 0;
    while (esc <= 7) {
        printf("=========================================\n"
               "Menu Principal\n"
               "=========================================\n\n"
               "Opcoes:\n\n"
               "1 - Ler turma de estudantes do arquivo\n"
               "2 - Imprimir turma de estudantes\n"
               "3 - Imprimir estatisticas da turma\n"
               "4 - Cadastrar novo estudante\n"
               "5 - Editar informacoes de um estudante\n"
               "6 - Reler turma de estudantes do arquivo\n"
               "7 - Salvar e Sair\n\n");
        do {
            printf("Digite uma opcao: ");
            esc = leiaDados();
        } while (esc > 7);
        switch (esc) {
            case 1:
                lerTurma(filename, est);
                break;
            case 2:
                imprimirTurma(filename, est);
                break;
            case 3:
                estatisTurma(filename, est);
                break;
            case 4:
                cadasEstudante(filename, est);
                break;
            case 5:
                editaEstudante(filename, est);
                break;
            case 6:
                relerTurma(filename, est);
                break;
            case 7:
                salvarSair(filename, est);
                return;
        }
    }
}

int main() {
    struct Estudante est[80];
    char filename[50] = "";
    menuPrincipal(filename, est);
    return 0;
}