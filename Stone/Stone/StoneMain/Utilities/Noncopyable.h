#ifndef _STONE_NONCOPYABLE_H_
#define _STONE_NONCOPYABLE_H_


class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
private:  // emphasize the following members are private
    Noncopyable( const Noncopyable& );
    const Noncopyable& operator=( const Noncopyable& );
};


#endif