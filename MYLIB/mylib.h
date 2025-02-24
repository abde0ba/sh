/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darkab <darkab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:45:48 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/13 21:15:10 by darkab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYLIB_H
# define MYLIB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

///////////////// HEAP_CLEANER /////////////////

# define TRUE 1

typedef struct s_allocate
{
	void				*block;
	struct s_allocate	*next;
}						t_allocate;

void	cleanup(t_allocate **collec);
void	*ft_calloc(size_t count, size_t size);
void	*allocate(t_allocate **collec, size_t count, size_t size);

///////////////// LIBFT PROTOTYPES /////////////////

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(t_allocate **alloc, const char *s1);

char	*ft_substr(t_allocate **alloc, char const *s, unsigned int start,
			size_t len);
char	*ft_strjoin(t_allocate **alloc, char const *s1, char const *s2);
char	*ft_strtrim(t_allocate **alloc, char const *s1, char const *set);
char	**ft_split(t_allocate **alloc, char const *s, char c);
char	*ft_itoa(t_allocate **alloc, int n);
char	*ft_strmapi(t_allocate **alloc, char const *s,
			char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strlwr(char *str);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

///////////////// PRINTF PROTOTYPES /////////////////

# define SPECIFIERS	"cspdiuxX%"

int		print_char(char c);
int		print_num(int num);
int		print_string(char *str);
int		print_address(void *ptr);
int		print_unum(unsigned int num);
int		print_hex(unsigned int num, char set);
int		ft_printf(const char *format, ...);

///////////////// GNL PROTOTYPES /////////////////

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define END '\0'
# define NLN '\n'

size_t	ft_search(char *s);
size_t	strlen_set(char *s, char set);
char	*strdup_set(char *str, char set);
char	*str_join(char *save, char *load);
char	*get_next_line(t_allocate **alloc, int fd);

#endif
