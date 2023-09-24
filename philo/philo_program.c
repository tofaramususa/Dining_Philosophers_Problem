/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 01:48:02 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/09 18:03:24 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	program_start(t_data *info)
{
	int	i;

	if (info->nbr_of_philo == 1)
		pthread_create(&info->philo[0].phlthread, NULL,
			&single_philo, (void *)&info->philo[0]);
	else
	{
		i = -1;
		while (++i < info->nbr_of_philo)
			pthread_create(&info->philo[i].phlthread, NULL,
				&philo_start, (void *)&info->philo[i]);
		while (info->finish == false)
			program_status(info);
	}
}

void	*philo_start(void *param)
{
	t_philo		*temp_philo;
	t_data		*temp_info;

	temp_philo = (t_philo *) param;
	temp_info = temp_philo->shared_info;
	while (1)
	{
		pthread_mutex_lock(&temp_philo->shared_info->lock);
		if ((temp_info->meal_nbr > 0 && temp_philo->nbr_of_meals
				== temp_info->meal_nbr)
			|| temp_philo->shared_info->finish == true)
		{
			pthread_mutex_unlock(&temp_philo->shared_info->lock);
			break ;
		}
		pthread_mutex_unlock(&temp_philo->shared_info->lock);
		eating(temp_philo);
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
		if (!(each_philo_eat(info) == false))
			break ;
		usleep(1000);
		if (i == info->nbr_of_philo - 1)
			i = -1;
		i++;
	}
}

bool	each_philo_eat(t_data *info)
{
	int	total_meals;

	total_meals = 0;
	if (info->meal_nbr > 0)
	{
		while (total_meals < info->nbr_of_philo)
		{
			pthread_mutex_lock(&info->lock);
			if (info->philo[total_meals].nbr_of_meals < info->meal_nbr)
			{
				pthread_mutex_unlock(&info->lock);
				return (false);
			}
			pthread_mutex_unlock(&info->lock);
			total_meals++;
		}
		pthread_mutex_lock(&info->lock);
		info->finish = true;
		pthread_mutex_unlock(&info->lock);
	}
	return (total_meals == info->nbr_of_philo);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_info->lock);
	if ((time_from_start(philo->shared_info) - philo->last_meal)
		>= philo->shared_info->time_to_die)
	{
		pthread_mutex_unlock(&philo->shared_info->lock);
		philo_logs(philo, DIED);
		pthread_mutex_lock(&philo->shared_info->lock);
		philo->shared_info->finish = true;
		pthread_mutex_unlock(&philo->shared_info->lock);
	}
	else
		pthread_mutex_unlock(&philo->shared_info->lock);
}
