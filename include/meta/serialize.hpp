#ifndef META_SERIALIZE
#define META_SERIALIZE

namespace meta {
    
    namespace serialize {
    
        // Specialize this type if you want to say that
        // we know how to serialize a given type in a given
        // format. 
        template <typename type, typename format, typename string> struct read {
            read() = delete;
            
            type operator()(string) const;
        };
    
        // Specialize this type if you want to say that
        // we know how to serialize a given type in a given
        // format. 
        template <typename type, typename format, typename string> struct write {
            write() = delete;
            
            string operator()(type) const;
        };
    
    }
    
};

#endif 
