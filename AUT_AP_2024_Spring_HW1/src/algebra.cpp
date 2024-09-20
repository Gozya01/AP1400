#include "algebra.h"
namespace algebra{
    template<typename T>
    MATRIX<T> create_matrix(
        std::size_t rows, std::size_t columns, 
        std::optional<MatrixType> type,
        std::optional<T> lowerBound,
        std::optional<T> upperBound){
            if(rows==0||columns==0){
                throw std::runtime_error("rows or columns must be not zero.");
            }
            MATRIX<T> matrix(rows,std::vector<T>(columns));
            if(type==MatrixType::Zeros){
                return matrix;
            }
            else if(type==MatrixType::Ones){
                for(std::size_t i=0;i<rows;++i)for(std::size_t j=0;j<rows;++j)matrix[i][j]=1;
                return matrix;
            }
            else if(type==MatrixType::Identity){
                if(rows!=columns){
                    throw std::runtime_error("error!");
                }
                else {
                    for(size_t i=0;i<rows;++i)matrix[i][i]=1;
                    return matrix;
                }
            }
            else if(type==MatrixType::Random){
                if(!lowerBound.has_value()||!upperBound.has_value()){
                    throw std::runtime_error("no bound!");
                }
                else {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    double lower=lowerBound.value_or(0.0);
                    double upper=upperBound.value_or(1.0);
                    if(lower>upper){
                        throw std::logic_error("min cannot be greater than max");
                    }
                    std::uniform_real_distribution<> dis(lower,upper);
                    for(std::size_t i=0;i<rows;++i)
                        for(std::size_t j=0;j<rows;++j)
                            matrix[i][j]=dis(gen);
                }
            }
            else {
                throw "no match type!";
                return matrix;
            }
            return matrix;
    }
    template MATRIX<int> create_matrix<int>(std::size_t, std::size_t,  std::optional<MatrixType>, std::optional<int>, std::optional<int>);
    template MATRIX<double> create_matrix<double>(std::size_t, std::size_t,  std::optional<MatrixType>, std::optional<double>, std::optional<double>);
    template MATRIX<float> create_matrix<float>(std::size_t, std::size_t,  std::optional<MatrixType>, std::optional<float>, std::optional<float>);

    template<typename T>
    void display(const MATRIX<T>& matrix){
        int n=matrix.size(),m=matrix[0].size();
        for(int i=0;i<n;++i){
            std::cout<<"|";
            for(int j=0;j<m;++j){
                std::cout<<std::format("{:^{}.{}f}|",1.0*matrix[i][j],7,3);
            }
            std::cout<<std::endl;
        }
    }
    template void display<int>(const MATRIX<int>&);
    template void display<double>(const MATRIX<double>&);

    template<typename T>
    MATRIX<T> sum_sub(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB, std::optional<std::string> operation){
        if (matrixA.empty() && matrixB.empty())
		{
			return {};
		}
        if(matrixA.size()==0||matrixA[0].size()==0||matrixB.size()==0||matrixB[0].size()==0){
            throw std::runtime_error("rows or colums must not be zero.");
        }
        std::string opt=operation.value_or("sum");
        // std::cout<<operation;
        MATRIX<T> ans(matrixA.size(),std::vector<T>(matrixA[0].size()));
        if(matrixA.size()!=matrixB.size()||matrixA[0].size()!=matrixB[0].size()){
            throw "size not equal!";
            return ans;
        }
        else {
            int n=matrixA.size(),m=matrixA[0].size();
            if(opt=="sub"){
                for(int i=0;i<n;++i){
                    for(int j=0;j<m;++j){
                        ans[i][j]=matrixA[i][j]-matrixB[i][j];
                    }
                }
            }
            else {
                for(int i=0;i<n;++i){
                    for(int j=0;j<m;++j){
                        ans[i][j]=matrixA[i][j]+matrixB[i][j];
                    }
                }
            }
            return ans;
        }
        return ans;
    }
    template MATRIX<int> sum_sub(const MATRIX<int>&,const MATRIX<int>&,std::optional<std::string>);
    template MATRIX<double> sum_sub(const MATRIX<double>&,const MATRIX<double>&,std::optional<std::string>);

    template<typename T>
    MATRIX<T> multiply(const MATRIX<T>& matrix, const T scalar){
        if (matrix.empty())
		{
			return {};
		}
        if(matrix.size()==0||matrix[0].size()==0){
            throw std::runtime_error("rows or colums must not be zero.");
        }
        int n=matrix.size();
        int m=matrix[0].size();
        MATRIX<T> ans(n,std::vector<T>(m,0));
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                ans[i][j]=matrix[i][j]*scalar;
            }
        }
        return ans;
    }
    template MATRIX<int> multiply(const MATRIX<int>&,const int);
    template MATRIX<double> multiply(const MATRIX<double>&,const double);

    template<typename T>
    MATRIX<T> multiply(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB){
        // if (matrixA.empty() || matrixB.empty())
		// {
        //     return {};
		// }
        if(matrixA.size()==0||matrixA[0].size()==0||matrixB.size()==0||matrixB[0].size()==0){
            throw std::runtime_error("rows or colums must not be zero.");
        }
        int n1=matrixA.size();
        int m=matrixA[0].size();
        int n2=matrixB[0].size();
        int m2=matrixB.size();
        if(m!=m2){
            throw "not match!";
        }
        MATRIX<T> ans(n1,std::vector<T>(n2,0));
        for(int k=0;k<m;++k){
            for(int i=0;i<n1;++i){
                for(int j=0;j<n2;++j){
                    ans[i][j]+=matrixA[i][k]*matrixB[k][j];
                }
            }
        }
        return ans;
    }
    template MATRIX<double> multiply(const MATRIX<double>&,const MATRIX<double>&);
    template MATRIX<int> multiply(const MATRIX<int>&,const MATRIX<int>&);

    template<typename T>
    MATRIX<T> hadamard_product(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB){
        if (matrixA.empty() || matrixB.empty())
		{
            return {};
			// return Matrix<T>{};
		}
        if(matrixA.size()==0||matrixA[0].size()==0||matrixB.size()==0||matrixB[0].size()==0){
            throw std::runtime_error("rows or colums must not be zero.");
        }
        int n1=matrixA.size();
        int m=matrixA[0].size();
        int n2=matrixB.size();
        int m2=matrixB[0].size();
        if(m!=m2||n1!=n2){
            throw "not match!";
        }
        MATRIX<T> ans(n1,std::vector<T>(m,0));
        for(int i=0;i<n1;++i){
            for(int j=0;j<m;++j){
                ans[i][j]=matrixA[i][j]*matrixB[i][j];
            }
        }
        return ans;
    }
    template MATRIX<int> hadamard_product(const MATRIX<int>&,const MATRIX<int>&);
    template MATRIX<double> hadamard_product(const MATRIX<double>&,const MATRIX<double>&);

    template<typename T>
    MATRIX<T> transpose(const MATRIX<T>& matrix){
        if(matrix.size()==0)return matrix;
        int n=matrix[0].size();
        int m=matrix.size();
        MATRIX ans(n,std::vector<T>(m));
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                ans[i][j]=matrix[j][i];
            }
        }
        return ans;
    }
    template MATRIX<int> transpose(const MATRIX<int>&);
    template MATRIX<double> transpose(const MATRIX<double>&);

    template<typename T>
    T trace(const MATRIX<T>& matrix){
        if(matrix.size()==0||matrix[0].size()==0){
            throw std::runtime_error("rows or colums must not be zero.");
        }
        T sum=0;
        int n=matrix.size();
        int m=matrix[0].size();
        if(n!=m){
            throw "rows colums not match";
        }
        for(int i=0;i<n;++i)sum+=matrix[i][i];
        return sum;
    }
    template int trace(const MATRIX<int>&);
    template double trace(const MATRIX<double>&);

    template<typename T>
    double determinant(const MATRIX<T>& matrix){
        if(matrix.size()==0||matrix[0].size()==0){
            throw std::runtime_error("rows or colums must not be zero.");
        }
        int n=matrix.size();
        int m=matrix[0].size();
        if(n!=m){
            throw "rows colums not match";
        }
        MATRIX<T> a(n,std::vector<T>(m));
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)a[i][j]=matrix[i][j];
        const double ex=1e-6;
        double ans=1;
        for(int i=0;i<m;++i){
            int z=-1;
            for(int j=i;j<m;++j){
                if(abs(a[j][i])>ex){z=j;break;}
            }
            if(z==-1){ans=0;continue;}
            if(z!=i){
                for(int j=0;j<m;++j)std::swap(a[i][j],a[z][j]);
            }
            for(int j=i+1;j<m;++j){
                double f=a[j][i]/a[i][i];
                for(int k=i;k<m;++k){
                    a[j][k]-=f*a[i][k];
                }
            }
            ans*=a[i][i];
        }
        return ans;
    }
    template double determinant(const MATRIX<int>&);
    template double determinant(const MATRIX<double>&);

    template<typename T>
    MATRIX<double> inverse(const MATRIX<T>& matrix){
        if(matrix.size()==0||matrix[0].size()==0){
            throw std::runtime_error("rows or colums must not be zero.");
        }
        int n=matrix.size();
        int m=matrix[0].size();
        if(n!=m){
            throw std::runtime_error("not match");
        }
        MATRIX<double> ans=create_matrix<double>(matrix.size(),matrix.size(),MatrixType::Identity);
        MATRIX<double> tmp(n,std::vector<double>(m));
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j)tmp[i][j]=matrix[i][j];
        }
        const double ex=1e-6;
        for(int i=0;i<n;++i){
            double x=tmp[i][i];
            if(abs(x)<ex){
                throw std::runtime_error("zero!");
            }
            for(int j=0;j<n;++j)tmp[i][j]/=x,ans[i][j]/=x;
            for(int j=0;j<n;++j){
                if(i!=j){
                    double f=tmp[j][i];
                    for(int k=0;k<m;++k){
                        tmp[j][k]-=f*tmp[i][k];
                        ans[j][k]-=f*ans[i][k];
                    }
                }
            }
        }
        return ans;
    }
    template MATRIX<double> inverse(const MATRIX<double>&);
    template MATRIX<double> inverse(const MATRIX<int>&);

}