//https://shakti.com/edu/
#define Z static inline
#define _(z) return z;
#define sysr(f,s) mu f(){mu r;asm volatile (s:"=r"(r));_(r)}
#define FOR(i,n,a)for(I i=0;i<n;i++){a;};

// https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst#1011arithmetic-types
typedef float F; typedef int I; typedef unsigned long long mu;

Z sysr(freq,"mrs %0, cntfrq_el0")
Z sysr(tiks,"mrs %0, cntpct_el0")

Z F b(F* y,I n){F xx=0,yy,xy=0,x_=0,y_=0,x2=0;FOR(i,n,xx+=1;yy=y[i];x_+=xx;y_+=yy;xy+=xx*yy;x2+=xx*xx);_((n*xy-x_*y_)/(n*x2-x_*x_))}

#define tk(a)({mu t0=tiks();{a;};mu t1=tiks();t1-t0;})
#define $t(a)({I n=4;F ts[4];FOR(m,n,F t=tk(FOR(_,m+1,a));ts[m]=t);(b(ts,n)*1e9/(F)freq());})
