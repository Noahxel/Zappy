##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile
##

GREEN		=	\033[1;32m
PURPLE		=	\033[1;35m
RED			=	\033[1;31m
ORANGE		=	\033[38;5;209;1m
NC			=	\033[0m

NAME		=	zappy_server

CPPFLAGS	=	-W -Wall -Wextra -Werror -lm

CFLAGS		= 	-I./include/

SRC_DIR		=	./src/

TEST_DIR	=	./tests/

SRCS 		:= 	$(shell find $(SRC_DIR) -name '*.c')

OBJS		=	$(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

all: $(NAME)
	@echo -e "$(GREEN)[✓] Zappy_server"

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(CPPFLAGS)
	@mv $(NAME) ..

debug:	CPPFLAGS += -g3
debug: $(NAME)
	@echo -e "$(ORANGE)[✓] Debug Zappy_server$(NC)"

tests_run:
	@make -C $(TEST_DIR)
	@echo -e "$(PURPLE)[✓] tests_run Zappy_server$(NC)"
	@gcovr --html --html-details -o $(TEST_DIR)cov.html
	@gcovr

clean:
	@$(RM) $(OBJS)
	@make clean -C $(TEST_DIR)
	@echo -e "$(RED)[✓] Clean Zappy_server$(NC)"

fclean:
	@$(RM) $(OBJS)
	@$(RM) ../$(NAME)
	@make fclean -C $(TEST_DIR)
	@echo -e "$(RED)[✓] Fclean Zappy_server$(NC)"

re: fclean all

.PHONY: all debug tests_run clean fclean re
