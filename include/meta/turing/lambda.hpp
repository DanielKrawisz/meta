// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_TURING_LAMBDA
#define META_TURING_LAMBDA

#include <meta/replace.hpp>

// lambda is one of the earliest programming languages. 

namespace meta {
    
    template <typename x, typename y> struct lambda;
    
    // use type template 'replace' to define how replacing a variable in a 
    // lambda expression works. 
    template <typename x, typename y, typename z> struct replace<lambda<x, y>, x, z> {
        using result = lambda<x, y>;
    };
    
    template <typename x, typename y, typename a, typename b> struct replace<lambda<x, y>, a, b> {
        using result = lambda<typename replace<x, a, b>::result, typename replace<y, a, b>::result>;
    };
    
    template <typename f, typename x> struct call;
    
    // call means to apply one lambda expression to another. 
    template <typename x, typename y, typename z> struct call<lambda<x, y>, z> {
        using result = typename replace<y, x, z>::result;
    };
    
};

#endif 
