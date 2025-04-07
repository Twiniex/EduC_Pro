#include "HwControl.h"
#include "PlcData.h"

bool diGetOne(uint16_t nChannel)
{
    uint16_t index  = nChannel / 16;
    uint16_t bit    = nChannel % 16;

    return (toPlc[index] & (1 << bit)) != 0;
}

bool doGetOne(uint16_t nChannel)
{
    uint16_t index  = nChannel / 16;
    uint16_t bit    = nChannel % 16;

    return (fromPlc[index] & (1 << bit)) != 0;
}

void doPutOne(uint16_t nChannel, bool bState)
{
    uint16_t index  = nChannel / 16;
    uint16_t bit    = nChannel % 16;

    fromPlc[index] = bState ? (fromPlc[index] | (1 << bit)) : (fromPlc[index] & ~(1 << bit));
}
