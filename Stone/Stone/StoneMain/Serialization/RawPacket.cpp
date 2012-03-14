#include "RawPacket.h"

#include <string>
#include <exception>


RawPacket::RawPacket(const char* const data, const unsigned int size)
:size_(size)
{
    if ( this->size_ > 0 ) 
    {
        this->data_ = (char *) malloc(size_);

        if(this->data_ == NULL)
        {
            throw std::bad_alloc("out of memory BufBuilder");
        }

        memcpy(this->data_, data, this->size_);           
    }
    else 
    {
        this->data_ = NULL;
    }

    this->length_ = this->size_;
}

RawPacket::RawPacket(const unsigned int initsize)
: size_(initsize)
{
    if ( size_ > 0 ) 
    {
        data_ = (char *) malloc(size_);

        if(data_ == NULL)
        {
            throw std::bad_alloc("out of memory BufBuilder");
        }        
    }
    else 
    {
        data_ = NULL;
    }

    length_ = 0;
}

RawPacket::~RawPacket()
{
    Kill();
}

void RawPacket::Kill(void)
{
    if (this->data_)
    {
        free(data_);
        data_ = NULL;
    }
}

char* RawPacket::Buf(void)
{
    return this->data_;
}

const char* RawPacket::Buf(void) const
{
    return this->data_;
}

int RawPacket::Length(void) const
{
    return this->length_;
}

void RawPacket::Length(int length)
{
    this->length_ = length;
}

int RawPacket::Size(void) const
{
    return this->size_;
}


const RawPacket* RawPacketFactory::CreateRawPacket(const char* const data, const unsigned int size) 
{
    RawPacket* buffer = new RawPacket(data, size);
    return buffer;
}