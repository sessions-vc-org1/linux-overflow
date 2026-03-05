#ifndef paymentProvider_H
#define paymentProvider_H

#include <string>

class PaymentProvider
{
    public:
        PaymentProvider(void);
        PaymentProvider(std::string s);
        PaymentProvider(std::string s, char* destination);
        static double calculate_required_payment(double principal, double annual_rate_percent, int months);
    private:
        unsigned int id;
        char* string;
        int year;
        int CVE;
};
#endif