#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int flag;

	flag = 0;
	if (argc > 1)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'n')
		{
			flag = 1;
			if (argc > 2)
				printf("%s", argv[2]);
		}
		else
			printf("%s", argv[1]);
	}

	if (flag == 0)
		printf("\n");
}