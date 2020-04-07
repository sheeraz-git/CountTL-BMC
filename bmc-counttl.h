#include "counttl-formula.h"

using namespace z3;
//---------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------
class counttl_bmc{
  public:
// private:
    context c;//context class manages all Z3 objects, global configuration options, etc.
    solver  S;//solver class provides methods for sat checking etc.

//Z3 expression is used to represent formulas and terms. a formula is any expression of sort Boolean. every expression (formula or term) has to have a sort. sort (aka type) is another Z3 class.
  
    expr    IF;//formula IF represents the initial states of the state-transition system .
    expr    TF;//formula TF represents the transition function of the state-transition system .

    expr    CountIF;//formula CountIF represents the initial states of the counter system .
    expr    CountTF;//formula CountTF represents the transition function of the counter system .

    FTree*  CountTLF;//formula tree CountTLF represents the temporal property to be checked for (CountIF,CountTF)

    int     N_s;//N is the number of state variables .
    int     N_c;//N is the number of counter variables .

// public:
    bool    init();

// protected:
    expr    instantiate_P_at_k(int k);

    expr    instantiate_CountT_at_k(int k);

    expr    loopFree_at_k(int k);//most probably not needed.

    void    translate(int k);

    void    print_trace(int k);

    expr    translate_CountTL_with_backloop_from_k_to_l(FTree* TLFormula,int k,int l,int i);

    expr    translate_CountTL_for_no_loop(FTree* TLFormula,int k,int i);

    expr    encode_CountTL_property_into_PL(int k);

    expr    compute_loop_constraints_at_k(int k);

    expr    instantiate_CountT_for_loop_constraints(int k,int j);

    expr 	encode_into_pl(FTree* TF,int k,int limit);//Does not belong to BMC-LTL Code

//exp_vector is vector of expressions defined as typedef ast_vector_tpl<expr>.
//class template ast_vector_tpl<T> defines various methods to manipulate generic vectors.
    expr_vector     x;

    expr_vector     y;

    expr_vector     u;

    expr_vector     v;

    expr_vector     ip;

    expr_vector     ipe;

    expr_vector     alpha;

    expr_vector     beta;

    expr_vector     lambda;

    expr    F;//Boolean constant FALSE
    
    expr    T;//Boolean constant TRUE

    counttl_bmc():
        S(c),
        IF(c),
        TF(c),
        CountIF(c),
        CountTF(c),
        x(c),
        y(c),
        u(c),
        v(c),
        ip(c),
        ipe(c),
        alpha(c),
        beta(c),
        lambda(c),F(c),T(c){};//constructor
    ~counttl_bmc(){};//destructor


};
//---------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------

