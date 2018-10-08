#include <bits/stdc++.h>
#include<time.h> 
using namespace std;

template <class K, class V>
class Unordered_map
{
	list< pair<K,V> > *mymap;
	long long a,b;
	long long p;
	long m;
public:
	Unordered_map(long n){
		m=n;
		mymap=new list< pair<K,V> >[m];
		initialize();
	}
	void initialize(){
		p=1000000007;
	    srand(time(0)); 
		a=rand()%p+1;
		b=rand()%p+1;
		printParam();
	}
	void insert(K k, V v){
		V flag;
		unsigned long hashKey=hashValue(k);
		if(find(k)==notExist(flag))
			mymap[hashKey].push_back(make_pair(k,v));
		else
			cout<<k<<" Key already exists\n";

	}
	void erase(K k){
		V flag;
		bool isDeleted=false;
		unsigned long hashKey=hashValue(k);		
		for(typename list< pair<K,V> > :: iterator it = mymap[hashKey].begin(); it != mymap[hashKey].end(); ++it){
			if(it->first==k){
				mymap[hashKey].erase(it);
				isDeleted=true;
				break;
			}
		}			
		if(!isDeleted)
			cout<<"Cant delete: "<<k<<" not exists.\n";
	}
	V find(K k){
		unsigned long hashKey=hashValue(k);
		V flag;
		if(mymap[hashKey].empty()){
			return notExist(flag);	
		}
		else{
			for(typename list< pair<K,V> > :: iterator it = mymap[hashKey].begin(); it != mymap[hashKey].end(); ++it) 
				if(it->first==k)
					return it->second;
			return notExist(flag);
		}
		
	}
	unsigned long hashValue(long long key){
		unsigned long temp=((a*key+b)%p)%m;
		return temp;
	}
	unsigned long hashValue(string key){
	  	unsigned long hash = 5381;
        int c;
        for(long i=0;i<key.size();i++)
            hash=(((hash << 5)+ hash) + key[i])%m; // hash * 33 + c
        return hash;
	}

	V notExist(string s){
		return "";
	}
	V notExist(long long s){
		return -1;
	}
	void printParam(){
		cout<<"m="<<m<<" ";
		cout<<"a="<<a<<" ";
		cout<<"b="<<b<<" ";
		cout<<"p="<<p<<" \n";
	}

	void printHash(){
		for(long i=0;i<m;i++){
			if(mymap[i].size()>0)
				cout<<i<<" "<<mymap[i].size()<<endl;
		}
	}

};



int main(int argc, char const *argv[])

{	


	Unordered_map<long long,long> map1(10);
	cout<<"Value "<<map1.find(24)<<endl;
	for(long i=0;i<80;i++){
		long y=rand()%1000007+1;
		map1.insert(y,i);
		// cout<<"key "<<y<<endl;
		// cout<<"Value "<<map1.find(y)<<endl;
	}
	map1.printHash();
	cout<<"Value "<<map1.find(4967)<<endl;
	// map1.insert(24,111);
	// map1.insert(24,1112);
	map1.erase(4967);
	cout<<"Value "<<map1.find(4967)<<endl;
	map1.printHash();
	
	Unordered_map<string,long> map3(10);
	map3.insert("anuj1",10);
	map3.insert("canada",2);
	map3.insert("china",3);
	map3.insert("adsadasdasdsa",4);
	map3.insert("test",5);
	map3.insert("hahahaha",6);
	map3.insert("anujanujanujanujanuj",7);
	map3.insert("testimonial",8);
	map3.insert("ponting",9);
	map3.insert("anuj",120);
	map3.insert("anuj",122);
	map3.insert("anuj321",101);
	map3.printHash();
	cout<<map3.find("anujanujanujanujanuj")<<endl;
	map3.erase("anujanujanujanujanuj");
	cout<<map3.find("anujanujanujanujanuj")<<endl;
	map3.printHash();

	Unordered_map<string,string> map4(10);
	map4.insert("canada1","canada11");
	map4.insert("canada2","canada22");
	map4.insert("canada3","canada33");
	map4.insert("canada4","canada44");
	map4.insert("canada5","canada55");
	map4.insert("canada6","canada66");
	map4.insert("canada3","canada77");
	cout<<map4.find("canada1");
	cout<<map4.find("canada2");
	cout<<map4.find("canada3");
	cout<<map4.find("canada4");
	cout<<map4.find("canada5");
	cout<<map4.find("canada6");
	cout<<endl;
	map4.printHash();
	cout<<map4.find("canada3")<<endl;
	map4.erase("canada3");
	cout<<map4.find("canada3")<<endl;
	map4.printHash();
	return 0;
}