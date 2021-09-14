/*=============================================================*/
#define motor1a 5
#define motor1b 6
#define motor2a 9
#define motor2b 10
#define led 13
int dif=360;
bool flag;  

void setup() {
   pinMode(motor1a, OUTPUT);
   pinMode(motor1b, OUTPUT);
   pinMode(motor2a, OUTPUT);
   pinMode(motor2b, OUTPUT);
   pinMode(led,OUTPUT);
   Serial.begin(9600);
   digitalWrite(led,1);  
   delay(3600);
}

void loop() {
  q0();
  //Calibrar();
}

/*======================== AUTOMATA 1 =========================*/
void R1(){
  
  if(sensorIF()>dif){
     Adelante(255);
    (flag)?flag=false:flag=true;    
  }
  if(flag)Right(180);
  if(!flag)Left(180);
}
/*========================= AUTOMATA 2 ========================*/
void q0(){
  if(!sensorLeft()&&!sensorRight()){
    q1();  
  } 
}
void q1(){
  if(sensorIF()>dif){
    Adelante(255);
    q1();
  }else{
    (flag)?flag=false:flag=true;
    q2();
  }
}
void q2(){
  if(sensorIF()<=dif){
    if(sensorLeft()||sensorRight()){
      q4();
    }else{
      q3();
    }
  }else{
    q1();
  }
}
void q3(){
  if(flag){
    Left(180);
    q2(); 
  }else{
    Right(180);
    q2();
  }
}
void q4(){
  if(sensorLeft()){
    AtrasI(180);
  }
  if(sensorRight()){
    AtrasD(180);
  }
  q2();
}
/*============================= AUTOMATA 3 =======================*/
void w0(){
  Adelante(200);
  delay(500);
  if(!sensorLeft()&&!sensorRight()){
    w1();  
  } 
}
void w1(){
  if(sensorIF()<50){
    Adelante(255);
    w1();
  }else{
    (flag)?flag=false:flag=true;
    w2();
  }
}
void w2(){
  if(sensorIF()>=50){
    if(sensorLeft()||sensorRight()){
      w4();
    }else{
      w3();
    }
  }else{
    w1();
  }
  
}
void w3(){
  if(flag){
    Left(180);
    w2(); 
  }else{
    Right(180);
    w2();
  }
}
void w4(){
  if(sensorLeft()){
    AtrasI(150);
  }
  if(sensorRight()){
    AtrasD(150);
  }
  w2();
}
/*============================= SENSORES ==============================*/
int sensorIF(){
  return (dist(20));
}
int dist(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A3);
  }  
  return(suma/n);
}
bool sensorRight(){
  if(sensorSR()<200){
    return (true);
  }else{
    return (false);  
  }
}
bool sensorLeft(){
  if(sensorSL()<200){
    return (true);
  }else{
    return (false);  
  }
}
int sensorSR(){
  return (analogRead(A4));
}
int sensorSL(){
  return (analogRead(A5));
}
void Calibrar(){
  Serial.print("distancia: ");
  Serial.print(sensorIF());
  Serial.print("cm ");
  Serial.print(" sensorRight: ");
  Serial.print(sensorSR());
  Serial.print(" ");
  Serial.print(sensorRight());
  Serial.print(" sensorLeft: ");
  Serial.print(sensorSL());
  Serial.print(" ");
  Serial.print(sensorLeft());
  Serial.println(" ");    
}
/*============================= MOVIMIENTOS ======================*/
void Atras(int vel){
   analogWrite(motor1a,vel);
   digitalWrite(motor1b,0);
   analogWrite(motor2a,vel);
   digitalWrite(motor2b,0);
}
void Adelante(int vel){
   digitalWrite(motor1a,0);
   analogWrite(motor1b,vel);
   digitalWrite(motor2a,0);
   analogWrite(motor2b,vel);
}
void Right(int vel){
   digitalWrite(motor1a,0);
   analogWrite(motor1b,vel);
   analogWrite(motor2a,vel);
   digitalWrite(motor2b,0);
}
void Left(int vel){
   analogWrite(motor1a,vel);
   digitalWrite(motor1b,0);
   digitalWrite(motor2a,0);
   analogWrite(motor2b,vel);
}
void AdelanteI(int vel){
   analogWrite(motor1a,vel);
   digitalWrite(motor1b,0);
   digitalWrite(motor2a,0);
   digitalWrite(motor2b,0);
}
void AdelanteD(int vel){
   digitalWrite(motor1a,0);
   digitalWrite(motor1b,0);
   analogWrite(motor2a,vel);
   digitalWrite(motor2b,0);
}
void AtrasI(int vel){
   digitalWrite(motor1a,0);
   analogWrite(motor1b,vel);
   digitalWrite(motor2a,0);
   digitalWrite(motor2b,0);
}
void AtrasD(int vel){
   digitalWrite(motor1a,0);
   digitalWrite(motor1b,0);
   digitalWrite(motor2a,0);
   analogWrite(motor2b,vel);
}
void Stop(){
   digitalWrite(motor1a,0);
   digitalWrite(motor1b,0);
   digitalWrite(motor2a,0);
   digitalWrite(motor2b,0);
}
/*=============================================================*/
