/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlahrach <mlahrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:02:25 by mlahrach          #+#    #+#             */
/*   Updated: 2024/11/15 18:28:40 by mlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (0);
	if (!is_digit(*str))
		return (0);
	number = str;
	while (is_digit(number[len]))
		len++;
	if (number[len] != '\0')
		return (0);
	if (len > 10)
		return (0);
	return (1);
}

long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	if (valid_input(str) == 0)
		return (0);
	else
	{
		while (is_digit(*str))
		{
			num = num * 10 + *str - '0';
			str++;
		}
	}
	if (num > INT_MAX)
		return (0);
	return (num);
}
