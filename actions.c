/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:01:59 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/09 19:02:00 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->print_mutex);
	print_action(philo, "is eating");
	precise_usleep(philo->data->time_to_eat, philo);
	philo->meals_eaten += 1;
}

void	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philosopher *philo)
{
	print_action(philo, "is sleeping");
	precise_usleep(philo->data->time_to_sleep, philo);
}

void	think(t_philosopher *philo)
{
	print_action(philo, "is thinking");
}
