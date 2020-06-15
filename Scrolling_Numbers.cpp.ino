/*
Changes: On changing Mode, Scrolling will be continued without resetting.
Controls: 
SW1 -->For Hexadecimal Number
Sw2 ---> Left To Right Scroll
Sw3 ---> Pause Scrolling.
Sw4 ---> Right To Left Scroll
Sw5 ---> For Decimal Number
LDR ---> Reset(Start from zero)........................................................
Connections:
Pin 2 to Pin 5 ---> D4 To D1
Pin 6 to Pin 13 ---> A to Dp(SSD)
A2-->Switches
A3-->LDR
NOTE:-
1.Place Finger On LDR To Reset.....................................
2.SW1 and SW5 will Change mode without resetting.................................
*/
int dash =16;
int d1 =2;
int d2 =3;
int d3 =4;
int d4 =5;
int a =6;
int b =7;
int c =8;
int d =9;
int e =10;
int f =11;
int g =12;
int dp =13;
void setup() {
  for(int pin=2;pin<=13;pin++)
  {
pinMode(pin,OUTPUT);
}
}
int mode=2;//Mode=1 for Hexadecimal Number and Mode=2 for Decimal Number
int msb=0;//msb--> Number on D4 SSD
int sw=0;
int switch_val = 0;//Determines Which Switch is Pressed
void loop() {
if(mode==1){
  switch_val = analogRead(A2);
if(switch_val>815&&switch_val<825){mode=2;sw=2;}//switch 5...............................define physical location of switches also
//sw=(switch_val>681&&switch_val<686)*0+(switch_val>509&&switch_val<519)*1+(switch_val>766&&switch_val<776)*2;//Scroll Only While Switch is Pressed.
if(switch_val>681&&switch_val<686){sw=0;}// Switch 3
if(switch_val>509&&switch_val<519){sw=1;}//Switch 2 
if(switch_val>766&&switch_val<776){sw=2;}//Switch 4
if(analogRead(A3)<10){msb=0;sw=0;}
if(msb<=0){printall(0,1,2,3);}
if(msb>=1&&msb<=12){printall(msb,msb+1,msb+2,msb+3);}
if(msb==13){printall(13,14,15,1);}
if(msb==14){printall(14,15,1,0);}
if(msb==15){printall(15,1,0,1);}
if(msb>=16&&msb<=251){
  //for 2 digit Numbers.Extracting Bits.
  int h1= msb;
  int h2 =msb+1;
  int h3 = msb+2;
  int h4 = msb-1;
  int hd1 = h1/16;
  int hd2 = h1%16;
  int hd3 = h2/16;
  int hd4 = h2%16;
  int hd5 = h3/16;
  int hd6 = h4%16;
  if(sw==0){printall(dash,hd1,hd2,dash);}
 if(sw==2){printall(hd1,hd2,dash,hd3);
  printall(hd2,dash,hd3,hd4);
  printall(dash,hd3,hd4,dash);}
  if(sw==1){printall(hd1,hd2,dash,hd3);
  printall(dash,hd1,hd2,dash);
  printall(hd6,dash,hd1,hd2);}
  }
 if(msb==252){printall(15,12,15,13);printall(12,15,13,15);}
 if(msb==253){printall(15,13,15,14);printall(13,15,14,15);}
 if(msb==254){printall(15,14,15,15);}
 if(sw==0){}
 if(sw==1){msb--;if(msb==0){sw=0;}}
 if(sw==2){msb++;if(msb==255){sw=0;msb=254;}}
}
if(mode == 2){
  switch_val = analogRead(A2);
if(switch_val>=0&&switch_val<15){mode=1;sw=2;}
//sw=(switch_val>681&&switch_val<686)*0+(switch_val>509&&switch_val<519)*1+(switch_val>766&&switch_val<776)*2;//Scroll Only when Switch is pressed.
if(switch_val>681&&switch_val<686){sw=0;}
if(switch_val>509&&switch_val<519){sw=1;}
if(switch_val>766&&switch_val<776){sw=2;}
if(analogRead(A3)<10){msb=0;sw=0;}
if(msb<1){printall(0,1,2,3);}
if(msb>=1&&msb<7){
printall(msb,msb+1,msb+2,msb+3);}
if(msb==7){printall(7,8,9,1);}
if(msb==8){printall(8,9,1,0);}
if(msb==9){printall(9,1,0,1);}/////////////////1 replaced by dash
if(msb>=10&&msb<98){
  int k1 =msb;
  int k2 =msb+1;
  int k3 = msb+2;
  int k4 = msb-1;
  int c1 = k1/10;
  int c2 = k1%10;
  int c3 = k2/10;
  int c4 = k2%10;
  int c5 = k3/10;
  int c6 = k4%10;
  if(sw==0){printall(dash,c1,c2,dash);}
  if(sw==2){printall(c1,c2,dash,c3);
  printall(c2,dash,c3,c4);
  printall(dash,c3,c4,dash);}
  if(sw==1){printall(c1,c2,dash,c3);
  printall(dash,c1,c2,dash);
  printall(c6,dash,c1,c2);}
  
  }
  if(msb==98){printall(9,8,dash,9);
  printall(8,dash,9,9);
  printall(dash,9,9,dash);}
//  printall(8,9,9,1);}
 if(msb==99){printall(9,9,dash,1);
 printall(9,dash,1,0);}
 if(msb>=100){printall(dash,1,0,0);}
 if(sw==0){}
 if(sw==1){msb--;if(msb==0){sw=0;}}
 if(sw==2){msb++;if(msb==100){sw=0;}}
}
}
void printall(int q,int w,int e,int r){
  for(int msb=0;msb<15;msb++){
  print1(q,2);//Prints at D4
  print1(w,3);// For D3
  print1(e,4);//For D2
  print1(r,5);//For D1
}}
void print1(int x , int digit)
{for(int msb=0;msb<5;msb++)
{
  digitalWrite(2,digit==2);
  digitalWrite(13,mode==2 && digit==2);
  digitalWrite(3,digit==3);
  digitalWrite(13,mode==1 && digit==3);
  digitalWrite(4,digit==4);
  digitalWrite(5,digit==5);
digitalWrite(a,!(x==1 ||x==4 ||x==11 ||x==12 ||x==13||x==16));
digitalWrite(b,!(x==5 ||x==6 ||x==11 ||x==12 ||x==15||x==16));
digitalWrite(c,!(x==2 ||x==12 ||x==14||x==15||x==16));
digitalWrite(d,!(x==1 ||x==4 ||x==7 ||x==9  ||x==15||x==16));
digitalWrite(e,!(x==1 ||x==3 ||x==4 ||x==5 ||x==7 ||x==9||x==16));
digitalWrite(f,!(x==1 ||x==2 ||x==3 ||x==7 ||x==10||x==12 ||x==13||x==16));
digitalWrite(g,!(x==0 ||x==1 ||x==7));
delay(1);
}}

