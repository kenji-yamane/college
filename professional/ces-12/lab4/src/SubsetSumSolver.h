#ifndef SSP_SOLVER
#define SSP_SOLVER


#include <vector>
#include <string>
#include <SubsetSumSolverAbstract.h>
#include <Subset.h>


class SSPSolverAluno2 : public SubsetSumSolverAbstract {

    
public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
        
    virtual std::string getName() { return "A2"; }
    
private:
	static std::vector<Subset> subsets;
	static std::vector<long> weigths;
	static std::vector<char> indexes;
	void reset(std::vector<long> &input);
	void collectSums(size_t posic, long sum);
}; 

class SSPSolverExtra : public SubsetSumSolverAbstract {

    
public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
        
    virtual std::string getName() { return "EX"; }
    
}; 

class SSPSolverPD : public SubsetSumSolverAbstract {

public:
    
    virtual bool solve(const std::vector< long> &input,
                        long value, std::vector< char> &output);
    
    virtual std::string getName() { return "PD"; }
    
}; 

#endif
