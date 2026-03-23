#pragma once
#include "array_sequence.hpp"
#include "mutable_array_sequence.hpp"

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    virtual ArraySequence<T>* get_instance() override {
        return this->clone(); // create complete copy before changing to return it
    }

public:
    using ArraySequence<T>::ArraySequence;

    // pattern builder
    class Builder : public ISequenceBuilder<T> {
    private:
        MutableArraySequence<T>* temp_buffer;
    public:
        Builder() { temp_buffer = new MutableArraySequence<T>(); }
        virtual void append(const T& item) override { temp_buffer->append(item); }

        virtual Sequence<T>* build() override {
            int len = temp_buffer->get_length();
            T* arr = new T[len];
            for(int i = 0; i < len; ++i) arr[i] = temp_buffer->get(i);

            Sequence<T>* result = new ImmutableArraySequence<T>(arr, len);

            delete[] arr;
            delete temp_buffer;
            return result;
        }
    };

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new Builder();
    }

    // split-slice
    virtual Sequence<T>* slice(int index, int count, const Sequence<T>* elements = nullptr) const override;

    virtual ArraySequence<T>* create_empty() const override {
        return new ImmutableArraySequence<T>();
    }

    virtual ArraySequence<T>* clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }
};

template <class T>
Sequence<T>* ImmutableArraySequence<T>::slice(int index, int count, const Sequence<T>* elements) const {
    return this->slice_internal(index, count, elements);
}