/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 23:18:38 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/15 23:19:27 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		init_fmt(t_fmt *fmt)
{
	if (!fmt)
		return (0);
	fmt->width = -1;
	fmt->precision = -1;
	//init_flag_char(&fmt->flag_char);
	fmt->flag_mlen = FLAG_MLEN_NODEF;
	fmt->convch = 0;
	fmt->len = 0;
	fmt->flag_char[0] = 0;
	fmt->flag_char[1] = 0;
	fmt->flag_char[2] = 0;
	fmt->flag_char[3] = 0;
	fmt->flag_char[4] = 0;
	return (1);
}

int		init_fmt_spec(t_fmt *fmt, char convch)
{
	if (!fmt)
		return (0);
	fmt->width = -1;
	fmt->precision = -1;
	//init_flag_char(&fmt->flag_char);
	fmt->flag_mlen = FLAG_MLEN_NODEF;
	fmt->convch = convch;
	fmt->len = 0;
	fmt->flag_char[0] = 0;
	fmt->flag_char[1] = 0;
	fmt->flag_char[2] = 0;
	fmt->flag_char[3] = 0;
	fmt->flag_char[4] = 0;
	return (1);
}