#pragma once

#include "bpstree.h"


template<class key_t, class unique_t, class comparator_t, class allocator_t>
struct bpstree_set_config_t
{
    template<class in_type> static key_t const &get_key(in_type &value)
    {
        return value;
    }
    typedef key_t key_type;
    typedef key_t const mapped_type;
    typedef key_t const value_type;
    typedef key_t storage_type;
    typedef comparator_t key_compare;
    typedef allocator_t allocator_type;
    typedef unique_t unique_type;
    template<size_t A, size_t B> struct max_t
    {
        enum
        {
            value = A > B ? A : B
        };
    };
    enum
    {
        min_inner_size = (sizeof(key_type) + sizeof(nullptr)) * 8 + sizeof(size_t) * 3 + sizeof(nullptr) * 2,
        min_leaf_size = sizeof(storage_type) * 8 + sizeof(size_t) * 2 + sizeof(nullptr) * 3,
        memory_block_size = max_t<256, max_t<min_inner_size, min_leaf_size>::value>::value,
    };
};
template<class value_t, class comparator_t = std::less<value_t>, class allocator_t = std::allocator<value_t>>
using bpstree_set = b_plus_size_tree<bpstree_set_config_t<value_t, std::true_type, comparator_t, allocator_t>>;
template<class value_t, class comparator_t = std::less<value_t>, class allocator_t = std::allocator<value_t>>
using bpstree_multiset = b_plus_size_tree<bpstree_set_config_t<value_t, std::false_type, comparator_t, allocator_t>>;