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

void sort_my_array(int* number,int start,int stop);
void merge_call(int* number,int start,int mid,int stop);
void count_result(int number[], int n, int target, int curr_sum, int tree_level, int next_node[], int *deadends,int *target_count);

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
    int deadends = 0;
    int target_count = 0;

    printf("Backtracking Program for subset sum problem\n");
    printf("Please enter the file name and the subset sum: ");
    scanf("%s %d",f_name,&target_sum);

    FILE *f_point = fopen(f_name,"r");
    if(!f_point) //Exit the program if file could not be opened
    {
        printf("File could not be opened.\nExit the program\n");
        return 0;
    }

    int line_count = 0;
    //The file is read using fscanf and results are stored in content array
    while(fscanf(f_point,"%s",content[line_count]) != EOF)
    {
        line_count++;
    }
    fclose(f_point); //close the file

    //The string array is converted into integers
    for(int i=0;i<line_count;i++)
    {
        number[i] = atoi(content[i]);
    }

    timespec_get( &now1, TIME_UTC );
	now_1 = ((long int) now1.tv_sec) * 1000 + ((long int) now1.tv_nsec)/1000000;
    
    sort_my_array(number,0,line_count-1); //Call the function to sort the input array read from the file
    int next_node[line_count];            //Create an array to keep count of the node level selected
    for (int i = 0; i < line_count; i++) 
    {
        next_node[i] = 0;
    }
    //Count the result for deadends and total count in the function
    count_result(number,line_count,target_sum,0,0,next_node,&deadends,&target_count);

    timespec_get( &now2, TIME_UTC );
	now_2 = ((long int) now2.tv_sec) * 1000 + ((long int) now2.tv_nsec)/1000000;
	diff = now_2 - now_1;  //difference stores the time taken to run the program

    printf("\nNumber of dead ends: %d \n",deadends);
    printf("Number of subset whose sum is %d: %d\n",target_sum,target_count);
    printf("Time for finding the maximum number: %ld ms\n",diff);
    return 0;
}

//Function counts the number of deadends and successful sum counts
void count_result(int number[], int n, int target, int curr_sum, int tree_level, int next_node[], int *deadends,int* target_count) 
{
    //if the current sum of nodes is equal to target, increment the target count
    if (curr_sum== target) 
    { 
        (*target_count)++; 
        return;  //backtrack since we already found the set
    }
    //if we have reached the end of the tree or sum is already higher than target, increment deadend
    if (tree_level == n || curr_sum > target) 
    {
        (*deadends)++; 
        return; //backtrack since we already hit a deadend
    }
    next_node[tree_level] = 1; //Set flag to 1 when including the next node level in the sum
    count_result(number, n, target, curr_sum + number[tree_level], tree_level + 1, next_node, deadends,target_count);
    next_node[tree_level] = 0;//Set flag to 0 when not including the next node level in the sum
    count_result(number, n, target, curr_sum, tree_level + 1, next_node, deadends,target_count);
}

//Function is used to sort the array using Merge Sort approach
void sort_my_array(int* number,int start,int stop)
{
    if(start < stop)
    {
        int mid = ((start + stop)/2);
        sort_my_array(number,start,mid);
        sort_my_array(number,mid+1,stop);
        merge_call(number,start,mid,stop);
    }
}

//Sort_Array dunction uses this sub funciton to divide the array and merge the sorted array
void merge_call(int* number,int start,int mid,int stop)
{
    int num1 = mid - start + 1;
    int num2 = stop - mid;
    int Left[num1];
    int Right[num2];

    for(int i=0;i<num1;i++)
    {
        Left[i] = number[start+i];
    }
    for(int i=0;i<num2;i++)
    {
        Right[i] = number[mid+1+i];
    }

    int i = 0;
    int j = 0;
    int k = start;

    while(i < num1 && j < num2)
    {
        if(Left[i] <= Right[j])
        {
            number[k] = Left[i];
            i++;
        }
        else
        {
            number[k] = Right[j];
            j++;
        }
        k++;
    }

    while(i < num1)
    {
        number[k] = Left[i];
        i++;
        k++;
    }
    while(j < num2)
    {
        number[k] = Right[j];
        k++;
        j++;
    }   
}