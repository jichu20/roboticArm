#include "httpHandler.h"
#include <Arduino.h>

ESP8266WebServer server(80);       // Create a webserver object that listens for HTTP request on port 80

void startHttpServer() {
    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);
    server.begin();
}

void handleRoot() {
    sendHTML();
}

void handleNotFound() {
    server.send(404, "text/plain", "404: Not Found");
}

void sendHTML() {
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
            .toggle-button {
                margin-top: 10px;
                display: flex;
                justify-content: center;
                align-items: center;
            }
            .toggle-button button {
                font-size: 16px;
                cursor: pointer;
                border: none;
                border-radius: 5px;
                background-color: #3498db;
                color: white;
                padding: 5px 10px;
                margin: 0 5px;
            }
            .toggle-button button:hover {
                background-color: #2980b9;
            }
            .scroll-bars {
                display: flex;
                justify-content: center;
                align-items: center;
                gap: 10px;
            }
            .vertical-scrollbar {
                writing-mode: bt-lr; /* IE */
                -webkit-appearance: slider-vertical; /* WebKit */
                width: 10px;
                height: 150px;
                background-color: #ccc;
                outline: none;
                opacity: 0.7;
                transition: opacity 0.2s;
            }
            .vertical-scrollbar:hover {
                opacity: 1;
            }
            .horizontal-scrollbar {
                width: 150px;
                height: 10px;
                background-color: #ccc;
                outline: none;
                opacity: 0.7;
                transition: opacity 0.2s;
            }
            .horizontal-scrollbar:hover {
                opacity: 1;
            }
            .hidden { display: none; }
        .control-panel, .scroll-arms { margin: 20px; }
        .scroll-arms { display: none; }
        .toggle-button { margin: 20px; }
        .empty { visibility: hidden; }
        .horizontal-scrollbar {
            outline: none;
            opacity: 0.7;
            transition: opacity 0.2s;
        }
        .horizontal-scrollbar:hover {
            opacity: 1;
        }
        </style>
    </head>
    <body>
        <h1>ESP Robotic Arm</h1>
        <div class="toggle-button">
            <button onclick="toggleControlPanel()">Mostrar/Ocultar</button>
        </div>
       
        </div>
        <div class="control-panel" id="controlPanel">
            <button class="empty"></button>
            <button onclick="moveArm('up', 5)">Arriba</button>
            <button class="empty"></button>
            <button onclick="moveArm('left', 5)">Izquierda</button>
            <button class="empty"></button>
            <button onclick="moveArm('right', -5)">Derecha</button>
            <button class="empty"></button>
            <button onclick="moveArm('down', -5)">Abajo</button>
            <button class="empty"></button>
            <button onclick="moveArm('open', 0)">Abrir Pinza</button>
            <button class="empty"></button>
            <button onclick="moveArm('close', 0)">Cerrar Pinza</button>
        </div>
        <div class="scroll-arms" id="scrollArms">
            <div class="scroll-bar-title">Rotación:</div>
            <input type="range" min="0" max="180" value="90" class="horizontal-scrollbar" id="horizontalScrollbar" onchange="moveArm('horizontal', this.value)">
            <div class="scroll-bar-title">Extensión:</div>
            <input type="range" min="0" max="180" value="90" class="vertical-scrollbar" id="verticalScrollbar" onchange="moveArm('vertical', this.value)">
        </div>
        <div class="log" id="log"></div>

        <script>
            let socket;

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

            function moveArm(direction, value) {
                console.log('Moviendo brazo hacia: ' + direction + ', valor: ' + value);
                addLog('Moviendo brazo hacia: ' + direction + ', valor: ' + value);

                if (socket && socket.readyState === WebSocket.OPEN) {
                    socket.send(direction + ':' + value);
                } else {
                    console.error('WebSocket no está conectado');
                    addLog('WebSocket no está conectado');
                }
            }

            function addLog(message) {
                const logDiv = document.getElementById('log');
                const newLog = document.createElement('div');
                newLog.textContent = message;
                logDiv.appendChild(newLog);
                logDiv.scrollTop = logDiv.scrollHeight;
            }

            function toggleControlPanel() {
                const controlPanel = document.getElementById('controlPanel');
                controlPanel.style.display = controlPanel.style.display === 'none' ? 'grid' : 'none';
            }

            function toggleControlPanel() {
                const controlPanel = document.getElementById('controlPanel');
                const scrollArms = document.getElementById('scrollArms');
                if (controlPanel.style.display === 'none') {
                    controlPanel.style.display = 'grid';
                    scrollArms.style.display = 'none';
                } else {
                    controlPanel.style.display = 'none';
                    scrollArms.style.display = 'flex';
                }
            }
    
            window.onload = function() {
                document.getElementById('controlPanel').style.display = 'grid';
                document.getElementById('scrollArms').style.display = 'none';
                connectWebSocket();
            };
        </script>
    </body>
    </html>
    )rawliteral";
    server.send(200, "text/html", html);
}