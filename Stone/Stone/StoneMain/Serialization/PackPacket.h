#ifndef _ECHO_SERVER_SERIALIZATION_PACK_PACKET_H
#define _ECHO_SERVER_SERIALIZATION_PACK_PACKET_H

#include <string>
#include <vector>
#include <iostream>

#include <cstdlib>



#include "RawPacket.h"

class PackPacket : public RawPacket
{
public:
	explicit PackPacket(const unsigned int length = 512);
	
public:
    char* Grow(size_t bytes) 
    {
        size_t old_length = this->length_;
        this->length_ += bytes;

        if (this->length_ > this->size_)
        {
            GrowReallocate();
        }

        return this->data_ + old_length;
    }
public:
     PackPacket& operator << (INT8 value);
     PackPacket& operator << (INT16 value);
     PackPacket& operator << (INT32 value);
     PackPacket& operator << (INT64 value);

     PackPacket& operator << (UINT8 value);
     PackPacket& operator << (UINT16 value);
     PackPacket& operator << (UINT32 value);
     PackPacket& operator << (UINT64 value);

     PackPacket& operator << (float value);
     PackPacket& operator << (double value);

     PackPacket& operator << (bool value);


     PackPacket& operator << (const std::string& text)
     {
         size_t size = text.size() + 1;
         std::memcpy(Grow(size), text.c_str(), size);
         return *this;
     }

     template <typename element>
     PackPacket& operator << (const std::vector<element>& vec) 
     {
         size_t size = vec.size()* sizeof(element);
         UINT32 count = vec.size();
         this->operator << (count);

         for (std::vector<element>::const_iterator ite = vec.begin();
             ite != vec.end();
             ite++)
         {
             *this << *ite;
         }

         return *this;
     };

private:
    void GrowReallocate(void)
    {
        unsigned int ReallocSize = this->size_ << 1;//* 2;
        if ( ReallocSize == 0 )
        {
            ReallocSize = 512;
        }
        if (this->length_ > ReallocSize)
        {
            ReallocSize = this->length_ + (1 << 14);//16 * 1024;
        }

        if( ReallocSize > (1 << 26) /*64 * 1024 * 1024*/ )
        {
            throw std::bad_alloc("BufBuilder grow() > 64MB");
        }

        this->data_ = (char *) realloc(this->data_, ReallocSize);

        this->size_ = ReallocSize;
    }

    template <typename T>
    PackPacket& Append(const T& t)
    {
        *((T*)Grow(sizeof(T))) = t;
        return *this;
    };

};



#endif
