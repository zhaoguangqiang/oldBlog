/* ************************************************************************
 *       Filename:  5.3.c
 *    Description:  
 *        Version:  1.0
 *        Created:  01/12/2015 10:50:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#include <stdio.h>


int main(int argc, char *argv[])
{
    int c;
    int time=0;
    char buf[2];
    setbuf(stdout,buf);

#if 1
    while(((c=getchar()) != EOF)&&time<15){
        putchar(c);
        time++;
    }
#else 
    puts("helloworld");
#endif
    return 0;
}


