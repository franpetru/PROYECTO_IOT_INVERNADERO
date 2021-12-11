 PROYECTO_IOT_INVERNADERO
  Sistema Embebido para monitoreo de Invernadero 
 El sistema embebido  Iot utiliza los siguientes componentes:
1. Microcontrolador ESP32 (4cuatro)
2. Protoboard(4 cuatro)
3. sensor de temperatura
4. sensor de humedad
5. Bomba de riego
6. Ventilador 
7. cables de conexion  hembra-hembra  x 10
8. fuente de alimentación
![Esp32](https://th.bing.com/th/id/R.6423a9b0bca3b44285b709db2947c69c?rik=NBUAI00TcVBEnQ&pid=ImgRaw&r=0)
 Descripción
 El sistema Iot son cuatro  nodos ESP32, que se conectan en una red wifi de area local, reportando la información a un servidor central ,enviando mensages por medio de node-red ,por otro lado se utiliza una Base de Datos Mysql para almacenar los datos , y finalmente una interfaz web con graficas de tendencia realizado en grafana.El sistema intercambia informacion con el servidor , sensando con los sensores de humedad y temperatura y accionando con los actuadores de bomba de riego y ventilacion .La comunicación se realiza por medio del protocolo MQTT, el cual envia los mensages al Broker del nodo.
![](https://mauropetrillo.com.ar/UTN_IOT_Grupo_5/Diagrama%20conexiones.JPG)
![](https://mauropetrillo.com.ar/UTN_IOT_Grupo_5/Conecciones%20del%20ESP32.jpeg)
 Implementación:
 Debera conectar su ESP32 y cargar el codigo "modulo.cpp"correspondiente para cada uno de los sensores o actuadores,debera ingresar de manera manual los datos de conexion : estos son nombre de la red wifi y contraseña ,para que el ESP32 pueda conectarse .
por otro lado copiar Y crear en su servidor la estructura de la Base de Datos proporcionada , en el software NODE-RED, importar el archivo JSON del FLow .
![](https://mauropetrillo.com.ar/UTN_IOT_Grupo_5/Flow%20nodered.JPG)
![](https://mauropetrillo.com.ar/UTN_IOT_Grupo_5/Columnas%20de%20la%20Base%20de%20Datos.jpeg)
![](https://mauropetrillo.com.ar/UTN_IOT_Grupo_5/Grafana.JPG)
![](https://mauropetrillo.com.ar/UTN_IOT_Grupo_5/Interface_dashboard.JPG)


