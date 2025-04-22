/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:39:41 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/18 20:17:39 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

// Inicializar mutexes y datos compartidos
t_data	init_data(int ac, char **av) 
{
	int	i;
	t_data data;
	data.num_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	//data.must_eat_count = (ac == 6) ? atoi(av[5]) : -1;
	if(ac == 6)
		data.must_eat_count = ft_atoi(av[5]);
	else
		data.must_eat_count = -1;
	data.forks = malloc(data.num_philos * sizeof(pthread_mutex_t));
	if (!data.forks)
		ft_putstr_fd("Error: Fallo en malloc data.forks", 1);
	while (i < data.num_philos)
	{
		if(pthread_mutex_init(&data.forks[i], NULL) != 0)
			ft_putstr_fd("Error: Fallo al crear mutex de tenedor", 1);
		i++;
	}
	if (pthread_mutex_init(&data.print_mutex, NULL) != 0)
		ft_putstr_fd("Error: Fallo al crear mutex de impresion", 1);
	if (pthread_mutex_init(&data.stop_mutex, NULL) != 0)
		ft_putstr_fd("Error: Fallo al crear mutex de parada", 1);
	data.stop_flag = 0;
	data.start_time = get_time();
    	return data;
}

//Inicializar Philos
t_philo	*init_philos(t_data *data)
{
	t_philo *philos;
	int	i;
	philos = malloc(data->num_philos * sizeof(t_philo));
	if (!philos)
		ft_putstr_fd("Error: Fallo en malloc philos", 1);
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
			ft_putstr_fd("Error: Fallo al crear mutex de comida", 1);
		philos[i].last_meal = data->start_time;
		philos[i].meals_eaten = 0;
		philos[i].shared_data = data;
		i++;
	}
	return (philos);
}
