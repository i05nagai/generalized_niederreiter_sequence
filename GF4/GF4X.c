#include<stdio.h>
#include<stdlib.h>
#include"GF4.h"

GF4X *GF4X_new( int degree ){
	GF4X *v;
	v = (GF4X*)malloc(sizeof(GF4X));
	v->degree = degree;
	v->a = (char*)malloc((degree+1)*sizeof(char));
	return v;
}

void GF4X_del( GF4X *t ){
	free(t->a);
	free(t);
}

void GF4X_mult_GF4(char a, GF4X *t){
	int i;
	if ( a != 0 )
		for(i=0;i < t->degree+1; i++)
			t->a[i] = GF4_mult(a, t->a[i]);
	else{
		t->degree = 0;
		t->a = (char*)realloc(t->a, sizeof(char*));
		t->a[0] = 0;
	}
}

void GF4X_copy(GF4X *from, GF4X *to){
	int i, degree;
	degree = to->degree = from->degree;
	to->a = (char*)realloc(to->a, (degree+1)*sizeof(char));
	for(i=0; i<degree+1; i++)
		to->a[i] = from->a[i];
}

int GF4X_is_zero(GF4X *t){
	int i, v;
	v = 1;
	for(i=0;i<t->degree+1;i++)
		if(t->a[i] != 0)
			v = 0;
	return v;
}

void GF4X_set_zero(GF4X *t){
	t->degree = 0;
	t->a = (char*)realloc(t->a, sizeof(char));
	t->a[0] = 0;
}

void GF4X_clear(GF4X *t){
	int i;
	for(i=0;i < t->degree+1;i++)
		t->a[i] = 0;
}

void GF4X_mult_x_n(GF4X *a, int n){
	char *buf;
	int i;
	buf = (char*)calloc(a->degree+1+n,sizeof(char));
	for(i=0;i<a->degree+1;i++)
		buf[i] = a->a[i];
	for(i=a->degree+1; i<a->degree+1+n;i++)
		buf[i] = 0;
	free(a->a);
	a->a = buf;
	a->degree += n;
}

void GF4X_add_assign(GF4X *a, GF4X *b){
	char *buf;
	int deg, i, j;

	deg = (a->degree > b->degree)? a->degree : b->degree;
	buf = (char*)calloc(deg+1, sizeof(char));
	for(i=0;i<deg+1;i++){
		char ax, bx;
		ax = (i >= deg - a->degree)? a->a[i - deg + a->degree] : 0;
		bx = (i >= deg - b->degree)? b->a[i - deg + b->degree] : 0;
		buf[i] = GF4_add(ax, bx);
	}
	for(j=0; j<deg+1; j++)
		if(buf[j] != 0)
			break;
	deg -=j;
	a->degree = deg;
	a->a = (char*)realloc(a->a, (deg+1)*sizeof(char));
	for(i=0;i<deg+1;i++)
		a->a[i] = buf[j+i];
	free(buf);
}

void GF4X_sub_assign(GF4X *a, GF4X *b){
	char *buf;
	int deg, i, j;

	deg = (a->degree > b->degree)? a->degree : b->degree;
	buf = (char*)calloc(deg+1, sizeof(char));
	for(i=0;i<deg+1;i++){
		char ax, bx;
		ax = (i >= deg - a->degree)? a->a[i - deg + a->degree] : 0;
		bx = (i >= deg - b->degree)? b->a[i - deg + b->degree] : 0;
		buf[i] = GF4_sub(ax, bx);
	}
	for(j=0;j<deg;j++)
		if(buf[j] != 0)
			break;
	deg -=j;
	a->degree = deg;
	a->a = (char*)realloc(a->a, (deg+1)*sizeof(char));
	for(i=0;i<deg+1;i++)
		a->a[i] = buf[j+i];
	free(buf);
}

void GF4X_div(GF4X *a, GF4X *b, GF4X *q, GF4X *r){
	GF4X *tb, *tq;

	GF4X_copy(a,r);
	tq = GF4X_new(a->degree - b->degree);
	tb = GF4X_new(b->degree);
	GF4X_clear(tq);
	while(r->degree >= b->degree){
		char c;
		c = tq->a[a->degree - r->degree] =
			GF4_mult(r->a[0], GF4_inv(b->a[0]));
		GF4X_copy(b, tb);
		GF4X_mult_GF4(c, tb);
		GF4X_mult_x_n(tb, r->degree - tb->degree);
		GF4X_sub_assign(r, tb);
		if(GF4X_is_zero(r)){
			GF4X_set_zero(r);
			break;
		}
	}
	if(GF4X_is_zero(tq))
		GF4X_set_zero(q);
	else
		GF4X_copy(tq, q);
	GF4X_del(tq);
	GF4X_del(tb);
}

void GF4X_display( GF4X *X ){

	int i;
	for( i = 0; i <= X->degree; i++)
		printf("%x",X->a[i]);

}
