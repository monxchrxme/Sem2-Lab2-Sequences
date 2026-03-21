#pragma once
#include "list_sequence.hpp"

template <class T>
class MutableListSequence : public ListSequence<T> {
protected:
    virtual ListSequence<T>* get_instance() override {
        return this; // mutable struct returns itself
    }

public:
    using ListSequence<T>::ListSequence;

    virtual ListSequence<T>* create_empty() const override {
        return new MutableListSequence<T>();
    }

    virtual ListSequence<T>* clone() const override {
        return new MutableListSequence<T>(*this);
    }
};