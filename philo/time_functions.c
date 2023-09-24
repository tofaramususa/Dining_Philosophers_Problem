/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:51:27 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/09 14:56:02 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	initial_time;

	gettimeofday(&initial_time, NULL);
	return ((initial_time.tv_sec * 1000) + (initial_time.tv_usec / 1000));
}

long long	time_from_start(t_data *info)
{
	struct timeval	time_from_start;

	gettimeofday(&time_from_start, NULL);
	return (((time_from_start.tv_sec * 1000) + (time_from_start.tv_usec / 1000))
		- info->time_to_start);
}

void	ft_delay(t_philo *philo, int waiting_time)
{
	long long	first_time;
	long long	change;

	first_time = time_from_start(philo->shared_info);
	while (1)
	{
		pthread_mutex_lock(&philo->shared_info->lock);
		change = time_from_start(philo->shared_info) - first_time;
		if (change >= waiting_time)
		{
			pthread_mutex_unlock(&philo->shared_info->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->shared_info->lock);
		usleep (200);
	}
}

void	philo_logs(t_philo *philo, char *message)
{
	bool	done;

	done = false;
	pthread_mutex_lock(&philo->shared_info->lock);
	if (philo->shared_info->finish == true)
	{
		done = true;
		pthread_mutex_unlock(&philo->shared_info->lock);
	}
	else
		pthread_mutex_unlock(&philo->shared_info->lock);
	if (done == false)
	{
		pthread_mutex_lock(&philo->shared_info->lock);
		printf("%lld\t | %d\t : %s\n", time_from_start(philo->shared_info),
			philo->id_number, message);
		pthread_mutex_unlock(&philo->shared_info->lock);
	}
}
