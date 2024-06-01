All the program can be compiled using Makefile with command "make all"

P11.c -> Finds the number of total subsets with sum equal to the value entered by the user. User also has to enter name of the file as input to read the data.
The program finds total number of subsets in the program and then computes the sum of all these subsets. If the sum of subset is found to be equal to the 
desired sum, then the count is incremented.The final count is then displayed to the screen along with the total time taken. The Brute force approach takes
around 3500 ms to find the count.

P12.c ->  Finds the number of total subsets with sum equal to the value entered by the user. User also has to enter name of the file as input to read the 
data.The program creates a state space tree to solve this problem. Here every tree branch is scanned until we reach the end of branch or we find the desired
sum or we have already gone higher than the desired sum. If going to a certain branch meets the sum, then the count is increment otherwise the numbers of 
deadends are incremented. Finally the program outputs total number of deadends and total count computed to the screen along with the time taken. The time
taken to compute this subset problem count is arounf 200 ms with this approach.

P21.c -> Program solves the Job assignment problem using the brute force approach. User has to enter the name of the file as input the read the data. The 
program finds the total number of possible job assignments and then compare the value amount for each set created. One the set with maximum value is found,
program prints to the screen final results containing the maximum value created and Person job assignment selected. Time taken to assign the jobs using 
brute force appraoch is also printed to the screen, which is around 30,000 ms. 

P22.c -> Program solve the job assignment problem using the Branch and Bound approach. User has to enter the name of the file as input to read the data. The
program creates the job search tree by computing the maximum bound created by assigning the job to a individual. This approach gives a much faster result
than the brute force approach with creates a high value but the job assignment may/may not be ideal. The program prints the person job assignment seleted 
to the screen along with the time taken which is around 20ms. 
