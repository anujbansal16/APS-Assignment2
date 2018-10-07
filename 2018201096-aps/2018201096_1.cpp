#include<bits/stdc++.h>
using namespace std;

struct suffix
{
	int index;
	int rank1;
	int rank2;
};

bool comp(suffix s1, suffix s2){
	if(s1.rank1<s2.rank1)
		return 1;
	else if(s1.rank1>s2.rank1)
		return 0;
	else{
		if(s1.rank2<s2.rank2)
			return 1;
		else
			return 0;
	}
}

void buildSuffixTree(string s, int n, int result[]){
	suffix suffixes[n];
	int indexes[n];
	for (int i = 0; i < n; ++i)
	{
		suffixes[i].index=i;
		suffixes[i].rank1=s[i]-97;
		suffixes[i].rank2=(i+1<n?s[i+1]-97:-1);// chracter at right- 1 
	}
	sort(suffixes,suffixes+n,comp);
	for(int j=2;j<n;j*=2){
		int prank=suffixes[0].rank1; 
		int rank=0;
		indexes[suffixes[0].index]=0;
        suffixes[0].rank1=0; 
		for(int i=1;i<n;i++){			
			if(suffixes[i].rank1==prank && suffixes[i].rank2==suffixes[i-1].rank2){
				prank=suffixes[i].rank1;
				suffixes[i].rank1=rank;
			}
			else{
				prank=suffixes[i].rank1;
				suffixes[i].rank1=++rank;
			}
			indexes[suffixes[i].index]=i;
		}
		for (int i = 0; i < n; ++i)//change rank2
			suffixes[i].rank2=(suffixes[i].index+j)<n?suffixes[indexes[suffixes[i].index+j]].rank1:-1;
		sort(suffixes,suffixes+n,comp);
	}
	for (int i = 0; i < n; ++i)
		result[i]=suffixes[i].index;
}

int main(int argc, char const *argv[])
{
	string s1="dcabca";
	string s=s1+s1;
	int result[s.size()];
	buildSuffixTree(s,s.size(),result);
	for (int i = 0; i < s.size(); ++i){
		if(result[i]<s1.size()){
			cout<<s.substr(result[i],s1.size());
			break;
		}
	}
	return 0;
}