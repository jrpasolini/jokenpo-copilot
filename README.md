# Jokenpo em C

Aplicativo CLI de Jokenpo em C11, desenvolvido a partir de um código autoral
para a Global Hack Week Builders Week. A mecânica jogador contra CPU e os
textos em português do Brasil foram preservados e aprimorados.

O código original está preservado sem alterações em
[`legacy/jokenpo-original.c`](legacy/jokenpo-original.c). A implementação atual
está em [`src/jokenpo.c`](src/jokenpo.c).

## Compilação

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic src/jokenpo.c -o jokenpo
./jokenpo
```

Ou use o Makefile:

```sh
make
make test
```

O programa usa `fgets` e `strtol` para validar números de 1 a 3, rejeitar
letras, lixo após números, linhas longas e EOF. Rodadas inválidas não alteram
o placar. O gerador aleatório é inicializado uma única vez; não há
dependências externas, `system` ou limpeza de tela.

## Testes sugeridos

O teste das nove combinações jogador/CPU está em
[`tests/test_jokenpo.c`](tests/test_jokenpo.c): Pedra/Pedra, Pedra/Papel,
Pedra/Tesoura, Papel/Pedra, Papel/Papel, Papel/Tesoura, Tesoura/Pedra,
Tesoura/Papel e Tesoura/Tesoura. Também há testes de letras, valores fora de
1-3, lixo após números, linhas longas, EOF e respostas inválidas de replay em
[`tests/test_inputs.sh`](tests/test_inputs.sh).

## Assistência do Copilot

O GitHub Copilot foi usado como assistência de programação para estruturar a
validação de entrada, separar leitura e avaliação, criar os testes e preparar a
documentação. As decisões sobre escopo, preservação do código original e
validação final permanecem sob responsabilidade do autor. O código legado foi
fornecido pelo autor.
