#ifndef TSECCONFIG_H
#define TSECCONFIG_H


// Standard C++ Headers
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <map>
#include <list>
#include <cassert>
#include <string>
#include <complex>
#include <set>

// Standard C Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parallel Header
#include "omp.h"
//#include "mpi.h"

// SUNDIALS Section
#include <idas/idas.h>
#include <idas/idas_klu.h>
#include <nvector/nvector_serial.h>/* defs. of serial NVECTOR fcts. and macros  */
#include <sundials/sundials_types.h>/* def. of type realtype */
#include <sundials/sundials_math.h>/* definition of ABS */


#ifdef ENABLE_IPOPT
// IPOPT Section
#include "IpIpoptApplication.hpp"
#include "IpTNLP.hpp"
#endif


// ADC Section
#include "adc04.h"

// MKL Section
#include "mkl_spblas.h"

// Macro Definition
#define TAIL -1
//#define Ith(v,i)    NV_Ith_S(v,i-1)       /* i-th vector component i=1..NEQ */
//#define IJth(A,i,j) DENSE_ELEM(A,i-1,j-1) /* (i,j)-th matrix component i,j=1..NEQ */

namespace TSEC
{
	using namespace std;
#ifdef ENABLE_IPOPT
    using namespace Ipopt;
#else
    typedef double Number;
    typedef int Index;
#endif

	//class PowerComponent;
	//class Profile;
	class Diary;
	//class SparseMatrix;
	//class Amatrix;
	//class sMatrix;
    //class dVector;
    //class DenseMatrix;
	class PowerInMath;
	//class PowerWorld;

	//class Optimizer;
    class Analyzer;
	class PowerInMath;
	class Optimizer;
}


#include "Analyzer.h"
#include "PowerInMath.h"
//#include "PowerWorld.h"
//#include "Profile.h"
#include "Diary.h"
//#include "Amatrix.h"
//#include "SparseTools.h"
//#include "PowerComponent.h"
#include "Optimizer.h"



#endif