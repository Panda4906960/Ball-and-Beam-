#include <Servo.h>
Servo myservo; 
long val, duration;
const int sensordistancia = A0;  
float lectura, cm, angulo;
int D_cm;   
double Setpointpos, Setpointvel;
float Lecturas [100]; 
float Vel;float suma;

int i,n;
float Output1;
float Output2;

void setup()  
{
myservo.attach(7);
Serial.begin(9600);
myservo.write(90);
delay(50);  
Setpointpos = 19;
Setpointvel = 0;
}

void loop()  
{
  long tiempo=millis(); //tiempo antes de iniciar la lectura
  D_cm=distancia(10); 
 // D_cm=D_cm*10;
  tiempo=millis()-tiempo; //milisegundos que duró la lectura
  Lecturas[i] = cm; 
  Vel = (Lecturas[i] - Lecturas[i + 1]); 
  int Controlador [2][2] = {
  {-20.0000, -11.0000},
  {0.0000, 5.0000}}; 

  //{-3.6013, -6.0302},
  //{1.0000, 0.0000}}; 
  
  float Input1= Setpointpos - cm;
  float Input2= Setpointvel - Vel;
  
  float Input [2][1] = {
  {Input1},
  {Output2}};
  
  Output1 = Controlador[0][0]*Input[0][0] + Controlador[0][1]*Input[1][0];
  Output2 = Controlador[1][0]*Input[0][0] + Controlador[1][1]*Input[1][0];
  
  float Output [2][1] = {
  {Output1},
  {Output2}};
  Serial.println(Output[0][0]);
  val = map(Output[0][0], -360, 360,1700 , 1100);
  val=val+Setpointpos;
  if(val<=1700 && val>=1100){
        myservo.writeMicroseconds(val);
  }
  else{
      if(val>1700){
             myservo.writeMicroseconds(1600);
      }
      else{
           if(val<1100){
             myservo.writeMicroseconds(1300);
           }
      }
  }
 Serial.print(Setpointpos-cm);
  Serial.print(" ");
  Serial.print(val);
  Serial.println(" ");
}

float distancia(float n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    lectura = analogRead(sensordistancia); // lectura del sensor 0
    suma=suma+lectura;
  }  
  float adc=suma/n;
  cm = pow(3027.4 / adc, 1.2134); // conversión a centímetros
  return(cm);
}
