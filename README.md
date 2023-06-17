# Auto a control remoto con ESP32

## Elementos básicos
- Motor: Dos motores conectados mediante un puente H para tracción y dirección
- Luces: Luces con switch con opciones de prendido/apagado manual y una automática haciendo uso de un ldr
- Sensor de estacionamiento: Usamos un HC-SR04 para detectar distancia desde la parte trasera del auto junto a un buzzer que suena con mayor frecuencia dependiendo de la distancia
- Control: Utilizando una interfaz de joystick con el celular
## Hardware (Componentes)
- ESP32
- Protoboard
- Puente H L298n
- Fuente Dc-Dc Step Down Lm2596
- LDR
- LED
- x2 Motores DC 6,5v
- Batería 7,4v
- Bornera WAGO
- chasis auto rc
- paragolpes con impresión 3d
- Cables Dupont 
- Cables UTP

## Hardware (desarrollo)
Comenzamos con la idea de construir un auto a control remoto con ESP32 utilizando un servidor para el manejo del auto.

Para la base del auto se desarmó otro auto de juguete que funcionaba con radiofrecuencia.

Una vez desarmado utilizamos el chasis, las ruedas y los dos motores, uno para la dirección y otro para la tracción. Además, se aprovechó el mecanismo de giro del auto original para poder direccionar el nuevo. 

Un motor se utiliza para traccionar (ir hacia adelante y hacia atrás) y otro para doblar. 

Como alimentación para el auto, se probaron discutieron múltiples opciones como pilas, pero finalmente se decidió utilizar una batería de otro auto de juguete. Debido a que la batería funciona con 7,4v y el esp32 con 5v se necesitó añadir otro componente para manejar esta diferencia. Una opción era usar un regulador de tensión 7805 pero debido a sus mejores prestaciones terminamos optando por una fuente stepdown regulable. 

Para el manejo de ambos motores se utilizó un puente H. Se consideraron dos modelos posibles, uno de ellos el L9110S pero terminamos optando por el L298N ya que este nos permite manejar además la velocidad de los motores. El modelo utiliza un tercer cable por cada motor que se conecta a una entrada PWM del ESP32 que permite modificar la velocidad de los motores. La alimentación del puente H no pasa por el stepdown pues eso alimenta directamente a los motores pudiendo tener hasta un máximo de 35V. 

Finalmente, se agregó un sistema de luces. Para esto se imprimió con una impresora 3D dos paragolpes (delantero y trasero). En el paragolpes trasero se instaló un led que está programado para encenderse cuando se da marcha atrás y en el paragolpes delantero un led que funciona como las luces bajas de un auto con tres modos posibles: Encendido, apagado y automático. El último funciona con un LDR, prendiéndose ante la falta de luz. 
## Software
Para el manejo del auto, se levantó un servidor en el esp32 el cual aloja una página web. La misma página provee diferentes botones para mover el auto hacia adelante, atrás, doblar a la izquierda y doblar a la derecha. 

Se utiliza una slidebar para modificar solamente la velocidad de los motores de tracción mediante el Puente H. Para doblar se necesita que el motor de dirección este en su máxima potencia. Cada vez que hay un cambio en el HTML se ejecuta una función donde se establece el valor de speed (entre 0 y 255) para que luego las demás funciones trabajen a la velocidad seteada. 

También se agregaron botones para controlar las luces, el botón de ON automáticamente pone el LED en high, el off en low, y el auto ejecuta una función donde cada 1 segundo se mide la resistencia del LDR, en caso de estar debajo de un valor establecido se prende. Se utiliza la biblioteca Ticker que permite automatizar la comprobación periódica de la intensidad de luz y el control de las luces sin bloquear la ejecución principal del programa.

## DEMO

https://github.com/nicolas-mangini/esp32-rc-car-mod/assets/72108522/2462815e-a7b9-4b3e-b488-a6023621570a
