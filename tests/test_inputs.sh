#!/bin/sh
set -eu

program="${1:-./build/jokenpo}"
long_line=$(awk 'BEGIN { for (i = 0; i < 200; i++) printf "x"; print "" }')

output=$(printf 'x\n4\n1x\n%s\n1\nn\n' "$long_line" | "$program")
printf '%s\n' "$output" | grep -q "Escolha inválida"
[ "$(printf '%s\n' "$output" | grep -c "Placar:")" -eq 1 ]
printf '%s\n' "$output" | grep -Eq \
    "Placar: (1 vitória\(s\), 0 derrota\(s\), 0 empate\(s\)|0 vitória\(s\), 1 derrota\(s\), 0 empate\(s\)|0 vitória\(s\), 0 derrota\(s\), 1 empate\(s\))"

eof_output=$(printf '1\n' | "$program")
if [ "$(printf '%s\n' "$eof_output" | grep -c "Placar:")" -eq 1 ] &&
   printf '%s\n' "$eof_output" | grep -q "Entrada encerrada."; then
    :
else
    printf '%s\n' "Falha: EOF após uma rodada não foi tratado." >&2
    exit 1
fi

replay_output=$(printf '1\nnextra\nn\n' | "$program")
if [ "$(printf '%s\n' "$replay_output" | grep -c "Placar:")" -eq 1 ] &&
   printf '%s\n' "$replay_output" | grep -q "Resposta inválida" &&
   ! printf '%s\n' "$replay_output" | grep -q "Entrada encerrada."; then
    :
else
    printf '%s\n' "Falha: resposta de replay inválida não foi tratada." >&2
    exit 1
fi
