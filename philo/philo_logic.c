/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:33:17 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/18 20:19:24 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	long long timestamp;
	char	*str_time;
	char	*str_id;
	pthread_mutex_lock(&philo->shared_data->print_mutex);
	if (!philo->shared_data->stop_flag)
	{
		timestamp = get_time() - philo->shared_data->start_time;
		str_time = ft_lltoa(timestamp);
		str_id = ft_lltoa(philo->id);
		write(1, str_time, ft_strlen(str_time));
		write(1, " ", 1);
		write(1, str_id, ft_strlen(str_id));
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		free(str_time);
		free(str_id);
	}
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

void	*philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1500);
	//if (check_stop(philo->shared_data))
	//	return (NULL);
//		precise_usleep(philo->shared_data->time_to_eat * 0.9);
	while (!check_stop(philo->shared_data))
	{
		//if (check_stop(philo->shared_data)) break;
		if (philo->shared_data->stop_flag)
			return (NULL);
		else
		{
		take_forks(philo);
		
		print_status(philo, "is eating");
		update_last_meal(philo);
		precise_usleep(philo->shared_data->time_to_eat);
		//release_forks(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		//sleep_philo(philo);
		print_status(philo, "is sleeping");
		print_status(philo, "is Thinking");
		precise_usleep(philo->shared_data->time_to_sleep);
		}
		//if(philo->shared_data->stop_flag)
		//	break ;
		
	}
	return (NULL);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}


