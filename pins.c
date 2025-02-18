#include "pins.h"

#include "registers.h"                
#include <stdlib.h>             // calloc
#include <string.h>
#include <stdio.h>
//#include <dlfcn.h>

typedef struct 
{
    const unsigned short length; 
    const char* pointer;     
} string_t;

string_t __UnionStringCommand(unsigned short pinNumber)
{
    static char str1[] = "BIT_PIN_";
    static char str2[] = "_IO";
    unsigned short number = pinNumber;
    
    unsigned short len1 = strlen(str1);
    unsigned short len2 = strlen(str2);
    unsigned short numberLenght = sizeof(number);
    unsigned short bufferLenght = len1 + numberLenght + len2 + 1;
    char* buffer = (char*)calloc(sizeof(char), bufferLenght); 
    
    strcpy(buffer, str1);
    sprintf(buffer + len1, "%u", number);
    strcpy(buffer + len1 + numberLenght, str2);
    
    string_t answer = {bufferLenght, buffer};
    return answer;
}

void __Clear(string_t object)
{
    free((void *)object.pointer);
}

void compiled_function(const char *function_string, void **function_ptr) {
    // Create a new buffer for the compiled function
    // (In a real-world scenario, use a more secure method for allocating memory)
    char *compiled_function_buf = malloc(strlen(function_string) + 1);

    strcpy(compiled_function_buf, function_string);

    // Compile the function into the buffer
    //int (*compiled_func)(int, int) = dlsym(RTLD_NOW, "add_numbers");


    // Replace the function pointer with the compiled function
    *function_ptr = compiled_function_buf;

    // Clean up and return success
    //free(compiled_function_buf);
}

const char *function_string = "int add_numbers(int a, int b) { return a + b; }";
void PinInitOutput(unsigned short pinNumber)
{  
        // Compile the function from the string
    int (*func_ptr)(int, int) = NULL;
    compiled_function(function_string, (void **)&func_ptr);

    // Call the function
    int result = func_ptr(5, 7);
    Nop();
    
//    static const char  __attribute__ ((address(0x34a))) instr[]
//    = "Nop();\0";

//    string_t command = __UnionStringCommand(pinNumber);
//    unsigned short length = command.length;
//    char * bitString = (char*)calloc(sizeof(char), command.length);
//    strncpy(bitString, command.pointer, command.length);
    
    
    if(BIT_PIN_87_IO == 0)
    {
        Nop();
    }
    else
    {
        Nop();
    }
    

//    __Clear(command);
    Nop();
}
