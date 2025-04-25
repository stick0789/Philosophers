#ifndef PHILO_H
# define PHILO_H

/***	Librerias usadas/Used Libraries		***/
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

/***	Estructuras de datos/Data structures	***/
typedef struct s_data t_data;
typedef struct s_data {
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_count;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    long long       start_time;
    int             stop_flag;
    pthread_mutex_t stop_mutex;
    struct s_philo	*philos;
} t_data;

typedef struct s_philo {
    int             id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long       last_meal;
    pthread_mutex_t meal_mutex;
    int             meals_eaten;
    t_data          *shared_data;
} t_philo;

/***	Funciones Auxiliares/Auxiliar Function	***/
int     ft_strlen(const char *s);
char    *ft_lltoa(long long n);
long    ft_atoi(const char *nptr);
void    ft_putstr_fd(char *s, int fd);
void    clean(t_data *data, t_philo *philos);
long long       get_time(void);
void    precise_usleep(long long miliseconds, t_data *data);
void    print_status(t_philo *philo, char *str);
/***	Inicializaciones datos/data inits	***/
t_data  init_data(int ac, char **av);
t_philo *init_philos(t_data *data);
/***	Monitor y verificadores/Checkers and monitor	***/
void	set_stop(t_data *data);
void    *monitor_routine(void *arg);
int     check_stop(t_data *data);
void    update_last_meal(t_philo *philo);
/***	Logica del filosofo/Philosopher Logic	***/
void    *philosopher(void *arg);

#endif
