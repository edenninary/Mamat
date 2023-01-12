#include "string.h"
#include "port.h"
#include "generic-field.h"

Port::Port(String value) : GenericField(){
    this->port_name = value;
    low_value = 0;
    high_value = 0;
}

Port::~Port(){}

bool Port::set_value(String value){

    String *arr_num;
    size_t size;
    value.split("-", &arr_num, &size);

    if(size != 2){
        delete[] arr_num;
        return false;
    }

    high_value = (arr_num[1].trim()).to_integer();
    low_value = (arr_num[0].trim()).to_integer();

    delete[] arr_num;
    return true;
}

bool Port::match(String value){
    
    String *split_temp;
    String *split_pkts = NULL;
    size_t size_pkts = 0;
    size_t size = 0;
    if(value.equals("")){
    	
    	return false;
    }
    value.split(",", &split_pkts, &size_pkts);
    for(int i=0; i<int(size_pkts); i++){
        size = 0;
        split_pkts[i].split("=", &split_temp, &size);
        if(split_temp[0].trim().equals(port_name)){
            break;
        }
        delete[] split_temp;
    }
    int temp_value = (split_temp[1].trim()).to_integer();
    delete[] split_temp;
    delete[] split_pkts;
    return ((temp_value >= this->low_value) && (temp_value <= high_value));
}
