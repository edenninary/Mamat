#ifndef PORT_H
#define PORT_H
#include "string.h"
#include "generic-field.h"

class Port : public GenericField {
    private:
        unsigned short low_value;
        unsigned short high_value;
        String port_name;

    protected:
        bool match(String value);

    public:
        Port(String value);
        ~Port();
        bool set_value(String value);
        
};

#endif

