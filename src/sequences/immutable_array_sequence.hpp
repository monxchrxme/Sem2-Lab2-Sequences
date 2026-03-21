#pragma once
#include "array_sequence.hpp"

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    virtual ArraySequence<T>* get_instance() override {
        return this->clone(); // create complete copy before changing to return it
    }

public:
    using ArraySequence<T>::ArraySequence;

    virtual ArraySequence<T>* create_empty() const override {
        return new ImmutableArraySequence<T>();
    }

    virtual ArraySequence<T>* clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }
};