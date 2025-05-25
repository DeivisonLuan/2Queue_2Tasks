#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <sstream>
#include <Arduino.h>

#define Built_in_Led 2

static const int serial_queue_len = 5;   // Tamanho da fila 1: Mensagens do serial
static const int freq_queue_len = 5;     // Tamanho da fila 2: Armazena a frequencia de piscadas
static const uint8_t blink_max = 10;   // Numero max de piscadas antes da mensagem 

static QueueHandle_t queue_1; // Define fila 1: Armazena as mensagens do serial
static QueueHandle_t queue_2; // Define fila 2: Recebe valores da fila e pisca led com frequencias usando esses valores

void SerialInfo(void* parameters){

}

void FreqDefine(void* parameters){

}

void setup() {
  pinMode(Built_in_Led, OUTPUT);

  Serial.begin(115200);

  queue_1 = xQueueCreate(serial_queue_len, sizeof(50*sizeof(char)));
  queue_2 = xQueueCreate(freq_queue_len, sizeof(int));

  // Inicia tarefa A: Leitura e escrita serial
  xTaskCreatePinnedToCore(SerialInfo, "SerialInfo", 1024, NULL, 1, NULL, 1);
 
  // Inicia a tarefa B: Pisca Led com frequencia controlada
  xTaskCreatePinnedToCore(FreqDefine, "FreqDefine", 1024, NULL, 1, NULL, 1);
}

void loop() {
  vTaskDelete(NULL);
}
