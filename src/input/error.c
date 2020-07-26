#include "lemin.h"

void	print_error(void)
{
    write(2, ERR, sizeof(ERR));
    exit(1);
}
