#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

enum branch {CSE, EE, ME};

struct student {
    char rollno[MAX];
    char name[MAX];
    enum branch branch;
    int semester;
    int ncourses;
    char **course_codes;
};

struct instructor {
    char id[MAX];
    char name[MAX];
    int ncoursess;
    char **courses_codes;
};

struct course {
    char code[MAX];
    char name[MAX];
    int ncourses;
    int credits;
    int ninstructors;
    char **instructor_ids;
    int nstudents;
    char **student_rollnos;
};

//student function prototypes
void load_students();
void allocate_student(struct student s);
void display_allstudents();
void display_student(struct student s);
int display_onestudent();
int add_newstudent();
void puttofile_student(struct student s);
int delete_student();
int modify_student();

//instructor function prototypes
void load_instructors();
void allocate_instructor(struct instructor i);
void display_allinstructors();
void display_instructor(struct instructor i);
int display_oneinstructor();
int add_newinstructor();
void puttofile_instructor(struct instructor i);
int delete_instructor();
int modify_instructor();

//course function prototypes
void load_courses();
void allocate_course(struct course c);
void display_allcourses();
void display_course(struct course c);
int display_onecourse();
int add_newcourse();
void puttofile_course(struct course c);
int delete_course();
int modify_course();  

struct course *courses;
struct student *students;
struct instructor *instructors;

FILE *fps;
FILE *fpc;
FILE *fpi;

char students_file[MAX] = "students.txt";
char courses_file[MAX] = "courses.txt";
char instructors_file[MAX] = "instructors.txt";

int ncourses = 0, nstudents = 0, ninstructors = 0,ncoursess=0;

int main() 
{
	int choice1;
	int choice2;
	int choice3;

	load_students();
	load_instructors();
	load_courses();
	
	printf("\n\n\t\t\t1.Student options\n\t\t\t2.Instructor options \n\t\t\t3.Course Options\n");
    printf("\n\t\t\tEnter Choice(1,2, or 3):");
	scanf("%d",&choice1);

	if(choice1==1)
	  {
	 	printf("\n\t\t\t-----------------\n\t\t\tSTUDENT OPTIONS\t\t\t\n\t\t\t-----------------\n\t\t\t1)Display Students \n\t\t\t2)Display Student of Choice(based on Roll No.) \n\t\t\t3)Add a Student \n\t\t\t4)Delete a Student \n\t\t\t5)Modify a Student\n");
		printf("\n\t\t\tEnter Choice(1,2,3,4 or 5):");	 	
		scanf("%d",&choice2);
	 	switch(choice2)
	  	{
	  	case 1:display_allstudents();       break;
	  	case 2:display_onestudent();        break;
 	  	case 3:add_newstudent();            break;
	  	case 4:delete_student();            break;
	  	case 5:modify_student();            break;	
	  	default:
	  	printf("\n\t\t\tINVALID,run again\n");break;
	  	}
 	  }

	else if(choice1==2)
	  { 
		printf("\n\t\t\t-----------------\n\t\t\tINSTRUCTOR OPTIONS\t\t\t\n\t\t\t-----------------\n\t\t\t1)Display Instructors\n\t\t\t2)Display Instructor of Choice(based on ID)\n\t\t\t3)Add an Instructor\n\t\t\t4)Delete an Instructor\n\t\t\t5)Modify an Instructor\n");
		printf("\n\t\t\tEnter Choice(1,2,3,4 or 5):");	 			
		scanf("%d",&choice2);
		switch(choice2)
	  	{
	  	case 1:display_allinstructors();    break;
	  	case 2:display_oneinstructor();     break;
 	  	case 3:add_newinstructor();         break;
	  	case 4:delete_instructor();         break;
	  	case 5:modify_instructor();         break;
	  	default:
	  	printf("\n\t\t\tINVALID,run again\n");break;	
	  	}
 	  }
 	  
	else if(choice1==3)
	  {
		printf("\n\t\t\t-----------------\n\t\t\tCOURSE OPTIONS\t\t\t\n\t\t\t-----------------\n\t\t\t1)Display All Courses \n\t\t\t2)Display Course of Choice(based on ID)\n\t\t\t3)Add a Course\n\t\t\t4)Delete a Course\n\t\t\t5)Modify a Course\n");
		printf("\n\t\t\tEnter Choice(1,2,3,4 or 5):");	 			
		scanf("%d",&choice2);
		switch(choice2)
	  	{
	  	case 1:display_allcourses(); 	    break;
	  	case 2:display_onecourse();         break;
 	  	case 3:add_newcourse();             break;
	  	case 4:delete_course();             break;
	  	case 5:modify_course();             break;
	  	default:
	  	printf("\n\t\t\tINVALID,run again\n");break;	
	  	}
 	  } 
	else
	printf("\n\t\t\tINVALID,run again\n");
	 	  
    return 0;
}

	
//STUDENT FUNCTION BODIES

void load_students() {
    fps = fopen(students_file, "r");
    int nstudents;
    char buf[MAX];
    struct student s;
    fscanf(fps, "%d", &nstudents);
    for (int i=0; i<nstudents; i++) 
    	{
        fgets(buf, MAX, fps);
        fscanf(fps, "%s", s.rollno);
        fscanf(fps, "%s", s.name);
        fscanf(fps, "%u", &s.branch);
        fscanf(fps, "%d", &s.semester);
        fscanf(fps, "%d", &s.ncourses);
        s.course_codes = malloc (s.ncourses * sizeof(char *));
        for (int j=0; j<s.ncourses; j++) 
        	{
            s.course_codes[j] = malloc (MAX * sizeof (char));
            fscanf(fps, "%s", s.course_codes[j]);
        	}
        allocate_student(s);
    	}
}
	
void allocate_student(struct student s) 
{
    students = realloc (students, (nstudents+1)*sizeof(struct student));
    students[nstudents] = s;
    nstudents++;
}

//DISPLAY ALL
void display_allstudents() 
{  
    printf("\n\t\t\t-----------------\n\t\t\tSTUDENT DETAILS\n\t\t\t-----------------\n");
    for (int i=0; i<nstudents; i++) 
    	{
        display_student(students[i]);
    	}
}

void display_student(struct student s) 
{
    printf("\n\t\t\tRoll no.: %s\n", s.rollno);
    printf("\t\t\tName: %s\n", s.name);
    printf("\t\t\tBranch: %d\n", s.branch);
    printf("\t\t\tSemester: %d\n", s.semester);
    printf("\t\t\tList of courses:\n\t\t\t");
    for (int i=0; i<s.ncourses; i++) 
    	{
        printf("%s\t", s.course_codes[i]);
    	}
    printf("\n\n");
}

//DISPLAY ONE
int display_onestudent()
{	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter Roll No.:");
    scanf("%s",str);
    for (int i=0; i<nstudents; i++) 
    	{
        if(strcmp(students[i].rollno,str)==0)
        {flag=1;}
        } 
    if(flag==0) printf("\t\t\tRoll No. entered is not present to be displayed,run again\n");	
    
	for(int i=0;i<nstudents;i++)
		{
	    if(strcmp(students[i].rollno,str)==0)
	    {display_student(students[i]);}
	    else 
	    {;}
		}
	return 0;		
}

//ADD
int add_newstudent()
{   
    struct student s;
	printf("\n\t\t\tEnter Roll No:");
	scanf("%s",s.rollno);
	for (int i=0; i<nstudents; i++) 
    	{
        if(strcmp(students[i].rollno,s.rollno)==0)
        {printf("\t\t\tRoll No. entered is already present,run again\n");
        return 0;}
    	}
	
	printf("\t\t\tEnter Name:");
	scanf("%s",s.name);
	printf("\t\t\tEnter Branch:");
	scanf("%u",&s.branch);
	printf("\t\t\tEnter Semester:");
	scanf("%d",&s.semester);
	printf("\t\t\tEnter No. of Courses:");
	scanf("%d",&s.ncourses);
    printf("\t\t\tEnter courses:\n\t\t\t");
    s.course_codes = malloc (s.ncourses * sizeof(char *));
	for (int j=0; j<s.ncourses; j++) 
	    {
        s.course_codes[j] = malloc (MAX * sizeof (char));
        scanf("%s", s.course_codes[j]);
        printf("\t\t\t");
        }
    printf("\n");   
    allocate_student(s);    
      
	fps=fopen(students_file,"w");
    fprintf(fps,"%d\n",nstudents);
    for(int i=0;i<nstudents;i++)
    	{
    	puttofile_student(students[i]);  
    	}
    fclose(fps); 
    return 0;
}

void puttofile_student(struct student s)
{
    fprintf(fps,"\n%s\n",s.rollno);
    fprintf(fps,"%s\n",s.name);
    fprintf(fps,"%u\n",s.branch);
    fprintf(fps,"%d\n",s.semester);
    fprintf(fps,"%d\n",s.ncourses);
    for (int j=0; j<s.ncourses; j++)  
        { 
        fprintf(fps, "%s ", s.course_codes[j]);
        }
    fprintf(fps,"\n");
        
    
}

//DELETE
int delete_student()
{	int flag=0;
	struct student s;
	char str[MAX];
	printf("\t\t\tEnter Roll No. of Student you wish to Delete:");
    scanf("%s",str);
    for (int i=0; i<nstudents; i++) 
    	{
        if(strcmp(students[i].rollno,str)==0)
        {flag=1;}
        } 
    if(flag==0) printf("\t\t\tRoll No. entered is not present to be deleted,run again\n");	
    
    if(flag==1) 
    {fps=fopen(students_file,"w");
    
    fprintf(fps,"%d\n",nstudents-1);
    for(int i=0;i<nstudents;i++)
		{
	    if(strcmp(students[i].rollno,str)==0)
	    {  ;}
	    else
	    puttofile_student(students[i]);   
		}
	printf("\t\t\tEntry deleted\n");
	}	
	return 0;
	
}

//MODIFY
int modify_student()
{
	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter Roll No. of Student you wish to Modify:");
    scanf("%s",str);
    for (int i=0; i<nstudents; i++) 
    	{
        if(strcmp(students[i].rollno,str)==0)
        {flag=1;}
        } 
    if(flag==0) printf("\t\t\tRoll No. entered is not present to be modified,run again\n");	
    
    if(flag==1)
    {
    fps=fopen(students_file,"w");
    fprintf(fps,"%d\n",nstudents);
    for(int i=0;i<nstudents;i++)
		{
	     if(strcmp(students[i].rollno,str)==0)
	     	 {
	     	 printf("\t\t\tEnter Roll No:");
	     	 scanf("%s",students[i].rollno);
	     	 printf("\t\t\tEnter Name:");
	     	 scanf("%s",students[i].name);
		  	 printf("\t\t\tEnter Branch:");
	 	 	 scanf("%u",&students[i].branch);
		 	 printf("\t\t\tEnter Semester:");
		  	 scanf("%d",&students[i].semester);
		 	 printf("\t\t\tEnter No. of Courses:");
		 	 scanf("%d",&students[i].ncourses);
    	 	 printf("\t\t\tEnter Courses:");
    	 	 students[i].course_codes = malloc (students[i].ncourses * sizeof(char *));
	     	 for (int j=0; j<students[i].ncourses; j++) 
	       	 	{
            	students[i].course_codes[j] = malloc (MAX * sizeof (char));
            	scanf("%s", students[i].course_codes[j]);
            	printf("\t\t\t");
           	 	}
	     	 puttofile_student(students[i]);
	    	 }
	     else
	     puttofile_student(students[i]);   
	   }
	}	   
	   return 0;
}


//INSTRUCTOR FUNCTION BODIES

void load_instructors() 
{
    fpi = fopen(instructors_file, "r");
    int ninstructors;
    char buf[MAX];
    struct instructor i;
    fscanf(fpi, "%d", &ninstructors);
    for (int j=0; j<ninstructors; j++) 
	{
        fgets(buf, MAX, fpi);
        fscanf(fpi, "%s", i.id);
        fscanf(fpi, "%s", i.name);
        fscanf(fpi, "%d", &i.ncoursess);
        i.courses_codes = malloc (i.ncoursess * sizeof(char *));
        for (int k=0; k<i.ncoursess; k++) 
	    	{ 
            i.courses_codes[k] = malloc (MAX * sizeof (char));
            fscanf(fpi, "%s", i.courses_codes[k]);
            }
        allocate_instructor(i);
     }
}

void allocate_instructor(struct instructor i)
{
    instructors = realloc (instructors, (ninstructors+1)*sizeof(struct instructor));
    instructors[ninstructors] = i;
    ninstructors++;
}

//DISPLAY ALL
void display_allinstructors() 
{
    printf("\n\t\t\t-----------------\n\t\t\tINSTRUCTOR DETAILS\n\t\t\t-----------------\n");
    for (int j=0; j<ninstructors; j++) 
    { 
	display_instructor(instructors[j]);
    }
}


void display_instructor(struct instructor i) 
{
    printf("\n\t\t\tID: %s\n", i.id);
    printf("\t\t\tInstructor Name: %s\n", i.name);
    printf("\t\t\tList of Courses:\n\t\t\t");
    for (int j=0; j<i.ncoursess; j++) 
    	{
        printf("%s\t", i.courses_codes[j]);
    	}
    printf("\n\n");
}

//DISPLAY ONE 
int display_oneinstructor()
{	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter Faculty ID :");
    scanf("%s",str);
    for (int l=0; l<ninstructors; l++) 
    	{
        if(strcmp(instructors[l].id,str)==0)
        {flag=1;}
        }
         
    if(flag==0)
    printf("\t\t\tID entered is not present to be displayed,run again\n");	
    
	for(int j=0;j<ninstructors;j++)
		{
	    if(strcmp(instructors[j].id,str)==0)
	    {display_instructor(instructors[j]);}
	    else 
	    {;}
	    } 
	return 0;    
}

//ADD  
int add_newinstructor()
{   
    struct instructor i;
	printf("\t\t\tEnter Faculty ID:");
	scanf("%s",i.id);
	for (int k=0; k<ninstructors; k++) 
    	{
        if(strcmp(instructors[k].id,i.id)==0)
        {printf("\t\t\tID entered is already present,run again\n");
        return 0;}
    	}
	printf("\t\t\tEnter Name:");
	scanf("%s",i.name);
	printf("\t\t\tEnter No. of Courses:");
	scanf("%d",&i.ncoursess);
    printf("\t\t\tEnter Courses:");
    i.courses_codes = malloc (i.ncoursess * sizeof(char *));
    
	for (int j=0; j<i.ncoursess; j++) 
	    {
        i.courses_codes[j] = malloc (MAX * sizeof (char));
        scanf("%s", i.courses_codes[j]);
        printf("\t\t\t");
        }
        
    printf("\n");    
        
    allocate_instructor(i);    
      
	fpi=fopen(instructors_file,"w");
    fprintf(fpi,"%d\n",ninstructors);
    for(int k=0;k<ninstructors;k++)
    	{
        puttofile_instructor(instructors[k]);  
        }
    fclose(fpi); 
    return 0; 
}

void puttofile_instructor(struct instructor i)
{
 
    fprintf(fpi,"\n%s\n",i.id);
    fprintf(fpi,"%s\n",i.name);
    fprintf(fpi,"%d\n",i.ncoursess);
    for (int j=0; j<i.ncoursess; j++)  
        { 
        fprintf(fpi, "%s ", i.courses_codes[j]);
        }
    fprintf(fpi,"\n");
    
}

//DELETE 
int delete_instructor()
{	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter ID of Faculty you wish to Delete:");
    scanf("%s",str);
    for (int l=0; l<ninstructors; l++) 
    	{
        if(strcmp(instructors[l].id,str)==0)
        {flag=1;}
        }
         
    if(flag==0)
    printf("\t\t\tID entered is not present to be deleted,run again\n");	
    
    if(flag==1)
    {
    fpi=fopen(instructors_file,"w");
    fprintf(fpi,"%d\n",ninstructors-1);
    for(int j=0;j<ninstructors;j++)
		{
	    if(strcmp(instructors[j].id,str)==0)
	    {  ;}
	    else
	    puttofile_instructor(instructors[j]);   
	    }
	}
	return 0;
}

//MODIFY 
int modify_instructor()
{	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter ID of Faculty you wish to Modify:");
    scanf("%s",str);
    for (int l=0; l<ninstructors; l++) 
    	{
        if(strcmp(instructors[l].id,str)==0)
        {flag=1;}
        }
         
    if(flag==0)
    printf("\t\t\tID entered is not present to be modified,run again\n");	
    if(flag==1)
    {
    fpi=fopen(instructors_file,"w");
    fprintf(fpi,"%d\n",ninstructors);
    for(int j=0;j<ninstructors;j++)
		{
	    if(strcmp(instructors[j].id,str)==0)
	    	{
	    	printf("\t\t\tEnter ID:");
	    	scanf("%s",instructors[j].id);
	    	printf("\t\t\tEnter Name:");
	     	scanf("%s",instructors[j].name);
		 	printf("\t\t\tEnter No. of Courses:");
	     	scanf("%d",&instructors[j].ncoursess);
         	printf("\t\t\tEnter Courses:");
    	 	instructors[j].courses_codes = malloc (instructors[j].ncoursess * sizeof(char *));
		 	for (int k=0; k<instructors[j].ncoursess; k++) 
	    		{	
            	instructors[j].courses_codes[k] = malloc (MAX * sizeof (char));
            	scanf("%s", instructors[j].courses_codes[k]);
            	printf("\t\t\t");
        		}
    	 	printf("\n");    
	     	puttofile_instructor(instructors[j]);
	    	}
	    else
	    puttofile_instructor(instructors[j]);   
	   }
	}
	return 0;
}


//COURSE FUNCTION BODIES

void load_courses() 
{
    fpc = fopen(courses_file, "r");
    int ncoursesss;
    char buf[MAX];
    struct course c;
    fscanf(fpc, "%d", &ncoursesss);
    for (int j=0; j<ncoursesss; j++) 
		{
        fgets(buf, MAX, fpc);
        fscanf(fpc, "%s", c.code);
        fscanf(fpc, " %[^\n]s", c.name);
        fscanf(fpc, "%d", &c.credits);
        fscanf(fpc,"%d",&c.ninstructors);
        c.instructor_ids = malloc (c.ninstructors * sizeof(char *));
        for (int j=0; j<c.ninstructors; j++) 
        	{
            c.instructor_ids[j] = malloc (MAX * sizeof (char));
            fscanf(fpc, "%s", c.instructor_ids[j]);
        	}
        fscanf(fpc,"%d",&c.nstudents);
        c.student_rollnos = malloc (c.nstudents * sizeof(char *));
        for (int j=0; j<c.nstudents; j++) 
			{
            c.student_rollnos[j] = malloc (MAX * sizeof (char));
            fscanf(fpc, "%s", c.student_rollnos[j]);
        	}
        allocate_course(c);
    	}
}   
 
void allocate_course(struct course c)
{
    courses = realloc (courses, (ncourses+1)*sizeof(struct course));
    courses[ncourses] = c;
    ncourses++;
}   

//DISPLAY ALL
void display_allcourses() 
{
    printf("\n\t\t\t-----------------\n\t\t\tCOURSE DETAILS\n\t\t\t-----------------\n");
    for (int i=0; i<ncourses; i++) 
    	{
        display_course(courses[i]);
    	}
}

void display_course(struct course c) 
{
    printf("\n\t\t\tCourse Code: %s\n", c.code);
    printf("\t\t\tName of Course: %s\n", c.name);
    printf("\t\t\tCredits: %d\n", c.credits);
    printf("\t\t\tList of Faculties for Course:\n\t\t\t");
    for (int i=0; i<c.ninstructors; i++) 
    	{
        printf("%s\t", c.instructor_ids[i]);
    	}
    printf("\n\t\t\tList of Students taking the Course:\n\t\t\t");
    for (int i=0; i<c.nstudents; i++) 
    	{
        printf("%s\t", c.student_rollnos[i]);
    	}
    printf("\n\n");
}

//DISPLAY ONE
int display_onecourse()
{	
	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter Course Code :");
    scanf("%s",str);
    for (int l=0; l<ncourses; l++) 
    	{
        if(strcmp(courses[l].code,str)==0)
        {flag=1;}
        }
         
    if(flag==0)
    printf("\t\t\tCourse Code entered is not present to be displayed,run again\n");	
    
	for(int j=0;j<ncourses;j++)
	   {
	   if(strcmp(courses[j].code,str)==0)
	   {	display_course(courses[j]);		}
	   else 
	   {;}
	   }
	return 0;
}

//ADD
int add_newcourse()
{  
    struct course c;
	printf("\t\t\tEnter Course Code:");
	scanf("%s",c.code);
	for (int k=0; k<ncourses; k++) 
    	 {
         if(strcmp(courses[k].code,c.code)==0)
         {printf("\t\t\tCourse entered is already present,run again\n");
         return 0;}
    	 }
	printf("\t\t\tEnter Course Name:");
	scanf(" %[^\n]s",c.name);
	printf("\t\t\tEnter Credits:");
	scanf("%d",&c.credits);
	printf("\t\t\tEnter No. of Faculties for Course:");
	scanf("%d",&c.ninstructors);
    printf("\t\t\tEnter Faculty Names:\n\t\t\t");
    c.instructor_ids = malloc (c.ninstructors  * sizeof(char *));
	for (int j=0; j<c.ninstructors ; j++) 
	    	{
            c.instructor_ids[j] = malloc (MAX * sizeof (char));
            scanf("%s", c.instructor_ids[j]);
            printf("\t\t\t");
        	}
    printf("\n");   
    
    printf("\t\t\tEnter No. of Students taking the Course:");
	scanf("%d",&c.nstudents);

    printf("\t\t\tEnter Student Roll Nos. :\n\t\t\t");
    c.student_rollnos = malloc (c.nstudents  * sizeof(char *));
	for (int l=0; l<c.nstudents  ; l++) 
	    	{
            c.student_rollnos[l] = malloc (MAX * sizeof (char));
            scanf("%s", c.student_rollnos[l]);
            printf("\t\t\t");
        	}
    printf("\n");   
    
    allocate_course(c);    
      
	fpc=fopen(courses_file,"w");
    fprintf(fpc,"%d\n",ncourses);
    for(int i=0;i<ncourses;i++)
     		{
     		puttofile_course(courses[i]);  
     		}
    fclose(fpc);  
    return 0;
}

void puttofile_course(struct course c)
{
 
    fprintf(fpc,"\n%s\n",c.code);
    fprintf(fpc,"%s\n",c.name);
    fprintf(fpc,"%d\n",c.credits);
    fprintf(fpc,"%d\n",c.ninstructors);
    for (int j=0; j<c.ninstructors; j++)  
        { 
        fprintf(fpc, "%s ", c.instructor_ids[j]);
        }  
    fprintf(fpc,"%d\n",c.nstudents);
    for (int j=0; j<c.nstudents; j++)  
        { 
        fprintf(fpc, "%s ", c.student_rollnos[j]);
        }
	fprintf(fpc,"\n");        
}

//DELETE
int delete_course()
{	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter Code of Course you wish to Delete:");
    scanf("%s",str);
    for (int l=0; l<ncourses; l++) 
    	{
        if(strcmp(courses[l].code,str)==0)
        {flag=1;}
        }
         
    if(flag==0)
    printf("\t\t\tCourse Code entered is not present to be deleted,run again\n");	
    
    if(flag==1)
    {
    fpc=fopen(courses_file,"w");
    fprintf(fpc,"%d\n",ncourses-1);
    for(int i=0;i<ncourses;i++)
	  {
	  if(strcmp(courses[i].code,str)==0)
	  {  ;}
	  else
	  puttofile_course(courses[i]);   
	  }
	printf("\t\t\tEntry deleted\n");  
	}
	return 0;	  
}

//MODIFY
int modify_course()
{
	int flag=0;
	char str[MAX];
	printf("\t\t\tEnter Code of Course you wish to Modify:");
    scanf("%s",str);
    
    for (int l=0; l<ncourses; l++) 
    	{
        if(strcmp(courses[l].code,str)==0)
        {flag=1;}
        }
         
    if(flag==0)
    printf("\t\t\tCourse Code entered is not present to be modified,run again\n");	
    
    if(flag==1)
    {
    fpc=fopen(courses_file,"w");
    fprintf(fpc,"%d\n",ncourses);
    for(int i=0;i<ncourses;i++)
	  {
	   if(strcmp(courses[i].code,str)==0)
	     {
	     printf("\t\t\tEnter Course Code:");
		 scanf("%s",courses[i].code);
	     printf("\t\t\tEnter Course Name:");
		 scanf(" %[^\n]s",courses[i].name);
		 printf("\t\t\tEnter Credits:");
		 scanf("%d",&courses[i].credits);
		 printf("\t\t\tEnter No. of Faculties for Course:");
		 scanf("%d",&courses[i].ninstructors);
    	 printf("\t\t\tEnter Faculty Names:\n\t\t\t");
    	 courses[i].instructor_ids = malloc (courses[i].ninstructors  * sizeof(char *));
		 for (int j=0; j<courses[i].ninstructors ; j++) 
	    	{
            courses[i].instructor_ids[j] = malloc (MAX * sizeof (char));
            scanf("%s", courses[i].instructor_ids[j]);
            printf("\t\t\t");
        	}
    	 printf("\n");   
    
    	 printf("\t\t\tEnter No. of Students taking the Course:");
		 scanf("%d",&courses[i].nstudents);
    	 printf("\t\t\tEnter Student Roll Nos. :\n\t\t\t");
    	 courses[i].student_rollnos = malloc (courses[i].nstudents  * sizeof(char *));
		 for (int l=0; l<courses[i].nstudents  ; l++) 
	    	{
            courses[i].student_rollnos[l] = malloc (MAX * sizeof (char));
            scanf("%s", courses[i].student_rollnos[l]);
            printf("\t\t\t");
        	}
    	 printf("\n");   
	     puttofile_course(courses[i]);
	     }
	     else
	     puttofile_course(courses[i]);   
	  }
	  
	}
	return 0;	  
}