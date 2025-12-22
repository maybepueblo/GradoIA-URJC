# Sockets UDP

En ocasiones vamos a necesitar enviar secuencias de datos a otros dispositivos y un mensaje de MQTT o una consulta http no es una opción eficiente. Por ejemplo si queremos muestrear un parámetro cientos o miles de veces por segundo y queremos enviarlo a un pc para procesarlos o graficarlos allí porque el microcontrolador no tiene recursos suficientes. O por ejemplo si queremos enviar los datos al pc para ir guardándolos en disco y genera así un conjunto de datos (o dataset) con el que entrenar un modelo de apredizaje automático.

Una posible solución sería usar como ya hemos visto el puerto serie, que tiene la ventaja de su secillez, pero el incoveniente de que tiene que ser cableado. SI queremeos que la conexión sea inhalámbrica podríamos usar una conexión serie sobre Bluettoth ([tutorial de BLE UART](https://www.prometec.net/esp32-serial-bluetooth/)) y otra posibilidad si tenemos WIFI es usar un socket:

Los sockets UDP (a diferencia de los websockets) no tienen sesiones y son más sencillos de usar y más rápidos. Tienen también un cliente y un servidor y el el mayor problema es quizá es el de conocer la IP del servidor. Cada proyecto tendrá una solución mejor para este problema.

A continuación tiene un ejemplo con un cliente en un script de python (para un pc) y un servidor udp en ESP32c6. El cliente además, grafica los datos recibidos en tiempo real con la librería MatplotLib. Matplotlib puede correr en raspeberry pero debe tener instalado y configurado el gestor de ventanas (x11) que no está instalado en la versión lite de raspbian. Puede intalarse posteriormente pero exige cierta pelea. 

Script de python para PC (cliente)

```python
import socket
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

UDP_IP = "192.168.1.242" # The IP that is printed in the serial monitor from the ESP32
SHARED_UDP_PORT = 4210

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
sock.connect((UDP_IP, SHARED_UDP_PORT))
def loop():

    plt.ion()    
    data=[0]*2000
    
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(data)

    i=0
    while True:
        data[i] = int(sock.recv(2048))
        i += 1
        if i>1999: 
            print(".")
           
            plt.plot(data)
            plt.draw()
            plt.pause(0.0001)
            plt.clf()
            i=0
           
if __name__ == "__main__":
    sock.send('Hello ESP32'.encode())
    loop()
```



Servidor UDP (Esp32)

```c
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>

//set up to connect to an existing network (e.g. mobile hotspot from laptop that will run the python code)
const char* ssid = "unaWifiCualquiera";
const char* password = "xxxxx";
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  //  port to listen on
char incomingPacket[255];  // buffer for incoming packets
int i;
void setup()
{
  i=0; //valor que voy a enviar al cliente
  int status = WL_IDLE_STATUS;
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to wifi");
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  // we recv one packet from the remote so we can know its IP and port
  bool readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
     {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      readPacket = true;
    } 
  }
}

void loop()
{
  // once we know where we got the inital packet from, send data back to that IP address and port

  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.printf(String(sin(i)).c_str(),2);
  Udp.endPacket();
  i +=1;
  if (i>360){i=0;}
}

```

## Trabajo de estudiante

* ¿Qué velocidad de transmisión se consigue con el socket UDP?¿Cuantos valores recibe en un segundo? Modifique es cliente para responder a la pregunta
* Haga que el cliente sea el ESP y el servidor el PC. 