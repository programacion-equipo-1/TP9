

#include <cstdlib>
#include <stdio.h>
#include <stdint.h>

typedef struct{
    
    uint8_t  b0 :1 ; //uint te permite definir un numero con cierta cantidad de bits.
    uint8_t  b1 :1 ;
    uint8_t  b2 :1 ;
    uint8_t  b3 :1 ;
    uint8_t  b4 :1 ;
    uint8_t  b5 :1 ;
    uint8_t  b6 :1 ;
    uint8_t  b7 :1 ;
    uint8_t b8 :1;
} bits_8 ;

typedef struct{
    
    uint16_t  b0 :1 ;
    uint16_t  b1 :1 ;
    uint16_t  b2 :1 ;
    uint16_t  b3 :1 ;
    uint16_t  b4 :1 ;
    uint16_t  b5 :1 ;
    uint16_t  b6 :1 ;
    uint16_t  b7 :1 ;
    uint16_t  b8 :1 ;
    uint16_t  b9 :1 ;
    uint16_t  b10 :1 ;
    uint16_t  b11 :1 ;
    uint16_t  b12 :1 ;
    uint16_t  b13 :1 ;
    uint16_t  b15 :1 ;

} D ;

typedef struct{
    bits_8 A;
    bits_8 B;
 
}AB;

typedef union{
  D D;
  AB AB;  
} registro;

static registro Registro;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Registro.AB.A.b0=1;
    printf("%d\n",Registro);
  
    Registro.D.b0=0;
    printf("%d\n",Registro);
   
    return 0;
}

