

#include <cstdlib>
#include <stdio.h>
#include <stdint.h>

typedef struct{
    
    uint8_t  a :1 ; //uint te permite definir un numero con cierta cantidad de bits.
    uint8_t  b :1 ;
    uint8_t  c :1 ;
    uint8_t  d :1 ;
    uint8_t  e :1 ;
    uint8_t  f :1 ;
    uint8_t  g :1 ;
    uint8_t  h :1 ;
    uint8_t i :1;
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

} bits_16 ;

typedef union{
    uint16_t word;
    bits_16 bit;
 
}D;

typedef struct{
    bits_8 bit;
    uint8_t byte;
    
}A;

typedef struct{
    bits_8 bit;
    uint8_t byte;
}B;

typedef struct{
   A A;
   B B;  
} AB;




/*
 * 
 */
int main(int argc, char** argv) {
    
    return 0;
}
