#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>

#define ANCHO 128
#define ALTO 64
Adafruit_SSD1306 display(ANCHO, ALTO, &Wire);

Adafruit_BME280 bme;

#define BOTON_IZQ 2
#define BUZZER 8

int pantalla = 0;
const int totalPantallas = 3;

// -------- ICONOS 32x32 --------
const unsigned char iconoTemp [] PROGMEM = {
  0x00,0x00,0x00,0x00,
  0x03,0xC0,0x07,0xE0,
  0x0E,0x70,0x1C,0x38,
  0x18,0x18,0x18,0x18,
  0x18,0x18,0x1C,0x38,
  0x0E,0x70,0x07,0xE0,
  0x03,0xC0,0x00,0x00
};

const unsigned char iconoHum [] PROGMEM = {
  0x00,0x30,0x00,0x78,
  0x00,0xFC,0x01,0xFE,
  0x03,0xFF,0x07,0xFF,
  0x0F,0xFF,0x1F,0xFF,
  0x3F,0xFF,0x7F,0xFF,
  0x7F,0xFF,0x3F,0xFF,
  0x1F,0xFF,0x0F,0xFF,
  0x07,0xFF,0x03,0xFE
};

const unsigned char iconoPres [] PROGMEM = {
  0x3C,0x3C,0x7E,0x7E,
  0xFF,0xFF,0xC3,0xC3,
  0x81,0x81,0x99,0x99,
  0xBD,0xBD,0xFF,0xFF,
  0x7E,0x7E,0x3C,0x3C
};

// ------- FUNCION DE DISEÑO -------
void pantallaEstiloVideo(String titulo, float valor, String unidad, const unsigned char* icono) {
  display.clearDisplay();

  // Título centrado
  display.setTextSize(1);
  display.setCursor((128 - titulo.length() * 6) / 2, 0);
  display.println(titulo);

  // Cuadro
  display.drawRect(5, 15, 118, 45, SSD1306_WHITE);

  // Valor grande
  display.setTextSize(2);
  display.setCursor(15, 32);
  display.print(valor);
  display.print(" ");
  display.print(unidad);

  // Icono
  display.drawBitmap(90, 25, icono, 32, 32, SSD1306_WHITE);

  display.display();
}

void setup() {
  pinMode(BOTON_IZQ, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  if (!bme.begin(0x76)) {
    display.println("BME280 ERROR!");
    display.display();
    while (1);
  }
}

void loop() {

  if (digitalRead(BOTON_IZQ) == LOW) {
    pantalla--;
    if (pantalla < 0) pantalla = totalPantallas - 1;

    tone(BUZZER, 1000, 100);
    delay(250);
  }

  float t = bme.readTemperature();
  float h = bme.readHumidity();
  float p = bme.readPressure() / 100.0;

  switch (pantalla) {
    case 0:
      pantallaEstiloVideo("Temperature", t, "C", iconoTemp);
      break;

    case 1:
      pantallaEstiloVideo("Humidity", h, "%", iconoHum);
      break;

    case 2:
      pantallaEstiloVideo("Pressure", p, "hPa", iconoPres);
      break;
  }

  delay(100);
}
