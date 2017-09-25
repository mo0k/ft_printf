/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 17:07:12 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/25 12:38:55 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int 	ft_printf(const char *format, ...)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = 1;
	va_start(print.args, format);
	if (!analyze_format(&print, format))
		return(-1);
	va_end(print.args);
	return (print.ret);
}

int 	ft_dprintf(int fd, const char *format, ...)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = fd;
	va_start(print.args, format);
	if (!analyze_format(&print, format))
		return(-1);
	va_end(print.args);
	return (print.ret);
}

int		vprintf(const char * restrict format, va_list ap)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = 1;
	ft_memmove(&print.args, ap, sizeof(va_list));
	if (!analyze_format(&print, format))
		return(-1);
	return (print.ret);
}

int		vdprintf(int fd, const char * restrict format, va_list ap)
{
	t_print			print;

	if (!format)
		return (-1);
	init_buffer_static(&print.sbuff);
	print.ret = 0;
	g_fd = fd;
	ft_memmove(&print.args, ap, sizeof(va_list));
	if (!analyze_format(&print, format))
		return(-1);
	return (print.ret);
}