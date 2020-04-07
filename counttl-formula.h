//#include<cstdio>
//#include<cstring>
//#include<cstdlib>
//#include<cmath>
#include<iostream>
#include<string>
#include<stack>
#include<set>
#include<map>
#include <z3++.h>

//using namespace std; 
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
typedef struct FTree
{

	int     type;
//--------------------------------------------------------------------------------------------------
//type can either be 0 (leaf or proposition) or 1 (unary opearator) or 2(binary operator) or 3 (quantifier) or 4 (counting quantifier)or 5 (predicate)-------we can make type as enum with 6 values, instead. 
//--------------------------------------------------------------------------------------------------
//if type is 4 (counting quantifier) then val field is irrelevant -- the relevant info is whether it is > or <= and the bound k
//--------------------------------------------------------------------------------------------------
      bool    ctype; 
//--------------------------------------------------------------------------------------------------
// counting quantifier type --- 0 means > and 1 means <=
//--------------------------------------------------------------------------------------------------
      int     bound;
// the k value in counting quantifier
//--------------------------------------------------------------------------------------------------
//------------------The following fields are not needed for Counting Temporal Logic-----------------
//-------------------------------------------------------------------------------------------------- 
//	bool    subd;//0 for not substituted 1 for substituted---useful only when type is 0

//	unsigned model;//model as a positive integer; can be converted to boolean std::string whenever needed---- refers to the object in the MFO model.

//	unsigned copy;//copy of the model above -- present due to occurrence of = (equality) symbol in the logic, not needed otherwise

//	unsigned num;//num=R*model+copy----where R is the max value copy can take, actually the number of variables of the type client in the formula.
//--------------------------------------------------------------------------------------------------
	std::string  val;
//--------------------------------------------------------------------------------------------------
//variable or operator (logical or temporal)
//--------------------------------------------------------------------------------------------------
	std::string  client;
//--------------------------------------------------------------------------------------------------
//client type as string
//--------------------------------------------------------------------------------------------------
      int     iclient;
//--------------------------------------------------------------------------------------------------
//client type in numbers 
//--------------------------------------------------------------------------------------------------
	struct  FTree*  parent;
	struct  FTree*  left;
	struct  FTree*  right;
	struct  FTree*  next;

//--------------------------------------------------------------------------------------------------
//----------------------------------------GET FUNCTIONS---------------------------------------------
//--------------------------------------------------------------------------------------------------
      int get_type(){return type;};
      bool get_ctype(){return ctype;};
      int get_bound(){return bound;};
      std::string get_val(){return val;};
      std::string get_client(){return client;};
      int get_iclient(){return iclient;};

	struct  FTree*  get_parent(){return parent;};
	struct  FTree*  get_left(){return left;};
	struct  FTree*  get_right(){return right;};
	struct  FTree*  get_next(){return next;};
//--------------------------------------------------------------------------------------------------
//----------------------------------------SET FUNCTIONS---------------------------------------------
//--------------------------------------------------------------------------------------------------
      void set_type(int t){this->type=t;};
      void set_ctype(bool ct){this->ctype=ct;};
      void set_bound(int b){this->bound=b;};
      void set_val(std::string v){this->val=v;};
      void set_client(std::string c){this->client=c;};
      void set_iclient(int ic){this->iclient=ic;};

      void set_parent(struct  FTree* p){this->parent=p;};
      void set_left(struct  FTree* l){this->left=l;};
      void set_right(struct  FTree* r){this->right=r;};
      void set_next(struct  FTree* n){this->next=n;};


}FTree;
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class Formula{
 protected:
	std::string  FormulaText;
	FTree*  FormulaTree;
      FTree*  NNFormula;

//	FTree*  QEFTree;//This is not needed ---- for Counting Temporal Logic
	
	int     NoOfCltTypes;
      int     MaxBound;//This is no longer needed -- when we have MaxBoundList?
      int     NoOfCntQntfrs;//Is this needed ?

	std::set<std::string> PredList;
	std::set<std::string> VarList;

	std::map<std::string,int> PredNum;
	std::map<std::string,int> VarNum;

      std::map<std::string,int> ClientList;//Each client type is numbered. Used, in turn, to assign a counter.
      std::map<std::string,int> MaxBoundList;//MaxBound for each Client type

 public:
	Formula(){};//Constructor
	Formula(std::string InExp){FormulaText=InExp;};//Parameterized Constructor
	~Formula(){};//Destructor
		
	bool    ftree_convert();
      bool    construct_nnf();

//	bool    quant_elim();----Not needed for Counting Temporal Logic

      FTree*  get_ftree(){return copy(FormulaTree);};
//    FTree*  get_qe_ftree(){return copy(QEFTree);};----Not needed for Counting Temporal Logic

      int     get_bound();
	std::map <std::string,int>    compute_bounds();

	void    display_ftree();
	void    display_ftree_pre();
//	void    display_ftree_sub();
//	void    display_ftree_pre_sub();

	void    display_lists();
	void    display_nums(); 

//display_ft(FTree*) and display_ft_pre(FTree*) should not be public
	static  void    display_ft(FTree*);//static as we need only one copy of this method
	static  void    display_ft_pre(FTree*);//static as we need only one copy of this method
//	static  void    display_ft_sub(FTree*);//static as we need only one copy of this method
//	static  void    display_ft_pre_sub(FTree*);//static as we need only one copy of this method

	static  FTree*  copy(FTree*);
      static  FTree*  negate(FTree*);

//	FTree*  eliminate_quantifier(FTree*);----Not needed for Counting Temporal Logic
      FTree*  const_nnf(FTree*,int);
 protected:
	int     isoperator(char);
	int     op_prcd(char);
	int     op_type(char);
//	void    substitute(FTree*,std::string,int,int,int);----Not needed for Counting Temporal Logic

	bool    add_variable_to_formula_info(std::string,std::string);
	void    add_predicate_to_formula_info(std::string,std::string);


};
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
