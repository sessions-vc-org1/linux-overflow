#ifndef paymentProvider_H
#define paymentProvider_H

class PaymentProvider
{
    public:
        PaymentProvider(void);
        PaymentProvider(std::string s);
        PaymentProvider(std::string s, char* destination);
    private:
        unsigned int id;
        char* string;
        int year;
        int CVE;
};
#endif