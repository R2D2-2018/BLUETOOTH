#ifndef IO_STREAM
#define IO_STREAM

#include "../wrap-hwlib.hpp"

/**
 * @brief Interface inheriting hwlib::istream and hwlib::ostream
 *
 * @details
 * The purpose of this interface is to merge the istream and ostream.
 */
class IOStream : public hwlib::istream, public hwlib::ostream {
  public:
    virtual void putc(char c) = 0;
    virtual void puts(const char *str) = 0;
    virtual unsigned int count_available() = 0;
    virtual char getc() = 0;

    void operator<<(const char *str) {
        puts(str);
    }

    void operator<<(const char c) {
        putc(c);
    }

    void operator>>(char &c) {
        c = getc();
    }
};

#endif // IO_STREAM
