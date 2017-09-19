/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 17:07:12 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/19 18:10:49 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

static int	is_flag_mlen(char *ptr)
{
	//if (!ft_strncmp(ptr, "ll", 2) || !ft_strncmp(ptr, "hh", 2))
	if ((ptr[0] == 'l' && ptr[1] == 'l') || (ptr[0] == 'h' && ptr[1] == 'h'))
	{
		//printf("return FLAG_MLEN_LL => %d\n", FLAG_MLEN_LL);
		return (2);
	}
	else if (ft_strchr("lhzj", *ptr))
		return (1);
	return (0);
}
static int		check_format(char **aptr)
{
	int		state;
	int		ret;
	char	*ptr;

	state = 0;
	while (**aptr)
	{
		//sleep(2);
		//ft_putstr("**end='");
		//ft_putcharcolor(**aptr, C_LMAGENTA);
		//ft_putendl("'");
		if (ft_strchr(FLAG_CHAR, **aptr))
		{
			//printf("is flag char\n");
			++(*aptr);
		}
		else if ((ft_isdigit(**aptr) || **aptr == '.')) //&& (state = 1))
		{
			//printf("ft_isdigit || '.'\n");
			++(*aptr);
		}
		else if ((ptr = ft_strchr(FLAG_CONVERT, **aptr)))// && (state = 1))
		{
			//printf("break in strchr(FLAG_CONVERT)\n");
			++(*aptr);
			return (1);
		}
		else if ((ret = is_flag_mlen(*aptr)))// && (state = 1))
		{
			*aptr += ret;
		}
		else
			return (0);
	}
	return (0);
}

static int		get_format(char **begin, t_print *print)
{
	//ft_putendlcolor("Begin get_value()", C_CYAN);
	//sleep(2);
	char	tmp[BUFF_SIZE_TEMP];
	char	*end;
	int 	diff;

	if (!begin || !*begin)
		return (0);
	end = *begin;
	//ft_putendlcolor(*begin, C_YELLOW);
	++end;
	if (!*end)
	{
		*begin = end;
		//ft_putendlcolor("return (0)", C_RED);
		return (0);
	}
	//ft_putendlcolor("DEBUG start check_format ____________________________", C_MAGENTA);
	//sleep(2);
	if (!check_format(&end))
	{
		*begin = end;
		return (0);
	}
	//ft_putendlcolor("DEBUG end check_format _______________________________", C_MAGENTA);
	//printf("ecart:%ld, *end:%d, char:'%c'\n",end - *begin, *end, *end);
	//sleep(2);

	diff = end - *begin;
	if (diff > BUFF_SIZE_TEMP)
	{
		*begin = end;
		return (0);
	}
	/*
	if (!*end)
	{
		//ft_putstr("strcpy\n");
		ft_strcpy(tmp, *begin);
	}
	else
	{
		//ft_putstr("strncpy\n");
		//printf("begin:%s, ecart:%ld\n", *begin,  end - *begin);
		ft_strncpy(tmp, *begin, end - *begin);
		tmp[end - *begin] = 0;
	}
	*/
	ft_strncpy(tmp, *begin, diff);
		tmp[diff] = 0;
	//ft_putendlcolor(tmp, C_GREEN);
	//do_format(tmp, &print->mbuff, &print->args, print->convfunc);
//changer avec size
	//do_format(tmp, print);
	if (do_fmt(tmp, print) == -1)
	{
		*begin = end + 1;
		return (-1);
	}
	*begin = end;
	//printf("begin:%p\nend:%p\nbuffer:%s\n", *begin, end, print->mbuff.buffer);
	return (1);
}

static int	analyze_format(t_print *print)//, const char *format)
{
	char	*ptr;
	char	*temp;
	//int state;

	//state = 1;
	ptr = (char *)print->format;
	while (*ptr)
	{
		//ft_putcharcolor(*ptr, C_MAGENTA);
		//sleep(2);
		//printf("(%p)\n", ptr);
		//sleep(1);
		//state = 0;
		//if (print->sbuff.remaining_size == 0)
		//{
		//	write(1, print->sbuff.buffer, BUFF_SIZE_INIT);
		//	print->ret += BUFF_SIZE_INIT;
		//	init_buffer_static(&print->sbuff);
		//}
		if (*ptr == '%' && *(ptr + 1) == '%')
		{
			print->ret += do_filler(&print->sbuff, "%", 1);
			ptr += 2;
		}
		/*else if (*ptr == '%' && ft_strchr(FLAG_CONVERT, *(ptr + 1)))
		{
			t_fmt fmt;

			init_fmt_spec(&fmt, *(ptr + 1));
			do_convch(&fmt, print);
			ptr += 2;
		}*/
		else if (*ptr == '%')
		{
			if (get_format(&ptr, print) == -1)
			{
				//printf("GET_FORMAT - par la return -1\n");
				return (0);
			}
		}
		else if (*ptr == '{')
		{
			if (!(temp = add_color(ptr + 1, &print->sbuff)))
			{
				print->ret += do_filler(&print->sbuff, ptr, 1);
				if (*ptr)
					++ptr;
			}
			else
				ptr = temp;
		}
		else
		{
			if (*ptr)
			{
				print->ret += do_filler(&print->sbuff, ptr, 1);
				++ptr;
			}
			else
				break;
		}
		//ptr++;
	}
	write(1, print->sbuff.buffer, print->sbuff.used_size);
	print->ret += print->sbuff.used_size;
	return (1);
}

int ft_printf(const char *format, ...)
{
	//ft_putendlcolor("START ft_printf", C_GREEN);
	t_print			print;
	//va_list			args;

	if (!format || !init(&print, format))
		return (-1);
	//ft_putendlcolor(format, C_YELLOW);
	va_start(print.args, format);
	//print.args = &args;
	//ft_putendlcolor("Apres va_start", C_CYAN);
	if (!analyze_format(&print))
		return(-1);
	va_end(print.args);
	//if (print.mbuff.increm > 1)
	//{
		//printf("FREEEEEEEEEE\n");
	//ft_memdel((void**)&print.mbuff.buffer);	
	//}
	//ft_putstrcolor("RETURN DE FIN: ", C_LBLUE);
	//ft_putnbrcolor(print.ret, C_BLUE);
	//write(1, "\n", 1);
	//printf("test 1\n");
	return (print.ret);
}
