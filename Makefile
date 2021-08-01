EXE_CLIENT		= client

EXE_SERVER		= server

SRCS_FILES		= server.c client.c

OBJS_DIR		= .objs

SRCS_DIR		= srcs

OBJS			= $(addprefix $(OBJS_DIR)/,$(SRCS_FILES:.c=.o))

SRCS			= $(addprefix $(SRCS_DIR)/,$(SRCS_FILES))

HEADERS			= include/minitalk.h libft/libft.h

CC				= gcc

CFLAGS			= -g -Wall -Werror -Wextra -Iinclude/ -Ilibft/

SANFLAGS		= -g3 -fsanitize=address

LIBFT_FILES		= libft

EXE_LIBFT		= libft.a

RM				= /bin/rm -rf

green			= \033[32m

yellow			= \033[33m

normal			= \033[0m

all				: $(EXE_SERVER) $(EXE_CLIENT)

$(EXE_SERVER)	: $(EXE_LIBFT) $(OBJS)
					$(CC) -o $(EXE_SERVER) $(OBJS_DIR)/server.o $(EXE_LIBFT)
					@echo "$(yellow)Server is $(green)ready$(normal)"

$(EXE_CLIENT)	: $(EXE_LIBFT) $(OBJS)
					$(CC) -o $(EXE_CLIENT) $(OBJS_DIR)/client.o $(EXE_LIBFT)
					@echo "$(yellow)Client is $(green)ready"

$(EXE_LIBFT)	:
					$(MAKE) -C$(LIBFT_FILES) -s
					cp $(LIBFT_FILES)/$(EXE_LIBFT) .

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c $(HEADERS)
					mkdir -p $(OBJS_DIR) $(addprefix $(OBJS_DIR)/,$(PATH_OBJS))
					$(CC) $(CFLAGS) -o $@ -c $<

clean			:
					$(RM) $(OBJS)

cleanlibft		:
					make -C libft clean
				
fclean			: clean cleanlibft
					$(RM) $(EXE_LIBFT)
					$(RM) $(EXE_CLIENT)
					$(RM) $(EXE_SERVER)
					$(RM) $(OBJS_DIR)

re				: fclean all

.PHONY			: all clean fclean re