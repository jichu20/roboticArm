#include "robotic_arm.h"
// #include <iostream>
#include <Arduino.h>
#include <Servo.h>

// using namespace std;

// Constructor
// RoboticArm::RoboticArm() : verticalPosition(0), horizontalPosition(90), gripperClosed(false) {}
RoboticArm::RoboticArm(int pinHombro, int pinCodo, int pinMuneca, int pinPinza): verticalPosition(0), horizontalPosition(90), gripperClosed(false),
      pinHombro(pinHombro), pinCodo(pinCodo), pinMuneca(pinMuneca), pinPinza(pinPinza) {}


// Función para inicializar el brazo robótico
void RoboticArm::init() {
    Serial.println("Inicializando brazo robótico");
    
    Serial.println("Ataching servos .... ");
    
    Serial.println("Ataching hombro .... ");
    servoHombro.attach(pinHombro);
    servoHombro.write(verticalPosition);
    Serial.println("Ataching codo .... ");
    // servoCodo.attach(pinCodo);

    Serial.println("Ataching muneca .... ");
    // servoMuneca.attach(pinMuneca);

    Serial.println("Ataching pinza .... ");
    // servoPinza.attach(pinPinza);

    // servoHombro.write(horizontalPosition);
    // servoCodo.write(verticalPosition);
    // servoMuneca.write(verticalPosition);
    
    // if (gripperClosed){
    //     servoPinza.write(0);
    // } else {
    //     servoPinza.write(90);
    // }
    
}

// Función para mover el brazo en posición vertical
void RoboticArm::moveVertical(int angle) {
    verticalPosition = verticalPosition + angle;
    servoCodo.write(verticalPosition);
    servoMuneca.write(verticalPosition);
    Serial.printf("Moviendo brazo en posición vertical a %d grados", verticalPosition);
}

// Función para mover el brazo en posición horizontal
void RoboticArm::moveHorizontal(int angle) {
    // Lógica para mover el brazo en posición horizontal
    horizontalPosition = horizontalPosition + angle;
    servoHombro.write(horizontalPosition);
    Serial.printf("Moviendo brazo en posición horizontal a %d grados", horizontalPosition);
}

// Función para abrir la pinza
void RoboticArm::openGripper() {
    // Lógica para abrir la pinza
    gripperClosed = false;
    Serial.println("Abriendo pinza");
    // Aquí iría el código específico para controlar el hardware
}

// Función para cerrar la pinza
void RoboticArm::closeGripper() {
    // Lógica para cerrar la pinza
    gripperClosed = true;
    Serial.println("Cerrando pinza");
    // Aquí iría el código específico para controlar el hardware
}