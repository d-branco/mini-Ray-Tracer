# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 21:04:23 by abessa-m          #+#    #+#              #
#    Updated: 2025/07/08 22:37:09 by abessa-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= miniRT
NAME-BONUS	:= miniRT_bonus
LIBFT		:= libft/libft.a
LIBFT_DIR	:= libft
##################################################################### Compiler #
CC			= cc
CFLAGS		+= -Wall -Wextra
CFLAGS		+= -Werror
########################################################### Intermidiate steps #
RM			:= rm -f
AR			:= ar rcs
########################################################## Objects and Headers #
INCLUDES	:= -I./include

SRCS		:=	\
	src/minirt.c															\
																			\
	src/utils/ft_free.c														\
	src/utils/ft_isspace.c													\
	src/utils/ft_malloc.c													\
	src/utils/ft_strcmp.c													\

OBJS		:= $(SRCS:.c=.o)
SRCS-BONUS	:=	\

OBJS-BONUS	:= $(SRCS-BONUS:.c=.o)
###################################################################### Targets #
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@\
	echo "$(GRAY)Compile flags:$(COR)	$(CC) $(CFLAGS)"				;	\
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	@\
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@								&&	\
	echo "$(GRAY)File compiled:$(COR)	$<"

$(LIBFT):
	@\
	make --silent --no-print-directory -C $(LIBFT_DIR)					&&	\
	echo "$(GRAY)Library built:$(COR)	$(LIBFT)"

libft : $(LIBFT)

bonus: $(NAME-BONUS)

$(NAME-BONUS): $(LIBFT) $(OBJS-BONUS)
	@\
	echo "$(GRAY)Compile flags:$(COR)	$(CC) $(CFLAGS)"				;	\
	$(CC) $(CFLAGS) $(OBJS-BONUS) $(LIBFT) -o $(NAME-BONUS)

debug:
	@\
	$(MAKE) --silent fclean												;	\
	$(MAKE) --silent all CFLAGS=\ -Wall\ -Wextra\ -D\ DEBUG=1			&&	\
	$(MAKE) --silent clean

clean:
	@\
	make --silent --no-print-directory -C $(LIBFT_DIR) clean			;	\
	$(RM) $(OBJS) $(OBJS-BONUS)											;	\
	rm -fr *.o *.gch *.exe 				 								;	\
	echo "$(GRAY)Files cleaned.$(COR)"

fclean: clean
	@\
	make --silent --no-print-directory -C $(LIBFT_DIR) fclean			&&	\
	echo "$(GRAY)Libft cleaned.$(COR)"									;	\
	$(RM) $(NAME) $(NAME-BONUS)											&&	\
	echo "$(GRAY)File fcleaned.$(COR)"

re: fclean all
	@echo "$(GRAY)redone$(COR)"

.PHONY: all clean fclean re
####################################################################### Colors #
COR		:= \033[0m# COlor Remove
PURPLE	:= \033[1;35m# purple
GRAY	:= \033[1;90m# gray
YELLOW	:= \033[1;93m# yellow
######################################################################### Test #
test:
	@\
	$(MAKE) --silent fclean												;	\
	$(MAKE) --silent all CFLAGS+=-D\ DEBUG=1\ -Wall\ -Wextra			&&	\
	$(MAKE) --silent clean												&&	\
	\
	echo "\
	$(COR)$(GRAY)========================================== $(NAME) START\
	$(COR)" && \
	\
	valgrind																\
		--track-fds=yes														\
		--show-error-list=yes												\
		--leak-check=full													\
		--show-leak-kinds=all												\
		--track-origins=yes													\
	\
		./miniRT														;	\
	\
	echo "\
	$(COR)$(GRAY)========================================== $(NAME) END\n\
	$(COR)RETURN VALUE: $$?"											&&	\
	\
		norminette src/ include/											\
		| grep -v OK 														\
		| grep -v 'Setting locale to en_US'								;	\
	echo -n "Error count: "												;	\
		norminette src/ include/ 											\
			| grep -v OK 													\
			| grep -v 'Setting locale to en_US'								\
			| grep -v Error!												\
		| wc -l

valgrind:
	@\
	valgrind																\
		--track-fds=yes														\
		--show-error-list=yes												\
		--leak-check=full													\
		--show-leak-kinds=all												\
		--track-origins=yes													\
	\
		./miniRT
