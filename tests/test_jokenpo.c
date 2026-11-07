#include <assert.h>

#define JOKENPO_TEST
#include "../src/jokenpo.c"

int main(void)
{
    assert(avaliar_jogada(1, 1) == EMPATE);
    assert(avaliar_jogada(1, 2) == VITORIA_CPU);
    assert(avaliar_jogada(1, 3) == VITORIA_JOGADOR);
    assert(avaliar_jogada(2, 1) == VITORIA_JOGADOR);
    assert(avaliar_jogada(2, 2) == EMPATE);
    assert(avaliar_jogada(2, 3) == VITORIA_CPU);
    assert(avaliar_jogada(3, 1) == VITORIA_CPU);
    assert(avaliar_jogada(3, 2) == VITORIA_JOGADOR);
    assert(avaliar_jogada(3, 3) == EMPATE);
    assert(avaliar_jogada(0, 1) == RESULTADO_INVALIDO);
    assert(avaliar_jogada(1, 4) == RESULTADO_INVALIDO);
    return 0;
}
