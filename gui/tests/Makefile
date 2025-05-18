##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile
##

NAME		=	unit_tests

# CFLAGS

CPPFLAGS	=	-std=c++20 -W -Wall -Wextra -Werror

LDFLAGS		=	--coverage -lcriterion

COVFLAGS	=	-lcriterion -lgcov

SRC_DIR		=	../src/

SRC_TESTS	=	$(SRC_DIR)CheckArgs.cpp		\

UT_FILES	=	TestsCheckArgs.cpp			\

SRC_OBJS	=	$(SRC_TESTS:.cpp=.o)

UT_OBJS		=	$(UT_FILES:.cpp=.o)

all: $(NAME)

$(NAME) :
	@g++ -c $(SRC_TESTS) $(CPPFLAGS) $(CFLAGS) $(LFLAGS) $(LDFLAGS)
	@g++ -c $(UT_FILES) $(CPPFLAGS) $(CFLAGS) $(LFLAGS)
	@g++ -o $(NAME) *.o $(CPPFLAGS) $(CFLAGS) $(LFLAGS) $(COVFLAGS)
	@./$(NAME)


clean:
	@$(RM) *.html
	@$(RM) *.css
	@$(RM) $(SRC_DIR)*.gcno
	@$(RM) $(SRC_DIR)*.gcda
	@$(RM) $(TEST_DIR)*.gcda
	@$(RM) $(TEST_DIR)*.gcno
	@$(RM) $(TEST_DIR)*.o
	@$(RM) $(TESTS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
