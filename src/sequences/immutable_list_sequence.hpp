#pragma once
#include "list_sequence.hpp"
#include "mutable_list_sequence.hpp"

template <class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    virtual ListSequence<T>* get_instance() override {
        return this->clone(); // create complete copy before changing to return it
    }

public:
    using ListSequence<T>::ListSequence;

    // pattern builder
    class Builder : public ISequenceBuilder<T> {
    private:
        MutableListSequence<T>* temp_buffer;
    public:
        Builder() { temp_buffer = new MutableListSequence<T>(); }
        virtual void append(const T& item) override {
            temp_buffer->append(item);
        }

        virtual Sequence<T>* build() override {
            int len = temp_buffer->get_length();
            T* arr = new T[len];
            int i = 0;
            for(const auto& item : *temp_buffer) {
                arr[i++] = item;
            }

            Sequence<T>* result = new ImmutableListSequence<T>(arr, len);

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

    virtual ListSequence<T>* create_empty() const override {
        return new ImmutableListSequence<T>();
    }

    virtual ListSequence<T>* clone() const override {
        return new ImmutableListSequence<T>(*this);
    }
};

template <class T>
Sequence<T>* ImmutableListSequence<T>::slice(int index, int count, const Sequence<T>* elements) const {
    return this->slice_internal(index, count, elements);
}