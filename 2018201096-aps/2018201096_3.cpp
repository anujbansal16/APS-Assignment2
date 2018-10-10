#include<iostream>
#include<algorithm>
#include <stdio.h>
#include <ctime>
#define rep(i,a,b) for(long i=a;i<b;i++)
using namespace std;
typedef long l;

l randGenerator(l low, l high){
	return low+rand()%(high-low+1);
}

l partition(l a[], l low, l r ){
	l i=low;	
	l randindex=randGenerator(low, r);
	swap(a[randindex], a[r]);
	l pVal=a[r];
	for(l j=low;j<r;j++){
		if(a[j]<=pVal){
			swap(a[i],a[j]);
			i++;
		}	
	}
	swap(a[i],a[r]);
	return i;
}

l findKth(l a[], l low, l high, l k){
	if(k<=0 || k>high-low+1)
		return -1;
	l pivot=partition(a,low,high);
	if(pivot-low==k-1)
		return a[pivot];
	else if(pivot-low>k-1)
		return findKth(a, low, pivot-1, k );
	else
		return findKth(a, pivot+1, high, k-(pivot-low+1));
}

int main()
{
	l n,k;
	scanf("%ld%ld", &n, &k);
	l a[n];
	rep(i,0,n)
		scanf("%ld", &a[i]);

    clock_t tStart = clock();
	long kth=findKth(a,0,n-1,k);
	clock_t tstop = clock();
	
	cout<<"kth smallest element: "<<kth<<"\n";
	cout<<(tstop-tStart)<<" clocks taken";
	cout<<endl;
	tStart = clock();
	nth_element(a,a+k-1,a+n);
	tstop = clock();
	cout<<(tstop-tStart)<<" clocks taken by nth_element";
	cout<<endl;
	return 0;
}