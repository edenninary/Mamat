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
    unsigned long int size;
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
    String *split_pkts;
    unsigned long size_pkts = 0;
    unsigned long size = 0;
    value.split(",", &split_pkts, &size_pkts);
    for(int i=0; i<int(size_pkts); i++){
        size = 0;
        split_pkts[i].split("=", &split_temp, &size);
        if(split_temp[0].trim().equals(this->port_name)){
            break;
        }
    }
    int temp_value = (split_temp[1].trim()).to_integer();
    return ((temp_value >= low_value) && (temp_value <= high_value));
}


