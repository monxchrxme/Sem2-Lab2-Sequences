#pragma once
#include "sequence.hpp"
#include "../types/exceptions.hpp"

template <class T>
Sequence<T>* Sequence<T>::slice(int index, int count, const Sequence<T>* elements) const {
    int len = this->get_length();
    int start = (index < 0) ? (len + index) : index;
    if (start < 0 || start > len) throw IndexOutOfRange("Slice: Out of bounds");
    if (count < 0) count = 0;
    if (start + count > len) count = len - start;

    ISequenceBuilder<T>* builder = this->create_builder();

    int curr_idx = 0;
    for (const auto& item : *this) {
        if (curr_idx == start && elements) {
            for (const auto& el : *elements) {
                builder->append(el);
            }
        }
        if (curr_idx < start || curr_idx >= start + count) {
            builder->append(item);
        }
        curr_idx++;
    }

    if (start == len && elements) {
        for (const auto& el : *elements) {
            builder->append(el);
        }
    }

    Sequence<T>* result = builder->build();
    delete builder;
    return result;
}

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

// getters

template <class T>
const T& Sequence<T>::get_first() const {
    if (this->get_length() == 0) {
        throw IndexOutOfRange("Sequence is empty");
    }
    return this->get(0);
}

template <class T>
const T& Sequence<T>::get_last() const {
    if (this->get_length() == 0) {
        throw IndexOutOfRange("Sequence is empty");
    }
    return this->get(this->get_length() - 1);
}

// Try-semantics

template <class T>
Option<T> Sequence<T>::try_get(int index) const {
    if (index < 0 || index >= this->get_length()) {
        return Option<T>(); // None when out of bounds
    }
    return Option<T>(this->get(index));
}

template <class T>
Option<T> Sequence<T>::try_get_first() const {
    return this->try_get(0);
}

template <class T>
Option<T> Sequence<T>::try_get_last() const {
    return this->try_get(this->get_length() - 1);
}