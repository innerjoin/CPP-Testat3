#ifndef TESTAT3_INDEXABLESET_H
#define TESTAT3_INDEXABLESET_H

#include <set>
#include <stdexcept>

template <typename T, typename COMPARE=std::less<T>>
class IndexableSet : public std::set<T, COMPARE> {
    using IdxSet = std::set<T, COMPARE>;
    using size_type = typename IdxSet::size_type;

public:

    T const & front() const {
        return at(0);
    }

    T const & back() const {
        return at(this->size() - 1);
    }

    T const & at(size_type index) const {
        if (index >= this->size() || -index > this->size())
            throw std::out_of_range{"index out of range!!"};
        size_t idx = index >= 0 ? index : this->size() + index;
        auto iterator = this->begin();
        std::advance(iterator, idx);
        return *iterator;
    }

    T const & operator[](size_type index) const {
        return at(index);
    }
};

#endif //TESTAT3_INDEXABLESET_H
