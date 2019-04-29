// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_MATH_POW
#define META_MATH_POW

#include <meta/replace.hpp>
#include <meta/math/times.hpp>
#include <meta/math/d.hpp>
#include <meta/types.hpp>

namespace meta {
    namespace math {
        template <typename x, uint32 n> struct Pow {
            template <typename F>
            operator F() {
                return x{} ^ n;
            } 
        };
            
        template <typename x> 
        struct d<Pow<x, 0>, x> {
            using derivative = number::N<1>;
        }; 
            
        template <typename x> 
        struct d<Pow<x, 1>, x> {
            using derivative = x;
        }; 
            
        template <typename x, uint32 n> 
        struct d<Pow<x, n>, x> {
            using derivative = Times<number::N<n>, Pow<x, n-1>>;
        }; 

    }
    
    template <typename x, uint32 n, typename var, typename value>
        struct replace<math::Pow<x, n>, var, value> {
        using result = math::Pow<typename replace<x, var, value>::result, n>;
    };
    
}

#endif 

