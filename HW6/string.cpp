#include <string.h>
#include "string.h"
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

String::String(){
    data = new char[1];
    *data = '\0';
    length = 0;
}

String::String(const String &str){
    data = new char[str.length + 1];
    strcpy(data, str.data);
    length = str.length;
}

String::String(const char *str){

    data = new char[strlen(str) + 1];
    strcpy(data, str);
    length = strlen(str);
}

String::~String(){
    delete[] data;
}

String& String::operator=(const String &rhs){
    if(this->equals(rhs)){
        return *this;
    } 
    delete[] data;
    data = new char[rhs.length +1];
    strcpy(data, rhs.data);
    length = rhs.length;
    return *this;
}

String& String::operator=(const char *str){

    delete[] data;

    data = new char[strlen(str) + 1];
	strcpy(data, str);
	length = strlen(str);
	return *this;
}

bool String::equals(const String &rhs) const{
    if(strcmp(data, rhs.data)){
        return false;
    }
    return true;
}

bool String::equals(const char *rhs) const{
    if(strcmp(data, rhs)){
        return false;
    }
    return true;
}

void String::split(const char *delimiters, String **output, size_t *size) const
{
    if(*data == '\0'){
        *output = NULL;
        return;
    }
    char *temp_data = new char[length + 1];
    strcpy(temp_data, data);
    
    //first calculating size, needed for memory allocation later on
    *size = 0;
    char *token;
    token = strtok(temp_data, delimiters);
   
    while(token != NULL){
        (*size)++;
        token = strtok(NULL, delimiters);
    }

    //Spliting and storing the sub-strings
    if(output){
        char *temp_data2 = new char[length +1];
        strcpy(temp_data2, data);
        String *temp = new String [(*size)];
        token = strtok(temp_data2, delimiters);
        int i=0;
        while(token != NULL){
            temp[i++] = token;
            token = strtok(NULL, delimiters);
        }
        *output = temp;
        delete[] temp_data2;
    } 
    delete[] temp_data;
}


int String::to_integer() const{
    return atoi(data);
}

String String::trim() const{
    int count_space_start = 0;

    int count_space_end = length - 1;
    String B;
	//counting white spaces
    while(data[count_space_start] == ' '){
        count_space_start++;
    }
    //if no white spaces
    if(count_space_start == int(length)){
        return B;
    }
    while(data[count_space_end] == ' '){
        count_space_end--;
    }
	//copying the data and returning
    char *temp = new char[(count_space_end - count_space_start + 2)];
    int k = 0;
    while(count_space_start <= count_space_end){
        temp[k] = data[count_space_start];
        k++;
        count_space_start++;
    }
    temp[k] = '\0';
    B = temp;
    delete[] temp;
    return B;
}
