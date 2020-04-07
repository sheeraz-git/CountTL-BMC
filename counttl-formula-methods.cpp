#include "counttl-formula.h"
//using namespace std;
//--------------------------------------------DISPLAY FUNCTIONS-------------------------------------
//--------------------------------------------------------------------------------------------------
void Formula::display_lists()
{

	int i=1;

	std::set <std::string> :: iterator setIter;
	
	std::cout << "\nPredicate List.\n";

	for(setIter=PredList.begin();setIter!=PredList.end();setIter++)
		std::cout << *setIter << std::endl;

	std::cout << "\nVariable List.\n";

	for(setIter=VarList.begin();setIter!=VarList.end();setIter++)
		std::cout << *setIter << std::endl;

//we have to display ClientList and MaxBoundList -- Done.
      std::map <std::string,int> :: iterator mapIter;

	std::cout << "\nClient Names... \nClient type: Name/Number\n";

	for(mapIter=ClientList.begin();mapIter!=ClientList.end();mapIter++){
		std::cout<< i++ <<"th entry->" << mapIter->first << "(Client Type):" << mapIter->second << "(Name/Number)\n";
	}

	std::cout << "\nClient MaxBounds... \nClient type: MaxBound\n";
	
	for(mapIter=MaxBoundList.begin();mapIter!=MaxBoundList.end();mapIter++){
		std::cout<< i++ <<"th entry->" << mapIter->first << "(Client Type):" << mapIter->second << "(Bound)\n";
	}
}
void Formula::display_nums()
{

	std::map <std::string,int> :: iterator mapIter;

	std::cout << "\nPredicates... \nClient type: No. of Predicates\n";
	int i=1;
	for(mapIter=PredNum.begin();mapIter!=PredNum.end();mapIter++){
		std::cout<< i++ <<"th entry->" << mapIter->first << "(Client Type):" << mapIter->second << "(No. of Predicates)\n";
	}
	i=1;
	std::cout << "\nVariables... \nClient type: No. of Variables\n";

	for(mapIter=VarNum.begin();mapIter!=VarNum.end();mapIter++){
		std::cout << i++ <<"th entry->" << mapIter->first << "(Client Type):" << mapIter->second << "(No. of Variables)\n";
	}

} 
//--------------------------------------------------------------------------------------------------
void Formula::display_ftree()
{
	display_ft(FormulaTree);
	return;
}
void Formula::display_ftree_pre()
{
	display_ft_pre(FormulaTree);
	return;
}
/*
void Formula::display_ftree_sub()
{
	display_ft_sub(QEFTree);
	return;
}
void Formula::display_ftree_pre_sub()
{
	display_ft_pre_sub(QEFTree);
	return;
}
*/
//--------------------------------------------------------------------------------------------------
void Formula::display_ft(FTree* FT)
{
	
	if(FT==NULL){
		std::cout <<"\nError in the formula tree.\n";
		return;
	}
	switch(FT->type){

		case 5:// std::cout <<"\nThe node type is " << FT->type << "\n";//monadic predicate
			std::cout << FT->val;
			display_ft(FT->next);
			break;

		case 4:// std::cout <<"\nThe node type is " << FT->type << "\n";//counting quantifier
			std::cout << FT->val;
           if(FT->ctype)
                std::cout << "<=";
            else
                std::cout << ">";
            std::cout << FT->bound;
			display_ft(FT->next);
			break;

		case 3:// std::cout <<"\nThe node type is " << FT->type << "\n";//FO quantifier
			std::cout << FT->val;
			display_ft(FT->next);
			break;

		case 2:// std::cout <<"\nThe node type is " << FT->type << "\n";//binary operator
			display_ft(FT->left);
			std::cout << " " << FT->val << " ";
			display_ft(FT->right);
			break;

		case 1:// std::cout <<"\nThe node type is " << FT->type << "\n";//unary operator
			std::cout << FT->val;
			display_ft(FT->next);
			break;

		case 0:// std::cout <<"\nThe node type is " << FT->type << "\n";
			std::cout << FT->val;
//the following is needed
			//if(!FT->client.empty()){
			//	std::cout << ":"<< FT->client;
			//}
			break;

		default:
			//std::cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void Formula::display_ft_pre(FTree* FT)
{
	
	if(FT==NULL){
//		//std::cout <<"\nError in the formula tree.\n")
		return;
	}
	switch(FT->type){

		case 5:// std::cout <<"\nThe node type is " << FT->type << "\n";//monadic predicate
			std::cout << FT->val;
			display_ft_pre(FT->next);
			break;

		case 4:// std::cout <<"\nThe node type is " << FT->type << "\n";//counting quantifier
			std::cout << FT->val;
            if(FT->ctype)
                  std::cout << "<=";
            else
                  std::cout << ">";
                  std::cout << FT->bound;
			display_ft_pre(FT->next);
			break;

		case 3:// std::cout <<"\nThe node type is " << FT->type << "\n";//FO quantifier
			std::cout << FT->val;
			display_ft_pre(FT->next);
			break;

		case 2:// std::cout <<"\nThe node type is " << FT->type << "\n";//binary operator
			std::cout << FT->val;
			display_ft_pre(FT->left);
			display_ft_pre(FT->right);
			break;

		case 1:// std::cout <<"\nThe node type is " << FT->type << "\n";//unary operator
			std::cout << FT->val;
			display_ft_pre(FT->next);
			break;

		case 0:// std::cout <<"\nThe node type is " << FT->type << "\n";
			std::cout << FT->val;
//the following is needed
			//if(!FT->client.empty()){
			//	std::cout << ":"<<FT->client;
			//}		
			break;

		default:
			//std::cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
/*
void Formula::display_ft_sub(FTree* FT)
{
	
	if(FT==NULL){
//		//std::cout <<"\nError in the formula tree.\n")
		return;
	}
	switch(FT->type){

		case 5:// std::cout <<"\nThe node type is " << FT->type << "\n";//---monadic predicates
			std::cout << FT->val;
			display_ft_pre(FT->next);
			break;

		case 4:// std::cout <<"\nThe node type is " << FT->type << "\n";//---counting quantifiers
			std::cout << FT->val<<FT->client;
			display_ft_sub(FT->next);
			break;

		case 3:// std::cout <<"\nThe node type is " << FT->type << "\n";//---quantifiers
			std::cout << FT->val;
			display_ft_sub(FT->next);
			break;

		case 2:// std::cout <<"\nThe node type is " << FT->type << "\n";//---binary operators
			display_ft_sub(FT->left);
			std::cout << FT->val;
			display_ft_sub(FT->right);
			break;

		case 1:// std::cout <<"\nThe node type is " << FT->type << "\n";//---unary operators
			std::cout << FT->val;
			display_ft_sub(FT->next);
			break;

		case 0:// std::cout <<"\nThe node type is " << FT->type << "\n";//---variable or local proposition
			if(FT->subd)
				std::cout << "[" << FT->num << "]";	
			else{
				std::cout << FT->val;
				//if(!FT->client.empty()){
				//	std::cout << ":"<< FT->client;
				//}

			}
			break;

		default:
			//std::cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void Formula::display_ft_pre_sub(FTree* FT)
{
	
	if(FT==NULL){
//		//std::cout <<"\nError in the formula tree.\n")
		return;
	}
	switch(FT->type){

		case 5:// std::cout <<"\nThe node type is " << FT->type << "\n";//---monadic predicates
			std::cout << FT->val;
			display_ft_pre(FT->next);
			break;
		case 4:// std::cout <<"\nThe node type is " << FT->type << "\n";//---counting quantifiers
			std::cout << FT->val<<FT->client;
			display_ft_pre_sub(FT->next);
			break;

		case 3:// std::cout <<"\nThe node type is " << FT->type << "\n";//---quantifiers
			std::cout << FT->val;
			display_ft_pre_sub(FT->next);
			break;

		case 2:// std::cout <<"\nThe node type is " << FT->type << "\n";//---binary operators
			std::cout << FT->val;
			display_ft_pre_sub(FT->left);
			display_ft_pre_sub(FT->right);
			break;

		case 1:// std::cout <<"\nThe node type is " << FT->type << "\n";//---unary operators
			std::cout << FT->val;
			display_ft_pre_sub(FT->next);
			break;

		case 0:// std::cout <<"\nThe node type is " << FT->type << "\n";//---variable or local proposition
			if(FT->subd)
				std::cout << "[" << FT->num << "]";			
			else{
				std::cout << FT->val;
				//if(!FT->client.empty()){
				//	std::cout << ":"<< FT->client;
				//}

			}
			break;

		default:
			//std::cout <<"\nError! Type can either be 0, 1 or 2.\n");
			break;
	}

}
*/
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool Formula::construct_nnf()
{
	int flag=-1;
	FTree* NNFTree=const_nnf(this->FormulaTree,flag);
	this->NNFormula = NNFTree;//what is this ?
    //when an object is being created using new then it has to be deleted eventually.
    //there is no garabage collection in C++

//After the NNF of the formula is constructed, we print and check it.
	//std::cout <<"\nNNF of Formula Tree Constructed...............\n" << std::endl;
	fflush(stdout);
//read the formula tree and print the leaves
	//std::cout <<"\nReading the Formula Tree...............\n" << std::endl;
	//std::cout <<"\nIn infix form:";
	//FTree::display_ft((this->NNFormula)->root);
      display_ft(NNFTree);
	//std::cout <<"\n" << std::endl;
	//std::cout <<"\nIn prefix form:";
	//FTree::display_ft((this->NNFormula)->root);
      display_ft(NNFTree);
	//std::cout <<"\n" << std::endl;
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
FTree* Formula::const_nnf(FTree* TFormula, int flag)
{
	FTree* NTFormula=NULL;
	
	switch(flag)
	{
		case -1:// this is the beginning of the nnf construction. look at the root. if it is labelled ~ make changes in the child node and call nnf recursively with flag =1. else if it is not labelled ~ keep the child as it is and call nnf recursively with flag=0.
			//std::cout <<"\nWe are looking at the root of the formula tree.\n" << std::endl;
			if(TFormula->get_val()[0]=='~')
			{
				//std::cout <<"\nThere is a ~(NOT) at the root.\n" << std::endl;
				return(const_nnf(TFormula->get_next(),1));
			}
			else{
				//std::cout <<"\nThere is NO ~(NOT) at the root.\n" << std::endl;
				return(const_nnf(TFormula,0));
			}
		case 0:
			if(!isoperator(TFormula->get_val()[0]))
			{
				//std::cout <<"\nWe have hit a leaf with flag " << flag << "\n" << std::endl;
				//std::cout <<"\nWe copy the node and return it.\n" << std::endl;
				NTFormula=Formula::copy(TFormula);
				return(NTFormula);
			}//end of if
			else
			{
				if(TFormula->get_val()[0]=='~')
				{
					//std::cout <<"\nWe hit a ~(NOT) with " << flag << " at an internal node.\n" << std::endl;
					//std::cout <<"\nRecursively Call the function with flag " << 1-flag << "\n" << std::endl;
					return(const_nnf(TFormula->get_next(),1-flag));
				}//end of if	
				else{
					switch(TFormula->get_val()[0])
					{
						case '@':
								//std::cout <<"\nWe hit a @ (AT) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),flag));
//we have pushed ~(NOT) inside the local formula. that is correct
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case '#':
								//std::cout <<"\nWe hit a # (COUNTING QUANTIFIER) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(4);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'E':
								//std::cout <<"\nWe hit a E (EXISTENTIAL QUANTIFIER) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(3);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'A':
								//std::cout <<"\nWe hit a A (UNIVERSAL QUANTIFIER) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(3);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case '|'://generate a new formula tree node labelled &, attach the nnf of its left and right child respectively and return it.
								//std::cout <<"\nWe hit a | (OR) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val("|");
								NTFormula->set_type(2);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_left(const_nnf(TFormula->get_left(),0));
								NTFormula->set_right(const_nnf(TFormula->get_right(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);


						case '&'://generate a new formula tree node labelled |, attach the nnf of its left and right child respectively and return it.
								//std::cout <<"\nWe hit a & (AND) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val("&");
								NTFormula->set_type(2);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_left(const_nnf(TFormula->get_left(),0));
								NTFormula->set_right(const_nnf(TFormula->get_right(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);


						case 'X':
								//std::cout <<"\nWe hit a X (NEXT) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'Y':
								//std::cout <<"\nWe hit a Y (PREVIOUS) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'F':
								//std::cout <<"\nWe hit a F (DIAMOND) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'G':
								//std::cout <<"\nWe hit a G (BOX) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'P':
								//std::cout <<"\nWe hit a P (PAST) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'Q':
								//std::cout <<"\nWe hit a Q (IFPAST) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),0));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						default:	if(TFormula->get_type()==5){//Looking at a predicate

				                              //std::cout <<"\nWe have hit a redicate with flag " << flag << "\n" << std::endl;
				                              //std::cout <<"\nWe copy the node and return it.\n" << std::endl;
				                              NTFormula=Formula::copy(TFormula);
				                              return(NTFormula);

                                                }else{
                                                      std::cout <<"\nError in the formula\n" << std::endl;
								      exit(0);
                                                }
					
					}//end of switch
				}//end of else
			}//end of else and case
		case 1:
			if(!isoperator(TFormula->get_val()[0]))
			{
				//it is an atomic proposition
				//add a NOT at the top and return it.
				//std::cout <<"\nWe have hit a leaf with flag " << flag << "\n" << std::endl;
				//std::cout <<"\nWe copy the node, add a ~(NOT) on top and return it.\n" << std::endl;
				NTFormula=Formula::copy(TFormula);
				NTFormula=Formula::negate(NTFormula);
				return(NTFormula);

			}//end of if
			else{
				if(TFormula->get_val()[0]=='~')
				{
					//std::cout <<"\nWe hit a ~(NOT) with " << flag << " at an internal node.\n" << std::endl;
					//std::cout <<"\nRecursively Call the function with flag " << 1-flag << "\n" << std::endl;
					return(const_nnf(TFormula->get_next(),1-flag));
				}	
				else{
					switch(TFormula->get_val()[0])
					{
						case '@':
								//std::cout <<"\nWe hit a @ (AT) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val(TFormula->get_val());
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());


								NTFormula->set_next(const_nnf(TFormula->get_next(),flag));
//we push ~(NOT) inside the local formula. that is quite correct. 
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case '#':
								//std::cout <<"\nWe hit a X (NEXT) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
                                                NTFormula->set_val("#");
								NTFormula->set_type(4);

								NTFormula->set_ctype(1-TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'E':
								//std::cout <<"\nWe hit a X (NEXT) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
                                                NTFormula->set_val("A");
								NTFormula->set_type(3);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'A':
								//std::cout <<"\nWe hit a X (NEXT) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
                                                NTFormula->set_val("E");
								NTFormula->set_type(3);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);


						case '|'://generate a new formula tree node labelled &, attach the nnf of its left and right child respectively and return it.
								//std::cout <<"\nWe hit a |(OR) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val("&");
								NTFormula->set_type(2);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_left(const_nnf(TFormula->get_left(),1));
								NTFormula->set_right(const_nnf(TFormula->get_right(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);


						case '&'://generate a new formula tree node labelled |, attach the nnf of its left and right child respectively and return it.
								//std::cout <<"\nWe hit a & (AND) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								NTFormula->set_val("|");
								NTFormula->set_type(2);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_left(const_nnf(TFormula->get_left(),1));
								NTFormula->set_right(const_nnf(TFormula->get_right(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);


						case 'X':
								//std::cout <<"\nWe hit a X (NEXT) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								//NTFormula->set_val(TFormula->get_val());
								//NTFormula->get_val()[0]='Y';
                                                NTFormula->set_val("Y");
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'Y':
								//std::cout <<"\nWe hit a Y (PREVIOUS) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								//NTFormula->set_val(TFormula->get_val());
								//NTFormula->get_val()[0]='X';
                                                NTFormula->set_val("X");
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'F':
								//std::cout <<"\nWe hit a F (DIAMOND) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								//NTFormula->set_val(TFormula->get_val());
								//NTFormula->get_val()[0]='G';
                                                NTFormula->set_val("G");
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'G':
								//std::cout <<"\nWe hit a G (BOX) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								//NTFormula->set_val(TFormula->get_val());
								//NTFormula->get_val()[0]='F';
                                                NTFormula->set_val("F");
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'P':
								//std::cout <<"\nWe hit a P (PAST) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								//NTFormula->set_val(TFormula->get_val());
								//NTFormula->get_val()[0]='Q';
                                                NTFormula->set_val("Q");
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);

						case 'Q':
								//std::cout <<"\nWe hit a Q (IFPAST) with flag " << flag << "\n" << std::endl;

								NTFormula=new FTree();//is it correct ? constructor ?
								//NTFormula->set_val(TFormula->get_val());
								//NTFormula->get_val()[0]='P';
                                                NTFormula->set_val("P");
								NTFormula->set_type(1);

								NTFormula->set_ctype(TFormula->get_ctype());
								NTFormula->set_bound(TFormula->get_bound());

								NTFormula->set_next(const_nnf(TFormula->get_next(),1));
								NTFormula->set_parent(NULL);
								return(NTFormula);


						default:	if(TFormula->get_type()==5){//Looking at a predicate

				                              //it is a predicate
                              				//add a NOT at the top and return it.
                              				//std::cout <<"\nWe have hit a leaf with flag " << flag << "\n" << std::endl;
				                              //std::cout <<"\nWe copy the node, add a ~(NOT) on top and return it.\n" << std::endl;
				                              NTFormula=Formula::copy(TFormula);
                              				NTFormula=Formula::negate(NTFormula);
                              				return(NTFormula);

                                                }else{
                                                      std::cout <<"\nError in the formula\n" << std::endl;
								      exit(0);
                                                }
					
					}//end of switch
				}//end of else
			}//end of else
		default:
			//std::cout <<"\Error in the flag\n"<<std::endl;
			exit(0);

	}//end of switch

}//end of const_nnf
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
/*FTree* Formula::negate(FTree* TFormula)
{
    FTree* neg_root = Formula::negate(TFormula->root);
    FTree* neg_formula = new FTree(neg_root);
    return neg_formula;
}*/
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
FTree* Formula::negate(FTree* TFormula)
{
			FTree* new_node=NULL;
			FTree* new_subf=NULL;

			new_node=new FTree();//is it correct ? constructor ?
			if(new_node==NULL){
				//printf("\nError in memory allocation\nExiting\n");
				exit(0);
			}
			//printf("\nnegating the formula (in prefix form):");
			//display_FTree_pre(TFormula);
			new_subf=copy(TFormula);
			//printf("\nMade a copy of the formula. The copy (in prefix form) is:");
			//display_FTree_pre(new_subf);
			fflush(stdout);

			new_node->set_type(1);
			//new_node.global=0;
			new_node->set_val("~");
			new_node->set_left(NULL);
			new_node->set_right(NULL);
			new_node->set_next(new_subf);
			return(new_node);

}
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------

//------------------------------------------------------ -------------------------------------------
//--------------------------------------------------------------------------------------------------
bool Formula::ftree_convert()
{

    //  we are going to construct formula tree from formula in std::string form
    //  we expect formula std::string to have substd::strings of the form 
    //  ((#x>k)(\alpha)) or ((#x<=k)(\alpha)) or
    //  ((#x:n>k)(\alpha)) or ((#x:n<=k)(\alpha))
    //  we do not have any = in the formula

	int len=0;
	int i,j;

	int done=-1;
	int in=0;

	bool flag=0;
      bool result;

	int ctype_in=0;

	short ctype_flag=-1;
    

      std::string prop;

	std::string var;
      std::string client;

      std::string cfoval;

//	std::string var1;
//	std::string client1;

//	std::string var2;
//	std::string client2;
	
	std::stack<FTree*> for_stack;	
	std::stack<FTree*> op_stack;

//op_stack should ideally be char stack to allow '(' to be pushed.
//for_stack has to be FTree* stack


	FTree* for_node_n;
	FTree* for_node_l;
	FTree* for_node_r;
	FTree* for_node;

	FTree* op_node;
	FTree* new_op_node;

	std::cout << "We are in the formula to tree conversion routine.\n";

//initialize the client type no. to zero
//this will be computed and updated here using the two add_to_formula_info methods. 

	NoOfCltTypes=0;
      MaxBound=-1;
      NoOfCntQntfrs=0;

	std::cout <<"\nThe input formula is:->" << FormulaText << std::endl;

	len=FormulaText.length();
	std::cout<<"\nLength of the formula is:-> " << len << std::endl;
	i=0;
	while(i<len)
	{
		std::cout<<"\nLooking at the " << i << "th symbol of the formula:" << FormulaText[i]<< std::endl;
		//looking at FormulaText[i]
		switch(isoperator(FormulaText[i])){//we expect operators to be single letter symbols, including ( and ).
		 case 1:
			std::cout<< FormulaText[i] << " is an operator\n";
//Presently the op_prcd method does nothing but differentiate (, ) and other operators. This is so as input is fully parenthesized.
//We will need operator precedence once we remove this constraint on the input.
			switch(op_prcd(FormulaText[i])){
				case 0://**(** do nothing
					std::cout<<"\nWe are looking at the symbol:" << FormulaText[i];
                    ////getchar();
					std::cout<<"\nIgnore, move to the next symbol\n";
					++i;
					continue;
				case 1://**)**
					std::cout<<"\nWe are looking at the symbol:" << FormulaText[i];
					////getchar();
//-----------------------------------------------------------------------------------------------------------------------------
//")" can be encountered in four different places 0. (x) or (x:i) 1. (p(x)) or (p(x:i)) 2. (#x<=k) or (#x:i<=k) or (#x>k) or (#x:i>k) 3. (\alpha op \beta) where op can be | or & or (~\alpha).
//-----------------------------------------------------------------------------------------------------------------------------
					if(FormulaText[i-1]==')'){//look at the operator on the top of the operation stack 
//and accordingly construct a tree by taking one or more operands from the operand stack
						std::cout<<"\npop an operator from the op stack\ncheck whether it is unary or binary\n";
						fflush(stdout);
						if(!op_stack.empty()){
							op_node=op_stack.top();
							op_stack.pop();
						}
						else{
							std::cout << "\nThere is some problem.\n";
							std::cout << "\nWe are trying to access an empty op_stack\n";
							return 0;
						}
						std::cout<<"\nThe operator is:->" << op_node->val;
                                    display_ft(op_node);
						fflush(stdout);
                        //getchar();
						switch(op_type(op_node->val[0])){
							case 1://unary operator
								std::cout<<"\nif unary, pop a subformula from the formula stack\n";
								if(!for_stack.empty()){
									for_node_n=for_stack.top();
									for_stack.pop();
								}
								else{
									std::cout << "\nThere is some problem.\n";
									std::cout << "\nWe are trying to access an empty for_stack\n";
									return 0;
								}
								display_ft(for_node_n);

								op_node->next=for_node_n;
//--------------------------------------------------------------------------------------------------
//Following fields have already been assigned -- The code is redundant.-----------------------------
/*--------------------------------------------------------------------------------------------------
								op_node->type=1;//for unary operator
								op_node->model=-1;//
								op_node->copy=-1;//
								op_node->subd=0;//
								op_node->num=-1;

								op_node->client="-1";

								op_node->iclient=-1;
								op_node->ctype=0;
								op_node->bound=-1;
-------------------------Redundant Code Ends------------------------------------------------------*/
								std::cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								std::cout<<"\npush the new subformula node onto the formula stack...\n";

								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;


							case 2://binary operator
								std::cout<<"\nif binary, pop two subformulas from the formula stack\n";
								if(for_stack.empty()){
									std::cout << "\nThere is some problem.\n";
									std::cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_r=for_stack.top();for_stack.pop();
								display_ft(for_node_r);
								std::cout << "\n";
								if(for_stack.empty()){
									std::cout << "\nThere is some problem.\n";
									std::cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_l=for_stack.top();for_stack.pop();
								display_ft(for_node_l);
								std::cout << "\n";

								op_node->left=for_node_l;
								op_node->right=for_node_r;
//--------------------------------------------------------------------------------------------------
//Following fields have already been assigned -- The code is redundant.-----------------------------
/*--------------------------------------------------------------------------------------------------
								op_node->type=2;//for binary operator
								op_node->model=-1;//
								op_node->copy=-1;//
								op_node->subd=0;//
								op_node->num=-1;

								op_node->client="-1";

								op_node->iclient=-1;
								op_node->ctype=0;
								op_node->bound=-1;
-------------------------Redundant Code Ends------------------------------------------------------*/
/*------------------------------------------Code Not Okay-------------------------------------------
								op_node->iclient=for_node_l->iclient;
								op_node->ctype=for_node_l->ctype;
								op_node->bound=for_node_l->bound;
--------------------------------------------------------------------------------------------------*/

								std::cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								std::cout << "\n";

								std::cout<<"\npush the new subformula node onto the formula stack...\n";
								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;
							case 3://quantifiers
								std::cout<<"\nif quantifier, pop a subformula from the formula stack\n";
								if(for_stack.empty()){
									std::cout << "\nThere is some problem.\n";
									std::cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_n=for_stack.top();for_stack.pop();
								display_ft(for_node_n);
								std::cout << "\n";

//make sure that formula is correctly popped from the formula stack.
								op_node->next=for_node_n;
                                op_node->iclient=for_node_n->iclient;
//--------------------------------------------------------------------------------------------------
//Following fields have already been assigned -- The code is redundant.-----------------------------
/*--------------------------------------------------------------------------------------------------
								op_node->type=3;//for quantifiers
								op_node->model=-1;//
								op_node->copy=-1;//
								op_node->subd=0;//
								op_node->num=-1;

								op_node->client=for_node_n->client;

								op_node->iclient=for_node_n->iclient;
								op_node->ctype=for_node_n->ctype;
								op_node->bound=for_node_n->bound;
-------------------------Redundant Code Ends------------------------------------------------------*/
								std::cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								std::cout << "\n";


								std::cout<<"\npush the new subformula node onto the formula stack...\n";
								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;

							case 4://counting quantifiers
								std::cout<<"\nif counting quantifier, pop a subformula from the formula stack\n";
								if(for_stack.empty()){
									std::cout << "\nThere is some problem.\n";
									std::cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_n=for_stack.top();for_stack.pop();
								display_ft(for_node_n);
								std::cout << "\n";
                                                //getchar();
//make sure that formula is correctly popped from the formula stack.
								op_node->next=for_node_n;
                                                op_node->iclient=for_node_n->iclient;
//The below fields have already been correctly assigned.
								//op_node->type=4;//for counting quantifiers
								//op_node->model=-1;//
								//op_node->copy=-1;//
								//op_node->subd=0;//
								//op_node->num=-1;

								//op_node->client=for_node_n->client;
								//op_node->iclient=for_node_n->iclient;
								//op_node->ctype=for_node_n->ctype;
								//op_node->bound=for_node_n->bound;

//------------------------------We print the fields in the op_node.---------------------------------
                                                std::cout << "\ttype: " << op_node->type;
                                                std::cout << "\tctype: " << op_node->ctype;
                                                std::cout << "\tclient type: " << op_node->client;
                                                std::cout << "\ticlient: " << op_node->iclient;
                                                std::cout << "\tbound: " << op_node->bound;
                                                std::cout << "\n\n";
                                                //getchar();getchar();

								std::cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								std::cout << "\n";


								std::cout<<"\npush the new subformula node onto the formula stack...\n";
								for_stack.push(op_node);
								//display_for_stack();

								i++;
                                                continue;
//the following case of predicate should not occur.
//we have aleady constructed a tree for pred(var:client) and pushed onto formula stack
							case 5://predicates
								std::cout<<"\nif predicate, pop a subformula from the formula stack\n";
								if(for_stack.empty()){
									std::cout << "\nThere is some problem.\n";
									std::cout << "\nWe are trying to access an empty stack.\n";
									return 0;
								}
								for_node_n=for_stack.top();for_stack.pop();
								display_ft(for_node_n);
								std::cout << "\n";

//make sure that formula is correctly popped from the formula stack.
								op_node->next=for_node_n;
								op_node->type=5;//for predicates
//								op_node->model=-1;//
//								op_node->copy=-1;//
//								op_node->subd=0;//
//								op_node->num=-1;
								op_node->client=for_node_n->client;

								std::cout<<"\nConstructed a larger subformula\n";
								display_ft(op_node);
								std::cout << "\n";

								std::cout<<"\npush the new subformula node onto the formula stack...\n";
								for_stack.push(op_node);
								//display_for_stack();

								i++;
								continue;
						}//end of switch(op_type(op_node->val[0]))

					
					}//end of if(FormulaText[i-1]==')')
					else{//do nothing
					//this is the case when we encounter closing paranethesis of 
						std::cout<<"\nIgnored the " << i << "th symbol " << FormulaText[i] << std::endl;
						i++;
						continue;
					}

				case 2:	//if FormulaText[i] is not left or right bracket but an operator (~,&,|,E,A) then construct an internal node and store in the stack, it is an operator proper ~,&,|, et. al.
					std::cout<<"\nLooking at a real operator:" << FormulaText[i] << std::endl;
					fflush(stdout);
					new_op_node= new FTree;
					if(new_op_node==NULL){
						std::cout<<"\nMemory Allocation Error\n";
						exit(1);
					}
					std::cout<<"\nConstructed a tree node to store " << FormulaText[i] << " with pointer " << new_op_node << "\n";
					fflush(stdout);

                    ////getchar();

					new_op_node->val=FormulaText[i];
//					new_op_node->model=-1;
//					new_op_node->copy=-1;
//					new_op_node->subd=0;
//					new_op_node->num=-1;
                    
					new_op_node->parent=NULL;
					new_op_node->right=NULL;
					new_op_node->left=NULL;
					new_op_node->next=NULL;

					new_op_node->client.clear();
                              new_op_node->iclient=-1;
                              new_op_node->ctype=0;
                              new_op_node->bound=-1;

					switch(op_type(new_op_node->val[0])){
						case 1: std::cout<< "\nUnary Operator\n";
							new_op_node->type=1;//unary operator
							i++;
							op_stack.push(new_op_node);
							break;
							
						case 2: std::cout<< "\nBinary Operator\n";
							new_op_node->type=2;//binary operator
							i++;
							op_stack.push(new_op_node);
							break;

						case 3: std::cout<< "\nQuantifier\n";
                                          var.clear();
                                          if(new_op_node->val=="A"){
                                                std::cout << "Invalid input -- we can not have universal quantifier\n";
                                                std::cout << "\nExiting\n";
                                          }
							new_op_node->type=3;//quantifier

                                          new_op_node->ctype=0;//updating ctype
                                          new_op_node->bound=0;//updating bound

							std::cout << "\nType field updated.\n";fflush(stdout);
//FormulaText[i] is either E or A. We expect it to be followed by variable or variable:client-type
							j=1;
							flag=0;
							in=0;
                            
//The following loop is needed--we read from FormulaText and construct val field for the FTree node for quantifier
							while(FormulaText[i+j]!='(' && FormulaText[i+j]!=')'){

								new_op_node->val.push_back(FormulaText[i+j]);
                                
								if(FormulaText[i+j]==':') {
									flag=1;
									in=j;
								}
								j++;
							}
							
							std::cout << "Value field updated.\n";fflush(stdout);
							if(!flag){//flag is false						
								new_op_node->client.clear();//no client info
                                                var = new_op_node->val.substr(1,new_op_node->val.length()-1);
								
							}
							else{//flag is true
//i think the following for loop can be replaced by a single std::string manipulation. i need to check;
//yes we can use substr method---std::string& substr(position,length);
								new_op_node->client.clear();
								//for(int k=in+1; k<=j;k++){
								//	new_op_node->client.push_back(new_op_node->val[k]);
								//}
							      new_op_node->client=new_op_node->val.substr(in+1,new_op_node->val.length()-in-1);
                                                var = new_op_node->val.substr(1,in-1);

							}
							std::cout<< "\nClient field updated.\n";fflush(stdout);
                                          client.clear();
                                          client=new_op_node->client;
//we should add variable (and client) to the list --- No way
                            //result=add_variable_to_formula_info(var,client);
                            //if(result){// a new client has just been added to the list
                            //    ClientList[client]=NoOfCltTypes-1;
                            //    MaxBoundList[client]=1;
                            //}
                                          MaxBoundList[client]=1;
                            //assign the client type as a number >=0
                                          new_op_node->iclient=ClientList[client];
                                          std::cout << "\nThe assigned iclient value to the E node is : " << new_op_node->iclient;
                                          //getchar();
							i=i+j;
							op_stack.push(new_op_node);
							break;



						case 4: std::cout<< "\nCounting Quantifier\n";
							new_op_node->type=4;//counting quantifier
							std::cout << "\nType field updated.\n";fflush(stdout);
//FormulaText[i] is #. We expect it to be followed by variable or variable:client-type and > or <= and a non-negative integer
							j=1;
							flag=0;
							in=0;
							
							ctype_in=0;
                                          cfoval="#";
//The following loop is needed--we read from FormulaText and construct val field for the FTree node for quantifier
							while(FormulaText[i+j]!='(' && FormulaText[i+j]!=')'){
								//new_op_node->val.push_back(FormulaText[i+j]);
                                                cfoval.push_back(FormulaText[i+j]);
								if(FormulaText[i+j]==':') {
									flag=1;
									in=j;
								}
                                                if(FormulaText[i+j]=='>') {
                                                      new_op_node->ctype=0;
									ctype_flag=0;
									ctype_in=j;
								}
                                                if(FormulaText[i+j]=='<') {
                                                      new_op_node->ctype=1;
									ctype_flag=1;
									ctype_in=j;
								}
								j++;
							}
//                            if(ctype_flag==-1){
//                                    std::cout << "\nInvalid input -- We should see a < or >= after #\n";
//                                    std::cout << "\nExiting\n";
//                                    exit(1);
//                            }
							if(!flag){//flag is false						
								new_op_node->client.clear();//no client info
								
							}
							else{//flag is true

								new_op_node->client.clear();

								new_op_node->client=cfoval.substr(in+1,ctype_in-in-1);
							}
							std::cout<< "\nClient field updated.\n";fflush(stdout);

//we store the client name in a seperate std::string as we do not want to dereference new_op_node often.
                                          client.clear();
                                          client=new_op_node->client;

                            switch(ctype_flag){

                            case 0:
                                new_op_node->bound=atoi(cfoval.substr(ctype_in+1,new_op_node->val.length()-ctype_in-1).c_str());
                                if(new_op_node->bound > MaxBound){
                                    MaxBound = new_op_node->bound;
                                }
                                break;

                            case 1:
                                new_op_node->bound=atoi(cfoval.substr(ctype_in+2,new_op_node->val.length()-ctype_in-2).c_str());
                                if(new_op_node->bound > MaxBound){
                                    MaxBound = new_op_node->bound;
                                }
                                break;

                            default:
                                //print error and exit;
                                std::cout << "\nError in Input -- Exiting.\n";
                                exit(1);

                            };
                            std::cout << "The bound value computed for the # node is : " <<  new_op_node->bound << "\n";
                            //getchar();     
                            //getchar();
				//cfoval std::string contains everything including variable, :, client, <, >= and bound
                //we store only the variable name along with # in new_op_node->val -- variable includes client type if any.

                            new_op_node->val.erase();
                            //std::cout << "\nnew_op_node->val is: " << new_op_node->val << "ctype_in is: " << ctype_in << "\n";
                            new_op_node->val=cfoval.substr(0,ctype_in);

						    std::cout << "\nValue field updated. It is "<< new_op_node->val << "\n";fflush(stdout);
                            std::cout << "\ncfoval is "<< cfoval << "\n";
                            //getchar();

//we should add variable (and client) to the list and update the MaxBoundList -- Don't add variable here.
                            //result=add_variable_to_formula_info(new_op_node->val,client);
                            //if(result){// a new client has just been added to the list
                            //    ClientList[client]=NoOfCltTypes-1;
                            //    MaxBoundList[client]=new_op_node->bound;
                            //}
                            
                            if(MaxBoundList[client] < new_op_node->bound){
                                std::cout << "Updating MaxBoundList\n";
                                MaxBoundList[client]=new_op_node->bound;
                                //getchar();
                            }
                            

                            //assign the client type as a number >=0
                            //new_op_node->iclient=ClientList[client];

                            //std::cout << "\nThe assigned client value to the # node is : " << client;
                            //std::cout << "\nThe assigned iclient value to the # node is : " << ClientList[client];
                            //getchar();
                            //getchar();

							i=i+j;
							op_stack.push(new_op_node);
                            NoOfCntQntfrs++;//No of Counting Quantifiers seen is incremented. 
							break;

						case 5: std::cout<< "\nMonadic Predicate\n";
							new_op_node->type=5;//monadic predicate p(var:client)
							j=1;
							while(FormulaText[i+j]!='('){
//we expect predicate p/q/r to be followed with only digits
								new_op_node->val.push_back(FormulaText[i+j]);
								j++;
							}
                            std::cout << "\nThe monadic predicate read is :" << new_op_node->val << "\n";
                            fflush(stdout);
                            ////getchar();
							
//in order to add predicate to formula_info we need client type.
//clearly the predicate should be followed by variable or variable:client-type enclosed in ().
							i=i+j+1;							
							j=0;	
							flag=0; in=0;
							var.clear();
							while(FormulaText[i+j]!=')'){
								var.push_back(FormulaText[i+j]);
								if(FormulaText[i+j]==':') {flag=1;in=j;}
								j++;
							}
							
							if(!flag){//flag is false						
								new_op_node->client.clear();//no client info
								
							}
							else{//flag is true

								new_op_node->client.clear();
								new_op_node->client=var.substr(in+1,var.length()-in-1);
							}
							i=i+j+2;

//we add the predicate to the formula_info
                            client.clear();//the client should be same for predicate and variable.
                            client=new_op_node->client;
//client name is carried into a separate std::string as we do not want to dereference new_op_node/new_for_node often.
							add_predicate_to_formula_info(new_op_node->val,client);

//we should also add a variable to formula_info	
							FTree* new_for_node= new FTree;
							if(new_for_node==NULL){
								std::cout<<"\nMemory Allocation Error\n";
								exit(1);
							}
							std::cout<<"\nConstructed a tree node to store "  << new_op_node->val << " with pointer " << new_op_node;
							fflush(stdout);

                            new_for_node->type=0;
                            new_for_node->ctype=0;
							new_for_node->val=var;
//							new_for_node->model=-1;
//							new_for_node->copy=-1;
//							new_for_node->subd=0;
//							new_for_node->num=-1;
							new_for_node->client=client;//new_for_node->client and new_op_node->client are same.

//the var in the following call is same as new_for_node->val but we do not dereference new_for_node and use var instead.
							result = add_variable_to_formula_info(var,client);
                            if(result){// a new client has just been added to the list
                                std::cout << "\nThe client type is :" << client << "\n"; 
                                ClientList[client]=NoOfCltTypes-1;
                                std::cout << "The corresponding iclient value is " << ClientList[client] << "\n";
                            }
                            //getchar();getchar();

							std::cout<<"\nConstructed a tree node to store "  << new_for_node->val << " with pointer " << new_for_node;
					        fflush(stdout);

                            //assign the client type as a number >=0
                            new_for_node->iclient=ClientList[client];
                            new_op_node->iclient=ClientList[client];
                            std::cout << "\nThe client type is :" << client << "\n"; 
                            std::cout << "The corresponding iclient value is " << new_op_node->iclient << "\n";
                            //getchar();getchar();


							new_op_node->next=new_for_node;	
							for_stack.push(new_op_node);	
							break;

					}//end of switch(op_type(new_op_node->val[0]))
					//std::cout<<"\nLabel for internal node is " << new_op_node->val << "\n";
					//std::cout<<"\nLabel for leaf node is " << new_op_node->next->val << "\n";

					//fflush(stdout);			
					
					std::cout << "\npushed the new op node onto the stack...............\n";
                    std::cout << "\nThe value of i is " << i << "\n"; 
					//display_op_stack();
					continue;

			
			}//end of switch(op_prcd(FormulaText[i]))
		 	continue;
//-------------------end of case 1 for isoperator----------------------------------------------------
		 case 0: //FormulaText[i] is not an operator
			//std::cout<<"\n%c is not an operator",FormulaText[i]);
			fflush(stdout);
//in this case, we shall encounter a proposition -- local property of server.
//local property of clients we have already taken care of as they occur along with variable
//in the form p(x) or p(x:i)
//variables also we have taken care of as they occur with monadic predicates

//here we have to construct token for the server proposition and create a formula node for it
//and push the formula node into the for_stack

			//construct token
			if(FormulaText[i-1]=='('){
				prop.clear();//initialize the token if the preceding character is '('
				std::cout<<"\nInitialized the token.\nWe have to read the full proposition.\n";
				fflush(stdout);
			}
			else{
				std::cout<<"\nThere is some problem with the structure of the input. Exiting.......\n";
				fflush(stdout);
				exit(1);
			}
			//std::cout<<"\nwe are here.1\n";
			//fflush(stdout);
			
			j=i;
			while(FormulaText[j]!=')' ){
				prop.push_back(FormulaText[j]);
				j++;
				//std::cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
				////getchar();
				//std::cout<<"\nwe are here.\n";
				fflush(stdout);

			}

			//std::cout<<"\nwe are here.2\n";
			//fflush(stdout);


			for_node=new FTree;
			if(for_node==NULL){
				std::cout<<"\nMemory Allocation Error\n";
				exit(1);
			}
			for_node->type=0;
			for_node->val=prop;
			for_node_l->client="server";
			//std::cout<<"\nwe are here.\n";
			fflush(stdout);

			//std::cout<<"\nwe are here.\n";
			fflush(stdout);


			fflush(stdout);
			for_node->parent=NULL;
			for_node->right=NULL;
			for_node->left=NULL;
			for_node->next=NULL;

//			for_node->model=-1;
//			for_node->copy=-1;
//			for_node->subd=0;
//			for_node->num=-1;

			for_stack.push(for_node);
			//std::cout<<"\npush the new leaf node onto the stack...............\n";
			fflush(stdout);

//--------------------code for = and !=-------------------------------------------------------------
/*
			//construct token
			if(FormulaText[i-1]=='('||FormulaText[i-1]=='='){
				var1.clear();//initialize the token if the preceding character is '('
				//std::cout<<"\nInitialized the token.\nWe have to read the full variable.\n";
				fflush(stdout);
			}
			else{
				//std::cout<<"\nThere is some problem with the structure of the input. Exiting.......;
				fflush(stdout);
				exit(1);
			}
			//std::cout<<"\nwe are here.1\n";
			//fflush(stdout);
			flag=0;
			j=i;
			while(FormulaText[j]!='='&& FormulaText[j]!='!' && FormulaText[j]!=':' && FormulaText[j]!=')' ){
				var1.push_back(FormulaText[j]);
				j++;
				//std::cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
				////getchar();
				//std::cout<<"\nwe are here.\n";
				fflush(stdout);

			}
			//var1[j-i]='\0';--no longer needed

			//std::cout<<"\nwe are here.2\n";
			//fflush(stdout);

//token carries a variable now. we have to make sure two things at this point, 
//1: is there any client info, 2: is it an equality formula or inequality formula

			
			client1.clear();
			if(FormulaText[j]==':'){
				//there is client info. we need to store it in client1
				i=++j;
				while(FormulaText[j]!='='&& FormulaText[j]!='!' && FormulaText[j]!=')'){
					client1.push_back(FormulaText[j]);
					j++;
					//std::cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
					////getchar();
					//std::cout<<"\nwe are here.\n";
					fflush(stdout);

				}
				//client1[j-i]='\0';--no longer needed
			}
						
			switch(FormulaText[j]){
				case '!':	flag=0;
						i=j+2;
						break;	
						
				case '=':	flag=1;
						i=j+1;
						break;

				default:	cerr << "\nError in input. Exiting";
						exit(1);

			}			

			for_node_l=new FTree;
			if(for_node_l==NULL){
				//std::cout<<"\nMemory Allocation Error\n";
				exit(1);
			}
			for_node_l->type=0;
			for_node_l->val=var1;
			for_node_l->client=client1;
			//std::cout<<"\nwe are here.\n";
			fflush(stdout);
			add_variable_to_formula_info(for_node_l->val,for_node_l->client);
			//std::cout<<"\nwe are here.\n";
			fflush(stdout);
//			if(done){
				//std::cout<<"\nSuccessfully added a variable to the VList.\n"; 
//				formula_info->VNum++;
//			}
			//std::cout<<"\nThe label for leaf node is %s with pointer %p\n",for_node->val,for_node);
			fflush(stdout);
			for_node_l->parent=NULL;
			for_node_l->right=NULL;
			for_node_l->left=NULL;
			for_node_l->next=NULL;

			for_node_l->model=-1;
			for_node_l->copy=-1;
			for_node_l->subd=0;
			for_node_l->num=-1;

//			for_stack.push(for_node);
			//std::cout<<"\npush the new leaf node onto the stack...............\n";
			fflush(stdout);

//now we compute the second part of the equality (inequality)
			if(FormulaText[i-1]=='='){
				var2.clear();//initialize the token if the preceding character is '('
				//std::cout<<"\nInitialized the token.\nWe have to read the full variable.\n";
				fflush(stdout);
			}
			else{
				//std::cout<<"\nThere is some problem with the structure of the input. Exiting.......;
				fflush(stdout);
				exit(1);
			}
			//std::cout<<"\nwe are here.1\n";
			//fflush(stdout);
			
			j=i;
			while(FormulaText[j]!=':' && FormulaText[j]!=')' ){
				var2.push_back(FormulaText[j]);
				j++;
				//std::cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
				////getchar();
				//std::cout<<"\nwe are here.\n";
				fflush(stdout);

			}
			//var2[j-i]='\0';-- no longer needed

			//std::cout<<"\nwe are here.2\n";
			//fflush(stdout);

//token carries a variable now. we have to make sure two things at this point, 
//1: is there any client info, 2: is it an equality formula or inequality formula

			
			client2.clear();
			if(FormulaText[j]==':'){
				//there is client info. we need to store it in client1
				i=++j;
				while(FormulaText[j]!=')'){
					client2.push_back(FormulaText[j]);
					j++;
					//std::cout<<"\nAdding %c to the token\n",FormulaText[j-1]);
					////getchar();
					//std::cout<<"\nwe are here.\n";
					fflush(stdout);

				}
				//client2[j-i]='\0';--no longer needed
			}
						
			for_node_r=new FTree;
			if(for_node_r==NULL){
				//std::cout<<"\nMemory Allocation Error\n";
				exit(1);
			}
			for_node_r->type=0;
			for_node_r->val=var2;
			for_node_r->client=client2;
			//std::cout<<"\nwe are here.\n";
			fflush(stdout);
			add_variable_to_formula_info(for_node_r->val,for_node_r->client);
			//std::cout<<"\nwe are here.\n";
			fflush(stdout);
//			if(done){
				//std::cout<<"\nSuccessfully added a variable to the VList.\n"; 
//				formula_info->VNum++;
//			}
			//std::cout<<"\nThe label for leaf node is %s with pointer %p\n",for_node->val,for_node);
			fflush(stdout);
			for_node_r->parent=NULL;
			for_node_r->right=NULL;
			for_node_r->left=NULL;
			for_node_r->next=NULL;

			for_node_r->model=-1;
			for_node_r->copy=-1;
			for_node_r->subd=0;
			for_node_r->num=-1;

//			for_stack.push(for_node);
			//std::cout<<"\npush the new leaf node onto the stack...............\n";
			fflush(stdout);	

//--------------------------------------------------------------------------------------------------------			
//at this point, we construct a subtree rooted at "=" or "!=" as a special case
			fflush(stdout);
			op_node=new FTree;
			if(op_node==NULL){
				//std::cout<<"\nMemory Allocation Error\n";
				exit(1);
			}
			if(flag==0)
				op_node->val="!=";
			else
				op_node->val="=";
			//std::cout<<"\nThe operator is %s\n",op_node->val);
			fflush(stdout);
			op_node->left=for_node_l;
			op_node->right=for_node_r;
			op_node->type=2;//for binary operator
			op_node->model=-1;//
			op_node->copy=-1;//
			op_node->subd=0;//
			op_node->num=-1;
			op_node->client.clear();

			//std::cout<<"\npush the new subformula node onto the formula stack ...............\n";
			for_stack.push(op_node);

*/
//----------------------code for = and != ends.-----------------------------------------------------

			i=j+1;
			continue;

//-------------------end of case 0 for isoperator----------------------------------------------------
		 case -1:
			//std::cout<<"\nThere is an error in the input. Exiting...........;
			exit(1);
//-------------------end of case -1 for isoperator----------------------------------------------------
		}//end of switch-case(isoperator(FormulaText[i]))
	}//end of while(i<len)


//	for_node=for_stack.top();for_stack.pop();
	FormulaTree=for_stack.top();for_stack.pop();

//print the number of client types.
	std::cout << "\nThe no. of client types mentioned in the formula is: " << NoOfCltTypes << std::endl;

	if(FormulaTree!=NULL){
        std::cout << "Formula tree constructed -- returning 1\n";
		return 1;
    }
	else{
        std::cout << "Formula tree not constructed -- returning 0\n";
		return 0;
    }

}//end of ftree_convert
//---------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------
void Formula::add_predicate_to_formula_info(std::string pred,std::string client)
{
	std::string PE;
//Note that pred does not contain client info.
	PE=pred;
	PE.append(":");
	PE.append(client);
	PE.shrink_to_fit();//works with --std=c++11

	if(PredList.find(PE)==PredList.end())//PE is not in the set PredList
	{
		PredList.insert(PE);
		if(PredNum.find(client)==PredNum.end()){//No entry for client in the map PredNum
			std::cout << "\nInitializing the entry for " << client << " in map PredNum.\n";
			std::cout << "\nRegistering a new client type.\n";
			////getchar();
			//std::cout << "\nLength of client is: " << strlen(client)<< std::endl;
			PredNum[client]=1;
		}
		else{
			std::cout << "\nIncrementing the entry for " << client << " in map PredNum.\n";
			////getchar();
			//std::cout << "\nLength of client is: " << strlen(client)<< std::endl;
			PredNum[client]=PredNum[client]+1;
		}
	}

}

//--------------------------------------------------------------------------------------------------
bool Formula::add_variable_to_formula_info(std::string VE,std::string client)
{

//Note that var contains both variable as well as client info.

	VE.shrink_to_fit();//works with --std=c++11

	if(VarList.find(VE)==VarList.end())//VE is not in the set VarList
	{
		VarList.insert(VE);
		std::cout << "\nInserting variable " << VE << " in the list.\n";
		////getchar();
		if(VarNum.find(client)==VarNum.end()){//No entry for client in the map VarNum
			std::cout << "\nInitializing the entry for " << client << " in map VarNum.\n";
			////getchar();
			//std::cout << "\nLength of client is: " << strlen(client)<< std::endl;
			VarNum[client]=1;
//register a new client type
			NoOfCltTypes++;
//return true
            return true;            

		}
		else{
			std::cout << "\nIncrementing the entry for " << client << " in map VarNum.\n";
			////getchar();
			//std::cout << "\nLength of client is: " << strlen(client)<< std::endl;
			VarNum[client]=VarNum[client]+1;
//return false -- no new client type
            return false;
		}
	}
}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
int Formula::get_bound()
{
/* -- Bound Computation for MFO --
    int B=0;
    int M;
    map <std::string,int> :: const_iterator pos;
    for(pos=PredNum.begin();pos!=PredNum.end();pos++)
    {
        M = 1 << pos->second;
        B = B + VarNum[pos->first] * M;
    }
    return B;
*/

/* -- Bound Computation for CFO -- */
    int PredCount=0;
    int M=0;
    std::map <std::string,int> :: const_iterator pos;
    for(pos=PredNum.begin();pos!=PredNum.end();pos++)
    {
        PredCount += pos->second;
    }
//PredCount is the no. of predicates occuring in the formula
    M = 1 << PredCount;
//M=2^B
//Final Bound is as follows
    return M * (MaxBound+1);    

}
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
std::map <std::string,int> Formula::compute_bounds()
{
    std::map <std::string,int> B;//define a map
    int M;
    std::map <std::string,int> :: const_iterator pos;
    for(pos=PredNum.begin();pos!=PredNum.end();pos++)
    {
        M = 1 << pos->second;
        B[pos->first] =  VarNum[pos->first] * M;
    }
    return B;//return the map containing the bounds for each client type
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
/*
bool Formula::quant_elim()
{
	QEFTree=eliminate_quantifier(FormulaTree);
	if(QEFTree!=NULL)
		return 1;
	else 
		return 0;
}
*/
//--------------------------------------------------------------------------------------------------
/*
FTree* Formula::eliminate_quantifier(FTree* TF)
{

	FTree* root=NULL;
	FTree* new_root=NULL;
	FTree* old_root=NULL;

	FTree* new_subformula=NULL;
	FTree* SubdTFnext=NULL;

	std::string var;
	int i,j,k;

	int M;
	int R;
	std::string client;
	bool flag=0;
	int in=0;
	
//We can not have  global M and R. It depends on client type.

	////getchar();

	std::cout << "\n\n\nWe are in quantifier elimination routine....";
	std::cout << "Looking at the following subformula:";
	display_ft_pre(TF);
	std::cout<<"\n";

	//std::cout<<"\nIn infix form:;
	//display_ft(TF);
	//std::cout<<"\n";
	
	//display_lists();
	//display_nums();

	client=TF->client;
	int PredVal=PredNum[client];
	int VarVal=VarNum[client];
	//std::cout << "The client name is: "<< client<< std::endl;
//	std::cout<<"\nThe no. of predicates for client "<< client<< " is: " << PredVal << std::endl;
//	std::cout<<"\nThe no. of variables is: " << VarVal << std::endl;
//compute M and R for the client type of E
	M=1 << PredVal;
	R=VarVal;
	std::cout<<"\n\nThe no. of models for client "<< client<< " is: " << M << std::endl;
	std::cout<<"\n\nThe no. of copies of models is: " << R << std::endl;

	////getchar();

	//we traverse the formula tree and replace Ex subtree by 2^M-1 'or' subtrees and replace Ax subtree by 2^M-1 'and' subtrees.
	switch(TF->type)
	{
		case 0:// type variable 
				return TF;

		case 1:// type unary connective
				TF->next=eliminate_quantifier(TF->next);
				return TF;

		case 2:// type binary connective
				TF->right=eliminate_quantifier(TF->right);
				TF->left=eliminate_quantifier(TF->left);
				return TF;

		case 3:// type quantifier
				switch(TF->val[0])
				{
					case 'E': 	//replace TF tree with Ev at root by an 'or' rooted tree
							//TF->val contains std::string Evar. we need to extract var
							//k=1;
							var.clear();
							var=TF->val.substr(1,TF->val.length()-1);
							//while(k<size){
							//	var.push_back(TF->val[k]);
							//	k++;
							//}
							//var[k-1]='\0';--no longer needed
							std::cout << "\neliminating E over the variable " << var << std::endl;
							std::cout << "\nAfter eliminating quantifiers from the sub-formula:";
							display_ft_pre_sub(TF->next);
							
							SubdTFnext=eliminate_quantifier(TF->next);
							std::cout<<"\n\nWe get the following formula:";
							display_ft_pre_sub(SubdTFnext);
							std::cout<<"\n\n";
							////getchar();

							//std::cout<<"\nEliminating an existential quantifier E" << var<< std::endl;


							//client=TF->client;
							//std::cout<<"\nThe no. of predicates for client "<< client<< " is: " << PredNum[client] << std::endl;
							//std::cout<<"\nThe no. of variables is: " << VarNum[client] << std::endl;
//compute M and R for the client type of E
							//M=1 << PredNum[client];
							//R=VarNum[client];
							std::cout<<"\nThe no. of models for client "<< client<< " is: " << M << std::endl;
							std::cout<<"\nThe no. of copies of models is: " << R << std::endl;

							////getchar();
//-----------------------------------no problem till here--------------------------------------------------
							for(int i=0;i<M;i++){
								for(int j=0;j<R;j++){
									if(i==0 && j==0){
										root=new FTree;
										root->val="|";
										root->type=2;
										root->client=client;
										std::cout << "\nConstructing a copy of the subformula.......\n";
										new_subformula=copy(SubdTFnext);

										std::cout<<"\nCopy of the subformula with free variable " << var;
										display_ft_pre_sub(new_subformula);
										std::cout<<"\n";

										std::cout<<"\n\nReplacing "<< var << " by " << R*i+j << " in the above formula\n\n";
										////getchar();

										substitute(new_subformula,var,0,0,R*0+0);

										std::cout<<"\nThe substituted subformula is:";
										display_ft_pre_sub(new_subformula);
										std::cout<<"\n\n";

										root->left=new_subformula;
										root->right=NULL;

										std::cout<<"\nThe partially quantifier eliminated formula is:";
										display_ft_pre_sub(root);
										std::cout<<"\n\n";

										old_root=root;
									}
									else if(i==M-1 && j==R-1){
										new_subformula=copy(SubdTFnext);

										std::cout<<"\nCopy of the subformula with free variable " << var;
										display_ft_pre_sub(new_subformula);
										std::cout<<"\n";

										std::cout<<"\n\nReplacing "<< var << " by " << R*i+j << " in the above formula\n\n";
										////getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										std::cout<<"\nThe substituted subformula is:";
										display_ft_pre_sub(new_subformula);
										std::cout<<"\n\n";

										old_root->right=new_subformula;

										std::cout<<"\nThe partially quantifier eliminated formula is:";
										display_ft_pre_sub(old_root);
										std::cout<<"\n\n";

									}
									else{
										new_root=new FTree;
										new_root->val="|";
										new_root->type=2;
										new_root->client=client;

										new_subformula=copy(SubdTFnext);

										std::cout<<"\nCopy of the subformula with free variable " << var;
										display_ft_pre_sub(new_subformula);
										std::cout<<"\n";

										std::cout<<"\n\nReplacing "<< var << " by " << R*i+j << " in the above formula\n\n";
										////getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										std::cout<<"\nThe substituted subformula is:";
										display_ft_pre_sub(new_subformula);
										std::cout<<"\n";

										new_root->left=new_subformula;
										new_root->right=NULL;

										std::cout<<"\nThe partially quantifier eliminated formula is:";
										display_ft_pre_sub(root);
										std::cout<<"\n\n";

										old_root->right=new_root;
										old_root=new_root;
									}
								}//end of for-j
							}//end of for-i
							return root;




					case 'A':	//replace TF tree with Av at root by an 'and' rooted tree

							var.clear();
							var=TF->val.substr(1,TF->val.length()-1);
							//k=1;
							//while(TF->val[k]!='\0'){
							//	var[k-1]=TF->val[k];
							//	k++;
							//}
							//var[k-1]='\0';
							//std::cout<<"\nEliminating an universal quantifier A%s\n",var);
							
							//client=TF->client;
//compute M and R for the client type of A
							//M=1 << PredNum[client];
							//R=VarNum[client];

							SubdTFnext=eliminate_quantifier(TF->next);

							//std::cout<<"\nAfter eliminating quantifiers from the sub-formula:;
							//display_ft_pre_sub(SubdTFnext);
							//std::cout<<"\n\n";							
							////getchar();

							for(int i=0;i<M;i++){
								for(int j=0;j<R;j++){
									if(i==0 && j==0){
										root=new FTree;
										root->val="&";
										root->type=2;
										root->client=client;

										new_subformula=copy(SubdTFnext);

										//std::cout<<"\nCopy of the subformula with free variable %s:",var);
										//display_ft_pre_sub(new_subformula);
										//std::cout<<"\n";
										////getchar();

										substitute(new_subformula,var,0,0,R*0+0);

										//std::cout<<"\nThe substituted subformula is:;
										//display_ft_pre_sub(new_subformula);
										//std::cout<<"\n";

										root->left=new_subformula;

										//std::cout<<"\nThe partially quantifier eliminated formula is:;
										//display_ft_pre_sub(root);
										//std::cout<<"\n";

										old_root=root;
									}
									else if(i==M-1 && j==R-1){
										new_subformula=copy(SubdTFnext);

										//std::cout<<"\nCopy of the subformula with free variable %s:",var);
										//display_ft_pre_sub(new_subformula);
										//std::cout<<"\n";
										////getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										//std::cout<<"\nThe substituted subformula is:;
										//display_ft_pre_sub(new_subformula);
										//std::cout<<"\n";

										old_root->right=new_subformula;

										//std::cout<<"\nThe partially quantifier eliminated formula is:;
										//display_ft_pre_sub(old_root);
										//std::cout<<"\n";

										
									}
									else{
										new_root=new FTree;
										new_root->val="&";
										new_root->type=2;
										new_root->client=client;

										new_subformula=copy(SubdTFnext);

										//std::cout<<"\nCopy of the subformula with free variable %s:",var);
										//display_ft_pre_sub(new_subformula);
										//std::cout<<"\n";

										////getchar();

										substitute(new_subformula,var,i,j,R*i+j);

										//std::cout<<"\nThe substituted subformula is:;
										//display_ft_pre_sub(new_subformula);
										//std::cout<<"\n";

										new_root->left=new_subformula;
										old_root->right=new_root;

										//std::cout<<"\nThe partially quantifier eliminated formula is:;
										//display_ft_pre_sub(root);
										//std::cout<<"\n";

										old_root=new_root;
									}
								}
							}
							return root;


					default: 	//std::cout<<"\nThere is an error in the subformula.\nWe expected a quantifier.\n";
							return 0;
				}			

		case 4:// type predicate
				return TF;

	}
}
*/
//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------
FTree* Formula::copy(FTree* TF)
{


	 FTree* new_node=NULL;
	 FTree* new_subtree=NULL;
	 FTree* new_l_subtree=NULL;
	 FTree* new_r_subtree=NULL;

	//std::cout<<"\nIn the copy routine for:";
	//display_ft_pre_sub(TF);
	if(TF==NULL){
		std::cout<<"\nError in the formula tree.\n";
		return(NULL);
	}
			//std::cout<<"\nThe formula to copy (in prefix form);
			//display_ft_pre_sub(TF);	
			fflush(stdout);

			new_node=new FTree;
			if(new_node==NULL){
				std::cout<<"\nError in memory allocation\nExiting\n";
				exit(1);
			}
			new_node->type=TF->type;
//			new_node->subd=TF->subd;
//			new_node->model=TF->model;
//			new_node->copy=TF->copy;
//			new_node->num=TF->num;

			new_node->val=TF->val;
			new_node->client=TF->client;
			new_node->iclient=TF->iclient;
			new_node->bound=TF->bound;
			new_node->ctype=TF->ctype;


	switch(TF->type){
		case 2: //std::cout<<"\nThe node type is %d",TF->type);
			new_l_subtree=copy(TF->left);
			new_r_subtree=copy(TF->right);
/*------No need to repeat the code---------------------------------
			new_node=new FTree;
			if(new_node==NULL){
				//std::cout<<"\nError in memory allocation\nExiting\n";
				exit(0);
			}
			new_node->type=2;
			new_node->subd=0;
			new_node->model=-1;
			new_node->copy=-1;
			new_node->num=-1;

			new_node->val=TF->val;
			new_node->client=TF->client;
-------------------Repeting code ends here-----------------------*/

			new_node->left=new_l_subtree;
			new_node->right=new_r_subtree;
			new_node->next=NULL;
			return(new_node);
        case 5:
		case 3:
		case 4:
		case 1: //std::cout<<"\nThe node type is %d",TF->type);
			fflush(stdout);
			new_subtree=copy(TF->next);
/*------No need to repeat the code---------------------------------
			new_node=new FTree;
			if(new_node==NULL){
				//std::cout<<"\nError in memory allocation\nExiting\n";
				exit(0);
			}
			new_node->type=TF->type;
			new_node->subd=0;
			new_node->model=-1;
			new_node->copy=-1;
			new_node->num=-1;

			new_node->val=TF->val;
			new_node->client=TF->client;
-------------------Repeting code ends here-----------------------*/
			new_node->left=NULL;
			new_node->right=NULL;
			new_node->next=new_subtree;
			return(new_node);

		case 0: //std::cout<<"\nThe node type is :" << TF->type;
			fflush(stdout);
/*------No need to repeat the code---------------------------------
			new_leaf=new FTree;
			if(new_leaf==NULL){
				std::cout<<"\nError in memory allocation\nExiting\n";
				exit(0);
			}
			new_leaf->type=0;
			new_leaf->subd=TF->subd;
			new_leaf->model=TF->model;	
			new_leaf->copy=TF->copy;
			new_leaf->num=TF->num;

			new_leaf->val=TF->val;
			new_leaf->client=TF->client;
-------------------Repeting code ends here-----------------------*/
			new_node->left=NULL;
			new_node->right=NULL;
			new_node->next=NULL;
			//std::cout << "\n\n";
			return(new_node);		
			

		default:
			std::cout<<"\nError! Type can either be 0, 1, 2, 3, 4 or 5.\n";
			break;

	}
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
/*
void Formula::substitute(FTree* TF,std::string var, int i, int j,int k)
{
//	//std::cout<<"\nReplacing %s by (%d,%d) recursively in the formula:",var,i,j);
//	//display_ft_pre(TF);
//	//std::cout<<"\n";
	if(TF==NULL){
		//std::cout<<"\nFormula is NULL\nThis should not have happened.\n";
		fflush(stdout);
		return;
	}
	switch(TF->type)
	{
		case 0:	if(TF->val==var && TF->subd ==0){
					//std::cout<<"We are replacing %s by (%d,%d) at the leaf level\n",TF->val,i,j);
					TF->model=i;
					TF->copy=j;
					TF->num=k;
					TF->subd=1;
				}
				return;

		case 2:	substitute(TF->left,var,i,j,k);
				substitute(TF->right,var,i,j,k);
				return;	

		case 1:
		case 3:
		case 4:
				substitute(TF->next,var,i,j,k);
				return;
	}
}
*/
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

int Formula::op_type(char symbol)
{
 switch (symbol)
 {
//-------------------------UNARY------------------------------------- 
    case '~'://NOT

    case 'X'://NEXT
    case 'Y'://ONE-STEP PAST

    case 'F'://DIAMOND
    case 'G'://BOX

    case 'P'://DIAMOND MINUS
    case 'Q'://BOX MINUS


	    return 1;
//-------------------------BINARY-------------------------------------
    case '|'://OR
    case '&'://AND
    case '='://EQUALS
    case '%'://IMPLICATION

    case 'U'://UNTIL
    case 'V'://RELEASE
	    return 2;
//------------------------QUANTIFIERS---------------------------------
    case 'E':
    case 'A':
	    return 3;
//------------------------COUNTING QUANTIFIER---------------------------
    case '#':
	    return 4;

//------------------------MONADIC PREDICATES----------------------------------
    case 'p'://local client proposition
//  case 'q':
//  case 'r':
//  case 's':
    case 'l'://load
    case 't'://terminate
	    return 5;
  }
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int Formula::op_prcd(char symbol)
{
 switch (symbol)
 {
//-------------------------UNARY------------------------------------- 
    case '~'://NOT

    case 'X'://NEXT
    case 'Y'://ONE-STEP PAST

    case 'F'://DIAMOND
    case 'G'://BOX

    case 'P'://DIAMOND MINUS
    case 'Q'://BOX MINUS

    case 'E':
    case 'A':
    case '#':

    case 'p':
//  case 'q':
//  case 'r':
//  case 's':
    case 'l'://load
    case 't'://terminate

//-------------------------BINARY-------------------------------------
    case '|'://OR
    case '&'://AND
    case '='://EQUALS
    case '%'://IMPLICATION

    case 'U'://UNTIL
    case 'V'://RELEASE
	    return 2;

    case '(':
	    return 0;
    case ')':
 	    return 1;
 }
 
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int Formula::isoperator(char symbol)
{
 switch (symbol)
 {
 	case '~'://~,V,&,X,U,R,P,Q,Y,F,G
 	case '|':
 	case '&':
 	case '=':
 	case '%':

 	case 'X':
 	case 'Y':
 	case 'U':


 	case 'V':
 	case 'F':
 	case 'G':
 	case 'P':
 	case 'Q':

 	case 'E'://\exists
 	case 'A'://\forall
	case '#'://counting quantifier

 	case 'p'://local client proposition

      case 'l'://load
 	case 't'://terminate

 	case '(':
 	case ')':
 		return 1;//non-variables

 	case 'q'://local server proposition
// 	case 'r':
// 	case 's':

 	case 'x':
 	case 'y':
 	case 'z':
 		return 0;//variables

	default: 
		return -1;//illegal input
 }

}
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
