#pragma once
#include "sequence.hpp"

template <class T>
Sequence<T>* Sequence<T>::map(T (*mapper)(const T&)) const {
    Sequence<T>* result = this->create_empty();

    for (int i = 0; i < this->get_length(); ++i) {
        T mapped_value = mapper(this->get(i));

        Sequence<T>* next_result = result->append(mapped_value);

        // MEMORY PROTECTION: if append returned a new object (as it will be in ImmutableSequence),
        // this means that the old intermediate result object is no longer needed, so we delete it
        if (next_result != result) {
            delete result;
            result = next_result;
        }
    }

    return result;
}

template <class T>
Sequence<T>* Sequence<T>::where(bool (*predicate)(const T&)) const {
    Sequence<T>* result = this->create_empty();

    for (int i = 0; i < this->get_length(); ++i) {
        const T& current_value = this->get(i);

        if (predicate(current_value)) {
            Sequence<T>* next_result = result->append(current_value);
            // MEMORY PROTECTION: the same as in map
            if (next_result != result) {
                delete result;
                result = next_result;
            }
        }
    }

    return result;
}

template <class T>
T Sequence<T>::reduce(T (*reducer)(const T&, const T&), const T &initial_value) const {
    T accumulator = initial_value;

    for (int i = 0; i < this->get_length(); ++i) {
        accumulator = reducer(accumulator, this->get(i));
    }

    return accumulator;
}