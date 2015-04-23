CLI =				client
SERV =				serveur
CC =				gcc
LIB =				ft
LIB_DIR =			./libft/
LIB_INCLUDES =		$(LIB_DIR)includes/
LIBFT =				$(LIB_DIR)libft.a
CFLAGS =			-Wall -Wextra -Werror -I ./includes -I$(LIB_INCLUDES) -g -c -o
CLI_CFLAGS =		-I./client_dir/includes
SERV_CFLAGS =		-I./server_dir/includes
LDFLAGS =			-L$(LIB_DIR) -l$(LIB) -o
CLI_SRC_DIR =		./client_dir/srcs/
SERV_SRC_DIR =		./server_dir/srcs/
CLI_OBJ_DIR =		./client_dir/obj/
SERV_OBJ_DIR =		./server_dir/obj/
CLI_SRCS =			main.c					create_client.c\
					read_from_client.c		write_to_serv.c\
					init_env.c				read_from_serv.c\
					check_fd.c				run_client.c\
					get_opt.c				usage.c
SERV_SRCS =			main.c					clean_fd.c\
					disp.c					get_opt.c\
					init_env.c				run_srv.c\
					srv_accept.c			srv_create.c\
					init_fd.c				check_fd.c\
					client_write.c			client_read.c\
					get_client_input.c		handlers1.c
CLI_OBJ =			$(CLI_SRCS:.c=.o)
SERV_OBJ =			$(SERV_SRCS:.c=.o)

all: $(LIBFT) $(CLI) $(SERV)

$(LIBFT):
	make -C $(LIB_DIR)

$(CLI_OBJ_DIR):
	mkdir $@

$(SERV_OBJ_DIR):
	mkdir $@

$(CLI): $(CLI_OBJ_DIR) $(addprefix $(CLI_OBJ_DIR), $(CLI_OBJ))
	$(CC) $(LDFLAGS) $(CLI) $(addprefix $(CLI_OBJ_DIR), $(CLI_OBJ))

$(CLI_OBJ_DIR)%.o: $(CLI_SRC_DIR)%.c
	$(CC) $(CLI_CFLAGS) $(CFLAGS) $@ $<

$(SERV): $(SERV_OBJ_DIR) $(addprefix $(SERV_OBJ_DIR), $(SERV_OBJ))
	$(CC) $(LDFLAGS) $(SERV) $(addprefix $(SERV_OBJ_DIR), $(SERV_OBJ))

$(SERV_OBJ_DIR)%.o: $(SERV_SRC_DIR)%.c
	$(CC) $(SERV_CFLAGS) $(CFLAGS) $@ $<

clean: client_clean server_clean

fclean: client_fclean server_fclean

client_clean:
	rm -rf $(CLI_OBJ_DIR)

server_clean:
	rm -rf $(SERV_OBJ_DIR)

client_fclean: client_clean
	rm -f $(CLI)

server_fclean: server_clean
	rm -f $(SERV)

re: fclean libre all

client_re: client_fclean libre $(CLI)

server_re: server_fclean libre $(SERV)

libre:
	make -C $(LIB_DIR) re

.PHONY: all clean fclean libre client_clean server_clean client_fclean\
	server_fclean client_re server_re client_build server_build