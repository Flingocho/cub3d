############################################################################################################
# Cub3d Variables
NAME		=		cub3d
NAME_BONUS	=		cub3d_bonus

# Dependencies	
LIBFT		=		libft
MLX			=		mlx
INC_DIR		=		./include
HEADER_FILE	=		$(INC_DIR)/cub3d.h

# Sources
SRC_DIR		=		./src
SRCS		=		$(addprefix $(SRC_DIR)/, \
					main.c init_vars.c check_args_01.c check_args_02.c check_args_03.c \
					check_map_01.c check_map_02.c check_map_03.c load_textures.c \
					load_textures_bonus.c key_mapping.c moves.c ray_casting_00.c\
					ray_casting_init.c ray_casting_core_01.c ray_casting_core_02.c \
					mini_map.c cleaner.c)

# Objects
OBJ_DIR		=		./obj
OBJ_B_DIR	=		./obj_bonus
OBJS		=		$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS	=		$(SRCS:$(SRC_DIR)/%.c=$(OBJ_B_DIR)/%.o)

# Compiler
CFLAGS		=		#-Wall -Wextra -Werror
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
bonus: ascii_art_bonus

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

ascii_art_bonus:
	@if ! $(MAKE) -q $(NAME_BONUS); then \
		printf " \033[0;35m                                           \n"; \
		printf " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗   \n"; \
		printf "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗  \n"; \
		printf "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║  \n"; \
		printf "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║  \n"; \
		printf "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝  \n"; \
		printf " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝   \n"; \
		printf "               BY JVIDAL-T && MRUBAL-C\033[0m\n"; \
		printf "$(YELLOW)\n[$(NAME_BONUS)]Compiling program...$(GREEN)\n"; \
		$(MAKE) -s $(NAME_BONUS); \
	else \
		echo "$(GREEN)[$(NAME_BONUS)] is already up to date.$(NC)"; \
	fi


$(NAME): $(OBJS)
	@printf "$(NC)"
	@make -C $(LIBFT) plus > /dev/null
	@make -C $(MLX) > /dev/null
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft $(MLXFLAGS) -o $(NAME) && \
	(printf "$(UGREEN)\n%s$(NC)" "[$(NAME)]"; printf "$(GREEN)%s$(NC)\n" "Compiled successfully.")

$(NAME_BONUS): $(OBJS_BONUS)
	@printf "$(NC)"
	@make -C $(LIBFT) plus > /dev/null
	@make -C $(MLX) > /dev/null
	$(CC) -D BONUS=1 $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT) -lft $(MLXFLAGS) -o $(NAME_BONUS) && \
	(printf "$(UGREEN)\n%s$(NC)" "[$(NAME_BONUS)]"; printf "$(GREEN)%s$(NC)\n" "Compiled successfully.")

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADER_FILE)
	@mkdir -p $(dir $@)
	@echo -n "██████"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_B_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILE)
	@mkdir -p $(dir $@)
	@echo -n "██████"
	@$(CC) -D BONUS=1 $(CFLAGS) -c $< -o $@ -I $(INC_DIR)


clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_B_DIR)
	@printf "$(RED)%s$(NC)\n" "[$(NAME)] Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make -s -C $(LIBFT) fclean
	@printf "$(RED)%s$(NC)\n" "[$(NAME)] Cleaned successfully."

re:	fclean all
rebonus: fclean bonus

.PHONY:	all clean fclean re
############################################################################################################