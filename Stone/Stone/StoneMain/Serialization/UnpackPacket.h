/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

#ifndef _ECHO_SERVER_SERIALIZATION_UNPACK_PACKET_H
#define _ECHO_SERVER_SERIALIZATION_UNPACK_PACKET_H

#include <string>
#include <vector>
#include <cstring>
#include <boost/shared_ptr.hpp>

#include "RawPacket.h"
#include "exception_info.h"


class UnpackPacket
{
public:
	UnpackPacket(boost::shared_ptr<const RawPacket> packet, size_t skip_bytes = 0);
	
public:
    void Skip(size_t bytes)
    {
        this->read_position_ += bytes;

        if (this->read_position_ > this->ptr_packet_->length_)
        {
            throw UnpackPacketException("Unpack failure");
        }
    }

    char* Read(size_t bytes) 
    {
        size_t old_read_position = this->read_position_;
        this->Skip(bytes);
        return this->ptr_packet_->data_ + old_read_position;
    }

    boost::shared_ptr<const RawPacket> PtrPacket(void)
    {
        return this->ptr_packet_;
    }

    UnpackPacket& operator >> (INT8& value);
    UnpackPacket& operator >> (INT16& value);
    UnpackPacket& operator >> (INT32& value);
    UnpackPacket& operator >> (INT64& value);

    UnpackPacket& operator >> (UINT8& value);
    UnpackPacket& operator >> (UINT16& value);
    UnpackPacket& operator >> (UINT32& value);
    UnpackPacket& operator >> (UINT64& value);

    UnpackPacket& operator >> (float& value);
    UnpackPacket& operator >> (double& value);

    UnpackPacket& operator >> (bool& value);

    UnpackPacket& operator >> (std::string& text)
    {
        unsigned int i = this->read_position_;
        for(; i < this->ptr_packet_->length_; ++i)
        {
            if(this->ptr_packet_->data_[i] == '\0')
            {
                break;
            }
        }

        if(i >= this->ptr_packet_->length_)
        {
            throw UnpackPacketException("Unpack failure (string)");
        }

        text = std::string((char*)(this->ptr_packet_->data_ + this->read_position_)); 

        this->Read(text.size() + 1);

        return *this;
    };

    template <typename element>
    UnpackPacket& operator >> (std::vector<element>& vec)
    {
        UINT32 size = 0;
        this->operator >>(size);

        for (UINT32 index = 0; index < size; index++)
        {
            element items;
            *this >> items;
            vec.push_back(items);
        }

        return *this;
    };

private:

    template <typename T>
    UnpackPacket& Extract(T& t)
    {
        t = (*((T*)Read(sizeof(T))));
        return *this;
    };

private:
	boost::shared_ptr<const RawPacket> ptr_packet_;
    unsigned int read_position_;
};


#endif
