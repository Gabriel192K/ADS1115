#include "ADS1115.h"

ADS1115::ADS1115(__TWI__* twi, const uint8_t address)
{
    this->twi = twi;
    this->address = address;
}

uint8_t ADS1115::begin(void)
{
    this->twi->begin();
    if (!this->isConnected()) return (0);

    this->setDataRate(DATA_RATE860);

    this->config |= (1 << ADS1115_PGA1) | (1 << ADS1115_MODE) | (1 << ADS1115_CMPQ1) | (1 << ADS1115_CMPQ0);
    this->twi->beginTransmission(this->address); /* Begin transmission to address */
    this->twi->write(ADS1115_CONFR);             /* Access conversion register */
    this->twi->write((uint8_t)(config >> 8));    /* Write LSB */
    this->twi->write((uint8_t)config);           /* Write MSB */
    this->twi->endTransmission();                /* End trnasmission to address */

    return (1);
}

uint8_t ADS1115::isConnected(void)
{
    uint8_t state = this->twi->beginTransmission(address);
    this->twi->endTransmission();
    return (state);
}

void ADS1115::setDataRate(data_rate_t rate)
{
    this->config = this->config & ~((1 << ADS1115_DR2) | (1 << ADS1115_DR1) | (1 << ADS1115_DR0)); /* Clear data rate bits */
    this->config |= (rate << ADS1115_DR0);
}

void ADS1115::setChannel(uint8_t channel)
{
    channel %= 4;
    this->config &= ~((1 << ADS1115_MUX2) | (1 << ADS1115_MUX1) | (1 << ADS1115_MUX0)); /* Clear MUX bits */
    channel += 4;                                                                       /* Offset channel becuase first 4 channels are for comparator */
    this->config |= (channel << ADS1115_MUX0);

    this->config |= (1 << ADS1115_OS);
    this->twi->beginTransmission(this->address); /* Begin transmission to address */
    this->twi->write(ADS1115_CONFR);             /* Access conversion register */
    this->twi->write((uint8_t)(config >> 8));    /* Write LSB */
    this->twi->write((uint8_t)config);           /* Write MSB */
    this->twi->endTransmission();                /* End trnasmission to address */
}

uint8_t ADS1115::isConverting(void)
{
    this->twi->beginTransmission(this->address);                                   /* Begin transmission to address */
    this->twi->write(ADS1115_CONFR);                                               /* Access conversion register */
    if (this->twi->requestFrom(this->address, 2) != 2) return (0);                 /* Request data and check if data can be received */ 
    this->config = ((uint8_t)this->twi->read() << 8) | (uint8_t)this->twi->read(); /* Read data from ADC */
    this->twi->endTransmission();                                                  /* End trnasmission to address */

    return (((this->config >> ADS1115_OS) & 1) == 0);
}

int16_t ADS1115::read(void)
{
    while (this->isConverting());

    this->twi->beginTransmission(this->address);                                   /* Begin transmission to address */
    this->twi->write(ADS1115_CONVR);                                               /* Access conversion register */
    if (this->twi->requestFrom(this->address, 2) != 2) return (0);                 /* Request data and check if data can be received */ 
    int16_t data = ((uint8_t)this->twi->read() << 8) | (uint8_t)this->twi->read(); /* Read data from ADC */
    this->twi->endTransmission();                                                  /* End trnasmission to address */
    return (data);
}

int16_t ADS1115::read(uint8_t channel)
{
    this->setChannel(channel);
    return (this->read());
}




