#ifndef THREE_H
#define THREE_H

#include <cstddef>
#include <string>
#include <initializer_list>

class Three {
public:
    Three();
    Three(const size_t& n, unsigned char t = 0);
    Three(const std::initializer_list<unsigned char>& t);
    Three(const std::string& t);
    Three(const Three& other);
    Three(Three&& other) noexcept;
    virtual ~Three() noexcept;

    Three add(const Three& other) const;
    Three subtract(const Three& other) const;
    Three copy() const;

    bool isEqual(const Three& other) const;
    bool isGreater(const Three& other) const;
    bool isLess(const Three& other) const;

    std::string toString() const;
    size_t size() const;

private:
    unsigned char* _data;
    size_t _len;

    void normalize();
    static size_t maxLen(size_t a, size_t b);
};

#endif
