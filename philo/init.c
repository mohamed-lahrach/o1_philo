/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:02:19 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/15 18:30:49 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_data(t_data *data)
{
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (0);
	if (data->nbr_times_must_eat <= 0 && data->nbr_times_must_eat != -1)
		return (0);
	if (data->number_of_philosophers == 0)
		return (0);
	return (1);
}

void	*parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (NULL);
	}
	data->number_of_philosophers = ft_atol(argv[1]);
	if (data->number_of_philosophers == 1)
	{
		printf("0 1 died\n");
		return (NULL);
	}
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->nbr_times_must_eat = ft_atol(argv[5]);
	else
		data->nbr_times_must_eat = -1;
	if (validate_data(data) == 0)
	{
		printf("Error: Invalid input\n");
		return (NULL);
	}
	return (data);
}

void	initialize_philosopher_data(t_data *data, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1)
			% data->number_of_philosophers];
		if (philos[i].id % 2 == 0)
		{
			philos[i].left_fork = &data->forks[(i + 1)
				% data->number_of_philosophers];
			philos[i].right_fork = &data->forks[i];
		}
		philos[i].time_last_meal = data->start_time;
		philos[i].meals_eaten = 0;
		i++;
	}
}

int	initialize_philosophers(t_data *data, t_philosopher **philos)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	*philos = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!data->forks || !*philos)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	data->dead_or_full_eaten = 0;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	initialize_philosopher_data(data, *philos);
	return (0);
}
