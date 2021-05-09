#include "philo_one.h"

ms_type get_time(void)
{
	struct timeval  time;
	ms_type ms;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void ft_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

static int	ft_isdigit(int c)
{
	if (c < 58 && c > 47)
		return (1);
	return (0);
}

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '\0')
		return (0);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	minus;
	int	i;
	int	result;

	i = 0;
	minus = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] <= 57 && str[i] >= 48)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (minus * result);
}
