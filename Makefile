all:
	@gcc mt_client.c mt_utils.c -o mt_client
server:
	@gcc mt_server.c mt_utils.c -o mt_server
	./mt_server