![image](https://github.com/nicolas-mangini/esp32-rc-car-mod/assets/72108522/4942dd6e-c4bd-4b3a-9429-ea97b9b5dfc7)

# Auto a control remoto con ESP32
## Elementos básicos
- Motor: Dos motores conectados mediante un puente H para tracción y dirección
- Luces: Dos leds con opciones de prendido/apagado manual y modo automático, haciendo uso de un LDR
- Control: Utilizando una interfaz de joystick en una pagina web
## Hardware (Componentes)
- ESP32
- Protoboard
- Puente H L298n
- Fuente Dc-Dc Step Down Lm2596
- LDR
- LED blancos
- x2 Motores DC 6,5v
- Batería 7,4v
- Bornera WAGO
- Chasis auto rc
- Dos paragolpes con impresión 3d
- Cables Dupont 
- Cables UTP

## Hardware (desarrollo)
Comenzamos con la idea de construir un auto a control remoto con ESP32 utilizando un servidor para el manejo del auto.

Para la base del auto se desarmó otro auto de juguete que funcionaba con radiofrecuencia.

Una vez desarmado utilizamos el chasis, las ruedas y los dos motores. Uno de ellos para la dirección y otro para la tracción. Además, se aprovechó el mecanismo de giro del auto original para poder direccionar el nuevo. 

Un motor se utiliza para traccionar (ir hacia adelante y hacia atrás) y otro para doblar. 

Como alimentación para el auto, se discutieron múltiples opciones como pilas, pero finalmente se decidió utilizar una batería de otro auto de juguete. Debido a que la batería funciona con 7,4v y el ESP32 con 5v se necesitó añadir otro componente para manejar esta diferencia. Una opción era usar un regulador de tensión 7805 pero debido a sus mejores prestaciones terminamos optando por una fuente stepdown regulable.

Para el manejo de ambos motores se utilizó un puente H L298n. Se consideraron dos modelos posibles, uno de ellos el L9110S pero terminamos optando por el L298n ya que este nos permite manejar además la velocidad de los motores. Para este manejo de la velocidad se utiliza un tercer cable por cada motor que se conecta a una entrada PWM del ESP32. La alimentación del puente H no pasa por el stepdown pues eso alimenta directamente a los motores pudiendo aprovechar los 7,4v de la batería. 

Finalmente, se agregó un sistema de luces. Para esto se imprimieron en 3D dos paragolpes (delantero y trasero). En el paragolpes trasero se instaló un led que está programado para encenderse cuando se da marcha atrás y en el paragolpes delantero un led que funciona como las luces bajas de un auto con tres modos posibles: Encendido, apagado y automático. El último funciona con un LDR, prendiéndose ante la falta de luz. 

## Software
Para el manejo del auto, se levantó un servidor en el ESP32 el cual aloja una página web. La misma página provee diferentes botones para mover el auto hacia adelante, atrás, doblar a la izquierda y doblar a la derecha. 

Se utiliza una slidebar para modificar solamente la velocidad del motor de tracción. En cambio, para doblar se necesita que el motor de dirección este en su máxima potencia. Cada vez que hay un cambio en el HTML se ejecuta una función donde se establece el valor de SPEED (entre 0 y 255) para que luego las demás funciones (ir hacia adelante y hacia atrás) trabajen a la velocidad seteada. 

También se agregaron botones para controlar las luces, el botón de ON automáticamente pone el LED en HIGH, el off en LOW, y el AUTO ejecuta una función donde cada 1 segundo se mide la resistencia del LDR, en caso de estar debajo de un valor establecido se prende. Se utiliza la biblioteca Ticker que permite automatizar la comprobación periódica de la intensidad de luz y el control de las luces sin bloquear la ejecución principal del programa.

## DEMO
https://github.com/nicolas-mangini/esp32-rc-car-mod/assets/72108522/c88e2a87-3ad3-4a92-a44b-5ae4985a6168

## Conclusión
Mediante la combinación de componentes electrónicos y el desarrollo de software, se logró crear un sistema que permite controlar el auto a través de una interfaz web. El uso de un puente H L298N para el manejo de los motores, una fuente DC-DC Step Down para la alimentación, y un LDR para el control automático de las luces, son aspectos destacados del proyecto.

El resultado final es un auto a control remoto funcional y versátil, que puede ser controlado de manera intuitiva desde cualquier dispositivo con conexión a la interfaz web. Este proyecto demuestra la integración exitosa de hardware y software en la construcción de un sistema de control remoto utilizando el ESP32 como plataforma principal.
![AUTO](https://github.com/nicolas-mangini/esp32-rc-car-mod/assets/72108522/e764bb63-d8ab-4a1d-9f82-f43eed08af62)
