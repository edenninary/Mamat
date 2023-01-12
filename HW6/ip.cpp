#include "string.h"
#include "ip.h"
#include "generic-field.h"
#include "stdint.h"

#define FIELDNUMBER 4
#define SHIFTSIZE 8
#define IP_SIZE 32


Ip::Ip(String value) : GenericField(){
    ip_name = value;
    ip_addr = 0;
    mask = 0;
}
Ip::~Ip(){}

//helper function that changes the ip address to an integer
static unsigned int change_to_int(String value, bool *check){
    String *ip;
    size_t size = 0;
    value.split(".", &ip, &size);

    if(size != FIELDNUMBER){
        delete[] ip;
        *check = false;
        return 0;
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
   size_t size;
   value.split("/", &ip_mask_split, &size);
   mask = (ip_mask_split[1].trim()).to_integer();
   if(mask < 0 || mask > IP_SIZE || size != 2){
        delete[] ip_mask_split;
        return false;
   }
   bool check = true;
   ip_addr = change_to_int(ip_mask_split[0].trim(), &check);
   if(!check){
        delete[] ip_mask_split;
        return false;
   }
   delete[] ip_mask_split;
   return true;
}

bool Ip::match(String value) {
   
    String *split_temp;
    String *split_pkts = NULL;
    size_t size_pkts = 0;
    size_t size = 0;
    unsigned int shift_temp = 0;
    unsigned int temp = 0;
    unsigned int shift_this_value = 0;
    
    if(value.equals("")){
        
    	return false;
    }
   
    value.split(",", &split_pkts, &size_pkts);
    for(int i=0; i< (int)size_pkts; i++){
        size = 0;
        split_pkts[i].split("=", &split_temp, &size);
        if(split_temp[0].trim().equals(ip_name)){
            break;
        }
        delete[] split_temp;
    }
    bool check = true;
    temp = change_to_int(split_temp[1].trim(), &check);
    if(!check){
    	 delete[] split_pkts;
    	 delete[] split_temp;
        return false;
    }
    //considering mask
    shift_temp  = temp >> (IP_SIZE - mask);
    shift_this_value = ip_addr >> (IP_SIZE - mask);
    delete[] split_pkts;
    delete[] split_temp;
    return (shift_temp == shift_this_value);
}
