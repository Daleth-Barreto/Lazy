/*
 * LazyA Type System - Header
 */

#ifndef LAZYA_TYPE_SYSTEM_H
#define LAZYA_TYPE_SYSTEM_H

#include <string>
#include <memory>
#include <vector>

namespace lazya {

class TypeSystem {
public:
    TypeSystem();
    ~TypeSystem();
    
    // Type checking (stub for now)
    bool check_types();
    
private:
    // Symbol table and type information
};

} // namespace lazya

#endif // LAZYA_TYPE_SYSTEM_H
