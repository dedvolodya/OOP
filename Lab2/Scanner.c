#include "Scanner.h"

int scan_id = 0;

int compare_year(const void  *x1, const void *x2) {
	SCAN_INFO *sc1, *sc2;

	sc1 = (SCAN_INFO*)x1;
	sc2 = (SCAN_INFO*)x2;

	return sc1->year - sc2->year;
}
int compare_price(const void  *x1, const void *x2) {
	SCAN_INFO *sc1, *sc2;

	sc1 = (SCAN_INFO*)x1;
	sc2 = (SCAN_INFO*)x2;

	if ((sc1->price - sc1->price) < 0)
		return -1;
	if ((sc1->price - sc1->price) > 0)
		return 1;
	return 0;
}
int compare_x(const void  *x1, const void *x2) {
	SCAN_INFO *sc1, *sc2;

	sc1 = (SCAN_INFO*)x1;
	sc2 = (SCAN_INFO*)x2;
	return sc1->x_size - sc2->x_size;
}
int compare_y(const void  *x1, const void *x2) {
	SCAN_INFO *sc1, *sc2;

	sc1 = (SCAN_INFO*)x1;
	sc2 = (SCAN_INFO*)x2;

	return sc1->y_size - sc2->y_size ;
}
int compare_manufacturer(const void  *x1, const void *x2) {
	SCAN_INFO *sc1, *sc2;

	sc1 = (SCAN_INFO*)x1;
	sc2 = (SCAN_INFO*)x2;

	return strcmp(sc1->manufacturer, sc2->manufacturer);
}
int compare_model(const void  *x1, const void *x2) {
	SCAN_INFO *sc1, *sc2;

	sc1 = (SCAN_INFO*)x1;
	sc2 = (SCAN_INFO*)x2;

	return strcmp(sc1->model, sc2->model);
}
int count(const char *str) {
	int i, n, result = 0;
	for (i = 0, n = strlen(str); i < n; i++)
		if (str[i] == ';') {
			result++;
		}
	return result + 1;
}
char **split(const char *str,const int length) {
	char **res;
	int i = 0, k = 0, j = 0,n;

	n = strlen(str);
	res = (char**)malloc(sizeof(char*)*length);
	for (k = 0; k < length; k++) {
		res[k] = (char*)malloc(sizeof(char) * 64);
	}

	for (k = 0; k < length; k++) {
		j = 0;
		while (i < n && str[i] != ';') {
			res[k][j] = str[i];
			i++;
			j++;
		}
		res[k][j] = '\0';
		i++;
	}
	return res;
}

void create_db(const char *csv, const char *db) {
	FILE *in, *out;
	
	char buf[256];

	in = fopen(csv, "rt");
	out = fopen(db, "wb");
	fclose(out);

	while (fgets(buf, 256 * sizeof(char), in)) {
		add_scanner(db, buf);
	}

	fclose(in);
}

int make_index(const char *db, const char *field_name) {
	FILE *db_file;
	FILE *indx_file;
	char name[32]; // for named result file  "field_name.idx"
	int i = 0 , *mas , n;
	SCAN_INFO *scanners;

	if (db == NULL || field_name == NULL)
		return 0;
	
	db_file = fopen(db, "rb");
	n = filelength(_fileno(db_file)) / (sizeof(SCAN_INFO) + sizeof(int)); //number scanners

	mas = (int*)malloc(sizeof(int)*n);
	scanners = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*n);

	while (i < n) {
		fread(&mas[i], sizeof(int), 1, db_file);
		fread(&scanners[i], sizeof(SCAN_INFO), 1, db_file);
		i++;
	}
	fclose(db_file);
	if (strcmp(field_name, "manufacturer") == 0)
		qsort(scanners, n, sizeof(SCAN_INFO), compare_manufacturer);
	else if (strcmp(field_name, "model") == 0)
		qsort(scanners, n, sizeof(SCAN_INFO), compare_model);
	else if (strcmp(field_name, "year") == 0)
		qsort(scanners, n, sizeof(SCAN_INFO), compare_year);
	else if (strcmp(field_name, "x_size") == 0)
		qsort(scanners, n, sizeof(SCAN_INFO), compare_x);
	else if (strcmp(field_name, "y_size") == 0)
		qsort(scanners, n, sizeof(SCAN_INFO), compare_y);
	else if (strcmp(field_name, "price") == 0)
		qsort(scanners, n, sizeof(SCAN_INFO), compare_price);
	else
		return 0;
	strcpy(name, field_name);
	strncat(name, ".idx", 4);

	indx_file = fopen(name, "wt");

	for (i = 0; i < n; i++)
		fprintf(indx_file, "%i ", scanners[i].id);
	fclose(indx_file);
	return 1;
}

RECORD_SET *get_recs_by_index(const char *dba, char *indx_field) {
	RECORD_SET *set;
	SCAN_INFO *scanners;
	FILE *f, *idx;
	int *mas, n, i = 0, k;
	char name[32];

	f = fopen(dba, "rb");
	n = filelength(_fileno(f)) / (sizeof(SCAN_INFO) + sizeof(int)); //number scanners
	set = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	mas = (int*)malloc(sizeof(int)*n);
	scanners = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*n);

	set->rec_nmb = n;
	set->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*n);
	while (fread(&k, sizeof(int), 1, f)) {
		fread(&scanners[i], sizeof(SCAN_INFO), 1, f);
		i++;
	}
	fclose(f);
	strcpy(name, indx_field, name);
	strncat(name, ".idx", 4);
	idx = fopen(name, "rt");
	if (idx == 0) {
		make_index(dba, indx_field);
		idx = fopen(name, "rt");
	}
	i = 0;
	while (i < n) {
		fscanf(idx, "%i", &mas[i]);
		i++;
	}
	for (i = 0; i < n; i++) {
		set->recs[i] = scanners[mas[i]];
	}
	
	fclose(idx);
	return set;
}

void reindex(const char *db) {
	make_index(db, "manufacturer");
	make_index(db, "model");
	make_index(db, "year");
	make_index(db, "price");
	make_index(db, "x_size");
	make_index(db, "y_size");
}

void del_scanner(const char *db, int id) {
	FILE *f;
	int i = 0 , n , flag = 0;
	SCAN_INFO *scanners;
	int *mas;

	scan_id = 0;
	f = fopen(db, "r+b");
	n = filelength(_fileno(f)) / (sizeof(SCAN_INFO) + sizeof(int)); //number scanners

	mas = (int*)malloc(sizeof(int)*n);
	scanners = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*n);

	while (i < n) {
		fread(&mas[i], sizeof(int), 1, f);
		fread(&scanners[i], sizeof(SCAN_INFO), 1, f);
		i++;
	}
	i = 0;
	fseek(f, 0, SEEK_SET);
	while (i < n) {
		if (scanners[i].id != id) {
			scanners[i].id = scan_id;
			scan_id++;
			fwrite(&mas[i], sizeof(int), 1, f);
			fwrite(&scanners[i], sizeof(SCAN_INFO), 1, f);
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
	    _chsize(_fileno(f), (n-1)*sizeof(SCAN_INFO));

	free(mas);
	free(scanners);
	fclose(f);
}

void add_scanner(const char *db, const char* scanner_str) {
	FILE *f;
	int n;
	char **buf2d;
	SCAN_INFO scanner;

	f = fopen(db, "ab" );
	n = count(scanner_str);
	buf2d = split(scanner_str, n);
	scanner.id = scan_id++;
	scanner.manufacturer = buf2d[0];
	scanner.model = buf2d[1];
	scanner.year = atoi(buf2d[2]);
	scanner.price = atof(buf2d[3]);
	scanner.x_size = atoi(buf2d[4]);
	scanner.y_size = atoi(buf2d[5]);
	fwrite(&n, sizeof(int), 1, f);
	fwrite(&scanner, sizeof(scanner), 1, f);
	fclose(f);
	//free_memory(buf2d, n);
	/*int i;
	if (buf2d != NULL) {
		for (i = 0; i < n; i++)
			free(buf2d[i]);
		free(buf2d);
	}*/
}

void print_db(const char *db) {
	FILE *f,*res;
	SCAN_INFO scanner;
	int n;

	f = fopen(db, "rb");
	res = fopen("scan_info.txt", "wt");

	while (fread(&n, sizeof(int), 1, f)) {
		fread(&scanner, sizeof(SCAN_INFO), 1, f);
		fprintf(res, "%s %s %i %.2f %i %i id=%i\n", 
			scanner.manufacturer
			, scanner.model
			, scanner.year
			, scanner.price
			, scanner.x_size
			, scanner.y_size
			, scanner.id);
	}
	fclose(res);
	fclose(f);
}

RECORD_SET* select(const char *db, const char *field, const char *value) {
	FILE *f;
	int i = 0, n, k = 0,j = 0 , buf1,buf2;
	float buff;
	SCAN_INFO *scanners;
	int *mas;
	RECORD_SET *rs;

	rs = (RECORD_SET*)malloc(sizeof(RECORD_SET));
	f = fopen(db, "rb");
	n = filelength(_fileno(f)) / (sizeof(SCAN_INFO) + sizeof(int)); //number scanners

	mas = (int*)malloc(sizeof(int)*n);
	scanners = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*n);

	while (i < n) {
		fread(&k, sizeof(int), 1, f);
		fread(&scanners[i], sizeof(SCAN_INFO), 1, f);
		if (strcmp(field, "manufacturer") == 0)
			if (strcmp(scanners[i].manufacturer,value) == 0) {
				mas[j] = i;
				j++;
			}
		if (strcmp(field, "model") == 0)
			if (strcmp(scanners[i].model, value) == 0) {
				mas[j] = i;
				j++;
			}
		if (strcmp(field, "year") == 0)
			if (scanners[i].year == atoi(value)) {
				mas[j] = i;
				j++;
			}
		if (strcmp(field, "x_size") == 0)
			if (scanners[i].x_size == atoi(value)) {
				mas[j] = i;
				j++;
			}
		if (strcmp(field, "y_size") == 0)
			if (scanners[i].y_size == atoi(value)) {
				mas[j] = i;
				j++;
			}
		if (strcmp(field, "price") == 0) {
			buff = scanners[i].price * 100;
			buf1 = (int)buff;
			buff = atof(value);
			buff *= 100;
			buf2 = (int)buff;
			if (buf1==buf2) {
				mas[j] = i;
				j++;
			}
		}
		i++;
	}
	i = 0;
	rs->rec_nmb = j;
	rs->recs = (SCAN_INFO*)malloc(sizeof(SCAN_INFO)*j);
	for (i = 0; i < j ; i++) {
		rs->recs[i] = scanners[mas[i]];
	}
	fclose(f);
	return rs;
}

void print_rec_set(RECORD_SET *rs) {
	int i = 0;
	for (i = 0; i < rs->rec_nmb; i++) {
		printf("%s %s %i %.2f %i %i id=%i\n",
			rs->recs[i].manufacturer
			, rs->recs[i].model
			, rs->recs[i].year
			, rs->recs[i].price
			, rs->recs[i].x_size
			, rs->recs[i].y_size
			, rs->recs[i].id);
	}
}