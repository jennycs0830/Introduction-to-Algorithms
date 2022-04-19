#include<iostream>
#include<cstring>
#include<fstream>
#include<map>
#include<list>
#include<vector>
using namespace std;
class node{
    public:
        int row,column,value;
};
class matrix{
    public:
        int row,column;
        list <node*> temp;
};
int main(){
    ifstream infile;
    infile.open("input.txt");
    ofstream output("output.txt");
    string buffer;
    map<string,matrix*> m;

    while(infile>>buffer){
        string MatrixName;
        if(buffer=="Matrix"){
            infile >> MatrixName;
            m[MatrixName]=new matrix;
        }
        else if(buffer=="Init"){
            int Row,Column;
            infile >> MatrixName >> Row >> Column;
            m[MatrixName]->row=Row;
            m[MatrixName]->column=Column;
        }
        else if(buffer=="Assign"){
            int Row,Column,Value;
            infile >> MatrixName >> Row >> Column >> Value;
            node* n=new node;
            n->row=Row;
            n->column=Column;
            n->value=Value;
            m[MatrixName]->temp.push_back(n);
        }
        else if(buffer=="Delete"){
            infile >> MatrixName;
            for(auto s:m[MatrixName]->temp){
                delete s;
            }
            delete m[MatrixName];
        }
        else if(buffer=="Mult"){
            string MatrixName2,MatrixName3;
            infile >> MatrixName >> MatrixName2 >> MatrixName3;
            map<pair<int,int>,int> cur;//<<row,column>,value>
            map<pair<int,int>,int> ans;

            for(auto s:m[MatrixName]->temp){
                cur[make_pair(s->row,s->column)]=s->value;
            }//將matrix1的value以<row,column>為key存進map

            for(auto s:cur){
                for(auto i:m[MatrixName2]->temp){
                    if(s.first.second==i->row)
                        ans[make_pair(s.first.first,i->column)]+=s.second*i->value;
                }
            }

            for(auto s:ans){
                node*n=new node;
                n->row=s.first.first;
                n->column=s.first.second;
                n->value=s.second;
                if(n->value==0)
                    delete n;
                else
                    m[MatrixName3]->temp.push_back(n);
            }
        }
        else if(buffer=="Add"){
            string MatrixName2,MatrixName3;
            infile>>MatrixName>>MatrixName2>>MatrixName3;
            map<pair<int,int>,int> cur2;
            map<pair<int,int>,int>::iterator i;
    
            for(auto s:m[MatrixName]->temp){
                cur2[make_pair(s->row,s->column)]=s->value;
            }

            for(auto s:m[MatrixName2]->temp){
                if((i=cur2.find(make_pair(s->row,s->column)))!=cur2.end()){
                    cur2[make_pair(s->row,s->column)]+=s->value;
                }
                else
                    cur2[make_pair(s->row,s->column)]=s->value;
            }

            for(auto s:cur2){
                node*n=new node;
                n->row=s.first.first;
                n->column=s.first.second;
                n->value=s.second;
                if(n->value==0)
                    delete n;
                else
                    m[MatrixName3]->temp.push_back(n);
            }
        }
        else if(buffer=="Print"){
            string MatrixName4;
            infile>>MatrixName4;
            int a = 0;
            for(auto s : m[MatrixName4]->temp){
                if(!a++){
                    output << "(" << s->row << " " << s->column << " " << s->value << ")";
                }
                else
				    output << " " << "(" << s->row << " " << s->column << " " << s->value << ")";
			}
            output << "\n";
        }
    }
    infile.close();
    output.close();
    return 0;
}