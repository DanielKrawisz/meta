// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_MATH_DISTRIBUTE
#define META_MATH_DISTRIBUTE

#include <meta/replace.hpp>
#include <meta/math/d.hpp>

namespace meta {
    
    namespace math {
        
        template <typename ...> struct Times;
        template <typename ...> struct Plus;
        
        template <typename x> struct distribute {
            using result = x;
        };
        
        template <typename x, typename a, typename ... rest> 
        struct distribute<Times<x, Plus<a, rest...>>> {
            using result = typename distribute<Times<x, Plus<rest...>>>::result::template add<typename distribute<Times<x, a>>::result>;
        };
        
        template <typename x, typename a, typename ... rest> 
        struct distribute<Times<Plus<a, rest...>, x>> {
            using result = typename distribute<Times<Plus<rest...>, >>::result::template add<typename distribute<Times<a, x>>::result>;
        };
        
        template <typename x, typename y, typename ... rest> 
        struct distribute<Times<x, y, rest...>> {
            using result = typename distribute<Times<x, typename distribute<y, rest>::result>>::result;
        };
        
    }
    
}

#endif 
