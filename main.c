#include "msp430_version.h" 
#include "osc.h"
#include "flash.h"
char hora1;
char hora2;
char hora3;
char min1;
char min2;
char min3;
char modo;

extern char hora1_ret;
extern char hora2_ret;
extern char hora3_ret;
extern char min1_ret;
extern char min2_ret;
extern char min3_ret;
extern char modo_ret;


int segmento;

void main(void){
  
    osc_init_xt2();
    WDTCTL = WDTPW + WDTHOLD;
    //codigo de ejemplo:
    hora1=02;
    min1=20;
    hora2=03;
    min2=22;
    hora3=04;
    min3=30;    
    modo=0;
    segmento=0;
    flash_operation (segmento, hora1, min1, hora2, min2, hora3, min3, modo);    
    
}