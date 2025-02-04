############################################################################################################
# Cub3d Variables
NAME		=		cub3d

# Dependencies	
LIBFT		=		libft
MLX			=		minilibx-linux
INC_DIR		=		./include
HEADER_FILE	=		$(INC_DIR)/cub3d.h

# Sources
SRC_DIR		=		./src
SRCS		=		$(addprefix $(SRC_DIR)/, \
					main.c init_vars.c check_args.c check_map.c parser.c cleaner.c)

# Objects
OBJ_DIR		=		./obj
OBJS		=		$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler
CFLAGS		=		-Wall -Wextra -Werror
MLXFLAGS	=		-L$(MLX) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
CC			=		cc

# Colors
GREEN		=		\033[0;32m
UGREEN		=		\033[4;32m
RED			=		\033[0;31m
YELLOW		=		\033[0;33m
LILA		=		\033[0;35m
NC			=		\033[0m # No color

############################################################################################################
# Cub3d Rules

all: ascii_art

lib:
	make -C $(LIBFT)

ascii_art:
	@if ! $(MAKE) -q $(NAME); then \
		printf " \033[0;35m                                           \n"; \
		printf " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗   \n"; \
		printf "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗  \n"; \
		printf "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║  \n"; \
		printf "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║  \n"; \
		printf "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝  \n"; \
		printf " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝   \n"; \
		printf "               BY JVIDAL-T && MRUBAL-C\033[0m\n"; \
		printf "$(YELLOW)\n[$(NAME)]Compiling program...$(GREEN)\n"; \
		$(MAKE) -s $(NAME); \
	else \
		echo "$(GREEN)[$(NAME)] is already up to date.$(NC)"; \
	fi


$(NAME): $(OBJS)
	@printf "$(NC)"
	@make -C $(LIBFT) plus > /dev/null
	@make -C $(MLX) > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft $(MLXFLAGS) -o $(NAME) && \
	(printf "$(UGREEN)\n%s$(NC)" "[$(NAME)]"; printf "$(GREEN)%s$(NC)\n" "Compiled successfully.")

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADER_FILE)
	@mkdir -p $(dir $@)
	@echo -n "███████"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)


clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)%s$(NC)\n" "[$(NAME)] Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFT) fclean
	@printf "$(RED)%s$(NC)\n" "[$(NAME)] Cleaned successfully."

re:	fclean all

.PHONY:	all clean fclean re
############################################################################################################