# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbernard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 16:22:44 by mbernard          #+#    #+#              #
#    Updated: 2024/03/25 12:01:19 by mbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g
MKDIR = mkdir -p
RMDIR = rm -rf
#colors
_GREEN=\033[0;32m
_BLUE=\033[0;34m
_YELLOW=\033[0;33m
_END=\033[0m
# ---------------------------------- Sources --------------------------------- #

SRCS = philo.c	
SRCS_WITH_DIR = $(addprefix ${SRCS_DIR}, ${SRCS}))

# ---------------------------------- Repertories ----------------------------- #
HEADER_DIR = header/
OBJS_DIR = .objs/
OBJS_BONUS_DIR = .objs_bonus/
SRCS_DIR = src/
BONUS_DIR = bonus/
HEADER = $(addprefix ${HEADER_DIR}, philo.h)
BONUS_HEADER = $(addprefix ${HEADER_DIR}, pipex_bonus.h)
OBJS = $(addprefix ${OBJS_DIR}, $(addsuffix .o, ${SRCS}))
OBJS_BONUS = $(addprefix ${OBJS_DIR}, $(addsuffix .o, ${BONUS}))
DEPS = ${OBJS:.o=.d}

# ---------------------------------- Lib Gestion ----------------------------- #
LIBFT_DIR = Libft/
LIBFT = $(addprefix ${LIBFT_DIR}, libft.a)
INCLUDES = -I ${LIBFT_DIR} -I ${HEADER_DIR} 
# ---------------------------------- Compilation ----------------------------- #
all: ${NAME} ${OBJS} | ${OBJS_DIR} clean_bonus Makefile
 
${NAME}: ${OBJS} ${LIBFT} Makefile
	${CC} ${CFLAGS} ${OBJS}  ${INCLUDES} ${LIBFT} -o $@
  
${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${HEADER} Makefile | ${OBJS_DIR}
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

bonus: clean 
	@echo "${_YELLOW}Make bonus !${_END}"
	@$(MAKE) SRCS="$(BONUS)"  SRCS_DIR="$(BONUS_DIR)" \
	OBJS_DIR="${OBJS_BONUS_DIR}" OBJS_BONUS_DIR="${OBJS_DIR}"
	@echo "${_YELLOW}Bonus done !${_END}"

${LIBFT}: FORCE
	@echo "${_GREEN}Building Libft${_END}"
	@$(MAKE) -s -C ${LIBFT_DIR}
	@echo "${_GREEN}Libft done${_END}"

-include ${DEPS}
# ---------------------------------- Create Repertory ---------------------- #
${OBJS_DIR}:
			${MKDIR} ${OBJS_DIR}

## ---------------------------------- Clean ----------------------------------- #
clean_bonus:
	${RMDIR} ${OBJS_BONUS_DIR}

clean:
	${RMDIR} ${OBJS_DIR}

fclean: clean
	${RM} ${NAME}

clean_lib: clean
	@echo "${_BLUE}Cleaning Libft"
	@${MAKE} -s clean -C $(LIBFT_DIR)
	@echo "Libft cleaned${_END}"

fclean_lib: fclean clean_lib
	${RM} ${LIBFT}

re:    fclean_lib
	${MAKE} ${NAME}

re_pipex_only: fclean
	${MAKE} ${NAME}

FORCE:

# ---------------------------------- Phony ----------------------------------- #
.PHONY: all bonus debug clean clean_bonus clean_lib fclean fclean_lib re re_pipex_only FORCE
