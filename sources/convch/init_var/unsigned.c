/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mo0ky <mo0ky@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 23:23:27 by mo0ky             #+#    #+#             */
/*   Updated: 2017/09/18 22:36:38 by mo0ky            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <stdio.h>

static char	*uitoa_base(char test[65], unsigned int value, int base, int *len)
{
	unsigned long	lvalue = (unsigned long)value;
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

static char	*uiltoa_base(char test[65], unsigned long value, int base, int *len)
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
	while (lvalue)
	{
		++(*len);
		--test;
		*test = hex[lvalue % base];	
		lvalue /= base;
	}
	return (test);
}

static char	*uilltoa_base(char test[65], unsigned long long value, int base, int *len)
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
	while (lvalue)
	{
		++(*len);
		--test;
		*test = hex[lvalue % base];	
		lvalue /= base;
	}
	return (test);
}

static unsigned long long get_nbr(int flag_mlen, va_list *args)
{
	/*
	if (flag_mlen < FLAG_MLEN_HH)
	{
		if (flag_mlen == FLAG_MLEN_NODEF)
			return((unsigned int)va_arg(*args, unsigned long long int));
		else if (flag_mlen == FLAG_MLEN_LL)
			return((unsigned long long int)va_arg(*args, unsigned long long int));
		else if (flag_mlen == FLAG_MLEN_L)
			return((unsigned long int)va_arg(*args, unsigned long long int));
		else
			return((unsigned short int)va_arg(*args, unsigned long long int));
	}
	else
	{
		if (flag_mlen == FLAG_MLEN_HH)
			return((unsigned char)va_arg(*args, unsigned long long int));
		else if (flag_mlen == FLAG_MLEN_J)
			return((uintmax_t)va_arg(*args, unsigned long long int));
		else
			return((size_t)va_arg(*args, unsigned long long int));
	}
	*/
	if (flag_mlen < FLAG_MLEN_L)
	{
		if (flag_mlen == FLAG_MLEN_NODEF)
			return((unsigned int)va_arg(*args, unsigned long long int));
		else if (flag_mlen == FLAG_MLEN_HH)
			return((unsigned char)va_arg(*args, unsigned long long int));
		else
			return((unsigned short int)va_arg(*args, unsigned long long int));
	}
	else
	{
		if (flag_mlen == FLAG_MLEN_L)
			return((unsigned long int)va_arg(*args, unsigned long long int));
		else if (flag_mlen == FLAG_MLEN_LL)
			return((unsigned long long int)va_arg(*args, unsigned long long int));
		else if (flag_mlen == FLAG_MLEN_Z)
			return((unsigned long long int)va_arg(*args, size_t));
		else
			return((unsigned long long int)va_arg(*args, uintmax_t));
	}
}

char	*init_var_unsigned(t_fmt *fmt, va_list *args, char nb[65], int base)
{
	fmt->type.ull = get_nbr(fmt->flag_mlen, args);
	//printf("nb:%lld\n", fmt->type.ull);
	//sleep(5);
	fmt->len = 0;

	if (fmt->flag_mlen < FLAG_MLEN_L)
	{
		if (fmt->flag_mlen == FLAG_MLEN_NODEF)
			return(uitoa_base(nb, (unsigned int)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_HH)
			return(uitoa_base(nb, (unsigned char)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_H)
			return(uitoa_base(nb, (unsigned short int)fmt->type.ull, base, &fmt->len));
	}
	else
	{
		if (fmt->flag_mlen == FLAG_MLEN_L)
			return(uiltoa_base(nb, (unsigned long)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_LL)
			return(uilltoa_base(nb, (unsigned long long)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_Z)
			return(uilltoa_base(nb, (unsigned long long)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_J)
			return(uilltoa_base(nb, (unsigned long long)fmt->type.ull, base, &fmt->len));
	}
	return (NULL);

/*
	if (fmt->flag_mlen < FLAG_MLEN_HH)
	{
		if (fmt->flag_mlen == FLAG_MLEN_NODEF)
			return(uitoa_base(nb, (unsigned int)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_LL)
			return(uilltoa_base(nb, (unsigned long long)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_L)
			return(uiltoa_base(nb, (unsigned long)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_H)
			return(uitoa_base(nb, (unsigned short int)fmt->type.ull, base, &fmt->len));
	}
	else
	{
		if (fmt->flag_mlen == FLAG_MLEN_HH)
			return(uitoa_base(nb, (unsigned char)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_J)
			return(uilltoa_base(nb, (unsigned long long)fmt->type.ull, base, &fmt->len));
		else if (fmt->flag_mlen == FLAG_MLEN_Z)
			return(uilltoa_base(nb, (unsigned long long)fmt->type.ull, base, &fmt->len));
	}
	*/
}
