/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpolatci <kpolatci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:12:49 by kpolatci          #+#    #+#             */
/*   Updated: 2023/10/23 15:20:50 by kpolatci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *count)
{
	int	index;

	index = 0;
	if (!str)
		str = "(null)";
	while (str[index])
	{
		*count += write(1, &str[index], 1);
		index++;
	}
}

void	ft_putnbr(long number, int base, int *count)
{
	char	*lower_base;

	lower_base = "0123456789abcdef";
	if (number < 0)
	{
		number *= -1;
		*count += write(1, "-", 1);
	}
	if (number >= base)
		ft_putnbr(number / base, base, count);
	*count += write(1, &lower_base[number % base], 1);
}

int	ft_is_format(char c)
{
	if (c == 'x' || c == 'd' || c == 's')
		return (1);
	return (0);
}

void	ft_process(char c, va_list list, int *count)
{
	if (c == 'd')
		ft_putnbr((long)va_arg(list, int), 10, count);
	else if (c == 'x')
		ft_putnbr((long)va_arg(list, unsigned int), 16, count);
	else if (c == 's')
		ft_putstr(va_arg(list, char *), count);
}

int	ft_printf(char *str, ...)
{
	va_list		list;
	int			count;
	int			index;

	index = 0;
	count = 0;
	va_start(list, str);
	while (str[index])
	{
		if (str[index] == '%')
		{
			if (ft_is_format(str[index + 1]))
			{
				ft_process(str[index + 1], list, &count);
				index++;
			}
			index++;
			continue ;
		}
		count += write(1, &str[index], 1);
		index++;
	}
	va_end(list);
	return (count);
}
