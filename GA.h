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
	static Chromosome_type algorithm_action(int genetic_genelations, double p_cross, double p_mutate, int popSize);
private:
	int			_genetic_genelations;	// �Ŵ�����
	double		_p_cross;				// ������
	double		_p_mutate;				// ������
	Chromosome	_chromosomes;			// ��Ⱦɫ����ɵ���Ⱥ
	
	// ������Ⱥ����Ӧ��
	static void caculateFitness(std::vector<double> &fitnesses, std::vector<Chromosome_type> &pop);
	// ������Ⱥ���ۻ�����
	static void  caculateAccumulate(std::vector<double> &accumulates, std::vector<Chromosome_type> &pop) ;
	// ��ȡ�������Ⱦɫ��
	static int getOptimalChromosome(std::vector<Chromosome_type> &pop) ;
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
 * @genetic_genelations: �Ŵ�����
 * @p_cross: ������
 * @p_mutate: ������
 * @chromosomes: ��Ⱥ 
 */
template<typename Chromosome_type>
Chromosome_type GA<Chromosome_type>::algorithm_action(int genetic_genelations, double p_cross, double p_mutate,  int popSize){
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
	for (int k = 1; k <= genetic_genelations; ++k){
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
		// ѡ������Ⱦɫ����н������
		for (int i = popSize/2; i > 0; --i){
			int index1 = rand()%(i*2);
			int index2 = 0;
			do {
				index2 = rand()%(i*2);
			}while (index1 == index2);

			// �Ƿ��м��ʽ���
			double p = rand()*1.0/RAND_MAX;
			if (p < p_cross){
				Chromosome_type::cross(subPop[index1], subPop[index2]);
			}
			std::swap(subPop[index1], subPop[i*2-1]);
			std::swap(subPop[index2], subPop[i*2-2]);
		}
		// һ�����˻�����
		pop = subPop;
		// ������
		allPopulation.push_back(pop);
	}
	int optimalIndex = getOptimalChromosome(allPopulation[allPopulation.size()-1]);
	Chromosome_type optimalChrom = allPopulation[allPopulation.size()-1][optimalIndex];
	return optimalChrom;
}
/**********************************************
 *	������Ӧ��
 * @fitnesses: ������Ⱥ����Ӧ��
 * @pop: ��Ⱥ
 */
template<typename Chromosome_type>
void  GA<Chromosome_type>::caculateFitness(std::vector<double> &fitnesses, std::vector<Chromosome_type> &pop)
{
	for (int i = 0; i < pop.size(); i++)
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
 *	�����ۻ�����
 * @accumulates: �����ۻ�����
 * @pop: ��Ⱥ
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
	std::cout <<std::endl;
	std::cout << selectChromosome(accumulates) << std::endl;
}
#endif