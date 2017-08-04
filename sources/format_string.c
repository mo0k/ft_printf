/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 00:06:52 by mo0ky             #+#    #+#             */
/*   Updated: 2017/08/05 01:06:10 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

static int		init_format(t_format *format)
{
	if (!format)
		return (0);
	format->fieldwidth = 0;
	format->precison = 0;
	format->flag_char = '.';
	format->flag_len = FLAG_LEN_NODEF;
	format->flag_convert = 0;
	return (1);
}

static int		printf_format(t_format *format)
{
	if (!format)
		return (0);
	printf("flag_char:%c\n, fieldwidth:%d\n, precison:%d\n, len_modifier:%d\n, convert_specifier%c\n", \
		format->flag_char, format->fieldwidth, format->precison,format->flag_len,format->flag_convert);
	return (1);
}

static int		merge_format(t_format *format, char *format_string)
{
	(void)format;
	(void)format_string;
	return (1);
}

int		do_format(char *format_string, t_buffer_malloc *mbuff, va_list *args)
{
	t_format	format;
	(void)format_string;
	(void)mbuff;
	(void)args;

	init_format(&format);
	printf_format(&format);
	merge_format(&format, format_string);
	return (1);
}