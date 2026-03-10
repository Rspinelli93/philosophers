# Philosophers

My implementation of the classic Dining Philosophers problem, a concurrency project for 42.

## Description

This project serves as an introduction to threading and processes. You will learn how to create multiple threads running concurrently and how to synchronize them using mutexes to prevent data races, deadlocks, and starvation.

The simulation follows these rules:
* One or more philosophers sit at a round table.
* There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively **eat**, **think**, or **sleep**.
* There are as many forks on the table as there are philosophers.
* A philosopher must acquire exactly two forks (the one on their left and the one on their right) to eat.
* When a philosopher finishes eating, they drop both forks and start sleeping. Once awake, they start thinking again. 
* The simulation stops the moment a philosopher starves to death.

## Core Concepts

* **Threads (`pthread_create`):** Every philosopher is a separate thread. This means they all execute their routines simultaneously within the same main process.
* **Mutexes (`pthread_mutex_init`):** Because the threads share the same memory, data races will occur if two philosophers try to grab the same fork at the exact same time. Every fork state, as well as the printing of the logs and the death status, must be strictly protected by mutex locks.

## Usage

Compile the executable using the provided Makefile:

    make

Run the program with the following arguments:

    ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

### Arguments:
1. **`number_of_philosophers`**: The number of philosophers and also the number of forks.
2. **`time_to_die` (in milliseconds)**: If a philosopher doesn't start eating `time_to_die` milliseconds since the beginning of their last meal (or the start of the simulation), they die.
3. **`time_to_eat` (in milliseconds)**: The time it takes for a philosopher to eat. They must hold two forks during this entire time.
4. **`time_to_sleep` (in milliseconds)**: The time a philosopher will spend sleeping after a meal.
5. **`number_of_times_each_philosopher_must_eat` (optional)**: If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation runs until someone dies.

### Example:

    # 5 philosophers. They die if they go 800ms without eating. 
    # They take 200ms to eat, and 200ms to sleep. 
    # This specific configuration should run indefinitely (no one dies).
    ./philo 5 800 200 200

    # 4 philosophers. They die if they go 310ms without eating.
    # They take 200ms to eat, and 100ms to sleep.
    # A philosopher will die in this setup.
    ./philo 4 310 200 100