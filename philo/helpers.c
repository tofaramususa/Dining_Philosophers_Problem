/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:02:07 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/02 21:16:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (count && SIZE_MAX / count < size)
		return (NULL);
	if (!ptr)
		return (NULL);
	memset(ptr, 0, count * size);
	return (ptr);
}

int	ft_atoi(const char *str)
{
	int			i;
	long		rs;
	int			sg;	

	i = 0;
	rs = 0;
	sg = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sg = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rs = rs * 10 + str[i] - '0';
		if (rs * sg > 2147483648)
			return (-1);
		else if (rs * sg < -2147483648)
			return (0);
		i++;
	}
	return (rs * sg);
}

int	ft_arg_checker(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (check_digit(argv[i]) == -1 || ft_atoi(argv[i]) < 1
			|| ft_atoi(argv[0]) > 200)
		{
			printf("%s", ERR_ARGS);
			return (-1);
		}
		if (i > 0 && i < 4 && (ft_atoi(argv[i]) < 60))
		{
			printf("%s", ERR_SIXTY_ARGS);
			return (-1);
		}
	}
	return (0);
}

int	check_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
	}
	return (0);
}
