#include "counttl-formula.h"
//using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
int main()
{

//CFO InExps -- For the time being we shall have only l (load) and t (terminate) predicates in the input
// No p's (client predicates) and q's (server propositions)

//    std::string InExp="(l(x))";
//    std::string InExp="(t(x))";
//	std::string InExp="(#x>1(l(x)))";//--output correct
//	std::string InExp="(Ex(l(x)))";//--output correct

//	std::string InExp="((#x:1>1)(l(x:1)))";//--output correct
//	std::string InExp="((#x:1>1)(t(x:1)))";//--output correct



//	std::string InExp="((#x<=2)(~(l(x))))";//--input wrong
//	std::string InExp="((#x<=2)(~(t(x))))";//--input wrong


//	std::string InExp="((#x:1<=2)(l(x:1)))";//--output correct
//	std::string InExp="(~((#x>1)(l(x))))";//--output correct
//	std::string InExp="((#y10<=2)(~(t1(y10))))";//--output correct


	std::string InExp="(((#x:1>1)(l(x:1)))&((#y:2<=2)(l(y:2))))";//--output correct
//	std::string InExp="(((#x:1>1)(l(x:1)))&((#x:1>1)(t(x:1))))";//--output correct


//	std::string InExp="(((#x>1)(l(x)))&((#y<=2)(t(y))))";//--output correct
//	std::string InExp="(((#x>1)(l(x)))&((#x>1)(t(x))))";//--output correct

//	std::string InExp="(((#x:1>1)(l(x:1)))&((#y:2<=2)(t(y:2))))";//--output correct


//CFOTL InExps
//	std::string InExp="(G((#x>1)(l(x))))";
//	std::string InExp="(G(((#x>1)(l(x)))&((#x>1)(t(x)))))";


//
//LTL InExps
//	std::string InExp="((G(F(p11)))&(~(G(p12))))";
//	std::string InExp="(~(G(p12)))";
// 	std::string InExp="(G(F(p)))";
// 	std::string InExp="(F(p))";
//	std::string InExp="(G(p))";
// 	std::string InExp="(G(F(X(p))))";

//PL InExps
//	std::string InExp="(((p1)&(p2))|((~(p2))&(p3)))";
//	std::string InExp="((p1)&(p2))";
//	std::string InExp="(p1)";


//define a Formula object. This will create a formula object with expression (formula) as raw text.
	Formula InFormula(InExp);

//Using the methods in formula object we compute, first the formula tree and then eliminate quantifiers from the formula.
//In this process, we gather necessary data from the formula, which can be used later.


	std::cout <<"\nThe input formula is:->" << InExp << std::endl;

//convert the InExp to InExp tree.
	bool done=InFormula.ftree_convert();
	if(!done){
		std::cout<< "\nFormula tree construction fails.\n";
		return 0;
	}
	std::cout <<"\nFormula Tree Constructed...............\n";
	std::cout <<"\nReading the Formula Tree...............\n";
	std::cout <<"\nIn infix form:";
	InFormula.display_ftree();
	std::cout <<"\n";
	std::cout <<"\nIn prefix form:";
	InFormula.display_ftree_pre();
	std::cout <<"\n";

//  return 0;
//ftree_convert method should also gather the relevant data into 
//PredList, VarList and PredNum, VarNum data members of the formula object
//at this point we can traverse the maps PredNum and VarNum and find the number of variables and predicates of each client type.

	InFormula.display_lists();
	InFormula.display_nums();

	return 0;
//---------------------------------------------------------------------------------------------------------------
//now eliminate quantifiers
/*
	done=InFormula.quant_elim();
	if(!done){
		std::cout<< "\nQuantifier Elimination fails.\n";
		return 0;
	}

	std::cout <<"The InExp with all quantifiers eliminated is as follows:\nIn prefix form:";
	InFormula.display_ftree_pre_sub();
	std::cout <<"\n";

	std::cout <<"\nIn infix form:";
	InFormula.display_ftree_sub();
	std::cout <<"\n";
	std::cout << std::endl;

//	InFormula.display_lists();
//	InFormula.display_nums();

	return 0;


//-----------------------------------------------------------------------------------------------------------------
//At this point we should free all the dynamic memory we created using new, otherwise it will lead to memory leak.
//-----------------------------------------------------------------------------------------------------------------

	return 0;
*/

}//end of main
