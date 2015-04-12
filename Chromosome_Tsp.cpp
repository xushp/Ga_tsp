//////////////////////////////////////////////////////////////
//
//	FileName : Chromosome_Tsp.cpp 
//	Creator : xsp
//	Date : 2015-04-10
//	Comment : 基因遗传算法中，tsp问题的相关类，染色体以及相关操作
//			  这是实现的文件
//
//////////////////////////////////////////////////////////////
#include "Chromosome_Tsp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

void init_map(){
}
Chromosome_Tsp::Chromosome_Tsp(){

}
// 城市数量 默认10个
int Chromosome_Tsp::city_cnt = 10;
Map_type Chromosome_Tsp::Map;
/****************************************
 *	初始化种群
 * @popsize: 种群数量
 */
void Chromosome_Tsp::initPopulation(int popSize, std::vector<Chromosome_Tsp> &pop){
	int *arr = new int[Chromosome_Tsp::city_cnt];
	for (int i = 0; i < Chromosome_Tsp::city_cnt; i++)
		arr[i] = i;

	for (int i = 0; i < popSize; ++i){
		Chromosome_Tsp chrom;
		for (int j = Chromosome_Tsp::city_cnt; j > 1; j--){
			int rndNum = rand() % j;
			chrom.genes.push_back(arr[rndNum]);
			std::swap(arr[rndNum], arr[j-1]);
		}
		chrom.genes.push_back(arr[0]);
		pop.push_back(chrom);
	}
	delete []arr;
}
/****************************************
 * 初始化地图数据
 */
Map_type Chromosome_Tsp::init_map(int city_cnt){
	Map_type map(city_cnt, std::vector<double>(city_cnt));
	for (int i = 0; i < city_cnt; ++i)
		for (int j = i+1; j < city_cnt; ++j)
			map[i][j] = map[j][i] = rand()*1.0/RAND_MAX * 100;
	return map;
}

/****************************************
 * 计算染色体的适应度
 */
double Chromosome_Tsp::fitness()const{
	double ret = 0.0;
	for (int i = 0; i < Chromosome_Tsp::city_cnt-1; i++)
		ret += Chromosome_Tsp::Map[this->genes[i]][this->genes[i+1]];
	return 1.0/ret;
}

bool Chromosome_Tsp::operator<(const Chromosome_Tsp &chrom)const{
	return this->fitness() < chrom.fitness();
}