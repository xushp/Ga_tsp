//////////////////////////////////////////////////////////////
//
//	FileName : Chromosome_Tsp.cpp 
//	Creator : xsp
//	Date : 2015-04-10
//	Comment : �����Ŵ��㷨�У�tsp���������࣬Ⱦɫ���Լ���ز���
//			  ����ʵ�ֵ��ļ�
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
// �������� Ĭ��10��
int Chromosome_Tsp::city_cnt = 10;
Map_type Chromosome_Tsp::Map;
/****************************************
 *	��ʼ����Ⱥ
 * @popsize: ��Ⱥ����
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
 * �������
 *@remark:	������������������Ⱦɫ����н���
 *			��ѡȡ������Ӧ����õ�Ⱦɫ��������
 *			�����з���
 */
void Chromosome_Tsp::cross(Chromosome_Tsp& chrom1, Chromosome_Tsp& chrom2){
	// ѡ�����������
	int crossp1 = rand()%city_cnt;
	int crossp2 = 0;
	// ��������������һ�ڶ����Ⱦɫ��
	std::vector<Chromosome_Tsp> tmpArr;
	tmpArr.push_back(chrom1);
	tmpArr.push_back(chrom2);
	do {
		crossp2 = rand()%city_cnt;
	}while (crossp1 == crossp2);
	if (crossp1 > crossp2)
		std::swap(crossp1, crossp2);
	for (int i = crossp1; i <= crossp2; ++i)
	{
		if (chrom1.genes[i] != chrom2.genes[i]){
			std::vector<int>::iterator it = std::find(chrom2.genes.begin(), chrom2.genes.end(), chrom1.genes[i]);
			*it = chrom2.genes[i];
			it = std::find(chrom1.genes.begin(), chrom1.genes.end(), chrom2.genes[i]);
			*it = chrom1.genes[i];
			std::swap(chrom1.genes[i], chrom2.genes[i]);
		}
	}
	// ������Ҳ��ȥ
	tmpArr.push_back(chrom1);
	tmpArr.push_back(chrom2);

	
	// ���һ�ڶ�����Ӧ�ȵ�Ⱦɫ��
	chrom1 = tmpArr[0];
	chrom2 = tmpArr[1];
	if (chrom1 < chrom2)
		std::swap(chrom1, chrom2);
	for (size_t i = 2; i < tmpArr.size(); ++i)
	{
		if (chrom1 < tmpArr[i]){
			chrom2 = chrom1;
			chrom1 = tmpArr[i];
		}
		else if(chrom2 < tmpArr[i])
			chrom2 = tmpArr[i];
	}
}

/****************************************
 * �������
 *@remark: �Ի����죬ѡȡ��������㣬������Ӧ�û���				
 */
void Chromosome_Tsp::mutate(Chromosome_Tsp& chrom){
	Chromosome_Tsp pre = chrom;
	int index1 = rand()%city_cnt;
	int index2 = 0;
	do {
		index2 = rand()%city_cnt;
	}while(index2 == index1);
	std::swap(chrom.genes[index1], chrom.genes[index2]);
	chrom = std::max(pre, chrom);
}
/****************************************
 * ��ʼ����ͼ����
 */
Map_type Chromosome_Tsp::init_map(int city_cnt){
	Map_type map(city_cnt, std::vector<double>(city_cnt));
	for (int i = 0; i < city_cnt; ++i)
		for (int j = i+1; j < city_cnt; ++j)
			map[i][j] = map[j][i] = rand()*1.0/RAND_MAX * 100;
	return map;
}

/****************************************
 * ����Ⱦɫ�����Ӧ��
 */
double Chromosome_Tsp::fitness()const{
	return 1.0/pathlength();
}
/****************************************
 * ·������
 */
double Chromosome_Tsp::pathlength()const{
	double ret = 0.0;
	for (int i = 0; i < Chromosome_Tsp::city_cnt-1; i++)
		ret += Chromosome_Tsp::Map[this->genes[i]][this->genes[i+1]];
	return ret;
}

bool Chromosome_Tsp::operator<(const Chromosome_Tsp &chrom)const{
	return this->fitness() < chrom.fitness();
}

std::ostream& operator<<(std::ostream &out, Chromosome_Tsp &chrom){
	for (size_t i = 0; i < chrom.genes.size()-1; ++i)
		out << chrom.genes[i] << ' ';
	out << chrom.genes[chrom.genes.size()-1];
	return out;
}