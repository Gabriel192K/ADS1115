#ifndef __ADS1115_H__
#define __ADS1115_H__

/* ADS1115 16-bit ADC */
/* | ADDRESS PIN TO | ADDRESS |
   |      GND       |   0x48  |
   |      VCC       |   0x49  |
   |      SDA       |   0x4A  |
   |      SCL       |   0x4B  |
*/
#define ADS1115_CONVR ((uint8_t)0x00) /* Conversion register */

#define ADS1115_CONFR ((uint8_t)0x01) /* Configure register */
#define ADS1115_CMPQ0 0                /* Comparator queue and disable bit 0 */
#define ADS1115_CMPQ1 1                /* Comparator queue and disable bit 1 */
#define ADS1115_CMPL  2                /* Latching comparator */
#define ADS1115_CMPP  3                /* Comparator polarity */
#define ADS1115_CMPM  4                /* Comparator mode */
#define ADS1115_DR0   5                /* Data rate bit 2 */
#define ADS1115_DR1   6                /* Data rate bit 2 */
#define ADS1115_DR2   7                /* Data rate bit 2 */
#define ADS1115_MODE  8                /* Device operating mode */
#define ADS1115_PGA0  9                /* Programmable gain amplifier configuration bit 0 */
#define ADS1115_PGA1  10               /* Programmable gain amplifier configuration bit 1 */
#define ADS1115_PGA2  11               /* Programmable gain amplifier configuration bit 2 */
#define ADS1115_MUX0  12               /* Input multiplexer configuration bit 0 */
#define ADS1115_MUX1  13               /* Input multiplexer configuration bit 1 */
#define ADS1115_MUX2  14               /* Input multiplexer configuration bit 2 */
#define ADS1115_OS    15               /* Operational status or single-shot conversion start */

/* Dependecies */
#include "TWI\TWI.h"
#include "USART/USART.h"

class ADS1115
{
    public:
        typedef enum
        {
            DATA_RATE8 = 0, 
            DATA_RATE16 = 1, 
            DATA_RATE32 = 2, 
            DATA_RATE64 = 3,
            DATA_RATE128 = 4, /* Default */
            DATA_RATE250 = 5,
            DATA_RATE475 = 6,
            DATA_RATE860 = 7
        }data_rate_t;

        ADS1115(__TWI__* twi, const uint8_t address);
        uint8_t begin      (void);
        uint8_t isConnected(void);
        void    setDataRate(data_rate_t rate);
        void    setChannel (uint8_t channel);
        int16_t read       (uint8_t channel);
        int16_t read       (void);
    private:
        __TWI__* twi;
        uint16_t config;
        uint8_t address;
        uint8_t isConverting(void);
};

#endif
