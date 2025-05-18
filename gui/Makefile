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

NAME		=	zappy_gui

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CFLAGS  	=	-I src/Elems			\
				-I src/Graphical		\
				-I src/PlayerInterface	\
				-I src/World			\
				-I src/Comunicator		\
				-I src/Animation		\
				-I src/Players			\
				-I src/					\
				-I libs/				\

CPPFLAGS	=	-std=c++20 -W -Wall -Wextra -Werror $(CFLAGS) -g3

SRC_DIR		=	./src/
LIB_DIR		=	./libs/
TEST_DIR	=	./tests/

SRCS		=	$(shell find $(SRC_DIR) -name '*.cpp' && find $(LIB_DIR) -name '*.cpp')

OBJS		=	$(SRCS:.cpp=.o)

%.o: %.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@

all: $(NAME)
	@echo -e "$(GREEN)[✓] Zappy_gui"

$(NAME): $(OBJS)
	@$(CXX) -o $(NAME) $(OBJS) $(CPPFLAGS) $(LDFLAGS)
	@mv $(NAME) ..

debug: CPPFLAGS += -g3
debug: $(NAME)
	@echo -e "$(ORANGE)[✓] Debug Zappy_gui"

tests_run:
	@make -C $(TEST_DIR)
	@echo -e "$(PURPLE)[✓] tests_run Zappy_gui$(NC)"
	@gcovr --html --html-details -o $(TEST_DIR)cov.html
	@gcovr

clean:
	@$(RM) $(OBJS)
	@make clean -C $(TEST_DIR)
	@echo -e "$(RED)[✓] Clean Zappy_ai$(NC)"

fclean:
	@$(RM) $(OBJS)
	@$(RM) ../$(NAME)
	@make fclean -C $(TEST_DIR)
	@echo -e "$(RED)[✓] Fclean Zappy_gui$(NC)"

re: fclean all

.PHONY: all debug tests_run clean fclean re
