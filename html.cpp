#include <Arduino.h>

String SendHTML(){
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>Control de Brazo Robótico</title>
    <style>
      body {
        font-family: Helvetica;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        height: 100vh;
        margin: 0;
        background-color: #f0f0f0;
      }
      .control-panel {
        display: grid;
        grid-template-columns: repeat(3, 100px);
        grid-template-rows: repeat(4, 100px);
        gap: 10px;
      }
      .control-panel button {
        width: 100%;
        height: 100%;
        font-size: 20px;
        cursor: pointer;
        border: none;
        border-radius: 10px;
        background-color: #1abc9c;
        color: white;
      }
      .control-panel button:hover {
        background-color: #16a085;
      }
      .empty {
        background-color: transparent;
        cursor: default;
      }
      .log {
        margin-top: 20px;
        width: 80%;
        height: 150px;
        overflow-y: auto;
        background-color: #fff;
        border: 1px solid #ccc;
        border-radius: 10px;
        padding: 10px;
        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
      }
    </style>
  </head>
  <body>
    <h1>ESP Robotic Arm</h1>
    <div class="control-panel">
      <button class="empty"></button>
      <button onclick="moveArm('up')">Arriba</button>
      <button class="empty"></button>
      <button onclick="moveArm('left')">Izquierda</button>
      <button class="empty"></button>
      <button onclick="moveArm('right')">Derecha</button>
      <button class="empty"></button>
      <button onclick="moveArm('down')">Abajo</button>
      <button class="empty"></button>
      <button onclick="moveArm('open')">Abrir Pinza</button>
      <button class="empty"></button>
      <button onclick="moveArm('close')">Cerrar Pinza</button>
    </div>

    <div class="log" id="log"></div>

    <script>
      let socket;
      const logDiv = document.getElementById('log');

      // Conectar al WebSocket
      function connectWebSocket() {
            socket = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
            socket.onopen = function(event) {
                console.log('WebSocket conectado');
                addLog('WebSocket conectado');
            };
            socket.onclose = function(event) {
                console.log('WebSocket desconectado');
                addLog('WebSocket desconectado');
            };
            socket.onmessage = function(event) {
                console.log('Mensaje recibido: ' + event.data);
                addLog('Mensaje recibido: ' + event.data);
            };
            socket.onerror = function(error) {
                console.error('WebSocket error: ' + error);
                addLog('WebSocket error: ' + error);
            };
        }

      function moveArm(direction) {
            console.log('Moviendo brazo hacia: ' + direction);
            addLog('Moviendo brazo hacia: ' + direction);

            if (socket && socket.readyState === WebSocket.OPEN) {
                socket.send(direction);
            } else {
                console.error('WebSocket no está conectado');
                addLog('WebSocket no está conectado');
            }
        }

       // Mostrar mensajes en el registro
      function logMessage(message) {
        const timestamp = new Date().toLocaleTimeString();
        const messageElement = document.createElement('p');
        messageElement.textContent = `[${timestamp}] ${message}`;
        logDiv.appendChild(messageElement);
        logDiv.scrollTop = logDiv.scrollHeight;
      }

      // Enviar comando al WebSocket
      function sendCommand(command) {
        if (!socket || socket.readyState !== WebSocket.OPEN) {
          logMessage("No estás conectado al WebSocket. Intenta reconectarte.");
          return;
        }

        socket.send(command);
        logMessage(`Comando enviado: ${command}`);
      }
      function addLog(message) {
        const logDiv = document.getElementById('log');
        const newLog = document.createElement('div');
        newLog.textContent = message;
        logDiv.appendChild(newLog);
        logDiv.scrollTop = logDiv.scrollHeight;
      }

      window.onload = function() {
            connectWebSocket();
        };
    </script>
  </body>
  </html>
    )rawliteral";
  
  return html;
}