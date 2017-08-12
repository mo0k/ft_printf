/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 17:07:12 by mo0ky             #+#    #+#             */
/*   Updated: 2017/08/13 00:30:04 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

static int	is_flag_mlen(char *ptr)
{
	if (!ft_strncmp(ptr, "ll", 2))
	{
		printf("return FLAG_MLEN_LL => %d\n", FLAG_MLEN_LL);
		return (2);
	}
	else if (*ptr == 'l')
	{
		printf("return FLAG_MLEN_L => %d\n", FLAG_MLEN_L);
		return (1);
	}
	else if (!ft_strncmp(ptr, "hh", 2))
	{
		printf("return FLAG_MLEN_HH => %d\n", FLAG_MLEN_HH);
		return (2);
	}
	else if (*ptr == 'h')
	{
		printf("return FLAG_MLEN_H => %d\n", FLAG_MLEN_H);
		return (1);
	}
	printf("return FLAG_MLEN_NODEF => %d\n", FLAG_MLEN_NODEF);
	return (0);
}
static int		check_format(char **aptr)
{
	int		i;
	int		state;
	int		ret;
	char	*ptr;

	i = 0;
	state = 0;
	while (**aptr && i < 3)
	{
		ft_putstr("**end='");
		ft_putcharcolor(**aptr, C_LMAGENTA);
		ft_putendl("'");
		if (!state && ft_strchr(FLAG_CHAR, **aptr))
		{
			printf("is flag char\n");
			++(*aptr);
		}
		else if ((ft_isdigit(**aptr) || **aptr == '.') && (state = 1))
		{
			printf("ft_isdigit || '.'\n");
			++(*aptr);
			state = 1;
		}
		else if ((ptr = ft_strchr(FLAG_CONVERT, **aptr)) && (state = 1))
		{
			printf("break in strchr(FLAG_CONVERT)\n");
			++(*aptr);
			return (1);
		}
		else if ((ret = is_flag_mlen(*aptr)) && (state = 1))
		{
			*aptr += ret;
		}
		else
			return (0);
	}
	return (0);
}
static int		get_format(char **begin, char **end, t_buffer_malloc *mbuff, va_list *args)
{
	ft_putendlcolor("Begin get_value()", C_CYAN);
	char	tmp[BUFF_SIZE_INIT];

	if (!begin || !*begin || !end || !*end)
		return (0);
	ft_putendlcolor(*begin, C_YELLOW);
	++(*end);
	if (!**end)
	{
		ft_putendlcolor("return (0)", C_RED);
		return (0);
	}
	ft_putendlcolor("DEBUG start get_format ____________________________", C_MAGENTA);
	if (!check_format(end))
	{
		*begin = *end;
		return (0);
	}
	ft_putendlcolor("DEBUG end get_format _______________________________", C_MAGENTA);
	printf("**end:%d, char:'%c'\n", **end, **end);
	if (!**end)
	{
		ft_putstr("strcpy\n");
		ft_strcpy(tmp, *begin);
	}
	else
	{
		ft_putstr("strncpy\n");
		printf("begin:%s, ecart:%ld\n", *begin,  *end - *begin);
		ft_strncpy(tmp, *begin, *end - *begin);
		tmp[*end - *begin] = 0;
	}
	do_format(tmp, mbuff, args);
	ft_putendlcolor(tmp, C_GREEN);
	*begin = *end;
	printf("begin:%p\nend:%p\n", *begin, *end);
	return (0);
}

static int	analyze_format(t_print *print)
{
	char	*begin;
	char	*end;
	//char	//state;
	int		len;
	int 	ret;
	char	tmp[BUFF_SIZE_INIT];

	ft_putendlcolor("Begin analyze()", C_CYAN);
	if (!print)
		return (0);
	//state = 0;
	len = 0;
	begin = (char *)print->format;
	end = (char *)print->format;
	while (*end)
	{
		ft_putcharcolor(*end, C_MAGENTA);
		printf("(%p)\n", end);
		++len;
		if (len == BUFF_SIZE_INIT)
		{
			char c = *end;
			*end = 0;
			while (!fill_buffer_static(&print->sbuff, begin))
			{
				write(1, print->sbuff.buffer, \
					print->sbuff.buff_size - print->sbuff.remaining_size);
				print->ret += BUFF_SIZE_INIT;
				init_buffer_static(&print->sbuff);
				len = 0;
			}
			*end = c;
			begin = end;
		}
		if (*end == '%' && *(end + 1) == '%')
		{
			while (!fill_buffer_static(&print->sbuff, "%"))
			{
				ft_putendlcolor("no fill buffer", C_LCYAN);
				write(1, print->sbuff.buffer, \
					print->sbuff.buff_size - print->sbuff.remaining_size);
				print->ret += (int)(print->sbuff.buff_size - print->sbuff.remaining_size);
				init_buffer_static(&print->sbuff);
				len = 0;
			}
			end += 2;
			begin = end;
		}
		else if (*end == '%')
		{
			ft_putendlcolor("*end == '%'", C_CYAN);
			printf("begin:%s, ecart:%ld\n", begin,  end - begin);
			ft_strncpy(tmp, begin, end - begin);
			tmp[end - begin] = 0;
			ft_putendlcolor(tmp, C_GREEN);
			while (!fill_buffer_static(&print->sbuff, tmp))
			{
				ft_putendlcolor("no fill buffer", C_LCYAN);
				write(1, print->sbuff.buffer, print->sbuff.buff_size - print->sbuff.remaining_size);
				print->ret += (int)(print->sbuff.buff_size - print->sbuff.remaining_size);
				init_buffer_static(&print->sbuff);
				len = 0;
			}
			begin = end;
			ft_putendlcolor("DEBUG", C_RED);
			get_format(&begin, &end, &print->mbuff, print->args);
			//state = 1;
		}
		else
		{
			if (*end)
				++end;
			else
				break;
		}
	}
	ret = fill_buffer_static(&print->sbuff, begin);
	{
		write(1, print->sbuff.buffer, print->sbuff.buff_size - print->sbuff.remaining_size);
		print->ret += (int)(print->sbuff.buff_size - print->sbuff.remaining_size);
		begin = begin + print->sbuff.buff_size - print->sbuff.remaining_size;
		if (!ret)
		{
			init_buffer_static(&print->sbuff);
			fill_buffer_static(&print->sbuff, begin);
			write(1,print->sbuff.buffer, print->sbuff.buff_size - print->sbuff.remaining_size);
			print->ret += (int)(print->sbuff.buff_size - print->sbuff.remaining_size);
		}
	}
	return (1);
}

int ft_printf(const char *format, ...)
{
	ft_putendlcolor("START ft_printf", C_GREEN);
	t_print			print;
	va_list			args;

	if (!format || !init(&print, format))
		return (0);
	ft_putendlcolor(format, C_YELLOW);
	va_start(args, format);
	print.args = &args;
	ft_putendlcolor("Apres va_start", C_CYAN);
	if (!analyze_format(&print))
		return(0);
	va_end(*print.args);
	if (print.mbuff.increm > 1)
	{
		printf("FREEEEEEEEEE\n");
		free(&print.mbuff.buffer);
	}
	ft_putstrcolor("\nRETURN DE FIN: ", C_LBLUE);
	ft_putnbrcolor(print.ret, C_BLUE);
	write(1, "\n", 1);
	return (print.ret);
}
