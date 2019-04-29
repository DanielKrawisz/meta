// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_MATH_TIMES
#define META_MATH_TIMES

#include <meta/replace.hpp>
#include <meta/math/d.hpp>
#include <meta/math/algebra/distribute.hpp>

namespace meta {
    namespace math {
        template<typename ...> struct Times;
        
        template<> struct Times<> {
            template <typename F> // F is some algebraic structure. 
            operator F() {
                return 0;
            }
            
            template <typename X>
            using multiply = Times<X>;
        };
        
        template<typename A> struct Times<A> {
            template <typename F>  
            operator F() {
                return A{};
            }
            
            template <typename X>
            using multiply = Times<X>;
        };
        
        // Specialize this if you want to use something other than *
        template<typename A, typename... rest> struct Times<A, rest...> {
            template <typename F>  
            operator F() {
                return A{} * static_cast<F>(Times<rest...>{});
            }
            
            template <typename X>
            using multiply = Times<X, A, rest...>;
        };
            
        template <typename x> 
        struct d<Times<>, x> {
            using derivative = number::N<1>;
        }; 
        
        template <typename x, typename A> 
        struct d<Times<A>, x> {
            using derivative = typename d<A, x>::derivative;
        }; 
        
        template <typename x, typename A, typename B> 
        struct d<Times<A, B>, x> {
            using derivative = Plus<
                Times<typename d<A, x>::derivative, B>, 
                Times<A, typename d<B, x>::derivative>>;
        }; 
        
        template <typename x, typename A, typename ... rest> 
        struct d<Times<A, rest...>, x> {
            using derivative = typename distribute<typename d<rest..., x>::derivative::template multiply<typename d<A, x>::derivative>>::result;
        }; 
    }
    
    template <typename var, 
        typename value> struct replace<math::Times<>, var, value> {
        using result = math::Times<>;
    };
    
    template <typename A,
        typename var, 
        typename value> struct replace<math::Times<A>, var, value> {
        using result = typename replace<A, var, value>::result;
    };
    
    template <typename A, typename B, 
        typename var, 
        typename value> struct replace<math::Times<A, B>, var, value> {
        using result = math::Times<
            typename replace<A, var, value>::result,
            typename replace<B, var, value>::result>;
    };
    
    template <typename A,
        typename var, 
        typename value,
        typename ...rest> struct replace<math::Times<A, rest...>, var, value> {
        using result = typename replace<math::Times<rest...>, var, value>::result::template multiply<typename replace<A, var, value>::result>;
    };
}

#endif 
