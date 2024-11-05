#include "philo.h"

/**
 * @brief Parse command-line arguments and initialize data.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param data Data structure to initialize.
 * @return int 0 on success, 1 on failure.
 */
void error_exit(const char *error)
{
    printf(RED "%s\n" RST, error);
    exit(EXIT_FAILURE);
}

void parse_arguments(int argc, char **argv, t_data *data)
{
    if (argc != 5 && argc != 6)
        error_exit("Wrong input: \n" G "Correct is ./philo 5 800 200 200 5" RST);
    data->number_of_philosophers = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if (data->time_to_die < 60 ||
        data->time_to_eat < 60 ||
        data->time_to_sleep < 60)
        error_exit("Use timestamps major than 60ms");
    if (argv[5])
        data->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
    else
        data->number_of_times_each_philosopher_must_eat = -1;
}

/**
 * @brief Initialize philosophers and mutexes.
 *
 * @param data Shared data structure.
 * @param philos Pointer to the array of philosophers.
 * @return int 0 on success, 1 on failure.
 */

int initialize_philosophers(t_data *data, t_philosopher **philos)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    *philos = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
    if (!data->forks || !*philos)
    {
        printf("Error: Memory allocation failed\n");
        return (1);
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    data->someone_died = 0;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    i = 0;
    while (i < data->number_of_philosophers)
    {
        (*philos)[i].id = i + 1;
        (*philos)[i].data = data;
        (*philos)[i].left_fork = &data->forks[i];
        (*philos)[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
        if ((*philos)[i].id % 2 == 0)
        {
            (*philos)[i].left_fork = &data->forks[(i + 1) % data->number_of_philosophers];
            (*philos)[i].right_fork = &data->forks[i];
        }
        (*philos)[i].last_meal_time = data->start_time;
        (*philos)[i].meals_eaten = 0;
        i++;
    }
    return (0);
}
