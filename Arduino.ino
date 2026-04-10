// Biblioteca para controlar o display LCD
#include <LiquidCrystal.h>

// Define os pinos do LCD: RS, Enable, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

// Pino analógico onde o LDR está conectado
int ldrPin = A0;

// Pinos dos LEDs indicadores de status
int ledVerde = 6;    // LED verde: ambiente OK
int ledAmarelo = 7;  // LED amarelo: nível de alerta
int ledVermelho = 8; // LED vermelho: nível crítico

// Pino do buzzer para alertas sonoros
int buzzer = 9;

// Caractere personalizado: ícone de garrafa de vinho
byte garrafa[8] = {
  B00100,B00100,B01110,B01110,
  B01110,B01110,B01110,B00100
};

// Caractere personalizado: taça vazia
byte tacaVazia[8] = {
  B00000,B01010,B01010,B01010,
  B01010,B00100,B00100,B01010
};

// Caractere personalizado: vinho caindo (animação)
byte vinhoCaindo[8] = {
  B00100,B00100,B00100,B00100,
  B00100,B00100,B00100,B00100
};

// Caractere personalizado: taça com vinho pela metade
byte tacaMeio[8] = {
  B00000,B01110,B01010,B01010,
  B01010,B00100,B00100,B01010
};

// Caractere personalizado: taça cheia de vinho
byte tacaCheia[8] = {
  B00000,B01110,B01110,B01110,
  B01110,B00100,B00100,B01010
};

void setup()
{
  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);

  // Inicializa a comunicação serial para debug
  Serial.begin(9600);

  // Configura os pinos dos LEDs e buzzer como saída
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Registra os caracteres personalizados na memória do LCD (slots 0 a 4)
  lcd.createChar(0, garrafa);
  lcd.createChar(1, tacaVazia);
  lcd.createChar(2, vinhoCaindo);
  lcd.createChar(3, tacaMeio);
  lcd.createChar(4, tacaCheia);

  // --- Animação de boas-vindas ---

  // Exibe o nome da vinheria
  lcd.setCursor(2, 0);
  lcd.print("Vinheria");

  // Mostra a garrafa ao lado do nome
  lcd.setCursor(7, 1);
  lcd.write(byte(0)); // garrafa
  delay(800);

  // Aparece a taça vazia ao lado da garrafa
  lcd.setCursor(8, 1);
  lcd.write(byte(1)); // taça vazia
  delay(800);

  // Animação do vinho caindo da garrafa para a taça
  lcd.setCursor(8, 0);
  lcd.write(byte(2)); // vinho caindo
  delay(800);

  // Taça com vinho pela metade
  lcd.setCursor(8, 1);
  lcd.write(byte(3)); // taça meio cheia
  delay(800);

  // Taça completamente cheia
  lcd.setCursor(8, 1);
  lcd.write(byte(4)); // taça cheia
  delay(800);

  // Limpa o caractere de vinho caindo
  lcd.setCursor(8, 0);
  lcd.print("i");
  delay(2000);

  // Limpa o LCD e exibe tela de carregamento
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AGNELLO");
  lcd.setCursor(0, 1);
  lcd.print("Monitorando...");
  delay(2500);

  // Limpa o LCD para iniciar o monitoramento
  lcd.clear();
}

void loop()
{
  // Lê o valor bruto do LDR (0 a 1023)
  int valor = analogRead(ldrPin);
  delay(100); // Pequena pausa para estabilizar a leitura

  // Converte o valor bruto para porcentagem de luminosidade (0% a 100%)
  // 54 = valor no escuro total, 974 = valor com luz máxima (calibrado)
  int luz = map(valor, 54, 974, 100, 0);

  // Envia os valores para o Serial Monitor para debug
  Serial.print("Valor: ");
  Serial.print(valor);
  Serial.print(" | Luz: ");
  Serial.println(luz);

  // Atualiza a primeira linha do LCD com a porcentagem de luminosidade
  lcd.setCursor(0, 0);
  lcd.print("Luz: ");
  lcd.print(luz);
  lcd.print("%   "); // Espaços para apagar dígitos anteriores

  // --- Lógica de status por faixa de luminosidade ---

  if (luz <= 80) {
    // Luminosidade OK: acende LED verde, apaga os outros, silencia o buzzer
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer);
    lcd.setCursor(0, 1);
    lcd.print("STATUS: OK      ");
  }
  else if (luz <= 90) {
    // Nível de alerta: acende LED amarelo e dispara buzzer por 3 segundos
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
    lcd.setCursor(0, 1);
    lcd.print("STATUS: Alerta! ");
    tone(buzzer, 1200);  // Toca o buzzer na frequência 1200Hz
    delay(3000);         // Mantém por 3 segundos conforme especificado
    noTone(buzzer);      // Para o buzzer
  }
  else {
    // Nível crítico: acende LED vermelho e buzzer intermitente
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("STATUS: CRITICO!");
    tone(buzzer, 1500);  // Toca na frequência 1500Hz (mais agudo que o alerta)
    delay(200);
    noTone(buzzer);
    delay(200);          // Pausa para efeito intermitente
  }

  delay(300); // Aguarda antes da próxima leitura
}
