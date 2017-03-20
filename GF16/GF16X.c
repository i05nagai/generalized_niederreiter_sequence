#include<stdio.h>
#include<stdlib.h>
#include"GF16.h"

GF16X *GF16X_new( int degree ){
	GF16X *v;
	v = (GF16X*)malloc(sizeof(GF16X));
	v->degree = degree;
	v->a = (char*)malloc((degree+1)*sizeof(char));
	return v;
}

void GF16X_del( GF16X *t ){
	free(t->a);
	free(t);
}

void GF16X_mult_GF16(char a, GF16X *t){
	int i;
	if ( a != 0 )
		for(i=0;i < t->degree+1; i++)
			t->a[i] = GF16_mult(a, t->a[i]);
	else{
		t->degree = 0;
		t->a = (char*)realloc(t->a, sizeof(char*));
		t->a[0] = 0;
	}
}

void GF16X_copy(GF16X *from, GF16X *to){
	int i, degree;
	degree = to->degree = from->degree;
	to->a = (char*)realloc(to->a, (degree+1)*sizeof(char));
	for(i=0; i<degree+1; i++)
		to->a[i] = from->a[i];
}

int GF16X_is_zero(GF16X *t){
	int i, v;
	v = 1;
	for(i=0;i<t->degree+1;i++)
		if(t->a[i] != 0)
			v = 0;
	return v;
}

void GF16X_set_zero(GF16X *t){
	t->degree = 0;
	t->a = (char*)realloc(t->a, sizeof(char));
	t->a[0] = 0;
}

void GF16X_clear(GF16X *t){
	int i;
	for(i=0;i < t->degree+1;i++)
		t->a[i] = 0;
}

void GF16X_mult_x_n(GF16X *a, int n){
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

void GF16X_add_assign(GF16X *a, GF16X *b){
	char *buf;
	int deg, i, j;

	deg = (a->degree > b->degree)? a->degree : b->degree;
	buf = (char*)calloc(deg+1, sizeof(char));
	for(i=0;i<deg+1;i++){
		char ax, bx;
		ax = (i >= deg - a->degree)? a->a[i - deg + a->degree] : 0;
		bx = (i >= deg - b->degree)? b->a[i - deg + b->degree] : 0;
		buf[i] = GF16_add(ax, bx);
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

void GF16X_sub_assign(GF16X *a, GF16X *b){
	char *buf;
	int deg, i, j;

	deg = (a->degree > b->degree)? a->degree : b->degree;
	buf = (char*)calloc(deg+1, sizeof(char));
	for(i=0;i<deg+1;i++){
		char ax, bx;
		ax = (i >= deg - a->degree)? a->a[i - deg + a->degree] : 0;
		bx = (i >= deg - b->degree)? b->a[i - deg + b->degree] : 0;
		buf[i] = GF16_sub(ax, bx);
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

void GF16X_div(GF16X *a, GF16X *b, GF16X *q, GF16X *r){
	GF16X *tb, *tq;

	GF16X_copy(a,r);
	tq = GF16X_new(a->degree - b->degree);
	tb = GF16X_new(b->degree);
	GF16X_clear(tq);
	while(r->degree >= b->degree){
		char c;
		c = tq->a[a->degree - r->degree] =
			GF16_mult(r->a[0], GF16_inv(b->a[0]));
		GF16X_copy(b, tb);
		GF16X_mult_GF16(c, tb);
		GF16X_mult_x_n(tb, r->degree - tb->degree);
		GF16X_sub_assign(r, tb);
		if(GF16X_is_zero(r)){
			GF16X_set_zero(r);
			break;
		}
	}
	if(GF16X_is_zero(tq))
		GF16X_set_zero(q);
	else
		GF16X_copy(tq, q);
	GF16X_del(tq);
	GF16X_del(tb);
}

void GF16X_display( GF16X *X ){

	int i;
	for( i = 0; i <= X->degree; i++)
		printf("%x",X->a[i]);

}
