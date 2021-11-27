all:
	@gcc mt_client.c mt_utils.c -o mt_client
server:
	@gcc mt_server.c mt_utils.c -o mt_server
	./mt_server
clean:
	@rm -f mt_server mt_client
fclean:
	@make clean
make re:
	@make clean
	@make all
bonus:
	@make all