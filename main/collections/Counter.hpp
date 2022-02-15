#pragma once

#include "../common.hpp"

template<typename K, typename V>
class Counter : public map<K, V> {
    public:
        void add(K key, V delta) {
            (*this)[key] += delta;
            if (delta < 0 && (*this)[key] == 0) {
                (*this).erase(key);
            }
        }
};