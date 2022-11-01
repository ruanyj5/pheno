#include<thread>
#include<iostream>
#include<memory>
#include<malloc.h>
#include<stdio.h>
#include <gdal_priv.h>
#include "gdal.h"
#include "mpfit.h"
#include "omp.h"
//#include <omp.h>

//coder matlab
#include "NDVI46to365.h"
#include "NDVI46to365_terminate.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"
#include <cstring>
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "NDVI46to365_types.h"


using namespace std;

GDALDataset* read_dataset(const char* pPath)
{
    //注册文件格式//
    GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");

    GDALDataset* imageDataset; // pre
    imageDataset = (GDALDataset *)GDALOpen(pPath, GA_ReadOnly);
    if (imageDataset == NULL /* no image data*/)
    {
        printf("文件无法打开！\n");
    }

    return imageDataset;
}

void CreateRasterFile(GDALDataset *poDataset, const char* pszRasterFile, const char *pszFormat)
{
    // support chinese language
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    GDALAllRegister();//注册文件格式//

    GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
    if (poDriver == NULL)
    {
        //printf("the format of image can't CreateRasterFile \n", pszFormat);
        printf("the format of image can't CreateRasterFile \n");
        return;
    }

    //CreateRasterFile
    int width = poDataset->GetRasterXSize();
    int height = poDataset->GetRasterYSize();
    GDALDataset *poDS = poDriver->Create(pszRasterFile, width, height, 6, GDT_Int16, NULL);

    // add geoinfomation
    double geoTransform[6];
    if (poDataset->GetGeoTransform(geoTransform) == CE_None)
        poDS->SetGeoTransform(geoTransform);
    poDS->SetProjection(poDataset->GetProjectionRef());

    // GDALClose
    GDALClose((GDALDatasetH)poDS);
}

void UpdateRasterFile(const char *pszRasterFile, short int *imageData)
{
    //support chinese language
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    GDALAllRegister();

    //open and update image
    GDALDataset *poDataset = (GDALDataset*)GDALOpen(pszRasterFile, GA_Update);
    if (poDataset == NULL)
    {
        //printf("error for update image\n", pszRasterFile);
        printf("error for update image\n");
        return;
    }
    // get image rows and cols
    int width = poDataset->GetRasterXSize();
    int height = poDataset->GetRasterYSize();
    int Bands = poDataset->GetRasterCount();

    // update image band
    CPLErr err = poDataset->RasterIO(GF_Write, 0, 0, width, height, imageData, width, height, GDT_Int16,Bands,NULL, 0,0,0);
    if (err == CE_Failure)
    {
        std::cout << "error for update image band" << std::endl;
        return;
    }

    //GDALClose
    GDALClose((GDALDatasetH)poDataset);
}
// mpfit.cpp
//////////////////////////////////////////

struct vars_struct {
    double *x;
    double *y;
    double *ey;
};

// fit
int func(int m, int n, double *p, double *dy, double **dvec, void *vars)
{
    int i;
    struct vars_struct *v = (struct vars_struct *) vars;
    double *x, *y, *ey, pred_f;

    x = v->x;
    y = v->y;
    ey = v->ey;

    for (i = 0; i<m; i++) {

        //pred_f = p[2] / (1 + exp(p[0] + p[1] * x[i])) + p[3];
        pred_f = p[0] + (p[1]-p[0])/ (1 + exp((p[2] - x[i]) * p[3]));
        dy[i] = (y[i]-pred_f)/ey[i];
    }

    return 0;
}

vector<double> datefunc(vector<double> x,vector<double> y, int num)
{
    double ey[num];
    vector<double> temp;
    double* x1=new double[x.size()];
    double* y1=new double[y.size()];

    for (int j = 0; j < x.size(); ++j) {
         x1[j]=x[j];
         y1[j]=y[j];
    }

    //double temp[4];

    double p[] = { 1.0, 1.0, 1.0 ,1.0 };        /* Initial conditions */
    double perror[4];		       /* Returned parameter errors */
    struct vars_struct v;
    int status;
    mp_result result;
    memset(&result, 0, sizeof(result));          /* Zero results structure */
    result.xerror = perror;

    for (int i = 0; i<num; i++)
        ey[i] = 0.001;       /* Data errors */

    v.x = x1;
    v.y = y1;
    v.ey = ey;

    /* Call fitting function for 365 data points and 4 parameters */
    status = mpfit(func, num, 4, p, 0, 0, (void *)&v, &result);

    temp.push_back(p[0]); //a
    temp.push_back(p[1]); //b
    temp.push_back(p[2]); //c
    temp.push_back(p[3]); //d

    delete[] x1;
    delete[] y1;

//    temp[0]=p[0]; //a
    //   temp[1]=p[1]; //b
//    temp[2]=p[2]; //c
//    temp[3]=p[3]; //d

    //printf("*** testquadfit status = %d\n", status);
    //printresult(p, pactual, &result);

    return temp;
}


////
//static omp_lock_t lock;

int main(int argc, char *argv[]) {
    //get input para and out para
    /* verify command line usage */
    if(argc!=3) {
        std::cout << "para input error" << std::endl;
        exit(1);
    }

    char* InFile=argv[1];
    char* outFile=argv[2];



    // start time
    auto start = chrono::system_clock::now();

    // gadl read geotiff image
    //string InFile = "/home/yongjian/Desktop/yongjian/clion-2019.3.3/open_MP_v1/LC08_016029.MOD09A1_2017001.sur_refl_b01_b02_QC_ESTARFM_NDVI_8DSGF2.tif"; // image path
    //GDALDataset* GDALRaster_NDVI46 = read_dataset(InFile.c_str());// image path
    GDALDataset* GDALRaster_NDVI46 = read_dataset(InFile);// image path

    // get image infomation
    GDALDataType Datatype = GDALRaster_NDVI46->GetRasterBand(1)->GetRasterDataType();  //GetRasterBand()是从1开始计数

    int nWidth = GDALRaster_NDVI46->GetRasterXSize();
    int nHeight = GDALRaster_NDVI46->GetRasterYSize();
    int nBands = GDALRaster_NDVI46->GetRasterCount(); //注意此处不是getrasterband;

    cout << "dataTypeNDVI : " << Datatype << endl; // GDT_UInt16 = 2   GDT_Int16=3
    cout << "nBands : " << nBands << endl;
    cout << "nWidth : " << nWidth << endl;
    cout << "nHeight : " << nHeight << endl;

    //读取影像：RasterIO
    // read image
    short int * pImageData = (short int *)malloc(sizeof(short int)*nWidth*nHeight*nBands);
    GDALRaster_NDVI46->RasterIO(GF_Read, 0, 0, nWidth, nHeight, pImageData, nWidth, nHeight,Datatype,nBands,NULL, 0,0,0);

    // int16  data convert float

    // rows = 行   cols= 列  int rows=nHeight;  int cols=nWidth;  and convert 3D to 2D =46*nWidth*nHeight
    int64_t rows=nBands;
    int64_t cols=nWidth*nHeight;

    // initialize  6 array for  phen result
    double* Date1=new double[cols];
    double* Date2=new double[cols];
    double* Date3=new double[cols];
    double* Date4=new double[cols];
    double* Date5=new double[cols];
    double* Date6=new double[cols];

    for (int64_t kk= 0; kk < cols; ++kk) {
        Date1[kk]=0.0;
        Date2[kk]=0.0;
        Date3[kk]=0.0;
        Date4[kk]=0.0;
        Date5[kk]=0.0;
        Date6[kk]=0.0;
    }

    //cout << "ok!  start do" << endl;
    // for circulation  array=46* nWidth*nHeight
    //float * TEMP46NDVI = (float *)malloc(sizeof(float)*46);
    double TEMP46NDVI [46];
    double TEMP46NDVI_flipud [46];
    double EXT09Data[545];
    double EXT09DMSK2[545];
    double LocMaxima;
    //double MOD09DEVI365[365];
    vector<double > x;
    vector<double > y;
    vector<double> param;
    double paramfit[4];
    double pred_f[545];

    // get value for time and x
    double time[545];
    for (int I_index = 0; I_index<545; I_index++) {
        time[I_index]=-89+I_index;
    }

    //float TEMP46NDVI [46]; // get cols 46 NDVI
    int64_t i,j;
    int k,l,m,n;

    // initialize opm lock
    //omp_init_lock(&lock);
    int num_threads=omp_get_num_procs();
    cout << "ok! start do with num_threads=" <<num_threads<< endl;

    #pragma omp parallel for num_threads(num_threads) private(j,i,k,l,m,n,TEMP46NDVI,TEMP46NDVI_flipud,EXT09Data, EXT09DMSK2, LocMaxima,x,y,param,paramfit,pred_f)
    for ( j = 0; j < cols; ++j) {

        //omp_set_lock(&lock);
        //#pragma omp atomic
        for ( i = 0; i < rows; ++i) { // rows=46,
            TEMP46NDVI[i] = (float)pImageData[i * cols + j]/10000.0;
        }

        // flip up-down  NDVI
        for (n = 0; n <46 ; ++n) {
            TEMP46NDVI_flipud[n]=TEMP46NDVI[45-n];
        }

        //NDVI46 to 365
        NDVI46to365(TEMP46NDVI_flipud, EXT09Data, EXT09DMSK2, &LocMaxima);

        // rmove nan for parafit
        for (k = 0; k <545 ; ++k) {
            if (isnan(EXT09Data[k])==0){
                x.push_back(time[k]);
                y.push_back(EXT09Data[k]);
            }
        }

        // fit time series
        //#pragma omp atomic
        param=datefunc(x,y,x.size());

        for (l = 0; l<545; l++) {
            pred_f[l] = param[0] + (param[1] - param[0]) / (1 + exp((param[2] - time[l]) * param[3]));
        }


        for (m = 0; m <4 ; ++m) {
            paramfit[m]=param[m];
        }


        if (LocMaxima >1){
            phen_6method(pred_f, EXT09DMSK2, paramfit, &Date1[j], &Date2[j], &Date3[j],&Date4[j], &Date5[j], &Date6[j]);

        }

        y.clear();
        x.clear();
        param.clear();

        // unset_lock
        //omp_unset_lock(&lock);
    }


    //free destory opm lock
    //omp_destroy_lock(&lock);


    // initialize output result array
    short int * SOS6method = (short int *)malloc(sizeof(short int)*nWidth*nHeight*6);

//    #pragma omp parallel for private(j)
    for (int j=0;j<cols;j++) {
        if ((short int)Date1[j]!=0){
            SOS6method[0*cols+j]=366-(short int)Date1[j];
            SOS6method[1*cols+j]=366-(short int)Date2[j];
            SOS6method[2*cols+j]=366-(short int)Date3[j];
            SOS6method[3*cols+j]=366-(short int)Date4[j];
            SOS6method[4*cols+j]=366-(short int)Date5[j];
            SOS6method[5*cols+j]=366-(short int)Date6[j];
        }
        else{
            SOS6method[0*cols+j]=365;
            SOS6method[1*cols+j]=365;
            SOS6method[2*cols+j]=365;
            SOS6method[3*cols+j]=365;
            SOS6method[4*cols+j]=365;
            SOS6method[5*cols+j]=365;
        }
    }


   // output image   output image path
    //string outFile = "/home/yongjian/Desktop/yongjian/clion-2019.3.3/open_MP_v1/LC08_016029.MOD09A1_2017001.sur_refl_b01_b02_QC_ESTARFM_NDVI_8DSGF_SOS6method_parfor.tif"; // image path

    // output  reference_data
    //GDALDataset* reference_data = read_dataset(InFile.c_str());

    GDALDataset* reference_data = read_dataset(InFile);

    //  CreateRasterFile and UpdateRasterFile
    CreateRasterFile(reference_data, outFile, "GTiff");// CreateRasterFile
    UpdateRasterFile(outFile, SOS6method);// overwrite data

    // free Memory
    free(pImageData);
    free(SOS6method);
    delete [] Date1;
    delete [] Date2;
    delete [] Date3;
    delete [] Date4;
    delete [] Date5;
    delete [] Date6;
    //free(MOD098DNDVI);
    //free(TEMP46NDVI);
    //free(TEMP);

    // end  time
    auto stop = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "time used with parallel:" << duration.count() <<"ms"<< endl;

    return 0;
}