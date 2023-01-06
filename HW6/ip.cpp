#include "string.h"
#include "ip.h"
#include "generic-field.h"
#include "stdint.h"

#define FIELDNUMBER 4
#define SHIFTSIZE 8
#define IP_SIZE 32


Ip::Ip(String value) : GenericField(){
    this->ip_name = value;
    ip_addr = 0;
    mask = 0;
}
Ip::~Ip(){}

//function that converts a given ip address to a unique integer
static unsigned int change_to_int(String value){
    String *ip;
    unsigned long int size = 0;
    value.split(".", &ip, &size);

    if(size != FIELDNUMBER){
        delete[] ip;
        return 0;//need to change this to something out of the field
    }
    unsigned int ip_int = 0;
    for(int i=0; i<FIELDNUMBER; i++){
        ip_int = ip_int + (ip[i].to_integer() << ((3-i)*SHIFTSIZE));
        ip_int |= (ip[i].to_integer() << ((3-i)*SHIFTSIZE));       
    }
    delete[] ip;
    return ip_int;
}

bool Ip::set_value(String value){
    String *ip_mask_split; 
    unsigned long int size;
    value.split("/", &ip_mask_split, &size);
    mask = (ip_mask_split[1].trim()).to_integer();
    
    if(mask < 0 || mask > IP_SIZE || size != 2){
        delete[] ip_mask_split;
        return false;
    }

    //set ip address to unique integer
    ip_addr = change_to_int(ip_mask_split[0].trim());
    if(ip_addr == 0){
        delete[] ip_mask_split;
        return false;
    }
    delete[] ip_mask_split;
    return true;
}

bool Ip::match(String value) {
   
    String *split_temp;
    String *split_pkts;
    unsigned long size_pkts = 0;
    unsigned long size = 0;
    unsigned int shift_temp = 0;
    unsigned int temp = 0;
    unsigned int shift_this_value = 0;
    value.split(",", &split_pkts, &size_pkts);
    for(int i=0; i<int(size_pkts); i++){
        size = 0;
        split_pkts[i].split("=", &split_temp, &size);
        if(split_temp[0].trim().equals(this->ip_name)){
            break;
        }
    }
    temp = change_to_int(split_temp[1].trim());
    //-----------------------considering mask--------
    shift_temp  = temp >> (IP_SIZE - mask);
    shift_this_value = ip_addr >> (IP_SIZE - mask);
    return (shift_temp == shift_this_value);
}