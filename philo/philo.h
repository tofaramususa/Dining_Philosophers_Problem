/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:22:03 by tmususa           #+#    #+#             */
/*   Updated: 2023/07/02 21:20:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_data	t_data;
typedef struct t_node	t_philo;

typedef struct s_data
{
	int				meal_nbr;
	int				nbr_of_philo;
	bool			finish;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_start;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_data;

typedef struct t_node
{
	t_data		*shared_info;
	int			id_number;
	int			left_fork;
	int			right_fork;
	pthread_t	phlthread;
	int			nbr_of_meals;
	long long	last_meal;
	bool		holding_fork;
}	t_philo;

# define ERR_ARGS    	"The arguments have to be POSITIVE INTEGER values\n"
# define ERR_SIXTY_ARGS    	"Times should not be under 60ms\n"
# define ERR_NUM_ARGS   "This program takes 4-5 integer arguments:"
# define ARGS "nbr_of_philos\ttime_2_die\ttime_2_eat\ttime_2_sleep\t[nbr_of_meals]\n"
# define FORK_TAKEN		"has taken a fork"
# define EATING			"is eating"
# define DIED			"died"
# define THINKING		"is thinking"
# define SLEEPING		"is sleeping"

int			ft_arg_checker(char **argv);
int			ft_atoi(const char *str);
int			check_digit(char *str);
long long	current_time(void);
long long	time_from_start(t_data *info);
void		ft_free(t_data *info);
void		*ft_calloc(size_t count, size_t size);
void		init(char **argv, t_data *info);
void		init_philo(t_data *info);
void		program_start(t_data *info);
void		*philo_start(void *param);
void		program_status(t_data *info);
void		each_philo_eat(t_data *info);
void		check_death(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		take_forks(t_philo *philo);
void		init(char **argv, t_data *info);
void		init_philo(t_data *info);
void		philo_logs(t_philo *philo, char *message);
void		ft_delay(t_philo *philo, int waiting_time);
void		*single_philo(void *param);

#endif