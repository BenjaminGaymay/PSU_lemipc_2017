/*
** my_getnbr.c for my_getnbr in /home/benjamin.g/delivery/CPool_Day04
**
** Made by Benjamin GAYMAY
** Login   <benjamin.g@epitech.net>
**
** Started on  Fri Oct  7 14:23:35 2016 Benjamin GAYMAY
** Last update Fri Feb 17 22:40:42 2017 Benjamin GAYMAY
*/

int	my_getnbr(char *s)
{
  int	nb;
  int	neg;
  int	i;

  nb = 0;
  i = -1;
  neg = 1;
  while (s[++i] == '-')
    neg *= -1;
  while (s[i] >= '0' && s[i] <= '9')
    nb = nb * 10 + s[i++] - '0';
  return (nb * neg);
}
