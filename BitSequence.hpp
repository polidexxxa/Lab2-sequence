#ifndef _BIT_SEQUENCE_HPP_
#define _BIT_SEQUENCE_HPP_

#include "Sequence.hpp"
#include "Exceptions.hpp"
#include "Bit.hpp"

class BitSequence : public Sequence<Bit> {
private:
    unsigned char* data;
    int bitCount;
    int byteCount;

    void setBit(int index, bool value) {
        if (index < 0 || index >= bitCount) {
            throw IndexOutOfRangeException("Bit index out of range");
        }
        
        int byteIndex = index / 8;
        int bitInByte = index % 8;
        
        if (value) {
            data[byteIndex] |= (1 << bitInByte);
        } 
        else {
            data[byteIndex] &= ~(1 << bitInByte);
        }
    }

    bool getBit(int index) const {
        if (index < 0 || index >= bitCount) {
            throw IndexOutOfRangeException("Bit index out of range");
        }
        
        int byteIndex = index / 8;
        int bitInByte = index % 8;
        
        return (data[byteIndex] >> bitInByte) & 1;
    }

    void copyFrom(const BitSequence& other) {
        bitCount = other.bitCount;
        byteCount = other.byteCount;
        data = new unsigned char[byteCount];
        for (int i = 0; i < byteCount; i++) {
            data[i] = other.data[i];
        }
    }
    
    void clear() {
        delete[] data;
        data = nullptr;
        bitCount = 0;
        byteCount = 0;
    }


    class BitEnumerator : public IEnumerator<Bit> {
    private:
        const BitSequence* seq;
        int idx;
        bool isConst;
        Bit currentBit;

    public:
        BitEnumerator(const BitSequence* s, bool isConst = false) : seq(s), idx(-1), isConst(isConst), currentBit(false) {
            if (s == nullptr) {
                throw InvalidArgumentException("BitEnumerator: sequence cannot be null");
            }
        }

        IEnumerator<Bit>* Clone() const override {
            return new BitEnumerator(*this); 
        }

        bool MoveNext() override {
            if (seq == nullptr) return false;
            idx++;
            if (idx < seq->GetLength()) {
                currentBit = seq->Get(idx); 
                return true;
            }
            return false;
        }

        const Bit& GetCurrent() const override {
            if (seq == nullptr) {
                throw InvalidArgumentException("Enumerator is not attached to a sequence");
            } 
            return currentBit; 
        }

        Bit& GetCurrent() override {
            if (seq == nullptr || idx < 0 || idx >= seq->GetLength()) {
                throw InvalidArgumentException("Enumerator is not attached to a sequence");
            }
            return currentBit; 
        }

        void Reset() override {
            idx = -1; 
        }
    };

protected:
    Sequence<Bit>* CreateEmptySameType() const override {
        return new BitSequence();
    }

    void AppendInternal(const Bit& item) override {
        int newBitCount = bitCount + 1;
        int newByteCount = (newBitCount + 7) / 8;
        
        if (newByteCount > byteCount) {
            unsigned char* newData = new unsigned char[newByteCount]();
            for (int i = 0; i < byteCount; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
            byteCount = newByteCount;
        }
        
        bitCount = newBitCount;
        setBit(bitCount - 1, static_cast<bool>(item));
    }

    void PrependInternal(const Bit& item) override {
        int newBitCount = bitCount + 1;
        int newByteCount = (newBitCount + 7) / 8;
        
        unsigned char* newData = new unsigned char[newByteCount]();
        
        for (int i = 0; i < bitCount; i++) {
            if (getBit(i)) {
                int newIdx = i + 1;
                newData[newIdx / 8] |= (1 << (newIdx % 8));
            }
        }
        
        if (static_cast<bool>(item)) newData[0] |= 1;
        
        delete[] data;
        data = newData;
        bitCount = newBitCount;
        byteCount = newByteCount;
    }

    void InsertAtInternal(const Bit& item, int index) override {
        if (index < 0 || index > bitCount) {
            throw IndexOutOfRangeException("Index out of range");
        }
        if (index == bitCount) { AppendInternal(item); return; }
        if (index == 0) { PrependInternal(item); return; }
        
        int newBitCount = bitCount + 1;
        int newByteCount = (newBitCount + 7)/8;
        unsigned char* newData = new unsigned char[newByteCount]();
        
        for (int i = 0; i < index; i++) {
            if (getBit(i)) newData[i/8] |= (1 << (i%8));
        }
        if (static_cast<bool>(item)) newData[index/8] |= (1 << (index%8));
        for (int i = index; i < bitCount; i++) {
            if (getBit(i)) {
                int newIdx = i + 1;
                newData[newIdx/8] |= (1 << (newIdx%8));
            }
        }
        
        delete[] data;
        data = newData;
        bitCount = newBitCount;
        byteCount = newByteCount;
    }

    void SetInternal(int index, const Bit& item) override {
        setBit(index, static_cast<bool>(item));
    }

public:
    BitSequence() : data(nullptr), bitCount(0), byteCount(0) {}

    BitSequence(Bit* items, int count) {
        if (count < 0) {
            throw InvalidArgumentException("Count cannot be negative");
        }
        
        bitCount = count;
        byteCount = (count + 7) / 8;
        data = new unsigned char[byteCount]();
        
        for (int i = 0; i < count; i++) {
            if (static_cast<bool>(items[i])) {
                setBit(i, true);
            }
        }
    }

    BitSequence(bool* items, int count) {
        if (count < 0) {
            throw InvalidArgumentException("Count cannot be negative");
        }
        
        bitCount = count;
        byteCount = (count + 7) / 8;
        data = new unsigned char[byteCount]();
        
        for (int i = 0; i < count; i++) {
            if (items[i]) {
                setBit(i, true);
            }
        }
    }

    explicit BitSequence(int size) {
        if (size < 0) {
            throw InvalidArgumentException("Size cannot be negative");
        }
        
        bitCount = size;
        byteCount = (size + 7) / 8;
        data = new unsigned char[byteCount]();
    }

    BitSequence(const BitSequence& other) {
        copyFrom(other);
    }
    
    BitSequence& operator=(const BitSequence& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    
    ~BitSequence() override {
        delete[] data;
    }

    Sequence<Bit>* Instance() override { return this; }

    Sequence<Bit>* Clone() const override {
        return new BitSequence(*this);
    }

    Bit GetFirst() const override {
        if (bitCount == 0) {
            throw EmptyContainerException("Cannot get first bit from empty sequence");
        }
        return Bit(getBit(0));
    }
    
    Bit GetLast() const override {
        if (bitCount == 0) {
            throw EmptyContainerException("Cannot get last bit from empty sequence");
        }
        return Bit(getBit(bitCount - 1));
    }
    
    Bit Get(int index) const override {
        return Bit(getBit(index));
    }
    
    int GetLength() const override {
        return bitCount;
    }
    
    Sequence<Bit>* Where(std::function<bool(const Bit&)> predicate) const = delete;

    template<typename Accumulator>
    Accumulator Reduce(const Accumulator& initial, std::function<Accumulator(Accumulator, const Bit&)> func) const = delete;

    BitSequence And(const BitSequence& other) const {
        if (this->GetLength() != other.GetLength()) {
            throw DifferentLengthException("Bit sequences must have same length for AND operation");
        }
        
        BitSequence result(this->GetLength());
        
        int minBytes = (byteCount < other.byteCount) ? byteCount : other.byteCount;
        for (int i = 0; i < minBytes; ++i) {
            result.data[i] = data[i] & other.data[i];
        }
        
        return result;
    }
    
    BitSequence Or(const BitSequence& other) const {
        if (this->GetLength() != other.GetLength()) {
            throw DifferentLengthException("Bit sequences must have same length for OR operation");
        }
        
        BitSequence result(this->GetLength());
        
        int minBytes = (byteCount < other.byteCount) ? byteCount : other.byteCount;
        for (int i = 0; i < minBytes; ++i) {
            result.data[i] = data[i] | other.data[i];
        }
        
        return result;
    }
    
    BitSequence Xor(const BitSequence& other) const {
        if (this->GetLength() != other.GetLength()) {
            throw DifferentLengthException("Bit sequences must have same length for XOR operation");
        }
        
        BitSequence result(this->GetLength());
        
        int minBytes = (byteCount < other.byteCount) ? byteCount : other.byteCount;
        for (int i = 0; i < minBytes; ++i) {
            result.data[i] = data[i] ^ other.data[i];
        }
        
        return result;
    }
    
    BitSequence Not() const {
        BitSequence result(this->GetLength());
        
        for (int i = 0; i < byteCount; ++i) {
            result.data[i] = ~data[i];
        }
        

        if (bitCount % 8 != 0) {
            int lastByteIndex = byteCount - 1;
            int usedBits = bitCount % 8;
            unsigned char mask = (1 << usedBits) - 1;
            result.data[lastByteIndex] &= mask;
        }
        
        return result;
    }

    const Bit& operator[](int index) const override {
        return getBit(index) ? Bit::BIT1 : Bit::BIT0;
    }

    Bit& operator[](int index) override {
        throw UnsupportedOperationException("BitSequence does not support mutable access via operator[]");
    }


    BitSequence operator&(const BitSequence& other) const {
        return And(other);
    }
    
    BitSequence operator|(const BitSequence& other) const {
        return Or(other);
    }
    
    BitSequence operator^(const BitSequence& other) const {
        return Xor(other);
    }
    
    BitSequence operator~() const {
        return Not();
    }

    IEnumerator<Bit>* GetEnumerator() const override {
        return new BitEnumerator(this, true);
    }


    
};

#endif //_BIT_SEQUENCE_HPP_
