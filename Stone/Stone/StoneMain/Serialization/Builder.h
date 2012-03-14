#ifndef _STONE_SERIALIZATION_BUILDER_H_
#define _STONE_SERIALIZATION_BUILDER_H_

#include <string>
#include <string.h>
#include <stdio.h>
#include <exception>


class BufBuilder
{
public:
    BufBuilder(int initsize = 512) : size(initsize) 
    {
        if ( size > 0 )
        {
            data = (char *) malloc(size);
            if( data == NULL )
            {
                throw bad_alloc("out of memory BufBuilder");
            }

        } else 
        {
            data = NULL;
        }

        l = 0;
    }

    ~BufBuilder()
    {
        kill();
    }

    void kill() 
    {
        if ( data ) 
        {
            free(data);
            data = NULL;
        }
    }

    void reset( int maxSize = 0 )
    {
        l = 0;

        if ( maxSize && size > maxSize )
        {
            free(data);
            data = (char*)malloc(maxSize);
            size = maxSize;
        }            
    }

    /* leave room for some stuff later */
    char* skip(int n) { return grow(n); }

    /* note this may be deallocated (realloced) if you keep writing. */
    char* buf() { return data; }
    const char* buf() const { return data; }

    /* assume ownership of the buffer - you must then free() it */
    void decouple() { data = NULL; }

    void appendChar(char j)
    {
        *((char*)grow(sizeof(char))) = j;
    }
    void appendNum(char j)
    {
        *((char*)grow(sizeof(char))) = j;
    }
    void appendNum(short j) {
        *((short*)grow(sizeof(short))) = j;
    }
    void appendNum(int j)
    {
        *((int*)grow(sizeof(int))) = j;
    }
    void appendNum(unsigned j)
    {
        *((unsigned*)grow(sizeof(unsigned))) = j;
    }
    void appendNum(bool j) 
    {
        *((bool*)grow(sizeof(bool))) = j;
    }
    void appendNum(double j)
    {
        *((double*)grow(sizeof(double))) = j;
    }
    void appendNum(long long j)
    {
        *((long long*)grow(sizeof(long long))) = j;
    }
    void appendNum(unsigned long long j)
    {
        *((unsigned long long*)grow(sizeof(unsigned long long))) = j;
    }

    void appendBuf(const void *src, size_t len)
    {
        memcpy(grow((int) len), src, len);
    }

    int len() const
    {
        return l;
    }

    void setlen( int newLen )
    {
        l = newLen;
    }

    /* returns the pre-grow write position */
    inline char* grow(int by)
    {
        int oldlen = l;
        l += by;
        if ( l > size ) 
        {
            grow_reallocate();
        }
        return data + oldlen;
    }

    int getSize() const { return size; }

private:
    /* "slow" portion of 'grow()'  */
    void grow_reallocate()
    {
        int a = size * 2;

        if ( a == NULL )
        {
            a = 512;
        }

        if ( l > a )
        {
            a = l + 16 * 1024;
        }

        if( a > 64 * 1024 * 1024 )
        {
            throw bad_alloc("BufBuilder grow() > 64MB");
        }

        data = (char *) realloc(data, a);
        size= a;
    }

    char *data;
    int l;
    int size;
};

#endif

