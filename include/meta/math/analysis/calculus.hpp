// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_MATH_ANALYSIS_CALCULUS
#define META_MATH_ANALYSIS_CALCULUS

#include <stdint.h>

#include <meta/math/d.hpp>
#include <meta/math/plus.hpp>

namespace meta {
    namespace math {
        template <typename x, typename y>
        struct function {
            template <typename X>
            X operator()(X arg) {
                return y{}(arg);
            }
        };
    
        template <typename x>
        struct function<x, x> {
            template <typename X>
            X operator()(X arg) {
                return arg;
            }
        };
        
        template <typename A, typename ...> struct plus;
        
        template <typename x, typename A, typename B> 
        struct function<x, plus<A, B>> {
            template <typename X>
            X operator()(X arg) {
                return function<x, A>{}(arg) + function<x, B>{}(arg);
            }
        };
        
        template <typename A> struct minus;
        
        template <typename x, typename A>
        struct function<x, minus<A>> {
            template <typename X>
            X operator()(X arg) {
                return -function<x, A>{}(arg);
            }
        };
        
        template <typename A, typename B, typename x> 
        struct d<plus<A, B>, x> {
            using derivative = plus<typename d<A, x>::derivative, typename d<B, x>::derivative>;
        }; 
        
        template <typename A, typename ...> struct times;
        
        template <typename x, typename A, typename B> 
        struct function<x, times<A, B>> {
            template <typename X>
            X operator()(X arg) {
                return function<x, A>{}(arg) + function<x, B>{}(arg);
            }
        };
        
        // product rule
        template <typename A, typename B, typename x> 
        struct d<times<A, B>, x> {
            using derivative = plus<
                times<typename d<A, x>::derivative, B>, 
                times<A, typename d<B, x>::derivative>>;
        };
        
        template <typename f, typename x> struct call;
        
        // chain rule
        template <typename x, typename f, typename g>
        struct function<x, call<f, g>> {
            template <typename X>
            X operator()(X arg) {
                return f{}(g{}(arg));
            }
        };
        
        template <uint32_t p> struct pow;
        
        template <typename x>
        struct d<call<pow<0>, x>, x> {
            using derivative = number::zero;
        }; 
        
        template <typename x>
        struct d<call<pow<1>, x>, x> {
            using derivative = number::one;
        }; 
        
        template <uint32_t p, typename x>
        struct d<call<pow<p>, x>, x> {
            using derivative = times<number::N<p>, call<pow<p - 1>, x>>;
        }; 
        
        struct exp;
        
        template <typename x>
        struct d<call<exp, x>, x> {
            using derivative = call<exp, x>;
        }; 
        
        struct cos;
        struct sin;
        
        template <typename x>
        struct d<call<cos, x>, x> {
            using derivative = minus<call<sin, x>>;
        }; 
        
        template <typename x>
        struct d<call<sin, x>, x> {
            using derivative = call<cos, x>;
        }; 
    } 
}

#endif 

