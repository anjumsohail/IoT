int display[]={2,3,4,5,6,7,8};  
// For Common Anode
int numStat1[10][7]={
{1,1,1,1,1,1,0},  
{0,1,1,0,0,0,0},
{1,1,0,1,1,0,1},
{1,1,1,1,0,0,1},
{0,1,1,0,0,1,1},
{1,0,1,1,0,1,1},
{1,0,1,1,1,1,1},
{1,1,1,0,0,0,0},
{1,1,1,1,1,1,1},
{1,1,1,1,0,1,1}
};


// For Common Anode
int numStat2[10][7]={
{0,0,0,0,0,0,1},  
{1,0,0,1,1,1,1},
{0,0,1,0,0,1,0},
{0,0,0,0,1,1,0},
{1,0,0,1,1,0,0},
{0,1,0,0,1,0,0},
{0,1,0,0,0,0,0},
{0,0,0,1,1,1,1},
{0,0,0,0,0,0,0},
{0,0,0,0,1,0,0}
};


int counter=0;
int previousButtonState = LOW;
void setup() {


  pinMode(13,INPUT_PULLUP);
  for (int i=0; i<7; i++){        
    pinMode(display[i], OUTPUT);}


displayDigit(0);  
 Serial.begin(9600);
}


void loop(){






  for (int i=0;i<=9;i++)
  {
    //Serial.println(digitalRead(13));
  displayDigit(i);
  Serial.println(i);
    delay(1000);


   
  }
 
}
void displayDigit(int num)
{
  //Serial.print("Number to Display") ;
  // Serial.println(num);
    for (int i=0; i<7; i++){
  digitalWrite(display[i], numStat2[num][i]);
 // Serial.println(digitalRead(display[i]));
}}
