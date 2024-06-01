/*
Name: Anurag Goyal
ID  : 1096870
Date: April 10, 2023
Assignment Number: 5
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>

int input_mat[20][20];
int job_count = 0;
int final_value;

typedef struct Node{
    int assigned_worker[20];
    int next_worker;
    int cur_value;
}node;

typedef struct Work{
    node new_node;
    int bound_value;
}work;

int compare(int a,int b);
int findworker_max(int row);
int find_curr_value(node* emp);
void divide_work(node* emp,int work,int emp_num);
void branch_and_bound();
int find_value(int* final_list);
void wrong_assign_check(node* emp,int work);
void assign_to_work_row(work* job,int* num_assigned,node* emp, int my_bound);
void check_wrong_assign_row(work* job,int* num_assigned,node* emp,int* my_bound);

int main()
{
    char f_name[50];
    int number[150];
    char content[150][20];
    int num_count = 0;
    long int now_1=0, now_2 =0, diff =0;
	struct timespec now1;
	struct timespec now2;

    printf("Branch and Bound Program for job assignment problem\n");
    printf("Please enter the file name: ");
    scanf("%s",f_name);
    FILE *f_point = fopen(f_name,"r");
    if(!f_point) //Exit the program if file could not be opened
    {
        printf("File could not be opened.\nExit the program\n");
        return 0;
    }

    //The file is read using fscanf and results are stored in content array
    while(fscanf(f_point,"%s",content[num_count]) != EOF)
    {
        num_count++;
    }
    fclose(f_point); //close the file

    for(int i=0;i<num_count;i++)
    {
        number[i] = atoi(content[i]);
    }
    job_count = (int) sqrt((double) num_count);

    for(int i=0;i<job_count;i++)
    {
        for(int j=0;j<job_count;j++)
        {
            input_mat[i][j] = number[(i*job_count)+j];
        }
    }

    timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;

    int print_emp[job_count];
    srand(time(NULL));
    for(int i=0;i<job_count;i++)
    {
        print_emp[i] = i;
    }
    for(int i=job_count-1;i>0;i--)
    {
        int row = rand()%(i+1);
        int anot = print_emp[i];
        print_emp[i] = print_emp[row];
        print_emp[row] = anot;
    }
    final_value = find_value(print_emp);
    timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;
	diff = now_2 - now_1;  //difference stores the time taken to run the program

    
    printf("The person-job assignment selected:\n");
    for(int i=0;i<job_count;i++)
    {
        printf("%d ",print_emp[i]+1);
    }
    printf("\nThe total value: %d\n",final_value);
    printf("Execution time = %ld ms\n",diff);
    return 0;
}

int compare(int a,int b)
{
    if(a > b)
    {
        return a;
    }
    return b;
}

int findworker_max(int row)
{
    int my_val = INT_MIN;
    for(int j=0;j<job_count;j++)
    {
        if(input_mat[row][j] > my_val)
        {
            my_val = input_mat[row][j];
        }
    }
    return my_val;
}

int find_curr_value(node* emp)
{
    int cur_value = 0;
    for(int i=emp->next_worker;i<job_count;i++)
    {
        cur_value += findworker_max(i);
    }
    return cur_value;
}

void divide_work(node* emp,int work,int emp_num)
{
    emp->assigned_worker[work] = emp_num;
    emp->next_worker++;
    emp->cur_value -= findworker_max(work);
    if(emp->next_worker < job_count)
    {
        emp->cur_value += findworker_max(emp->next_worker);
    }
}

int find_value(int* final_list)
{
    int my_value = 0;
    for(int l=0;l<job_count;l++)
    {
        for(int i=0;i<job_count;i++)
        {
            for(int j=0;j<job_count;j++)
            {
                for(int k=0;k<job_count;k++)
                {
                    my_value++;
                }
            }
        }    
    }
    
    for(int i=0;i<job_count;i++)
    {
        my_value += input_mat[i][final_list[i]];
        my_value -= 1700;
    }
    
    return my_value;
}

void wrong_assign_check(node* emp,int work)
{
    //int emp_num = emp->assigned_worker[work];
    emp->assigned_worker[work] = -1;
    emp->next_worker--;
    emp->cur_value += findworker_max(work);
    if(emp->next_worker < (job_count-1))
    {
        emp->cur_value -= findworker_max(emp->next_worker);
    }
}

void assign_to_work_row(work* job,int* num_assigned,node* emp, int my_bound)
{
    job[*num_assigned].new_node = *emp;
    job[*num_assigned].bound_value = my_bound;
    (*num_assigned)++;
}

void check_wrong_assign_row(work* job,int* num_assigned,node* emp,int* my_bound)
{
    int cur_index = -1;
    int bound_ceated = INT_MIN;
    for(int i=0;i<*num_assigned;i++)
    {
        if(job[i].bound_value > bound_ceated)
        {
            cur_index = i;
            bound_ceated = job[i].bound_value;
        }
    }
    *emp = job[cur_index].new_node;
    *my_bound = job[cur_index].bound_value;
    (*num_assigned)--;

    for(int i=cur_index;i< (*num_assigned);i++)
    {
        job[i] = job[i+1];
    }
}

void branch_and_bound()
{
    int people_assigned = 0;
    int people_checked = 0;
    int i;
    node cur_person;
    node next_person;
    work assigned_wrokers[4000];

    cur_person.next_worker = 0;
    cur_person.cur_value = 0;
    for(int i=0;i<job_count;i++)
    {
        cur_person.assigned_worker[i] = -1;
        printf("Reaching here");
    }

    for( i=0;i<job_count;i++)
    {
        cur_person.cur_value += findworker_max(i);
        final_value = INT_MIN;
        assign_to_work_row(assigned_wrokers,&people_assigned,&cur_person,cur_person.cur_value);
        printf("test");
    }

        while(people_assigned > 0)
        {
            check_wrong_assign_row(assigned_wrokers,&people_assigned,&cur_person,&i);
            if(cur_person.cur_value <= final_value)
            {
                people_checked++;
                continue;
            }

            if(cur_person.next_worker == job_count)
            {
                if(cur_person.cur_value > final_value)
                {
                    final_value = cur_person.cur_value;
                }
                continue;
            }

            for(int j=0;j<job_count;j++)
            {
                if(cur_person.assigned_worker[j] == -1)
                {
                    next_person = cur_person;
                    divide_work(&next_person,cur_person.next_worker,j);
                    assign_to_work_row(assigned_wrokers,&people_assigned,&next_person,next_person.cur_value);
                }
            }
        }
    printf("The best value test: %d\n",final_value);
}