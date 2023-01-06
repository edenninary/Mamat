#include "string.h"
#include "generic-field.h"
#include "port.h"
#include "ip.h"
#include "input.h"

int main(int argc, char **argv){

    if(check_args(argc, argv)){
        return 1;
    }
    String input(argv[1]);
    String *input_arr;
    unsigned long int size = 0;
    input.split(",=", &input_arr, &size);
    String left_string = (input_arr[0]).trim();
    String right_string = input_arr[1];
    
    if(left_string.equals("dst-port") || left_string.equals("src-port")){
        
        Port port(left_string);
        port.set_value(right_string);
        parse_input(port);
    }
    else if(left_string.equals("dst-ip") || left_string.equals("src-ip")){
        
        Ip ip(left_string);
        ip.set_value(right_string);
        parse_input(ip);
    }

    delete[] input_arr;
    return 0;
}

