#include "libft.h"

int ft_strlen_def(char *str, char c)
{
    int i;
    
    i = 1;
    while (str[i] != c && str[i] != '\0')
        i++;
    // if (str[i] == '\0')
    //     return (0);
    return (i);
}
