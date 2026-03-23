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

public:
    // pattern builder
    class Builder : public ISequenceBuilder<T> {
    private:
        MutableListSequence<T>* seq;
    public:
        Builder() {
            seq = new MutableListSequence<T>();
        }

        virtual void append(const T& item) override {
            seq->append(item);
        }

        virtual Sequence<T>* build() override {
            return seq;
        }
    };

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new Builder();
    }

    // split-slice
    virtual Sequence<T>* slice(int index, int count, const Sequence<T>* elements = nullptr) const override;
};

template <class T>
Sequence<T>* MutableListSequence<T>::slice(int index, int count, const Sequence<T>* elements) const {
    return this->slice_internal(index, count, elements);
}