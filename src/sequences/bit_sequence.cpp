#include "bit_sequence.hpp"

BitSequence::BitSequence(const std::string& bit_string) : MutableArraySequence<Bit>(bit_string.length()) {
    for (size_t i = 0; i < bit_string.length(); ++i) {
        if (bit_string[i] == '1') {
            this->items->set(i, Bit(true));
        } else if (bit_string[i] == '0') {
            this->items->set(i, Bit(false));
        } else {
            throw std::invalid_argument("BitSequence: String must contain only '0' or '1'");
        }
    }
}

BitSequence* BitSequence::bitwise_not() const {
    BitSequence* result = new BitSequence(this->get_length());
    for (int i = 0; i < this->get_length(); ++i) {
        result->items->set(i, ~this->get(i));
    }

    return result;
}

BitSequence* BitSequence::bitwise_and(const Sequence<Bit>* other) const {
    int len1 = this->get_length();
    int len2 = other->get_length();
    int max_len = (len1 > len2) ? len1 : len2;

    int offset1 = max_len - len1;
    int offset2 = max_len - len2;

    BitSequence* result = new BitSequence(max_len);

    for (int i = 0; i < max_len; ++i) {
        Bit b1 = (i >= offset1) ? this->get(i - offset1) : Bit(false);
        Bit b2 = (i >= offset2) ? other->get(i - offset2) : Bit(false);
        result->items->set(i, b1 & b2);
    }
    return result;
}

BitSequence* BitSequence::bitwise_or(const Sequence<Bit>* other) const {
    int len1 = this->get_length();
    int len2 = other->get_length();
    int max_len = (len1 > len2) ? len1 : len2;

    int offset1 = max_len - len1;
    int offset2 = max_len - len2;

    BitSequence* result = new BitSequence(max_len);

    for (int i = 0; i < max_len; ++i) {
        Bit b1 = (i >= offset1) ? this->get(i - offset1) : Bit(false);
        Bit b2 = (i >= offset2) ? other->get(i - offset2) : Bit(false);
        result->items->set(i, b1 | b2);
    }
    return result;
}

BitSequence* BitSequence::bitwise_xor(const Sequence<Bit>* other) const {
    int len1 = this->get_length();
    int len2 = other->get_length();
    int max_len = (len1 > len2) ? len1 : len2;

    int offset1 = max_len - len1;
    int offset2 = max_len - len2;

    BitSequence* result = new BitSequence(max_len);

    for (int i = 0; i < max_len; ++i) {
        Bit b1 = (i >= offset1) ? this->get(i - offset1) : Bit(false);
        Bit b2 = (i >= offset2) ? other->get(i - offset2) : Bit(false);
        result->items->set(i, b1 ^ b2);
    }
    return result;
}

BitSequence* BitSequence::clone() const {
    return new BitSequence(*this);
}

BitSequence* BitSequence::create_empty() const {
    return new BitSequence();
}