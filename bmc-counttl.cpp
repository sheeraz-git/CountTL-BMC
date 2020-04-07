#include "bmc-counttl.h"
//--------------------------------------------------------------------------------------------------
void dummy_display_ft(FTree* FT)
{
	
	if(FT==NULL){
		std::cout <<"\nError in the formula tree.\n" << std::endl;
		return;
	}
	switch(FT->get_type()){

		case 2: //std::cout <<"\nThe node type is " << FT->get_type() << std::endl;
            std::cout << "(";
			dummy_display_ft(FT->get_left());
			std::cout << FT->get_val();
			dummy_display_ft(FT->get_right());
            std::cout << ")";
			break;

		case 1: //std::cout <<"\nThe node type is " << FT->get_type() << std::endl;
            std::cout << "(";
			std::cout << FT->get_val();
			dummy_display_ft(FT->get_next());
            std::cout << ")";
			break;

		case 0:// std::cout <<"\nThe node type is " << FT->get_type()<<std::endl;
            std::cout << "(";
			std::cout << FT->get_val();
            std::cout << ")";
			break;

		default:
			std::cout <<"\nError! Type can either be 0,1 or 2.\n" << std::endl;
			break;
	}

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void dummy_display_ft_pre(FTree* FT)
{
	
	if(FT==NULL){
		std::cout <<"\nError in the formula tree.\n" << std::endl;
		return;
	}
	switch(FT->get_type()){
		case 2: 
            //std::cout <<"\nThe node type is " << FT->get_type()<<std::endl;
			std::cout << FT->get_val();
			dummy_display_ft_pre(FT->get_left());
			dummy_display_ft_pre(FT->get_right());
			break;

		case 1: 
            //std::cout <<"\nThe node type is " << FT->get_type()<<std::endl;
			std::cout << FT->get_val();
			dummy_display_ft_pre(FT->get_next());
			break;

		case 0: 
            //std::cout <<"\nThe node type is " << FT->get_type()<<std::endl;
            std::cout << "(";
			std::cout << FT->get_val();
            std::cout << ")";	
			break;

		default:
			std::cout <<"\nError! Type can either be 0,1 or 2.\n" << std::endl;
			break;
	}

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int main()
{
//--------------------------------------------------------------------------------------------------
//---------------------------------------- CONVENTIONS ---------------------------------------------
//------ | means lor------ & means land----- ^ means lxor--- % means limplies-- ~ means lnot--------
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//Create an object of the type CountTLBMC to start the CountTL BMC algorithm.
//--------------------------------------------------------------------------------------------------
      counttl_bmc CountTLBMC;//uses the default constructor: don't we need any parameters ?
//--------------------------------------------------------------------------------------------------
//Call the root method that does the rest.
//--------------------------------------------------------------------------------------------------
      bool result=CountTLBMC.init();
//-------------------------------------------------------------------------------------------------- 	
      return 0;
}
//--------------------------------------------------------------------------------------------------
void counttl_bmc::print_trace(int k)
{
                    model m = S.get_model();
 //                   std::cout << m << "\n\n" <<std::endl;
    // traversing the model
                    for (unsigned i = 0; i < m.size(); i++) {
                 //       std::cout << m[i] << "\n\n" <<std::endl;
                        func_decl v = m[i];
                //        std::cout << v << "\n\n" <<std::endl;
                    // this problem contains only constants
                 //       assert(v.arity() == 0); 
                        std::cout << v.name() << " = " << m.get_const_interp(v) << " ";
                    }
                    std::cout << "\n\n" <<std::endl;


}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool counttl_bmc::init()
{
/*
//--------------------------------------------------------------------------------------------------
//--------------------------------CODE FOR LTL BMC--------------------------------------------------
//--------------------------------------------------------------------------------------------------
//	std::string IF = "(((x0)=(f))&((x1)=(f)))";//Boolean formula for Input state set	

// 	std::string IF = "(((x0)=(f))&((x2)=(f)))";//Boolean formula for Input state set	

// 	std::string IF = "(((x1)=(f))&((x2)=(f)))";//Boolean formula for Input state set 

// 	std::string IF = "(((x0)=(t))&((x2)=(f)))";//Boolean formula for Input state set

//	std::string IF = "((((x0)=(f))&((x1)=(f)))&((x2)=(f)))";//Boolean formula for Input state set	

//    std::string TF = "(((y0)=(x1))&(((y1)=(x2))&((y2)=(t))))";//Boolean formula for Transition Relation

//    std::string TLF = "(G((((x0)=(t))&((x1)=(t)))&((x2)=(t))))";//CountTL Formula with G modality

// 	std::string TLF = "(F((((x0)=(t))&((x1)=(t)))&((x2)=(t))))";//CountTL Formula with F modality

//	std::string TLF = "(((x0)=(f))U((x0)=(t)))";//CountTL Formula with U modality

//    std::string TLF = "(X(((x1)=(f))U((x1)=(t))))";//CountTL Formula with X and U modality
//--------------------------------------------------------------------------------------------------
//------------------------------- CONVENTIONS-------------------------------------------------------
//-------| means lor-------& means land------^ means lxor----% means limplies---~ means lnot--------
//--------------------------------------------------------------------------------------------------
//-------------------------------Two bit Counter----------------------------------------------------
//	std::string IF = "(((x0)=(f))&((x1)=(f)))";

//	std::string TF = "((~((y0)^(~(x0))))&(~((y1)^((x0)^(x1)))))";
//--------------------------------------------------------------------------------------------------
//-------------------------------CountTL Properties-----------------------------------------------------
//--------------------------------------------------------------------------------------------------
//	std::string TLF = "(G((((x0)=(f))%(X((x0)=(t))))&((((x0)=(t))%(X((x0)=(f))))))";

//	std::string TLF = "(G((((x0)=(t))&(X((x0)=(f))))%((((x1)=(t))&(X((x1)=(f)))|(((x1)=(f))&(X((x1)=(t))))))))";

//	std::string TLF = "(G(((x0)=(f))|((x1)=(f))))";
//--------------------------------------------------------------------------------------------------
//---------------------------------------Safety Property--------------------------------------------
//--------------------------------------------------------------------------------------------------
//	std::string TLF = "(G(((~(x0))|(~(x1)))|(~(x2))))";//at least one of the state variable is 0
//--------------------------------------------------------------------------------------------------
//--------------------------------------Liveness Property-------------------------------------------
//--------------------------------------------------------------------------------------------------
//    std::string TLF = "(F(((x0)&(x1))&(x2)))";//all the state variables are eventually 1
//--------------------------------------------------------------------------------------------------
//	std::cout << "The initial state set in symbolic form:" << IF << "\n\n" <<std::endl;

//	std::cout << "The Transition relation in symbolic form:" << TF << "\n\n" <<std::endl;

//	std::cout << "The CountTL Formula in symbolic form:" << TLF << "\n\n" <<std::endl;
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
      std::cout << "\n\nEnter the no. of state variables:->";
      std::cin >> this->N;
      std::cout << "\n\n" <<std::endl;            
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
	// loop for creating the current state variables [x0,x1,x2,etc.]
	for(unsigned i=0; i<this->N; ++i){
		std::stringstream xName;
		xName << "x" << i;
		this->x.push_back(c.bool_const(xName.str().c_str()));
	}
	std::cout << this->x << "\n\n" <<std::endl;fflush(stdout);
//--------------------------------------------------------------------------------------------------
	// loop for creating the next state variables [y0,y1,y2,etc.]
//--------------------------------------------------------------------------------------------------
	for(unsigned i=0; i<this->N; ++i){
		std::stringstream yName;
		yName << "y" << i;
		this->y.push_back(c.bool_const(yName.str().c_str()));
	}
	std::cout << this->y << "\n\n" <<std::endl;fflush(stdout);
//--------------------------------------------------------------------------------------------------
//-----------The following state transition system is symbolically represented as (IF,TF)-----------
//------------------------>000->100->110->111->111--------------------------------------------------
//--------------------------------------------------------------------------------------------------
      this->IF=(!x[0] && !x[1] && !x[2]); // initial state formula --- initial state is (0,0,0)
      std::cout << "I is :" << this->IF << "\n\n" <<std::endl;fflush(stdout);

      this->TF= (y[0]== x[1]) && (y[1]==x[2]) && y[2];// transition relation formula --- right shift with MSB 1
      std::cout << "T is :" << this->TF << "\n\n" <<std::endl;fflush(stdout);
    
      std::getchar();
//--------------------------------------------------------------------------------------------------
//--Convert the CountTL Formula TLF in text (string type) form to tree (FTree*) form	
//--Then assign this to CountTLF, so that it can later be used by other methods.
//--------------------------------------------------------------------------------------------------
      Formula CountTLFormula(TLF);//Creating an object of the type Formula with parameter TLF
	CountTLFormula.ftree_convert();//Converting TLF to tree form.
	std::cout <<  "\nFormula Tree for TLF Constructed...............\n" <<std::endl;
//	return(0);

//read the formula tree for TLF and print the leaves
	std::cout <<  "\nReading the Formula Tree...............\n" <<std::endl;
	std::cout <<  "\nIn infix form:";
	CountTLFormula.display_formula();
	std::cout << "\n\n\n" <<std::endl;
	std::cout << "\nIn prefix form:";
	CountTLFormula.display_formula_pre();
	std::cout << "\n\n\n" <<std::endl;

	std::getchar();
//	return(0);
//--------------------------------------------------------------------------------------------------
//--------------Negate the CountTLFormula and construct the NNF-------------------------------------
//--------------------------------------------------------------------------------------------------
      FTree* TFormula = CountTLFormula.get_ftree();
      FTree* NegTFormula = FTree::negate(TFormula);
      FTree* NegTFormulaRoot = NegTFormula->get_root();
      FTree* TLFNode = CountTLFormula.const_nnf(NegTFormulaRoot,-1);   
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------Assign the CountTL formula, in tree form, to the appropriate data member----------------
//---------------------- in the counttl_bmc object we are working with.-----------------------------
//--------------------------------------------------------------------------------------------------    
      this->CountTLF = new FTree(TLFNode);
//--------------------------------------------------------------------------------------------------
//---------------------definition of logical constants f and t.-------------------------------------
//--------------------------------------------------------------------------------------------------
      this->f=c.bool_const("f");
      this->t=c.bool_const("t");
//--------------------------------------------------------------------------------------------------
//---------For k=0, we don't need to initialize x[0],x[1],.......,x[N-1]. Already done above.
//--------------------------------------------------------------------------------------------------
//------Compute the necessary formulas for k=0 trace length, by calling the translate method.
//--------------------------------------------------------------------------------------------------
      this->translate(0);
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Now compute the actual formula to be sent to SAT solver, for k=0 trace length.
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------		
      S.add(alpha[0] && beta[0]);
	bool result=S.check();

	if(result==sat){
//Print the counterexample and exit	
		std::cout <<"\nThe counterexample is of length 0";
		std::cout << "\n(";
        print_trace(0);
		return 0;
	}
	else{
		std::cout <<"\nNo counterexample of length 0";
		std::cout <<"\n----------------------------------------------------------------\n" <<std::endl;
		std::getchar();	
				
	}
    S.reset();
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Run a loop to inductively check property for trace lengths of k>0.
//--------------------------------------------------------------------------------------------------
	int k=1;
	while(1){
		std::cout <<"\nLooking at traces of length " << k;
//--------------------------------------------------------------------------------------------------
//--------------Before we compute the various formulas in the translate routine,--------------------
//------------------ we should initialize the sequence of x expressions.----------------------------
//--------------------------------------------------------------------------------------------------
//------------loop for creating the current state variables [xk*N+0,xk*N+1,xk*N+2,etc.]-------------
//--------------------------------------------------------------------------------------------------
	 	for(unsigned i=0; i<N; ++i){
		    std::stringstream xName;
		    xName << "x" << k*N+i;
		    x.push_back(c.bool_const(xName.str().c_str()));
    	}
       	std::cout << "list of x variables:" << x << "\n\n" <<std::endl;
       	std::getchar();
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Translate the CountTLFormula to a PL formula for all traces of length k in the transition system (IF,TF).
//CountTLformula is being asserted in an initial state at the time instant 0.
//The CountTLFormula is encoded into the trace of length k. 
//This is done through an inductive process starting from point 0.
//That is why we have an i in the encoding.
//--------------------------------------------------------------------------------------------------
		this->translate(k);
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Now compute the actual formula to be sent to SAT solver
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------			
        S.add(alpha[k] && beta[k]);
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//Reset the previous switches
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
		result=S.check();

		if(result==sat){
//Print the counterexample and exit	
			std::cout <<"\nThe counterexample is of length "<< k << "\n" <<std::endl;fflush(stdout);
			std::getchar();
            print_trace(k);
			return 0;
		}
		else{
//Continue the loop
			std::cout <<"\nNo counterexample of length "<< k << "\n" <<std::endl;
			std::cout <<"\n----------------------------------------------------------------\n" <<std::endl;
//--------------------------------------------------------------------------------------------------
			k++;//move to the next trace length
            S.reset();//reset the SAT-solver state
            std::cout<<"Move to the next trace length k =  " << k << "\n";
			std::getchar();
			continue;
		}
			

	}
//-------------------------------------------------------------------------------------------------- 	
	return 0;
//-------------------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------------------- 
//------------------------CODE FOR LTL BMC ENDS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

*/

//--------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------- 
//-------------------------CODE FOR CountTL BMC BEGINS----------------------------------------------
//-------------------------------------------------------------------------------------------------- 
//    int     N_s;//N_s represents no. of state variables
//    int     N_c;//N_c represents no. of client types

//      expr    path(c); // expr that contains the path so far.
//      expr    loopFree(c); // expr that contatins the loopFree formula so far.
//      solver  S(c); // solver that is used to check satisfiability of formulas constructed.

      std::cout << "\n\nEnter the no. of state variables:->";
      std::cin >> this->N_s;
      std::cout << "\n\n";            

      std::cout << "\n\nEnter the no. of client types:->";
      std::cin >> this->N_c;
      std::cout << "\n\n";            
	
	// loop for creating the current state variables [x0, x1, x2, etc.]
	for(unsigned i=0; i<N_s; ++i){
		std::stringstream xName;
		xName << "x" << i;
		this->x.push_back(c.bool_const(xName.str().c_str()));
	}
	std::cout << this->x << "\n\n";

	// loop for creating the next state variables [y0, y1, y2, etc.]
	for(unsigned i=0; i<N_s; ++i){
		std::stringstream yName;
		yName << "y" << i;
		this->y.push_back(c.bool_const(yName.str().c_str()));
	}
	std::cout << this->y << "\n\n";

	// loop for creating the current counter variables [u0, u1, u2, etc.]
	for(unsigned i=0; i<N_c; ++i){
		std::stringstream uName;
		uName << "u" << i;
		this->u.push_back(c.int_const(uName.str().c_str()));
	}
	std::cout << this->u << "\n\n";

	// loop for creating the next counter variables [v0, v1, v2, etc.]
	for(unsigned i=0; i<N_c; ++i){
		std::stringstream vName;
		vName << "v" << i;
		this->v.push_back(c.int_const(vName.str().c_str()));
	}
	std::cout << this->v << "\n\n";

	// loop for creating the input variables [ip0, ip1, ip2, etc.]
	for(unsigned i=0; i<N_c; ++i){
		std::stringstream ipName;
		ipName << "ip" << i;
		this->ip.push_back(c.bool_const(ipName.str().c_str()));
	}
	std::cout << this->ip << "\n\n";

	// loop for creating the input variables [ip0, ip1, ip2, etc.]
	for(unsigned i=0; i<N_c; ++i){
		std::stringstream ipeName;
		ipeName << "ipe" << i;
		this->ipe.push_back(c.bool_const(ipeName.str().c_str()));
	}
	std::cout << this->ipe << "\n\n";

//-------As N_s = 2, The number of (local) states in the counter system is 4. Let us call them q0=00, q1=01, q2=10 and q3=11. 
//-------Initial state is q0=00. The ip variable captures the request and answer messages in the system. As N_c = 2, the number of counters are 2 which keep track of number of active clients of each type in the system. 
//-------ip0=TRUE means there is a request of type 0 in the system. This leads to addition of a client of type 0 in the system. If ip0=FALSE then there is answer of type 0 in the system. This leads to removal of a client of type 0 from the system.
//-------How the internal state of the system changes with respect to the inputs coming to the system is captured by transition relation T.

//-------T is as follows: q0--req0-->q1--req1-->q2--ans0-->q3--ans1-->q0.
//-------which is the same as: q0--ip0-->q1--!ip0-->q2--ip1-->q3--!ip1-->q0.

//-------The behaviour of T is as follows: q0-->q1 increments the counter0, q1-->q2 increments counter1, q2-->q3 decrements counter0, q3-->q0 decrements counter1.

	this->IF=(!x[0] && !x[1]); // initial state formula
      std::cout << "I is :" << this->IF << "\n\n";

//-------Why do we have an extra (set of) variable/s, ipe?

	expr 	alpha1=(!x[0] && !x[1] && ipe[0] && ip[0]);
	expr 	alpha2=(x[0] && !x[1] && ipe[0] && !ip[0]);
	expr 	alpha3=(!x[0] && x[1] && ipe[1] && ip[1]);
	expr 	alpha4=(x[0] && x[1] && ipe[1] && !ip[1]);

	expr	alpha=alpha1 || alpha2 || alpha3 || alpha4;

	this->TF= implies(alpha1,y[0] && !y[1]) && implies(alpha2,!y[0] && y[1]) && implies(alpha3,y[0] && y[1]) && implies(alpha4,!y[0] && !y[1]) && implies(!alpha,y[1]==x[1] && y[0]==x[0]); // transition formula

      std::cout << "T is :" << this->TF << "\n\n";

	expr 	iP=(u[0]==0) && (u[1]==0); 
	std::cout << "iP is :" << iP << "\n\n";
	
//	expr	P(c); // property formula

//-------------------------------CountTL Formula Inputs---------------------------------------------
// We shall have a number of CountTL formulas here.
// We consider safety properties	 

//	std::string CountTLF="(Ex(l(x)))";//--output correct
//	std::string CountTLF="((#x:1>1)(l(x:1)))";//--output correct
//	std::string CountTLF="(((#x:1>1)(l(x:1)))&((#y:2<=2)(l(y:2))))";//--output correct

//  here we have a safety property with X modality
// if there are >1 active clients of type 1 then at least one of them are terminated in the next instance.
	std::string CountTLText="(((#x:1>1)(l(x:1)))%(X(Ex:1(t(x:1)))))";//--


//define a Formula object. This will create a formula object with expression (formula : CountTLText) as raw text.
	Formula CountTLFormula(CountTLText);

//Using the methods in formula object we compute, first the formula tree and then eliminate quantifiers from the formula.
//In this process, we gather necessary data from the formula, which can be used later -- Are we eliminating quantifiers here ?


	std::cout <<"\nThe input formula is:->" << CountTLText << std::endl;

//convert the CountTLF to CountTLF tree.
	bool done=CountTLFormula.ftree_convert();
	if(!done){
		std::cout<< "\nFormula tree construction fails.\n";
		return 0;
	}
	std::cout <<"\nFormula Tree Constructed...............\n";
	std::cout <<"\nReading the Formula Tree...............\n";
	std::cout <<"\nIn infix form:";
	CountTLFormula.display_ftree();
	std::cout <<"\n";
	std::cout <<"\nIn prefix form:";
	CountTLFormula.display_ftree_pre();
	std::cout <<"\n";

	CountTLFormula.display_lists();
	CountTLFormula.display_nums();

      return 0;
//--------------------------------------------------------------------------------------------------
//--------------Negate the CountTLFormula, construct the NNF and------------------------------------
//--------------Assign the CountTL formula, in tree form, to the appropriate data member------------
//---------------------- in the counttl_bmc object we are working with.-----------------------------
//--------------------------------------------------------------------------------------------------
      FTree* TFormula = CountTLFormula.get_ftree();
      FTree* NegTFormula = Formula::negate(TFormula);
      this->CountTLF = CountTLFormula.const_nnf(NegTFormula,-1);   
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//-----------configurations are different from states.---------------------------------------------- 
//-----------initial configuration this->CountIF=I && u0==0 && u1 ==0-------------------------------
//--------------------------------------------------------------------------------------------------
      int MB = CountTLFormula.get_bound();
	this->CountIF=this->IF;
	for(unsigned i=0; i<N_c; ++i){
		this->CountIF=this->CountIF && (u[i]==0);
	}// This is okay. We want all counters to be zero intially. We also need to make sure they remain non-negative. 

//u[i] is the value of the ith counter before the transition. v[i] is the value of the ith counter after the transition.

	this->CountTF=this->TF;
	for(unsigned i=0; i<N_c; ++i){
		this->CountTF=this->CountTF && implies(ipe[i]&& ip[i],(v[i]== u[i]+1)) 
                                                                && implies(ipe[i] && !ip[i],(v[i]== u[i]-1)) 
                                                                && implies(!ipe[i],(v[i]==u[i])) 
                                                                && u[i] >=0 && v[i]>=0;
                                                               // && u[i] <= MB && v[i] <= MB;
	}


/*
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//-------------------------------CountTL Formula Inputs---------------------------------------------
//-----------Now encode CountTL formula into a Z3 expression over counter values--------------------
//--------------------------------------------------------------------------------------------------
      expr P = encode_into_pl(this->CountTLF,0,0);
      std::cout << "\n" << P << "\n";
//--------------------------------------------------------------------------------------------------
    //check whether initial states (this->CountIF) are consistent with the property (P).
	S.add(this->CountIF && P);
//--------------------------------------------------------------------------------------------------
 // std::cout<<s<<"\n\n";
      if(S.check()==sat){
            std::cout << "\n\nInitial Property does not hold for some path of length 0 (i.e., some initial state).\n\n Here is the state---->";
            std::cout << "\n\nLooking at the model\n\n";
            model m = S.get_model();
            std::cout << m << "\n\n";
    // traversing the model
            for (unsigned i = 0; i < m.size(); i++) {
                  std::cout << m[i] << "\n\n";
                  func_decl v = m[i];
            //std::cout << v << "\n\n";                    
                  std::cout << v.name() << " = " << m.get_const_interp(v) << "\t";
            }
            std::cout << "\n\n";
            //getchar();
            return 0;
      }     //end of if
      else{
            std::cout << "\n\nProperty holds for all paths of length 0 (i.e., all initial states).\n\nContinue.........";
            //getchar();
            //getchar();
            S.reset();
      }//end of else
//    return 0;
//--------------------------------------------------------------------------------------------------	
      int k=1;
      while(1){ // 
//The encoding of the property will change with the size of the trace -- due to the presence of X.
		P = encode_into_pl(this->CountTLF,0,k);
//--------------------------------------------------------------------------------------------------
//First we construct expression vectors that will be needed to intantiate T and P
//--------------------------------------------------------------------------------------------------
//For state variables -- why are we using different expression vectors instead of x ?
//--------------------------------------------------------------------------------------------------
            expr_vector	z(c);
				for(unsigned i=0; i<k*N_s; ++i){
					std::stringstream xName;
					xName << "x" << i;
					z.push_back(c.bool_const(xName.str().c_str()));
				}
                //std::cout << z << "\n\n";
                expr_vector	z0(c);
				for(unsigned i=0; i<N_s; ++i){
					std::stringstream xName;
					xName << "x" << i+N_s*(k-1);
					z0.push_back(c.bool_const(xName.str().c_str()));
				}
		        //std::cout << z0 << "\n\n";
                expr_vector	z1(c);
				for(unsigned i=0; i<N_s; ++i){
					std::stringstream xName;
					xName << "x" << i+N_s*k;
					z1.push_back(c.bool_const(xName.str().c_str()));
				}
		        //std::cout << z1 << "\n\n";
//--------------------------------------------------------------------------------------------------
				for(unsigned i=0; i<N_s; ++i){
					std::stringstream xName;
					xName << "x" << i+N_s*k;
					x.push_back(c.bool_const(xName.str().c_str()));
				}
//--------------------------------------------------------------------------------------------------
//For counter variables  -- why are we using different expression vectors instead of u ?
//--------------------------------------------------------------------------------------------------
                expr_vector	w(c);
				for(unsigned i=0; i<k*N_c; ++i){
					std::stringstream uName;
					uName << "u" << i;
					w.push_back(c.int_const(uName.str().c_str()));
				}
                //std::cout << w << "\n\n";
                expr_vector	w0(c);
				for(unsigned i=0; i<N_c; ++i){
					std::stringstream uName;
					uName << "u" << i+N_c*(k-1);
					w0.push_back(c.int_const(uName.str().c_str()));
				}
		        //std::cout << w0 << "\n\n";
                expr_vector	w1(c);
				for(unsigned i=0; i<N_c; ++i){
					std::stringstream uName;
					uName << "u" << i+N_c*k;
					w1.push_back(c.int_const(uName.str().c_str()));
				}
		        //std::cout << w1 << "\n\n";
//--------------------------------------------------------------------------------------------------
				for(unsigned i=0; i<N_c; ++i){
					std::stringstream uName;
					uName << "u" << i+N_c*k;
					u.push_back(c.bool_const(uName.str().c_str()));
				}
//--------------------------------------------------------------------------------------------------
//For input variables  -- why are we using different expression vectors instead of ip and ipe ?
//--------------------------------------------------------------------------------------------------
                expr_vector	jp(c);
				for(unsigned i=0; i<N_c; ++i){
					std::stringstream ipName;
					ipName << "ip" << i+N_c*(k-1);
					jp.push_back(c.bool_const(ipName.str().c_str()));
				}
		        //std::cout << jp << "\n\n";
                expr_vector	jpe(c);
				for(unsigned i=0; i<N_c; ++i){
					std::stringstream ipeName;
					ipeName << "ipe" << i+N_c*(k-1);
					jpe.push_back(c.bool_const(ipeName.str().c_str()));
				}

		        //std::cout << jpe << "\n\n";
//--------------------------------------------------------------------------------------------------
				for(unsigned i=0; i<N_c; ++i){
					std::stringstream ipName;
					ipName << "u" << i+N_c*k;
					ip.push_back(c.bool_const(ipName.str().c_str()));
				}
				for(unsigned i=0; i<N_c; ++i){
					std::stringstream ipeName;
					ipeName << "u" << i+N_c*k;
					ipe.push_back(c.bool_const(ipeName.str().c_str()));
				}
//--------------------------------------------------------------------------------------------------
//Now, compute loopFree expression ------------- This is important --- Needed for termination ------
//--------------------------------------------------------------------------------------------------
/*              expr temp0(c);
                expr temp1(c);
                temp0=(z1[0]!=z[0]);
                for(unsigned i=1; i<N_s; ++i){
                    temp0=temp0 || (z1[i]!=z[i]);
                }
                for(unsigned i=1; i<N_c; ++i){
                    temp0=temp0 || (w1[i]!=w[i]);
                }
                temp1=temp0;
                for(unsigned j=1; j<k; ++j){
                    temp0=(z1[0]!=z[N_s*j]);
                    for(unsigned i=1; i<N_s; ++i){
                        temp0=temp0 || (z1[i]!=z[N_s*j+i]);
                    }
                    for(unsigned i=1; i<N_c; ++i){
                        temp0=temp0 || (w1[i]!=w[N_c*j+i]);
                    }

                    temp1=temp1 && temp0;
                }

                if(k==1){
                    loopFree=temp1;
                }
                else{
                    loopFree=loopFree && temp1;
                }
                std::cout << "\n\nLoopFree formula is-->"<< loopFree <<"\n\n";
                //getchar();*/
//--------------------------------------------------------------------------------------------------
//Now, instantiate T and compute path expression
//--------------------------------------------------------------------------------------------------      
//subT is T(x,y) with x=(x0,x1,x2) replaced current state z0 and y=(y0,y1,y2) replaced by next state z1.
//--------------------------------------------------------------------------------------------------
/*
                expr subTF(c);
                subTF=this->CountTF.substitute(y,z1);
		        //std::cout << subT << "\n\n";

                subTF=subTF.substitute(x,z0);
		        //std::cout << subT << "\n\n";
		
		        //std::cout << "v is " << v << "\n\n";
		        //std::cout << "w1 is " << w1 << "\n\n";

                subTF=subTF.substitute(v,w1);
		        //std::cout << subT << "\n\n";

                subTF=subTF.substitute(u,w0);
		        //std::cout << subT << "\n\n";

                subTF=subTF.substitute(ip,jp);
		        //std::cout << subT << "\n\n";

                subTF=subTF.substitute(ipe,jpe);
		        //std::cout << subT << "\n\n";

               //std::cout << "T substituted : " << subT << "\n\n"; 
               //getchar();
//update the path expression by adding subT
                if(k==1){
                    path=subTF;
                }
                else{
                    path=path && subTF;
                }
//Now, instantiate P
                //expr subP(c);
                //subP=iP.substitute(x,z1);
                //std::cout << "P substituted : " << subP << "\n\n"; 
                //getchar();

//Before we do safety check, we need to check the bound (forward and/or backward)
//first, check forward bound
/*                S.add(this->CountIF && path && loopFree);		
                if(S.check()==unsat){//there is no path of length k starting from a initial state with all states distinguishable.
//that means there is a (k,l) loop with 0<=l<=k
                    std::cout << "\n\nForward bound reached for k= " << k << ".\n\nSafety Property holds for all reachable stateS. \n\nExiting......\n\n";
                    return 0;
                }
                else{
                     std::cout << "\n\nForward bound not reached.\n\nChecking backward bound......\n\n";   
                     S.reset();
                }
//now check backward bound
               S.add(path && loopFree && !subP);  
               if(S.check()==unsat){//there is no path of length k starting from an unsafe state with all states distinguishable.
//that means we can not reach from an unsafe state to initial state
                    std::cout << "\n\nBackward bound reached for k= " << k << ".\n\nSafety Property holds for all reachable states. \n\nExiting......\n\n";
                    return 0;
                }
                else{
                     std::cout << "\n\nBackward bound not reached.\n\nChecking Safety for extended runs......\n\n";   
                     S.reset();
                }
*/
/*          
//Safety Check                
//check whether the next reachable state fails the safety property
                S.add(this->CountIF && path && P);                
//if yes then print the trace and get out            
                if(S.check()==sat){
                    std::cout << "\n\nProperty does not hold for path of length " << k <<"\n\n Here is the trace";
                    //std::cout << "\n\nLooking at the model\n\n";
                    model m = S.get_model();
                    std::cout << m << "\n\n";
    // traversing the model
                 //   for (unsigned i = 0; i < m.size(); i++) {
                 //       std::cout << m[i] << "\n\n";
                 //       func_decl v = m[i];
                //        std::cout << v << "\n\n";
                    // this problem contains only constants
                 //       assert(v.arity() == 0); 
                 //       std::cout << v.name() << " = " << m.get_const_interp(v) << " ";
                    //}
                  //  std::cout << "\n\n";
                    getchar();
                    return 0;
                }//end of if
//or look at paths of length k+1.
                else{
                    std::cout << "\n\nProperty holds for all paths of length " << k <<"\n\nContinue.....";
                    getchar();
                    k++;
//before you move to longer paths, reset the solver  
                    S.reset();
                    continue;
                }//end of else

    }//end of while	

*/		
//-------------------------------------------------------------------------------------------------- 
//--------------------------------------------------------------------------------------------------
//------------Here we have code for CountTL BMC that mimics that of LTL BMC-------------------------
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//---------------------definition of logical constants f and t.-------------------------------------
//--------------------------------------------------------------------------------------------------
      this->F=c.bool_const("F");
      this->T=c.bool_const("T");
//--------------------------------------------------------------------------------------------------
//------Compute the necessary formulas for k=0 trace length, by calling the translate method.
//--------------------------------------------------------------------------------------------------
      this->translate(0);
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Now compute the actual formula to be sent to SAT solver, for k=0 trace length.
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------		
      S.add(alpha[0] && beta[0]);
	bool result=S.check();

	if(result==sat){
//Print the counterexample and exit	: what does sat mean?
		std::cout <<"\nThe counterexample is of length 0";
		std::cout << "\n(";
            print_trace(0);
		return 0;
	}
	else{ //what does unsat mean?
		std::cout <<"\nNo counterexample of length 0";
		std::cout <<"\n----------------------------------------------------------------\n" <<std::endl;
		std::getchar();	
				
	}
      S.reset();
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Run a loop to inductively check property for trace lengths of k>0.
//--------------------------------------------------------------------------------------------------
	int k=1;
	while(1){
		std::cout <<"\nLooking at traces of length " << k;

//-----------For the present case we need to do more initializations--------------------------------
//-----------------We have may more variables: ip, ipe, u, v, etc.----------------------------------
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//--------------Before we compute the various formulas in the translate routine,--------------------
//------------------ we should initialize the sequence of x expressions.----------------------------
//--------------------------------------------------------------------------------------------------
//------------loop for creating the current state variables [xk*N+0,xk*N+1,xk*N+2,etc.]-------------
//--------------------------------------------------------------------------------------------------
//	 	for(unsigned i=0; i<N_s; ++i){
//		    std::stringstream xName;
//		    xName << "x" << k*N+i;
//		    x.push_back(c.bool_const(xName.str().c_str()));
//  	      }
//       	std::cout << "list of x variables:" << x << "\n\n" <<std::endl;
//       	std::getchar();
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Translate the CountTLFormula to a PL formula for all traces of length k in the transition system (IF,TF).
//CountTLformula is being asserted in an initial state at the time instant 0.
//The CountTLFormula is encoded into the trace of length k. 
//This is done through an inductive process starting from point 0.
//That is why we have an i in the encoding.
//--------------------------------------------------------------------------------------------------
		this->translate(k);
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//Now compute the actual formula to be sent to SAT solver
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------			
            S.add(alpha[k] && beta[k]);
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//Reset the previous switches
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
		result=S.check();

		if(result==sat){
//Print the counterexample and exit	
			std::cout <<"\nThe counterexample is of length "<< k << "\n" <<std::endl;fflush(stdout);
			std::getchar();
                  print_trace(k);
			return 0;
		}
		else{
//Continue the loop
			std::cout <<"\nNo counterexample of length "<< k << "\n" <<std::endl;
			std::cout <<"\n----------------------------------------------------------------\n" <<std::endl;
//--------------------------------------------------------------------------------------------------
			k++;//move to the next trace length
                  S.reset();//reset the SAT-solver state
                  std::cout<<"Move to the next trace length k =  " << k << "\n";
			std::getchar();
			continue;
		}
			

	}//end of while
//-------------------------------------------------------------------------------------------------- 	
	return 0;

//-------------------------------------------------------------------------------------------------- 
//-------------------------------------------------------------------------------------------------- 
//------------------------CODE FOR CountTL BMC ENDS-------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

