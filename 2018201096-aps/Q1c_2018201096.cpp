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

void buildSuffixArray(string s, int n, int result[]){
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
	string s;
	cin>>s;
	string s1=s;
	int oLength=s.size();
	int k=0;
	for(int j=oLength-1;j>=0;j--)
		s1[k++]=s[j];
	
	s1=s+"#"+s1;//banana#ananab
	int mLength=s1.size();//size of banana
	int result[s1.size()];//size of banana#ananab
	
	buildSuffixArray(s1,s1.size(),result);

	int lcp[s1.size()];//lcp calculated in nlogn
	memset(lcp,0,sizeof(lcp));
	int inv[mLength];
	for (int i=0;i<mLength;i++) 
        inv[result[i]] =i; 
    k=0;
    //ksai algorithm
	for (int i=0;i<mLength;++i){
		if(inv[i]==mLength-1){
			k=0;
			continue;
		}
        int j=result[inv[i]+1];//next suffix 
        // Directly start matching from k'th index as 
        // at-least k-1 characters will match 
        while (i+k<mLength && j+k<mLength && s1[i+k]==s1[j+k]) 
            k++; 
        lcp[inv[i]]=k; // lcp for the present suffix. 
        // Deleting the starting character from the string. 
        if(k>0) 
            k--; 
	}
	// for (int i = 0; i < mLength; ++i)
	// 	cout<<result[i]<<" ";
	// cout<<endl;
	// for (int i = 0; i < mLength; ++i)
	// 	cout<<lcp[i]<<" ";
	// cout<<endl;
	int position=0;
	int longestlength=0;
    for(int i=0;i<mLength-1;++i)
    {
        if((lcp[i]>longestlength))
        {
            if((result[i+1]<oLength && result[i]>oLength)||(result[i]<oLength && result[i+1]>oLength))
            {	
                longestlength=lcp[i];
                position=result[i];
                // cout<<"string "<<s1.substr(position,longestlength)<<" "<<position<<" " << longestlength<<endl;
            }
        }
    }
    cout<<"longest Palindrome length "<<longestlength;
    cout<<" with string "<<s1.substr(position,longestlength)<<endl;
	
	return 0;
}