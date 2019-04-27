// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_MATH_ANALYSIS_D
#define META_MATH_ANALYSIS_D

#include <stdint.h>

namespace meta {
    namespace math {
        namespace number {
            template <uint32_t c> struct N {
                operator uint32_t() const {
                    return c;
                }
                
                uint32_t operator()(uint32_t) const {
                    return c;
                }
            };
            
            using zero = N<0>;
            using one = N<1>;
        }
            
        template <typename y, typename x> struct d;
            
        template <typename x> struct d<x, x> {
            using derivative = number::one;
        };
        
        template <typename y, typename x> struct d {
            using derivative = number::zero;
        };
    }
}

#endif 

