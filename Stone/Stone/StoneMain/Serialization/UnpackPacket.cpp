#include "UnpackPacket.h"


UnpackPacket::UnpackPacket(boost::shared_ptr<const RawPacket> packet, size_t skip_bytes) 
:ptr_packet_(packet), read_position_(0)
{
    this->Read(skip_bytes);
}


UnpackPacket& UnpackPacket::operator >> (INT8& value)
{
    return this->Extract<INT8> (value);
}

UnpackPacket& UnpackPacket::operator >> (INT16& value)
{
    return this->Extract<INT16> (value);
}

UnpackPacket& UnpackPacket::operator >> (INT32& value)
{
    return this->Extract<INT32> (value);
}

UnpackPacket& UnpackPacket::operator >> (INT64& value)
{
    return this->Extract<INT64> (value);
}

UnpackPacket& UnpackPacket::operator >> (UINT8& value)
{
    return this->Extract<UINT8> (value);
}
UnpackPacket& UnpackPacket::operator >> (UINT16& value)
{
    return this->Extract<UINT16> (value);
}
UnpackPacket& UnpackPacket::operator >> (UINT32& value)
{
    return this->Extract<UINT32> (value);
}
UnpackPacket& UnpackPacket::operator >> (UINT64& value)
{
    return this->Extract<UINT64> (value);
}

UnpackPacket& UnpackPacket::operator >> (float& value)
{
    return this->Extract<float> (value);
}
UnpackPacket& UnpackPacket::operator >> (double& value)
{
    return this->Extract<double> (value);
}

UnpackPacket& UnpackPacket::operator >> (bool& value)
{
    UINT8 temp_value;
    return this->Extract<UINT8> (temp_value);

    value = (temp_value == 0) ? false : true; 
}