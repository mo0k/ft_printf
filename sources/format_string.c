/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 00:06:52 by mo0ky             #+#    #+#             */
/*   Updated: 2017/08/05 22:38:34 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

static int		init_flag_char(t_flag_char *flag_char)
{
	if (!flag_char)
		return (0);
	flag_char->key[0] = '#';
	flag_char->key[1] = '0';
	flag_char->key[2] = '-';
	flag_char->key[3] = ' ';
	flag_char->key[4] = '+';
	flag_char->flag[0] = 0;
	flag_char->flag[1] = 0;
	flag_char->flag[2] = 0;
	flag_char->flag[3] = 0;
	flag_char->flag[4] = 0;
	return (1);
}

static int 		print_flag_char(t_flag_char flag_char)
{
	int			i;

	i = -1;
	ft_putendlcolor("Details flag_char:", C_LGREEN);
	while (++i <= 4)
	{
		ft_putstr("\t");
		ft_putchar(flag_char.key[i]);
		ft_putstr(" = ");
		ft_putnbrcolor(flag_char.flag[i], C_LBLUE);
		write(1, "\n", 1);
	}
	return (1);
}
static int		init_format(t_format *format)
{
	if (!format)
		return (0);
	format->fieldwidth = 0;
	format->precison = 0;
	//format->flag_char = '.';
	init_flag_char(&format->flag_char);
	format->flag_len = FLAG_LEN_NODEF;
	format->flag_convert = 0;
	return (1);
}

static int		printf_format(t_format *format)
{
	if (!format)
		return (0);
	printf("fieldwidth:%d\nprecison:%d\nlen_modifier:%d\nconvert_specifier:'%c'\n", \
		format->fieldwidth, format->precison,format->flag_len,format->flag_convert);
	print_flag_char(format->flag_char);
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