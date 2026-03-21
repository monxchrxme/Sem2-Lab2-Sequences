#pragma once

#include "../interfaces/sequence.hpp"
#include "../memory/dynamic_array.hpp"
#include <stdexcept>

template <class T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T> *items; // protected so that heirs can copy it

    // method that determines which object to mutate
    virtual ArraySequence<T>* get_instance() = 0;

public:
    // constructors
    ArraySequence();
    explicit ArraySequence(int size);
    ArraySequence(T *items, int count);
    ArraySequence(const ArraySequence<T> &other);
    ArraySequence(ArraySequence<T> &&other) noexcept;
    // cross-constructor from any collection
    explicit ArraySequence(const ICollection<T> &collection);

    virtual ~ArraySequence() override;

    // iterator
    virtual IEnumerator<T>* get_enumerator() const override;

    // operators=
    // copy assignment operator
    ArraySequence<T>& operator=(const ArraySequence<T> &other);
    // move assignment operator
    ArraySequence<T>& operator=(ArraySequence<T> &&other) noexcept;

    // fabric methods
    virtual Sequence<T>* create_empty() const override = 0;
    virtual Sequence<T>* clone() const override = 0;

    // getters
    virtual const T& get_first() const override;
    virtual const T& get_last() const override;
    virtual const T& get(int index) const override;
    virtual Sequence<T>* get_subsequence(int start_index, int end_index) const override;
    virtual int get_length() const override;

    // modifying operations
    virtual Sequence<T>* append(const T &item) override;
    virtual Sequence<T>* prepend(const T &item) override;
    virtual Sequence<T>* insert_at(const T &item, int index) override;
    virtual Sequence<T>* remove_at(int index) override;
    virtual Sequence<T>* concat(Sequence<T> *list) const override;
};

#include "array_sequence.tpp"