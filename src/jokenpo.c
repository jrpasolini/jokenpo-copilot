#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_LINHA 128

enum Resultado {
    RESULTADO_INVALIDO = -1,
    EMPATE = 0,
    VITORIA_JOGADOR = 1,
    VITORIA_CPU = 2
};

int avaliar_jogada(int jogador, int cpu)
{
    if (jogador < 1 || jogador > 3 || cpu < 1 || cpu > 3) {
        return RESULTADO_INVALIDO;
    }

    if (jogador == cpu) {
        return EMPATE;
    }

    if ((jogador == 1 && cpu == 3) ||
        (jogador == 2 && cpu == 1) ||
        (jogador == 3 && cpu == 2)) {
        return VITORIA_JOGADOR;
    }

    return VITORIA_CPU;
}

const char *nome_jogada(int jogada)
{
    switch (jogada) {
    case 1:
        return "Pedra";
    case 2:
        return "Papel";
    case 3:
        return "Tesoura";
    default:
        return "Inválida";
    }
}

#ifndef JOKENPO_TEST
static void descartar_resto_linha(char *linha)
{
    size_t tamanho = 0;

    while (linha[tamanho] != '\0') {
        ++tamanho;
    }

    if (tamanho > 0 && linha[tamanho - 1] != '\n') {
        int caractere;

        do {
            caractere = getchar();
        } while (caractere != '\n' && caractere != EOF);
    }
}

static int converter_inteiro(const char *texto, int *valor)
{
    char *fim;
    long numero;

    errno = 0;
    numero = strtol(texto, &fim, 10);
    if (texto == fim || errno == ERANGE || numero < INT_MIN || numero > INT_MAX) {
        return 0;
    }

    while (*fim == ' ' || *fim == '\t' || *fim == '\r' || *fim == '\n') {
        ++fim;
    }

    if (*fim != '\0') {
        return 0;
    }

    *valor = (int)numero;
    return 1;
}

static int ler_escolha(int *escolha)
{
    char linha[TAMANHO_LINHA];

    if (fgets(linha, sizeof linha, stdin) == NULL) {
        return 0;
    }

    if (linha[0] == '\0' ||
        (strchr(linha, '\n') == NULL && strlen(linha) == sizeof linha - 1)) {
        descartar_resto_linha(linha);
        return -1;
    }

    if (!converter_inteiro(linha, escolha) || *escolha < 1 || *escolha > 3) {
        return -1;
    }

    return 1;
}

static int ler_continuacao(void)
{
    char linha[TAMANHO_LINHA];
    char resposta;
    char *resto;

    for (;;) {
        if (fgets(linha, sizeof linha, stdin) == NULL) {
            return -1;
        }

        if (linha[0] == '\0' ||
            (strchr(linha, '\n') == NULL && strlen(linha) == sizeof linha - 1)) {
            descartar_resto_linha(linha);
            printf("Resposta inválida. Digite s ou n: ");
            continue;
        }

        resposta = linha[0];
        resto = linha + 1;
        while (*resto == ' ' || *resto == '\t' || *resto == '\r' || *resto == '\n') {
            ++resto;
        }

        if (*resto != '\0' || (resposta != 's' && resposta != 'S' &&
                               resposta != 'n' && resposta != 'N')) {
            printf("Resposta inválida. Digite s ou n: ");
            continue;
        }

        return resposta == 's' || resposta == 'S';
    }
}

int main(void)
{
    int escolha_jogador;
    int escolha_cpu;
    int resultado;
    int leitura;
    unsigned int vitorias = 0;
    unsigned int derrotas = 0;
    unsigned int empates = 0;
    int continuar = 1;

    srand((unsigned int)time(NULL));
    printf("Bem-vindo ao Jokenpo!\n");

    while (continuar > 0) {
        printf("\nEscolha uma opção:\n"
               "1 - Pedra\n"
               "2 - Papel\n"
               "3 - Tesoura\n"
               "Digite sua escolha: ");

        leitura = ler_escolha(&escolha_jogador);
        if (leitura == 0) {
            printf("\nEntrada encerrada.\n");
            break;
        }
        if (leitura < 0) {
            printf("Escolha inválida. Digite um número de 1 a 3.\n");
            continue;
        }

        escolha_cpu = (rand() % 3) + 1;
        printf("Você escolheu %s!\n", nome_jogada(escolha_jogador));
        printf("A CPU escolheu %s!\n", nome_jogada(escolha_cpu));

        resultado = avaliar_jogada(escolha_jogador, escolha_cpu);
        if (resultado == EMPATE) {
            ++empates;
            printf("O jogo empatou!\n");
        } else if (resultado == VITORIA_JOGADOR) {
            ++vitorias;
            printf("Você venceu!\n");
        } else {
            ++derrotas;
            printf("A CPU venceu!\n");
        }

        printf("Placar: %u vitória(s), %u derrota(s), %u empate(s).\n",
               vitorias, derrotas, empates);
        printf("Deseja jogar novamente? (s/n): ");
        continuar = ler_continuacao();
        if (continuar < 0) {
            printf("\nEntrada encerrada.\n");
        }
    }

    printf("Obrigado por jogar Jokenpo! Até a próxima!\n");
    return 0;
}
#endif
