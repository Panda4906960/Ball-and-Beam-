#include <Servo.h> 
Servo myservo;

float alpha=0.5;  //siempre menor a 1
float s;
const int sensordistancia = A0;  
float lectura, suma;
float cm;
float D_cm; 

float kp =1.5;           //1.5
float kd = 20;    //20
float ki = 0.1;   //01

float error_previo;
float integral=0;
float derivative=0;
float output=0;
float error=0;
float salida=0;
float sp=180; 

unsigned long time = 0; // tiempo de ejecucion del ultimo ciclo
int period = 40; // Periodo de muestreo en ms

void setup() {
  Serial.begin(115200);
  myservo.attach(7);
}

void loop() {
  if (millis()>time+period){ // ¿Ha transcurrido el periodo?
      time = millis();

        //lectura de distancia
        D_cm=distancia(10); 
        D_cm=D_cm*10;
       //PARTE DEL PID
       error = sp - D_cm;
       
       if(error<1 && error>-1){
             error=0;
       }
       if(sp==0){
           integral=0;
       }
       if(integral>600){
            integral=600;
       }
       if(integral<0){
             integral=abs(integral);
       }
       integral=error+error_previo;
       output=kp*error+ki*integral+kd*(error-error_previo);
       error_previo=error;
       //FIN DE LA PARTE DEL PID

       //Validando la salida
       salida=output+1440;
       if(salida<=1600 && salida>=1200){
          myservo.writeMicroseconds(salida);
       }
       else{
           if(salida>1600){
              myservo.writeMicroseconds(1600);
           }
           else{
               if(salida<1200){
                   myservo.writeMicroseconds(1300);
               }
           }
       }
       //FIN DE LA SALIDA  
       Serial.println(D_cm);
  }    
}


float distancia(float n){
  
  suma=0;
  for(int i=0;i<n;i++)
  {
    lectura = analogRead(sensordistancia); // lectura del sensor 0
    //cm = 17569.7 * pow(lectura, -1.2062); // conversión a centímetros
    s=(alpha*lectura)+((1-alpha)*s); //donde y es ,i lectura
    suma=suma+s;
  }  
  
  float adc=suma/n;
  cm = 17569.7 * pow(adc, -1.2062); // conversión a centímetros
  return(cm);
}
