FLAGS:=-Wall -Wextra -Werror

all:
	@make server
	@make client
server: mt_server.c mt_utils.c
	@gcc $(FLAGS) mt_server.c mt_utils.c -o server
client: mt_client.c mt_utils.c
	@gcc $(FLAGS) mt_client.c mt_utils.c -o client
clean:
	@rm server client
fclean:
	@rm -f server client
re:
	@make fclean
	@make all
bonus:
	@make all