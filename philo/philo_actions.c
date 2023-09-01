/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:20:45 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/02 21:42:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_info->lock);
	if (!philo->shared_info->finish)
	{
		pthread_mutex_unlock(&philo->shared_info->lock);
		take_forks(philo);
		philo_logs(philo, EATING);
		pthread_mutex_lock(&philo->shared_info->lock);
		philo->last_meal = time_from_start(philo->shared_info);
		philo->nbr_of_meals++;
		pthread_mutex_unlock(&philo->shared_info->lock);
		ft_delay(philo, philo->shared_info->time_to_eat);
		if (philo->holding_fork == true)
		{
			pthread_mutex_unlock(&philo->shared_info->fork[philo->left_fork]);
			pthread_mutex_unlock(&philo->shared_info->fork[philo->right_fork]);
			philo->holding_fork = false;
		}
	}
	else
		pthread_mutex_unlock(&philo->shared_info->lock);
}

void	sleeping(t_philo *philo)
{
	if (!philo->shared_info->finish)
	{
		philo_logs(philo, SLEEPING);
		ft_delay(philo, philo->shared_info->time_to_eat);
	}
}

void	thinking(t_philo *philo)
{
	if (!philo->shared_info->finish)
	{
		philo_logs(philo, THINKING);
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->id_number % 2)
	{
		usleep(1500);
		pthread_mutex_lock(&philo->shared_info->fork[philo->left_fork]);
		pthread_mutex_lock(&philo->shared_info->fork[philo->right_fork]);
		philo_logs(philo, FORK_TAKEN);
		philo_logs(philo, FORK_TAKEN);
		philo->holding_fork = true;
	}
	else if (!philo->id_number % 2)
	{
		pthread_mutex_lock(&philo->shared_info->fork[philo->right_fork]);
		pthread_mutex_lock(&philo->shared_info->fork[philo->left_fork]);
		philo_logs(philo, FORK_TAKEN);
		philo_logs(philo, FORK_TAKEN);
		philo->holding_fork = true;
	}
}

void	*single_philo(void *param)
{
	t_philo	*temp_philo;

	temp_philo = (t_philo *)param;
	pthread_mutex_lock(&temp_philo->shared_info->fork[temp_philo->left_fork]);
	philo_logs(temp_philo, FORK_TAKEN);
	usleep((useconds_t) temp_philo->shared_info->time_to_die * 1000);
	pthread_mutex_unlock(&temp_philo->shared_info->fork[temp_philo->left_fork]);
	philo_logs(temp_philo, DIED);
	pthread_mutex_lock(&temp_philo->shared_info->lock);
	temp_philo->shared_info->finish = true;
	pthread_mutex_unlock(&temp_philo->shared_info->lock);
	return (NULL);
}
