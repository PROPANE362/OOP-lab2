#include "Three.h"
#include <stdexcept>
#include <algorithm>
#include <cstring>
using namespace std;

Three::Three() : _data(nullptr), _len(0) {
    _data = new unsigned char[1];
    _data[0] = 0;
    _len = 1;
}

Three::Three(const size_t& n, unsigned char t) : _data(nullptr), _len(0) {
    if (t > 2) {
        throw invalid_argument("Mojno tolko 0,1 ili 2");
    }
    if (n == 0) {
        _len = 1;
        _data = new unsigned char[1];
        _data[0] = 0;
    } else {
        _len = n;
        _data = new unsigned char[_len];
        for (size_t i = 0; i < _len; ++i) {
            _data[i] = t;
        }
    }
}

Three::Three(const initializer_list<unsigned char>& t) : _data(nullptr), _len(0) {
    if (t.size() == 0) {
        _len = 1;
        _data = new unsigned char[1];
        _data[0] = 0;
        return;
    }
    
    _len = t.size();
    _data = new unsigned char[_len];
    
    size_t i = 0;
    for (auto it = t.begin(); it != t.end(); ++it, ++i) {
        if (*it > 2) {
            delete[] _data;
            _data = nullptr;
            _len = 0;
            throw invalid_argument("Mojno tolko 0,1 ili 2");
        }
        _data[i] = *it;
    }
    normalize();
}

Three::Three(const string& t) : _data(nullptr), _len(0) {
    if (t.empty()) {
        _len = 1;
        _data = new unsigned char[1];
        _data[0] = 0;
        return;
    }
    
    _len = t.length();
    _data = new unsigned char[_len];
    
    for (size_t i = 0; i < t.length(); ++i) {
        char c = t[t.length() - 1 - i];
        if (c < '0' || c > '2') {
            delete[] _data;
            _data = nullptr;
            _len = 0;
            throw invalid_argument("idiot?");
        }
        _data[i] = c - '0';
    }
    normalize();
}

Three::Three(const Three& other) : _data(nullptr), _len(0) {
    _len = other._len;
    _data = new unsigned char[_len];
    memcpy(_data, other._data, _len);
}

Three::Three(Three&& other) noexcept : _data(other._data), _len(other._len) {
    other._data = nullptr;
    other._len = 0;
}

Three::~Three() noexcept {
    delete[] _data;
}

void Three::normalize() {
    while (_len > 1 && _data[_len - 1] == 0) {
        --_len;
    }
}

size_t Three::maxLen(size_t a, size_t b) {
    return (a > b) ? a : b;
}

Three Three::add(const Three& other) const {
    size_t len = maxLen(_len, other._len) + 1;
    unsigned char* res = new unsigned char[len];
    memset(res, 0, len);
    
    unsigned char carry = 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char a = (i < _len) ? _data[i] : 0;
        unsigned char b = (i < other._len) ? other._data[i] : 0;
        unsigned char sum = a + b + carry;
        res[i] = sum % 3;
        carry = sum / 3;
    }
    
    Three result;
    delete[] result._data;
    result._data = res;
    result._len = len;
    result.normalize();
    return result;
}

Three Three::subtract(const Three& other) const {
    if (isLess(other)) {
        throw underflow_error("Rezultat - otricatelni");
    }
    
    size_t len = _len;
    unsigned char* res = new unsigned char[len];
    memcpy(res, _data, len);
    
    unsigned char borrow = 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char b = (i < other._len) ? other._data[i] : 0;
        int diff = res[i] - b - borrow;
        if (diff < 0) {
            diff += 3;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res[i] = static_cast<unsigned char>(diff);
    }
    
    Three result;
    delete[] result._data;
    result._data = res;
    result._len = len;
    result.normalize();
    return result;
}

Three Three::copy() const {
    return Three(*this);
}

bool Three::isEqual(const Three& other) const {
    if (_len != other._len) {
        Three a = this->copy();
        Three b = other.copy();
        a.normalize();
        b.normalize();
        if (a._len != b._len) return false;
        for (size_t i = 0; i < a._len; ++i) {
            if (a._data[i] != b._data[i]) return false;
        }
        return true;
    }
    for (size_t i = 0; i < _len; ++i) {
        if (_data[i] != other._data[i]) return false;
    }
    return true;
}

bool Three::isGreater(const Three& other) const {
    size_t len1 = _len;
    size_t len2 = other._len;
    
    while (len1 > 1 && _data[len1 - 1] == 0) --len1;
    while (len2 > 1 && other._data[len2 - 1] == 0) --len2;
    
    if (len1 != len2) {
        return len1 > len2;
    }
    
    for (size_t i = len1; i > 0; --i) {
        if (_data[i - 1] != other._data[i - 1]) {
            return _data[i - 1] > other._data[i - 1];
        }
    }
    return false;
}

bool Three::isLess(const Three& other) const {
    return other.isGreater(*this);
}

string Three::toString() const {
    if (_len == 0) return "0";
    
    string s;
    s.reserve(_len);
    for (size_t i = _len; i > 0; --i) {
        s += ('0' + _data[i - 1]);
    }
    return s;
}

size_t Three::size() const {
    return _len;
}
