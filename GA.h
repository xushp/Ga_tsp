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
	// ga算法的主体
	static std::vector<std::vector<Chromosome_type> > algorithm_action(int genetic_genelations, double p_cross, double p_mutate, int popSize);
	// 获取最优秀的染色体
	static int getOptimalChromosome(std::vector<Chromosome_type> &pop) ;
	// 获取最垃圾的染色体
	static int getWorstChromosome(std::vector<Chromosome_type> &pop) ;
	// 统计
	static void statistic(std::vector<std::vector<Chromosome_type> > allPopulation);
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
	static int selectChromosome(std::vector<double> &accumulates);
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
 * @genetic_generations: 遗传代数
 * @p_cross: 交叉率
 * @p_mutate: 变异率
 * @chromosomes: 种群 
 * @return: 返回遗传操作中每一代的种群
 */
template<typename Chromosome_type>
std::vector<std::vector<Chromosome_type> > GA<Chromosome_type>::algorithm_action(
	int genetic_generations, double p_cross, double p_mutate,  int popSize)
{
	// 族谱
	std::vector<std::vector<Chromosome_type> > allPopulation;
	// 每一代的适应度
	std::vector<std::vector<double> > allfitness;
	// 当代种群
	std::vector<Chromosome_type> pop;
	// 当代种群的适应度
	std::vector<double> fitnesses;
	// 初始化原始种群
	Chromosome_type::initPopulation(popSize, pop);
	// 计算初代的适应度
	caculateFitness(fitnesses, pop);
	for (int k = 1; k <= genetic_generations; ++k){
		// 计算累计概率
		std::vector<double> accumulates;
		caculateAccumulate(accumulates, pop);

		// 获取精英
		int optimalIndex = getOptimalChromosome(pop);
		Chromosome_type optimalChrom = pop[optimalIndex];

		// 轮盘赌选择出新一代的种群
		std::vector<Chromosome_type> subPop;
		for (int i = 0; i < popSize; ++i){
			int index = selectChromosome(accumulates);
			subPop.push_back(pop[index]);
		}
		// 交叉操作
		Chromosome_type::popCross(subPop, p_cross);

		// 变异
		for (int i = 0; i < popSize; i++)
		{
			double p = rand()*1.0/RAND_MAX;
			if (p < p_mutate)
				Chromosome_type::mutate(subPop[i]);
		}
		// 最优保留策略
		optimalIndex = getOptimalChromosome(subPop);
		if (subPop[optimalIndex] < optimalChrom)
		{// 精英在遗传过程中被破坏
			int worstIndex = getWorstChromosome(subPop);
			subPop[worstIndex] = optimalChrom;
		}
		// 一代新人换旧人
		pop = subPop;
		// 进族谱
		allPopulation.push_back(pop);
	}
	return allPopulation;
}
/**********************************************
 *	计算适应度
 * @fitnesses: 返回种群的适应度
 * @pop: 种群
 */
template<typename Chromosome_type>
void  GA<Chromosome_type>::caculateFitness(std::vector<double> &fitnesses, std::vector<Chromosome_type> &pop)
{
	for (size_t i = 0; i < pop.size(); i++)
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
	for (size_t i = 0; i < pop.size(); i++)
		sum += pop[i].fitness();
	for (size_t i = 0; i < pop.size()-1; i++)
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
	for (size_t i = 1; i < pop.size(); ++i)
		if (chrom < pop[i]){
			chrom = pop[i];
			index = i;
		}
	return index;
}
/**********************************************
 *	计算累积概率
 * @accumulates: 返回累积概率
 * @pop: 种群
 */
template<typename Chromosome_type>
int GA<Chromosome_type>::getWorstChromosome(std::vector<Chromosome_type> &pop)
{
	int index = 0;
	Chromosome_type chrom = pop[0];
	for (size_t i = 1; i < pop.size(); ++i)
		if (pop[i] < chrom){
			chrom = pop[i];
			index = i;
		}
	return index;
}
/**********************************************
 *	轮盘赌选择一个染色体
 * @accumulates: 累积概率
 * @return: 返回下标
 */
template<typename Chromosome_type>
int GA<Chromosome_type>::selectChromosome(std::vector<double> &accumulates)
{
	double rndNum = rand()*1.0/RAND_MAX;
	int index = -1;
	while(rndNum > accumulates[++index] );
	return index;
}
/**********************************************
 *	统计数据
 */
template<typename Chromosome_type>
void GA<Chromosome_type>::statistic(std::vector<std::vector<Chromosome_type> > allPopulation)
{
	for (size_t i = 0; i < allPopulation.size(); ++i){
		std::cout << "Genalations:" << i+1;
		std::cout << ",Optimal chromosome:" << std::endl;
		int index = getOptimalChromosome(allPopulation[i]);
		std::cout << "Genes:" << allPopulation[i][index] << ",Length:" << allPopulation[i][index].pathlength() << std::endl;
		double sum = 0.0;
		for (size_t j = 0; j < allPopulation[i].size(); ++j)
			sum += allPopulation[i][j].pathlength();
		std::cout << "average path length:" << sum/allPopulation[i].size() << std::endl;
	}
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

	for (size_t i = 0; i < pop.size(); i++){
		std::cout << pop[i].fitness() << ':';
		for (int j = 0; j < Chromosome_Tsp::city_cnt; ++j){
			std::cout << pop[i].genes[j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::vector<double> accumulates;
	caculateAccumulate(accumulates, pop);
	for (size_t i = 0; i < pop.size(); i++){
		std::cout << accumulates[i] << '\t';
	}
	std::cout << "\n"<<pop[0] <<',' << pop[0].pathlength() << "\n" << pop[1] <<  ',' << pop[1].pathlength() <<std::endl;
	Chromosome_type::cross(pop[0], pop[1]);
	std::cout << "\n"<<pop[0] <<',' << pop[0].pathlength() << "\n" << pop[1] <<  ',' << pop[1].pathlength() <<std::endl;
}
#endif