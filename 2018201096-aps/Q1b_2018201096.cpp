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
	string s="ababbaabb";
	int result[s.size()];
	buildSuffixTree(s,s.size(),result);
	int lcp[s.size()];
	int result3[s.size()];
	// cout<<s.substr(result[0],s.size()-result[0])<<endl;
	memset(lcp,0,sizeof(lcp));
	memset(result3,0,sizeof(result3));
	result3[0]=1;
	for (int i = 0; i < s.size()-1; ++i){
		int j=result[i],k=result[i+1];
		bool flag=true;
		cout<<s.substr(j,s.size())<<endl;
		while(j<s.size()&&k<s.size()){
			if(s[j]!=s[k]){
				flag=false;
				break;
			}
			lcp[i]++;
			j++;k++;
		}
	}
	for (int i = 0; i < s.size(); ++i){
		cout<<result[i]<<" "<<s.substr(result[i],s.size())<<"\n";
	}
	cout<<endl;
	for (int i = 0; i < s.size(); ++i)
		cout<<lcp[i]<<" ";
	cout<<endl;
	int K=4;
	int ans=0;
	for(int i = 0;i<(s.size()-3+1);i++){
		ans=max(ans, min(lcp[i],lcp[i+3]));
		cout<<i<<" "<<i+3<<" "<<ans<<"\n";
	}
	cout<<endl;
    cout<<ans;
	return 0;
}