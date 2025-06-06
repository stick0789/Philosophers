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

void	take_forks(t_philo *philo)
{
	if (philo->shared_data->must_eat_count != -1)
	{
        pthread_mutex_lock(&philo->meal_mutex);
        if (philo->meals_eaten >= philo->shared_data->must_eat_count) {
            pthread_mutex_unlock(&philo->meal_mutex);
            return ;
        }
        pthread_mutex_unlock(&philo->meal_mutex);
    }
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken: right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken: left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken: right fork");
	}
}

void	*philosopher(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->shared_data->num_philos == 1)
	{
		print_status(philo, "has taken: right fork");
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(1, philo->shared_data);
	if (philo->shared_data->stop_flag == 1 )
		return (NULL) ;
	else
	{
	while (!check_stop(philo->shared_data))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		if (philo->shared_data->must_eat_count != -1 
			&& philo->meals_eaten >= philo->shared_data->must_eat_count)
		break ;
		sleep_philo(philo);
		think_philo(philo);
		}
	}
	return (NULL);
}

void *monitor_routine(void *arg) {
    t_data *data = (t_data *)arg;
    
	if (data->num_philos % 2 == 0)
		precise_usleep(1, data);
    while (!check_stop(data)) {
        usleep(500);
        for (int i = 0; i < data->num_philos; i++) {
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            long long time_since_last_meal = get_time() - data->philos[i].last_meal;
            
            if (time_since_last_meal > data->time_to_die) {

                pthread_mutex_lock(&data->print_mutex);
				
                if (!data->stop_flag) 
				{
                    printf("%lld %d died\n", 
                          get_time() - data->start_time, 
                          data->philos[i].id);
                    //fflush(stdout);
                    set_stop(data);
                }
				
                pthread_mutex_unlock(&data->print_mutex);
                pthread_mutex_unlock(&data->philos[i].meal_mutex);
				//pthread_mutex_unlock(&data->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
			//pthread_mutex_unlock(&data->stop_mutex);
        }

        // Verificar comidas completadas
        if (data->must_eat_count != -1 && check_meals(data)) 
		{
			//pthread_mutex_lock(&data->stop_mutex);
            pthread_mutex_lock(&data->print_mutex);
            set_stop(data);
            pthread_mutex_unlock(&data->print_mutex);
			//pthread_mutex_unlock(&data->stop_mutex);
            return NULL;
        }
    }
    return NULL;
}

/*
void	*monitor_routine(void *arg)
{
	t_data *data;
	int	i;
	long long current_time;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		usleep(5000);
		//precise_usleep(1, data);
		i = 0;
		while(i < data->num_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			current_time = get_time() - data->philos[i].last_meal;
			//pthread_mutex_unlock(&data->philos[i].meal_mutex);
			
			if ((current_time > data->time_to_die))
			{
				pthread_mutex_lock(&data->print_mutex);
				if (!data->stop_flag)
				{
					printf("%lld %d died\n", 
						get_time() - data->start_time, 
						data->philos[i].id);
					//print_status(&data->philos[i], "has died");
					fflush(stdout);
					set_stop(data);
				}
				//print_status(&data->philos[i], "has died");
				//fflush(stdout);
				//set_stop(data);
				
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->philos[i].meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			i++;
		}
		if (check_meals(data))
		{
			pthread_mutex_lock(&data->print_mutex);
			set_stop(data);
			pthread_mutex_unlock(&data->print_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
	*/