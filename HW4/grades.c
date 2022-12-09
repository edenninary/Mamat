#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "linked-list.h"



//------------------------------creating the structures-------
struct grades{
	 struct list *students_list;	
};

typedef struct student_t{
	int id;
	char* name;
	struct list *courses_list;
}student;

typedef struct course_grade_t{
	char* name;
	int grade;
}course_grade;

//----------------------------------------declering all functions---------
void course_destroy(void *element);
int course_clone(void *element, void **output);
int student_clone(void *element, void **output);
void student_destroy(void *element);
struct grades* grades_init();
void grades_destroy(struct grades *grades);
static student* find_id(struct grades *grades, int id);
static course_grade* find_course(struct list *courses_list, const char *name);
int grades_add_student(struct grades *grades, const char *name, int id);
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade);
float grades_calc_avg(struct grades *grades, int id, char **out);
int grades_print_student(struct grades *grades, int id);
int grades_print_all(struct grades *grades);


//----------destroy functions for deallocating memories and erasing elements--
void course_destroy(void *element){
	course_grade *temp = (course_grade*)element;
	free(temp->name);
	free(temp);
}

void grades_destroy(struct grades *grades){
	
	list_destroy(grades->students_list);
	free(grades);
}

void student_destroy(void *element){
	student *temp = (student*)element;
	free(temp->name);
	list_destroy(temp->courses_list);
	free(temp);
}

//----------------------------clone functions for the linked list---------

int course_clone(void *element, void **output){
	course_grade *source = (course_grade*)element;
	course_grade *new = (course_grade*)malloc(sizeof(*source));
	
	if(new == NULL){
		return 1;
	}
	
	new->name = malloc(strlen(source->name)+1);
	
	if((new->name) == NULL){
		course_destroy(new);
		return 1;
	}
	
	strcpy(new->name, source->name);
	new->grade = source->grade;
	*output = new;
	return 0;
}

int student_clone(void *element, void **output){
	student *source = (student*)element;
	student *new = (student*)malloc(sizeof(*source));
	
	if(new == NULL){
		return 1;
	}
	
	new->name = malloc(strlen(source->name)+1);
	
	if((new->name) == NULL){
		student_destroy(new);
		return 1;
	}
	
	new->courses_list = list_init(course_clone, course_destroy);
	
	if(new->courses_list == NULL){
		student_destroy(new);
		return 1;
	}
	
	strcpy(new->name, source->name);
	new->id = source->id;
	*output = new;
	return 0;
}


//-------------------------------initilize the grade struct--------------- 
struct grades* grades_init() {
	struct grades *grades = (struct grades*)malloc(sizeof(*grades));
	if(!grades){
		return NULL;
	}
	grades->students_list = list_init(student_clone, student_destroy);
	if(!(grades-> students_list)){
		return NULL;
	}
	return grades;
}


//------------------usfulle functions for finding student or course-------	
static student* find_id(struct grades *grades, int id){
	if(list_size(grades->students_list) == 0){
		return NULL;
	}
	else{
		struct iterator *it = list_begin(grades->students_list);
		student *temp;
		while(it != NULL){
			temp = (student*)list_get(it);
			if(!temp){
				return NULL;
			}
			if(temp->id == id){
				return temp;
			}
			it=list_next(it);
		}
		
	}
	return NULL;
	
}

static course_grade* find_course(struct list *courses_list, const char *name){
	if(list_size(courses_list) == 0){
		return NULL;
	}
	else{
		struct iterator *it = list_begin(courses_list);
		course_grade *temp;
		while(it != NULL){
			temp = (course_grade*)list_get(it);
			if(!temp){
				return NULL;
			}
			if(!strcmp(temp->name, name)){
				return temp;
			}
			it=list_next(it);
		}
		
	}
	return NULL;
	
}


//-----------------adding student or course functions to the lists--------
int grades_add_student(struct grades *grades, const char *name, int id){
	
	if( !grades || find_id(grades,id)){
		return 1;
	}
	
	student *temp = (student*)malloc(sizeof(*temp));
	
	if(!temp){
		return 1;
	}
	
	
	temp->courses_list = NULL;
	temp->id = id;
	temp->name = malloc(strlen(name)+1);
	
	if(!(temp->name)){
		student_destroy(temp);
		return 1;
	}
	
	strcpy(temp->name,name);
	if(list_push_back(grades->students_list, temp)){
		student_destroy(temp);
		return 1;
	}
	student_destroy(temp);
	return 0;
		

}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
	if(!grades || grade > 100 || grade <0){
		return 1;
	}
	
	student *student = find_id(grades, id);
	
	if(!student){
		return 1;
	}
	
	if(find_course(student->courses_list, name)){
		return 1;
	}
	else{
			
		course_grade *new = (course_grade*)malloc(sizeof(*new));
		
		if(!new){
			return 1;
		}
		
		new->grade = grade;
		new->name = malloc(strlen(name)+1);
		
		if(!(new->name)){
			course_destroy(new);
			return 1;
		}
		
		strcpy(new->name,name);
		if(list_push_back(student->courses_list, new)){
			course_destroy(new);
			return 1;
		}
		course_destroy(new);
		return 0;
	}
	return 1;
	
					 }	
					 

//-------------------------prints the avg of a specific student-----------			
float grades_calc_avg(struct grades *grades, int id, char **out){
	
	if(!grades){
		*out = NULL;
		return -1;
	}
	
	student *student_p  = find_id(grades,id);
	if(student_p == NULL){
		*out = NULL;
		return -1;
	}
	
	char *name = malloc(strlen(student_p->name)+1);
	
	
	if(name == NULL){
		*out = NULL;
		return -1;
	}
	
	strcpy(name, student_p->name);
	*out = name;
	
	float sum =0;
	float counter=0;
	struct iterator *it = list_begin(student_p->courses_list);
	course_grade *temp;
	
		while(it != NULL){
			temp = (course_grade*)list_get(it);
			if(temp == NULL){
				*out = NULL;
				free(name);
				return -1;
			}
			sum = temp->grade + sum;
			counter++;
			it=list_next(it);
		}
	
	return counter == 0 ? 0 : (sum/counter);
}	
	
//------------------------------printing functions------------------------

int grades_print_student(struct grades *grades, int id){
	
	if(!grades){
		return 1;
	}
	
	student *student_p  = find_id(grades,id);
	if(student_p == NULL){
		return 1;
	}
	
	struct iterator *it = list_begin(student_p->courses_list);
	
	course_grade *temp;
	printf("%s %d:",student_p->name,student_p->id);
	int flag=0;
	while(it != NULL){
		temp = (course_grade*)list_get(it);
		if(temp == NULL){
			return 1;
		}
		if(!flag){
			printf(" %s %d",temp->name,temp->grade);
			flag++;
		}
		else{
			printf(", %s %d",temp->name,temp->grade);
		}
		it=list_next(it);
		
	}
	
	printf("\n");
	
	return 0;
}

int grades_print_all(struct grades *grades){
	
	if(!grades){
		return 1;
	}
	
	struct iterator *it = list_begin(grades->students_list);
	student *temp;
	while(it != NULL){
		
		temp = (student*)list_get(it);
		
		if(!temp){
			return 1;
		}
		
		if(grades_print_student(grades, temp->id)){
			return 1;
		}
		
		it=list_next(it);

	}
	return 0;
}
