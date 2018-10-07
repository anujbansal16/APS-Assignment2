#include<bits/stdc++.h>
using namespace std;
typedef struct stringBuilderStruct
{
    const char *s;
    struct stringBuilderStruct *tail;
    struct stringBuilderStruct *next;
    struct stringBuilderStruct *rec;
    int count;
} *stringBuilder;

stringBuilder stringInitialze(const char *c){
    stringBuilder newStringBuilder=(stringBuilder)malloc(sizeof(struct stringBuilderStruct));
    newStringBuilder->s=c;
    newStringBuilder->next=NULL;
    newStringBuilder->tail=newStringBuilder;
    newStringBuilder->rec=NULL;
    newStringBuilder->count=1;
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

void printStringBuilder(stringBuilder sb){
    stringBuilder temp=sb;
    stringBuilder temp2=sb;
    bool flag=false;
    int count=1;
    long k=0;
    memset(buffer,'\0',sizeof(buffer));
    while(temp!=NULL){        
        cout<<temp->s;
        for(long i=0;i<strlen(temp->s);i++)
            buffer[k++]=(temp->s)[i];
        if(  temp->count!=1 && !(flag&&count==1)){
            temp=temp->rec;
            flag=true;
            if(count==1)
                count=temp->count;
            else
                count--;
            if(count!=1)
                continue;
        }
        if(count==1 && flag){
            flag=false;
            count=1;
        }
        temp=temp->next;
    }
    cout<<"\n";
}

stringBuilder stringAppend(stringBuilder a, stringBuilder b){
    a->tail->next=b;
    a->tail=b->tail;
    if((a->tail->next)==a){
        a->tail->rec=a;
        a->tail->count=2*(a->tail->count);
        cout<<"yes "<<a->tail->count<<(a->tail->rec->count)<<endl;
        a->tail->next=NULL;
    }
    else if((a->tail->next)==b){
        a->tail->rec=b;
        a->tail->count=2*(a->tail->count);
        cout<<"yes2 "<<a->tail->count<<(a->tail->rec->count)<<endl;
        a->tail->next=NULL;
    }
    return a;
}

long findSubstring(stringBuilder a, const char * pat){
    cout<<"In findSubstring\n";
    printStringBuilder(a);
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
    stringBuilder s2=stringInitialze("badsadab");
    stringBuilder s3=stringInitialze("cc");
    stringBuilder s4=stringInitialze("dd");
    stringBuilder s5=stringAppend(s1,s1);

    // stringBuilder s15=stringAppend(s1,s2);
    // printStringBuilder(s15);
    // stringBuilder s16=stringAppend(s1,s2);
    // printStringBuilder(s16);

    printStringBuilder(s1);
    stringBuilder s15=stringAppend(s2,s2);
    printStringBuilder(s15);
    stringBuilder s16=stringAppend(s1,s2);
    printStringBuilder(s16);
    long index2 = findSubstring(s1, "dab");
    cout<<index2;
    // printStringBuilder(s3);
    // printStringBuilder(s4);
    // printStringBuilder(s5);
    // stringBuilder s6=stringAppend(s5,s1);
    // printStringBuilder(s6);
    // stringBuilder s11=stringAppend(s1,s2);
    // printStringBuilder(s11);
    // stringBuilder s9=stringAppend(s3,s4);
    // printStringBuilder(s9);
    // stringBuilder s10=stringAppend(s11,s9);
    // printStringBuilder(s10);
    // stringBuilder s8=stringAppend(s11,s1);
    // printStringBuilder(s8);
    return 0;
}
