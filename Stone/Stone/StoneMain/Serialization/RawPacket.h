#ifndef _ECHO_SERVER_SERIALIZATION_RAWPACKET_H_
#define _ECHO_SERVER_SERIALIZATION_RAWPACKET_H_

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

//#include "../Utilities/Noncopyable.h"

class UnpackPacket;

class RawPacket : public boost::noncopyable
{
    friend class UnpackPacket;
public:

    RawPacket(const char* const data, const unsigned int size);
    RawPacket(const unsigned int initsize = 512);
    ~RawPacket();

public:
    void Kill(void);

    char* Buf(void); 
    const char* Buf(void) const;

    int Length(void) const;
    void Length(int length);

    int Size(void) const;

protected:
    char* data_;
    unsigned int size_;
    unsigned int length_;

};

class RawPacketFactory
{
public:
    static const RawPacket* CreateRawPacket(const char* const data, const unsigned int size);
};

#endif
