/**
 * 
 *     /$$$$$$            /$$    /$$$$$$        /$$$$$$$  /$$$$$$$$ /$$$$$$$$
 *    /$$__  $$         /$$$$   /$$$_  $$      | $$__  $$| $$_____/|__  $$__/
 *   | $$  \__/        |_  $$  | $$$$\ $$      | $$  \ $$| $$         | $$   
 *   | $$ /$$$$ /$$$$$$  | $$  | $$ $$ $$      | $$$$$$$/| $$$$$      | $$   
 *   | $$|_  $$|______/  | $$  | $$\ $$$$      | $$____/ | $$__/      | $$   
 *   | $$  \ $$          | $$  | $$ \ $$$      | $$      | $$         | $$   
 *   |  $$$$$$/         /$$$$$$|  $$$$$$/      | $$      | $$         | $$   
 *   \______/         |______/ \______/       |__/      |__/         |__/   
 *   
 *   By ~ Keith Davies.
 *   
 *   This is an internal file meant to retrieve the sha256 hashed password
 *   from "secure/pass.hpp" and convert it to a usable c type.
 */

#pragma once

#include <stdlib.h> 
#include <stdint.h>
#include <stdio.h>

#include "sha256.hpp"

#include "secure/pass.hpp"

#ifndef SYSTEM_PASSWORD
    #error "Password hash file has been corrupted and invalidated \
in some way. The file must define "SYS_PASS_HASH", and \
it appears this value is missing. The file "pass.hpp" \
should look like this. \
\
#define SYSTEM_PASSWORD a1cdf9b86be063bced6916eb4bb31d600f234 \

#endif

#define __wrap(name) #name
#define wrap(name) __wrap(name)

inline void __get_sys_pass_hash(uint8_t sys_pass[]) {          
    const char* sys_hash = wrap(SYSTEM_PASSWORD);

    char hash_hex[2];
    for (int i=0; i<SHA256_BLOCK_SIZE; i++) {
        memcpy(hash_hex, sys_hash+i*2, 2);
        sys_pass[i] = static_cast<uint8_t>(strtol(hash_hex , NULL, 16));
    }
}

#undef wrap
#undef __wrap
