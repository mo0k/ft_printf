/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 23:23:27 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 22:36:27 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>
static char	*itoa_base(char test[65], int value, int base, int *len)
{
	long	lvalue = (long)value;
	static char	hex[] = "0123456789abcdef";

	test += 64;
	*test = '\0';
	if (value == 0)
	{
		*len = 1;
		--test;
		*test = '0';
		return (test);
	}
	if (value < 0)
		lvalue *= -1;

	while (lvalue)
	{
		++(*len);
		--test;
		*test = hex[lvalue % base];	
		//printf("char:%c\n", *test);
		lvalue /= base;
	}
	//printf("final:%s\n", test);
	return (test);
	return (test);
}

static char	*iltoa_base(char test[65], long value, int base, int *len)
{
	long long	lvalue = (long long)value;
	static char	hex[] = "0123456789abcdef";

	test += 64;
	*test = '\0';
	if (value == 0)
	{
		*len = 1;
		--test;
		*test = '0';
		return (test);
	}
	if (value < 0)
		lvalue *= -1;

	while (lvalue)
	{
		++(*len);
		--test;
		*test = hex[lvalue % base];	
		lvalue /= base;
	}
	return (test);
}

static char	*illtoa_base(char test[65], long long value, int base, int *len)
{
	unsigned long long	lvalue = (unsigned long long)value;
	static char	hex[] = "0123456789abcdef";

	test += 64;
	*test = '\0';
	if (value == 0)
	{
		*len = 1;
		--test;
		*test = '0';
		return (test);
	}
	if (value < 0)
		lvalue *= -1;
	while (lvalue)
	{
		++(*len);
		--test;
		*test = hex[lvalue % base];	
		lvalue /= base;
	}
	return (test);
}

static long long get_nbr(int flag_mlen, va_list *args)
{
	if (flag_mlen < FLAG_MLEN_L)
	{
		if (flag_mlen == FLAG_MLEN_NODEF)
			return((int)va_arg(*args, long long int));
		else if (flag_mlen == FLAG_MLEN_HH)
			return((signed char)va_arg(*args, long long int));
		else
			return((short int)va_arg(*args, long long int));
	}
	else
	{
		if (flag_mlen == FLAG_MLEN_L)
			return((long int)va_arg(*args, long long int));
		else if (flag_mlen == FLAG_MLEN_LL)
			return((long long int)va_arg(*args, long long int));
		else if (flag_mlen == FLAG_MLEN_Z)
			return((long long int)va_arg(*args, size_t));
		else
			return((long long int)va_arg(*args, intmax_t));
	}
}
char	*init_var_signed(t_fmt *fmt, va_list *args, char nb[65], int base)
{
	fmt->type.ll = get_nbr(fmt->flag_mlen, args);
	//printf("nb:%lld\n", fmt->type.ll);
	fmt->len = 0;

	if (fmt->flag_mlen < FLAG_MLEN_L)
	{
		if (fmt->flag_mlen == FLAG_MLEN_NODEF)
			return(itoa_base(nb, (int)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_HH)
			return(itoa_base(nb, (signed char)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_H)
			return(itoa_base(nb, (short int)fmt->type.ll, base, &fmt->len));
	}
	else
	{
		if (fmt->flag_mlen == FLAG_MLEN_L)
			return(iltoa_base(nb, (long)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_LL)
			return(illtoa_base(nb, (long long)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_Z)
			return(illtoa_base(nb, (long long)fmt->type.ll, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_J)
			return(illtoa_base(nb, (long long)fmt->type.ll, base, &fmt->len));
	}
	return (NULL);
}