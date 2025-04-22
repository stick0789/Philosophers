/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaacosta <jaacosta@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:47:51 by jaacosta          #+#    #+#             */
/*   Updated: 2025/04/21 17:25:55 by jaacosta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int    validate_av(int ac, char **av)
{
	int     i;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Error: Nro de argumentos incorrectos", 1);
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_positive_number(av[i]))
		{
			ft_putstr_fd("Error: Argvs deben ser enteros positivos", 1);
			return (0);
		}
		i++;
    }
	if (ft_atoi(av[1]) < 1)
	{
		ft_putstr_fd("Error: Debe haber almenos un filosofo", 1);
		return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;
	pthread_t	*threads;
	pthread_t	monitor;
	int	i;

	if(validate_av(ac, av))
	{
		data = init_data(ac, av);
		philos = init_philos(&data);
		data.philos = philos;
		threads = malloc(data.num_philos * sizeof(pthread_t));
		if (!threads)
			return (0);
		i = 0;
		while (i < data.num_philos)
		{
			if (pthread_create(&threads[i], NULL, philosopher, &philos[i]) != 0)
				return (1); // Manejo de error simple
			if (pthread_detach(threads[i]) != 0)
				return (1);
			i++;
		}
		pthread_create(&monitor, NULL, monitor_routine, &data);
		/*
		while (i < data.num_philos)
		{
			pthread_create(&threads[i], NULL, philosopher, &philos[i]);
			i++;
		}
		pthread_create(&monitor, NULL, monitor_routine, &data);
		*/
		//i = 0;
		//pthread_detach(monitor);
		pthread_join(monitor, NULL);
		/*while (i < data.num_philos)
		{
			pthread_join(threads[i], NULL);
			i++;
		}*/
		/*
		while (i < data.num_philos)
		{
			if (data.num_philos == 1)
			{
				pthread_join(threads[0], NULL);
				break ;
			}
			else
			{
				pthread_join(threads[i], NULL);
				i++;
			}
		}
		*/
		sleep(2);
		clean(&data, philos);
		free(threads);
	}
	write(1, "\n", 1);
}

