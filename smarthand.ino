#define nbvaleur 5   // one value for each finger 
#define digitsperval 1
#include <Servo.h>

Servo thumbfinger;  
Servo indexfinger;  
Servo middlefinger;  
Servo ringfinger;  
Servo pinkyfinger;



int valeurrecus[nbvaleur] ;  
int stringlength = nbvaleur * digitsperval +1 ; //$00000
int counter =0;
bool counterstart=false;    
String stringrecived ;  // this string will determinate the hand position 


/******************************************************************************************************************************/
void setup() {
 Serial.begin(9600);   // serial connexion  
  thumbfinger.attach(5);
  indexfinger.attach(6);
  middlefinger.attach(10); 
  ringfinger.attach(9);  
  pinkyfinger.attach(11);
  
}
/***************************************************loop*******************************************************************/
void loop() {
  recieveData();
  handmove(valeurrecus[0],valeurrecus[1],valeurrecus[2],valeurrecus[3],valeurrecus[4]) ;
  
  }
/**************************************************function*********************************************************************/
void recieveData() {
   while ( Serial.available() ) 
   {
    char c =Serial.read();  
      
     if (c=='$') {  //the first caracter should be  $ 
      counterstart=true;
     }
     if (counterstart==true) {
      //test  if we just reach the maximal string size ( equal to 6)
      if (counter < stringlength) {
        stringrecived = String(stringrecived +c); //add the caracter read 
        counter++;  //incriment the counter
      }
      if (counter >= stringlength) {   //kamalna 9rina el chaine bech n3abiwhom fel tableau we finish reading string then we start appending values to list 
        for ( int i=0 ; i<nbvaleur;i++) {
          int num = (i*digitsperval)+1 ;
          valeurrecus[i] = stringrecived.substring(num,num+1).toInt(); //lezem $00000 nekhdhou el valeur loula mel indice 1 w ahna mechin 
         }
         stringrecived="";  // remake parameteres to initial values 
         counter=0;         // remake parameteres to initial values 
         counterstart=false;// remake parameteres to initial values 
      }
     }
   }
}
/******************************************************************************************************************************/
void handmove(int e1,int e2,int e3,int e4,int e5) {
  thumbfinger.write(180*e1); 
  indexfinger.write(180*e2);
  middlefinger.write(180*e3);
  ringfinger.write(180*e4);
  pinkyfinger.write(180*e5);
  
  
}
