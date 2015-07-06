/* ************************************************************************
 *       Filename:  test1.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年04月10日 23时44分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>

//enum week{0x00000001,0x00000002,0x00000003,0x00000004}a;
int main(int argc, char *argv[])
{
    enum week{mon,tues,wes,thr};
    enum week a;
    a = 42;
    printf("%d\n",a);
    return 0;
}


