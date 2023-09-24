/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:20:45 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/16 18:26:58 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id_number % 2)
	{
		usleep(1500);
		pthread_mutex_lock(&philo->shared_info->fork[philo->left_fork]);
		pthread_mutex_lock(&philo->shared_info->fork[philo->right_fork]);
		print_fork(philo);
		philo->holding_fork = true;
	}
	else
	{
		pthread_mutex_lock(&philo->shared_info->fork[philo->right_fork]);
		pthread_mutex_lock(&philo->shared_info->fork[philo->left_fork]);
		print_fork(philo);
		philo->holding_fork = true;
	}
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	philo_logs(philo, EATING);
	pthread_mutex_lock(&philo->shared_info->lock);
	philo->last_meal = time_from_start(philo->shared_info);
	philo->nbr_of_meals++;
	pthread_mutex_unlock(&philo->shared_info->lock);
	ft_delay(philo, philo->shared_info->time_to_eat);
	if (philo->holding_fork == true)
	{
		philo->holding_fork = false;
		pthread_mutex_unlock(&philo->shared_info->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->shared_info->fork[philo->right_fork]);
	}
	philo_logs(philo, SLEEPING);
	ft_delay(philo, philo->shared_info->time_to_sleep);
	philo_logs(philo, THINKING);
}

void	print_fork(t_philo *philo)
{
	philo_logs(philo, FORK_TAKEN);
	philo_logs(philo, FORK_TAKEN);
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
