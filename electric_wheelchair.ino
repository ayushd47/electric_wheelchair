int xpin=0;
int ypin=1;
//int cklickypin=8;
//3 and  9 pins for PWM 
int motorRpin=9;
int motorLpin=3;
//*dont change* 3 and 9 are PWM on different frequency and work with the same level of hirtz
float motorRout=0;
float motorLout=0;
float x;
float y;
float Nx;
float Ny;
//int cklickystate=0;
float RmotorRout=63;
//one motor was connected the other way around
float RmotorLout=254;
void setup()
{
  Serial.begin(9600);
  //pinMode(cklickypin,INPUT);
  pinMode(xpin,INPUT);
  pinMode(ypin,INPUT);
  pinMode(motorRpin,OUTPUT);
  pinMode(motorLpin,OUTPUT);
}
void loop()
{
  //cklickystate=digitalRead(cklickypin);
 // Serial.println(cklickystate);
 
    x=analogRead(xpin);
    y=analogRead(ypin);
    Serial.print("x:");
    Serial.println(x);
    Serial.print("y:");
    Serial.println(y);
    if (x<530&&x>490)//dead zone in case there is a small unintentional movement
    {
      x=512;
    }
    if(y<530&&y>490)
    {
      y=512;
    }
    Serial.print("x:");
    Serial.println(x);
    Serial.print("y:");
    Serial.println(y);
    //agents the range of values to make arcade easier
    Nx=x-512;
    Ny=y-512;
    //y is left right 0 is left xis forward back 0 is back
    //arcade drive
    motorRout=Nx+Ny;
    Serial.print("NX");
    Serial.println(Nx);
    Serial.print("Ny");
    Serial.println(Ny);
    motorLout=Ny-Nx;
    /*remaps the vlause to match the range of the Sparks */
    RmotorRout=map(motorRout,-512,512,254,63);
    RmotorLout=map(motorLout,-512,512,63,254);
    Serial.print("motorRout");
    Serial.println(motorRout);
    Serial.print("motorLout");
    Serial.println(motorLout);
    RmotorRout=RmotorRout+30;//the value that makes the sparks stop moving is 30 away from the middle of the range witch is when the joystick is in the middle.
    RmotorLout=RmotorLout+30;
    /*if the Spark gets a value out side its possible range it 
  will not work at all so this part rounds the
  values in to the range.*/ 
    if(RmotorLout>254)
    {
      RmotorLout=254;
    }
    if(RmotorRout>254)
    {
      RmotorRout=254;
    }
    if(RmotorLout<63)
    {
      RmotorLout=63;
    }
    if(RmotorRout<63)
    {
      RmotorRout=63;
    }
    /*outputs the value to the motors and prints them to the
    screen*/
    analogWrite(motorRpin,RmotorRout);
    analogWrite(motorLpin,RmotorLout);
    Serial.print("motor L out");
    Serial.println(RmotorLout);
    Serial.print("motor R out");
    Serial.println(RmotorRout);
    Serial.println("");
  delay(200);
}     
