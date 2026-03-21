#pragma once

#include "mutable_array_sequence.hpp"
#include "../types/bit.hpp"
#include <string>
#include <stdexcept>

class BitSequence : public MutableArraySequence<Bit> {
public:
    // inheriting Base Constructors
    using MutableArraySequence<Bit>::MutableArraySequence;

    // constructor from string (for example, "1010")
    explicit BitSequence(const std::string& bit_string);

    // specific bitwise operations
    BitSequence* bitwise_and(const Sequence<Bit>* other) const;
    BitSequence* bitwise_or(const Sequence<Bit>* other) const;
    BitSequence* bitwise_xor(const Sequence<Bit>* other) const;
    BitSequence* bitwise_not() const;

    // factory methods for correct polymorphism
    virtual BitSequence* clone() const override;
    virtual BitSequence* create_empty() const override;
};