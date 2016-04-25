#ifndef RANDOM_VARIABLE_H
#define RANDOM_VARIABLE_H

#ifdef __cplusplus

template <class T>
class UniformRandomVariable{
public:
	UniformRandomVariable(T min,T max,int n);
	~UniformRandomVariable();
	T min_;
	T max_;
	int n_;
	std::vector<T> values;
	std::default_random_engine generator;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif
int* UniformIntRandomVariable(int min,int max, int n);
double* UniformDoubleRandomVariable(double min,double max, int n);
#ifdef __cplusplus
}
#endif

#endif