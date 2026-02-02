// paymentProvider.cpp
#include <cstring>
#include <string>
#include <iostream>
#include "paymentProvider.h"

PaymentProvider::PaymentProvider(void)
{
    id = 0;
    string = nullptr;
    year = 0;
    CVE = 0;
}

PaymentProvider::PaymentProvider(std::string s)
{
    id = 0;
    if (!s.empty()) {
        // VULNERABILITY 1: Heap Buffer Overflow
        // We enforce a fixed heap allocation of 16 bytes, assuming inputs will be small.
        // However, we do not validate the incoming string size.
        
        string = new char[16];
        // Debug output to show the address we are about to corrupt
        std::cout << "[PaymentProvider] Allocated 16 bytes on heap at: " << static_cast<void*>(string) << std::endl;

        // FLAW: strcpy copies the entire source string ('s') into 'string' until it hits a null terminator.
        // Since 's' comes from the database and is > 16 bytes, this writes past the allocated chunk.
        std::strcpy(string, s.c_str());
    } else {
        string = nullptr;
    }
    year = 0;
    CVE = 0;
    
    // VULNERABILITY 2: Memory Leak
    // We have allocated memory with 'new', but this class lacks a destructor to call 'delete[]'.
    // Every time this object is created, 16 bytes (plus metadata) are permanently lost.
}

PaymentProvider::PaymentProvider(std::string s, char* dest)
{
    id = 0;
    if (!s.empty()) {
        // VULNERABILITY 1: Heap Buffer Overflow
        // We enforce a fixed heap allocation of 16 bytes, assuming inputs will be small.
        // However, we do not validate the incoming string size.
        
        // Debug output to show the address we are about to corrupt
        std::cout << "[PaymentProvider] Allocated 16 bytes on at: " << static_cast<void*>(dest) << std::endl;

        // FLAW: strcpy copies the entire source string ('s') into 'string' until it hits a null terminator.
        // Since 's' comes from the database and is > 16 bytes, this writes past the allocated chunk.
        std::strcpy(dest, s.c_str());
    } else {
        dest = nullptr;
    }
    year = 0;
    CVE = 0;
    
    // VULNERABILITY 2: Memory Leak
    // We have allocated memory with 'new', but this class lacks a destructor to call 'delete[]'.
    // Every time this object is created, 16 bytes (plus metadata) are permanently lost.
}