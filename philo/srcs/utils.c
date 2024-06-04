/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:13:57 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/04 13:13:57 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_skip_white_spaces(const char *str)
{
	int	x;

	x = 0;
	while ((str[x] > 8 && str[x] < 14) || str[x] == 32)
		x++;
	return (x);
}

static int	ft_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	nb = 0;
	i = ft_skip_white_spaces(str);
	sign = ft_sign(str[i]);
	if (ft_strncmp(str + i, "-2147483648", 12) == 0)
		return (-2147483648);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		if ((nb * 10 + (str[i] - '0')) < nb)
			return (-(sign == 1));
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((nb * sign));
}
