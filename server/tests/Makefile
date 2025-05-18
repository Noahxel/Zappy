##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile
##

NAME		=	unit_tests

CPPFLAGS	=	-W -Wall -Wextra -Werror -lm

CFLAGS		= 	-I../include/

LDFLAGS		=	--coverage -lcriterion

COVFLAGS	=	-lcriterion -lgcov

SRC_DIR		=	../src/

SRC_TESTS	=	$(SRC_DIR)data/game/init/init_game.c					\
				$(SRC_DIR)data/game/init/init_players.c					\
				$(SRC_DIR)data/game/init/init_teams.c					\
				$(SRC_DIR)data/game/init/init_freq.c					\
				$(SRC_DIR)tools/tools.c									\
				$(SRC_DIR)data/game/management/assignment.c				\
				$(SRC_DIR)data/game/management/incantation.c			\
				$(SRC_DIR)data/game/management/inventory.c				\
				$(SRC_DIR)data/game/management/map.c					\
				$(SRC_DIR)data/game/management/player.c					\
				$(SRC_DIR)data/game/management/egg.c					\
				$(SRC_DIR)data/game/management/time_info.c				\
				$(SRC_DIR)data/game/management/resources.c				\
				$(SRC_DIR)data/game/management/team.c					\
				$(SRC_DIR)data/network/management/client.c				\
				$(SRC_DIR)commands/commands_player/cmd_broadcast_text.c	\
				$(SRC_DIR)commands/commands_player/cmd_eject.c			\
				$(SRC_DIR)commands/commands_player/cmd_incantation.c	\
				$(SRC_DIR)commands/commands_player/cmd_look.c			\
				$(SRC_DIR)commands/commands_player/cmd_take_object.c	\
				$(SRC_DIR)commands/commands_player/cmd_fork.c			\
				$(SRC_DIR)commands/commands_player/cmd_inventory.c		\
				$(SRC_DIR)commands/commands_player/cmd_right.c			\
				$(SRC_DIR)commands/commands_player/cmd_connect_nbr.c	\
				$(SRC_DIR)commands/commands_player/cmd_forward.c		\
				$(SRC_DIR)commands/commands_player/cmd_left.c			\
				$(SRC_DIR)commands/commands_player/cmd_set_object.c		\
				$(SRC_DIR)commands/commands_gui/cmd_bct.c				\
				$(SRC_DIR)commands/commands_gui/cmd_mct.c				\
				$(SRC_DIR)commands/commands_gui/cmd_msz.c				\
				$(SRC_DIR)commands/commands_gui/cmd_pin.c				\
				$(SRC_DIR)commands/commands_gui/cmd_plv.c				\
				$(SRC_DIR)commands/commands_gui/cmd_ppo.c				\
				$(SRC_DIR)commands/commands_gui/cmd_sgt.c				\
				$(SRC_DIR)commands/commands_gui/cmd_sst.c				\
				$(SRC_DIR)commands/commands_gui/cmd_tna.c				\
				$(SRC_DIR)commands/commands_gui/cmd_pwa.c				\
				$(SRC_DIR)data/queue/queue_management.c					\

UT_FILES	=	tests_init.c			\
				tests_tools.c			\
				tests_player_commands.c	\
				tests_management.c		\
				tests_gui_commands.c	\

SRC_OBJS	=	$(SRC_TESTS:.c=.o)

UT_OBJS		=	$(UT_FILES:.c=.o)

all: $(NAME)

$(NAME):
	@$(CC) -c $(SRC_TESTS) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
	@$(CC) -c $(UT_FILES) $(CFLAGS) $(CPPFLAGS)
	@$(CC) -o $(NAME) *.o $(CFLAGS) $(CPPFLAGS) $(COVFLAGS)
	@./$(NAME)

clean:
	@$(RM) *.html
	@$(RM) *.css
	@$(RM) $(SRC_DIR)*.gcno
	@$(RM) $(SRC_DIR)*.gcda
	@$(RM) $(TEST_DIR)*.gcda
	@$(RM) $(TEST_DIR)*.gcno
	@$(RM) $(TEST_DIR)*.o
	@$(RM) $(UT_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all build_lib clean fclean re
