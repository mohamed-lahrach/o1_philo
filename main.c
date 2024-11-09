/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:01:42 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/09 19:01:43 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_mutex);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosopher	*philos;
	int				i;

	i = 0;
	memset(&data, 0, sizeof(t_data));
	parse_arguments(argc, argv, &data);
	data.start_time = get_current_time();
	if (initialize_philosophers(&data, &philos))
		return (1);
	while (i < data.number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, philosopher_routine,
			&philos[i]);
		i++;
	}
	data.philos = philos;
	monitor_philosophers(&data);
	i = 0;
	while (i < data.number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	clean_up(&data);
	return (0);
}
