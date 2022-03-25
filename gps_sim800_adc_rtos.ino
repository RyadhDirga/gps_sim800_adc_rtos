#include <Arduino_FreeRTOS.h>
#include <SoftwareSerial.h>

SoftwareSerial sim800l (2, 3);

char c = ' ';
void adc(void *parameter);
void sim(void *parameter);

void setup() {
  Serial.begin(9600);
  sim800l.begin(9600);
  delay(1000);
  Serial.println("sim800l Ready");
  xTaskCreate(adc,"adc", 128, NULL, 1, NULL);
  xTaskCreate(sim,"sim800l", 128, NULL, 1, NULL);
}

void adc(void *parameter){
  (void) parameter;
  for(;;){
    int hasil = analogRead(A0);
    Serial.println(hasil);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void sim(void *parameter){
  (void) parameter;
  for(;;){
    if (sim800l.available()){ 
      c = sim800l.read();
      Serial.write(c);
      } 
  }
}

void loop() {

}
