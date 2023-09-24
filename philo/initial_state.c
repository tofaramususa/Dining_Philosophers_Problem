/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:02:17 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/08 18:06:39 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(char **argv, t_data *info)
{
	int	i;

	i = -1;
	info->nbr_of_philo = ft_atoi(argv[0]);
	info->time_to_die = ft_atoi(argv[1]);
	info->time_to_eat = ft_atoi(argv[2]);
	info->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		info->meal_nbr = ft_atoi(argv[4]);
	else
		info->meal_nbr = -1;
	info->finish = false;
	info->print = false;
	info->philo = ft_calloc(info->nbr_of_philo, (sizeof(t_philo)));
	info->fork = ft_calloc(info->nbr_of_philo, (sizeof(pthread_mutex_t)));
	pthread_mutex_init(&info->lock, NULL);
	while (++i < info->nbr_of_philo)
		pthread_mutex_init(&info->fork[i], NULL);
	init_philo(info);
	info->time_to_start = current_time();
}

void	init_philo(t_data *info)
{
	int	i;

	i = -1;
	while (++i < info->nbr_of_philo)
	{
		info->philo[i].id_number = i + 1;
		info->philo[i].nbr_of_meals = 0;
		info->philo[i].left_fork = i;
		info->philo[i].right_fork = (i + 1) % info->nbr_of_philo;
		info->philo[i].shared_info = info;
		info->philo[i].last_meal = 0;
		info->philo[i].holding_fork = false;
	}
}
