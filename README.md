# Philosophers

A simulation of the Dining Philosophers problem using POSIX threads and mutexes. It coordinates fork access, tracks meal timing, monitors starvation, and supports an optional meal-count stopping condition.

**42 Common Core · Rank 03** · [Curriculum hub](https://github.com/Rspinelli93/42-Common-Core) · [All projects](https://github.com/Rspinelli93/Rspinelli93/blob/main/PROJECTS.md)

## Build and run

Requirements: C compiler, Make, and POSIX threads.

```bash
git clone https://github.com/Rspinelli93/philosophers.git
cd philosophers
make
./philo 5 800 200 200 3
```

This example creates five philosophers and requests three meals per philosopher. Timing values are milliseconds.

## Using the project

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_per_philosopher]
```

The optional final argument stops the simulation when all philosophers reach the meal count. Without it, the simulation runs until a philosopher dies. Scheduling and machine load affect timing; a successful run is not a proof that all concurrent executions are race-free.

`init.c` creates simulation state, `philo_routine.c` implements the lifecycle, `monitor_routine.c` checks timing and completion, and `exit.c` handles cleanup.

## Build cleanup

Use `make clean` to remove object files, `make fclean` to remove build products, and `make re` to rebuild.
