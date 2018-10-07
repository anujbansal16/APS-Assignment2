#include<bits/stdc++.h>
using namespace std;
long k;
typedef struct stringBuilderStruct
{
    const char *s;
    struct stringBuilderStruct *left;
    struct stringBuilderStruct *right;
    bool isLeaf;
} *stringBuilder;

void printStringBuilder(stringBuilder a){
    if(a!=NULL){
        printStringBuilder(a->left);
        if(a->isLeaf)
            cout<<(a->s);
        printStringBuilder(a->right);
    }
}

stringBuilder stringInitialze(const char *c){
    stringBuilder newStringBuilder=(stringBuilder)malloc(sizeof(struct stringBuilderStruct));
    newStringBuilder->s=c;
    newStringBuilder->left=NULL;
    newStringBuilder->right=NULL;
    newStringBuilder->isLeaf=true;
    return newStringBuilder;
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
    stringBuilder s3=(stringBuilder)malloc(sizeof(struct stringBuilderStruct));
    s3->left=a;
    s3->right=b;
    s3->isLeaf=false;
    return s3;
}

void toStr(stringBuilder a){
    if(a!=NULL){
        toStr(a->left);
        if(a->isLeaf)
            for(long i=0;i<strlen(a->s);i++)
                buffer[k++]=(a->s)[i];
        toStr(a->right);
    }
}

long findSubstring(stringBuilder a, const char * pat){
    // cout<<"In findSubstring\n";
    k=0;
    memset(buffer,'\0',sizeof(buffer));
    toStr(a);
    // printf("buffer %s\n", buffer );
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
    stringBuilder s1=stringInitialze("hello");
    printStringBuilder(s1);
    cout<<endl;
    stringBuilder s2=stringInitialze(" world");
    printStringBuilder(s2);
    cout<<endl;
    stringBuilder s3=stringInitialze("cc");
    printStringBuilder(s3);
    cout<<endl;
    stringBuilder s4=stringAppend(s3,s3);
    printStringBuilder(s4);
    cout<<endl;
    stringBuilder s5=stringAppend(s1,s2);
    printStringBuilder(s5);
    cout<<endl;
    stringBuilder s6=stringAppend(s5,s3);
    printStringBuilder(s6);
    cout<<endl;
    stringBuilder s7=stringAppend(s6,s6);
    printStringBuilder(s7);
    cout<<endl;
    stringBuilder s8=stringAppend(s4,s6);
    printStringBuilder(s8);
    cout<<endl;
    long index2 = findSubstring(s7, "chello world");
    cout<<index2;
    return 0;
}
