/* ************************************************************************
 *       Filename:  test.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年04月04日 10时39分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>

int add(int num1,int num2){
    int total;
    total = num1+num2;
    return total;
}

int main(int argc, char *argv[])
{
    int a,b,c;
    int (*p)();

    a = 2;
    b = 3;
    p = add;
    c = (*p)(a,b);
    printf("c = %d\n",c);

    return 0;
}


