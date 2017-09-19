/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:35:29 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 23:41:23 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void convert_char(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	(void)args;
	int len;
	char test;

	len = 1;
	test = va_arg(*args, int);
	//printf("test:%d\n", test);
	if (test < 0)
	{
		*ret = -1;
		//printf("par la ret -1\n");
		return ;
	}
	//printf("char:'%c' => %d\n", test, test);
	if (fmt->width > -1)
	{
		if (fmt->flag_char[2])// && fmt->type.c >= 0)
			ret += do_filler(sbuff, &test, 1);
		if (len < fmt->width)
			ret += fmt->flag_char[1] ?
				do_filler_n(sbuff, "0", fmt->width - len) :
				do_filler_n(sbuff, " ", fmt->width - len);
		if (!fmt->flag_char[2])// && fmt->type.c >= 0)
			ret += do_filler(sbuff, &test, 1);
	}
	else// if (fmt->type.c >= 0)
		ret += do_filler(sbuff, &test, 1);
}
