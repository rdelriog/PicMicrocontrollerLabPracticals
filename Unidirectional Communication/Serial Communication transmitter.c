/*CETI COLOMOS                                        
TGO EN CONTROL AUTOMÁTICO E INSTRUMENTACIÓN         
Práctica 2.4: Comunicación serial                      
Martín Ricardo Del Río Grageda 15300067             
Lázaro Fabricio Torres Orozco 15300277              
06/MAYO/2019*/

//DECLARAMOS LAS DIRECTIVAS QUE VAMOS A USAR
#INCLUDE <16F886.H>                                            
#USE DELAY(CLOCK=4000000)                                      
#INCLUDE <LCD1.C>                                              
#FUSES INTRC_IO,NOWDT,NOPUT,MCLR,NOPROTECT, NOCPD,NOBROWNOUT 
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21  
#BYTE TRISA = 0X85            
#BYTE PORTA = 0X05      
#BYTE TRISB = 0X86        
#BYTE PORTB = 0X06         
#BYTE TRISC = 0X87              
#BYTE PORTC = 0X07
#USE RS232(BAUD=9600, XMIT=PIN_C6, RCV=PIN_C7, BITS=8)

//DECLARACIÓN DE VARIABLES TECLADO
INT CUENTA_TECLADO,CUENTA_BARRIDO,BARRIDO,TECLA=0;
INT TECLADO();
INT ARRAY_TECLA[16]={1,2,3,16,4,5,6,16,7,8,9,16,10,0,11,16};

//DECLARACIÓN DE VARIABLES GLOBALES
INT CANAL, POT = 0;

//INTERRUPCIÓN PARA OBTENER EL VALOR ENVIADO POR EL PIC 2
#INT_RDA
VOID RDA_ISR(){
   POT = GETC();
}

//FUNCIÓN PARA UTILIZAR EL TECLADO MATRICIAL
INT TECLADO(){
   CUENTA_TECLADO=0;
   BARRIDO=0B11110111;
   
   FOR(CUENTA_BARRIDO=0; CUENTA_BARRIDO<=3; CUENTA_BARRIDO++)
   {
      BARRIDO=BARRIDO<<1;
      PORTA=((PORTA&0X0F)|(BARRIDO&0XF0));
      DELAY_MS(20);
      
      IF(BIT_TEST(PORTA,0)==0)
      {
         WHILE(BIT_TEST(PORTA,0)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
      IF(BIT_TEST(PORTA,1)==0)
      {
         WHILE(BIT_TEST(PORTA,1)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
      IF(BIT_TEST(PORTA,2)==0)
      {
         WHILE(BIT_TEST(PORTA,2)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
      IF(BIT_TEST(PORTA,3)==0)
      {
         WHILE(BIT_TEST(PORTA,3)==0){}
         BREAK;
      }
      CUENTA_TECLADO++;
   }
   IF(CUENTA_TECLADO!=3&&CUENTA_TECLADO!=7&&CUENTA_TECLADO!=11&&CUENTA_TECLADO!=15&&CUENTA_TECLADO!=16)
   {
      TECLA=ARRAY_TECLA[CUENTA_TECLADO];
   }
   RETURN(TECLA);
}

//PROGRAMA PRINCIPAL
VOID MAIN(){
   //DECLARACIÓN DE PUERTOS E INICIALIACIÓN DE FUNCIONES
   TRISA=0X0F;
   TRISB=0X00;
   TRISC=0B10000000;
   ENABLE_INTERRUPTS(GLOBAL);
   ENABLE_INTERRUPTS(INT_RDA); 
   LCD_INIT();
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"CETI             \nTGO CONTROL     ");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"LAZARO TORRES    \nREG 15300277    ");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"RICARDO DEL RIO  \nREG 15300067    ");
   delay_ms(500);
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"PRACTICA 2.4     \nCOM SERIAL      ");
   
   //MIENTRAS NO SE PULSE LA TECLA * EL MENÚ NO VA A CAMBIAR
   WHILE(TECLA != 10){
      TECLADO();
      PUTC(TECLA);
   }
      
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC,"ELIJA CANAL 0-4  \n                ");
   
   TECLA = 255;
   WHILE(TECLA == 255)
      TECLADO();

   WHILE(TRUE){
      TECLADO();
      //SI LA TECLA ES MAYOR A 4 NO SE PERMITE SELECIONAR EL CANAL
      IF(TECLA > 4){
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC," CANAL INVALIDO");
         DELAY_MS(500);
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"ELIJA CANAL 0-4  \n                ");
         
         TECLA = 255;
         WHILE(TECLA == 255)
            TECLADO();
      //SI LA TECLA ES MENOR A 4 SE PERMITE SELECIONAR EL CANAL Y
      //SE ENVÍA POR LA COMUNICACIÓN SERIAL AL PIC2
      }ELSE{
         CANAL = TECLA;
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC,"CANAL ELEGIDO %U   \nVALOR: %U   ",TECLA, POT);
         PUTC(CANAL);
      }
   }
}
