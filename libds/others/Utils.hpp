//
//  Utils.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//
#pragma once

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <string>

namespace libds {
// beginning of namespace libds

int rand();

template <typename T>
void swap(T& x, T& y);

template <typename T>
struct Printer : std::unary_function<T, void> {
    void operator()(T const& e) { std::cout << e << std::endl; }
};

template <typename value_type>
struct Hasher : std::unary_function<value_type, int> {
    int operator()(value_type const& e) const;
};

template <>
struct Hasher<int> : std::unary_function<int, int> {
    int operator()(int const& e) const { return e; }
};
template <>
struct Hasher<char> : std::unary_function<char, int> {
    int operator()(char const& e) const { return (int)e; }
};
template <>
struct Hasher<const char*> : std::unary_function<const char*, int> {
    using value_type      = const char*;
    using value_const_ref = value_type const&;
    int operator()(value_const_ref str) const {
        int h = 0;
        for (auto i = 0; i < std::strlen(str); ++i) {
            h = (h << 5) | (h >> 27);
            h += (int)str[i];
        }
        return h;
    }
};
template <>
struct Hasher<std::string> : std::unary_function<std::string, int> {
    int operator()(std::string const& str) const {
        int h = 0;
        for (auto i = 0; i < str.length(); ++i) {
            h = (h << 5) | (h >> 27);
            h += (int)str.at(i);
        }
        return h;
    }
};

unsigned long primeNLT(unsigned long x);

// end of namespace libds
}

#endif /* Utils_hpp */
