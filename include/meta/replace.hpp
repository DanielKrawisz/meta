// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef META_REPLACE
#define META_REPLACE

namespace meta {
    
    // Specialize this type in order to specify how a given type
    // can be replaced into the name of another. 
    //
    // replace must be defined for every word in your language
    // in order to operate on sentences. 
    template <typename x, typename y, typename z> struct replace {
        using result = x;
    };
    
    template <typename x, typename z> struct replace<x, x, z> {
        using result = z;
    };
    
};

#endif 

