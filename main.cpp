// main.cpp
#include <iostream>
#include <cstring>
#include "paymentHandler.h"
#include <zlib.h> 

extern std::string get_payload();

// main.cpp
#include <iostream>
#include <cstring>
#include "paymentHandler.h"

int main(int argc, char* argv[]) {
    // 1. CLEAR SOURCE: Use command line arg instead of complex DB call
    // Most SAST tools automatically treat argv as "tainted" (untrusted)
    std::string firstInput;
    if (argc > 1) {
        firstInput = argv[1];
    } else {
        firstInput = "THIS_PAYLOAD_IS_DEFINITELY_TOO_LONG"; 
    }

    std::cout << "[App] Payload content: " << firstInput << std::endl;

    char* inputBuffer = (char*)malloc(size_t (24));
    // 2. PROPAGATION
    PaymentHandler personalHandler = PaymentHandler();
    personalHandler.get_input(inputBuffer);
    char* string = new char[16];
    PaymentProvider data = PaymentProvider(inputBuffer, string);
    PaymentProvider provider = PaymentProvider(firstInput);
    // 3. SINK: This path is now much easier for a scanner to trace
    personalHandler.addProvider(data);
    personalHandler.addProvider(provider);
    std::string results = personalHandler.get_payload(inputBuffer);
    
    std::cout << "[App] Retrieved payload: " << results << std::endl;

    // Load a file based on the payload value and show its contents
    std::string fileContents = personalHandler.load_file_for_payload(results);
    std::cout << "[App] Loaded file contents:\n" << fileContents << std::endl;
    
    return 0;
}