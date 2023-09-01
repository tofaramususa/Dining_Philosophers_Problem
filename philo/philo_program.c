/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:48:02 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/02 21:49:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	program_start(t_data *info)
{
	int	i;

	i = -1;
	if (info->nbr_of_philo == 1)
		pthread_create(&info->philo[0].phlthread, NULL,
			&single_philo, (void *)&info->philo[0]);
	else
	{
		while (++i < info->nbr_of_philo)
			pthread_create(&info->philo[i].phlthread, NULL,
				&philo_start, (void *)&info->philo[i]);
		while (!info->finish)
			program_status(info);
	}
}

void	*philo_start(void *param)
{
	t_philo		*temp_philo;
	t_data		*temp_info;

	temp_philo = (t_philo *) param;
	temp_info = temp_philo->shared_info;
	while (!temp_info->finish)
	{
		pthread_mutex_lock(&temp_philo->shared_info->lock);
		if (temp_info->meal_nbr > 0
			&& temp_philo->nbr_of_meals == temp_info->meal_nbr)
		{
			pthread_mutex_unlock(&temp_philo->shared_info->lock);
			break ;
		}
		pthread_mutex_unlock(&temp_philo->shared_info->lock);
		eating(temp_philo);
		sleeping(temp_philo);
		thinking(temp_philo);
	}
	return (NULL);
}

void	program_status(t_data *info)
{
	int	i;

	i = 0;
	while (info->finish == false)
	{
		check_death(&info->philo[i]);
		each_philo_eat(info);
		usleep(1000);
		if (i == info->nbr_of_philo - 1)
			i = -1;
		i++;
	}	
}

void	each_philo_eat(t_data *info)
{
	int	total_meals;

	total_meals = 0;
	if (info->meal_nbr > 0)
	{
		while (total_meals < info->meal_nbr)
		{
			pthread_mutex_lock(&info->lock);
			if (info->philo[total_meals].nbr_of_meals < info->meal_nbr)
			{
				pthread_mutex_unlock(&info->lock);
				break ;
			}
			pthread_mutex_unlock(&info->lock);
		}
		if (total_meals == info->nbr_of_philo)
		{
			pthread_mutex_lock(&info->lock);
			info->finish = true;
			pthread_mutex_unlock(&info->lock);
		}
	}
}

void	check_death(t_philo *philo)
{
	long long	elapsed_time;

	if (philo->shared_info->finish == false)
	{	
		pthread_mutex_lock(&philo->shared_info->lock);
		elapsed_time = time_from_start(philo->shared_info) - philo->last_meal;
		pthread_mutex_unlock(&philo->shared_info->lock);
		if (elapsed_time >= philo->shared_info->time_to_die)
		{
			philo_logs(philo, DIED);
			pthread_mutex_lock(&philo->shared_info->lock);
			philo->shared_info->finish = true;
			pthread_mutex_unlock(&philo->shared_info->lock);
		}
	}
}
