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

int count_subset_sum(int* number,int line_count,int target_sum,int num_subset);

//driver function of the code
int main()
{
    char f_name[50];
    int target_sum;
    int number[25];
    char content[30][20];
    long int now_1=0, now_2 =0, diff =0;
	struct timespec now1;
	struct timespec now2;

    printf("Brute Force Program for subset sum problem\n");
    printf("Please enter the file name and the subset sum: ");
    scanf("%s %d",f_name,&target_sum);

    FILE *f_point = fopen(f_name,"r");
    if(!f_point) //Exit the program if file could not be opened
    {
        printf("File could not be opened.\nExit the program\n");
        return 0;
    }

    int line_count = 0;
    //read the file and store the file data in content array
    while(fscanf(f_point,"%s",content[line_count]) != EOF)
    {
        line_count++;
    }
    fclose(f_point);

    //content array is converted to type int from type string
    for(int i=0;i<line_count;i++)
    {
        number[i] = atoi(content[i]);
    }

    timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;

    int num_subset = (int)pow(2,(double)line_count);  //calculate total number of possible subsets
    //Function is called to count the target count
    int target_count = count_subset_sum(number,line_count,target_sum,num_subset);
    
    timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;
	diff = now_2 - now_1;  //difference stores the time taken to run the program

    printf("\nNumber of all the subsets: %d \n",num_subset);
    if(target_sum == 0)
    {
        target_count = 0;
    }
    printf("Number of subset whose sum is %d: %d\n",target_sum,target_count);
    printf("Time for finding the maximum number: %ld ms\n",diff);
    return 0;
}

//Function return the total count of subsets with sum equal to the target sum
int count_subset_sum(int* number,int line_count,int target_sum,int num_subset)
{   
    int target_count = 0;

    for(int i=0;i<num_subset;i++)  //take all the possible subsets from the subset array
    {
        int sub_sum = 0;
        for(int j=0;j<line_count;j++)  //Iterate throught the elements of the subset
        {
            int check = (1 << j);
            check = check & i;
            if(check != 0)  //check if subset has a valid length to get the next element
            {
                sub_sum = sub_sum + number[j];
            }
        }
        //the calculated sum of each subset is compared to the target sum
        if(sub_sum == target_sum)
        {
            target_count++;
        }
    }
    return target_count;
}