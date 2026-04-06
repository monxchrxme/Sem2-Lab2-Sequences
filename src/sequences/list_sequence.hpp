#pragma once

#include "../interfaces/sequence.hpp"
#include "../memory/linked_list.hpp"
#include <stdexcept>

template <class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> *items; // protected so that heirs can copy it

    // method that determines which object to mutate
    virtual ListSequence<T>* get_instance() = 0;

public:
    // constructors
    ListSequence();
    explicit ListSequence(int size);
    ListSequence(T *items, int count);
    ListSequence(const ListSequence<T> &other);
    ListSequence(ListSequence<T> &&other) noexcept;
    // cross-constructor from any collection
    explicit ListSequence(const ICollection<T> &collection);

    ~ListSequence() override;

    // iterator
    IEnumerator<T>* get_enumerator() const override;

    // operators=
    // copy assignment operator
    ListSequence<T>& operator=(const ListSequence<T> &other);
    // move assignment operator
    ListSequence<T>& operator=(ListSequence<T> &&other) noexcept;

    // fabric methods
    Sequence<T>* create_empty() const override = 0;
    Sequence<T>* clone() const override = 0;

    // getters
    const T& get(int index) const override;
    [[nodiscard]] int get_length() const override;

    // modifying operations
    Sequence<T>* append(const T &item) override;
    Sequence<T>* prepend(const T &item) override;
    Sequence<T>* insert_at(const T &item, int index) override;
    Sequence<T>* remove_at(int index) override;
};

#include "list_sequence.tpp"