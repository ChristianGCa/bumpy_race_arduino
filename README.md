# Bumpy Race

Bumpy Race é um jogo interativo utilizando o Arduino e um display LCD de duas linhas. Durante o jogo, o jogador controlará um carrinho que precisa desviar de obstáculos representado por buracos na pista utilizando um botão para enviar um sinal para o Arduino, permitindo que o carrinho exibido no display se mova para cima ou para baixo. Conforme o jogo avança, a velocidade do carrinho aumenta automaticamente, dificultando o controle do mesmo. A velocidade será exibida em forma de números de 1 a 9 em um display de 7 segmentos.

## Componentes

* Arduino UNO
* Display LCD 16x2, com módulo I2C soldado
* Display de 7 segmentos catodo comum
* CI CD4026BE (Decodificador para o display de 7 segmentos)
* Sete resistores de 1K Ohms
* Botão (Push button)
* Jumpers diversos
* Protoboard

## Caracteres especias do display

O display LCD possui 2 linhas com 16 espaços em cada uma para os caracteres aparecerem. Cada espaço desses possui 40 pontos ou pixels que podem ser acesos para formá-los. Uma vantagem é que pode-se criar caracteres personalizados, decidindo quais pixels devem acender. Foi utilizada uma ferramenta chamada “LCD Custom Character Generator” do site https://maxpromer.github.io/LCD-Character-Creator/ para isso.

## Esquema de montagem

<img alt="esquema" src="./imgs/esquema_bumpy_race.png">

## Fotos do projeto

<img alt="inicio" src="./pictures/picture1.png">
<img alt="meio" src="./pictures/picture2.png">
<img alt="fim" src="./pictures/picture3.png">

## Funcionamento do Jogo

O jogo utiliza um botão para alternar a posição do carrinho entre as duas linhas do display LCD. O objetivo é desviar dos buracos que aparecem aleatoriamente em ambas as linhas. A cada buraco desviado com sucesso, a velocidade do jogo aumenta, tornando o desafio mais difícil.

### Regras do Jogo

1. O carrinho começa na linha inferior do display.
2. Pressione o botão para alternar entre a linha superior e a linha inferior.
3. Buracos aparecem aleatoriamente e se movem da direita para a esquerda.
4. Se o carrinho colidir com um buraco, o jogo exibe "Game Over!" e reinicia automaticamente após um breve intervalo.
5. A cada 5 buracos desviados, a velocidade do jogo aumenta, reduzindo o intervalo entre as atualizações.

## Código Fonte

O código do jogo está localizado no arquivo [script/bumpy_race.ino](script/bumpy_race.ino). Ele utiliza as bibliotecas `LCDI2C_Multilingual` para controlar o display LCD e `SevSeg` para o display de 7 segmentos. O código define sprites personalizados para o carrinho, os buracos e a fumaça, além de implementar a lógica do jogo, como movimentação, detecção de colisões e aumento de dificuldade.

### Principais Funções

- **`setup()`**: Configura o display LCD, registra os caracteres personalizados e inicializa as variáveis do jogo.
- **`loop()`**: Contém a lógica principal do jogo, incluindo a leitura do botão, movimentação dos buracos, exibição do carrinho e detecção de colisões.

## Melhorias Futuras

- Adicionar um sistema de pontuação exibido no display de 7 segmentos.
- Implementar níveis de dificuldade configuráveis.
- Adicionar sons utilizando um buzzer para indicar colisões ou mudanças de nível.
- Expandir o jogo para suportar múltiplos jogadores ou modos de jogo diferentes.