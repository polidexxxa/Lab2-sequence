#ifndef _BIT_HPP_
#define _BIT_HPP_

class Bit {
private:
    bool value;

public:
    Bit() : value(false) {}
    
    explicit Bit(bool v) : value(v) {}
    
    explicit Bit(int v) : value(v != 0) {}
    
    explicit operator bool() const { return value; }
    
    operator int() const { return value ? 1 : 0; }
    

    Bit operator!() const {
        return Bit(!value);
    }
    
    bool operator==(const Bit& other) const {
        return value == other.value;
    }
    
    bool operator!=(const Bit& other) const {
        return value != other.value;
    }
    
    
    Bit operator&(const Bit& other) const {
        return Bit(value & other.value);
    }
    
    Bit operator|(const Bit& other) const {
        return Bit(value | other.value);
    }
    
    Bit operator^(const Bit& other) const {
        return Bit(value ^ other.value);
    }
    

    Bit& operator&=(const Bit& other) {
        value &= other.value;
        return *this;
    }
    
    Bit& operator|=(const Bit& other) {
        value |= other.value;
        return *this;
    }
    
    Bit& operator^=(const Bit& other) {
        value ^= other.value;
        return *this;
    }

    static const Bit BIT0;
    static const Bit BIT1;
    
};

const Bit Bit::BIT0(false);
const Bit Bit::BIT1(true);

#endif // _BIT_HPP_