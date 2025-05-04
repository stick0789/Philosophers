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

/*void	print_status(t_philo *philo, char *str)
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
}*/

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->shared_data->print_mutex);
	if (!check_stop(philo->shared_data))
	{
		printf("%lld %d %s\n", get_time() - philo->shared_data->start_time,
			philo->id, str);
	}
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	long long think_delay = philo->id * 20;

	if (philo->shared_data->must_eat_count != -1)
	{
        pthread_mutex_lock(&philo->meal_mutex);
        if (philo->meals_eaten >= philo->shared_data->must_eat_count) 
		{
            pthread_mutex_unlock(&philo->meal_mutex);
            return; // No toma tenedores si ya comió suficiente
        }
        pthread_mutex_unlock(&philo->meal_mutex);
    }
	if (philo->shared_data->num_philos == 2)
    {
		//printf("entro aqui %d\n", philo->id);
		//precise_usleep(think_delay, philo->shared_data);
        if (philo->id == 1)
        {
			
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken: left fork");
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken: right fork");
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken: right fork");
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken: left fork");
        }
        return ;
    }
	if (philo->id % 2 == 0)
	{
		//printf("entro aqui tambien");
		precise_usleep(think_delay, philo->shared_data);
		//usleep(5000);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken: right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken: left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken: left fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken: right fork");
	}
}

// void	take_forks(t_philo *philo)
// {
// 	if (philo->id == philo->shared_data->num_philos)
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		print_status(philo, "has taken: right fork");
// 		pthread_mutex_lock(philo->left_fork);
// 		print_status(philo, "has taken left fork");
// 	}
// 	else
// 	{
// 		if (philo->id % 2 == 0)
// 		{
// 			pthread_mutex_lock(philo->right_fork);
// 			print_status(philo, "has taken: right fork");
// 			pthread_mutex_lock(philo->left_fork);
// 			print_status(philo, "has taken left fork");
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(philo->left_fork);
// 			print_status(philo, "has taken left fork");
// 			pthread_mutex_lock(philo->right_fork);
// 			print_status(philo, "has taken right fork");
// 		}
// 	}
// 	// version original comentado lo siguiente
// 	// if (philo->shared_data->must_eat_count != -1)
// 	// {
// 	// 	pthread_mutex_lock(&philo->meal_mutex);
// 	// 	if(philo->meals_eaten >= philo->shared_data->must_eat_count)
// 	// 	{
// 	// 		pthread_mutex_unlock(&philo->meal_mutex);
// 	// 		return ;
// 	// 	}
// 	// 	pthread_mutex_unlock(&philo->meal_mutex);
// 	// }
// }

/*void think_philo(t_philo *philo) {
    long long time_since_last_meal = get_time() - philo->last_meal;
    
    if (time_since_last_meal > philo->shared_data->time_to_die * 0.7) {
        precise_usleep(philo->shared_data->time_to_eat, philo->shared_data);  // Espera larga
    } else {
		ft_usleep(5);
        //precise_usleep(philo->shared_data->time_to_eat / 3, philo->shared_data);  // Espera normal
    }
	
}*/

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
		usleep(5000);
	while (!check_stop(philo->shared_data))
	{
		if (philo->shared_data->must_eat_count != -1 && philo->meals_eaten >= philo->shared_data->must_eat_count)
			break ;
		take_forks(philo);
		update_last_meal(philo);
		print_status(philo, "is eating");
		precise_usleep(philo->shared_data->time_to_eat, philo->shared_data);
		
		if (philo->id == philo->shared_data->num_philos)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}		
		print_status(philo, "is sleeping");
		precise_usleep(philo->shared_data->time_to_sleep, philo->shared_data);
		print_status(philo, "is thinking");
		ft_usleep(5);
		//think_philo(philo);
		//precise_usleep(philo->shared_data->time_to_eat / 2, philo->shared_data);
		/*if (philo->shared_data->num_philos % 2 != 0 )
		{
			update_last_meal(philo);
			precise_usleep(philo->shared_data->time_to_eat, philo->shared_data);
			//precise_usleep(philo->shared_data->time_to_sleep, philo->shared_data);
		}*/
		
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data *data;
	int	i;

	data = (t_data *)arg;
	//while (!check_stop(data))
	//while (!data->stop_flag)
	if (data->num_philos % 2 == 0)
		usleep(5000);
	while (!check_stop(data))
	{
		//usleep(1500);
		i = 0;
		while(i < data->num_philos)
		{
			if ((get_time() - get_last_meal(&data->philos[i]) > data->time_to_die))
			{
				print_status(&data->philos[i], " died");
				set_stop(data);
				return (NULL);
			}
			i++;
		}
		if (check_meals(data))
		{
			set_stop(data);
			return (NULL);
		}
	}
	return (NULL);
}




