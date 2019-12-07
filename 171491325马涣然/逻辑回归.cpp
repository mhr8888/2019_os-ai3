#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

template <typename DataType>
double sigmoid(DataType z) {
    return 1.0/(1+exp((-1)*z));
}

template <typename DataType, typename WeightType>
double getMatResult(typename::std::vector<DataType> &data, typename::std::vector<WeightType> &weights) {
    double result=0.0;
    for(size_t i=0;i<data.size();++i) {
        result+=data.at(i)*weights.at(i);
    }
    return result;
}

template <typename DataType>
void DisplayData(typename::std::vector<std::vector<DataType> > &vv) {
    std::cout<<"the number of data: "<<vv.size()<<std::endl;
    for(size_t i=0;i<vv.size();++i) {
        for(typename::std::vector<DataType>::iterator it=vv[i].begin();it!=vv[i].end();++it) {
            std::cout<<*it<<" ";
        }
        std::cout<<std::endl;
    }
}

template <typename DataType, typename WeightType>
double CostFun(typename::std::vector<std::vector<DataType> > &vv, typename::std::vector<WeightType> &v_weights) {
    double J=0.0;
    typename::std::vector<DataType> v_x;
    for(size_t i=0;i<vv.size();++i) {
        v_x.clear();
        v_x.push_back(vv[i][0]);
        v_x.push_back(vv[i][1]);
        v_x.push_back(vv[i][2]);
        double z=getMatResult(v_x,v_weights);
        J=J+vv[i][3]*log2(sigmoid(z))+(1-vv[i][3])*log2(1-sigmoid(z));
    }
    J=-J/vv.size();
    return J;
}

int main() {
    std::ifstream infile_feat("train.data");
    std::string feature;
    float feat_onePoint;
    std::vector<float> lines;
    std::vector<double> v_weights;
    std::vector<std::vector<float> > lines_feat;
    lines_feat.clear();
    v_weights.clear();
    for(size_t i=0;i<3;++i) {
        v_weights.push_back(1.0);
    }
    while(!infile_feat.eof()) {
        getline(infile_feat, feature);
        if(feature.empty())
            break;
        std::stringstream stringin(feature);
        lines.clear();
        lines.push_back(1.0);
        while(stringin >> feat_onePoint) {
            lines.push_back(feat_onePoint);
        }
        lines_feat.push_back(lines);
    }
    infile_feat.close();
    std::cout<<"display train data: "<<std::endl;
    DisplayData(lines_feat);
    double res=CostFun(lines_feat, v_weights);
    std::cout<<"the value of cost function: "<<res<<std::endl;
    std::vector<double> v_x;
    while(true) {
        double grad0=0.0,grad1=0.0,grad2=0.0;
        for(size_t i=0;i<lines_feat.size();++i) {
            v_x.clear();
            v_x.push_back(lines_feat[i][0]);
            v_x.push_back(lines_feat[i][1]);
            v_x.push_back(lines_feat[i][2]);
            grad0+=(lines_feat[i][3]-sigmoid(getMatResult(v_x,v_weights)))*lines_feat[i][0];
            grad1+=(lines_feat[i][3]-sigmoid(getMatResult(v_x,v_weights)))*lines_feat[i][1];
            grad2+=(lines_feat[i][3]-sigmoid(getMatResult(v_x,v_weights)))*lines_feat[i][2];
        }
        grad0=grad0/lines_feat.size();
        grad1=grad1/lines_feat.size();
        grad2=grad2/lines_feat.size();

        //0.03??????????
        v_weights[0]=v_weights[0]+0.03*grad0;
        v_weights[1]=v_weights[1]+0.03*grad1;
        v_weights[2]=v_weights[2]+0.03*grad2;

        double res_new;
        res_new=CostFun(lines_feat,v_weights);
        if(std::abs(res_new-res)<0.0000000001)
            break;
        res=res_new;
    }
    for(size_t i=0;i<3;++i) {
        std::cout<<v_weights.at(i)<<" ";
    }
    std::cout<<std::endl;
    lines_feat.clear();
    infile_feat.open("test.data");
    while(!infile_feat.eof()) {
        getline(infile_feat, feature);
        if(feature.empty())
            break;
        std::stringstream stringin(feature);
        lines.clear();
        lines.push_back(1.0);
        while(stringin >> feat_onePoint) {
            lines.push_back(feat_onePoint);
        }
        lines_feat.push_back(lines);
    }
    infile_feat.close();
    std::cout<<"display test data: "<<std::endl;
    DisplayData(lines_feat);
    for(size_t i=0;i<lines_feat.size();++i) {
        v_x.clear();
        v_x.push_back(lines_feat[i][0]);
        v_x.push_back(lines_feat[i][1]);
        v_x.push_back(lines_feat[i][2]);
        res=getMatResult(v_x,v_weights);
        double lable=sigmoid(res);
        for(size_t j=0;j<4;++j) {
            std::cout<<lines_feat[i][j]<<" ";
        }
        if(lable>0.5)
            std::cout<<" 1"<<std::endl;
        else
            std::cout<<" 0"<<std::endl;
    }
    return 0;
}
