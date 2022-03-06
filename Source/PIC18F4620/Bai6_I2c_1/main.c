#include "main.h"
#define     LED     PORTD
#define     ON      1
#define     OFF     0

#define     NONE   0
#define     MODE1  1
#define     MODE2  2

#define     ADDRESS_SECOND  0x00
#define     ADDRESS_MINUTE  0x01
#define     ADDRESS_HOUR    0x02
#define     ADDRESS_DAY     0x03
#define     ADDRESS_DATE    0x04
#define     ADDRESS_MONTH   0x05
#define     ADDRESS_YEAR    0x06

#define     ADDRESS_WATER_MODE      0x08
#define     ADDRESS_MAX_VALUE       0x09

#define     FIRST_TURN              0
#define     ADDRESS_HOUR_SCHED1     0x0A
#define     ADDRESS_MINUTE_SCHED1   0x0B
#define     ADDRESS_ENABLE_SCHED1   0x0C
#define     ADDRESS_DURATION_SCHED1 0x0D
#define     ADDRESS_FRE_SCHED1      0x0E

#define     SECOND_TURN             1
#define     ADDRESS_HOUR_SCHED2     0x0F
#define     ADDRESS_MINUTE_SCHED2   0x10
#define     ADDRESS_ENABLE_SCHED2   0x11
#define     ADDRESS_DURATION_SCHED2 0x12
#define     ADDRESS_FRE_SCHED2      0x13

#define     THIRD_TURN              2
#define     ADDRESS_HOUR_SCHED3     0x14
#define     ADDRESS_MINUTE_SCHED3   0x15
#define     ADDRESS_ENABLE_SCHED3   0x16
#define     ADDRESS_DURATION_SCHED3 0x17
#define     ADDRESS_FRE_SCHED3      0x18

#define     FOURTH_TURN             3
#define     ADDRESS_HOUR_SCHED4     0x19
#define     ADDRESS_MINUTE_SCHED4   0x1A
#define     ADDRESS_ENABLE_SCHED4   0x1B
#define     ADDRESS_DURATION_SCHED4 0x1C
#define     ADDRESS_FRE_SCHED4      0x1D

#define     ADDRESS_REST_HOUR_BEGIN      0x1E
#define     ADDRESS_REST_MINUTE_BEGIN    0x1F
#define     ADDRESS_REST_HOUR_STOP       0x20
#define     ADDRESS_REST_MINUTE_STOP     0x21
#define     ADDRESS_MIN_VALUE            0x22
#define     ADDRESS_DURATION_M2          0x23

#define     ADDRESS_ENABLE_PASS    0x3B
#define     ADDRESS_PASS_1         0x3C
#define     ADDRESS_PASS_2         0x3D
#define     ADDRESS_PASS_3         0x3E
#define     ADDRESS_PASS_4         0x3F

char second = 0,minute = 0,hour = 0;
char day = 0;
char date = 0,month = 0,year = 0;
unsigned char count = 0;
char timewait = 0;
char Password [4]= {1,1,1,1};
unsigned char arrayPassword[4];
  

int minute_timer = 0,hour_timer = 0, bit_timer=0,fre_timer=0,dur_timer=0,max_humidity=0;
int fre_turn1=0,fre_turn2=0,fre_turn3=0,fre_turn4=0;
int minute_begin = 0,hour_begin = 0, minute_stop=0,hour_stop=0,min_humidity=0,dur_m2=0;
int old_day1=0,old_day2=0,old_day3=0,old_day4=0;
int duration_watering=0;
unsigned int count_1m=0;
unsigned char i;
unsigned int adcValue;
int humidityvalue;
int humiditystart;
void Get_humidity(void);
void Send_humidity(void);
void send_parameter(char* name,int temp);
void send_All_parameter(void);
void watering();

void init_system(void);
void delay_ms(int value);

void SetupTimeForRealTime();
//void BaiTap_I2C();
void Getmode();
void get_order();
void Check_condition();
void DisplayTimeandHum();
void DisplayTime();
void Security();
void Direction();
void Configpass();
void DisplayCustom_mode1();
void DisplayCustom_mode2();
void SetTime();
void Set_Custom_mode1();
void Set_Custom_mode2();


#define INIT_SYSTEM     0
#define SET_WATER_MODE  1
#define SET_HOUR        2
#define SET_MINUTE      3
#define SET_DAY         4
#define SET_DATE        5
#define SET_MONTH       6
#define SET_YEAR        7
#define EN_PASS         8


#define DISPLAY_MODE      0
#define PASS_MODE         1
#define CHOICE_DIRECTION  2
#define CONFIG_PASS       3
#define SET_TIME_MODE     4
#define CUSTOM_MODE_1     5
#define CUSTOM_MODE_2     6

#define INIT_SEC              0
#define ENTER_PASSWORD        1
#define CHECK_PASS            2
#define FORGOT_PASS           3
#define SEND_PASS             4

#define INIT_CM1        0
#define SET_TURN_CM1    1
#define SET_EN_CM1      2
#define SET_HOUR_CM1    3
#define SET_MINUTE_CM1  4
#define SET_DUR_CM1     5
#define SET_FRE_CM1     6
#define SET_MHV_CM1     7

#define INIT_CM2        0
#define SET_HB_CM2      1
#define SET_MB_CM2      2
#define SET_HS_CM2      3
#define SET_MS_CM2      4
#define SET_MHV_CM2     5
#define SET_DUR_CM2     6

#define COMPARE    0
#define WATERING   1



unsigned char ispress=0,timedouble=0,timepress=0,isfree=0;
int pressfunction=0, doubleclick=0,holdfunction=0;
void buttonfunction();
unsigned char isButtonMode();
unsigned char isButtonFuntion();
unsigned char isButtonBack();
unsigned char isButtonUp();
unsigned char isButtonDown();
unsigned char timeBlink = 0;
unsigned char statusMode =  DISPLAY_MODE;
unsigned char statusSetTime = INIT_SYSTEM;
unsigned char statusSecurity = INIT_SEC;
unsigned char statusChoice = 0;
unsigned char statusPassmode =0;
unsigned char statusChoicepass =0;
int statusenterpass = 0;
int statusenternewpass = 0;
int checkpass=1;
unsigned char statusSet_cm1 = INIT_CM1;
unsigned char status_watering = COMPARE;
unsigned char statusSet_cm2 = INIT_CM2;

char watermode = MODE2;

unsigned char statusTurn = FIRST_TURN;
unsigned int countuart=0;
int count_free_time=0;
void main(void)
{
    //unsigned int k = 0;
    init_system();
    lcd_clear();
    LcdClearS();
    delay_ms(1000);
    send_All_parameter();
    if(read_ds1307(ADDRESS_YEAR)==0){
        write_ds1307(ADDRESS_SECOND, '5');
        write_ds1307(ADDRESS_WATER_MODE, MODE2);
        write_ds1307(ADDRESS_ENABLE_PASS, ON);
        write_ds1307(ADDRESS_PASS_1, 1);
        write_ds1307(ADDRESS_PASS_2, 1);
        write_ds1307(ADDRESS_PASS_3, 1);
        write_ds1307(ADDRESS_PASS_4, 1);
    }
    
    while (1)
    {
        while (!flag_timer3);
        flag_timer3 = 0;
        scan_key_matrix_with_uart();
        buttonfunction();      
        Get_humidity();
        Send_humidity();
        Getmode();
        get_order();
        Check_condition();
        DisplayLcdScreen();
    }
}

void delay_ms(int value)
{
    int i,j;
    for(i = 0; i < value; i++)
        for(j = 0; j < 160; j++);
}

void init_system(void)
{
    TRISB = 0x00;		//setup PORTB is output
    TRISD = 0x00;
    init_lcd();
    LED = 0x00;
    init_interrupt();
    delay_ms(1000);
    init_timer0(4695);  //dinh thoi 1ms
    init_timer1(9390);  //dinh thoi 2ms
    init_timer3(46950); //dinh thoi 10ms
    SetTimer0_ms(2);
    SetTimer1_ms(10);
    SetTimer3_ms(50);   //Chu ky thuc hien viec xu ly input,proccess,output
    init_key_matrix_with_uart();
    init_uart();
    init_i2c();
    init_adc();
}

void Check_condition(){
    switch (status_watering){
        case COMPARE:
            watermode=read_ds1307(ADDRESS_WATER_MODE);
            switch(watermode){
                case NONE: break;
                case MODE1:
                    if(humidityvalue<read_ds1307(ADDRESS_MAX_VALUE)){
                    if(hour==read_ds1307(ADDRESS_HOUR_SCHED1)&&minute==read_ds1307(ADDRESS_MINUTE_SCHED1)&&second==0
                            &&read_ds1307(ADDRESS_ENABLE_SCHED1)==ON){
                        if(old_day1!=read_ds1307(ADDRESS_DATE)){
                            old_day1=read_ds1307(ADDRESS_DATE);
                            if(fre_turn1==0){
                                duration_watering=read_ds1307(ADDRESS_DURATION_SCHED1);
                                status_watering=WATERING;
                                humiditystart=humidityvalue;
                            }
                            fre_turn1=(fre_turn1+1)%(read_ds1307(ADDRESS_FRE_SCHED1));
                        }
                    }
                    if(hour==read_ds1307(ADDRESS_HOUR_SCHED2)&&minute==read_ds1307(ADDRESS_MINUTE_SCHED2)&&second==0
                            &&read_ds1307(ADDRESS_ENABLE_SCHED2)==ON){
                        if(old_day2!=read_ds1307(ADDRESS_DATE)){
                            old_day2=read_ds1307(ADDRESS_DATE);
                        if(fre_turn2==0){
                        duration_watering=read_ds1307(ADDRESS_DURATION_SCHED2);
                        status_watering=WATERING;
                        humiditystart=humidityvalue;
                        }
                        fre_turn2=(fre_turn2+1)%(read_ds1307(ADDRESS_FRE_SCHED2));
                        }
                    }
                    if(hour==read_ds1307(ADDRESS_HOUR_SCHED3)&&minute==read_ds1307(ADDRESS_MINUTE_SCHED3)&&second==0
                            &&read_ds1307(ADDRESS_ENABLE_SCHED3)==ON){
                        if(old_day3!=read_ds1307(ADDRESS_DATE)){
                            old_day3=read_ds1307(ADDRESS_DATE);
                        if(fre_turn3==0){
                        duration_watering=read_ds1307(ADDRESS_DURATION_SCHED3);
                        status_watering=WATERING;
                        humiditystart=humidityvalue;
                        }
                        fre_turn3=(fre_turn3+1)%(read_ds1307(ADDRESS_FRE_SCHED3));
                        }
                    }
                    if(hour==read_ds1307(ADDRESS_HOUR_SCHED4)&&minute==read_ds1307(ADDRESS_MINUTE_SCHED4)&&second==0
                            &&read_ds1307(ADDRESS_ENABLE_SCHED4)==ON){
                        if(old_day4!=read_ds1307(ADDRESS_DATE)){
                            old_day4=read_ds1307(ADDRESS_DATE);
                        if(fre_turn4==0){
                        duration_watering=read_ds1307(ADDRESS_DURATION_SCHED4);
                        status_watering=WATERING;
                        humiditystart=humidityvalue;
                        }
                        fre_turn4=(fre_turn4+1)%(read_ds1307(ADDRESS_FRE_SCHED4));
                        }
                    }}
                    break;
                case MODE2:
                    if(humidityvalue<read_ds1307(ADDRESS_MIN_VALUE)&&
                    (((hour==read_ds1307(ADDRESS_REST_HOUR_BEGIN)&&minute<read_ds1307(ADDRESS_REST_MINUTE_BEGIN))||(hour<read_ds1307(ADDRESS_REST_HOUR_BEGIN)))||
                    ((hour==read_ds1307(ADDRESS_REST_HOUR_STOP)&&minute>read_ds1307(ADDRESS_REST_MINUTE_STOP))||(hour>read_ds1307(ADDRESS_REST_HOUR_STOP)))))
                    {
                        duration_watering=read_ds1307(ADDRESS_DURATION_M2);
                        status_watering=WATERING;
                        humiditystart=humidityvalue;
                    }
                    break;
            }
            break;
        case WATERING:
            if(duration_watering<=0){
                if(humidityvalue<=humiditystart){
                  UartSendString("!warn#");  
                }
                duration_watering=0;
                status_watering=COMPARE;
            }else{
                count_1m++;
                if(count_1m>1200){
                    count_1m=0;
                    duration_watering--;
                }
                watering();
            }
            break;    
    }
}

void Getmode(){
    switch(statusMode){
        case DISPLAY_MODE:
            DisplayTimeandHum(); 
            if(isButtonMode()){
                pressfunction=0;
                statusMode=PASS_MODE;
                statusSecurity=INIT_SEC;}
            break;
        case PASS_MODE:
            count_free_time++;
            if(count_free_time>=200){
                count_free_time=0;
                statusMode=DISPLAY_MODE;
            }
            Security();
            break;
        case CHOICE_DIRECTION:
            count_free_time++;
            if(count_free_time>=200){
                count_free_time=0;
                statusMode=DISPLAY_MODE;
            }
            Direction();
            if(isButtonBack()) {doubleclick=0; statusMode=DISPLAY_MODE;}
            break;
        case CONFIG_PASS:
            count_free_time++;
            if(count_free_time>=200){
                count_free_time=0;
                statusMode=DISPLAY_MODE;
            }
            Configpass();
            if(isButtonBack()) {statusMode=CHOICE_DIRECTION;}
            if(isButtonMode())  {statusMode=DISPLAY_MODE;}
            break;
        case SET_TIME_MODE:
            count_free_time++;
            if(count_free_time>=200){
                count_free_time=0;
                statusMode=DISPLAY_MODE;
            }
            SetTime();
            if(isButtonBack()) {statusMode=CHOICE_DIRECTION;}
            if(isButtonMode())  {statusMode=DISPLAY_MODE;}
            break;
        case CUSTOM_MODE_1:
            count_free_time++;
            if(count_free_time>=200){
                count_free_time=0;
                statusMode=DISPLAY_MODE;
            }
            Set_Custom_mode1();
            if(isButtonBack()) {statusMode=CHOICE_DIRECTION;}
            if(isButtonMode())  {statusMode=DISPLAY_MODE;}
            break;
        case CUSTOM_MODE_2:
            count_free_time++;
            if(count_free_time>=200){
                count_free_time=0;
                statusMode=DISPLAY_MODE;
            }
            Set_Custom_mode2();
            if(isButtonBack()) {statusMode=CHOICE_DIRECTION;}
            if(isButtonMode()){statusMode=DISPLAY_MODE;}
            break;
    }
}

void DisplayTimeandHum()
{
    second = read_ds1307(ADDRESS_SECOND);
    minute = read_ds1307(ADDRESS_MINUTE);
    hour = read_ds1307(ADDRESS_HOUR);
    day = read_ds1307(ADDRESS_DAY);
    date = read_ds1307(ADDRESS_DATE);
    month = read_ds1307(ADDRESS_MONTH);
    year = read_ds1307(ADDRESS_YEAR);

    switch(day)
    {
        case 1:
            LcdPrintStringS(0,0,"SUN");
            break;
        case 2:
            LcdPrintStringS(0,0,"MON");
            break;
        case 3:
            LcdPrintStringS(0,0,"TUE");
            break;
        case 4:
            LcdPrintStringS(0,0,"WED");
            break;
        case 5:
            LcdPrintStringS(0,0,"THU");
            break;
        case 6:
            LcdPrintStringS(0,0,"FRI");
            break;
        case 7:
            LcdPrintStringS(0,0,"SAT");
            break;
        default:
            LcdPrintStringS(0,0,"ERR");
            break;    
    }
    LcdPrintStringS(0,3," ");
    LcdPrintNumS(0,4,hour/10);
    LcdPrintNumS(0,5,hour%10);
    LcdPrintStringS(0,6,":");
    LcdPrintNumS(0,7,minute/10);
    LcdPrintNumS(0,8,minute%10);
    LcdPrintStringS(0,9,":");
    LcdPrintNumS(0,10,second/10);
    LcdPrintNumS(0,11,second%10);
    watermode=read_ds1307(ADDRESS_WATER_MODE);
    if(watermode==NONE) LcdPrintStringS(0,12," OFF");
    else if(watermode==MODE1) LcdPrintStringS(0,12," MO1");
    else if(watermode==MODE2) LcdPrintStringS(0,12," MO2");
    
    switch(month)
    {
        case 1:
            LcdPrintStringS(1,0,"JAN");
            break;
        case 2:
            LcdPrintStringS(1,0,"FEB");
            break;
        case 3:
            LcdPrintStringS(1,0,"MAR");
            break;
        case 4:
            LcdPrintStringS(1,0,"APR");
            break;
        case 5:
            LcdPrintStringS(1,0,"MAY");
            break;
        case 6:
            LcdPrintStringS(1,0,"JUN");
            break;
        case 7:
            LcdPrintStringS(1,0,"JUL");
            break;
        case 8:
            LcdPrintStringS(1,0,"AUG");
            break;
        case 9:
            LcdPrintStringS(1,0,"SEP");
            break;
        case 10:
            LcdPrintStringS(1,0,"OCT");
            break;
        case 11:
            LcdPrintStringS(1,0,"NOV");
            break;
        case 12:
            LcdPrintStringS(1,0,"DEC");
            break;
        default:
            LcdPrintStringS(1,0,"ERR");
            break;    
    }
    LcdPrintStringS(1,3," ");
    LcdPrintNumS(1,4,date/10);
    LcdPrintNumS(1,5,date%10);
    LcdPrintStringS(1,6," ");
    LcdPrintNumS(1,7,20);
    LcdPrintNumS(1,9,year/10);
    LcdPrintNumS(1,10,year%10);
    LcdPrintStringS(1,11," ");
    LcdPrintNumS(1,12,humidityvalue/100);
    LcdPrintNumS(1,13,(humidityvalue/10)%10);
    LcdPrintNumS(1,14,humidityvalue%10);
    LcdPrintStringS(1,15,"%");
}

void DisplayTime()
{
    second = read_ds1307(ADDRESS_SECOND);
    minute = read_ds1307(ADDRESS_MINUTE);
    hour = read_ds1307(ADDRESS_HOUR);
    day = read_ds1307(ADDRESS_DAY);
    date = read_ds1307(ADDRESS_DATE);
    month = read_ds1307(ADDRESS_MONTH);
    year = read_ds1307(ADDRESS_YEAR);

    switch(day)
    {
        case 1:
            LcdPrintStringS(0,0,"SUN");
            break;
        case 2:
            LcdPrintStringS(0,0,"MON");
            break;
        case 3:
            LcdPrintStringS(0,0,"TUE");
            break;
        case 4:
            LcdPrintStringS(0,0,"WED");
            break;
        case 5:
            LcdPrintStringS(0,0,"THU");
            break;
        case 6:
            LcdPrintStringS(0,0,"FRI");
            break;
        case 7:
            LcdPrintStringS(0,0,"SAT");
            break;
        default:
            LcdPrintStringS(0,0,"ERR");
            break;    
    }
    LcdPrintStringS(0,3," ");
    LcdPrintNumS(0,4,hour/10);
    LcdPrintNumS(0,5,hour%10);
    LcdPrintStringS(0,6,":");
    LcdPrintNumS(0,7,minute/10);
    LcdPrintNumS(0,8,minute%10);
    LcdPrintStringS(0,9,":");
    LcdPrintNumS(0,10,second/10);
    LcdPrintNumS(0,11,second%10);
    watermode=read_ds1307(ADDRESS_WATER_MODE);
    if(watermode==NONE) LcdPrintStringS(0,12," OFF");
    else if(watermode==MODE1) LcdPrintStringS(0,12," MO1");
    else if(watermode==MODE2) LcdPrintStringS(0,12," MO2");
    
    switch(month)
    {
        case 1:
            LcdPrintStringS(1,2,"JAN");
            break;
        case 2:
            LcdPrintStringS(1,2,"FEB");
            break;
        case 3:
            LcdPrintStringS(1,2,"MAR");
            break;
        case 4:
            LcdPrintStringS(1,2,"APR");
            break;
        case 5:
            LcdPrintStringS(1,2,"MAY");
            break;
        case 6:
            LcdPrintStringS(1,2,"JUN");
            break;
        case 7:
            LcdPrintStringS(1,2,"JUL");
            break;
        case 8:
            LcdPrintStringS(1,2,"AUG");
            break;
        case 9:
            LcdPrintStringS(1,2,"SEP");
            break;
        case 10:
            LcdPrintStringS(1,2,"OCT");
            break;
        case 11:
            LcdPrintStringS(1,2,"NOV");
            break;
        case 12:
            LcdPrintStringS(1,2,"DEC");
            break;
        default:
            LcdPrintStringS(1,2,"ERR");
            break;    
    }
    LcdPrintStringS(1,0,"  ");
    LcdPrintStringS(1,5," ");
    LcdPrintNumS(1,6,date/10);
    LcdPrintNumS(1,7,date%10);
    LcdPrintStringS(1,8," ");
    LcdPrintNumS(1,9,20);
    LcdPrintNumS(1,11,year/10);
    LcdPrintNumS(1,12,year%10);
    LcdPrintStringS(1,13,"   ");
}

void SetTime()
{
    switch(statusSetTime)
    {
        case INIT_SYSTEM:         
            DisplayTime();
            if(isButtonFuntion()){
                statusSetTime = SET_WATER_MODE; 
            }
            break;
        case SET_WATER_MODE:
            DisplayTime();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,13,"    ");
            if(isButtonUp())
            {
                watermode = (watermode + 1)%3;  
                write_ds1307(ADDRESS_WATER_MODE, watermode);
            }
            if(isButtonDown())
            {
                watermode = watermode - 1;
                if(watermode < 0)  watermode = 2;
                write_ds1307(ADDRESS_WATER_MODE, watermode);
            } 
            if(isButtonFuntion()){
                send_parameter("08", read_ds1307(ADDRESS_WATER_MODE));
                statusSetTime = SET_HOUR;
            }
            break;
        case SET_HOUR:
            DisplayTime();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,4,"  ");
            if(isButtonUp())
            {
                hour = (hour + 1)%24;  
                write_ds1307(ADDRESS_HOUR, hour);
            }
            if(isButtonDown())
            {
                hour = hour - 1;
                if(hour < 0)  hour = 23;
                write_ds1307(ADDRESS_HOUR, hour);
            } 
            if(isButtonFuntion()){
                statusSetTime = SET_MINUTE;
            }
            break;
        case SET_MINUTE:
            DisplayTime();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,7,"  ");
            if(isButtonUp())
            {
                minute = (minute + 1)%60;  
                write_ds1307(ADDRESS_MINUTE, minute);
            }
            if(isButtonDown())
            {
                minute = minute - 1;
                if(minute < 0)  minute = 59;
                write_ds1307(ADDRESS_MINUTE, minute);
            } 
            if(isButtonFuntion())
                statusSetTime = SET_DAY;
            break;
        case SET_DAY:
            DisplayTime();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,0,"   ");
            if(isButtonUp())
            {
                day = (day + 1)%7;  
                write_ds1307(ADDRESS_DAY, day);
            }
            if(isButtonDown())
            {
                day = day - 1;
                if(day < 1)  day = 7;
                write_ds1307(ADDRESS_DAY, day);
            } 
            if(isButtonFuntion())
                statusSetTime = SET_DATE;
            break;
        case SET_DATE:
            DisplayTime();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,6,"  ");
            if(isButtonUp())
            {
                date = date + 1; 
                if(date >31)  date = 1;
                write_ds1307(ADDRESS_DATE, date);
            }
            if(isButtonDown())
            {
                date = date - 1;
                if(date < 1)  date = 31;
                write_ds1307(ADDRESS_DATE, date);
            } 
            if(isButtonFuntion())
                statusSetTime = SET_MONTH;
            break;
        case SET_MONTH:
            DisplayTime();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,2,"   ");
            if(isButtonUp())
            {
                month = month + 1;
                if(month > 12)  month = 1; 
                write_ds1307(ADDRESS_MONTH, month);
            }
            if(isButtonDown())
            {
                month = month - 1;
                if(month < 1)  month = 12;
                write_ds1307(ADDRESS_MONTH, month);
            } 
            if(isButtonFuntion())
                statusSetTime = SET_YEAR;
            break;
        case SET_YEAR:
            DisplayTime();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,9,"    ");
            if(isButtonUp())
            {
                year = (year + 1)%100;  
                write_ds1307(ADDRESS_YEAR, year);
            }
            if(isButtonDown())
            {
                year = year - 1;
                if(year < 1)  year = 99;
                write_ds1307(ADDRESS_YEAR, year);
            } 
            if(isButtonFuntion())               
                    statusSetTime = INIT_SYSTEM;
            break;
        default:
            break;
            
        
    }
}

void Security(){
    switch(statusSecurity){
        case INIT_SEC:
            if(read_ds1307(ADDRESS_ENABLE_PASS)==1){
                statusenterpass=0;
                checkpass=1;
                for (i = 0; i<4; i++){
                    arrayPassword[i]=0;
                }
                statusSecurity=ENTER_PASSWORD;
            }else {
                statusChoice=0;
                statusMode=CHOICE_DIRECTION;
            }
            break;
        case ENTER_PASSWORD:
            LcdPrintStringS(0,0,"ENTER PASSWORD  ");
            LcdPrintStringS(1,0,"    ");
            LcdPrintNumS(1,4,arrayPassword[0]);
            LcdPrintStringS(1,5," ");
            LcdPrintNumS(1,6,arrayPassword[1]);
            LcdPrintStringS(1,7," ");
            LcdPrintNumS(1,8,arrayPassword[2]);
            LcdPrintStringS(1,9," ");
            LcdPrintNumS(1,10,arrayPassword[3]);
            LcdPrintStringS(1,11,"     ");
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 ){
                switch(statusenterpass){
                    case 0:LcdPrintStringS(1,4," ");break;
                    case 1:LcdPrintStringS(1,6," ");break; 
                    case 2:LcdPrintStringS(1,8," ");break;
                    case 3:LcdPrintStringS(1,10," ");break;
                }
            }
            if(isButtonUp()){
                arrayPassword[statusenterpass]=(arrayPassword[statusenterpass]+1)%10;
            }
            if(isButtonDown()){
                arrayPassword[statusenterpass]=arrayPassword[statusenterpass]-1;
                if(arrayPassword[statusenterpass]<0) arrayPassword[statusenterpass]=9;
            }
            if(isButtonFuntion()){
                if(statusenterpass>=3){
                    statusSecurity=CHECK_PASS;
                }else{
                    statusenterpass++;
                }
            } 
            if(isButtonBack()){
                statusSecurity=FORGOT_PASS;
            }
            break;
        case CHECK_PASS:
            if(arrayPassword[0]!=read_ds1307(ADDRESS_PASS_1)||arrayPassword[1]!=read_ds1307(ADDRESS_PASS_2)||
                    arrayPassword[2]!=read_ds1307(ADDRESS_PASS_3)||arrayPassword[3]!=read_ds1307(ADDRESS_PASS_4)){
                checkpass=0;
            }
            if(checkpass==0){
                doubleclick=0;
                statusMode=DISPLAY_MODE;
            }else{
                statusChoice=0;
                statusMode=CHOICE_DIRECTION;
            }
            break;
        case FORGOT_PASS:
            LcdPrintStringS(0,0,"FORGOT PASSWORD ");
            LcdPrintStringS(1,0,"SEND TO EMAIL  <");
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  
                LcdPrintStringS(1,15," ");
            if(isButtonFuntion()){
                UartSendString("!pa");
                UartSendNum(read_ds1307(ADDRESS_PASS_1));
                UartSendNum(read_ds1307(ADDRESS_PASS_2));
                UartSendNum(read_ds1307(ADDRESS_PASS_3));
                UartSendNum(read_ds1307(ADDRESS_PASS_4));
                uart_putchar('#');
                statusSecurity=SEND_PASS;
            }
            break;
        case SEND_PASS:
            LcdPrintStringS(0,0,"  PWD HAS BEEN  ");
            LcdPrintStringS(1,0,"  SENT TO EMAIL ");
            if(isButtonMode())  {statusMode=DISPLAY_MODE;}
            break;
    }
}


void Direction(){
    switch(statusChoice){
        case 0:
            LcdPrintStringS(0,0,"1.TIME & MODE  <");
            LcdPrintStringS(1,0,"2.CONFIG MODE1  ");
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  
                LcdPrintStringS(0,15," ");
            if(isButtonFuntion()){
                doubleclick=0;
                holdfunction=0;
                statusSetTime=INIT_SYSTEM;
                statusMode=SET_TIME_MODE;
            }
            if(isButtonDown()){
                statusChoice=1;
            }
            if(isButtonUp()){
                statusChoice=3;
            }
            break;
        case 1:
            LcdPrintStringS(0,0,"1.TIME & MODE   ");
            LcdPrintStringS(1,0,"2.CONFIG MODE1 <");
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  
                LcdPrintStringS(1,15," ");
            if(isButtonFuntion()){
                doubleclick=0;
                holdfunction=0;
                statusSet_cm1=INIT_CM1;
                statusMode=CUSTOM_MODE_1;
                statusTurn=FIRST_TURN;
            }
            if(isButtonDown()){
                statusChoice=2;
            }
            if(isButtonUp()){
                statusChoice=0;
            }
            break;
        case 2:
            LcdPrintStringS(0,0,"3.CONFIG MODE2 <");
            LcdPrintStringS(1,0,"4.CONFIG PASS   ");
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  
                LcdPrintStringS(0,15," ");
            if(isButtonFuntion()){
                doubleclick=0;
                holdfunction=0;
                statusSet_cm2=INIT_CM2;
                statusMode=CUSTOM_MODE_2;
            }
            if(isButtonDown()){
                statusChoice=3;
            }
            if(isButtonUp()){
                statusChoice=1;
            }
            break;
        case 3:
            LcdPrintStringS(0,0,"3.CONFIG MODE2  ");
            LcdPrintStringS(1,0,"4.CONFIG PASS  <");
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  
                LcdPrintStringS(1,15," ");
            if(isButtonFuntion()){
                doubleclick=0;
                holdfunction=0;
                statusPassmode=0;
                statusMode=CONFIG_PASS;
            }
            if(isButtonDown()){
                statusChoice=0;
            }
            if(isButtonUp()){
                statusChoice=2;
            }
            break;
    }
}

void Configpass(){
    switch(statusPassmode){
        case 0:
            switch(statusChoicepass){
                case 0:
                    LcdPrintStringS(0,0,"1.ENABLE PASS  <");
                    LcdPrintStringS(1,0,"2.NEW PASS      ");
                    timeBlink = (timeBlink + 1)%10;
                    if(timeBlink < 5 )  
                        LcdPrintStringS(0,15," ");
                    if(isButtonFuntion()){
                        statusPassmode=1;
                    }
                    if(isButtonDown()){
                        statusChoicepass=1;
                    }
                    if(isButtonUp()){
                        statusChoicepass=1;
                    }
                    break;
                case 1:
                    LcdPrintStringS(0,0,"1.ENABLE PASS   ");
                    LcdPrintStringS(1,0,"2.NEW PASS     <");
                    timeBlink = (timeBlink + 1)%10;
                    if(timeBlink < 5 )  
                        LcdPrintStringS(1,15," ");
                    if(isButtonFuntion()){
                        statusenternewpass=0;
                        statusPassmode=2;
                    }
                    if(isButtonDown()){
                        statusChoicepass=0;
                    }
                    if(isButtonUp()){
                        statusChoicepass=0;
                    }
                    break;
            }
            break;
        case 1:
            LcdPrintStringS(0,0,"USE PASS OR NOT ");
            LcdPrintStringS(1,0,"      ");
            if(read_ds1307(ADDRESS_ENABLE_PASS)==1){
                LcdPrintStringS(1,6,"YES");
            }else{
                LcdPrintStringS(1,6,"NO ");
            }
            LcdPrintStringS(1,9,"       ");
            if(isButtonUp()){
                write_ds1307(ADDRESS_ENABLE_PASS, ON);
            }
            if(isButtonDown()){
                write_ds1307(ADDRESS_ENABLE_PASS, OFF);
            }
            if(isButtonFuntion()){
                doubleclick=0;
                statusPassmode=0;
            }            
            break;
        case 2:
            Password[0]=read_ds1307(ADDRESS_PASS_1);
            Password[1]=read_ds1307(ADDRESS_PASS_2);
            Password[2]=read_ds1307(ADDRESS_PASS_3);
            Password[3]=read_ds1307(ADDRESS_PASS_4);
            LcdPrintStringS(0,0,"  NEW PASSWORD  ");
            LcdPrintStringS(1,0,"    ");
            LcdPrintNumS(1,4,Password[0]);
            LcdPrintStringS(1,5," ");
            LcdPrintNumS(1,6,Password[1]);
            LcdPrintStringS(1,7," ");
            LcdPrintNumS(1,8,Password[2]);
            LcdPrintStringS(1,9," ");
            LcdPrintNumS(1,10,Password[3]);
            LcdPrintStringS(1,11,"     ");
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 ){
                switch(statusenternewpass){
                    case 0:LcdPrintStringS(1,4," ");break;
                    case 1:LcdPrintStringS(1,6," ");break; 
                    case 2:LcdPrintStringS(1,8," ");break;
                    case 3:LcdPrintStringS(1,10," ");break;
                }
            }
            if(isButtonUp()){
                Password[statusenternewpass]=(Password[statusenternewpass]+1)%10;
                switch(statusenternewpass){
                    case 0:write_ds1307(ADDRESS_PASS_1,Password[0]);send_parameter("3C",read_ds1307(ADDRESS_PASS_1));break;
                    case 1:write_ds1307(ADDRESS_PASS_2,Password[1]);send_parameter("3D",read_ds1307(ADDRESS_PASS_2));break; 
                    case 2:write_ds1307(ADDRESS_PASS_3,Password[2]);send_parameter("3E",read_ds1307(ADDRESS_PASS_3));break;
                    case 3:write_ds1307(ADDRESS_PASS_4,Password[3]);send_parameter("3F",read_ds1307(ADDRESS_PASS_4));break;
                }
            }
            if(isButtonDown()){
                Password[statusenternewpass]=Password[statusenternewpass]-1;
                if(Password[statusenternewpass]<0) Password[statusenternewpass]=9;
                switch(statusenternewpass){
                    case 0:write_ds1307(ADDRESS_PASS_1,Password[0]);send_parameter("3C",read_ds1307(ADDRESS_PASS_1));break;
                    case 1:write_ds1307(ADDRESS_PASS_2,Password[1]);send_parameter("3D",read_ds1307(ADDRESS_PASS_2));break; 
                    case 2:write_ds1307(ADDRESS_PASS_3,Password[2]);send_parameter("3E",read_ds1307(ADDRESS_PASS_3));break;
                    case 3:write_ds1307(ADDRESS_PASS_4,Password[3]);send_parameter("3F",read_ds1307(ADDRESS_PASS_4));break;
                }
            }
            if(isButtonFuntion()){
                if(statusenternewpass>=3){
                    doubleclick=0;
                    statusPassmode=0;
                }else{
                    statusenternewpass++;
                }
            }             
            break;
    }
}


void DisplayCustom_mode1(){
    max_humidity   = read_ds1307(ADDRESS_MAX_VALUE);
    switch (statusTurn){
        case FIRST_TURN:
            hour_timer   = read_ds1307(ADDRESS_HOUR_SCHED1);
            minute_timer = read_ds1307(ADDRESS_MINUTE_SCHED1);
            bit_timer    = read_ds1307(ADDRESS_ENABLE_SCHED1);
            fre_timer    = read_ds1307(ADDRESS_FRE_SCHED1);
            dur_timer    = read_ds1307(ADDRESS_DURATION_SCHED1);
            break;
        case SECOND_TURN:
            hour_timer   = read_ds1307(ADDRESS_HOUR_SCHED2);
            minute_timer = read_ds1307(ADDRESS_MINUTE_SCHED2);
            bit_timer    = read_ds1307(ADDRESS_ENABLE_SCHED2);
            fre_timer    = read_ds1307(ADDRESS_FRE_SCHED2);
            dur_timer    = read_ds1307(ADDRESS_DURATION_SCHED2);
            break;
        case THIRD_TURN:
            hour_timer   = read_ds1307(ADDRESS_HOUR_SCHED3);
            minute_timer = read_ds1307(ADDRESS_MINUTE_SCHED3);
            bit_timer    = read_ds1307(ADDRESS_ENABLE_SCHED3);
            fre_timer    = read_ds1307(ADDRESS_FRE_SCHED3);
            dur_timer    = read_ds1307(ADDRESS_DURATION_SCHED3);
            break;
        case FOURTH_TURN:
            hour_timer   = read_ds1307(ADDRESS_HOUR_SCHED4);
            minute_timer = read_ds1307(ADDRESS_MINUTE_SCHED4);
            bit_timer    = read_ds1307(ADDRESS_ENABLE_SCHED4);
            fre_timer    = read_ds1307(ADDRESS_FRE_SCHED4);
            dur_timer    = read_ds1307(ADDRESS_DURATION_SCHED4);
            break;
    }
    LcdPrintStringS(0,0,"T");
    LcdPrintNumS(0,1,statusTurn+1);
    LcdPrintStringS(0,2,"  ");
    LcdPrintNumS(0,4,hour_timer/10);
    LcdPrintNumS(0,5,hour_timer%10);
    LcdPrintStringS(0,6,":");
    LcdPrintNumS(0,7,minute_timer/10);
    LcdPrintNumS(0,8,minute_timer%10);
    LcdPrintStringS(0,9," max");
    LcdPrintNumS(0,13,max_humidity/10);
    LcdPrintNumS(0,14,max_humidity%10);
    LcdPrintStringS(0,15,"%");
    if(bit_timer==ON){LcdPrintStringS(1,0,"ON  ");}
    else {LcdPrintStringS(1,0,"OFF ");}
    LcdPrintNumS(1,4,dur_timer/10);
    LcdPrintNumS(1,5,dur_timer%10);
    LcdPrintStringS(1,6,"M/T ");
    LcdPrintStringS(1,10,"1T/");
    LcdPrintNumS(1,13,fre_timer/10);
    LcdPrintNumS(1,14,fre_timer%10);
    LcdPrintStringS(1,15,"D");
}

void Set_Custom_mode1(){
    switch (statusSet_cm1){
        case INIT_CM1:
            DisplayCustom_mode1();
            if(isButtonFuntion()){
                statusSet_cm1 = SET_TURN_CM1; 
            }
            break;
        case SET_TURN_CM1:
            DisplayCustom_mode1();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,1," ");
            if(isButtonUp())
            {
                statusTurn = statusTurn + 1;
                if(statusTurn>3) statusTurn=0;
            }
            if(isButtonDown())
            {
                statusTurn = statusTurn - 1;
                if(statusTurn < 0)  statusTurn = 3;
            } 
            if(isButtonFuntion()){
                statusSet_cm1 = SET_EN_CM1;
            }
            break;
        case SET_EN_CM1:
            DisplayCustom_mode1();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,0,"   ");
            if(isButtonUp())
            {
                bit_timer = ON;
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_ENABLE_SCHED1, bit_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_ENABLE_SCHED2, bit_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_ENABLE_SCHED3, bit_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_ENABLE_SCHED4, bit_timer); break;
                }
            }
            if(isButtonDown())
            {
                bit_timer = OFF;
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_ENABLE_SCHED1, bit_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_ENABLE_SCHED2, bit_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_ENABLE_SCHED3, bit_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_ENABLE_SCHED4, bit_timer); break;
                }
            } 
            if(isButtonFuntion()){
                switch(statusTurn){
                    case FIRST_TURN:  send_parameter("0C",read_ds1307(ADDRESS_ENABLE_SCHED1)); break;
                    case SECOND_TURN: send_parameter("11",read_ds1307(ADDRESS_ENABLE_SCHED2)); break;
                    case THIRD_TURN:  send_parameter("16",read_ds1307(ADDRESS_ENABLE_SCHED3)); break;
                    case FOURTH_TURN: send_parameter("1B",read_ds1307(ADDRESS_ENABLE_SCHED4)); break;
                }
                statusSet_cm1 = SET_HOUR_CM1;
            }
            break;
        case SET_HOUR_CM1:
            DisplayCustom_mode1();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,4,"  ");
            if(isButtonUp())
            {
                hour_timer = (hour_timer + 1)%24; 
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_HOUR_SCHED1, hour_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_HOUR_SCHED2, hour_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_HOUR_SCHED3, hour_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_HOUR_SCHED4, hour_timer); break;
                } 
            }
            if(isButtonDown())
            {
                hour_timer = hour_timer - 1;
                if(hour_timer < 0)  hour_timer = 23;
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_HOUR_SCHED1, hour_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_HOUR_SCHED2, hour_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_HOUR_SCHED3, hour_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_HOUR_SCHED4, hour_timer); break;
                } 
            } 
            if(isButtonFuntion()){
                switch(statusTurn){
                    case FIRST_TURN:  send_parameter("0A",read_ds1307(ADDRESS_HOUR_SCHED1)); break;
                    case SECOND_TURN: send_parameter("0F",read_ds1307(ADDRESS_HOUR_SCHED2)); break;
                    case THIRD_TURN:  send_parameter("14",read_ds1307(ADDRESS_HOUR_SCHED3)); break;
                    case FOURTH_TURN: send_parameter("19",read_ds1307(ADDRESS_HOUR_SCHED4)); break;
                }
                statusSet_cm1 = SET_MINUTE_CM1;
            }
            break;
        case SET_MINUTE_CM1:
            DisplayCustom_mode1();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,7,"  ");
            if(isButtonUp())
            {
                minute_timer = (minute_timer + 1)%60; 
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_MINUTE_SCHED1, minute_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_MINUTE_SCHED2, minute_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_MINUTE_SCHED3, minute_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_MINUTE_SCHED4, minute_timer); break;
                } 
            }
            if(isButtonDown())
            {
                minute_timer = minute_timer - 1;
                if(minute_timer < 0)  minute_timer = 59;
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_MINUTE_SCHED1, minute_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_MINUTE_SCHED2, minute_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_MINUTE_SCHED3, minute_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_MINUTE_SCHED4, minute_timer); break;
                }
            } 
            if(isButtonFuntion()){
                switch(statusTurn){
                    case FIRST_TURN:  send_parameter("0B",read_ds1307(ADDRESS_MINUTE_SCHED1)); break;
                    case SECOND_TURN: send_parameter("10",read_ds1307(ADDRESS_MINUTE_SCHED2)); break;
                    case THIRD_TURN:  send_parameter("15",read_ds1307(ADDRESS_MINUTE_SCHED3)); break;
                    case FOURTH_TURN: send_parameter("1A",read_ds1307(ADDRESS_MINUTE_SCHED4)); break;
                }
                statusSet_cm1 = SET_DUR_CM1;
            }
            break;
        case SET_DUR_CM1:
            DisplayCustom_mode1();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,4,"  ");
            if(isButtonUp())
            {
                dur_timer = (dur_timer + 1)%60; 
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_DURATION_SCHED1, dur_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_DURATION_SCHED2, dur_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_DURATION_SCHED3, dur_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_DURATION_SCHED4, dur_timer); break;
                } 
            }
            if(isButtonDown())
            {
                dur_timer = dur_timer - 1;
                if(dur_timer < 0)  dur_timer = 59;
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_DURATION_SCHED1, dur_timer); break;
                    case SECOND_TURN: write_ds1307(ADDRESS_DURATION_SCHED2, dur_timer); break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_DURATION_SCHED3, dur_timer); break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_DURATION_SCHED4, dur_timer); break;
                } 
            } 
            if(isButtonFuntion()){
                switch(statusTurn){
                    case FIRST_TURN:  send_parameter("0D",read_ds1307(ADDRESS_DURATION_SCHED1)); break;
                    case SECOND_TURN: send_parameter("12",read_ds1307(ADDRESS_DURATION_SCHED2)); break;
                    case THIRD_TURN:  send_parameter("17",read_ds1307(ADDRESS_DURATION_SCHED3)); break;
                    case FOURTH_TURN: send_parameter("1C",read_ds1307(ADDRESS_DURATION_SCHED4)); break;
                }
                statusSet_cm1 = SET_FRE_CM1;
            }
            break;
        
        case SET_FRE_CM1:
            DisplayCustom_mode1();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,13,"  ");
            if(isButtonUp())
            {
                fre_timer = fre_timer + 1;
                if(fre_timer > 10)  fre_timer = 1;
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_FRE_SCHED1, fre_timer);fre_turn1=0;old_day1=0; break;
                    case SECOND_TURN: write_ds1307(ADDRESS_FRE_SCHED2, fre_timer);fre_turn2=0;old_day2=0; break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_FRE_SCHED3, fre_timer);fre_turn3=0;old_day3=0; break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_FRE_SCHED4, fre_timer);fre_turn4=0;old_day4=0; break;
                } 
            }
            if(isButtonDown())
            {
                fre_timer = fre_timer - 1;
                if(fre_timer < 1)  fre_timer = 10;
                switch(statusTurn){
                    case FIRST_TURN:  write_ds1307(ADDRESS_FRE_SCHED1, fre_timer);fre_turn1=0;old_day1=0; break;
                    case SECOND_TURN: write_ds1307(ADDRESS_FRE_SCHED2, fre_timer);fre_turn2=0;old_day2=0; break;
                    case THIRD_TURN:  write_ds1307(ADDRESS_FRE_SCHED3, fre_timer);fre_turn3=0;old_day3=0; break;
                    case FOURTH_TURN: write_ds1307(ADDRESS_FRE_SCHED4, fre_timer);fre_turn4=0;old_day4=0; break;
                } 
            } 
            if(isButtonFuntion()){
                switch(statusTurn){
                    case FIRST_TURN:  send_parameter("0E",read_ds1307(ADDRESS_FRE_SCHED1)); break;
                    case SECOND_TURN: send_parameter("13",read_ds1307(ADDRESS_FRE_SCHED2)); break;
                    case THIRD_TURN:  send_parameter("18",read_ds1307(ADDRESS_FRE_SCHED3)); break;
                    case FOURTH_TURN: send_parameter("1D",read_ds1307(ADDRESS_FRE_SCHED4)); break;
                }
                statusSet_cm1 = SET_MHV_CM1;
            }
            break;
        case SET_MHV_CM1:
            DisplayCustom_mode1();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,13,"  ");
            if(isButtonUp())
            {
                max_humidity = (max_humidity + 1)%100;
                write_ds1307(ADDRESS_MAX_VALUE, max_humidity);
            }
            if(isButtonDown())
            {
                max_humidity = max_humidity - 1;
                if(max_humidity < 0)  max_humidity = 99;
                write_ds1307(ADDRESS_MAX_VALUE, max_humidity);
            } 
            if(isButtonFuntion()){
                send_parameter("09",read_ds1307(ADDRESS_MAX_VALUE));
                statusSet_cm1 = INIT_CM1; 
            }
            break;
    }
}


void DisplayCustom_mode2(){
    hour_begin    = read_ds1307(ADDRESS_REST_HOUR_BEGIN);
    minute_begin  = read_ds1307(ADDRESS_REST_MINUTE_BEGIN);
    hour_stop     = read_ds1307(ADDRESS_REST_HOUR_STOP);
    minute_stop   = read_ds1307(ADDRESS_REST_MINUTE_STOP);
    min_humidity  = read_ds1307(ADDRESS_MIN_VALUE);
    dur_m2        = read_ds1307(ADDRESS_DURATION_M2);
    
    LcdPrintStringS(0,0,"BEG ");
    LcdPrintNumS(0,4,hour_begin/10);
    LcdPrintNumS(0,5,hour_begin%10);
    LcdPrintStringS(0,6,":");
    LcdPrintNumS(0,7,minute_begin/10);
    LcdPrintNumS(0,8,minute_begin%10);
    LcdPrintStringS(0,9," ");
    LcdPrintNumS(0,10,dur_m2/10);
    LcdPrintNumS(0,11,dur_m2%10);
    LcdPrintStringS(0,12,"M/T ");
    LcdPrintStringS(1,0,"END ");
    LcdPrintNumS(1,4,hour_stop/10);
    LcdPrintNumS(1,5,hour_stop%10);
    LcdPrintStringS(1,6,":");
    LcdPrintNumS(1,7,minute_stop/10);
    LcdPrintNumS(1,8,minute_stop%10);
    LcdPrintStringS(1,9," min");
    LcdPrintNumS(1,13,min_humidity/10);
    LcdPrintNumS(1,14,min_humidity%10);
    LcdPrintStringS(1,15,"%");
}

void Set_Custom_mode2(){
    switch(statusSet_cm2){
        case INIT_CM2:
            DisplayCustom_mode2();
            if(isButtonFuntion()){
                statusSet_cm2 = SET_HB_CM2; 
            }
            break;
        case SET_HB_CM2:
            DisplayCustom_mode2();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,4,"  ");
            if(isButtonUp())
            {
                hour_begin = (hour_begin + 1)%24;
                write_ds1307(ADDRESS_REST_HOUR_BEGIN, hour_begin);
            }
            if(isButtonDown())
            {
                hour_begin = hour_begin - 1;
                if(hour_begin < 0)  hour_begin = 23;
                write_ds1307(ADDRESS_REST_HOUR_BEGIN, hour_begin);
            } 
            if(isButtonFuntion()){
                send_parameter("1E",read_ds1307(ADDRESS_REST_HOUR_BEGIN));
                statusSet_cm2 = SET_MB_CM2; 
            }
            break;
        case SET_MB_CM2:
            DisplayCustom_mode2();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,7,"  ");
            if(isButtonUp())
            {
                minute_begin = (minute_begin + 1)%60;
                write_ds1307(ADDRESS_REST_MINUTE_BEGIN, minute_begin);
            }
            if(isButtonDown())
            {
                minute_begin = minute_begin - 1;
                if(minute_begin < 0)  minute_begin = 59;
                write_ds1307(ADDRESS_REST_MINUTE_BEGIN, minute_begin);
            } 
            if(isButtonFuntion()){
                send_parameter("1F",read_ds1307(ADDRESS_REST_MINUTE_BEGIN));
                statusSet_cm2 = SET_HS_CM2; 
            }
            break;
        case SET_HS_CM2:
            DisplayCustom_mode2();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,4,"  ");
            if(isButtonUp())
            {
                hour_stop = (hour_stop + 1)%24;
                write_ds1307(ADDRESS_REST_HOUR_STOP, hour_stop);
            }
            if(isButtonDown())
            {
                hour_stop = hour_stop - 1;
                if(hour_stop < 0)  hour_stop = 23;
                write_ds1307(ADDRESS_REST_HOUR_STOP, hour_stop);
            } 
            if(isButtonFuntion()){
                send_parameter("20",read_ds1307(ADDRESS_REST_HOUR_STOP));
                statusSet_cm2 = SET_MS_CM2; 
            }
            break;
        case SET_MS_CM2:
            DisplayCustom_mode2();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,7,"  ");
            if(isButtonUp())
            {
                minute_stop = (minute_stop + 1)%60;
                write_ds1307(ADDRESS_REST_MINUTE_STOP, minute_stop);
            }
            if(isButtonDown())
            {
                minute_stop = minute_stop - 1;
                if(minute_stop < 0)  minute_stop = 59;
                write_ds1307(ADDRESS_REST_MINUTE_STOP, minute_stop);
            } 
            if(isButtonFuntion()){
                send_parameter("21",read_ds1307(ADDRESS_REST_MINUTE_STOP));
                statusSet_cm2 = SET_MHV_CM2; 
            }
            break;
        case SET_MHV_CM2:
            DisplayCustom_mode2();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(1,13,"  ");
            if(isButtonUp())
            {
                min_humidity = (min_humidity + 1)%100;
                write_ds1307(ADDRESS_MIN_VALUE, min_humidity);
            }
            if(isButtonDown())
            {
                min_humidity = min_humidity - 1;
                if(min_humidity < 0)  min_humidity = 99;
                write_ds1307(ADDRESS_MIN_VALUE, min_humidity);
            } 
            if(isButtonFuntion()){
                send_parameter("22",read_ds1307(ADDRESS_MIN_VALUE));
                statusSet_cm2 = SET_DUR_CM2; 
            }
            break;
        case SET_DUR_CM2:
            DisplayCustom_mode2();
            timeBlink = (timeBlink + 1)%10;
            if(timeBlink < 5 )  //&& enableBlink()
                LcdPrintStringS(0,10,"  ");
            if(isButtonUp())
            {
                dur_m2 = (dur_m2 + 1)%60;
                write_ds1307(ADDRESS_DURATION_M2, dur_m2);
            }
            if(isButtonDown())
            {
                dur_m2 = dur_m2 - 1;
                if(dur_m2 < 0)  dur_m2 = 59;
                write_ds1307(ADDRESS_DURATION_M2, dur_m2);
            } 
            if(isButtonFuntion()){
                send_parameter("23",read_ds1307(ADDRESS_DURATION_M2));
                statusSet_cm2 = INIT_CM2; 
            }
            break;
        default:
            
            break;
    }
}

unsigned char isButtonMode()
{
    if (doubleclick>0){
        count_free_time=0;
        doubleclick--;
        return 1;}
    else
        return 0;
}

unsigned char isButtonFuntion()
{
    if (pressfunction>0){
        count_free_time=0;
        pressfunction--;
        return 1;}
    else
        return 0;
}

unsigned char isButtonBack()
{
    if (holdfunction>0){
        count_free_time=0;
        holdfunction--;
        return 1;}
    else
        return 0;
}

unsigned char isButtonUp()
{
    if ((key_code[4] == 1) || (key_code[4] >= 10 && key_code[4]%2 == 0)){
        count_free_time=0;
        return 1;
    }
    else
        return 0;
}

unsigned char isButtonDown()
{
    if ((key_code[6] == 1) || (key_code[6] >= 10 && key_code[6]%2 == 0)){
        count_free_time=0;
        return 1;
    }
    else
        return 0;
}

void buttonfunction()
{
    if(key_code[5] == 1){
        ispress=1;
        
    }
    if(ispress==1){
        timepress++;
        if(timepress>15){
            ispress=0;
            isfree=0;
            timedouble=0;
            timepress=0;
            holdfunction++;
        }
        if(key_code[5] == 0){
            isfree=1;
            timepress=0;
            timedouble++;
            if(timedouble>5){
                ispress=0;
                isfree=0;
                timedouble=0;
                timepress=0;
                pressfunction++;
            }
        } 
    }
    if(isfree==1){
        if(key_code[5]==1){
            ispress=0;
            isfree=0;
            timedouble=0;
            timepress=0;
            doubleclick++;
        }
    }
}

void Get_humidity(void)
{
    adcValue = get_adc_value(1);
    humidityvalue=0 + (long)(1023 - adcValue ) * (100 - 0) / (1023 - 0);   
}
void Send_humidity(void){
    countuart++;
    if(countuart>=12000){
    countuart=0;
    UartSendString("!hu");
    UartSendNum(humidityvalue/10);
    UartSendNum(humidityvalue%10);
    uart_putchar('#');
    }
}

void watering(){
    if(count_1m%40>38||(count_1m%40>34&&count_1m%40<37)){
        PORTA = PORTA | 0b00010000;
    }else{
        PORTA = PORTA & 0b11101011;
    }
}

void get_order(){
    int temp=0;
    if(fullorder==1){
        fullorder=0;
        temp=(int)(dataReceive[3]-'0')*10+(int)(dataReceive[4]-'0');
        switch(dataReceive[1]){
            case '0':
            switch(dataReceive[2]){
                case '8':
                    write_ds1307(ADDRESS_WATER_MODE,temp);
                    break;
                case '9':
                    write_ds1307(ADDRESS_MAX_VALUE,temp);
                    break;
                case 'A':
                    write_ds1307(ADDRESS_HOUR_SCHED1,temp);
                    break;
                case 'B':
                    write_ds1307(ADDRESS_MINUTE_SCHED1,temp);
                    break;
                case 'C':
                    write_ds1307(ADDRESS_ENABLE_SCHED1,temp);
                    break;
                case 'D':
                    write_ds1307(ADDRESS_DURATION_SCHED1,temp);
                    break;
                case 'E':
                    write_ds1307(ADDRESS_FRE_SCHED1,temp);fre_turn1=0;old_day1=0;
                    break;
                case 'F':
                    write_ds1307(ADDRESS_HOUR_SCHED2,temp);
                    break;
            }
            break;
            case '1':
            switch(dataReceive[2]){
                case '0':
                    write_ds1307(ADDRESS_MINUTE_SCHED2,temp);
                    break;
                case '1':
                    write_ds1307(ADDRESS_ENABLE_SCHED2,temp);
                    break;
                case '2':
                    write_ds1307(ADDRESS_DURATION_SCHED2,temp);
                    break;
                case '3':
                    write_ds1307(ADDRESS_FRE_SCHED2,temp);fre_turn2=0;old_day2=0;
                    break;
                case '4':
                    write_ds1307(ADDRESS_HOUR_SCHED3,temp);
                    break;
                case '5':
                    write_ds1307(ADDRESS_MINUTE_SCHED3,temp);
                    break;
                case '6':
                    write_ds1307(ADDRESS_ENABLE_SCHED3,temp);
                    break;
                case '7':
                    write_ds1307(ADDRESS_DURATION_SCHED3,temp);
                    break;
                case '8':
                    write_ds1307(ADDRESS_FRE_SCHED3,temp);fre_turn3=0;old_day3=0;
                    break;
                case '9':
                    write_ds1307(ADDRESS_HOUR_SCHED4,temp);
                    break;
                case 'A':
                    write_ds1307(ADDRESS_MINUTE_SCHED4,temp);
                    break;
                case 'B':
                    write_ds1307(ADDRESS_ENABLE_SCHED4,temp);
                    break;
                case 'C':
                    write_ds1307(ADDRESS_DURATION_SCHED4,temp);
                    break;
                case 'D':
                    write_ds1307(ADDRESS_FRE_SCHED4,temp);fre_turn4=0;old_day4=0;
                    break;
                case 'E':
                    write_ds1307(ADDRESS_REST_HOUR_BEGIN,temp);
                    break;
                case 'F':
                    write_ds1307(ADDRESS_REST_MINUTE_BEGIN,temp);
                    break;
            }    
            break;
            case '2':
            switch(dataReceive[2]){
                case '0':
                    write_ds1307(ADDRESS_REST_HOUR_STOP,temp);
                    break;
                case '1':
                    write_ds1307(ADDRESS_REST_MINUTE_STOP,temp);
                    break;
                case '2':
                    write_ds1307(ADDRESS_MIN_VALUE,temp);
                    break;
                case '3':
                    write_ds1307(ADDRESS_DURATION_M2,temp);
                    break;
            }
            break;
        }
    }
}

void send_parameter(char* name,int temp){
    uart_putchar('!');
    UartSendString(name);
    UartSendNum(temp/10);
    UartSendNum(temp%10);
    uart_putchar('#');
}

void send_All_parameter(){
    send_parameter("08",read_ds1307(ADDRESS_WATER_MODE));
    send_parameter("09",read_ds1307(ADDRESS_MAX_VALUE));
    send_parameter("0A",read_ds1307(ADDRESS_HOUR_SCHED1));
    send_parameter("0B",read_ds1307(ADDRESS_MINUTE_SCHED1));
    send_parameter("0C",read_ds1307(ADDRESS_ENABLE_SCHED1));
    send_parameter("0D",read_ds1307(ADDRESS_DURATION_SCHED1));
    send_parameter("0E",read_ds1307(ADDRESS_FRE_SCHED1));
    send_parameter("0F",read_ds1307(ADDRESS_HOUR_SCHED2));
    send_parameter("10",read_ds1307(ADDRESS_MINUTE_SCHED2));
    send_parameter("11",read_ds1307(ADDRESS_ENABLE_SCHED2));
    send_parameter("12",read_ds1307(ADDRESS_DURATION_SCHED2));
    send_parameter("13",read_ds1307(ADDRESS_FRE_SCHED2));
    send_parameter("14",read_ds1307(ADDRESS_HOUR_SCHED3));
    send_parameter("15",read_ds1307(ADDRESS_MINUTE_SCHED3));
    send_parameter("16",read_ds1307(ADDRESS_ENABLE_SCHED3));
    send_parameter("17",read_ds1307(ADDRESS_DURATION_SCHED3));
    send_parameter("18",read_ds1307(ADDRESS_FRE_SCHED3));
    send_parameter("19",read_ds1307(ADDRESS_HOUR_SCHED4));
    send_parameter("1A",read_ds1307(ADDRESS_MINUTE_SCHED4));
    send_parameter("1B",read_ds1307(ADDRESS_ENABLE_SCHED4));
    send_parameter("1C",read_ds1307(ADDRESS_DURATION_SCHED4));
    send_parameter("1D",read_ds1307(ADDRESS_FRE_SCHED4));
    send_parameter("1E",read_ds1307(ADDRESS_REST_HOUR_BEGIN));
    send_parameter("1F",read_ds1307(ADDRESS_REST_MINUTE_BEGIN));
    send_parameter("20",read_ds1307(ADDRESS_REST_HOUR_STOP));
    send_parameter("21",read_ds1307(ADDRESS_REST_MINUTE_STOP));
    send_parameter("22",read_ds1307(ADDRESS_MIN_VALUE));
    send_parameter("23",read_ds1307(ADDRESS_DURATION_M2));
    send_parameter("3C",read_ds1307(ADDRESS_PASS_1));
    send_parameter("3D",read_ds1307(ADDRESS_PASS_2));
    send_parameter("3E",read_ds1307(ADDRESS_PASS_3));
    send_parameter("3F",read_ds1307(ADDRESS_PASS_4));
}
