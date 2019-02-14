#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "intal.h"

struct ial{
	char* s;
	int n;	
}typedef ial;

void* intal_create(const char* str)
{
	//printf("%s\n", str);
	for(;(!str) || (str[0] == '-');)
		return NULL;

	int count=0;
	int i = 0;
	for(i=0;i<strlen(str);i++)
	{
		for(;str[i]=='0';)
		{
			count++;
			break;
		}
		if(str[i]!='0')
		{
			break;
		}
	}
	for (i = count; i < strlen(str); ++i)
	{
		if(str[i]-48<0 || str[i]-48>9)
			break;
	}
	//--i;
	//printf("%d %d\n", count, i);
	ial* intal=(ial*)malloc(sizeof(ial));
	intal->n=i-count;
	for(;intal->n == 0;)
	{
		intal->n = 1;
		intal->s=(char*)malloc((intal->n)*sizeof(char));
		intal->s[0] = '0' - 48;
		//printf("%s=\n", intal->s);
		return intal;
	}
	intal->s=(char*)malloc((intal->n)*sizeof(char));
	for(int i=0;i<(intal->n);i++)
	{
		intal->s[i]=str[i+count]-48;
	}
	return intal;
}

void intal_destroy(void* intal)
{
	//ial* inta=(ial*)intal;
	//free(inta->s);
	for(;!intal;)
		return;

	free(intal);
}

char* intal2str(void* intal)
{	
	for(;!intal;)
	{
		char* chh=(char*)malloc(3*sizeof(char));
		strcpy(chh, "NaN");
		return chh;
	}
	ial* inta = (ial*)intal;
	char* ch=(char*)malloc((inta->n+1)*sizeof(char));
	for(int i=0;i<(inta->n);i++)
	{
		ch[i]=inta->s[i]+48;
	}
	ch[inta->n]='\0';
	return ch;
}

void* intal_add(void* intal1, void* intal2)
{
	for(;!intal1;)
		return NULL;
	for(;!intal2;)
		return NULL;
	ial* inta1= (ial*)intal1;
	ial* inta2= (ial*)intal2;
	int a=inta1->n;
	int b=inta2->n;
	int flag=0 ;
	int p;
	int c=0;
	ial* intal3=(ial*)malloc(sizeof(ial));
	for (;a>b;)
	{
		a=inta2->n;
		b=inta1->n;
		flag=1;
		break;
	}
	intal3->s=(char*)malloc((b+1)*sizeof(char));
	intal3->n=b+1;
	int diff= b-a;
	for(int i=(a-1);i>=0;i--)
	{
		for(;flag;)
		{
			p=inta1->s[i+diff]+inta2->s[i]+c;
			break;
		}
		for(;!flag;)
		{
			p=inta1->s[i]+inta2->s[i+diff]+c;
			break;
		}
		intal3->s[i+diff+1]=p%10;
		c=p/10;

	}
	for (int i=diff-1;i>=0;i--)
	{
		for(;flag;)
		{
			p=inta1->s[i]+c;
			break;
		}
		for(;!flag;)
		{
			p=inta2->s[i]+c;
			break;
		}
		intal3->s[i+1]=p%10;
		c=p/10;
	}
	intal3->s[0]=c;
	for(;c==0;)
	{
		intal3->s=intal3->s+1;
		intal3->n=b;
		break;
	}
	return intal3;
}

void* intal_increment(void* intal)
{
	for(;!intal;)
		return NULL;
	ial* inta=(ial*)intal;
	
	for(int i=inta->n-1;i>=0;i--)
	{
		if(inta->s[i]!=9)
		{
			inta->s[i]=inta->s[i]+1;
			return inta;
		}
		for(;inta->s[i]==9;)
		{
			inta->s[i]=0;
			break;
		}
	}
	ial* intal1=(ial*)malloc(sizeof(ial));
	intal1->s=(char*)malloc(inta->n+1*sizeof(char));
	intal1->n=inta->n+1;
	intal1->s[0]=1;
	for(int i=1;i<intal1->n;i++)
	{
		intal1->s[i]=0;
	}
	return intal1;
}

void* intal_decrement(void* intal)
{
	for(;!intal;)
		return NULL;
	ial* inta=(ial*)intal;
	for(;!strcmp(intal2str(inta->s),"0");)
		return intal_create("0");
	for(;inta->n==1;)
	{
		if(inta->s[0]==1 || inta->s[0]==0)
		{
			char* ch="0";
			void* intal2= intal_create(ch);
			return intal2;
		}
		break;
	}
	for(int i=inta->n-1;i>=0;i--)
	{
		for(;inta->s[i]!=0;)
		{
			if(i==0 && inta->s[i]==1 )
			{
				inta->s=inta->s+1;
				inta->n=inta->n-1;
				return inta;
			}
			inta->s[i]=inta->s[i]-1;
			return inta;
		}
		for(;inta->s[i]==0;)
		{
			inta->s[i]=9;
			break;
		}
	} 
}

int intal_compare(void* intal1, void* intal2)
{
	ial* a= (ial*)intal1;
	ial* b= (ial*)intal2;
	for(;!intal1;)
		return 0;
	for(;!intal2;)
		return 0;
	//printf("%s=%s", a->s, b->s);
	for(;a->n > b->n;)
	{
		return 1;
	}
	for(;a->n < b->n;)
	{
		return -1;
	}
	for(int i=0;i<a->n;i++)
	{
		for(;a->s[i] > b->s[i];)
		{
			return 1;
		}
		for(;a->s[i] < b->s[i];)
		{
			return -1;
		}
	}
	return 0;
}

void* intal_diff(void* intal1, void* intal2)
{
	for(;!intal1;)
		return NULL;
	for(;!intal2;)
		return NULL;
	ial* a=(ial*)intal1;
	ial* b=(ial*)intal2;
	int flag=intal_compare(intal1,intal2) ;
	ial*c=(ial*)malloc(sizeof(ial)) ;
	int bor=0 ;
	int count=0 ;
	for (;flag==0;)
	{
		c->s=(char*)malloc(1*sizeof(char)) ;
		c->s[0]=0;
		c->n=1 ;
		return c ;
	}
	for(;flag==1;)
	{
		int diff=(a->n)-(b->n) ;
		char p=0 ;
		c->s=(char*)malloc((a->n)*sizeof(char)) ;
		c->n=a->n ;
		for(int i=b->n;i>=0;i--)
		{
			for(;bor==0;)
			{
				for (;a->s[i+diff]>=b->s[i];)
				{
					c->s[i+diff]=a->s[i+diff]-b->s[i];
					break;
				}
				for(;a->s[i+diff]<b->s[i];)
				{
					p=a->s[i+diff]+10 ;
					c->s[i+diff]=p-b->s[i];
					bor=1 ;
					break;
				}
				break;
			}
			for(;bor!=0;)
			{
				for (;a->s[i+diff]>b->s[i];)
				{
					c->s[i+diff]=a->s[i+diff]-b->s[i]-1;
					bor=0 ;
					break;
				}
				for (;a->s[i+diff]<=b->s[i];)
				{
					p=a->s[i+diff]+9 ;
					c->s[i+diff]=p-b->s[i] ;
					break;
				}
				break;
		
			}
		}
		for (int i=(diff-1);i>=0;i--)
		{
			for(;bor==0;)
			{
				c->s[i]=a->s[i] ;
				break;
			}
			for(;bor!=0;)
			{
				for(;a->s[i]==0;) 
				{
					c->s[i]=9 ;
					break;
				}
				for(;a->s[i]!=0;)
				{
					c->s[i]=a->s[i]-1 ;
					bor=0 ;
					break;
				}
				break;
			}
		}
		for(int i=0 ;i<c->n;i++)
		{
			if(c->s[i]!=0)
			{
				break ;
			}
			count++ ;
		}
		
		c->s=c->s+count;
		c->n=c->n-count;
		return c;
	}
	for(;flag!=1;)
	{
		int diff=(b->n)-(a->n) ;
		char p=0 ;
		c->s=(char*)malloc((b->n)*sizeof(char)) ;
		c->n=b->n ;
		for(int i=a->n;i>=0;i--)
		{
			for(;bor==0;)
			{
				for (;b->s[i+diff]>=a->s[i];)
				{
					c->s[i+diff]=b->s[i+diff]-a->s[i];
					break;
				}
				for (;b->s[i+diff]<a->s[i];)
				{
					p=b->s[i+diff]+10 ;
					c->s[i+diff]=p-a->s[i];
					bor=1 ;
					break;
				}
				break;
			}
			for(;bor!=0;)
			{
				for (;b->s[i+diff]>a->s[i];)
				{
					c->s[i+diff]=b->s[i+diff]-a->s[i]-1;
					bor=0 ;
					break;
				}
				for (;b->s[i+diff]<=a->s[i];)
				{
					p=b->s[i+diff]+9 ;
					c->s[i+diff]=p-a->s[i] ;
					break;
				}
				break;
			}
		}
		for (int i=(diff-1);i>=0;i--)
		{
			for(;bor==0;)
			{
				c->s[i]=b->s[i] ;
				break;
			}
			for(;bor!=0;)
			{
				for(;b->s[i]==0;) 
				{
					c->s[i]=9 ;
					break;
				}
				for(;b->s[i]!=0;)
				{
					c->s[i]=b->s[i]-1 ;
					bor=0 ;
					break;
				}
				break;
			}
		}
		for(int i=0 ;i<c->n;i++)
		{
			if(c->s[i]!=0)
			{
				break ;
			}
			count++ ;
		}
		
		//ial* d=(ial*)malloc(sizeof(ial));
		//d->s=(char*)realloc(c->s,(c->n-count)*sizeof(char));
		//d->s=c->s;
		c->s=c->s+count;
		c->n=c->n-count;
		//free(c->s);
		//free(c);
		/*
		for(int i=0;i<c->n-count;i++)
		{
			c->s[i]=c->s[i+count];
		}
		c->n=c->n-count;
		char* ch=c->s+(c->n);
		free(ch);
		return c;*/
		break;
	}
	
}


void* intal_multiply(void* intal1, void* intal2)
{
	/*
	ial* c=(ial*)malloc(sizeof(ial));
	int cnt=0;
	//printf("er");
	//printf("%d",a->n);
	if(a->n==1)
	{
		c->s=(char*)calloc((a->n+b->n),sizeof(char));
		c->n=a->n+b->n;	
		//printf("er");
		char car=0;
		int ch;
		for(int i=b->n-1;i>=0;i--)
		{
			ch=(a->s[0]*b->s[i])+car;
			c->s[i+1]=ch%10;
			car=ch/10;
			//printf("asdfsa");
			//printf("%d\n",ch);
		}
		c->s[0]=car;
		
		if(car==0)
		{
			c->n=c->n-1;
			c->s=c->s+1;
		}
		if (c->n!=1)
		{
			for(int i=0;i<c->n-1;i++)
			{
				if(c->s[i]!=0)
				{
					break;
				}
				cnt++;
			}
			c->s=c->s+cnt;
			c->n=c->n-cnt;
		}
		return c;
		
	}
	if(b->n==1)
	{
		c->s=(char*)calloc((a->n+b->n),sizeof(char));
		c->n=a->n+b->n;
		char car=0;
		char ch;
		for(int i=a->n-1;i>=0;i--)
		{
			ch=(b->s[0]*a->s[i])+car;
			c->s[i+1]=ch%10;
			car=ch/10;
		}
		c->s[0]=car;
		if(car==0)
		{
			c->n=c->n-1;
			c->s=c->s+1;
		}
		if (c->n!=1)
		{
			for(int i=0;i<c->n-1;i++)
			{
				if(c->s[i]!=0)
				{
					break;
				}
				cnt++;
			}
			c->s=c->s+cnt;
			c->n=c->n-cnt;
		}
		return c;
	}
	int m= a->n;
	if(m> b->n)
	{
		m=b->n;
	}
	int m2=m/2;
	ial* high1=(ial*)malloc(sizeof(ial));
	high1->s=(char*)calloc(m2,sizeof(ial));
	high1->n=m2;
	high1->s=a->s;
	ial* low1=(ial*)malloc(sizeof(ial));
	low1->s=(char*)calloc((a->n-m2),sizeof(ial));
	low1->n=a->n-m2;
	low1->s=a->s+m2;
	ial* high2=(ial*)malloc(sizeof(ial));
	high2->s=(char*)calloc(m2,sizeof(ial));
	high2->n=m2;
	high2->s=b->s;
	ial* low2=(ial*)malloc(sizeof(ial));
	low2->s=(char*)calloc((b->n-m2),sizeof(ial));
	low2->n=b->n-m2;
	low2->s=b->s+m2;
	ial* z0=intal_multiply(low1,low2);
	ial* A=intal_add(high1,low1);
	ial* B=intal_add(high2,low2);
	ial* z1=intal_multiply(A,B);
	ial* z2=intal_multiply(high1,high2);
	//printf("z0: %s\n", intal2str(z0));
	//printf("z1: %s\n", intal2str(z1));
	//printf("z2: %s\n", intal2str(z2));
	
	ial* r1=(ial*)malloc(sizeof(ial));
	r1->s=(char*)calloc(((2*m2)+z2->n),sizeof(char));
	r1->n=(2*m2)+z2->n;
	for(int i=0;i<z2->n;i++)
	{
		r1->s[i]=z2->s[i];
	}
	for (int i=z2->n;i<r1->n;i++)
	{
		r1->s[i]=0;
	}
	printf("r2: %s\n", intal2str(r1));
	ial* x1=intal_diff(z1,z2);
	ial* x2=intal_diff(x1,z0);
	ial* r2=(ial*)malloc(sizeof(ial));
	r2->n=x2->n+m2;
	r2->s=(char*)calloc(r2->n,sizeof(char));
	for (int i=0;i<x2->n;i++)
	{
		r2->s[i]=x2->s[i];
	}
	for (int i=x2->n;i<r2->n;i++)
	{
		r2->s[i]=0;
	}
	ial* R=intal_add(r1,r2);
	ial* res=intal_add(R,z0);
	return res;*/
	for(;!intal1;)
		return NULL;
	for(;!intal2;)
		return NULL;
	ial* a=(ial*)intal1;
	ial* b=(ial*)intal2;
	int cnt=0;
	ial* d=(ial*)malloc(sizeof(ial));
	//ial* c=(ial*)malloc(sizeof(ial));
	d->s=(char*)malloc(sizeof(char));
	d->s[0]=0;
	d->n=1;
	int z;
	for(int j=b->n-1;j>=0;j--)
	{
		cnt=0;
		ial* c=(ial*)malloc(sizeof(ial));
		z= b->n-1-j;
		c->s=(char*)calloc((a->n+1+z),sizeof(char));
		c->n=a->n+1+z;
		char car=0;
		char ch;
		for(int i=a->n-1;i>=0;i--)
		{
			ch=(b->s[j]*a->s[i])+car;
			c->s[i+1]=ch%10;
			car=ch/10;
		}
		for (int k=a->n+1;k<c->n;k++)
		{
			c->s[k]=0;
		}
		c->s[0]=car;
		//printf("c: %s\n", intal2str(c));	

		for(int i=0;i<c->n-1;i++)
		{
			if(c->s[i]!=0)
			{
				break;
			}
			//printf("check");
			cnt++;
		}
		c->s=c->s+cnt;
		c->n=c->n-cnt;
		d=intal_add(c,d);
		//printf("c: %s\n", intal2str(c));
		free(c);
	}
	return d;
}



/*
void* intal_divide(void* intal1, void* intal2)
{
	
	ial* d=(ial*)malloc(sizeof(ial));
	ial* q=(ial*)malloc(sizeof(ial));	
	q->s=(char*)malloc(sizeof(char));
	q->s[0]=0;
	q->n=1;
	check=intal_compare(a,b);
	while(check==1)
	{
		diff=c->n-b->n;
		if(diff>1)
		{
			ial* temp=(ial*)malloc(sizeof(ial));
			temp->s=(char*)malloc(diff*sizeof(char));
			temp->n=diff;
			temp->s[0]=1;
			//q=intal_add(q,temp);
			d->s=(char*)malloc((b->n+diff-1)*sizeof(char));
			d->n=b->n+diff-1;
			for(int i=0;i<b->n;i++)
			{
				d->s[i]=b->s[i];
			}
			intal_diff(c,d);
			q=intal_add(q,temp);
			//printf("q: %s\n", intal2str(q));
			//printf("temp: %s\n", intal2str(temp));
			free(temp);
		}
		else
		{
			c=intal_diff(c,b);
			q=intal_increment(q);
			//printf("q: %s\n", intal2str(q));
		}
		check=intal_compare(c,b);
	}
	//free(temp);
	free(c);
	free(d);
	return q;
} 	
*//* failed attempt 1*/
/*
void* intal_divide(void* intal1, void* intal2)
{
	ial* a= (ial*)intal1;
	ial* b= (ial*)intal2;
	ial* h=(ial*)malloc(sizeof(ial));
	h->s=(char*)malloc(a->n*sizeof(char));
	h->n=0;
	int j=0;
	int count=0;
	int check;
	int cnt=0;
	ial* c=(ial*)malloc(sizeof(ial));
	c->s=(char*)malloc(a->n*sizeof(char));
	c->n=a->n;
	ial* d=(ial*)malloc(sizeof(ial));
	ial*q=(ial*)malloc(sizeof(ial));
	d->s=c->s;
	d->n=b->n;
	for(int i=0;i<a->n;i++)
	{
		c->s[i]=a->s[i];
	}	

	while (count<=a->n-b->n)
	{
		check=intal_compare(d,b);
		count=count+b->n-cnt;
		cnt=0;
		if (check==-1)
		{
			if(count<=(a->n))
			{	
				d->n=d->n+1;
				d->s=(char*)realloc(d->s,d->n*sizeof(char));
				d->s[d->n-1]=c->s[count];
				count++;
				h->s[j]=0;
				j++;
				h->n=j;
			}
			else
			{
				break;
			}
		}
		else
		{
			q->s=(char*)malloc(sizeof(char));
			q->n=1;
			q->s[0]=0;
			while(check)
			{
				d=intal_diff(d,b);
				check=intal_compare(d,b);
				q=intal_increment(q);
			}
			for(int i=0;i<q->n;i++)
			{
				h->s[j]=q->s[i];
				j++;
				h->n=j;
				
			}
			printf("h: %s\n", intal2str(h));
			if(d->n==1 && d->s[0]==0)
			{
				d->n=b->n;
				d->s=c->s+count;
				count+=b->n;
			}
			else
			{
				cnt=d->n;
				d->n=b->n;
				d->s=(char*)realloc(d->s,d->n*sizeof(char));
				for(int i=cnt;i<d->n;i++)
				{
					d->s[i]=b->s[count+i];
				}
			}
		}
	}
	return h;
}*//*failed attempt 2 did not account for the zero adding process and the count variable can go out of bound*/

void* intal_divide(void* intal1, void* intal2)
{
	for(;!intal1;)
		return NULL;
	for(;!intal2;)
		return NULL;
	ial* a=(ial*)intal1;
	ial* b=(ial*)intal2;
	for(;!strcmp((b->s), "0");)
		return NULL;
	for(;b->n==1;)
	{
		for(;b->s[0]==0;)
		{
			return NULL;
		}
		for(;b->s[1]==1;)
		{
			ial* c=(ial*)malloc(sizeof(ial));
			c->s=(char*)malloc(a->n*sizeof(char));
			c->n=a->n;
			for(int i=0;i<a->n;i++)
			{
				c->s[i]=a->s[i];
			}
			return c;

		}
		break;
	}
	int chk;
	chk=intal_compare(a,b);
	for(;chk==0;)
	{
			ial* c=(ial*)malloc(sizeof(ial));
			c->s=(char*)malloc(sizeof(char));
			c->s[0]=1;
			c->n=1;
			return c;
	} 
	for(;chk==-1;)
	{
		//printf("er\n");
		ial* c=(ial*)malloc(sizeof(ial));
		c->s=(char*)malloc(sizeof(char));
		c->s[0]=0;
		c->n=1;
		return c;
	}
	ial* h=(ial*)malloc(sizeof(ial));
	h->s=(char*)malloc(a->n*sizeof(char));
	h->n=0;
	int j=0;
	ial* q=(ial*)malloc(sizeof(ial));
	int count=-1;
	int tmp;
	//int cnt=0;
	ial* temp=(ial*)malloc(sizeof(ial));
	ial* temp1=(ial*)malloc(sizeof(ial));
	temp->s=(char*)malloc((b->n+1)*sizeof(char));
	temp->n=b->n;
	//temp->s=a->s;
	for(int i=0;i<temp->n;i++)
	{
		temp->s[i]=a->s[++count];
	}
	int check=intal_compare(b,temp);
	//count=count+b->n-1;
	for(;check==1;)
	{
		temp->n=temp->n+1;
		//temp->s=(char*)realloc(temp->s,temp->n*sizeof(char));
		/*for(int i=0;i<temp->n-1;i++)
		{
			temp1->s[i]=temp->s[i];
		}*/
		temp->s[temp->n-1]=a->s[++count];
		//temp->s=temp1->s;
		//check=intal_compare(b,temp);
		break;
		
	}
	//printf("temp: %s\n", intal2str(temp));

	while(a->n > count)
	{
		//printf("er");
		//printf("temp: %s\n", intal2str(temp));
		check=intal_compare(temp,b);
		q->s=(char*)malloc(1*sizeof(char));
		q->s[0]=0;
		q->n=1;
		while(check!=-1)
		{
			temp=intal_diff(temp,b);
			q=intal_increment(q);
			check=intal_compare(temp,b);
		}
		h->s[j]=q->s[q->n-1];//the length of q is 1 only 
		/*printf("%d\n",q->n);
		if(q->n!=1)
		{
			printf("q: %s\n", intal2str(q));
		}*/
		j++;
		//check=intal_compare(b,temp);
		tmp=temp->n;
		for(;tmp==1 && temp->s[0]==0;)
		{
			tmp--;
			break;
		}
		temp1->s=(char*)malloc((tmp)*sizeof(char));
		temp1->n=tmp;
		for(int i=0;i<tmp;i++)
		{
			temp1->s[i]=temp->s[i];
		}
		//temp1->s[tmp]=a->s[++count];
		temp->s=(char*)malloc((tmp+1)*sizeof(char));
		temp->n=tmp+1;
		for(int i=0;i<temp->n;i++)
		{
			temp->s[i]=temp1->s[i];
		}
		temp->s[tmp]=a->s[++count];
	}
	h->n=j;
	return h;
}

void* intal_pow(void* intal1, void* intal2)
{
	for(;!intal1;)
		return NULL;
	for(;!intal2;)
		return NULL;
	ial* a=(ial*)intal1;
	ial* b=(ial*)intal2;
	for(;(!strcmp((a->s), "0")) && (!strcmp((b->s), "0"));)
		return intal_create("0");
	for(;!strcmp((a->s), "0");)
		return intal_create("1");
	
	for(;b->n==1 && b->s[0]==0;)
	{
		ial* c=(ial*)malloc(sizeof(ial));
		c->s=(char*)malloc(sizeof(char));
		c->s[0]=1;
		c->n=1;
		return c;
	}
	ial* d=(ial*)malloc(sizeof(ial));
	d->s=(char*)malloc(sizeof(char));
	d->s[0]=2;
	d->n=1;
	ial* c = intal_divide(b,d);
	ial* p=intal_pow(a,c);
	ial* x=intal_multiply(p,p);
	int k =b->s[b->n-1];
	//printf("%d",k);	
	for (;k%2==1;)
	{
		//printf("%d",k);
		x=intal_multiply(x,a);
		break;
	}
	return x;
}

