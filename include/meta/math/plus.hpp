// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_MATH_PLUS
#define META_MATH_PLUS

#include <meta/replace.hpp>
#include <meta/math/d.hpp>

namespace meta {
    namespace math {
        template<typename ...> struct Plus;
        
        template<> struct Plus<> {
            template <typename F> // F is some algebraic structure. 
            operator F() {
                return 0;
            }
            
            template <typename X>
            using add = Plus<X>;
        };
        
        template<typename A> struct Plus<A> {
            template <typename F>  
            operator F() {
                return A{};
            }
            
            template <typename X>
            using add = Plus<X>;
        };
        
        // Specialize this if you want to use something other than +
        template<typename A, typename... rest> struct Plus<A, rest...> {
            template <typename F>  
            operator F() {
                return A{} + static_cast<F>(Plus<rest...>{});
            }
            
            template <typename X>
            using add = Plus<X, A, rest...>;
        };
            
        template <typename x> 
        struct d<Plus<>, x> {
            using derivative = number::N<0>;
        }; 
        
        template <typename x, typename A> 
        struct d<Plus<A>, x> {
            using derivative = typename d<A, x>::derivative;
        }; 
        
        template <typename x, typename A, typename B> 
        struct d<Plus<A, B>, x> {
            using derivative = Plus<
                typename d<A, x>::derivative, 
                typename d<B, x>::derivative>;
        }; 
        
        template <typename x, typename A, typename ... rest> 
        struct d<Plus<A, rest...>, x> {
            using derivative = typename d<rest..., x>::derivative::template add<typename d<A, x>::derivative>;
        }; 
    }
    
    template <typename var, 
        typename value> struct replace<math::Plus<>, var, value> {
        using result = math::Plus<>;
    };
    
    template <typename A,
        typename var, 
        typename value> struct replace<math::Plus<A>, var, value> {
        using result = typename replace<A, var, value>::result;
    };
    
    template <typename A, typename B, 
        typename var, 
        typename value> struct replace<math::Plus<A, B>, var, value> {
        using result = math::Plus<
            typename replace<A, var, value>::result,
            typename replace<B, var, value>::result>;
    };
    
    template <typename A,
        typename var, 
        typename value,
        typename ...rest> struct replace<math::Plus<A, rest...>, var, value> {
        using result = typename replace<math::Plus<rest...>, var, value>::result::template add<typename replace<A, var, value>::result>;
    };
}

#endif 
