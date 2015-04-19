//////////////////////////////////////////////////////////////
//
//	FileName : Chromosome_Tsp.h 
//	Creator : xsp
//	Date : 2015-04-09
//	Comment : �����Ŵ��㷨�У�tsp���������࣬Ⱦɫ���Լ���ز���
//
//////////////////////////////////////////////////////////////
#ifndef CHROMOSOME_TSP_H
#define CHROMOSOME_TSP_H
#include <vector>

typedef std::vector<std::vector<double> >	Map_type;

class Chromosome_Tsp{
public:

	// ���캯��
	Chromosome_Tsp();
	// ��Ӧ�ȼ���
	double fitness() const;
	// ·������
	double pathlength() const;
	// �Ƚϲ�����
	bool operator < (const Chromosome_Tsp &chrom) const;
	friend std::ostream& operator << (std::ostream & out, Chromosome_Tsp&);
	// ÿ��Ⱦɫ��Ļ���
	std::vector<int>	genes;
	//////////////////////////////////////
	// ��̬��Ա����
	//
	// ��ʼ����ͼ
	static Map_type init_map(int city_cnt);		
	// ��ʼ����Ⱥ
	static void initPopulation(int popSize, std::vector<Chromosome_Tsp> &pop);
	// ��Ⱥ�������
	static void popCross(std::vector<Chromosome_Tsp> &pop, double p_cross);
	// �������
	static void cross(Chromosome_Tsp& chrom1, Chromosome_Tsp& chrom2);
	// �������
	static void mutate(Chromosome_Tsp& chrom);
	static int city_cnt;
	static Map_type Map;
private:
};

#endif