#pragma once
#include "list_sequence.hpp"

// Nested Class iterator for a list

template <class T>
class ListEnumerator : public IEnumerator<T> {
private:
    const ListSequence<T>* sequence;
    int current_index;

public:
    explicit ListEnumerator(const ListSequence<T>* seq) : sequence(seq), current_index(-1) {}

    virtual bool move_next() override {
        if (current_index + 1 < sequence->get_length()) {
            current_index++;
            return true;
        } else {
            current_index = sequence->get_length();
            return false;
        }
    }

    virtual const T& get_current() const override {
        if (current_index < 0 || current_index >= sequence->get_length()) {
            throw IndexOutOfRange("IEnumerator: Invalid state");
        }
        return sequence->get(current_index);
    }

    virtual void reset() override {
        current_index = -1;
    }
};

// realization of the get_enumerator method
template <class T>
IEnumerator<T>* ListSequence<T>::get_enumerator() const {
    return new ListEnumerator<T>(this);
}

// constructors

template <class T>
ListSequence<T>::ListSequence() {
    this->items = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(int size) {
    if (size < 0) {
        throw std::invalid_argument("ListSequence: size cannot be negative");
    }
    this->items = new LinkedList<T>();
    for (int i = 0; i < size; ++i) {
        this->items->append(T());
    }
}

template <class T>
ListSequence<T>::ListSequence(T *items, int count) {
    this->items = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T> &other) {
    this->items = new LinkedList<T>(*(other.items));
}

template <class T>
ListSequence<T>::ListSequence(ListSequence<T> &&other) noexcept {
    this->items = other.items;
    other.items = nullptr;
}

template <class T>
ListSequence<T>::ListSequence(const ICollection<T> &collection) {
    this->items = new LinkedList<T>();

    for (int i = 0; i < collection.get_length(); ++i) {
        // for the list we use append, because nodes are created step by step
        this->items->append(collection.get(i));
    }
}

template <class T>
ListSequence<T>::~ListSequence() {
    delete this->items;
}

// operators=

template <class T>
ListSequence<T>& ListSequence<T>::operator=(const ListSequence<T> &other) {
    if (this == &other) {
        return *this;
    }
    *(this->items) = *(other.items);
    return *this;
}

template <class T>
ListSequence<T>& ListSequence<T>::operator=(ListSequence<T> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete this->items;
    this->items = other.items;
    other.items = nullptr;
    return *this;
}

// getters

template <class T>
const T& ListSequence<T>::get(int index) const {
    return this->items->get(index);
}

template <class T>
int ListSequence<T>::get_length() const {
    return this->items->get_length();
}

// modifying operations

template <class T>
Sequence<T>* ListSequence<T>::append(const T &item) {
    ListSequence<T>* target = this->get_instance();
    target->items->append(item);

    return target;
}

template <class T>
Sequence<T>* ListSequence<T>::prepend(const T &item) {
    ListSequence<T>* target = this->get_instance();
    target->items->prepend(item);

    return target;
}

template <class T>
Sequence<T>* ListSequence<T>::insert_at(const T &item, int index) {
    if (index < 0 || index > this->get_length()) {
        throw IndexOutOfRange("ListSequence::insert_at: Index out of range");
    }

    ListSequence<T>* target = this->get_instance();
    target->items->insert_at(item, index);

    return target;
}

template <class T>
Sequence<T>* ListSequence<T>::remove_at(int index) {
    if (index < 0 || index >= this->get_length()) {
        throw IndexOutOfRange("ListSequence::remove_at: Index out of range");
    }

    ListSequence<T>* target = this->get_instance();
    target->items->remove_at(index);

    return target;
}