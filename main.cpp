#include <iostream>
#include <fstream>
#include "/usr/local/include/eigen3/Eigen/Core"
#include "/usr/local/include/eigen3/Eigen/Dense"
#include "/usr/local/include/eigen3/Eigen/Eigen"
#include "cloud.h"

using namespace std;

void load_matrix(std:: string, Eigen::Matrix4f*);

int main(int argc, char *argv[])
{
    float temp=0;
    int idx;
    for(int q=0; q<4; q++)
    {
        Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
        std::stringstream sstm;
        std::string file_name;

        sstm.str("");
        sstm<<"data/transformations/SW2_sampled_SW3_sampled_"<<q<<".txt";
        file_name = sstm.str();

        load_matrix(file_name, &transform);

        pcl::PointCloud<pcl_point>::Ptr cloud_src(new pcl::PointCloud<pcl_point>);
        //load src
        pcl::PointCloud<pcl_point>::Ptr cloud_tgt(new pcl::PointCloud<pcl_point>);
        // load tgt

        //transform
        pcl::transformPointCloudWithNormals (*cloud_in, *cloud_in, transform);
        //compute LCP
        if(temp<LCP)
        {
            temp=LCP;
            idx=q;
        }
    }

    std::cout<<"good rotation is: "<<idx<<std::endl<<std::endl;
}




void load_matrix(std:: string file_name, Eigen::Matrix4f* matrix)
{
    ifstream fin;
    fin.open (file_name);
    Eigen::Matrix4f res = Eigen::Matrix4f::Identity();

    if (fin.is_open())
    {
        for (int row = 0; row < 4; row++)
            for (int col = 0; col < 4; col++)
            {
                float item = 0.0;
                fin >> item;
                res(row, col) = item;
            }
        fin.close();
    }
    *matrix=res;
}
