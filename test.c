/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:57:46 by rick              #+#    #+#             */
/*   Updated: 2025/12/10 14:05:39 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
# 1. WRONG ARGUMENT COUNT
./philo 1 800 200                    # -> Error (Too few args)
./philo 1 800 200 200 7 5            # -> Error (Too many args)

# 2. NON-NUMERIC CHARACTERS
./philo a 800 200 200                # -> Error (Letter in arg 1)
./philo 1 800 200 200 a              # -> Error (Letter in arg 5)
./philo 1 800 200 200 7a             # -> Error (Letter attached to number)
./philo 1 800 200.5 200              # -> Error (Float/Decimal)

# 3. NEGATIVE NUMBERS (Must be positive)
./philo -5 800 200 200               # -> Error (Negative philosophers)
./philo 5 800 200 200 -5             # -> Error (Negative eat count)
./philo 5 -800 200 200               # -> Error (Negative time)

# 4. SIGN ISSUES
./philo + 800 200 200                # -> Error (Lonely plus)
./philo 5 ++800 200 200              # -> Error (Double sign)
./philo 5 800- 200 200               # -> Error (Sign after number)

# 5. ZERO VALUES (Logical errors)
./philo 0 800 200 200                # -> Error (0 Philosophers not allowed)
./philo 4 0 200 200                  # -> Error (0 Time to die)

# 6. INT LIMITS
./philo 2147483648 800 200 200       # -> Error (INT MAX overflow)
./philo 5 800 200 200 3000000000     # -> Error (Overflow)

# 7. VALID CASES (Should run)
./philo 4 800 200 200                # -> OK (Infinite simulation)
./philo 4 800 200 200 7              # -> OK (Simulation stops after 7 eats)
./philo 1 800 200 200                # -> OK (1 Philo is valid, though he dies)
./philo +4 800 200 200               # -> OK (Explicit plus is valid)*/