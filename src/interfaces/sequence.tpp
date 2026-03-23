#pragma once
#include "sequence.hpp"
#include "../types/exceptions.hpp"

template <class T>
Sequence<T>* Sequence<T>::map(T (*mapper)(const T&)) const {
    ISequenceBuilder<T>* builder = this->create_builder();

    for (const auto& item : *this) {
        builder->append(mapper(item));
    }

    Sequence<T>* result = builder->build();
    delete builder;
    return result;
}

template <class T>
Sequence<T>* Sequence<T>::where(bool (*predicate)(const T&)) const {
    ISequenceBuilder<T>* builder = this->create_builder();

    for (const auto& item : *this) {
        if (predicate(item)) {
            builder->append(item);
        }
    }

    Sequence<T>* result = builder->build();
    delete builder;
    return result;
}

template <class T>
T Sequence<T>::reduce(T (*reducer)(const T&, const T&), const T &initial_value) const {
    T result = initial_value;

    for (const auto& item : *this) {
        result = reducer(item, result);
    }

    return result;
}

template <class T>
Sequence<T>* Sequence<T>::get_subsequence(int start_index, int end_index) const {
    int len = this->get_length();

    if (start_index < 0 || start_index >= len || end_index < 0 || end_index >= len || start_index > end_index) {
        throw IndexOutOfRange("GetSubsequence: Invalid indices");
    }

    ISequenceBuilder<T>* builder = this->create_builder();
    int current_index = 0;

    for (const auto& item : *this) {
        if (current_index >= start_index && current_index <= end_index) {
            builder->append(item);
        }
        if (current_index > end_index) {
            break;
        }
        current_index++;
    }

    Sequence<T>* result = builder->build();
    delete builder;
    return result;
}

template <class T>
Sequence<T>* Sequence<T>::concat(Sequence<T> *list) const {
    if (!list) {
        return this->clone();
    }

    ISequenceBuilder<T>* builder = this->create_builder();

    for (const auto& item : *this) {
        builder->append(item);
    }

    for (const auto& item : *list) {
        builder->append(item);
    }

    Sequence<T>* result = builder->build();
    delete builder;
    return result;
}