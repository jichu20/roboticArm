#ifndef ROBOTIC_ARM_H
#define ROBOTIC_ARM_H

#include <Servo.h>

class RoboticArm {
public:
    // Constructor
    RoboticArm(int pinHombro, int pinCodo, int pinBase, int pinPinza);

    // Inicializa el brazo robótico
    void init();

    // Establece la posición vertical del brazo a la indicada como parámetro.
    void setVertical(int angle);

    // Establece la posición horizontal del brazo a la indicada como parámetro.
    void setHorizontal(int angle);
    
    // Mueve el brazo en posición vertical (up)
    void moveUpVertical(int angle);

    // Mueve el brazo en posición vertical (down)
    void moveDownVertical(int angle);

    // Mueve el brazo en posición horizontal 
    void moveHorizontal(int angle);

    int getVerticalPosition() {
        return verticalPosition;
    }

    int getHorizontalPosition() {
        return horizontalPosition;
    }

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
    int pinBase; // Almacena el pin del servomotor de la muñeca
    int pinPinza; // Almacena el pin del servomotor de la pinza

    Servo servoHombro; // Variable que declara el servomotor pra actuar sobre el mismo
    Servo servoCodo; // Variable que declara el servomotor pra actuar sobre el mismo
    Servo servoBase; // Variable que declara el servomotor pra actuar sobre el mismo
    Servo servoPinza; // Variable que declara el servomotor pra actuar sobre el mismo
};

#endif // ROBOTIC_ARM_H