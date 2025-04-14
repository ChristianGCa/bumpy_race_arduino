#include <LCDI2C_Multilingual.h>
#include <SevSeg.h>

LCDI2C_Generic lcd(0x27, 17, 2); // Configura o display

const int button = 2;
int carPos = 1; // 0 para a linha superior, 1 para a linha inferior
bool isPressed = false;
int points = 0;
int speed = 1000;
bool toggleSmoke = false; // Variável para alternar entre os sprites de fumaça
int holePassed = 0; // Contador de buracos passados

// Definindo o sprite do carro do jogador
byte carPlayer[8] = {
  0b10010,
  0b11110,
  0b11111,
  0b11001,
  0b11001,
  0b11111,
  0b11110,
  0b10010
};

// Definindo o sprite do inimigo (buraco)
byte hole[8] = {
  0b00000,
  0b00100,
  0b11110,
  0b11111,
  0b01110,
  0b01111,
  0b00110,
  0b00000
};

// Definindo os sprites de fumaça
byte smoke1[8] = {
  0b00000,
  0b01000,
  0b00110,
  0b01001,
  0b00111,
  0b10100,
  0b01000,
  0b00000
};

byte smoke2[8] = {
  0b10000,
  0b00100,
  0b11010,
  0b01001,
  0b10101,
  0b10100,
  0b01100,
  0b10000
};

// Variáveis do jogo
int holePos[2] = {15, -1}; // Coluna dos inimigos em cada linha

unsigned long previousMillis = 0;
const long interval = 350;  // Intervalo do jogo (controle de velocidade)
bool buttonState = false;
bool lastButtonState = false;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(button, INPUT_PULLUP);
  lcd.clear();
  lcd.createChar(0, carPlayer); // Registra o carro do jogador
  lcd.createChar(1, hole);      // Registra o buraco
  lcd.createChar(2, smoke1);    // Registra a primeira fumaça
  lcd.createChar(3, smoke2);    // Registra a segunda fumaça
}

void loop() {
  // Verificar o botão de forma não bloqueante
  buttonState = digitalRead(button) == LOW;
  if (buttonState && !lastButtonState) {
    carPos = !carPos;
  }
  lastButtonState = buttonState;

  // Atualizar o tempo e verificar se o intervalo de tempo passou
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Atualizar posições dos inimigos
    lcd.clear();
    for (int linha = 0; linha < 2; linha++) {
      if (holePos[linha] >= 0) {
        lcd.setCursor(holePos[linha], linha);
        lcd.write((uint8_t)1); // Exibe o buraco
        holePos[linha]--; // Move o buraco para a esquerda
      } else {
        // Novo buraco entra na direita
        if (random(0, 4) == 0) { // 1 em 4 chances de surgir novo buraco
          holePos[linha] = 15;
        }
      }
    }

    // Exibir o carro do jogador
    lcd.setCursor(1, carPos);
    lcd.write((uint8_t)0); // Exibe o carro do jogador

    // Alternar a fumaça do carro do jogador
    lcd.setCursor(0, carPos);
    if (toggleSmoke) {
      lcd.write((uint8_t)2); // Exibe smoke1
    } else {
      lcd.write((uint8_t)3); // Exibe smoke2
    }
    toggleSmoke = !toggleSmoke; // Alterna entre fumaça 1 e 2

    // Verificar colisão
    if (holePos[carPos] == 1) { // Buraco na mesma posição do carro do jogador
      lcd.clear();
      lcd.print("Game Over!");
      delay(2000); // Game Over delay, que pode ser alterado para um timeout com millis()
      speed = 1000;
      setup(); // Reinicia o jogo
    }

    // Verificar se o buraco passou pela tela
    for (int i = 0; i < 2; i++) {
      if (holePos[i] == -1) {
        holePassed++; // Incrementa o contador de buracos passados
        if (holePassed >= 5) {
          holePassed = 0; // Resetar o contador
          speed = max(speed - 30, 40);
        }
      }
    }
  }
}
