cc:= CC
CCFLAGS:= -Wall -Werror -Wextra

FILES:=	parsing/assign_inputs.c \
		parsing/ft_split.c \
		parsing/parsing.c \
		parsing/utils.c \
		assign_philos.c \
		monitor.c \
		routine.c \
		main.c

OFILES:= $(FILES:.c=.o)
HEADER:= philo.h
NAME:= philo

BONUS:=
OBONUS:=
BHEADER:=
BNAME:=

all: $(NAME)

%.o: %.c $(HEADER) $(BHEADER)
	$(CC) $(CCFLAGS) -c $< -o $@

$(NAME): $(OFILES)
	$(CC) $(CCFLAGS) $(OFILES) -o $(NAME) -pthread

bonus: $(OBONUS)
	$(CC) $(CCFLAGS) $(OBONUS) -o $(BNAME)

clean:
	rm -f $(OFILES) $(OBONUS)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: all clean fclean re