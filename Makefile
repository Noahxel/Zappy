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

SUBDIRS	= server gui ai

.PHONY: all $(SUBDIRS)

all: $(SUBDIRS)
	@echo -e "$(GREEN)[✓] Build Zappy Successful!$(NC)"

$(SUBDIRS):
	@make --no-print-directory -C $@

debug:
	@for dir in $(SUBDIRS); do \
		make debug --no-print-directory -C $$dir; \
	done
	@echo -e "$(ORANGE)[✓] Build Debug Zappy Successful!$(NC)"

tests_run: fclean all
	@for dir in $(SUBDIRS); do \
		make tests_run --no-print-directory -C $$dir; \
	done
	@echo -e "$(PURPLE)[✓] Tests Zappy Successful!$(NC)"

clean:
	@for dir in $(SUBDIRS); do \
		make clean --no-print-directory -C $$dir; \
	done
	@echo -e "$(RED)[✓] Clean Zappy Successful!$(NC)"

fclean:
	@for dir in $(SUBDIRS); do \
		make fclean --no-print-directory -C $$dir; \
	done
	@echo -e "$(RED)[✓] Fclean Zappy Successful!$(NC)"

re: fclean all
