
#include "llist.h"

list *mk_list(char* remoteIP, char* mountPoint, char* filePath, int size)
{
	list *lst;

	lst = (list*)malloc(sizeof(list));
	if (lst == NULL)
		return NULL;
	lst->IP = remoteIP;
	lst->mountPoint = mountPoint;
	lst->filePath = filePath;
	lst->size = size;
	return lst;
}



int call_print_list(char* remoteIP, char* mountPoint, char* filePath, int size)
{
	list *l;
	int *result;
	CLIENT* cl = clnt_create(remoteIP, PRINTER, PRINTER_V1, "udp");
	l = mk_list(remoteIP, mountPoint, filePath, size);
	if (cl == NULL) {
		printf("error: could not connect to server.\n");
		return 1;
	}
	printf("%s %s %s %d\n", l->IP, l->mountPoint, l->filePath, l->size);
	result = print_list_1(l, cl);
	if (result == NULL) {
		printf("error: RPC failed!\n");
		return 1;
	}
	printf("client: server says it printed %d items.\n", *result);

}
int main(int argc, char *argv[])
{
	call_print_list(argv[1], "/Pool-1/nfs", "aaa", 50);
	return 0;
}
