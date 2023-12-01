#include "./get_next_line.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
    // char *str;
    // while (1)
    // {
    //     str = get_next_line(fd);
    //     if (!str)
    //         break;
    //     printf("str = %s\n", str);
    //     free(str);
    // }
    // free(str);

    //////////////////
    // int fd = open("./test.txt", O_RDWR);
    // int fd2 = open("./alternate_line_nl_with_nl", O_RDWR);

    // char *str;
    // while (1)
    // {
    //     str = get_next_line(0);
    //     if (!str)
    //         break;
    //     printf("str = %s\n", str);
    //     free(str);
    // }

    char *str;
    str = get_next_line(0);
    printf("str = %s", str);
    free(str);

}