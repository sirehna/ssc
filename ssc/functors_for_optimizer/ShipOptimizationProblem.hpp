#ifndef __OPTIMIZATIONPROBLEMGENERATORHPP__
#define __OPTIMIZATIONPROBLEMGENERATORHPP__

class OptimizationProblemGenerator
{
    public:
        OptimizationProblemGenerator(const StateList& states);
        OptimizationProblemGenerator& minimize(const Node& f);
        OptimizationProblemGenerator& subject_to(const Parameter& min_bound, const Node& f, const Parameter& max_bound);
        ValType get_obj_fun() const;

    private:
        ValType obj_fun

};


#endif
