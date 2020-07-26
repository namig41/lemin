#include "lemin.h"
#include <stdio.h>

void	print_error(int line)
{
    printf("%d\n", line);
    write(2, ERR, sizeof(ERR));
    exit(1);
}
