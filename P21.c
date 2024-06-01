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
int current_assigned[20];
int final_assigned[20];
int max_value_created = 0;

void assign_jobs(int cur_value,int cur_empl);
int calc_fact(int total_pos_ass,int job_count);

int main()
{
    char f_name[50];
    int number[150];
    char content[150][20];
    int num_count = 0;
    long int now_1=0, now_2 =0, diff =0;
	struct timespec now1;
	struct timespec now2;
    int total_pos_ass = 1;

    printf("Brute Force Program for job assignment problem\n");
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

    for(int i=0;i<job_count;i++)
    {
        current_assigned[i] = -1;
    }
    assign_jobs(0,0);
    total_pos_ass = calc_fact(total_pos_ass,job_count);

    timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;
	diff = now_2 - now_1;  //difference stores the time taken to run the program

    printf("Number of all the possible assignments: %d\n",total_pos_ass);
    printf("The person-job assignment selected:\n");
    for(int i=0;i<job_count;i++)
    {
        printf("%d ",final_assigned[i]+1);
    }
    printf("\nThe total value: %d\n",max_value_created);
    printf("Execution time = %ld ms\n",diff);
    return 0;
}

void assign_jobs(int cur_value,int cur_empl)
{
    if(cur_empl == job_count)
    {
        if(cur_value > max_value_created)
        {
            max_value_created = cur_value;
            for(int i=0;i<job_count;i++)
            {
                final_assigned[i] = current_assigned[i];
            }
        }
        return;
    }

    for(int i=0;i<job_count;i++)
    {
        if(current_assigned[i] == -1)
        {
            current_assigned[i] = cur_empl;
            assign_jobs(cur_value+input_mat[cur_empl][i],cur_empl+1);
            current_assigned[i] = -1;
        }
    }

    if(cur_value <= max_value_created)
    {
        return;
    }
}

//Function returns the total number of possible assignment
int calc_fact(int total_pos_ass,int job_count)
{
    for(int i=1;i<=job_count;i++)
    {
        total_pos_ass = total_pos_ass*i;
    }
    return total_pos_ass;
}