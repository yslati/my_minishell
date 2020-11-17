#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char	*ft_strcpy_pro(char *dst, const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int main()
{
	char *s;

	s = strdup("1");
	s = ft_strcpy_pro(s, "$yassin", '$');
	if ((s = ft_strcpy_pro(s, "$yassin", '$')) && (!strcmp("", s)))
		puts("ok");
	printf("|%s|\n", s);
	return 0;
}

/* ============ */
