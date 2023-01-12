#ifndef IP_H
#define IP_H
#include "string.h"
#include "generic-field.h"

class Ip : public GenericField {
    private:
        String ip_name;
        unsigned int ip_addr;
        int mask;

    protected:
        bool match(String value);

    public:
        Ip(String value);
        ~Ip();
        bool set_value(String value);
    
};

#endif

