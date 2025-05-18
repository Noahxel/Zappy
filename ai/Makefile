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

NAME		= 	zappy_ai

SRC_DIR		= 	./src/

TEST_DIR	= 	./tests/

all: $(NAME)
	@echo -e "$(GREEN)[✓] Zappy_ai$(NC)"

$(NAME):
	@cp $(SRC_DIR)main.py $@
	@chmod +x $@
	@mv $(NAME) ..

debug: $(NAME)
	@echo -e "$(ORANGE)[✓] Debug Zappy_ai"

tests_run:
	@make -C $(TEST_DIR)
	@echo -e "$(PURPLE)[✓] tests_run Zappy_ai$(NC)"

clean:
	@make clean -C $(TEST_DIR)
	@find . -name "__pycache__" -exec rm -r {} +
	@echo -e "$(RED)[✓] Clean Zappy_ai$(NC)"

fclean:
	@make clean -C $(TEST_DIR)
	@find . -name "__pycache__" -exec rm -r {} +
	@$(RM) ../$(NAME)
	@echo -e "$(RED)[✓] Fclean Zappy_ai$(NC)"

.PHONY: all debug tests_run clean fclean
