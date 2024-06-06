# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 16:22:44 by mbernard          #+#    #+#              #
#    Updated: 2024/03/25 12:01:19 by mbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g -pthread # -fsanitize=pthread
MKDIR = mkdir -p
RMDIR = rm -rf

# ---------------------------------- Sources --------------------------------- #
SRCS = philo utils check_and_assign routine messages
SRCS_WITH_DIR = $(addprefix ${SRCS_DIR}, ${SRCS}))

# ---------------------------------- Repertories ----------------------------- #
HEADER_DIR = includes/
OBJS_DIR = .objs/
SRCS_DIR = srcs/
HEADER = $(addprefix ${HEADER_DIR}, philo.h)
OBJS = $(addprefix ${OBJS_DIR}, $(addsuffix .o, ${SRCS}))
DEPS = ${OBJS:.o=.d}

# ---------------------------------- Lib Gestion ----------------------------- #
INCLUDES = -I ${HEADER_DIR}
# ---------------------------------- Compilation ----------------------------- #
all: ${NAME} ${OBJS} | ${OBJS_DIR} Makefile
 
${NAME}: ${OBJS} Makefile
	${CC} ${CFLAGS} ${OBJS}  ${INCLUDES} ${LIBFT} -o $@

${OBJS_DIR}%.o: ${SRCS_DIR}%.c ${HEADER} Makefile | ${OBJS_DIR}
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

-include ${DEPS}
# ---------------------------------- Create Repertory ---------------------- #
${OBJS_DIR}:
			${MKDIR} ${OBJS_DIR}

## ---------------------------------- Clean ----------------------------------- #
clean:
	${RMDIR} ${OBJS_DIR}

fclean: clean
	${RM} ${NAME}

re:    fclean
	${MAKE} ${NAME}

# ---------------------------------- Phony ----------------------------------- #
.PHONY: all clean fclean re
