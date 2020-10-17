/*CETI COLOMOS 
  TGO EN CONTROL AUTOMÁTICO E INSTRUMENTACIÓN
  Práctica 1.2:Control de temperatura
  Martín Ricardo Del Río Grageda 15300067
  Lázaro Fabricio Torres Orozco 15300277
  26/FEBRERO/2019
  */
 #INCLUDE <16F886.H>                                              //Inicio del programa            
 #DEVICE ADC=10                                                   //Directivas y variables globales      
 #USE DELAY(CLOCK=4000000)
 #INCLUDE <LCD1.C>
 #FUSES INTRC_IO,NOWDT,NOPUT,NOMCLR,NOPROTECT,NOCPD,NOBROWNOUT
 #FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21
 #BYTE TRISA=0X85
 #BYTE PORTA=0X05
 #BYTE TRISB=0X86
 #BYTE PORTB=0X06
 #BYTE TRISC=0X87
 #BYTE PORTC=0X07
 signed int u=0;
 signed int d=0;
 int32 sp=0;
 int32 A=0;
 int32 Temp=0;
 int32 time=2000;
 
void main(void){                                                   //Inicio del programa principal
 LCD_INIT( );                                                 
 TRISA=0xF8;                                                   
 TRISB=0X00;
 TRISC=0XFF;
 while(1){
    SETUP_ADC(ADC_CLOCK_INTERNAL);
    SET_ADC_CHANNEL(3);
    SETUP_ADC_PORTS(sAN3);
    BIT_CLEAR(PORTA,0);
    BIT_CLEAR(PORTA,1);
    BIT_CLEAR(PORTA,2);
    while(BIT_TEST(PORTC, 4)==0){                                    //Mostrar información básica
       LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"CETI            \nTgo Control     ");
       if(BIT_TEST(PORTC, 4)==1)break;
       delay_ms(time);
       if(BIT_TEST(PORTC, 4)==1)break;
       LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"LAZARO TORRES          \nREG.15300277     ");
       if(BIT_TEST(PORTC, 4)==1)break;
       delay_ms(time);
       if(BIT_TEST(PORTC, 4)==1)break;
       LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"RICARDO DEL RIO      \nREG.15300067");
       if(BIT_TEST(PORTC, 4)==1)break;
       delay_ms(time);
       if(BIT_TEST(PORTC, 4)==1)break;
       LCD_GOTOXY(1,1);
       PRINTF(LCD_PUTC,"PRACTICA 1.2      \nCONTROL TEMP");
       if(BIT_TEST(PORTC, 4)==1)break;
       delay_ms(time);}
    LCD_GOTOXY(1,1);
    PRINTF(LCD_PUTC,"   Ajuste  SP            \n                ");        //Ajuste de SP 
    while(BIT_TEST(PORTC, 4)==1){}                                
    while(BIT_TEST(PORTC, 4)==0){
       if(bit_test(portc,0)==1){                             //Unidades menos
          delay_ms(40);
          u=u-1;}
       while(bit_test(portc,0)==1){}
       if(bit_test(portc,1)==1){                           //Unidades más            
          delay_ms(40);
          u=u+1;}
       while(bit_test(portc,1)==1){}
      if(bit_test(portc,2)==1){                              //Decenas menos
          delay_ms(40);
          d=d-1;
          sp=d*10+u;}          
      while(bit_test(portc,2)==1){}
      if(bit_test(portc,3)==1){                              //Decenas más   
          delay_ms(40);
          d=d+1;}
      while(bit_test(portc,3)==1){}
      if(d==10)d=0;
      if(u==10)u=0;
      if(u<0)u=9;
      if(d<0)d=9;
      sp=d*10+u;
      if(d==0){
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"   Ajuste  SP       \n       0%lu            ",sp);}
      if(d!=0){
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"   Ajuste  SP            \n       %lu            ",sp);}
    }
    while(BIT_TEST(PORTC, 4)==1){}                               
    while(BIT_TEST(PORTC, 4)==0){                           //Leer temperatura
    A=READ_ADC();
    Temp=(A/2.046);
    LCD_GOTOXY(1,1);
    PRINTF(LCD_PUTC,"SP= %lu          \nLM35= %lu         ",sp,Temp);}
    while(BIT_TEST(PORTC, 4)==1){}                                
    while(BIT_TEST(PORTC, 4)==0){            //Hacer comparaciones
       if (sp<temp){
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"    SP<LM35        \n     %lu < %lu         ",sp,Temp);
         BIT_SET(PORTA,0);
         BIT_CLEAR(PORTA,1);
         BIT_CLEAR(PORTA,2);}
       if (sp==temp){
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"    SP=LM35        \n     %lu = %lu         ",sp,Temp);
         BIT_CLEAR(PORTA,0);
         BIT_SET(PORTA,1);
         BIT_CLEAR(PORTA,2);}
       if (sp>temp){
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"    SP>LM35        \n     %lu > %lu         ",sp,Temp);
         BIT_CLEAR(PORTA,0);
         BIT_CLEAR(PORTA,1);
         BIT_SET(PORTA,2);}
    }
 }
}
