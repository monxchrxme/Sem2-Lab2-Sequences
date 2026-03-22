#pragma once

#include "icollection.hpp"
#include "ienumerable.hpp"
#include "../types/exceptions.hpp"
#include "../types/option.hpp"
#include <iostream>

template <class T>
class Sequence : public ICollection<T>, public IEnumerable<T> {
public:
    virtual ~Sequence() = default;

    virtual IEnumerator<T>* get_enumerator() const override = 0;

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

    // Try-semantics
    virtual Option<T> try_get_first() const = 0;
    virtual Option<T> try_get_last() const = 0;
    virtual Option<T> try_get(int index) const = 0;

    // overloading operators << and []
    // operator[] (read-only, guarantees immutability safety)
    const T& operator[](int index) const {
        return this->get(index);
    }

    // operator<<
    friend std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
        os << "[";
        bool first = true;

        for (const auto& item : seq) {
            if (!first) {
                os << ", ";
            }
            os << item;
            first = false;
        }
        os << "]";
        return os;
    }

    //  Cpp-style Range-based for loop (for (auto x : seq))
    class CppIterator {
    private:
        const Sequence<T>* seq;
        int current_index;

    public:
        CppIterator(const Sequence<T>* sequence, int index) : seq(sequence), current_index(index) {}
        // 1. dereference operator (retrieving the value)
        const T& operator*() const {
            return seq->get(current_index);
        }

        // 2. increment operator (step forward)
        CppIterator& operator++() {
            current_index++;
            return *this;
        }

        // 3. comparison operator (have we reached the end?)
        bool operator!=(const CppIterator& other) const {
            return current_index != other.current_index;
        }
    };

    CppIterator begin() const {
        return CppIterator(this, 0); // begin with 0 index
    }

    CppIterator end() const {
        return CppIterator(this, this->get_length()); // end immediately after the last one
    }
};

#include "sequence.tpp"