#include "comunicacion.h"

uint32_t comunicacion::codificar(uint8_t mensaje)
{
        uint32_t mcod,mcodi=0;
        est_act=0;

    for(i=7;i>=0;i--){

        mcod= ((((mensaje)&(1<<i))>>i)<<3);

        mcod|= (((((mensaje)&(1<<i))>>i)^(est_act&1)^((est_act&(1<<1))>>1)^((est_act&(1<<2))>>2))<<2);

        mcod|=   ((((mensaje)&(1<<i))>>i)^((est_act&(1<<1))>>1))<<1;

        mcod|=  ((est_act&1)^((est_act&(1<<1))>>1)^((est_act&(1<<2))>>2));

        est_act= est_act | ((((mensaje)&(1<<i))>>i)<<3);

        est_act=est_act>>1;

        mcodi|= (mcod<<(4*i));
        }

        return mcodi;
}

uint8_t  comunicacion::decodificar(uint32_t mensajecod)
{
        uint8_t mess=0;
        est_act=0;


        for(i=7;i>=0;i--){

        if(est_act==0){
            if(((mensajecod<<(7-i)*4)>>(28))==14){
                mess|=1<<i;est_act=4;}
            else
                est_act=0;

        }


        if(est_act==1){
            if(((mensajecod<<(7-i)*4)>>(28))==11){
                mess|=1<<i;est_act=4;}
            else if(((mensajecod<<(7-i)*4)>>(28))==5)
                est_act=0;

        }

                if(est_act==2){
            if(((mensajecod<<(7-i)*4)>>(28))==9){
                mess|=1<<i;est_act=5;}
             else if(((mensajecod<<(7-i)*4)>>(28))==7)
                est_act=1;

        }


                if(est_act==3){
            if(((mensajecod<<(7-i)*4)>>(28))==12){
                mess|=1<<i;est_act=5;}
            else if(((mensajecod<<(7-i)*4)>>(28))==2)
                est_act=1;

        }

              if(est_act==4){
            if(((mensajecod<<(7-i)*4)>>(28))==11){
                mess|=1<<i;est_act=6;}
            else if(((mensajecod<<(7-i)*4)>>(28))==5)
                est_act=2;

        }

                if(est_act==5){
            if(((mensajecod<<(7-i)*4)>>(28))==14){
                mess|=1<<i;est_act=6;}
            else if(((mensajecod<<(7-i)*4)>>(28))==1)
                est_act=2;

        }

               if(est_act==6){
            if(((mensajecod<<(7-i)*4)>>(28))==12){
                mess|=1<<i;
                est_act=7;
                    }
            else if(((mensajecod<<(7-i)*4)>>(28))==2)
                est_act=3;

        }

                if(est_act==7){
            if(((mensajecod<<(7-i)*4)>>(28))==9){
                mess|=1<<i;est_act=7;}
            else if(((mensajecod<<(7-i)*4)>>(28))==7)
                est_act=3;

        }



        }

        return mess;

}

void comunicacion::modular(uint32_t port){
            
         for(i=4;i>0;i--){
            digitalWrite(8,(uint8_t)((port<<(4-i)*8)>>24));  
         }
}


uint32_t comunicacion::demodular(void)
{
      
    for(i=4;i>0;i--){
            d=(((analogRead(A0))/4)<<((4-i)*8));
            dem|=d;
            Serial.print("Dato Leido: ");
            Serial.println(d);   
         }
    return dem;

}

comunicacion::~comunicacion()
{
	//destructor por defecto
}
