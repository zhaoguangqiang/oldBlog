/* ************************************************************************
 *       Filename:  integer_overflow.c
 *    Description:  
 *        Version:  1.0
 *        Created:  01/09/2015 11:31:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
    int a0,b0,c0;
    int a1,b1,c1;
    a0=a1=0xffffffff;
    b0=b1=0x000000f1;
    if((c0=a0+b0)<0){
        printf("%d--%x\n",c0);
    }
    if((c1=(unsigned)a1+(unsigned)b1)<0){
        printf("%d--%x\n",c1);
    }
    printf("%d--%x\n",c0);
    printf("%d--%x\n",c1);
    return 0;
}


