#include<fstream>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main(){
		string t;
		vector<char> v;
		if (FILE *fp = fopen("token.bin", "rb"))
		{
			char buf[1024];
			while (size_t len = fread(buf, 1, sizeof(buf), fp))
				v.insert(v.end(), buf, buf + len);
			fclose(fp);
		}
		cout<<v.size()<<endl;
		for(char i : v)
			cout<<i<<" ";
}