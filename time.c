#include "Philosophers.h"

size_t	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	delay(int ms)
{
	usleep(ms * 1000);
}
