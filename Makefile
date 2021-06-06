SRCS	=	server.c

OBJS	=	$(SRCS:.c=.o)

CSRCS	=	client.c

COBJS	=	$(CSRCS:.c=.o)

NAME	=	server

CNAME	=	client

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

all:		$(NAME) $(CNAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS)  -o $@ $^

$(CNAME):	$(COBJS)
			$(CC) $(CFLAGS)  -o $@ $^

%.o:		%.c header.h
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS) $(COBJS)

fclean:		clean
			$(RM) $(NAME) $(CNAME)

re:			fclean all

.PHONY:		all clean fclean re