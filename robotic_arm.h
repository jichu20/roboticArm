#ifndef ROBOTIC_ARM_H
#define ROBOTIC_ARM_H

#include <Servo.h>

class RoboticArm {
public:
    // Constructor
    RoboticArm(int pinHombro, int pinCodo, int pinMuneca, int pinPinza);

    // Inicializa el brazo robótico
    void init();

    // Mueve el brazo en posición vertical
    void moveVertical(int angle);

    // Mueve el brazo en posición horizontal
    void moveHorizontal(int angle);

    // Abre la pinza
    void openGripper();

    // Cierra la pinza
    void closeGripper();

private:
    int verticalPosition;  // Posición actual del brazo en vertical
    int horizontalPosition; // Posición actual del brazo en horizontal
    bool gripperClosed;    // Estado de la pinza (cerrada o abierta)

    int pinHombro; // Almacena el pin del servomotor del hombro
    int pinCodo; // Almacena el pin del servomotor del codo
    int pinMuneca; // Almacena el pin del servomotor de la muñeca
    int pinPinza; // Almacena el pin del servomotor de la pinza

    Servo servoHombro; // Variable que declara el servomotor pra actuar sobre el mismo
    Servo servoCodo; // Variable que declara el servomotor pra actuar sobre el mismo
    Servo servoMuneca; // Variable que declara el servomotor pra actuar sobre el mismo
    Servo servoPinza; // Variable que declara el servomotor pra actuar sobre el mismo
};

#endif // ROBOTIC_ARM_H