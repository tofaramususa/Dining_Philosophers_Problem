/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:46:55 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/08 17:39:20 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **argv)
{
	t_data	*info;

	if (ac == 1 || ac > 6 || ac < 5)
	{
		printf("%s\n", ERR_NUM_ARGS);
		printf("%s", ARGS);
		return (-1);
	}
	argv++;
	if (ft_arg_checker(argv) == -1)
		return (-1);
	info = (t_data *) ft_calloc(1, sizeof(t_data));
	init(argv, info);
	program_start(info);
	ft_free(info);
	return (0);
}

void	ft_free(t_data *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philo)
		pthread_join(info->philo[i].phlthread, NULL);
	i = -1;
	while (++i < info->nbr_of_philo)
		pthread_mutex_destroy(&info->fork[i]);
	pthread_mutex_destroy(&info->lock);
	free(info->philo);
	free(info->fork);
	free(info);
}
