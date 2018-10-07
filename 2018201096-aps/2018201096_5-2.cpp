#include<bits/stdc++.h>
using namespace std;

class stringBuilder
{
public:
    std::vector<const char *> v;
    
};

void printStringBuilder(stringBuilder s){
    for (int i = 0; i < s.v.size(); ++i)
    {
        cout<<s.v[i];
    }
    cout<<endl;

}

stringBuilder stringInitialze(const char *c){
    stringBuilder s;
    s.v.push_back(c);
    return s;
}

char buffer[1000000];
void computeLPSArray(const char* pat, long M, long* lps) 
{ 
    int len = 0; 
    lps[0] = 0;
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else
        { 
            if (len != 0) { 
                len = lps[len - 1]; 
            } 
            else
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 

stringBuilder stringAppend(stringBuilder a, stringBuilder b){
    stringBuilder result;
    for (int i = 0; i < a.v.size(); ++i)
        result.v.push_back(a.v[i]);
    for (int i = 0; i < b.v.size(); ++i)
        result.v.push_back(b.v[i]);
    return result;
}

void toStr(stringBuilder s){
    memset(buffer,'\0',sizeof(buffer));
    int k=0;
    for (int i = 0; i < s.v.size(); ++i)
    {
        for(long j=0;j<strlen(s.v[i]);j++)
            buffer[k++]=(s.v[i][j]);
    }
}

long findSubstring(stringBuilder a, const char * pat){
    cout<<"In findSubstring\n";
    toStr(a);
    printf("buffer %s\n", buffer );
    long M = strlen(pat); 
    long N = strlen(buffer); 
    long lps[M];
    computeLPSArray(pat, M, lps); 
    long i = 0;
    long j = 0;
    while (i < N) { 
        if (pat[j] == buffer[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            // printf("Found pattern at index %d ", i - j); 
            return (i - j);
            j = lps[j - 1]; 
        }   
        else if (i < N && pat[j] != buffer[i]) { 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
    return -1;
}

int main()
{   
    stringBuilder s1=stringInitialze("aa");
    printStringBuilder(s1);
    stringBuilder s2=stringInitialze("badsadab");
    printStringBuilder(s2);
    stringBuilder s3=stringInitialze("cc");
    printStringBuilder(s3);
    stringBuilder s4=stringInitialze("dd");
    stringBuilder s5=stringAppend(s1,s2);
    printStringBuilder(s5);
    long index2 = findSubstring(s5, "sad");
    cout<<index2;
        return 0;
}
