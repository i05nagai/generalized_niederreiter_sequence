/*
 * GaussDevBM.c
 *
 * $Source: /Users/ninomiya/lib/source/lds2/RCS/GaussDevBM.c,v $
 * $Author: ninomiya $
 * $Date: 1996/06/24 12:18:43 $
 *
 * 8/Jan/95
 * by Syoiti Ninomiya
 */

/*
 * Gaussian Deviates generator using Box-Muller method.
 */
/**********************************
* usage:
*
*     double x1, x2, y[2];
*     x1 = drand48();
*     x2 = drand48();
*     GaussDevBM(x1, x2, y);
*
**********************************/


#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif /** M_PI **/

void GaussDevBM(double x1, double x2, double y[]){
	y[0] = sqrt(-2.0*log(x1))*cos(2.0*M_PI*x2);
	y[1] = sqrt(-2.0*log(x1))*sin(2.0*M_PI*x2);
}

