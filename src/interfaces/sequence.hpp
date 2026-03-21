#pragma once

#include "icollection.hpp"
#include "../types/exceptions.hpp"

template <class T>
class Sequence : public ICollection<T> {
public:
    virtual ~Sequence() = default;

    // fabric methods (virtual constructors)
    // create an empty sequence of the same type (array or list)
    virtual Sequence<T>* create_empty() const override = 0;
    // create an exact copy of the current sequence
    virtual Sequence<T>* clone() const override = 0;

    // getters
    virtual const T& get_first() const = 0;
    virtual const T& get_last() const = 0;
    virtual Sequence<T>* get_subsequence(int start_index, int end_index) const = 0;

    // modifying operations
    virtual Sequence<T>* append(const T &item) = 0;
    virtual Sequence<T>* prepend(const T &item) = 0;
    virtual Sequence<T>* insert_at(const T &item, int index) = 0;
    virtual Sequence<T>* remove_at(int index) = 0;
    virtual Sequence<T>* concat(Sequence<T> *list) const = 0;

    // map-reduce operations
    virtual Sequence<T>* map(T (*mapper)(const T&)) const;
    virtual Sequence<T>* where(bool (*predicate)(const T&)) const;
    virtual T reduce(T (*reducer)(const T&, const T&), const T &initial_value) const;
};

#include "sequence.tpp"