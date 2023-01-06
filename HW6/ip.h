#ifndef IP_H
#define IP_H
#include "string.h"
#include "generic-field.h"

class Ip : public GenericField {
    private:
        unsigned int ip_addr;
        int mask;
        String ip_name;

    protected:
        bool match(String value);

    public:
        Ip(String value);
        ~Ip();
        bool set_value(String value);
    
};

#endif

