/*CETI COLOMOS                                        
TGO EN CONTROL AUTOMÁTICO E INSTRUMENTACIÓN         
Práctica 2.1:Control de nivel
Martín Ricardo Del Río Grageda 15300067             
Lázaro Fabricio Torres Orozco 15300277              
01/ABRIL/2019
*/

//Directivas y variables globales
#INCLUDE <16F886.H>    
#DEVICE ADC=10;                                                
#USE DELAY(CLOCK=4000000)                                      
#INCLUDE <LCD1.C>                                              
#FUSES INTRC_IO,NOWDT,NOPUT,NOMCLR,NOPROTECT,NOCPD,NOBROWNOUT 
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21              
#BYTE TRISA = 0X85            
#BYTE PORTA = 0X05      
#BYTE TRISB = 0X86        
#BYTE PORTB = 0X06         
#BYTE TRISC = 0X87              
#BYTE PORTC = 0X07

int cuenta=0;
int tecla();
int Y=0;
int X=0xEF;
int A=0;
int SP=0;
float N=0;
float Nn=0.0;
int pot=0;

//Inicio de programa
VOID MAIN (VOID)
{
   //Dclaración de entradas y salidas e inicialización de funciones
   LCD_INIT(); 
   SETUP_ADC(ADC_CLOCK_INTERNAL);
   SETUP_ADC_PORTS(sAN0);
   TRISA=0X0F;    
   PORTA=0;
   TRISC=0XFF;
   
   //Mostrar información básica
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"CETI            \nTgo Control     ");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"LAZARO TORRES          \nREG.15300277     ");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"RICARDO DEL RIO      \nREG.15300067");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"PRACTICA 2.1      \nControl nivel");
   //No hacer nada hasta que se presione el botón
   WHILE (bit_test(PORTC,0)==0){};
   WHILE (bit_test(PORTC,0)==1){};
   while(1)
   {
      WHILE (bit_test(PORTC,0)==1){}
      WHILE (bit_test(PORTC,0)==0){
      //Obtener y mostrar el valor del potenciómetro (nivel)
      SET_ADC_CHANNEL(0);
      DELAY_US(20);
      N=READ_ADC( );
      Nn=((N/1023)*5);
      LCD_GOTOXY(1,1);
      PRINTF(LCD_PUTC,"NIVEL:%1.0f            ", (N/1023*5));
      LCD_GOTOXY(1,2);
      PRINTF(LCD_PUTC,"SP:%u            ", SP);
      //Obtener y mostrar el valor del teclado (SP)
      tecla();
      LCD_GOTOXY(1,2);
      //PRINTF(LCD_PUTC,"SP:                  ");
      if(cuenta!=13){
      if(cuenta==11)cuenta=0;
      LCD_GOTOXY(1,2);
      PRINTF(LCD_PUTC,"SP:%u                  ", Cuenta);
      SP=Cuenta;
      }
      }
      //Cuando se presione el botón se enseñará la comparación entre SP y nivel
      WHILE (bit_test(PORTC,0)==1){}
      WHILE (bit_test(PORTC,0)==0){
      Pot=Nn;
         if(SP>Pot){             //Si el SP es mayor
            LCD_GOTOXY(16,2);
            PRINTF(LCD_PUTC,"L");
         }
         if(SP==Pot){            //Si son iguales
            LCD_GOTOXY(16,2);
            PRINTF(LCD_PUTC,"E");
         }
         if(SP<Pot){             //Si el SP es menor
            LCD_GOTOXY(16,2);
            PRINTF(LCD_PUTC,"V");
         } 
      if (bit_test(PORTC,0)==1){
           break;
      }
      }
      
   }
}
int tecla(){               //Funcion para saber que tecla se presiono
   X=0xF7;
   FOR(A=0;A<=3;A++)
   {
      X=X<<1;
      PORTA=((PORTA&0X0F)|(X&0XF0));            //Configuracion de puerto
      DELAY_MS(20);
      IF(BIT_TEST(PORTA,3)==0)BREAK; 
      Y++;
      IF(BIT_TEST(PORTA,2)==0)BREAK;
      Y++;
      IF(BIT_TEST(PORTA,1)==0)BREAK;
      Y++;
   }
      cuenta=Y+1;
      y=0;
      delay_ms(20);
      return(cuenta);
}

