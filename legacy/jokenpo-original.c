#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void){
int escolhajogador, escolhaCPU;
char continuar;
srand(time(0));
do {
printf("Bemvindo ao Jokenpo!\nEscolha uma das opcoes abaixo:\n1 - Pedra\n2 - Papel\n3 - Tesoura\n");
printf("Digite sua escolha: ");
scanf("%d", &escolhajogador); escolhaCPU = (rand() % 3) + 1;

/* Aqui a escolha do jogador*/
    switch (escolhajogador){
        case 1:
            printf("Voce escolheu Pedra!\n");
            break;
        case 2:
            printf("Voce escolheu Papel!\n");
            break;
        case 3:
            printf("Voce escolheu Tesoura!\n");
            break;
        default:
            printf("Escolha invalida! Tente novamente.\n");}
            /* Aqui a escolha da CPU */
        switch (escolhaCPU){
        case 1:
            printf("A CPU escolheu Pedra!\n");
            break;
        case 2:
            printf("A CPU escolheu Papel!\n");
            break;
        case 3:
            printf("A CPU escolheu Tesoura!\n");
            break;}
        
    /* Aqui a verificação de quem ganhou */
            if (escolhaCPU == escolhajogador){
            printf("O Jogo EMPATOU!!!\n");

            }else if ((escolhajogador == 1 && escolhaCPU == 3) || (escolhajogador == 2 && escolhaCPU == 1) || (escolhajogador == 3 && escolhaCPU == 2)){
            printf("#### VOCE VENCEU!!! ##### \n");
            }else {printf("#### A CPU VENCEU!!! ##### \n");}
            printf("Deseja jogar novamente? (s/n): ");
            scanf(" %c", &continuar);
        } while (continuar == 's' || continuar == 'S');
        printf("Obrigado por jogar Jokenpo! Ate a proxima!\n");
        return 0;
        }    
