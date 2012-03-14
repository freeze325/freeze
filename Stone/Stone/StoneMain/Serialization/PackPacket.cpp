#include "PackPacket.h"

#include <algorithm>
#include <cstdlib>

PackPacket::PackPacket(const unsigned int length) 
: RawPacket(length)
{
    //Nothing
}

PackPacket& PackPacket::operator << (INT8 value)
{
    return this->Append<INT8> (value);
}

PackPacket& PackPacket::operator << (INT16 value)
{
    return this->Append<INT16> (value);
}

PackPacket& PackPacket::operator << (INT32 value)
{
    return this->Append<INT32> (value);
}

PackPacket& PackPacket::operator << (INT64 value)
{
    return this->Append<INT64> (value);
}

PackPacket& PackPacket::operator << (UINT8 value)
{
    return this->Append<UINT8> (value);
}

PackPacket& PackPacket::operator << (UINT16 value)
{
    return this->Append<UINT16> (value);
}

PackPacket& PackPacket::operator << (UINT32 value)
{
    return this->Append<UINT32> (value);
}

PackPacket& PackPacket::operator << (UINT64 value)
{
    return this->Append<UINT64> (value);
}

PackPacket& PackPacket::operator << (float value)
{
    return this->Append<float> (value);
}

PackPacket& PackPacket::operator << (double value)
{
    return this->Append<double> (value);
}

PackPacket& PackPacket::operator << (bool value)
{
    return this->Append<INT8> (value ? 1 : 0);
}


