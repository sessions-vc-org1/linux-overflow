#ifndef paymentHandler_H
#define paymentHandler_H

#include <cstring>
#include <string>
#include <iostream>
#include "paymentProvider.h"
class PaymentHandler
{
    public:
        PaymentHandler(void);
        PaymentHandler(PaymentProvider);
        void addProvider(PaymentProvider providerToAdd)
        {
            this->currentProvider = providerToAdd;
        };
        void addProvider(std::string s)
        {
            
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
        };
        void removeProvider()
        {
            this->currentProvider = PaymentProvider();
        };
        PaymentProvider getProvider()
        {
            return this->currentProvider;
        };

        // Make payload retrieval a method and the sqlite callback a static member
        std::string get_payload(char* input);
        std::string load_file_for_payload(const std::string& payload);
        void get_input(char* text);
        static int callback(void* data, int argc, char** argv, char** azColName);
        

    private:
        PaymentProvider currentProvider;
        char* string;
        

};
#endif