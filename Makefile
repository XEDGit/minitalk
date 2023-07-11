FLAGS:=-Wall -Wextra -Werror -O3 -g

all: server client

server: mt_server.c mt_utils.c
	@gcc $(FLAGS) mt_server.c mt_utils.c -o server
client: mt_client.c mt_utils.c
	@gcc $(FLAGS) mt_client.c mt_utils.c -o client

clean:
	@rm server client
fclean: clean

re: fclean all

bonus: all