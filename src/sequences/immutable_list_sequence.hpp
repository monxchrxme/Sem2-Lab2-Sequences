#pragma once
#include "list_sequence.hpp"

template <class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    virtual ListSequence<T>* get_instance() override {
        return this->clone(); // create complete copy before changing to return it
    }

public:
    using ListSequence<T>::ListSequence;

    virtual ListSequence<T>* create_empty() const override {
        return new ImmutableListSequence<T>();
    }

    virtual ListSequence<T>* clone() const override {
        return new ImmutableListSequence<T>(*this);
    }
};