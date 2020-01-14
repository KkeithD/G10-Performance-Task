#pragma once

#include <stdint.h>
#include <stdlib.h> 
#include <stdio.h>

#include "../lib/sha256/sha256.hpp"

#include "../secure/pass.hpp"

#ifndef SYSTEM_PASSWORD
    #error "Password hash file has been corrupted and invalidated
            in some way. The file must define \"SYS_PASS_HASH\", and
            it appears this value is missing. The file \"pass.hpp\"
            should look like this.
            
                #define SYSTEM_PASSWORD a1cdf9b86be063bced6916eb4bb31d600f234
                
            Please fix password hash file before attempting compilation."
#endif

#define __wrap(name) #name
#define wrap(name) __wrap(name)

inline uint8_t* getSystemPass() {          
    uint8_t sys_pass[SHA256_BLOCK_SIZE];
    const char* sys_hash = wrap(SYSTEM_PASSWORD);

    char hash_hex[2];
    for (int i=0; i<SHA256_BLOCK_SIZE; i++) {
        memcpy(hash_hex, sys_hash+i*2, 2);
        sys_pass[i] = static_cast<uint8_t>(strtol(hash_hex , NULL, 16));
    }

    return sys_pass;
}

#undef wrap
#undef __wrap