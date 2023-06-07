
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <math.h>

#define dirX 5     // pin D5 Uno arduino
#define stepX 2    //pin D2 Uno arduino
#define dirY 6
#define stepY 3
#define dirZ 7
#define stepZ 4
#define en 8 

long speed1,speed2,speed3;
long positions[3]; // Array of desired stepper positions 

float dem,x,y,L=300;
float l1=75.0;
float l2=250.0;
float l3=250.0;
int x0=90,y0=-84,z0= 138;
float lech_but=40;
String input="      " ;
String siz=" ";
String hang=" ";
String cot=" ";
char ki_tu;
int col=0,row=0,sizechess=0;

//float Px, Py, Pz, x, y;
AccelStepper StepperX(1, stepX, dirX); //1 là chế độ dùng Driver
AccelStepper StepperY(1, stepY, dirY); //1 là chế độ dùng Driver
AccelStepper StepperZ(1, stepZ, dirZ); //1 là chế độ dùng Driver
MultiStepper steppers;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_begin_position() {
  StepperX.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Y là 0
  //Cho động cơ X chạy ra đúng vị trí ban đầu
  StepperX.moveTo(0*2*8.888888889); // 866 cần thực nghiệm lại để xác định chính xác
  StepperX.runToPosition(); //chạy đến vị trí đã set
  delay(1000);
  StepperY.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Y là 0
  //Cho động cơ Y chạy ra đúng vị trí ban đầu
  StepperY.moveTo(26*3*8.888888889); // 866 cần thực nghiệm lại để xác định chính xác
  StepperY.runToPosition(); //chạy đến vị trí đã set
  delay(1000);
  StepperZ.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Y là 0
  //Cho động cơ Z chạy ra đúng vị trí ban đầu
  StepperZ.moveTo(5*3*8.888888889); // -267 cần thực nghiệm lại để xác định chính xác
  StepperZ.runToPosition(); //chạy đến vị trí đã set
  delay(100);
   
   /* StepperY.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Y là 0
    StepperZ.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Z là 0
    
    positions[0] = 0;
    positions[1] = 31*8.8888888889*3.75;
    positions[2] = 31*8.8888888889*3.75;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition(); // Blocks until all are in position
    delay(1000);
     positions[2] = 31*8.8888888889*3.75;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition(); // Blocks until all are in position
    delay(1000);*/
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  pinMode(en, OUTPUT);
  set_vantoc_3_Step(500,500,500);
  set_giatoc_3_Step(1000,1500,1500);
/////////////////////////////////////////////////////
  //Start 
  Serial.begin(9600);
  Serial.print("Nhập <1> nếu bạn muốn ROBOT bắt đầu chạy= ");
  while (Serial.available() == 0) {}     //wait for data available
  String str5 = Serial.readString();  //read until timeout
  str5.trim();                        // remove any \r \n whitespace at the end of the String
  Serial.println(str5);
  if(str5=="1"){
    set_begin_position();
  } 

  ///////////////////////////////////////////////////
  // Give stepX,Y,Z to MultiStepper to manage
  steppers.addStepper(StepperX);
  steppers.addStepper(StepperY);
  steppers.addStepper(StepperZ);
  digitalWrite(en, LOW);
  ////////////////////////////////////////////////////
  /*// Nhap speed stepX
  Serial.print("Nhập vận tốc bàn quay(stepX) = ");
  while (Serial.available() == 0) {}     //wait for data available
  String str6 = Serial.readString();  //read until timeout
  str6.trim();                        // remove any \r \n whitespace at the end of the String
  speed1 = atoi(str6.c_str());
  Serial.println(speed1);*/

}

void loop()   // Driver: 1/16 step , Motor 1.8' => 3200 bước = 1 vòng 360'
{  
    Serial.println(" NHAP : SIZ_POS_X(O) (EX: 3_11_X) ");
    while (Serial.available()==0);
    input=Serial.readString();
    siz[0]=input[0];
    hang[0]=input[2];
    cot[0]=input[3];
    ki_tu= input[5];
    sizechess=siz.toInt();
    col=cot.toInt();
    row=hang.toInt();
    Serial.println(sizechess);
    Serial.println(col);
    Serial.println(row);
    delay(500);
    if (ki_tu=='X')
    {
    draw_X();
    }
    if (ki_tu=='O')
    {
    draw_O(sizechess,col,row);
    }
    delay(500);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_O(int siz,int col,int row)
{
  int tamX= ((L/siz)*col -L/(2*siz) )-150 ;   
  int tamY= (L/siz)*row -L/(2*siz)+120  ;
  float R= 0.50*float(L/(2*siz));
  
  float px=0,py=0,pz=75,c1=0,s1=0,c2=0,s2=0,c3=0,s3=0,A,B,goc_lech,l_lech,them;
  float t1=0,t2=0,t3=0;
  StepperX.setCurrentPosition(0); //Set vị trí hiện tại của động cơ X là 0
  StepperY.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Y là 0
  StepperZ.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Z là 0
  for (float t = 0 ; t <= 2*PI + 0.1; t = t + 0.08)
  {  
      if(t==0){
        set_vantoc_3_Step(500,500,500);
        set_giatoc_3_Step(2000,3500,3500);
      }
      if(t>0){
         set_vantoc_3_Step(100,150,150);
         set_giatoc_3_Step(800,1000,1000);
      }
      if ( row ==1 ){
        them=2;
        }
      if (row!=1) {
        them=0;
        }
      
      px = tamX +R*cos(t);
      py = tamY +R*sin(t);

      l_lech= sqrtf((px*px)+(py*py));
      goc_lech= atan2(lech_but,l_lech);
      goc_lech= goc_lech *180/PI;
      Serial.print("Goc lech = ");
      Serial.println(goc_lech);
      t1 = atan2(py,px);
      c1= cos(t1);
      s1= sin(t1);      
      A= px /c1;
      B= pz-l1;

      c3= (sq(A) +sq(B) -sq(l2) - sq(l3))/(2*l2*l3);
      s3 = sqrtf(abs(1-sq(c3)));
      t3= atan2(s3,c3);

      c2= (A*(l2 +l3*c3 )+ B*l3*s3)/(sq(l2+l3*c3) +sq(l3*s3));
      s2 = (B*(l2+l3*c3)- A*l3*s3)/(sq(l2+l3*c3) +sq(l3*s3));
      t2= atan2(s2,c2);
      Serial.println(t2);
      t1=(t1*180/PI)-x0+goc_lech;
      t2=(t2*180/PI)-y0;
      t3=(t3*180/PI)-z0-them;
      Serial.print("Goc theta 1 = ");
      Serial.println(t1);
      Serial.print("Goc theta 2 = ");
      Serial.println(t2);
      Serial.print("Goc theta 3 = ");
      Serial.println(t3);
      //tinh toan goc quay//
      positions[0] = t1*8.8888888889*2;
      positions[1] = t2*8.8888888889*3;
      positions[2] = t3*8.8888888889*3;
      steppers.moveTo(positions);
      steppers.runSpeedToPosition(); // Blocks until all are in position
      if ( row ==1 ){
        pz=115;
        }
      if (row!=1) {
        pz= 117;
        }
      
      if (t==0) delay(1000);
  }
  delay(1000);
  Go_back();
}


   /* 
    Nhap_toa_do_matrix();
    
    //Robot hạ bút để viết
    int angle_pen=5;
    StepperY.moveTo( (t2+angle_pen)*8.8888888889*3); //<cần thực nghiệm lại để xác định chính xác>
    StepperY.runToPosition(); //chạy đến vị trí đã set
    delay(1000);
     for(float t=0;t<=2*PI;t=t+0.01)
  {
    /// Code đánh O|X
    Danh_O(t);
  }
    //Back 
    Go_back();
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_X()
{
  StepperX.setCurrentPosition(0); //Set vị trí hiện tại của động cơ X là 0
  StepperY.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Y là 0
  StepperZ.setCurrentPosition(0); //Set vị trí hiện tại của động cơ Z là 0
  draw_phai(sizechess,col,row);
  Serial.print("XONG1/////////////////////////////////////////////////////////////////////////////////////////");
  draw_trai(sizechess,col,row);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_phai(int siz,int col,int row)
{
  float d= 0.5*float(L/(2*siz)); //giam kich thuoc chu x
  float xa= (L/siz)*(col-1)+d;
  float xb= (L/siz)*col-d;
  float ya=(L/siz)*(row-1)+d;
  float yb= (L/siz)*row -d ;
  Serial.println(xa);
  Serial.println(xb);
  Serial.println(ya);
  Serial.println(yb);
  float px=0,py=0,pz=75,c1=0,s1=0,c2=0,s2=0,c3=0,s3=0,A,B,goc_lech,l_lech,them;
  float t1=0,t2=0,t3=0;
  for (float t = 0 ; t <= 1; t = t + 0.09)
  { 
    if(t==0){
        set_vantoc_3_Step(500,500,500);
        set_giatoc_3_Step(2000,3500,3500);
      }
      if(t!=0){
        pz= 120;
         set_vantoc_3_Step(100,150,150);
         set_giatoc_3_Step(800,1000,1000);
      } 
      if ( row ==1 ){
        them=6;
       
        }
      if (row!=1) {
        them=0;
        }
    px =(xa) +(xb-xa)*t-150;   
    py =(ya) +(yb-ya)*t+120; 

    l_lech= sqrtf((px*px)+(py*py));
    goc_lech= atan2(lech_but,l_lech);
    goc_lech= goc_lech *180/PI;
    Serial.print("Goc lech = ");
    Serial.println(goc_lech);
    t1 = atan2(py,px);
    c1= cos(t1);
    s1= sin(t1);      
    A= px /c1;
    B= pz-l1;
    
    c3= (sq(A) +sq(B) -sq(l2) - sq(l3))/(2*l2*l3);
    s3 = sqrtf(abs(1-sq(c3)));
    t3= atan2(s3,c3);
    
    c2= (A*(l2 +l3*c3 )+ B*l3*s3)/(sq(l2+l3*c3) +sq(l3*s3));
    s2 = (B*(l2+l3*c3)- A*l3*s3)/(sq(l2+l3*c3) +sq(l3*s3));
    t2= atan2(s2,c2);
    t1=(t1*180/PI)-x0+goc_lech;
    t2=(t2*180/PI)-y0;
    t3=(t3*180/PI)-z0-them;
    Serial.print("Goc theta 1 = ");
    Serial.println(t1);
    Serial.print("Goc theta 2 = ");
    Serial.println(t2);
    Serial.print("Goc theta 3 = ");
    Serial.println(t3);
    //tinh toan goc quay//
    positions[0] = t1*8.8888888889*2;
    positions[1] = t2*8.8888888889*3;
    positions[2] = t3*8.8888888889*3;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition(); // Blocks until all are in position
    if(t==0){
      delay(1000);
      //Ha_but
      }
    
  }  
  Nang_ha_but(t2);  
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_trai(int siz,int col,int row)
{
  float d= 0.5*float(L/(2*siz)); //giam kich thuoc chu x
  float xa= (L/siz)*(col-1)+d;
  float xb= (L/siz)*col-d;
  float ya=(L/siz)*(row-1)+d;
  float yb= (L/siz)*row -d ;
  float px=0,py=0, pz=90,c1=0,s1=0,c2=0,s2=0,c3=0,s3=0,A,B,goc_lech,l_lech,them;
  float t1=0,t2=0,t3=0;
  for (float t = 0 ; t <= 1; t = t + 0.09)
  {  
    if(t==0){
        set_vantoc_3_Step(500,500,500);
        set_giatoc_3_Step(2000,3500,3500);
      }
      if(t!=0){
         pz= 120;
         set_vantoc_3_Step(120,150,150);
         set_giatoc_3_Step(800,1000,1000);
      }
      if ( row ==1 ){
        them=6;
        }
      if (row!=1) {
        them=0;
        }
    px =(xa) +(xb-xa)*t-150;   
    py =(yb) +(ya-yb)*t+120; 
    
    l_lech= sqrtf((px*px)+(py*py));
    goc_lech= atan2(lech_but,l_lech);
    goc_lech= goc_lech *180/PI;
    Serial.print("Goc lech = ");
    Serial.println(goc_lech);
    t1 = atan2(py,px);
    c1= cos(t1);
    s1= sin(t1);      
    A= px /c1;
    B= pz-l1;
    
    c3= (sq(A) +sq(B) -sq(l2) - sq(l3))/(2*l2*l3);
    s3 = sqrtf(abs(1-sq(c3)));
    t3= atan2(s3,c3);
    
    c2= (A*(l2 +l3*c3 )+ B*l3*s3)/(sq(l2+l3*c3) +sq(l3*s3));
    s2 = (B*(l2+l3*c3)- A*l3*s3)/(sq(l2+l3*c3) +sq(l3*s3));
    t2= atan2(s2,c2);
    t1=(t1*180/PI)-x0+goc_lech;
    t2=(t2*180/PI)-y0;
    t3=(t3*180/PI)-z0-them;
    Serial.print("Goc theta 1 = ");
    Serial.println(t1);
    Serial.print("Goc theta 2 = ");
    Serial.println(t2);
    Serial.print("Goc theta 3 = ");
    Serial.println(t3);
    //tinh toan goc quay//
    positions[0] = t1*8.8888888889*2;
    positions[1] = t2*8.8888888889*3;
    positions[2] = t3*8.8888888889*3;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition(); // Blocks until all are in position
    if(t==0){
      Serial.print("BAT_DAU/////////////////////////////////////////////////////////////////////////////////////////");
      delay(2000);
      //Ha_but
      }
  } 
   Nang_ha_but(t2);
   Go_back() ;  
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void Go_back(){
     set_vantoc_3_Step(900,900,900);
     set_giatoc_3_Step(3500,3500,2500);
     positions[0] = 0;
     positions[1] = 0;
     positions[2] = 0;
     steppers.moveTo(positions);
     steppers.runSpeedToPosition(); // Blocks until all are in position        
     delay(1000);
         
}
void Nang_ha_but(int h){ 
         h=h-5;    
         positions[1] = h*8.8888888889*3;
         steppers.moveTo(positions);
         steppers.runSpeedToPosition(); // Blocks until all are in position        
         delay(100);     
}

void set_vantoc_3_Step(int v_stepX,int v_stepY,int v_stepZ ){
  StepperX.setMaxSpeed(v_stepX);    
  StepperY.setMaxSpeed(v_stepY);    
  StepperZ.setMaxSpeed(v_stepZ);          
}
void set_giatoc_3_Step(int a_stepX,int a_stepY,int a_stepZ ){
   StepperX.setAcceleration(a_stepX);    
   StepperY.setAcceleration(a_stepY);    
   StepperZ.setAcceleration(a_stepZ);          
}
