//////////////////////////////////////////////////////////////
//
//	FileName : GA.h 
//	Creator : xsp
//	Date : 2015-04-09
//	Comment : �����Ŵ��㷨��ʵ����
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
	// ga�㷨������
	static std::vector<std::vector<Chromosome_type> > algorithm_action(int genetic_genelations, double p_cross, double p_mutate, int popSize);
	// ��ȡ�������Ⱦɫ��
	static int getOptimalChromosome(std::vector<Chromosome_type> &pop) ;
	// ��ȡ��������Ⱦɫ��
	static int getWorstChromosome(std::vector<Chromosome_type> &pop) ;
	// ͳ��
	static void statistic(std::vector<std::vector<Chromosome_type> > allPopulation);
private:
	int			_genetic_genelations;	// �Ŵ�����
	double		_p_cross;				// ������
	double		_p_mutate;				// ������
	Chromosome	_chromosomes;			// ��Ⱦɫ����ɵ���Ⱥ
	
	// ������Ⱥ����Ӧ��
	static void caculateFitness(std::vector<double> &fitnesses, std::vector<Chromosome_type> &pop);
	// ������Ⱥ���ۻ�����
	static void  caculateAccumulate(std::vector<double> &accumulates, std::vector<Chromosome_type> &pop) ;
	// ���̶�ѡ��һ��Ⱦɫ��
	static int selectChromosome(std::vector<double> &accumulates);
};
/**********************************************
 *	��ʼ���Ŵ��㷨�Ĳ���
 * @genetic_genelations: �Ŵ�����
 * @p_cross: ������
 * @p_mutate: ������
 * @chromosomes: ��Ⱥ
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
 *	�Ŵ��㷨����
 * @genetic_generations: �Ŵ�����
 * @p_cross: ������
 * @p_mutate: ������
 * @chromosomes: ��Ⱥ 
 * @return: �����Ŵ�������ÿһ������Ⱥ
 */
template<typename Chromosome_type>
std::vector<std::vector<Chromosome_type> > GA<Chromosome_type>::algorithm_action(
	int genetic_generations, double p_cross, double p_mutate,  int popSize)
{
	// ����
	std::vector<std::vector<Chromosome_type> > allPopulation;
	// ÿһ������Ӧ��
	std::vector<std::vector<double> > allfitness;
	// ������Ⱥ
	std::vector<Chromosome_type> pop;
	// ������Ⱥ����Ӧ��
	std::vector<double> fitnesses;
	// ��ʼ��ԭʼ��Ⱥ
	Chromosome_type::initPopulation(popSize, pop);
	// �����������Ӧ��
	caculateFitness(fitnesses, pop);
	for (int k = 1; k <= genetic_generations; ++k){
		// �����ۼƸ���
		std::vector<double> accumulates;
		caculateAccumulate(accumulates, pop);

		// ��ȡ��Ӣ
		int optimalIndex = getOptimalChromosome(pop);
		Chromosome_type optimalChrom = pop[optimalIndex];

		// ���̶�ѡ�����һ������Ⱥ
		std::vector<Chromosome_type> subPop;
		for (int i = 0; i < popSize; ++i){
			int index = selectChromosome(accumulates);
			subPop.push_back(pop[index]);
		}
		// �������
		Chromosome_type::popCross(subPop, p_cross);

		// ����
		for (int i = 0; i < popSize; i++)
		{
			double p = rand()*1.0/RAND_MAX;
			if (p < p_mutate)
				Chromosome_type::mutate(subPop[i]);
		}
		// ���ű�������
		optimalIndex = getOptimalChromosome(subPop);
		if (subPop[optimalIndex] < optimalChrom)
		{// ��Ӣ���Ŵ������б��ƻ�
			int worstIndex = getWorstChromosome(subPop);
			subPop[worstIndex] = optimalChrom;
		}
		// һ�����˻�����
		pop = subPop;
		// ������
		allPopulation.push_back(pop);
	}
	return allPopulation;
}
/**********************************************
 *	������Ӧ��
 * @fitnesses: ������Ⱥ����Ӧ��
 * @pop: ��Ⱥ
 */
template<typename Chromosome_type>
void  GA<Chromosome_type>::caculateFitness(std::vector<double> &fitnesses, std::vector<Chromosome_type> &pop)
{
	for (size_t i = 0; i < pop.size(); i++)
		fitnesses.push_back(pop[i].fitness());
}
/**********************************************
 *	�����ۻ�����
 * @accumulates: �����ۻ�����
 * @pop: ��Ⱥ
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
 *	�����ۻ�����
 * @accumulates: �����ۻ�����
 * @pop: ��Ⱥ
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
 *	�����ۻ�����
 * @accumulates: �����ۻ�����
 * @pop: ��Ⱥ
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
 *	���̶�ѡ��һ��Ⱦɫ��
 * @accumulates: �ۻ�����
 * @return: �����±�
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
 *	ͳ������
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
 * ����
 */
template<typename Chromosome_type>
void  GA<Chromosome_type>::test(int popSize)
{
	// ������Ⱥ
	std::vector<Chromosome_type> pop;
	// ������Ⱥ����Ӧ��
	std::vector<double> fitnesses;
	// ��ʼ��ԭʼ��Ⱥ
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