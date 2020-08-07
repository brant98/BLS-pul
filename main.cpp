#include <iostream>
#include <ctime>
#include"test_bls.h"
int main()
{
	clock_t start, finish;//计算运行时间用
	start = clock();
	for (int i = 0; i < 1000; i++)
	{

		test_bls();
	}
	finish = clock();
	printf("Test of this algorithm finished\n");
	printf("Start at  %f s\n", (double)start / CLOCKS_PER_SEC);
	printf("End at %f s\n", (double)finish / CLOCKS_PER_SEC);
	printf("1000 times tests  used %f seconds in total.\n", (double)difftime(finish, start) / CLOCKS_PER_SEC);
	printf("The algorithm runs once used %f seconds on average.\n", (double)difftime(finish, start) / CLOCKS_PER_SEC / 1000);
		return 0;


}