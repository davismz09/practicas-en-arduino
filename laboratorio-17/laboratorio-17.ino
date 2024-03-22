#include <Servo.h>

// Constantes para los pines
const int PULSADOR_PIN = 3;
const int SEMAFORO_1_VERDE_PIN = 12, SEMAFORO_1_AMARILLO_PIN = 11, SEMAFORO_1_ROJO_PIN = 10;
const int SEMAFORO_2_VERDE_PIN = 9, SEMAFORO_2_AMARILLO_PIN = 8, SEMAFORO_2_ROJO_PIN = 7;
const int SEMAFORO_3_VERDE_PIN = 6, SEMAFORO_3_AMARILLO_PIN = 5, SEMAFORO_3_ROJO_PIN = 4;
const int BARRERA_PIN = 13;

Servo barrera;

void inicializarPines() {
    pinMode(PULSADOR_PIN, INPUT);
    pinMode(SEMAFORO_1_VERDE_PIN, OUTPUT);
    pinMode(SEMAFORO_1_AMARILLO_PIN, OUTPUT);
    pinMode(SEMAFORO_1_ROJO_PIN, OUTPUT);
    pinMode(SEMAFORO_2_VERDE_PIN, OUTPUT);
    pinMode(SEMAFORO_2_AMARILLO_PIN, OUTPUT);
    pinMode(SEMAFORO_2_ROJO_PIN, OUTPUT);
    pinMode(SEMAFORO_3_VERDE_PIN, OUTPUT);
    pinMode(SEMAFORO_3_AMARILLO_PIN, OUTPUT);
    pinMode(SEMAFORO_3_ROJO_PIN, OUTPUT);
}

void encenderSemaforo(int verdePin, int amarilloPin, int rojoPin) {
    digitalWrite(verdePin, HIGH);
    digitalWrite(amarilloPin, LOW);
    digitalWrite(rojoPin, LOW);
}

void apagarSemaforo(int verdePin, int amarilloPin, int rojoPin) {
    digitalWrite(verdePin, LOW);
    digitalWrite(amarilloPin, LOW);
    digitalWrite(rojoPin, LOW);
}

void mostrarError(String mensaje) {
    Serial.println("Error: " + mensaje);
}

void setup() {
    barrera.attach(BARRERA_PIN);
    Serial.begin(9600);
    inicializarPines();
}

void loop() {
    char pasoTrenPC = '0';

    do {
        barrera.write(0);
        apagarSemaforo(SEMAFORO_1_ROJO_PIN, SEMAFORO_2_ROJO_PIN, SEMAFORO_3_ROJO_PIN);
        encenderSemaforo(SEMAFORO_1_VERDE_PIN, SEMAFORO_2_VERDE_PIN, SEMAFORO_3_VERDE_PIN);

        if (Serial.available() > 0) {
            pasoTrenPC = Serial.read();
            Serial.println(pasoTrenPC);

            if (pasoTrenPC != '1') {
                pasoTrenPC = '0';
                Serial.println(pasoTrenPC);
            }
        }
    } while (digitalRead(PULSADOR_PIN) == 1 && pasoTrenPC == '0');

    barrera.write(90);
    delay(30);

    apagarSemaforo(SEMAFORO_1_VERDE_PIN, SEMAFORO_2_VERDE_PIN, SEMAFORO_3_VERDE_PIN);
    encenderSemaforo(SEMAFORO_1_AMARILLO_PIN, SEMAFORO_2_AMARILLO_PIN, SEMAFORO_3_AMARILLO_PIN);
    delay(3000);

    apagarSemaforo(SEMAFORO_1_AMARILLO_PIN, SEMAFORO_2_AMARILLO_PIN, SEMAFORO_3_AMARILLO_PIN);
    encenderSemaforo(SEMAFORO_1_ROJO_PIN, SEMAFORO_2_ROJO_PIN, SEMAFORO_3_ROJO_PIN);
    delay(4000);
}
