#include "flash.h"
char hora1_ret;
char hora2_ret;
char hora3_ret;
char min1_ret;
char min2_ret;
char min3_ret;
char modo_ret;

/**************************************************
* Nombre    		: flash_erase_segment
* returns		: void
* arg1			: address byte to be erased 
* Creada por		: Choro vidal 
* Fecha creación	: 04/12/2017
* Descripción		: Borra lo que hay en la memoria flash en el segmento partiendo en addr. 
Se debe borrar el contenido de la flash antes de escribir en la flash.
**************************************************/

//0x1000 Segmento B | 0x1080 Segmento A
void flash_erase_segment(int seg_erase){
  int *addr;
  if(seg_erase==0){                    // Si seg_erase es 0 borra segmento A
    addr =(int*)0x1080;                      
    }
  else if (seg_erase==1){              // Si seg_erase es 1 borra segmento B.
    addr = (int *)0x1000;
  }
  _DINT();
  while(BUSY & FCTL3);
  FCTL2 = FWKEY + FSSEL_1 + FN1 + FN2 + FN4;
  FCTL1 = FWKEY + ERASE;  
  FCTL3 = FWKEY;
  *addr=0;
  while(BUSY & FCTL3);
  FCTL1 = FWKEY;  
  FCTL3 = FWKEY + LOCK; 
  _EINT();
}

/**************************************************
* Nombre    		: flash_write_byte 
* returns		: void
* arg1			: address byte to be erased 
* Creada por		: Choro videl 
* Fecha creación	: 04/12/2017
* Descripción		: Guarda en *addr la variabl var_save, asumiendo que se borró la dirección anteriormente 
**************************************************/
void flash_write_byte(int seg_save, char var1, char var2, char var3, char var4, char var5, char var6, char modo){ //Deberia indicar el segmento A o segmento B. 
  _DINT();
  char *add;
  if(seg_save==0){                    // Si seg_erase es 0 empieza a escribir en segmento A.
    add = (char *) 0x1080;                      
    }
  else if (seg_save==1){              // Si seg_erase es 1 empieza a escribir en segmento B.
    add = (char *) 0x1000;
    }
  while(BUSY & FCTL3);
  FCTL2 = FWKEY + FSSEL_1 + FN1 + FN2 + FN4;
  FCTL3 = FWKEY;
  FCTL1 = FWKEY + WRT;
  if(*add!=var1){
    *add=var1;
  }
  add++;
  if(*add!=var2){
    *add=var2;
  }
  add++;
  if(*add!=var3){
    *add=var3;
  }
  add++;
  if(*add!=var4){
    *add=var4;
  }
  add++;
  if(*add!=var5){
    *add=var5;
  }
  add++;
  if(*add!=var6){
    *add=var6;
  }
  add++;
  if(*add!=modo){
    *add=modo;
  }
  while(BUSY & FCTL3);
  FCTL1 = FWKEY;
  FCTL3 = FWKEY + LOCK;
  _EINT();
}


/**************************************************
* Nombre    		: flash_read_data 
* returns		: char
* arg1			: address byte to be erased 
* Creada por		: Choro vidal 
* Fecha creación	: 04/12/2017
* Descripción		: Segun la variable "valor" retorna un char correspondiente a las horas
o minutos que se desea
**************************************************/
//seg_read=0 segmento A | seg_read=1 segmento B
void flash_read_data(int seg_read){
   int *flash_mem;
   if (seg_read==0){
    flash_mem = (int *) 0x1080;
    }
   else if (seg_read==1){
    flash_mem = (int *)0x1000;
   }
   hora1_ret=*flash_mem;
   min1_ret=*flash_mem+1;
   hora2_ret=*flash_mem+2;
   min2_ret=*flash_mem+3;
   hora3_ret=*flash_mem+4;
   min3_ret=*flash_mem+5;
   modo_ret=*flash_mem+6;      
}

/**************************************************
* Nombre    		: flash_operation 
* returns		: char
* arg1			: address byte to be erased 
* Creada por		: Choro vidal 
* Fecha creación	: 04/12/2017
* Descripción		: 
**************************************************/
void flash_operation (int segmento, char hora1, char min1, char hora2, char min2, char hora3, char min3, char modo){
  flash_erase_segment(segmento);
  flash_write_byte(segmento, hora1, min1, hora2, min2, hora3, min3, modo);
  flash_read_data(segmento);
}


