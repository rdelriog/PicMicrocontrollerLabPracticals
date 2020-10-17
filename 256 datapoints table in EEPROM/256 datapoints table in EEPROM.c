/*CETI COLOMOS                                        
TGO EN CONTROL AUTOMÁTICO E INSTRUMENTACIÓN         
Práctica 2.2: Contador con eeprom                      
Martín Ricardo Del Río Grageda 15300067             
Lázaro Fabricio Torres Orozco 15300277              
07/MARZO/2019*/

//DECLARAMOS LAS DIRECTIVAS QUE VAMOS A USAR
#INCLUDE <16F886.H>                                            
#USE DELAY(CLOCK=4000000)                                      
#INCLUDE <LCD1.C>                                              
#FUSES INTRC_IO,NOWDT,NOPUT,MCLR,NOPROTECT,NOCPD,NOBROWNOUT 
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21              
#BYTE TRISA = 0X85            
#BYTE PORTA = 0X05      
#BYTE TRISB = 0X86        
#BYTE PORTB = 0X06         
#BYTE TRISC = 0X87              
#BYTE PORTC = 0X07
int tecla();
void dato();
long int U=0, D=0, C=0, info=0, guardar=0, guardar1=0,direccion=0, direccion1=0;  
int estado=0, A=0, Y=0, X=0xEF, cuenta=0;

VOID MAIN(VOID)
{
   //CONGIFURACIÓN DE ENTRADAS Y SALIDAS DE LOS PUERTOS
   TRISA=0XFF;
   TRISB=0X00;
   TRISC=0X0F;
   LCD_INIT();
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"CETI             \nTgo Control     "); //DATOS DE LA PRACTICA
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"LAZARO TORRES    \nREG 15300277    ");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"RICARDO DEL RIO  \nREG 15300067    ");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"PRACTICA 2.3     \nTabla 256 datos");
   delay_ms(500);
while(1)
   {
      if(estado==0)           //1ER PASO: GUARDAR DATO
      {
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"Elegir dato a     \nguardar=           ");
         dato();
         if(cuenta==12)estado=3;
         guardar=info; 
         if(estado==0&&guardar>255) //DATO INVALIDO
         {
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC,"Dato inválido     \nIngrese <255         ");
            delay_ms(500);
            estado=0;
            U=0;
            D=0;
            C=0;
         }
         if(estado==0&&guardar<=255)estado=1;
         info=0;
         U=0;
         D=0;
         C=0;
         cuenta=0;
      }
      if(estado==1)        //ELEGIR DIRECCION DE MEMORIA
      {
         tecla();
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"Elegir direccion \ndireccion=       ");
         cuenta=0;
         dato();
         direccion=info;
         if(direccion>255)    //DATO INVALIDO
         {
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC,"Dato inválido     \nIngrese <255   ");
            delay_ms(500);
            estado=1;
            U=0;
            D=0;
            C=0;
         }
         else
         {
         estado=2;
         info=0;
         U=0;
         D=0;
         C=0;
         cuenta=0;
         }
       }
       if(estado==2)    //MOSTRAR AMBOS DATOS
       {
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"Valor=%03lu         \nDir=%03lu              ",guardar, direccion); 
         delay_ms(500);
         estado=0;
         WRITE_EEPROM(direccion,guardar);          //GUARDAR DATO EN LA DIRECCION INDICADA
       }
       if(estado==3)                            //LEER DIRECCION
       {
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"      Leer         \n    Direccion              "); 
         delay_ms(500);
         tecla();
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"Elegir direccion \ndireccion=       ");
         cuenta=0;
         dato();
         direccion1=info;
         if(direccion1>255)         //DATO INVÁLIDO
         {
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC,"Dato inválido     \nIngrese <255   ");
            delay_ms(500);
            estado=3;
            U=0;
            D=0;
            C=0;
         }
         else
         {
         estado=4;
         info=0;
         U=0;
         D=0;
         C=0;
         cuenta=0;
         }
       }
       if(estado==4)       //MOSTRAR VALOR PEDIDO
       {
         guardar1=READ_EEPROM(direccion1);     
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"Valor=%03lu         \nDir=%03lu              ",guardar1, direccion1); 
         delay_ms(500);
         estado=0;
       }
   }
}   
int tecla(){               //Funcion para saber que tecla se presiono
   X=0B11110111;
   FOR(A=0;A<=3;A++)
   {
      X=X<<1;
      PORTC=((PORTC&0X0F)|(X&0XF0));            //Configuracion de puerto
      DELAY_MS(20);
      IF(BIT_TEST(PORTC,0)==0)BREAK; 
      Y++;
      IF(BIT_TEST(PORTC,1)==0)BREAK;
      Y++;
      IF(BIT_TEST(PORTC,2)==0)BREAK;
      Y++;
   }
      cuenta=Y+1;
      y=0;
      delay_ms(20);
      return(cuenta);
}

void dato()          //FUNCION PARA SABER Y VER DATO DE 3 DIGITOS
{
  while(cuenta!=10)
  {
   tecla();
   if(cuenta==10)break;
   if(cuenta==12)break;
   while(cuenta>12)
   {
      tecla();
      if(cuenta==10)break;
      if(cuenta==12)break;
   }
   if(cuenta==10)break;
   if(cuenta==12)break;
   C=cuenta;
   while(cuenta==C)tecla();
   if (C==11) C=0;
   cuenta=0;
   tecla();
   if(cuenta==10)break;
   if(cuenta==12)break;
   info=C*100+D*10+U;
   LCD_GOTOXY(12,2);
   PRINTF(LCD_PUTC,"%03lu", info);
   if(cuenta==10)break;
   if(cuenta==12)break;
   while(cuenta>12)
   {
      tecla();
      if(cuenta==10)break;
      if(cuenta==12)break;
   }
   if(cuenta==10)break;
   if(cuenta==12)break;
   D=cuenta;
   while(cuenta==D)tecla();
   if (D==11) D=0;
   cuenta=0;
   tecla();
   if(cuenta==10)break;
   if(cuenta==12)break;
   info=C*100+D*10+U;
   LCD_GOTOXY(12,2);
   PRINTF(LCD_PUTC,"%03lu", info);
   if(cuenta==10)break;
   if(cuenta==12)break;
   while(cuenta>=12)
   {
      tecla();
      if(cuenta==10)break;
      if(cuenta==12)break;
   }
   if(cuenta==10)break;
   if(cuenta==12)break;
   U=cuenta;
   while(cuenta==U)tecla();
   if (U==11) U=0;
   cuenta=0;
   tecla();
   if(cuenta==10)break;
   if(cuenta==12)break;
   info=C*100+D*10+U;
   LCD_GOTOXY(12,2);
   PRINTF(LCD_PUTC,"%03lu", info);
   if(cuenta==10)break;
   if(cuenta==12)break;
 }
}
