/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 00:06:52 by mo0ky             #+#    #+#             */
/*   Updated: 2017/08/13 00:25:23 by mo0ky            ###   ########.fr       */
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
	format->precision = 0;
	//format->flag_char = '.';
	init_flag_char(&format->flag_char);
	format->flag_mlen = FLAG_MLEN_NODEF;
	//ft_strclr(format->mlen);
	format->convch = 0;
	return (1);
}

static int		printf_format(t_format *format)
{
	if (!format)
		return (0);
	printf("fieldwidth:%d\nprecison:%d\nlen_modifier:%d\nconvert_specifier:'%c'\n", \
		format->fieldwidth, format->precision, format->flag_mlen, format->convch);
	print_flag_char(format->flag_char);
	return (1);
}

static enum e_flag_mlen	is_flag_mlen(char *ptr)
{
	if (!ft_strncmp(ptr, "ll", 2))
	{
		printf("return FLAG_MLEN_LL => %d\n", FLAG_MLEN_LL);
		return (FLAG_MLEN_LL);
	}
	else if (*ptr == 'l')
	{
		printf("return FLAG_MLEN_L => %d\n", FLAG_MLEN_L);
		return (FLAG_MLEN_L);
	}
	else if (!ft_strncmp(ptr, "hh", 2))
	{
		printf("return FLAG_MLEN_HH => %d\n", FLAG_MLEN_HH);
		return (FLAG_MLEN_HH);
	}
	else if (*ptr == 'h')
	{
		printf("return FLAG_MLEN_H => %d\n", FLAG_MLEN_H);
		return (FLAG_MLEN_H);
	}
	printf("return FLAG_MLEN_NODEF => %d\n", FLAG_MLEN_NODEF);
	return (FLAG_MLEN_NODEF);
}

static void 		set_flag_char(t_flag_char *flag_char, char *ptr)
{
	int		i;

	if (!flag_char || !ptr)
		return ;
	i = 0;
	while (flag_char->key[i])
	{
		if (*ptr == flag_char->key[i])
			flag_char->flag[i] = TRUE;
		i++;
	}
}

static void 		set_fieldwidth(int *fieldwidth, char **aptr)
{
	char			c;
	char			*start;

	if (!fieldwidth || !aptr || !*aptr)
		return ;
	start = *aptr;
	while (**aptr && ft_isdigit(**aptr))
		++(*aptr);
	if (start < *aptr)
	{
		c = **aptr;
		**aptr = 0;
		*fieldwidth = ft_atoi(start);
		if (*fieldwidth < 0)
			*fieldwidth = 0;
		**aptr = c;
		--(*aptr);
	}
	//else
	//	++(*aptr);
}

static void 		set_precision(int *precision, char **aptr)
{
	ft_putendlcolor("DEBUG start set_precision ____________________________", C_YELLOW);
	char			c;
	char			*start;

	if (!precision || !aptr || !*aptr)
		return ;
	printf("*aptr(%p):'%c'\n", *aptr, **aptr);
	if (*(*aptr + 1) != '.')
		++(*aptr);

	printf("*aptr inc\n");
	start = *aptr;
	printf("*aptr(%p):'%c'\tstart(%p):'%c'\n", *aptr, **aptr, start, *start);
	while (**aptr && ft_isdigit(**aptr))
	{
		printf("boucle is_digit => *aptr(%p):'%c'\n", *aptr, **aptr);
		++(*aptr);
	}
	if (start < *aptr)
	{
		printf("start < *aptr\n");
		c = **aptr;
		**aptr = 0;
		*precision = ft_atoi(start);
		if (*precision < 0)
			*precision = 0;
		**aptr = c;
		--(*aptr);
		printf("*aptr(%p):'%c'\n", *aptr, **aptr);
	}
	//else
		//++(*aptr);
	ft_putendlcolor("DEBUD end set_precision ____________________________", C_YELLOW);
}

static int			merge_format(t_format *format, char *format_string)
{
	ft_putendlcolor("DEBUG start merge_format ____________________________", C_RED);
	enum e_flag_mlen	flag_mlen;
	int state;
	int i;

	(void)flag_mlen;
	state = 0;
	i = 0;
	if (!format_string)
		return (0);
	++format_string;
	while (*format_string)
	{
		printf("%p\n", format_string);
		ft_putstr("*format_string='");
		ft_putcharcolor(*format_string, C_LRED);
		ft_putendl("'");
		if (!state && ft_strchr(format->flag_char.key, *format_string))
		{
			ft_putendlcolor("Go set_flag_char", C_LRED);
			printf("flag char:%c\n", *format_string);
			set_flag_char(&format->flag_char, format_string);
			//++format_string;
		}
		else if (*format_string == '.' && (state = 1))
		{
			ft_putendlcolor("Go set_precision", C_LRED);
			set_precision(&format->precision, &format_string);
		}
		else if (ft_isdigit(*format_string) && (state = 1))
		{
			ft_putendlcolor("Go set_fieldwidth", C_LRED);
			set_fieldwidth(&format->fieldwidth, &format_string);
		}
		else if (*format_string && !*(format_string + 1))
		{
			ft_putendlcolor("Go set_convch", C_LRED);
			format->convch = *format_string;
		}
		else if ((format->flag_mlen = is_flag_mlen(format_string)) != FLAG_MLEN_NODEF)
		{
			if (format->flag_mlen == FLAG_MLEN_LL || format->flag_mlen == FLAG_MLEN_HH)
				++format_string;
		}
		++format_string;
	}
	ft_putendlcolor("DEBUG end merge_format _______________________________", C_RED);
	return (1);
}

int		do_format(char *format_string, t_buffer_malloc *mbuff, va_list *args)
{
	t_format	format;
	(void)format_string;
	(void)mbuff;
	(void)args;

	if (!format_string || !mbuff || !args)
		return (0);
	init_format(&format);
	//printf_format(&format);
	merge_format(&format, format_string);
	printf_format(&format);

	return (1);
}