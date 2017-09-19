/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:28:45 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 17:03:39 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int add_prefix(t_buffer_static *sbuff, char convch, int *len)
{
	//printf("start add_prefix\n");
	(void)len;
	char c[2];
	/*if (!ptr || !*ptr || !len)
		return ;
	--*ptr;
	**ptr = convch;
	--*ptr;
	**ptr = '0';*/
	*len += 2;
	c[0] = '0';
	c[1] = convch;
	return (do_filler(sbuff, c, 2));
}

static int func(t_fmt *fmt, t_buffer_static *sbuff, char *ptr, int *nbrlen)
{
	//int ret;
	//printf("passage 2\n");
	if (fmt->flag_char[0] && *ptr != '0')
		add_prefix(sbuff, fmt->convch, nbrlen);
	//ret = do_filler_n(sbuff, "0", diff);
	return (1);
}
static int func2(t_fmt *fmt, char *ptr, int *diff)
{
	//int ret;
	//printf("passage 2\n");
	if (!fmt->flag_char[2] && fmt->flag_char[0] && *ptr != '0')
		*diff = (*diff -2  < 0) ? 0 : *diff - 2;
	//ret = do_filler_n(sbuff, "0", diff);
	return (1);
}
static char *ft_strtoupper(char *str)
{
	int i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
	return (str);
}
void convert_hexa(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	int nbrlen;
	char test[65];
	char *ptr;
	int diff;
	int prefix;

	prefix = 0;
	ptr = init_var_unsigned(fmt, args, test, 16);
	if (fmt->convch == 'X')
		ptr = ft_strtoupper(ptr);
	nbrlen = fmt->len;
	if (fmt->flag_char[4])
		do_space(sbuff, fmt->width, &nbrlen, ret);
	if (fmt->precision == -1 && fmt->width == -1)
	{
		//printf("pasage 1\n");
		if (fmt->flag_char[0] && *ptr != '0')
			add_prefix(sbuff, fmt->convch, &nbrlen);
		*ret += do_filler(sbuff, ptr, fmt->len);
		return ;//(more_speed1(fmt, sbuff, ptr, ret));
	}
	if (fmt->flag_char[2])
	{
		if (fmt->flag_char[0] && *ptr != '0' && (prefix = 1))
			add_prefix(sbuff, fmt->convch, &nbrlen);
		//*ret = do_preci_and_fill_spec2(fmt, sbuff, ptr, nbrlen);
		*ret = do_preci_and_fill_spec(fmt, sbuff, ptr);
	}
	/*if (fmt->width > fmt->precision)
		if ((diff = fmt->width - fix_count_unsigned(fmt, nbrlen)) >= 0)
			*ret += (fmt->flag_char[1] && fmt->precision == -1) ?
											do_filler_n(sbuff, "0", diff) :
											do_filler_n(sbuff, " ", diff);*/
	int temp;
	if (fmt->width > fmt->precision)
		//printf("width:%d\n", fmt->width);
		if ((diff = fmt->width - (temp = fix_count_unsigned1(fmt, nbrlen, ptr))) >= 0)
		{
			//printf("diff:%d\tresult fix counter:%d\n", diff, temp);
			*ret += (func2(fmt, ptr, &diff) && fmt->flag_char[1] && fmt->precision == -1 &&
					!prefix && (prefix = 1) && func(fmt, sbuff, ptr, &nbrlen)) ?
								do_filler_n(sbuff, "0", diff):
								do_filler_n(sbuff, " ", diff);//ici errur
		}

	if (!fmt->flag_char[2])
	{
		//printf("par la=>diff:%d\n", diff);
		if (!prefix && fmt->flag_char[0] && *ptr != '0')
		{
			//printf("mais pas par la\n");
			add_prefix(sbuff, fmt->convch, &nbrlen);
		}
		//*ret = do_preci_and_fill_spec2(fmt, sbuff, ptr, nbrlen);
		*ret = do_preci_and_fill_spec(fmt, sbuff, ptr);
	}
}
