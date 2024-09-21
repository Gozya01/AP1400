#ifndef Q2_H
#define Q2_H

#endif //Q2_H
#include<fstream>
#include<stdexcept>
#include<sstream>
namespace q2{
    struct Patient{
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
        int val(){
            return 3*age + 5*smokes + 2*area_q + 4*alkhol;
        }
    };
    std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return ""; // 如果字符串全是空格，返回空字符串
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, last - first + 1); // 提取非空格部分
    }

    std::vector<Patient> read_file(std::string filename){
        std::ifstream file(filename);
        if(!file.is_open()){
            throw std::runtime_error("no file");
        }
        std::string line;
        int i=0;
        std::vector<Patient>ans;
        while(getline(file,line)){
            i++;
            if(i<=2)continue;
            std::stringstream ss(line);
            std::string word;
            int j=0;
            Patient a;
            while(getline(ss,word,',')){
                j++;
                // std::cout<<word<<std::endl;
                word=trim(word);
                if(j==1){
                    a.name+=word+' ';
                }
                else if(j==2)a.name+=word;
                else if(j==3)a.age=std::stoi(word);
                else if(j==4)a.smokes=std::stoi(word);
                else if(j==5)a.area_q=std::stoi(word);
                else {
                    a.alkhol=std::stoi(word);
                }
            }
            ans.push_back(a);
        }
        return ans;
    }
    void sort(std::vector<Patient> &p){
        std::sort(p.begin(),p.end(),[](Patient& a,Patient& b){
            return a.val()>b.val();
        });
    }
}