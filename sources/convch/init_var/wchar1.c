/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 00:00:40 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/19 16:29:51 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	fill_wchar(unsigned char *ret, wchar_t c, int len)
{
	if (len == 1)
	{
		ret[0] = c;
		ret[1] = 0;
	}
	else if (len == 2)
	{
		ret[0] = (((c & 0x07c0) >> 6) + 0xC0);
		ret[1] = (((c & 0x003F)) + 0x80);
		ret[2] = 0;
	}
	else if (len == 3)
	{
		ret[0] = (((c & 0xF000) >> 12) + 0xE0);
		ret[1] = (((c & 0x0FC0) >> 6) + 0x80);
		ret[2] = (((c & 0x003F)) + 0x80);
		ret[3] = 0;
	}
	else if (len == 4)
	{
		ret[0] = (((c & 0x1C0000) >> 18) + 0xF0);
		ret[1] = (((c & 0x03F000) >> 12) + 0x80);
		ret[2] = (((c & 0x0FC0) >> 6) + 0x80);
		ret[3] = (((c & 0x003F)) + 0x80);
		ret[4] = 0;
	}
}

int init_wchar(unsigned char *ret, wchar_t c, int *len)
{
	if (c >= 0 && c < 0x10FFFF)
	{
		if (c <= 127)
			*len = 1;
		else if (c < 0x07FF)
			*len = 2;
		else if (c < 0xFFFF)
			*len = 3;
		else
			*len = 4;
		fill_wchar(ret, c, *len);
		return (1);
		//printf("result:%s\n", c);
	}
	else
		return (0);
}