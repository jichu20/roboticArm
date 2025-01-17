# roboticArm

## Descripción
Proyecto para la generación de un brazo robotico construido con impresora 3D siguiendo los [diseños](https://www.printables.com/model/449747-brazo-robotico-robotic-arm) de [@RACBOTS](https://www.printables.com/@RACBOTS_756978).

El brazo estará compuesto de 4 servomotores que controlaran los movimientos del brazo.
- Base: se encargará de mover el brazo de izquierda a derecha 
- Hombro: posiciona junto con la `codo` el brazo en posición recogido o extendido.
- Codo: posiciona junto con el `hombro` el brazo en posición recogido o extendido.
- Pinza: Abre y cierra la pinza situada en el extremo del brazo.

Dichos servomotores, serán gestionados desde una placa NodeMcu que expondrá un punto de acceso WiFi denominado `ESP8266-Access-Point`cuya contraseña será `123456789`. 

La placa expondrá un servidor http para exponer una interface web de ayuda para controlar el brazo robotico en la direción [http://192.168.4.22/](http://192.168.4.22/).

Dicha web se comunicará con la placa nodeMcu a través de un websocket que escuchará en el puerto 81 de dicha placa las instrucciones a ejecutar.

## Recursos

### 3d-model

Contiene los archivos de impresión 3d de las piezas que forman parte del brazo

# Referencias 

- https://tttapa.github.io/ESP8266/Chap14%20-%20WebSocket.html
- https://www.instructables.com/Esp8266Websockets-RGB-LED-controller/