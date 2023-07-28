#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

struct NAME_SURNAME {
	char NAME[5][100];
	char *SURNAME[5][100];
};

typedef struct data {
	int ID;
	char TITLE[150];
	struct NAME_SURNAME n_s[5];
	int pocet_autorov;
	char TYPE[3];
	int TIME;
	int DATE;
	struct data *next;
} DATA;


DATA* create_element(int set_id, char *set_title, char set_name[5][100], char set_surname[5][100], int c_a, char *set_type, int set_time, int set_date) {
	DATA* newData = (DATA*)malloc(sizeof(DATA));
	char copy_of_title[150];
	char copy_of_type[3];
	strcpy(copy_of_title, set_title);
	strcpy(copy_of_type, set_type);
	newData->ID = set_id;
	strcpy(newData->TITLE, copy_of_title);
	for (int i = 0; i < c_a; i++) {
		strcpy(newData->n_s->NAME[i], set_name[i]);
		strcpy(newData->n_s->SURNAME[i], set_surname[i]);
	}
	newData->pocet_autorov = c_a;
	strcpy(newData->TYPE, copy_of_type);
	newData->TIME = set_time;
	newData->DATE = set_date;
	newData->next = NULL;

	return newData;
}

void create_first_element(DATA** list, int set_id, char *set_title, char set_name[5][100], char set_surname[5][100], int c_a, char *set_type, int set_time, int set_date) {	
	*list = create_element(set_id, set_title, set_name, set_surname, c_a, set_type, set_time, set_date);
}

void push(DATA** list, int set_id, char* set_title, char set_name[5][100], char set_surname[5][100], int c_a, char* set_type, int set_time, int set_date) {

	DATA* new_element = create_element(set_id, set_title, set_name, set_surname, c_a, set_type, set_time, set_date);
	DATA* copy = *list;
	while (copy->next != NULL) {
		copy = copy->next;
	}

	copy->next = new_element;

}

int v_function(DATA** list, int *nacitano, int *added) {
	if (*nacitano == 1 || *added == 1) {
		int k = 1;
		DATA* copy_of_list = *list;
		while (copy_of_list != NULL) {
			printf("%d.\n", k);
			printf("ID cislo : %d\n", copy_of_list->ID);
			printf("Nazov prispevku: %s\n", copy_of_list->TITLE);
			printf("Mena autorov: \n");
			for (int i = 0; i < copy_of_list->pocet_autorov; i++) {
				printf("%d: %s %s\n", i + 1, copy_of_list->n_s->NAME[i], copy_of_list->n_s->SURNAME[i]);
			}
			printf("Typ prezentovania: %s\n", copy_of_list->TYPE);
			printf("Cas prezentovania: %d\n", copy_of_list->TIME);
			printf("Datum: = %d\n", copy_of_list->DATE);
			printf("---------------------------------------\n\n");
			k++;
			copy_of_list = copy_of_list->next;
		}
	}
	else {
		printf("Prazdny zoznam zaznamov");
	}
	
	return 0;
}

int n_function(FILE** file, DATA** list, int *nacitano) {
	*file = fopen("subor.txt", "r");
	int l = 0, c_d = 0;
	int c_a = 0;
	char line[200];
	int id = 0, time = 0, date = 0;
	char title[150], names[200], type[3];
	char autor_names[5][100];
	char autor_surname[5][100];
	if (!(*file)) {
		printf("Neotvoreny subor\n");
	}
	else {
		while (fgets(line, sizeof(line), *file)) {
			line[strcspn(line, "\n")] = 0;
			if (strcmp(line, "$$$") == 0) {
				//printf("\n");
			}
			else {
				if (l == 0) {
					if (atoi(line) % 15 == 0) {
						id = atoi(line);
					}
				}
				if (l == 1) {
					strcpy(title, line);
				}
				if (l == 2) {
					strcpy(names, line);
					c_a = 0;
					char* t = strtok(line, "#");
					char autors[5][100] = {0};
					
					while (t != NULL) {
						strcpy(autors[c_a], t);
						t = strtok(NULL, "#");   
						c_a++;
					}			
					for (int i = 0; i < c_a; i++) {
						char* c_t = strtok(autors[i], " ");
						strcpy(autor_names[i], c_t);
						c_t = strtok(NULL, " ");
						strcpy(autor_surname[i], c_t);
					}

				}
				if (l == 3) {
					strcpy(type, line);
				}
				if (l == 4) {
					time = atoi(line);

				}
				if (l == 5) {
					date = atoi(line);					
				}
				l++;
				if (l == 6) {
					if (c_d == 0) {		
						create_first_element(list, id, title, autor_names, autor_surname, c_a, type, time, date);
					}
					else {
						push(list, id, title, autor_names, autor_surname, c_a, type, time, date);
					}
					l = 0;
					c_d++;
				}


				
			}
		}
		*nacitano = 1;
		printf("Nacitalo sa <%d> zaznamov\n", c_d);

		fseek(*file, 0, SEEK_SET);

	}
	
	return 0;
}

int h_function(DATA** list, int *nacitano) {
	if (*nacitano == 1) {
		char t[3];
		int k = 1;
		int a = 0;
		printf("write the type of presentation: ");
		scanf("%s", &t);
		printf("t = %s\n\n", t);
		DATA* copy_of_list = *list;
		while (copy_of_list != NULL) {
			if (!strcmp(copy_of_list->TYPE, t)) {
				printf("%d.", k);
				printf("ID cislo : %d\n", copy_of_list->ID);
				printf("Nazov prispevku: %s\n", copy_of_list->TITLE);
				printf("Mena autorov: \n");
				for (int i = 0; i < copy_of_list->pocet_autorov; i++) {
					printf("%d: %s %s\n", i + 1, copy_of_list->n_s->NAME[i], copy_of_list->n_s->SURNAME[i]);
				}
				printf("Typ prezentovania: %s\n", copy_of_list->TYPE);
				printf("Cas prezentovania: %d\n", copy_of_list->TIME);
				printf("Datum: = %d\n", copy_of_list->DATE);
				printf("---------------------------------------\n\n");
				a = 1;
				k++;
			}			
			copy_of_list = copy_of_list->next;
		}
		if (a == 0) {
			printf("Pre typ: <%s> nie su ziadne zaznamy\n", t);
		}
	}
	else {
		printf("Prazdny zoznam zaznamov\n");
	}
	return 0;
}

int z_function(DATA** list, int* nacitano) {
	if (*nacitano == 0) {
		printf("Prazdny zoznam zaznamov");
	}
	else {
		char name[200];
		char surname[200];
		int i[50] = {0}, j = 0;
		printf("napiste meno autora: ");
		scanf("%s", &name);
		scanf("%s", &surname);
		DATA* copy_of_list = *list;
		DATA* to_delete = *list;
		DATA* previous = *list;
		while (copy_of_list != NULL) {	
			if (!strcmp(copy_of_list->n_s->NAME, name) && !strcmp(copy_of_list->n_s->SURNAME, surname)) {
				//printf("THATS IT!\n");
				i[j]++;
				while (previous->next != copy_of_list) {
					//printf("title = %s\n", previous->TITLE);
					previous = previous->next;
				}
				previous->next = copy_of_list->next;
				to_delete = copy_of_list;
			}
			else {
				//printf("NO!\n");
			}
			j++;
			copy_of_list = copy_of_list->next;
		}
		printf("Prispevok s nazvom %s bol vymazany", to_delete->TITLE);
		free(to_delete);
		
	}
	return 0;
}

int p_function(DATA** list, int *nacitano, int *added) {
	DATA* copy_of_list = *list;
	int n = 0, k = 0;
	int c_a = 0;
	int position;
	int id = 0, time = 0, date = 0;
	char title[150], names[200], type[3];
	char autor_names[5][100];
	char autor_surname[5][100];
	if (*nacitano == 1) {
		while (copy_of_list != NULL) {
			n++;
			copy_of_list = copy_of_list->next;
		}
		printf("write the position: ");
		scanf("%d", &position);
		if (position >= n) {
			printf("write the id: ");
			scanf("%d", &id);
			if (id % 15 != 0) {
				printf("id is wrong\n");
			}
			else {
				printf("write the title: ");
				scanf("\n");
				fgets(title, 150, stdin);
				title[strcspn(title, "\n")] = 0;
				printf("write the names of autors: ");
				fgets(names, 200, stdin);
				names[strcspn(names, "\n")] = 0;
				char* t = strtok(names, "#");
				char autors[5][100] = { 0 };

				while (t != NULL) {
					strcpy(autors[c_a], t);
					t = strtok(NULL, "#");
					c_a++;
				}
				for (int i = 0; i < c_a; i++) {
					char* c_t = strtok(autors[i], " ");
					strcpy(autor_names[i], c_t);
					c_t = strtok(NULL, " ");
					strcpy(autor_surname[i], c_t);
				}
				printf("write the type of presentation: ");
				scanf("%s", &type);
				printf("wrtie the time of presentation: ");
				scanf("%d", &time);
				printf("write the date of presentation: ");
				scanf("%d", &date);
				push(list, id, title, autor_names, autor_surname, c_a, type, time, date);

			}
		}
		else {
			printf("write the id: ");
			scanf("%d", &id);
			if (id % 15 != 0) {
				printf("id is wrong\n");
			}
			else {
				printf("write the title: ");
				scanf("\n");
				fgets(title, 150, stdin);
				title[strcspn(title, "\n")] = 0;
				printf("write the names of autors: ");
				fgets(names, 200, stdin);
				names[strcspn(names, "\n")] = 0;
				char* t = strtok(names, "#");
				char autors[5][100] = { 0 };

				while (t != NULL) {
					strcpy(autors[c_a], t);
					t = strtok(NULL, "#");
					c_a++;
				}
				for (int i = 0; i < c_a; i++) {
					char* c_t = strtok(autors[i], " ");
					strcpy(autor_names[i], c_t);
					c_t = strtok(NULL, " ");
					strcpy(autor_surname[i], c_t);
				}
				printf("write the type of presentation: ");
				scanf("%s", &type);
				printf("wrtie the time of presentation: ");
				scanf("%d", &time);
				printf("write the date of presentation: ");
				scanf("%d", &date);
				DATA* new = (DATA*)malloc(sizeof(DATA));
				new->ID = id;
				strcpy(new->TITLE, title);
				for (int i = 0; i < c_a; i++) {
					strcpy(new->n_s->NAME[i], autor_names[i]);
					strcpy(new->n_s->SURNAME[i], autor_surname[i]);
				}
				new->pocet_autorov = c_a;
				strcpy(new->TYPE, type);
				new->TIME = time;
				new->DATE = date;
				new->next = NULL;
				DATA* copy = *list;
				int o = 0;
				while (copy->next != NULL) {
					if (o+2 == position) {
						new->next = copy->next;
						copy->next = new;
					}
					o++;
					copy = copy->next;
				}
			}
			

		}
	}
	else if (*nacitano == 0 && *added == 0){
		printf("write the id: ");
		scanf("%d", &id);
		if (id % 15 != 0) {
			printf("id is wrong\n");
		}
		else {
			printf("write the title: ");
			scanf("\n");
			fgets(title, 150, stdin);
			title[strcspn(title, "\n")] = 0;
			printf("write the names of autors: ");
			fgets(names, 200, stdin);
			names[strcspn(names, "\n")] = 0;
			char* t = strtok(names, "#");
			char autors[5][100] = { 0 };

			while (t != NULL) {
				strcpy(autors[c_a], t);
				t = strtok(NULL, "#");
				c_a++;
			}
			for (int i = 0; i < c_a; i++) {
				char* c_t = strtok(autors[i], " ");
				strcpy(autor_names[i], c_t);
				c_t = strtok(NULL, " ");
				strcpy(autor_surname[i], c_t);
			}
			printf("write the type of presentation: ");
			scanf("%s", &type);
			printf("wrtie the time of presentation: ");
			scanf("%d", &time);
			printf("write the date of presentation: ");
			scanf("%d", &date);
			DATA* list = (DATA*)malloc(sizeof(DATA));
			//*list = (DATA*)malloc(sizeof(DATA));
			list->ID = id;
			strcpy(list->TITLE, title);
			for (int i = 0; i < c_a; i++) {
				strcpy(list->n_s->NAME[i], autor_names[i]);
				strcpy(list->n_s->SURNAME[i], autor_surname[i]);
			}
			list->pocet_autorov = c_a;
			strcpy(list->TYPE, type);
			list->TIME = time;
			list->DATE = date;
			list->next = NULL;
			*added = 1;
		}
		
	}
	else if (*added == 1) {
	printf("write the position: ");
	scanf("%d", &position);
	if (position >= n) {
		printf("write the id: ");
		scanf("%d", &id);
		if (id % 15 != 0) {
			printf("id is wrong\n");
		}
		else {
			printf("write the title: ");
			scanf("\n");
			fgets(title, 150, stdin);
			title[strcspn(title, "\n")] = 0;
			printf("write the names of autors: ");
			fgets(names, 200, stdin);
			names[strcspn(names, "\n")] = 0;
			char* t = strtok(names, "#");
			char autors[5][100] = { 0 };

			while (t != NULL) {
				strcpy(autors[c_a], t);
				t = strtok(NULL, "#");
				c_a++;
			}
			for (int i = 0; i < c_a; i++) {
				char* c_t = strtok(autors[i], " ");
				strcpy(autor_names[i], c_t);
				c_t = strtok(NULL, " ");
				strcpy(autor_surname[i], c_t);
			}
			printf("write the type of presentation: ");
			scanf("%s", &type);
			printf("wrtie the time of presentation: ");
			scanf("%d", &time);
			printf("write the date of presentation: ");
			scanf("%d", &date);
			push(list, id, title, autor_names, autor_surname, c_a, type, time, date);

		}
	}
	}
	

	return 0;
}

int r_function(DATA** list, int* nacitano) {
	if (*nacitano == 1) {
		int a = 0, b = 0;
		printf("write first position: ");
		scanf("%d", &a);
		printf("wrtie second position: ");
		scanf("%d", &b);
		printf("a = %d, b = %d\n", a, b);
		DATA* f_copy = *list;
		DATA* f_copy_previous = *list;
		DATA* s_copy = *list;
		DATA* s_copy_previous = *list;
		DATA* s_copy_next = *list;
		if (a == 1) {
			/*
			f_copy = *list;
			printf("f_copy->title = %s\n", f_copy->TITLE);
			for (int k = 0; k < b; k++) {
				s_copy = s_copy->next;
			}
			for (int t = 0; t < b - 1; t++) {
				s_copy_previous = s_copy_previous->next;
			}
			printf("s_copy->title = %s\n", s_copy->TITLE);
			printf("s_copy_prev->title = %s\n", s_copy_previous->TITLE);
			s_copy_next = s_copy->next;
			*list = s_copy;
			s_copy->next = f_copy->next;
			s_copy_previous->next = f_copy;
			f_copy->next = s_copy_next->next;
			*/
		}
		else {
			for (int i = 0; i < a; i++) {
				f_copy = f_copy->next;
			}
			for (int j = 0; j < a - 1; j++) {
				f_copy_previous = f_copy_previous->next;
			}
			printf("f_copy->title = %s\n", f_copy->TITLE);
			printf("f_copy_prev->title = %s\n", f_copy_previous->TITLE);
			for (int k = 0; k < b; k++) {
				s_copy = s_copy->next;
			}
			for (int t = 0; t < b - 1; t++) {
				s_copy_previous = s_copy_previous->next;
			}
			printf("s_copy->title = %s\n", s_copy->TITLE);
			printf("s_copy_prev->title = %s\n", s_copy_previous->TITLE);
			s_copy_next = s_copy->next;
			f_copy_previous->next = s_copy;
			s_copy->next = f_copy->next;
			s_copy_previous->next = f_copy;
			f_copy->next = s_copy_next;
		}
		
		

		
	}
	else {
		printf("Prazdny zoznam zaznamov\n");
	}
	return 0;
}

int a_function(DATA** list, int* nacitano) {
	if (*nacitano == 1) {
		int s_id;
		char t[3];
		printf("write the ID of Presentation: ");
		scanf("%d", &s_id);
		if (s_id % 15 != 0) {
			printf("wrong ID");
		}
		else {
			printf("write the new type of presentation: ");
			scanf("%s", &t);
			DATA* copy_of_list = *list;
			while (copy_of_list != NULL) {
				if (copy_of_list->ID == s_id) {
					char old_t[3];
					strcpy(old_t, copy_of_list->TYPE);
					strcpy(copy_of_list->TYPE, t);
					printf("Prispevok s nazvom %s sa bude prezentovat %s[%s].", copy_of_list->TITLE, copy_of_list->TYPE, old_t);
				}
				copy_of_list = copy_of_list->next;
			}
		}
	}
	else {
		printf("Prazdny zoznam zaznamov\n");
	}
	return 0;
}

void navigation() {
	char func_name = NULL;
	DATA* list = 0;
	FILE* file = 0;
	int nacitano = 0, added = 0;
	printf("zadajte pismeno: ");
	while (1) {
		scanf("%c", &func_name);;
		printf("\n");
		switch (func_name) {
		case 'v':
			v_function(&list, &nacitano, &added);
			break;
		case 'n':
			n_function(&file, &list, &nacitano);
			break;
		case 'a':
			a_function(&list, &nacitano);
			break;
		case 'r':
			r_function(&list, &nacitano);
			break;
		case 'h':
			h_function(&list, &nacitano);
			break;
		case 'z':
			z_function(&list, &nacitano);
			break;
		case 'p':
			p_function(&list, &nacitano, &added);
			break;
		case 'k':	
			DATA * copy = list;
			while (list != NULL) {
				copy = list;
				list = list->next;
				free(copy);
			}
			exit(1);
			break;
		default:
			printf("zadajte pismeno: ");
			break;
		}


	}
}

int main() {

	navigation();
	return 0;
}