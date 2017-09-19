/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 20:48:36 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/16 00:08:36 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
//MODIF A FAIRE sur WHILE do filler n
void noconvert(t_fmt *fmt, t_buffer_static *sbuff, va_list *args, int *ret)
{
	(void)args;
	int len;

	len = 1;
	if (fmt->width > -1)
	{
		if (fmt->flag_char[2])
			*ret += do_filler(sbuff, "%", 1);
		while (len < fmt->width)
		{
			if (fmt->flag_char[1])
				*ret += do_filler(sbuff, "0", 1);
			else
				*ret += do_filler(sbuff, " ", 1);
			len++;
		}
		if (!fmt->flag_char[2])
			*ret += do_filler(sbuff, "%", 1);
	}
	else
		*ret += do_filler(sbuff, "%", 1);
}