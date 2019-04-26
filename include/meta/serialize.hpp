#ifndef META_SERIALIZE
#define META_SERIALIZE

namespace meta {
    
    namespace serialize {
    
        // Specialize this type if you want to say that
        // we know how to serialize a given type in a given
        // format. 
        template <typename type, typename string, typename format> struct read {
            read() = delete;
            
            type operator()(string) const;
        };
    
        // Specialize this type if you want to say that
        // we know how to serialize a given type in a given
        // format. 
        template <typename type, typename string, typename format> struct write {
            write() = delete;
            
            string operator()(type) const;
        };
    
    }
    
};

#endif 
