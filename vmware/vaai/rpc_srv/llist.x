
struct list {
	string IP<>;
	string mountPoint<>;
	string filePath<>;
	int size;
};

program PRINTER {
	version PRINTER_V1 {
		int PRINT_LIST(list) = 1;
		int SUM_LIST(list) = 2;
	} = 1;
} = 0x2fffffff;
