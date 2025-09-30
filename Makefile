cc:= CC
CCFLAGS:= -Wall -Werror -Wextra

FILES:=	assign_inputs.c \
		ft_split.c \
		parsing.c \
		utils.c \
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
	$(CC) $(CCFLAGS) $(OFILES) -o $(NAME)

bonus: $(OBONUS)
	$(CC) $(CCFLAGS) $(OBONUS) -o $(BNAME)

clean:
	rm -f $(OFILES) $(OBONUS)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

.PHONY: all clean fclean re