#include <iostream>
#include "7.cpp"

#define SIZE    12

int main()
{
//    bool array[SIZE];
//    int max_num = 1 << SIZE;
//
//    for(int i = 0; i < max_num; i++)
//    {
//        for(int j = 0; j < SIZE; j++)
//        {
//            array[j] = (i >> j) & 1;
//        }
//        for(int j = 0; j < SIZE; j++)
//        {
//            printf("%d", array[j]);
//            if(j != SIZE - 1) printf(", ");
//            else printf("\n");
//        }
//    }


    Code7 code7;

    std::cout << code7.getTotal() << std::endl;
    return 0;
}
