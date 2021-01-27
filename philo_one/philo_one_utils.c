#include "philo_one.h"

void			ft_putnbr_ull(unsigned long long n)
{
	unsigned long long		div;
	char					mod;

	div = n / 10;
	mod = n % 10;
	if (div)
		ft_putnbr_ull(div);
	mod += 48;
	write(1, &mod, 1);
}


