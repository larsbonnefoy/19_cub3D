#include  "parsing.h"

int ft_error(char *s, int ret_val)
{
    write(2, "Error\n", 6);
    write(2, s, ft_strlen(s));
    write(2, "\n", 1);
    exit(ret_val);
    return (ret_val);
}
