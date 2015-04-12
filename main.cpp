#include "GA.h"
#include "Chromosome_Tsp.h"
#include <time.h>
#include <iostream>
#define CITY_CNT	5
#define CROSS_RATE	0.8
#define MUTATE_RATE	0.05
int main()
{
	srand(time(0));

	Chromosome_Tsp::Map = Chromosome_Tsp::init_map(CITY_CNT);
	Chromosome_Tsp::city_cnt = CITY_CNT;
	
	for (int i = 0; i < CITY_CNT; ++i)
	{
		for (int j = 0; j < CITY_CNT; ++j)
			std::cout << Chromosome_Tsp::Map[i][j] << '\t';
		std::cout << std::endl;
	}
	std::cout << std::endl;
	GA<Chromosome_Tsp>::test(5);
    GA<Chromosome_Tsp>::algorithm_action(5, CROSS_RATE,MUTATE_RATE, 5);
	
	std::getchar();
	return 0;
}