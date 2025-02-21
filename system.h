
#ifndef XC_HEADER_TEMPLATE_H_SYSTEM
#define	XC_HEADER_TEMPLATE_H_SYSTEM

static const unsigned short Mmin = 2; 
static const unsigned short Mmax = 513; 
static const unsigned short N1min = 2;
static const unsigned short N1max = 33;
static const unsigned short N2all[3] = {2, 4, 8};


void EnablePLL(unsigned long long freqIn, unsigned long long freqOut);


#endif	/* XC_HEADER_TEMPLATE_H */

