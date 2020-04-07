#include "bmc-counttl.h"


//--------------------------------------------------------------------------------------------------
//----------------------------------Simple Encoding Routine-----------------------------------------
//-----------------------------------------Begins---------------------------------------------------
      expr counttl_bmc::encode_into_pl(FTree* TLF,int k,int limit){

            expr new_l_exp(c);
            expr new_r_exp(c);
         	expr new_exp(c);	

            std::cout << "\nWe are in the encoding routine -- that converts following countTL formula to PL.";
            Formula::display_ft(TLF);
            std::cout << "\n";
            fflush(stdout);

        //getchar();//getchar();

	      if(TLF==NULL){
		      std::cout<<"\nError in the formula tree.\n";
		      exit(1);
	      }
		
		fflush(stdout);

	      switch(TLF->val[0]){
//----------------------------------------------------------------------------------------------------------------
		      case '|': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
		          		new_l_exp=encode_into_pl(TLF->left,k,limit);
		          		new_r_exp=encode_into_pl(TLF->right,k,limit);

		    	      	return(new_l_exp || new_r_exp);
//----------------------------------------------------------------------------------------------------------------
		      case '&': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
		    	      	new_l_exp=encode_into_pl(TLF->left,k,limit);
		    	      	new_r_exp=encode_into_pl(TLF->right,k,limit);

		    	      	return(new_l_exp && new_r_exp);
//----------------------------------------------------------------------------------------------------------------
		      case '%': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
		    	      	new_l_exp=encode_into_pl(TLF->left,k,limit);
		    	      	new_r_exp=encode_into_pl(TLF->right,k,limit);

		    	      	return(implies(new_l_exp,new_r_exp));
//----------------------------------------------------------------------------------------------------------------
		      case '~': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
		    	      	fflush(stdout);
		    	      	new_exp=encode_into_pl(TLF->next,k,limit);
		    	
		    	      	return(!new_exp);
//----------------------------------------------------------------------------------------------------------------
              case 'X': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
                        if(k<limit)
                              return encode_into_pl(TLF->next,k+1,limit);
                        else
                              return (F && false);
//----------------------------------------------------------------------------------------------------------------
//what is TLF->iclient?
//at this point we need to differentiate between t(x) and l(x).
		  case '#': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
//what is TLF->ctype?
                        switch(TLF->next->val[0]){
                              case 'l':
                                    std::cout << "We are doing a case analysis of TLF->ctype with value: -> " << TLF->ctype << "\n";
                                    std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n"; 
                                    switch(TLF->ctype){
                                          case 0: std::cout << "We are in case 0.\n"; 
                                                  return u[k*N_c+TLF->iclient] <= TLF->bound+1;
                                          case 1: std::cout << "We are in case 1.\n"; 
                                                  return u[k*N_c+TLF->iclient] <= TLF->bound;
                    
                                    }

                              case 't':
                                    std::cout << "We are doing a case analysis of TLF->ctype with value: -> " << TLF->ctype << "\n";
                                    std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n"; 
                                    switch(TLF->ctype){
                                          case 0: std::cout << "We are in case 0.\n"; 
                                                  return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] <= TLF->bound+1;
                                          case 1: std::cout << "We are in case 1.\n"; 
                                                  return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] <= TLF->bound;
                    
                                    }
                        }
//----------------------------------------------------------------------------------------------------------------
//at this point too we need to differentiate between t(x) and l(x).    
		      case 'E':
                        std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n";  
                        switch(TLF->next->val[0]){

                              case 'l':
		    	                  return u[k*N_c+TLF->iclient] > 0;

                              case 't':
		    	                  return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] > 0;
                        }
//--------------------------------------------------------------------------------------------------
		      default:
		    	      std::cout<<"\nError in input.\n";
		    	      exit(1);
//--------------------------------------------------------------------------------------------------
	      }  
      }//end of encode routine
//----------------------------------Simple Encoding Routine-----------------------------------------
//-------------------------------------------Ends---------------------------------------------------

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//----------------loopFree_at_k() is not needed for CountTL-BMC.------------------------------------
//--------------------------------------------------------------------------------------------------
expr counttl_bmc::loopFree_at_k(int k)
{
// z vector contains the following variables : (x_0,x_1,...x_{N_s-1},x_{N_s},x_{N_s+1},....,x_{2*N_s-1},....x_{(k-1)*N_s},x_{(k-1)N_s+1},...,x_{k*N_s-1}) --- First (k-1) set of state variables.
      expr_vector	z(c);
      for(unsigned i=0; i<k*N_s; ++i){
      	std::stringstream xName;
		xName << "x" << i;
		z.push_back(c.bool_const(xName.str().c_str()));
	}

//    std::cout << "\n\ncontents of z are" << z << "\n" << std::endl;
//    getchar();

// z1 vector contains the following variables : (x_{k*N_s},x_{k*N_s+1},.....x_{k*N_s+N_s-1}) --- Last (kth) set of state variables.
      expr_vector	z1(c);
	for(unsigned i=0; i<N_s; ++i){
      	std::stringstream xName;
		xName << "x" << i+N_s*k;
		z1.push_back(c.bool_const(xName.str().c_str()));
	}

//    std::cout << "\n\ncontents of z1 are" << z1 << "\n" << std::endl;
//    getchar();

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
// w vector contains the following variables : (u_0,u_1,...u_{N_c-1},u_{N_c},u_{N_c+1},....,u_{2*N_c-1},....u_{(k-1)*N_c},u_{(k-1)N_c+1},...,u_{k*N_c-1}) --- First (k-1) set of counter variables.
//--------------------------------------------------------------------------------------------------

      expr_vector	w(c);
      for(unsigned i=0; i<k*N_c; ++i){
      	std::stringstream wName;
		wName << "u" << i;
		w.push_back(c.bool_const(wName.str().c_str()));
	}

//    std::cout << "\n\ncontents of w are" << w << "\n" << std::endl;
//    getchar();

//--------------------------------------------------------------------------------------------------
// w1 vector contains the following variables : (w_{k*N_c},w_{k*N_c+1},.....w_{k*N_c+N_c-1}) --- Last (kth) set of state variables.
//--------------------------------------------------------------------------------------------------

      expr_vector	w1(c);
	for(unsigned i=0; i<N_c; ++i){
      	std::stringstream wName;
		wName << "u" << i+N_c*k;
		w1.push_back(c.bool_const(wName.str().c_str()));
	}

//    std::cout << "\n\ncontents of z1 are" << z1 << "\n" << std::endl;
//    getchar();

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

//Now, compute loopFree expression
      std::cout << "\n\nNow we compute loopFree expression for k=" << k << "\n" << std::endl;

      expr temp0(c);
      expr temp1(c);

      temp0=(z1[0]!=z[0]);
      for(unsigned i=1; i<N_s; ++i){
            temp0=temp0 || (z1[i]!=z[i]);
      }

      temp0 = temp0 || (w1[0]!=w[0]); 
      for(unsigned i=1; i<N_c; ++i){
            temp0=temp0 || (w1[i]!=w[i]);
      }
//--------------------------------------------------------------------------------------------------
// temp0 is s_0 != s_k
//--------------------------------------------------------------------------------------------------
      temp1=temp0;
      for(unsigned j=1; j<k; ++j){
            temp0=(z1[0]!=z[N_s*j]);
            for(unsigned i=1; i<N_s; ++i){
                  temp0=temp0 || (z1[i]!=z[N_s*j+i]);
            }
            temp0=temp0  || (w1[0]!=w[N_c*j]);
            for(unsigned i=1; i<N_c; ++i){
                  temp0=temp0 || (w1[i]!=w[N_c*j+i]);
            }
//--------------------------------------------------------------------------------------------------
            // temp0 is s_j != s_k
//--------------------------------------------------------------------------------------------------
            temp1=temp1 && temp0;
//--------------------------------------------------------------------------------------------------
            // temp1 is (s_0 != s_k) && (s_1 != s_k) && ..... && (s_j != s_k)
//--------------------------------------------------------------------------------------------------
      }
      std::cout << "\n\nLoopFree formula is-->" << temp1 << "\n\n" << std::endl;
      return temp1;

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void counttl_bmc::translate(int k)
{
//--------------------------------------------------------------------------------------------------
//The translate method takes parameter k as input and constructs the Boolean expressions needed to execute BMC
//for any k: alpha[k] contains the Boolean expression describing all paths of length k in input system represented by (IF,TF).
//for any k: beta[k] contains the Boolean approximation of the CountTL property TLF for length k trace.
//for any k: lambda[k] contains the Boolean expression describing (k,l)-loop for any k<=l in the path of length k.
//--------------------------------------------------------------------------------------------------
	std::cout << "\nWe are in the translate routine with k= " << k << std::endl;

	switch(k){
	
		case 0:	

			alpha.push_back(IF);//for trace of length 0
			std::cout << "\nComputed alpha[0]\n" << std::endl;
        	      std::getchar();
			
			beta.push_back(encode_CountTL_property_into_PL(0));//for trace of length 0
			std::cout << "\nComputed beta[0]\n" << std::endl;
        	      std::getchar();

			lambda.push_back(compute_loop_constraints_at_k(0));//loop constraint for trace of length k
			std::cout << "\nComputed lambda[0]\n" << std::endl;
        	      std::getchar();

			break;

		default:

			alpha.push_back(alpha[k-1] && instantiate_CountT_at_k(k));//for trace of length k
			std::cout << "\nComputed alpha[" << k << "]\n" << std::endl;
        	      std::getchar();
			
			beta.push_back(encode_CountTL_property_into_PL(k));//for trace of length k
			std::cout << "\nComputed beta[" << k << "]\n" << std::endl;
        	      std::getchar();

			lambda.push_back(compute_loop_constraints_at_k(k));//loop constraint for trace of length k
			std::cout << "\nComputed lambda[" << k << "]\n" << std::endl;
        	      std::getchar();

			break;
	}
	
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------IMPORTANT---------------------------------------------------
//---The lambda being computed in the translate() method is not being used in CountTL encoding.---------
//---Consequently, the method compute_loop_constraints_at_k() is not being used anywhere.-----------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
expr counttl_bmc::encode_CountTL_property_into_PL(int k)
{

	expr temp0(c),temp1(c),temp2(c),temp3(c);

	std::cout << "\nWe are in encode_CountTL_property_into_PL routine with k= " << k << "\n" << std::endl;
	std::getchar();

	temp0=instantiate_CountT_for_loop_constraints(k,0);//T(s_k,s_0)
	std::cout << "\nComputed the loop constraint T(s_"<< k << ",s_0) and assigned to temp0\n" << std::endl;
	std::getchar();

	temp2=temp0 && translate_CountTL_with_backloop_from_k_to_l(CountTLF,k,0,0);
	std::cout << "\nComputed the encoded formula T(s_"<< k << ",s_0) land 0_[f]_" << k << "^0 and assigned to temp2\n" 
                                << std::endl;
	std::getchar();
    
	temp3=temp0;
	for (int l=1;l<=k;l++){

		temp0=instantiate_CountT_for_loop_constraints(k,l);//T(s_k,s_l)

    	      std::cout << "\nComputed the loop constraint T(s_" << k << ",s_" << l << ") and assigned to temp0\n" 
                                << std::endl;
	      std::getchar();

		temp1=temp0 && translate_CountTL_with_backloop_from_k_to_l(CountTLF,k,l,0);
	      std::cout << "\nComputed the encoded formula T(s_" << k << ",s_" << l << ") land " << l << "_[f]_" << k
                                << "^0 and assigned to temp1\n" << std::endl;
	      std::getchar();

		temp2=temp2 || temp1;//\bigwedge_{j=0}^{l}(L_k^j \land [f,0]_k^j)
            std::cout << "\ntemp2 is updated by ORing it with temp1\n" << std::endl;
	      std::getchar();
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
		temp3=temp3||temp0;//L_k^l=T(s_k,s_0)\lor T(s_k,s_1)\lor \cdots \lor T(s_k,s_l)		
            std::cout << "\ntemp3 is updated by ORing it with temp0\n" <<std::endl;
	      std::getchar();

		
	}
//--------------------------------------------------------------------------------------------------
//--------------temp2 contains the encoded formula guarded with loop constraints.-------------------
//-----------------------temp3 contains all the loop constraints.-----------------------------------
//--------------------------------------------------------------------------------------------------
	return ((!temp3 && translate_CountTL_for_no_loop(CountTLF,k,0)) || temp2);
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
expr counttl_bmc::translate_CountTL_with_backloop_from_k_to_l(FTree* TLF,int k,int l,int i)
{
	expr temp0(c),temp1(c),temp2(c),temp3(c),temp4(c),temp5(c),temp6(c);


	std::cout << "\nWe are in the method translate_CountTL_with_backloop_from_k_to_l with k= " << k 
                << " and i=" << i << " and l= " << l << "\n" << std::endl;
    
	if(TLF==NULL){
		std::cout << "\nError in the formula tree.\n" << std::endl;
		std::exit(1);
	}

      std::cout << "\nConsidering the CountTL subformula:" <<std::endl;Formula::display_ft_pre(TLF);

	switch(TLF->get_type()){

            case 5://we should not get here. this must give an error.
		      std::cout << "\nError in the formula tree.\n" << std::endl;
		      std::exit(1);
            case 4:
                  switch(TLF->get_val()[0]){
//what is TLF->iclient?
//at this point we need to differentiate between t(x) and l(x).
		         case '#': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
//what is TLF->ctype?
                        switch(TLF->next->val[0]){
                              case 'l':
                                    std::cout << "We are doing a case analysis of TLF->ctype with value: -> " << TLF->ctype << "\n";
                                    std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n"; 
                                    switch(TLF->ctype){
                                          case 0: std::cout << "We are in case 0.\n"; 
                                                  return u[k*N_c+TLF->iclient] <= TLF->bound+1;
                                          case 1: std::cout << "We are in case 1.\n"; 
                                                  return u[k*N_c+TLF->iclient] <= TLF->bound;
                    
                                    }

                              case 't':
                                    std::cout << "We are doing a case analysis of TLF->ctype with value: -> " << TLF->ctype << "\n";
                                    std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n"; 
                                    switch(TLF->ctype){
                                          case 0: std::cout << "We are in case 0.\n"; 
                                                  return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] <= TLF->bound+1;
                                          case 1: std::cout << "We are in case 1.\n"; 
                                                  return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] <= TLF->bound;
                    
                                    }//end of switch on ctype
		                  default:
		    	                  std::cout<<"\nError in input.\n";
		    	                  exit(1);

                        }//end of inner switch
		         default:
		    	      std::cout<<"\nError in input.\n";
		    	      exit(1);
                  }//end of outer switch
            case 3:
			switch(TLF->get_val()[0]){
//at this point too we need to differentiate between t(x) and l(x).    
		            case 'E':
                              std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n";  
                              switch(TLF->next->val[0]){

                                    case 'l':
		    	                        return u[k*N_c+TLF->iclient] > 0;

                                    case 't':
		    	                        return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] > 0;
                        }
//----------------------------------------------------------------------------------------------------------------
		            default:
		    	            std::cout<<"\nError in input.\n";
		    	            exit(1);
                  }

		case 2: 
			switch(TLF->get_val()[0]){
				case '='://EQUALITY
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					temp3=(temp1==temp2);
					return temp3;
				case '&'://AND
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					temp3=(temp1 && temp2);
					return temp3;

				case '|'://OR
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					temp3=(temp1 || temp2);
					return temp3;

/*
				case '^'://XOR
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					temp3=(temp1 || temp2) && ! (temp1 && temp2);
					return temp3;

				case '$'://NAND
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					temp3=! (temp1 && temp2);
					return temp3;



				case '#'://NOR
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					temp3=!(temp1 || temp2);
					return temp3;
*/

				case '%'://IMPLIES
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					temp3=implies(temp1,temp2);
					return temp3;


/*
				case 'U'://UNTIL
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);//[g]^i
					for(int j=i+1;j<=k;j++){
						temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,j); //[g]^j
						temp3=temp2 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i); //[g]^j and [f]^i
						for(int n=i+1;n<=j-1;n++){
						  temp3=temp3 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,n); //[g]^j and [f]^i and [f]^i+1 and ....[f]^n
						}
						temp1=temp1 || temp3;//[g]^i or ([g]^j and [f]^i and [f]^i+1 and ....[f]^j)
					}



					temp0=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,l);//[g]^i
					temp5=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
					for(int n=i+1;n<=k;n++){
						temp5=temp5 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,n);
					}
					temp0=temp0 && temp5;

					for(int j=l+1;j<=k;j++){
						temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,j); //[g]^j

				     	temp4=temp2 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
						for(int n=i+1;n<=k;n++){
							temp4=temp4 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,n);
						}

						temp3=temp4 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,l); //[g]^j and [f]^i
						for(int n=l+1;n<=j-1;n++){
						  temp3=temp3 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,n); //[g]^j and [f]^i and [f]^i+1 and ....[f]^n
						}
						temp0=temp0 || temp3;//[g]^i or ([g]^j and [f]^i and [f]^i+1 and ....[f]^j)
					}
					std::cout << "\nReturning a proposition for " << TLF->get_val() << " formula\n" << std::endl;
					std::cout << "\n----------------------------------------------------------------\n" << std::endl;
					//std::getchar();

					return temp1 || temp0;


				case 'R'://RELEASE
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;


					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);//[g]^i
					for(int j=i+1;j<=k;j++){
						temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,j); //[g]^j
						temp3=temp2 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i); //[g]^j and [f]^i
						for(int n=i+1;n<=j;n++){
						  temp3=temp3 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,n); //[g]^j and [f]^i and [f]^i+1 and ....[f]^n
						}
						temp1=(temp1 || temp3);//[g]^i or ([g]^j and [f]^i and [f]^i+1 and ....[f]^j)
					}



					temp0=translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,l);//[g]^i
					temp5=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
					for(int n=i+1;n<=k;n++){
						temp5=temp5 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,n);
					}
					temp0=temp0 && temp5;

					for(int j=l+1;j<=k;j++){
						temp2=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,j); //[g]^j

    					     	temp4=temp2 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,i);
						for(int n=i+1;n<=k;n++){
							temp4=temp4 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,n);
						}

						temp3=temp4 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,l); //[g]^j and [f]^i
						for(int n=l+1;n<=j;n++){
						  temp3=temp3 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_left(),k,l,n); //[g]^j and [f]^i and [f]^i+1 and ....[f]^n
						}
						temp0=temp0 || temp3;//[g]^i or ([g]^j and [f]^i and [f]^i+1 and ....[f]^j)
					}
					std::cout << "\nReturning a proposition for " << TLF->get_val() << " formula\n" << std::endl;
					std::cout << "\n----------------------------------------------------------------\n" << std::endl;
					//std::getchar();


					if(i<l){
						std::cout<< "\nThe Case when i < l: i=  " << i << "  l=  " << l << "\n" << std::endl;
						temp6=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,i);
						for(int j=i+1;j<=k;j++){
						 temp6=temp6 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,j);
						}
						std::cout << "\nReturning a non-false proposition for G formula\n" << std::endl;
						std::cout << "\n----------------------------------------------------------------\n" << std::endl;
						//std::getchar();

					}
					else{
						std::cout<< "\nThe Case when i >= l: i=  " << i << "  l=  " << l << "\n" << std::endl;
						temp6=translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,l);
						for(int j=l+1;j<=k;j++){
						 temp6=temp6 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_right(),k,l,j);
						}
						std::cout << "\nReturning a non-false proposition for G formula\n" << std::endl;
						std::cout << "\n----------------------------------------------------------------\n" << std::endl;
						//std::getchar();

					}

					return (temp6 || (temp0 || temp1));
--------------------------------------------------------------------------------------------------*/
				default:
					std::cout << "\nError\n" << std::endl;
					std::exit(1);

			}

		case 1: 
			switch(TLF->get_val()[0]){
				case '~'://NOT
					std::cout << "\nLooking at a " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,i);					
					return !temp1;

				case 'X'://NEXT
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					if(i<k)
						return(translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,i+1));
					else
						return(translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,l));
					

				case 'F'://DIAMOND -- EVENTUALLY
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					if(i<l){
						temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,i);
						for(int j=i+1;j<=k;j++){
						 temp1=temp1 || translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,j);
						}
						std::cout << "\nReturning a non-false proposition for F formula\n" << std::endl;
						std::cout << "\n----------------------------------------------------------------\n" << std::endl;
						return temp1;
					}
					else{
						temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,l);
						for(int j=l+1;j<=k;j++){
						 temp1=temp1 || translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,j);
						}
						std::cout << "\nReturning a non-false proposition for F formula\n" << std::endl;
						std::cout << "\n----------------------------------------------------------------\n" << std::endl;
						return temp1;
					}


				case 'G'://BOX -- ALWAYS
					std::cout << "\nLooking at a " << TLF->get_val()[0] << " node\n" << std::endl;
					if(i<l){
						std::cout<< "\nThe Case when i < l: i=  " << i << "  l=  " << l << "\n" << std::endl;
						temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,i);
						for(int j=i+1;j<=k;j++){
						 temp1=temp1 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,j);
						}
						std::cout << "\nReturning a non-false proposition for G formula:" << temp1 << std::endl;
						std::cout << "\n----------------------------------------------------------------\n" << std::endl;
						std::getchar();
						return temp1;
					}
					else{
						std::cout<< "\nThe Case when i >= l: i=  " << i << "  l=  " << l << "\n" << std::endl;
						temp1=translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,l);
						for(int j=l+1;j<=k;j++){
						 temp1=temp1 && translate_CountTL_with_backloop_from_k_to_l(TLF->get_next(),k,l,j);
						}
						std::cout << "\nReturning a non-false proposition for G formula:" << temp1 << std::endl;
						std::cout << "\n----------------------------------------------------------------\n" << std::endl;
						std::getchar();
						return temp1;
					}


					
				default:
					std::cout << "\nError\n" << std::endl;
					std::exit(1);

			}
		case 0: 

			if(TLF->get_val()=="t"){
				std::cout << "\nReplacing t by true\n" << std::endl;
				return (T || true);
			}
			else if(TLF->get_val()=="f"){
				std::cout << "\nReplacing f by false\n" << std::endl;
				return (F && false);			
            }
			else{
				char* strng;
				int M=0;
				int ia;
				int len=TLF->get_val().size();

				if(TLF->get_val()[0]!='x'){
					std::cout << "Error in the input\nThe variables in I/P can only have x\n" << std::endl;
					std::exit(1);
				
				}
				
				TLF->get_val().copy(strng,len-1,1);
//Copies a substring of the string object TLF->get_val() into the array pointed by strng. 
//This substring contains the len-1 characters that start at position position 1.

				//strng contains a number as string -- this string is converted to integer M
				for(int t=0;t<len-1;t++){
					ia=strng[t]-'0';
					M=10*M+ia;
				}
				std::cout << "\nReplacing " << TLF->get_val() << " by x[" << M << "][" << i << "]\n" << std::endl;
		        //std::stringstream xName;
		        //xName << "x" << M + i*N;
		        //return c.bool_const(xName.str().c_str());
//is this expr of Boolean type or int type ? please check ?			
				return x[M + i*N];
				
				
			}			
			std::cout << "\nError\n" << std::endl;
			std::exit(1);

		default:
					std::cout << "\nError\n" << std::endl;
					std::exit(1);
			
			break;

	}

}
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
expr counttl_bmc::translate_CountTL_for_no_loop(FTree* TLF,int k,int i)
{

	expr temp1(c),temp2(c),temp3(c);

//    expr f=c.bool_const("f");
//    expr t=c.bool_const("t");

	std::cout << "\nWe are in the method translate_CountTL_for_no_loop routine with k= " << k << " and i= " << i << "\n" << std::endl;
	if(TLF==NULL){
		std::cout << "\nError in the formula tree.\n" << std::endl;
		std::exit(1);
	}

	switch(TLF->get_type()){

            case 5://we should not get here. this must give an error.
		      std::cout << "\nError in the formula tree.\n" << std::endl;
		      std::exit(1);
            case 4:
                  switch(TLF->get_val()[0]){
//what is TLF->iclient?
//at this point we need to differentiate between t(x) and l(x).
		         case '#': std::cout<<"\nThe node type is " << TLF->val[0] << "\n";fflush(stdout);
//what is TLF->ctype?
                        switch(TLF->next->val[0]){
                              case 'l':
                                    std::cout << "We are doing a case analysis of TLF->ctype with value: -> " << TLF->ctype << "\n";
                                    std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n"; 
                                    switch(TLF->ctype){
                                          case 0: std::cout << "We are in case 0.\n"; 
                                                  return u[k*N_c+TLF->iclient] <= TLF->bound+1;
                                          case 1: std::cout << "We are in case 1.\n"; 
                                                  return u[k*N_c+TLF->iclient] <= TLF->bound;
                    
                                    }

                              case 't':
                                    std::cout << "We are doing a case analysis of TLF->ctype with value: -> " << TLF->ctype << "\n";
                                    std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n"; 
                                    switch(TLF->ctype){
                                          case 0: std::cout << "We are in case 0.\n"; 
                                                  return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] <= TLF->bound+1;
                                          case 1: std::cout << "We are in case 1.\n"; 
                                                  return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] <= TLF->bound;
                    
                                    }//end of switch on ctype
		                  default:
		    	                  std::cout<<"\nError in input.\n";
		    	                  exit(1);

                        }//end of inner switch
		         default:
		    	      std::cout<<"\nError in input.\n";
		    	      exit(1);
                  }//end of outer switch
            case 3:
			switch(TLF->get_val()[0]){
//at this point too we need to differentiate between t(x) and l(x).    
		            case 'E':
                              std::cout << "We use the TLF->iclient value here: -> " << TLF->iclient << "\n";  
                              switch(TLF->next->val[0]){

                                    case 'l':
		    	                        return u[k*N_c+TLF->iclient] > 0;

                                    case 't':
		    	                        return u[k*N_c+TLF->iclient]-u[(k-1)*N_c+TLF->iclient] > 0;
                        }
//----------------------------------------------------------------------------------------------------------------
		            default:
		    	            std::cout<<"\nError in input.\n";
		    	            exit(1);
                  }

		case 2: 
			switch(TLF->get_val()[0]){
				case '=':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << "  node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);
					temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,i);
					temp3=temp1==temp2;
					return temp3;
				case '&':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);
					temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,i);
					temp3=(temp1 && temp2);
					return temp3;

				case '|':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);
					temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,i);
					temp3=(temp1 || temp2);
					return temp3;




				case '^':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);
					temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,i);
					temp3=(temp1 || temp2) && !(temp1 && temp2);
					return temp3;

				case '$':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);
					temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,i);
					temp3=!(temp1 && temp2);
					return temp3;



				case '#':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);
					temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,i);
					temp3=!(temp1 || temp2);
					return temp3;




				case '%':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);
					temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,i);
					temp3=implies(temp1,temp2);
					return temp3;




/*--------------------------------------------------------------------------------------------------
				case 'U':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
//loop from j=i to j=k
					temp1=translate_CountTL_for_no_loop(TLF->get_right(),k,i);//[g]^i
					for(int j=i+1;j<=k;j++){
						temp2=translate_CountTL_for_no_loop(TLF->get_right(),k,j); //[g]^j
						temp3=(temp2 && translate_CountTL_for_no_loop(TLF->get_left(),k,i)); //[g]^j and [f]^i
						for(int n=i+1;n<=j-1;n++){
						  temp3=(temp3 && translate_CountTL_for_no_loop(TLF->get_left(),k,n)); //[g]^j and [f]^i and [f]^i+1 and ....[f]^n
						}
						temp1=(temp1 || temp3);//[g]^i or ([g]^j and [f]^i and [f]^i+1 and ....[f]^j)
					}
					std::cout << "\nReturning a proposition for " << TLF->get_val() << " formula\n" << std::endl;
					std::cout << "\n----------------------------------------------------------------\n" << std::endl;
					//std::getchar();

					return temp1;

				case 'R':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_left(),k,i);//[f]^i
					for(int j=i+1;j<=k;j++){
						temp2=translate_CountTL_for_no_loop(TLF->get_left(),k,j); //[f]^j
						temp3=(temp2 && translate_CountTL_for_no_loop(TLF->get_right(),k,i)); //[f]^j and [g]^i
						for(int n=i+1;n<=j;n++){
						  temp3=(temp3 && translate_CountTL_for_no_loop(TLF->get_right(),k,n)); //[f]^j and [g]^i and [g]^i+1 and ....[g]^n
						}
						temp1=(temp1 || temp3);//[f]^i or ([f]^j and [g]^i and [g]^i+1 and ....[g]^j)
					}
					std::cout << "\nReturning a proposition for " << TLF->get_val() << " formula\n" << std::endl;
					std::cout << "\n----------------------------------------------------------------\n" << std::endl;
					//std::getchar();

					return temp1;
--------------------------------------------------------------------------------------------------*/

				default:
					std::cout << "\nError\n" << std::endl;
					std::exit(1);

			}

		case 1: 
			switch(TLF->get_val()[0]){
				case '~':
					std::cout << "\nLooking at a " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_next(),k,i);
					//temp2=S.lnot(temp1);
					temp2=!temp1;
					return temp2;

				case 'X':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					if(i<k)
						return(translate_CountTL_for_no_loop(TLF->get_next(),k,i+1));
					else{
                                    expr f=c.bool_const("f");
				            return (F && false);				
                    }
				case 'F':
					std::cout << "\nLooking at an " << TLF->get_val()[0] << " node\n" << std::endl;
					temp1=translate_CountTL_for_no_loop(TLF->get_next(),k,i);
					for(int j=i+1;j<=k;j++){
						temp1=(temp1 || translate_CountTL_for_no_loop(TLF->get_next(),k,j));
					}
					std::cout << "\nReturning a proposition for " << TLF->get_val() << " formula\n" << std::endl;
					std::cout << "\n----------------------------------------------------------------\n" << std::endl;
					//std::getchar();

					return temp1;


				case 'G':
					std::cout << "\nLooking at a " << TLF->get_val()[0] << " node\n\nReturning false proposition";
					//std::getchar();
				    return (F && false);

					
				default:
					std::cout << "\nError\n" << std::endl;
					std::exit(1);

			}
		case 0: 

			if(TLF->get_val()=="t"){
				std::cout << "\nReplacing t by true\n" << std::endl;
				return (T || true);
			}
			else if(TLF->get_val()=="f"){
				std::cout << "\nReplacing f by false\n" << std::endl;
				return (F && false);
			}
			else{
				char* strng;
				int M=0;
				int ia;
				int len=TLF->get_val().size();

				if(TLF->get_val()[0]!='x'){
					std::cout << "Error in the input\nThe variables in CountTLF can only have x\n" << std::endl;
					exit(0);
				
				}

				
				TLF->get_val().copy(strng,len-1,1); 
//Copies a substring of the string object TLF->get_val() into the array pointed by strng. 
//This substring contains the len-1 characters that start at position position 1.

				//strng contains a number as string -- this is converted to integer M
				for(int t=0;t<len-1;t++){
					ia=strng[t]-'0';
					M=10*M+ia;
				}
				//std::cout << "\nReplacing " << TLF->get_val() << " by x[" << M << "][" << i << "]\n" << std::endl;
		        //std::stringstream xName;
		        //xName << "x" << M + i*N;
		        //return c.bool_const(xName.str().c_str());	
                        return x[M + i*N];								
			}


			
			std::cout << "\nError\n" << std::endl;
			std::exit(1);
			
		default:
					std::cout << "\nError\n" << std::endl;
					std::exit(1);
			
			break;

	}

}
//--------------------------------------------------------------------------------------------------
//------------------------This method has to be suitably modified.----------------------------------
//--------------------------------------------------------------------------------------------------
expr counttl_bmc::instantiate_CountT_at_k(int k)
{
//--------------------------------------------------------------------------------------------------
//-------------In the case of instantiation of T, we do not need any tree traversal.----------------
//--------------We just have to call the substitute method provided by expr class.------------------
//--------------------------------------------------------------------------------------------------
//--------------------This method computes T(s_{k-1},s_{k}), given k.-------------------------------
//---------------So, in the formula T, (x_0,x_1,...x_{N-1}) is replaced by -------------------------
//---------------------(x_{N*(k-1)+1},x_{N*(k-1)+2},...x_{N*(k-1)+N-1})-----------------------------
//----------------and (y_0,y_1,...y_{N-1}) is replaced by (x_{N*k+1},x_{N*k+2},...x_{N*k+N-1})------
//--------------------------------------------------------------------------------------------------

	std::cout << "\nWe are in the instantiate_CountT_at_k routine with k= " << k << "\n" << std::endl;
/*
                expr_vector	z(c);
				for(unsigned i=0; i<N; ++i){
					z.push_back(x[i]);
				}
                expr_vector	z0(c);
				for(unsigned i=0; i<N; ++i){
					z0.push_back(x[i+N*(k-1)]);
				}
                std::cout << "\nz0 that replaces x in T is:\t" << z0 << std::endl;
                expr_vector	z1(c);
				for(unsigned i=0; i<N; ++i){
					z1.push_back(x[i+N*k]);
				}
                std::cout << "\nz1 that replaces y in T is:\t" << z1 << std::endl;
*/
//-----------------------------------------------------------------------------------------------------
//We have replaced the above three loops by one loop.
//-----------------------------------------------------------------------------------------------------
/*--------------------------------------------------------------------------------------------------
    expr_vector	z(c);
    expr_vector	z0(c);
    expr_vector	z1(c);
    for(unsigned i=0; i<N; ++i){
        z.push_back(x[i]);
        z0.push_back(x[i+N*(k-1)]);
        z1.push_back(x[i+N*k]);
    }
    std::cout << "\nz0 that replaces x in T is:\t" << z0 << std::endl;
    std::cout << "\nz1 that replaces y in T is:\t" << z1 << std::endl;
//--------------------------------------------------------------------------------------------------------
//-------------subT is T(x,y) with x=(x0,x1,..x_N-1) replaced by current state z0 and --------------------
//---------------------y=(y0,y1,...y_N-1) replaced by next state z1.--------------------------------------
//-----------------We should make a copy of TF before substitution.---------------------------------------
//--------------------------------------------------------------------------------------------------------
    expr subCountT(c);
    expr CountT=CountTF;
    subCountT=CountT.substitute(y,z1);
    subCountT=subCountT.substitute(z,z0);
    std::cout << "T substituted : " << subCountT << "\n\n" << std::endl; 
    std::getchar();
    return subCountT;
--------------------------------------------------------------------------------------------------*/
//--------------------------------------------------------------------------------------------------
//      expr_vector	z(c);
//	for(unsigned i=0; i<k*N_s; ++i){
//	      std::stringstream xName;
//		xName << "x" << i;
//		z.push_back(c.bool_const(xName.str().c_str()));
//	}
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
//No change in original expr_vector x is allowed.
//--------------------------------------------------------------------------------------------------
//	for(unsigned i=0; i<N_s; ++i){
//		std::stringstream xName;
//		xName << "x" << i+N_s*k;
//	      x.push_back(c.bool_const(xName.str().c_str()));
//	}
//--------------------------------------------------------------------------------------------------
//For counter variables  -- why are we using different expression vectors instead of u ?
//--------------------------------------------------------------------------------------------------
//      expr_vector	w(c);
//	for(unsigned i=0; i<k*N_c; ++i){
//		std::stringstream uName;
//		uName << "u" << i;
//	      w.push_back(c.int_const(uName.str().c_str()));
//	}
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
//No change in original expr_vector u is allowed.
//--------------------------------------------------------------------------------------------------
//	for(unsigned i=0; i<N_c; ++i){
//	      std::stringstream uName;
//		uName << "u" << i+N_c*k;
//		u.push_back(c.bool_const(uName.str().c_str()));
//	}
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
//--------------No change in original expr_vector ip and ipe is allowed
//--------------------------------------------------------------------------------------------------
//	for(unsigned i=0; i<N_c; ++i){
//	      std::stringstream ipName;
//		ipName << "ip" << i+N_c*k;
//		ip.push_back(c.bool_const(ipName.str().c_str()));
//	}
//	for(unsigned i=0; i<N_c; ++i){
//	      std::stringstream ipeName;
//		ipeName << "ipe" << i+N_c*k;
//		ipe.push_back(c.bool_const(ipeName.str().c_str()));
//	}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//The above set of loops can be replaced by two loops.
//--------------------------------------------------------------------------------------------------
      expr subT(c);
      subT=this->CountTF.substitute(y,z1);
	//std::cout << subT << "\n\n";

      subT=subT.substitute(x,z0);
      //std::cout << subT << "\n\n";
		
      //std::cout << "v is " << v << "\n\n";
      //std::cout << "w1 is " << w1 << "\n\n";

      subT=subT.substitute(v,w1);
      //std::cout << subT << "\n\n";

      subT=subT.substitute(u,w0);
      //std::cout << subT << "\n\n";

      subT=subT.substitute(ip,jp);
      //std::cout << subT << "\n\n";

      subT=subT.substitute(ipe,jpe);
      //std::cout << subT << "\n\n";

      //std::cout << "T substituted : " << subT << "\n\n"; 
      //getchar();
      return subT;
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//------------------------This method has to be suitably modified.----------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
expr counttl_bmc::compute_loop_constraints_at_k(int k)
{
//This method computes temp0=T(s_k,s_0) \lor T(s_k,s_1) \lor T(s_k,s_2) \lor \cdots \lor T(s_k,s_k)
	expr temp0(c);
	std::cout << "\nIn the compute_loop_constraints_at_k routine with k=" << k << "\n" << std::endl;

	temp0=instantiate_CountT_for_loop_constraints(k,0);//Initially, temp0=T(s_k,s_0)
	for (unsigned j=1;j<=k;j++){
		temp0=temp0 || instantiate_CountT_for_loop_constraints(k,j);//temp0=temp0 \lor T(s_k,s_j) --- where j=1 to k 
		
	}
	return temp0;
//temp0 is satisfiable only if there is a back loop from k to some l: 0 \le l \le k
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//------------------------This method has to be suitably modified.----------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
expr counttl_bmc::instantiate_CountT_for_loop_constraints(int k,int j)
{
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//This method computes T(s_k,s_j), given k and j.
//So, in the formula T, (x_0,x_1,...x_{N-1}) is replaced by (x_{N*k},x_{N*k+1},...x_{N*k+N-1})
//and (y_0,y_1,...y_{N-1}) is replaced by (x_{N*j},x_{N*j+1},...x_{N*j+N-1})
//--------------------------------------------------------------------------------------------------

      std::cout << "\nWe are in the instantiate_CountT_for_loop_constraints routine with k=" << k << " and j=" <<j << "\n" << std::endl;
      std::cout << "\nComputing the formula T(s_" << k<< ",s_" <<j<< ")\n" << std::endl;
//--------------------------------------------------------------------------------------------------               
/*                
                expr_vector	z(c);
				for(unsigned i=0; i<N; ++i){
					z.push_back(x[i]);
				}
                expr_vector	z0(c);
				for(unsigned i=0; i<N; ++i){
					z0.push_back(x[i+N*k]);
				}
                std::cout << "\nz0 that replaces y in T is:\t" << z0 << std::endl;
                expr_vector	z1(c);
				for(unsigned i=0; i<N; ++i){
					z1.push_back(x[i+N*j]);
				}
                std::cout << "\nz1 that replaces x in T is:\t" << z1 << std::endl;
*/
//--------------------------------------------------------------------------------------------------
//We have replaced the above three loops by one loop.
//--------------------------------------------------------------------------------------------------
/*--------------------------------------------------------------------------------------------------
      expr_vector	z(c);
      expr_vector	z0(c);
      expr_vector	z1(c);
      for(unsigned i=0; i<N; ++i){
            z.push_back(x[i]);
		z0.push_back(x[i+N*k]);
    	      z1.push_back(x[i+N*j]);
	}

      std::cout << "\nz0 that replaces y in T is:\t" << z0 << std::endl;
      std::cout << "\nz1 that replaces x in T is:\t" << z1 << std::endl;

      std::cout << "\ns_" << k<< " is:" << z0 << "\ns_" <<j<< " is:" << z1 << "\n" << std::endl;
      std::cout << "\nT is: " << TF << std::endl;

//subT is T(x,y) with x=(x0,x1,x2) replaced current state z0 and y=(y0,y1,y2) replaced by next state z1.
      expr subCountT(c);
      expr CountT=CountTF;
      subCountT=CountT.substitute(y,z1);
      subCountT=subCountT.substitute(z,z0);
      std::cout << "T substituted : " << subCountT << "\n\n" << std::endl; 
      std::getchar();
      return subCountT;
--------------------------------------------------------------------------------------------------*/
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//      expr_vector	z(c);
//	for(unsigned i=0; i<k*N_s; ++i){
//	      std::stringstream xName;
//		xName << "x" << i;
//		z.push_back(c.bool_const(xName.str().c_str()));
//	}
//      //std::cout << z << "\n\n"; //vector z is not
      expr_vector	z0(c);
	for(unsigned i=0; i<N_s; ++i){
	      std::stringstream xName;
		xName << "x" << i+N_s*k;
		z0.push_back(c.bool_const(xName.str().c_str()));
	}
	//std::cout << z0 << "\n\n";
      expr_vector	z1(c);
	for(unsigned i=0; i<N_s; ++i){
		std::stringstream xName;
		xName << "x" << i+N_s*j;
	      z1.push_back(c.bool_const(xName.str().c_str()));
	}
	//std::cout << z1 << "\n\n";
//--------------------------------------------------------------------------------------------------
//we should not change vector x; they contain the variables x_0,x_1,...x_{N_s-1} which are replaced by 
//another vector of variables x_{N_s*l}, x_{N_s*l+1},...x_{N_s*l + N_s-1}, for some l, on instantiation
//--------------------------------------------------------------------------------------------------
//	for(unsigned i=0; i<N_s; ++i){
//		std::stringstream xName;
//		xName << "x" << i+N_s*k;
//	      x.push_back(c.bool_const(xName.str().c_str()));
//	}
//--------------------------------------------------------------------------------------------------
//For counter variables  -- why are we using different expression vectors instead of u ?
//--------------------------------------------------------------------------------------------------
//      expr_vector	w(c);
//	for(unsigned i=0; i<k*N_c; ++i){
//		std::stringstream uName;
//		uName << "u" << i;
//	      w.push_back(c.int_const(uName.str().c_str()));
//	}
//      //std::cout << w << "\n\n"; // vector w not required
      expr_vector	w0(c);
	for(unsigned i=0; i<N_c; ++i){
		std::stringstream uName;
		uName << "u" << i+N_c*k;
	      w0.push_back(c.int_const(uName.str().c_str()));
	}
	//std::cout << w0 << "\n\n";
      expr_vector	w1(c);
	for(unsigned i=0; i<N_c; ++i){
	      std::stringstream uName;
		uName << "u" << i+N_c*j;
		w1.push_back(c.int_const(uName.str().c_str()));
	}
	//std::cout << w1 << "\n\n";
//--------------------------------------------------------------------------------------------------
//	for(unsigned i=0; i<N_c; ++i){
//	      std::stringstream uName;
//		uName << "u" << i+N_c*k;
//		u.push_back(c.bool_const(uName.str().c_str()));
//	}
//--------------------------------------------------------------------------------------------------
//For input variables  -- why are we using different expression vectors instead of ip and ipe ?
//--------------------------------------------------------------------------------------------------
      expr_vector	jp(c);
	for(unsigned i=0; i<N_c; ++i){
	      std::stringstream ipName;
		ipName << "ip" << i+N_c*k;
		jp.push_back(c.bool_const(ipName.str().c_str()));
	}
	//std::cout << jp << "\n\n";
      expr_vector	jpe(c);
	for(unsigned i=0; i<N_c; ++i){
	      std::stringstream ipeName;
		ipeName << "ipe" << i+N_c*k;
		jpe.push_back(c.bool_const(ipeName.str().c_str()));
	}

	//std::cout << jpe << "\n\n";
//--------------------------------------------------------------------------------------------------
//	for(unsigned i=0; i<N_c; ++i){
//	      std::stringstream ipName;
//		ipName << "ip" << i;
//		ip.push_back(c.bool_const(ipName.str().c_str()));
//	}
//	for(unsigned i=0; i<N_c; ++i){
//	      std::stringstream ipeName;
//		ipeName << "ipe" << i;
//		ipe.push_back(c.bool_const(ipeName.str().c_str()));
//	}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//The above set of loops can be replaced by two loops.
//--------------------------------------------------------------------------------------------------
      expr subT(c);
      subT=this->CountTF.substitute(y,z1);
	//std::cout << subT << "\n\n";

      subT=subT.substitute(x,z0);
      //std::cout << subT << "\n\n";
		
      //std::cout << "v is " << v << "\n\n";
      //std::cout << "w1 is " << w1 << "\n\n";

      subT=subT.substitute(v,w1);
      //std::cout << subT << "\n\n";

      subT=subT.substitute(u,w0);
      //std::cout << subT << "\n\n";

      subT=subT.substitute(ip,jp);
      //std::cout << subT << "\n\n";

      subT=subT.substitute(ipe,jpe);
      //std::cout << subT << "\n\n";

      //std::cout << "T substituted : " << subT << "\n\n"; 
      //getchar();
      return subT;
}
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
