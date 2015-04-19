//////////////////////////////////////////////////////////////
//
//	FileName : Chromosome_Tsp.h 
//	Creator : xsp
//	Date : 2015-04-09
//	Comment : 基因遗传算法中，tsp问题的相关类，染色体以及相关操作
//
//////////////////////////////////////////////////////////////
#ifndef CHROMOSOME_TSP_H
#define CHROMOSOME_TSP_H
#include <vector>

typedef std::vector<std::vector<double> >	Map_type;

class Chromosome_Tsp{
public:

	// 构造函数
	Chromosome_Tsp();
	// 适应度计算
	double fitness() const;
	// 路径长度
	double pathlength() const;
	// 比较操作符
	bool operator < (const Chromosome_Tsp &chrom) const;
	friend std::ostream& operator << (std::ostream & out, Chromosome_Tsp&);
	// 每条染色体的基因
	std::vector<int>	genes;
	//////////////////////////////////////
	// 静态成员变量
	//
	// 初始化地图
	static Map_type init_map(int city_cnt);		
	// 初始化种群
	static void initPopulation(int popSize, std::vector<Chromosome_Tsp> &pop);
	// 种群交叉操作
	static void popCross(std::vector<Chromosome_Tsp> &pop, double p_cross);
	// 交叉操作
	static void cross(Chromosome_Tsp& chrom1, Chromosome_Tsp& chrom2);
	// 变异操作
	static void mutate(Chromosome_Tsp& chrom);
	static int city_cnt;
	static Map_type Map;
private:
};

#endif