#include "robotic_arm.h"
#include <Arduino.h>
#include <Servo.h>

// using namespace std;

// Constructor
// RoboticArm::RoboticArm() : verticalPosition(0), horizontalPosition(90), gripperClosed(false) {}
RoboticArm::RoboticArm(int pinHombro, int pinCodo, int pinBase, int pinPinza): verticalPosition(5), horizontalPosition(90), gripperClosed(false),
      pinHombro(pinHombro), pinCodo(pinCodo), pinBase(pinBase), pinPinza(pinPinza) {}


// Función para inicializar el brazo robótico
void RoboticArm::init() {
    Serial.println("Inicializando brazo robótico");
    
    Serial.println("Ataching servos .... ");
    
    Serial.println("Ataching Base .... ");
    servoBase.attach(pinBase);
    servoHombro.write(horizontalPosition);

    Serial.println("Ataching hombro .... ");
    servoHombro.attach(pinHombro);
    servoHombro.write(verticalPosition);
    
    Serial.println("Ataching codo .... ");
    servoCodo.attach(pinCodo);
    servoCodo.write(verticalPosition);

    Serial.println("Ataching pinza .... ");
    servoPinza.attach(pinPinza);
    servoPinza.write(0);
    
}

// Función para mover el brazo en posición vertical
void RoboticArm::moveUpVertical(int angle) {
    if (verticalPosition < 180){
        verticalPosition = verticalPosition + angle;
        servoCodo.write(verticalPosition);
        servoHombro.write(verticalPosition);
        Serial.printf("Moviendo brazo en posición vertical a %d grados", verticalPosition);
    }else{
        Serial.printf("No se realiza movimiento en el brazo, la posición actual es de %d", verticalPosition);
    }
}

void RoboticArm::moveDownVertical(int angle) {
    if (verticalPosition < 180){
        verticalPosition = verticalPosition + angle;
        servoCodo.write(verticalPosition);
        servoHombro.write(verticalPosition);
        Serial.printf("Moviendo brazo en posición vertical a %d grados", verticalPosition);
    }else{
        Serial.printf("No se realiza movimiento en el brazo, la posición actual es de %d", verticalPosition);
    }
}

// Función para mover el brazo en posición horizontal
void RoboticArm::moveHorizontal(int angle) {
 
 if (horizontalPosition > 0 && horizontalPosition < 180){
        // Lógica para mover el brazo en posición horizontal
        horizontalPosition = horizontalPosition + angle;
        servoBase.write(horizontalPosition);
        Serial.printf("Moviendo brazo en posición horizontal a %d grados", horizontalPosition);
    }else{
        Serial.printf("No se realiza movimiento en el brazo, la posición actual es de %d", horizontalPosition);
    }

}

void RoboticArm::setVertical(int angle) {

    if (angle> verticalPosition){
        while (angle > verticalPosition)
        {
            verticalPosition = verticalPosition + 1;
            servoCodo.write(verticalPosition);
            servoHombro.write(verticalPosition);
            delay(10);
        }
    }else if (angle < verticalPosition){
        while (angle < verticalPosition)
        {
            verticalPosition = verticalPosition - 1;
            servoCodo.write(verticalPosition);
            servoHombro.write(verticalPosition);
            delay(10);
        }
    }

        Serial.printf("Estableciendo posición del brazo a %d grados", verticalPosition);
}

void RoboticArm::setHorizontal(int angle) {

    if (angle> horizontalPosition){
        while (angle > horizontalPosition)
        {
            horizontalPosition = horizontalPosition + 1;
            servoBase.write(horizontalPosition);
            delay(10);
        }
    }else if (angle < horizontalPosition){
        while (angle < horizontalPosition)
        {
            horizontalPosition = horizontalPosition - 1;
            servoBase.write(horizontalPosition);
            delay(10);
        }
    }
    
    Serial.printf("Estableciendo posición del brazo a %d grados", horizontalPosition);
}
// Función para abrir la pinza
void RoboticArm::openGripper() {
    // Lógica para abrir la pinza
    gripperClosed = false;
    Serial.println("Abriendo pinza");
    servoPinza.write(0);
    // Aquí iría el código específico para controlar el hardware
}

// Función para cerrar la pinza
void RoboticArm::closeGripper() {
    // Lógica para cerrar la pinza
    gripperClosed = true;
    Serial.println("Cerrando pinza");
    servoPinza.write(30);
    // Aquí iría el código específico para controlar el hardware
}