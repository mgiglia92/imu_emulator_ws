
#include <rcc.h>
unsigned long cur, prev;
unsigned long dt = 10000;
double a[100];
float val;
int index=0;

MPU6050 imu;
char ax[10];
char curstr[10];


const unsigned long dtbufflen = 100;
unsigned long dtbuff[dtbufflen];
unsigned long dtavg=0;
unsigned long dta;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(460800);
  cur = prev = micros();
//  Serial.println(ARR_LEN(a));
//  delay(1000);
imu.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  imu.update();
  cur = micros();
  dta = cur-prev;
  if (dt < dta) {
    
    dtbuff[index]=dta;
    if(index<100){index++;}else{index=0;}
    dtavg = get_avg(dtbuff, dtbufflen);
    ultoa(dtavg, curstr, 10);
    dtostrf(imu.getAccelX(), 4, 4, ax);
    Serial.print('$');
    Serial.print(ax);
    Serial.print('|');
    Serial.print(curstr);
    Serial.print('%');
    prev = cur;
  }
  
}

unsigned long get_avg(unsigned long *buf, int len)
{
  unsigned long avg=0;
  for(int i=0; i<len; i++)
  {
    avg = avg+buf[i];
  }
  avg = avg/len;
  return avg;
}