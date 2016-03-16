/*/*==========================================================
 * DAC4_d2xxInterface - Mex interface to contorl the DAC4 for the OKO
 * tiptilit mirror.
 *
 * This is a MATLAB mex program that accepets a 1x3 vector with values
 * between  -1 and 1. These coresspond to min and max tip/tilts of the
 * mirror.
 *
 * Index 0 and 1 are x and y tips/tilts of mirror. Index 2 is for a second
 * mirror (not clear why only 3 outputs work, buts part of the OKO SDK).
 *
 * Software utilises interface supplied by OKO.
 *
 * Compliation is can be done with the following cmd:
 * mex -L".\d2xx\amd64" -I".\d2xx" -I".\dac4" -lFTD2XX DAC4_d2xxInterface.c .\dac4\DAC4Protocol.c .\dac4\FT245R.c .\dac4\TT2DAC4.c
 *
 * Copyright 2016 Chris Betters
 *
 */

#include <mex.h>

#include "ftd2xx.h"

#include "SUTypes.h"
#include "FT245R.h"
#include "DAC4Protocol.h"
#include "TT2Dac4.h"

FT_HANDLE ftHandle;

static void CloseComms(void)
{
    mexPrintf("Closing connection to d2xx. \n");
    ft245rClose(ftHandle);
}

void mexFunction( int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[] )
{
    double *amplitude1;
    double *amplitude2;
    double *amplitude3;
    double *amplitude4;
    double amplitudes[4];
    int count;
    //(void) plhs;
    
    /* check for proper number of arguments */
    if(nrhs!=4) {
        mexErrMsgIdAndTxt("chrislib:DAC4interface:nrhs","Four inputs required.");
    }
    if(nlhs!=0) {
        mexErrMsgIdAndTxt("chrislib:DAC4interfac:nlhs","No output required.");
    }
    
    /* make sure the input argument is type double */
    if( !mxIsDouble(prhs[0]) || mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("chrislib:DAC4interfac:notRealDouble","Input matrix must be type real double.");
    }
    
    /* check that number of rows in second input argument is 1 and cols is 3 */
//     if((mxGetM(prhs[0])!=1) || (mxGetN(prhs[0])!=4)) {
//         mexErrMsgIdAndTxt("chrislib:DAC4interfac:not1x4RowVector","Input must be a 1x4 row vector.");
//     }
    
    /* Assign pointer to inputs */
    amplitude1 =  mxGetPr(prhs[0]);
    amplitude2 =  mxGetPr(prhs[1]);
    amplitude3 =  mxGetPr(prhs[2]);
    amplitude4 =  mxGetPr(prhs[3]);
    
    //mexPrintf("N: %d M: %d\n",mxGetN(prhs[0]),mxGetM(prhs[0]));
    //mexPrintf("value %f %f %f\n",amplitudes[0],amplitudes[1],amplitudes[2]);
    /* check is d2xx serial connection has been establised, otherwise start it */
    if (ftHandle==NULL){
        ftHandle = ft245rInit();
        if (ftHandle == NULL){
            mexErrMsgIdAndTxt( "chrislib:DAC4interfac:initError",
                    "Could not init d2xx interface.");
        }
        mexAtExit(CloseComms);
    }
    
    if (NULL != ftHandle)
    {
        
        if( mxGetN(prhs[0])==1 ){
            amplitudes[0]=amplitude1[0];
            amplitudes[1]=amplitude2[0];
            amplitudes[2]=amplitude3[0];
            amplitudes[3]=amplitude4[0];
            
            /* Call actual writing to usb subroutine. */
            setCS(&amplitudes, 3);
            
        } else {
            for(count=0;count<=mxGetN(prhs[0])-1;++count)  //for loop terminates if count>n
            {
                amplitudes[0]=amplitude1[count];
                amplitudes[1]=amplitude2[count];
                amplitudes[2]=amplitude3[count];
                amplitudes[3]=amplitude4[count];
                //mexPrintf("value multi %f %f %f\n",amplitudes[0],amplitudes[1]);
                setCS(amplitudes, 3);    /* this statement is equivalent to sum=sum+count */
                Sleep(1); //force delay
            }
        }
    } else {
        mexErrMsgIdAndTxt("chrislib:DAC4interfac:ft245rInit","ft245rInit init failed.");
    }
}

