#include <cstdlib>
#include <stdio.h>
#include <stdint.h>

int bitSet(int puerto,int n_bit);
int bitClr(int puerto,int n_bit);
int bitGet(int puerto,int n_bit);
int bitToggle(int puerto,int n_bit);

int maskOn(int puerto,void*mascara);
int maskOff(int puerto,void*mascara);
int maskToggle(int puerto,void*mascara);

static int masterMask(int puerto,void*mascara,int operacion);
static int manip (int puerto,int n_bit,int operacion);

enum Registros {portA , portB , portD};
enum Operaciones {SETEA0, SETEA1, LEE, TOGGLE};
//en el .c


typedef struct{
    
    uint8_t  b0 :1 ; //uint te permite definir un numero con cierta cantidad de bits.
    uint8_t  b1 :1 ;
    uint8_t  b2 :1 ;
    uint8_t  b3 :1 ;
    uint8_t  b4 :1 ;
    uint8_t  b5 :1 ;
    uint8_t  b6 :1 ;
    uint8_t  b7 :1 ;
    

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
 
}structD;

typedef union{
    bits_8 bit;
    uint8_t byte;
    
}struct8;


typedef struct{
   struct8 A;
   struct8 B;  
} structAB;

typedef union{
    structAB AB;
    structD D;
    
}registro;

static registro Registro;





int main (void)
{
    manip(portA, 5 , SETEA1);
    manip(portA, 3 , SETEA1);
    manip(portA, 1 , SETEA1);
    int a= manip(portA, 1 , LEE);
    printf("%d\n",a);
    manip(portA, 1 , TOGGLE);
    a= manip(portA, 1 , LEE);
    printf("%d\n",a);
    
    
    {
        //uint16_t mask=0xFFFF;
        int i;
        for (i=15;i>=0;i--){
            printf("%d",bitGet(portD,i));
        }
        printf("\n");
        bitSet(portD,8);
        for (i=15;i>=0;i--){
            printf("%d",bitGet(portD,i));
        }
    }
}
int manip (int puerto, int nbit , int Operacion){
uint8_t *p;
    {
    switch (puerto)
    {
            case portA:
           
                if ((0<= nbit) && (nbit <=7))
                    p=&Registro.AB.A.byte;
                else
                   {
                        printf ("Error de numero de bit a modificar");
                        return -1;
                    }
                break;
            
            case portB:
            
                 if ((0<= nbit) && (nbit <=7))
                    p=&Registro.AB.B.byte;
                else
                    {
                        printf ("Error de numero de bit a modificar");
                        return -1;
                    }
                 break;
            
            case portD:
            
                if ((0<= nbit) && (nbit <=15)){
                    if ((0<= nbit) && (nbit <=7))
                    p=&Registro.AB.A.byte;
                    else if ((8<= nbit) && (nbit <=15)){
                    p=&Registro.AB.B.byte;
                    nbit -=8;
                    }
                    else 
                    {
                        printf ("Error de numero de bit a modificar");
                        return -1;
                    }
                }
                break;
            
            default:
            
                printf("No existe el puerto especificado");
                return -1; 
                break;
            
    }
   

}
switch (Operacion)
{
        case LEE:
        
            return ((*p) >> nbit)&1;
        
        case SETEA1:
        
            *p |= 1 << nbit;
            return 0;
        
        case SETEA0:
        
            *p&= ~(1 << nbit);
           return 0;
        
        case TOGGLE:
        
            *p ^= 1 << nbit;
           return 0;
        
        default:
        
            printf("Error en funcion especificada");
            return -1;
}

        
            
        
}

//NOTA:
// 0 o 1 segun la lectura
// 0 si no hay lectura
// -1 si hay error



int bitSet(int puerto,int n_bit){
	return manip(puerto,n_bit,SETEA1);
}

int bitClr(int puerto,int n_bit){
	return manip(puerto,n_bit,SETEA0);
}

int bitGet(int puerto,int n_bit){
	return manip(puerto,n_bit,LEE);
}

int bitToggle(int puerto,int n_bit){
	return manip(puerto,n_bit,TOGGLE);
}


//NOTA: en vez de mascaras, usa punteros a mascaras

int maskOn(int puerto,void*mascara){
	return masterMask(puerto,mascara,SETEA1);
}
int maskOff(int puerto,void*mascara){
	return masterMask(puerto,mascara,SETEA0);
}
int maskToggle(int puerto,void*mascara){
	return masterMask(puerto,mascara,TOGGLE);
}

static int masterMask(int puerto,void*mascara,int operacion){
	uint16_t msk;
	int aux;
	int i;

	switch(puerto){
		case portA: case portB:
			aux=8;
			msk=(uint16_t) (*(uint8_t*)mascara);
			break;
		case portD:
			aux=16;
			msk=*(uint16_t*)mascara;
			break;
		default:
			printf("ERROR: puerto no valido\n");
			return -1;
	}

	for (i=0;i<aux;i++,msk>>=1){

		if((msk&1)==1){
		/*NOTA: ya se que...
			-El puerto es bueno
			-El nro de bit es valido
			-La operacion existe */
			manip(puerto,i,operacion);
			
		}


	}

	return 0;

}
