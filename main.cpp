#include "GA.h"
#include "Chromosome_Tsp.h"
#include <time.h>
#include <iostream>
#define CITY_CNT	20			// 城市数量
#define CROSS_RATE	1			// 交叉率
#define MUTATE_RATE	0.5			// 变异率
#define GENERATIONS	150			// 遗传代数
#define POPSIZE		50			// 种群大小
int main()
{/*
	double arr[] = {1,3, 2, 0};
	int a1 = arr[0];
	int a2 = arr[1];
	if (a1 < a2)
		std::swap(a1, a2);
	for (int i = 2; i < 4; i++)
	{
		if (a1 < arr[i]){
			a1 = arr[i];
			a2 = a1;
		} else if (a2 < arr[i])
			a2 = arr[i];
	}
	std::cout << a1 << ", " << a2 << std::endl;
	std::getchar();
	return 0;*/
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
	std::vector<std::vector<Chromosome_Tsp> > allpopulation =  GA<Chromosome_Tsp>::algorithm_action(GENERATIONS, CROSS_RATE,MUTATE_RATE, POPSIZE);
	GA<Chromosome_Tsp>::statistic(allpopulation);
	//GA<Chromosome_Tsp>::test(POPSIZE);
	std::getchar();
	return 0;
}