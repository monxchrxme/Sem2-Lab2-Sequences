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

public:
    // pattern builder
    class Builder : public ISequenceBuilder<T> {
    private:
        MutableArraySequence<T>* seq;
    public:
        Builder() {
            seq = new MutableArraySequence<T>();
        }

        virtual void append(const T& item) override {
            seq->append(item);
        }

        virtual Sequence<T>* build() override {
            return seq; // return the finished object, transferring ownership of the memory
        }
    };

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new Builder();
    }

    // slice-split
    virtual Sequence<T>* slice(int index, int count, const Sequence<T>* elements = nullptr) const override;
};

template <class T>
Sequence<T>* MutableArraySequence<T>::slice(int index, int count, const Sequence<T>* elements) const {
    return this->slice_internal(index, count, elements);
}