#include<stdio.h>
#include<stdlib.h>
#include"GF.h"

GFX *GFX_new( int degree ){
	GFX *v;
	v = (GFX*)malloc(sizeof(GFX));
	v->degree = degree;
	v->a = (unsigned char*)malloc((degree+1)*sizeof(unsigned char));
	return v;
}

void GFX_del( GFX *t ){
	free(t->a);
	free(t);
}

void GFX_mult_GF(unsigned char a, GFX *t){
	int i;
	if ( a != 0 )
		for(i=0;i < t->degree+1; i++)
			t->a[i] = GF_mult(a, t->a[i]);
	else{
		t->degree = 0;
		t->a = (unsigned char*)realloc(t->a, sizeof(unsigned char*));
		t->a[0] = 0;
	}
}

void GFX_copy(GFX *from, GFX *to){
	int i, degree;
	degree = to->degree = from->degree;
	to->a = (unsigned char*)realloc(to->a, (degree+1)*sizeof(unsigned char));
	for(i=0; i<degree+1; i++)
		to->a[i] = from->a[i];
}

int GFX_isZero(GFX *t){
	int i, v;
	v = 1;
	for(i=0;i<t->degree+1;i++)
		if(t->a[i] != 0)
			v = 0;
	return v;
}

void GFX_setZero(GFX *t){
	t->degree = 0;
	t->a = (unsigned char*)realloc(t->a, sizeof(unsigned char));
	t->a[0] = 0;
}

void GFX_clear(GFX *t){
	int i;
	for(i=0;i < t->degree+1;i++)
		t->a[i] = 0;
}

void GFX_mult_x_n(GFX *a, int n){
	unsigned char *buf;
	int i;
	buf = (unsigned char*)calloc(a->degree+1+n,sizeof(unsigned char));
	for(i=0;i<a->degree+1;i++)
		buf[i] = a->a[i];
	for(i=a->degree+1; i<a->degree+1+n;i++)
		buf[i] = 0;
	free(a->a);
	a->a = buf;
	a->degree += n;
}

void GFX_add_assign(GFX *a, GFX *b){
	unsigned char *buf;
	int deg, i, j;

	deg = (a->degree > b->degree)? a->degree : b->degree;
	buf = (unsigned char*)calloc(deg+1, sizeof(unsigned char));
	for(i=0;i<deg+1;i++){
		unsigned char ax, bx;
		ax = (i >= deg - a->degree)? a->a[i - deg + a->degree] : 0;
		bx = (i >= deg - b->degree)? b->a[i - deg + b->degree] : 0;
		buf[i] = GF_add(ax, bx);
	}
	for(j=0; j<deg+1; j++)
		if(buf[j] != 0)
			break;
	deg -=j;
	a->degree = deg;
	a->a = (unsigned char*)realloc(a->a, (deg+1)*sizeof(unsigned char));
	for(i=0;i<deg+1;i++)
		a->a[i] = buf[j+i];
	free(buf);
}

void GFX_sub_assign(GFX *a, GFX *b){
	unsigned char *buf;
	int deg, i, j;

	deg = (a->degree > b->degree)? a->degree : b->degree;
	buf = (unsigned char*)calloc(deg+1, sizeof(unsigned char));
	for(i=0;i<deg+1;i++){
		unsigned char ax, bx;
		ax = (i >= deg - a->degree)? a->a[i - deg + a->degree] : 0;
		bx = (i >= deg - b->degree)? b->a[i - deg + b->degree] : 0;
		buf[i] = GF_sub(ax, bx);
	}
	for(j=0;j<deg;j++)
		if(buf[j] != 0)
			break;
	deg -=j;
	a->degree = deg;
	a->a = (unsigned char*)realloc(a->a, (deg+1)*sizeof(unsigned char));
	for(i=0;i<deg+1;i++)
		a->a[i] = buf[j+i];
	free(buf);
}

void GFX_div(GFX *a, GFX *b, GFX *q, GFX *r){
	GFX *tb, *tq;

	GFX_copy(a,r);
	tq = GFX_new(a->degree - b->degree);
	tb = GFX_new(b->degree);
	GFX_clear(tq);
	while(r->degree >= b->degree){
		unsigned char c;
		c = tq->a[a->degree - r->degree] =
			GF_mult(r->a[0], GF_inv(b->a[0]));
		GFX_copy(b, tb);
		GFX_mult_GF(c, tb);
		GFX_mult_x_n(tb, r->degree - tb->degree);
		GFX_sub_assign(r, tb);
		if(GFX_isZero(r)){
			GFX_setZero(r);
			break;
		}
	}
	if(GFX_isZero(tq))
		GFX_setZero(q);
	else
		GFX_copy(tq, q);
	GFX_del(tq);
	GFX_del(tb);
}

void GFX_display( GFX *X ){

	int i;
	for( i = 0; i <= X->degree; i++)
		printf("%x",X->a[i]);

}
