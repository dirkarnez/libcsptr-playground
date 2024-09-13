
#include <stdio.h>
#include "libcsptr/unique_ptr.h"
#include "libcsptr/shared_ptr.h"

typedef struct {
    int value;
} MyStruct;

void use_shared_ptr(shared_ptr_t shared_ptr) {
    MyStruct* my_struct = (MyStruct*)shared_ptr_get(shared_ptr);
    printf("Value inside function: %d\n", my_struct->value);
}

int main() {
    {
        // 使用唯一指针管理动态分配的结构体
        unique_ptr_t my_struct_ptr = unique_ptr_create((void*)malloc(sizeof(MyStruct)));
        MyStruct* my_struct = (MyStruct*)unique_ptr_get(my_struct_ptr);
        my_struct->value = 42;
        // 当 unique_ptr 超出作用域时，自动释放内存
    }
    {
        shared_ptr_t shared_ptr = shared_ptr_create((void*)malloc(sizeof(MyStruct)));
        MyStruct* my_struct = (MyStruct*)shared_ptr_get(shared_ptr);
        my_struct->value = 42;
    
        // 将共享指针传递给函数
        use_shared_ptr(shared_ptr);
    
        // 即使在函数调用后，共享指针仍然有效
        printf("Value after function call: %d\n", ((MyStruct*)shared_ptr_get(shared_ptr))->value);
    }
}
