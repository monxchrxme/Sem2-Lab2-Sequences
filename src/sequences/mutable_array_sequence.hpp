#pragma once
#include "array_sequence.hpp"

template <class T>
class MutableArraySequence : public ArraySequence<T> {
protected:
    virtual ArraySequence<T>* get_instance() override {
        return this; // mutable struct returns itself
    }

public:
    // inherit all constructors of the base class
    using ArraySequence<T>::ArraySequence;

    virtual ArraySequence<T>* create_empty() const override {
        return new MutableArraySequence<T>();
    }

    virtual ArraySequence<T>* clone() const override {
        return new MutableArraySequence<T>(*this);
    }
};