/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:26:21 by rick              #+#    #+#             */
/*   Updated: 2025/12/01 23:27:40 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*valid_input(char *str);
static int	is_digit(char c);
static int	is_space(char c);

/*
* Parses the arguments recieved in argv.
* Checks for valid numbers for all of them as well
* as the amount of parameters.*/
int	input_parser(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_atol(av[1]) == 0)
			exit_msg("You must input at least one philosopher\n");
		if (ft_atol(av[2]) < 60
			|| ft_atol(av[3]) < 60
			|| ft_atol(av[4]) < 60)
			exit_msg("Timestamps must be bigger than 60ms\n");
		return (1);
	}
	return (0);
}

/*
* Transforms a char * into its long int representation.
* if the number exedes INT_MAX prints an error message and
* exits the program.*/
long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		exit_msg("Inputs contains non-numeric characters\n");
	if (num > INT_MAX)
		exit_msg("Input is bigger than INT_MAX\n");
	return (num);
}

/*
* validates the string, if not valid prints a message and
* exits the program.*/
static char	*valid_input(char *str)
{
	int		len;
	char	*num;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		exit_msg("Arguments must be positive\n");
	if (!is_digit(*str))
		exit_msg("Inputs must be numbers\n");
	num = str;
	while (is_digit(*num))
	{
		len++;
		num++;
	}
	if (len > 10)
		exit_msg("Input is bigger than INT_MAX\n");
	return (str);
}

/*
* bool to check if char 'c' is a digit*/
static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
* bool to check if char 'c' is a space*/
static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
