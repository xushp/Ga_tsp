//////////////////////////////////////////////////////////////
//
//	FileName : GA.h 
//	Creator : xsp
//	Date : 2015-04-09
//	Comment : 基因遗传算法的实现类
//
//////////////////////////////////////////////////////////////
#ifndef GA_H
#define GA_H
#include "Chromosome_Tsp.h"

template <typename Chromosome_type>
class GA{
public:
	typedef std::vector<Chromosome_type> Chromosome;
	static void test(int popSize);
	static void algorithm_init(int genetic_genelations, double p_cross, double p_mutate, Chromosome chromosomes);
	static Chromosome_type algorithm_action(int genetic_genelations, double p_cross, double p_mutate, int popSize);
private:
	int			_genetic_genelations;	// 遗传代数
	double		_p_cross;				// 交叉率
	double		_p_mutate;				// 变异率
	Chromosome	_chromosomes;			// 由染色体组成的种群
	
	// 计算种群的适应度
	static void caculateFitness(std::vector<double> &fitnesses, std::vector<Chromosome_type> &pop);
	// 计算种群的累积概率
	static void  caculateAccumulate(std::vector<double> &accumulates, std::vector<Chromosome_type> &pop) ;
	// 轮盘赌选择一个染色体
	static int getOptimalChromosome(std::vector<Chromosome_type> &pop) ;
};
/**********************************************
 *	初始化遗传算法的参数
 * @genetic_genelations: 遗传代数
 * @p_cross: 交叉率
 * @p_mutate: 变异率
 * @chromosomes: 种群
 */
template<typename Chromosome_type>
void GA<Chromosome_type>::algorithm_init(int genetic_genelations, double p_cross, 
											double p_mutate,Chromosome chromosomes)
{
	/*
	this->_genetic_genelations = genetic_genelations;
	this->_p_cross = p_cross;
	this->_p_mutate = p_mutate;
	this->_chromosomes = chromosomes;
	*/
}
/**********************************************
 *	遗传算法主体
 * @genetic_genelations: 遗传代数
 * @p_cross: 交叉率
 * @p_mutate: 变异率
 * @chromosomes: 种群 
 */
template<typename Chromosome_type>
Chromosome_type GA<Chromosome_type>::algorithm_action(int genetic_genelations, double p_cross, double p_mutate,  int popSize){
	// 族谱
	std::vector<std::vector<Chromosome_type> > allPopulation;
	// 每一代的适应度
	std::vector<vector<double> > allfitness;
	// 当代种群
	std::vector<Chromosome_type> pop;
	// 当代种群的适应度
	std::vector<double> fitnesses;
	// 初始化原始种群
	Chromosome_type::initPopulation(popSize, pop);
	// 计算初代的适应度
	caculateFitness(fitnesses, pop);
	for (int k = 1; k <= genetic_genelations; ++k){
		// 计算累计概率
		std::vector<double> accumulates;
		caculateAccumulate(accumulates, pop);

		// 获取精英

		// 轮盘赌选择出新一代的种群

	}

	return NULL;
}
/**********************************************
 *	计算适应度
 * @fitnesses: 返回种群的适应度
 * @pop: 种群
 */
template<typename Chromosome_type>
void  GA<Chromosome_type>::caculateFitness(std::vector<double> &fitnesses, std::vector<Chromosome_type> &pop)
{
	for (int i = 0; i < pop.size(); i++)
		fitnesses.push_back(pop[i].fitness());
}
/**********************************************
 *	计算累积概率
 * @accumulates: 返回累积概率
 * @pop: 种群
 */
template<typename Chromosome_type>
void  GA<Chromosome_type>::caculateAccumulate(std::vector<double> &accumulates, std::vector<Chromosome_type> &pop) 
{
	double sum = 0.0;
	double accumulate = 0.0;
	for (int i = 0; i < pop.size(); i++)
		sum += pop[i].fitness();
	for (int i = 0; i < pop.size()-1; i++)
	{
		accumulate += pop[i].fitness()/sum;
		accumulates.push_back(accumulate);
	}
	accumulates.push_back(1.0);
}
/**********************************************
 *	计算累积概率
 * @accumulates: 返回累积概率
 * @pop: 种群
 */
template<typename Chromosome_type>
int GA<Chromosome_type>::getOptimalChromosome(std::vector<Chromosome_type> &pop)
{
	int index = 0;
	Chromosome_type chrom = pop[0];
	for (int i = 1; i < pop.size(); ++i)
		if (chrom < pop[i]){
			chrom = pop[i];
			index = i;
		}
	return i;
}
/**********************************************
 * 测试
 */
template<typename Chromosome_type>
void  GA<Chromosome_type>::test(int popSize)
{
	// 当代种群
	std::vector<Chromosome_type> pop;
	// 当代种群的适应度
	std::vector<double> fitnesses;
	// 初始化原始种群
	Chromosome_type::initPopulation(popSize, pop);
	caculateFitness(fitnesses, pop);

	for (int i = 0; i < pop.size(); i++){
		std::cout << pop[i].fitness() << ':';
		for (int j = 0; j < Chromosome_Tsp::city_cnt; ++j){
			std::cout << pop[i].genes[j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::vector<double> accumulates;
	caculateAccumulate(accumulates, pop);
	for (int i = 0; i < pop.size(); i++){
		std::cout << accumulates[i] << '\t';
	}
}
#endif