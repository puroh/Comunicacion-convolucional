#include "Arduino.h"
#include <stdint.h>


class comunicacion
{
public:
	uint32_t codificar(uint8_t mensaje);
        uint8_t decodificar(uint32_t mensajecod);
        void modular(uint32_t port);
        uint32_t demodular(void);
private:

	uint8_t est_act;
        int i;
        uint32_t dem=0;
        uint8_t d;
public:

	~comunicacion();
};

