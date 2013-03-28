/*
 Mide la temperatura con el sensor NTC. Basado en:
 Tutorial # 0005 Arduino Academy - Sensor NTC
 http://www.arduteka.com/2011/12/tutorial-arduino-0005-sensor-de-temperatura-ntc/

 Author: F. Tricas, basado en el trabajo de
 Author: Pablo Murillo
 Conectamos una NTC a una entrada
 analógica.

 Este proyecto es de dominio público.
 */

//Añadimos la librería math.h
#include <math.h>

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Begin ArduinoPi shield code
//Include ArduPi library
#include "arduPi.h"

SerialPi Serial;

//Needed for accesing GPIO (pinMode, digitalWrite, digitalRead, I2C functions)
WirePi Wire;

//Needed for SPI
SPIPi SPI;

/*********************************************************
 *  IF YOUR ARDUINO CODE HAS OTHER FUNCTIONS APART FROM  *
 *  setup() AND loop() YOU MUST DECLARE THEM HERE        *
 * *******************************************************/
// End ArduinoPi shield code



//Pines para los LED
int pinLed1 = 8;
int pinLed2 = 9;
int pinLed3 = 10;
int pinLed4 = 11;
int pinLed5 = 12;

//Pines para las entradas analógicas
int analogPin1 = 0;

//Datos para las ecuaciones

float Vin = 5.0;      // [V]       Tensión alimentación del divisor
float Rfija = 1000;   // [ohm]     Resistencia fija del divisor
float R25 = 2800;     // [ohm]     Valor de NTC a 25ºC
float Beta = 3950.0;  // [K]      Parámetro Beta de NTC
float T0 = 273.15+25; // [K]       Temperatura de referencia en Kelvin

float reading=0.0;

float Vout = 0.0;    // [V]       Variable para almacenar Vout
float Rntc = 0.0;    // [ohm]     Variable para NTC en ohmnios

float TempK = 0.0;   // [K]       Temperatura salida en Kelvin
float TempC = 0.0;   // [ºC]      Temperatura salida en Celsius

void setup() {

  //Declaramos pines de salida
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinLed4, OUTPUT);
  pinMode(pinLed5, OUTPUT);

  //Declaramos el pin de entrada
  pinMode(analogPin1, INPUT);

}

float tempLoop(int verbose)
{
  //Calculamos la Temperatura

  //Primero la Vout del divisor
  reading=analogRead(analogPin1);

  //Ahora la resistencia de la NTC
  Rntc=Rfija/((1024/reading) -1);

  //Y por último la temperatura en Kelvin
  TempK = Beta/(log(Rntc/R25)+(Beta/T0));

  //Y ahora la pasamos a celsius
  TempC = TempK-273.15;

  //Y lo mostramos 
  if (verbose) {
	  printf("\n");
	  printf("NTC Temperature: ");
	  printf("%f", TempC);
	  printf(" DEGREES CELSIUS");
	  printf("\n");
  }

  digitalWrite(pinLed1, HIGH);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);
  digitalWrite(pinLed4, LOW);
  digitalWrite(pinLed5, LOW);

  //Un pequeño delay para no volver loco al puerto serie
  delay(500);

  //Devolver el valor
  return(TempC);
}

int main (int argc, char *argv[]){
	int i=0;
	int verbose=0;
	float tempNTC=0.0;
	
	if (argc>1) {
		if (argv[1][1]=='v') {
			verbose=1;
		}
		else
		{
			printf("Usage: %s [-v]\n", argv[0]);
			exit(1);
		}
	}


	setup();
	while(i<5){
		tempNTC=tempNTC+tempLoop(verbose);
		i++;
	}
	if (verbose)
		printf("\nTemperatura: %f\n", tempNTC/i);
	else
		printf("%f\n", tempNTC/i);

	return (0);
}
