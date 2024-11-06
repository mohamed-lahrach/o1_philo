/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [Your Name]                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [Date]                                   #+#    #+#             */
/*   Updated: [Date]                                   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>      // For usleep
# include <sys/time.h>    // For gettimeofday
# include <string.h>      // For memset
# include <stdbool.h>        // For bool
# include <limits.h>        // For INT_MAX

#define RST "\033[0m"    // Reset to default color
#define RED "\033[1;31m" /* Bold Red */
#define G "\033[1;32m"   /* Bold Green */
#define Y "\033[1;33m"   /* Bold Yellow */
#define B "\033[1;34m"   /* Bold Blue */
#define M "\033[1;35m"   /* Bold Magenta */
#define C "\033[1;36m"   /* Bold Cyan */
#define W "\033[1;37m"   /* Bold White */

typedef struct s_data
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             number_of_times_each_philosopher_must_eat;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    int             someone_died;
}               t_data;

typedef struct s_philosopher
{
    int             id;
    t_data          *data;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long       last_meal_time;
    int             meals_eaten;
}               t_philosopher;

/* init.c */
void         parse_arguments(int argc, char **argv, t_data *data);
int         initialize_philosophers(t_data *data, t_philosopher **philos);
void error_exit(const char *error);

/* philosopher.c */
void        *philosopher_routine(void *arg);

/* actions.c */
void        take_forks(t_philosopher *philo);
void        eat(t_philosopher *philo);
void        put_down_forks(t_philosopher *philo);
void        philo_sleep(t_philosopher *philo);
void        think(t_philosopher *philo);
void        show_last_meal_time(t_philosopher *philo);

/* utils.c */
long long   get_current_time(void);
long long   get_timestamp(long long start_time);
void        print_action(t_philosopher *philo, char *action);
void        precise_usleep(long long time_in_ms, t_philosopher *philo);

/* monitoring.c */
void        monitor_philosophers(t_philosopher *philos, t_data *data);

/* libft.c */
long        ft_atol(const char *str);
void        ft_memset(void *s, int c, size_t n);

#endif
