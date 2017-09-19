/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 23:22:05 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 22:49:25 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static enum e_flag_mlen	is_flag_mlen(char *ptr)
{
	if (ptr[0] == 'l' && ptr[1] == 'l')
		return (FLAG_MLEN_LL);
	else if (*ptr == 'l')
		return (FLAG_MLEN_L);
	else if (ptr[0] == 'h' && ptr[1] == 'h')
		return (FLAG_MLEN_HH);
	else if (*ptr == 'h')
		return (FLAG_MLEN_H);
	else if (*ptr == 'z')
		return (FLAG_MLEN_Z);
	else if (*ptr == 'j')
		return (FLAG_MLEN_J);
	return (FLAG_MLEN_NODEF);
}

static void 		set_flag_char(int flag_char[5], char *ptr)
{
	int		i;

	if (!flag_char || !ptr)
		return ;
	i = 0;
	while (FLAG_CHAR[i])
	{
		if (*ptr == FLAG_CHAR[i])
			flag_char[i] = TRUE;
		i++;
	}
}

static void 		set_width(int *width, char **aptr)
{
	char			c;
	char			*start;

	if (!width || !aptr || !*aptr)
		return ;
	start = *aptr;
	while (**aptr && ft_isdigit(**aptr))
		++(*aptr);
	if (start < *aptr)
	{
		c = **aptr;
		**aptr = 0;
		*width = ft_atoi(start);
		if (*width < 0)
			*width = 0;
		**aptr = c;
		--(*aptr);
	}
}

static void 		set_precision(int *precision, char **aptr)
{
	char			c;
	char			*start;

	if (!precision || !aptr || !*aptr)
		return ;
	if (*(*aptr + 1) != '.' && !ft_strchr(FLAG_CONVERT, *(*aptr + 1)))
		++(*aptr);
	start = *aptr;
	while (**aptr && ft_isdigit(**aptr))
		++(*aptr);
	if (start < *aptr)
	{
		c = **aptr;
		**aptr = 0;
		*precision = ft_atoi(start);
		if (*precision < 0)
			*precision = 0;
		**aptr = c;
		--(*aptr);
	}
	else
		*precision = 0;
}

int			parse_fmt(t_fmt *fmt, char *fmt_string)
{
	//ft_putendlcolor("DEBUG start merge_fmt ____________________________", C_RED);
	//printf("merge_fmt start: chaine:%s\n", fmt_string);
	//enum e_flag_mlen	flag_mlen;
	//int state;
	//int i;

	//(void)flag_mlen;
	//state = 0;
	//i = -1;
	if (!fmt_string)
		return (0);
	++fmt_string;
	unsigned int temp = 0;
	while (*fmt_string)
	{
		//printf("%p\n", fmt_string);
		//ft_putstr("*fmt_string='");
		//ft_putcharcolor(*fmt_string, C_LRED);
		//ft_putendl("'");
		//if (!state && ft_strchr(fmt->flag_char.key, *fmt_string))
		if (ft_strchr(FLAG_CHAR, *fmt_string))
		{
			//ft_putendlcolor("Go set_flag_char", C_LRED);
			//printf("flag char:%c\n", *fmt_string);
			set_flag_char(fmt->flag_char, fmt_string);
		}
		else if (*fmt_string == '.')// && (state = 1))
		{
			//ft_putendlcolor("Go set_precision", C_LRED);
			set_precision(&fmt->precision, &fmt_string);
		}
		else if (ft_isdigit(*fmt_string))// && (state = 1))
		{
			//ft_putendlcolor("Go set_width", C_LRED);
			set_width(&fmt->width, &fmt_string);
		}
		else if (*fmt_string && !*(fmt_string + 1))
		{
			//ft_putendlcolor("Go set_convch", C_LRED);
			fmt->convch = *fmt_string;
		}
		//else if ((fmt->flag_mlen = is_flag_mlen(fmt_string)) != FLAG_MLEN_NODEF)
		else if ((temp = is_flag_mlen(fmt_string)) > fmt->flag_mlen)
		{
			fmt->flag_mlen = temp;
			//printf("flag_mlen:%d\n", temp);
			if (fmt->flag_mlen == FLAG_MLEN_LL || fmt->flag_mlen == FLAG_MLEN_HH)
				++fmt_string;
		}
		++fmt_string;
	}
	//ft_putendlcolor("DEBUG end merge_fmt _______________________________", C_RED);
	return (1);
}
