/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 00:06:02 by mo0ky             #+#    #+#             */
/*   Updated: 2017/08/05 01:00:28 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		init(t_print *print, const char *format)
{
	va_list			args;

	if (!print || !format)
		return (0);
	init_buffer_static(&print->sbuff);
	init_buffer_malloc(&print->mbuff);
	print->args = &args;
	print->format = format;
	print->ret = 0;
	return (1);
}