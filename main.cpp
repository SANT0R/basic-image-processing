#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

class matris{
protected:

    int heigth,width;
    int *img=new int[heigth*width];

public:

    ~matris(){
        delete img;
    }

    void setheigth(int h){
        heigth=h;
    }

    void setwidth(int x){
        heigth=x;
    }

    void setimg(int i,int x){
        img[i]=x;
    }
    int getimg(int i){
        return img[i];
    }

    int getheigth(){
        return heigth;
    }

    int getwidth(){
        return width;
    }
};

class image:public matris{
private:

public:
    image(){

    }

    ~image(){
        delete img;
    }

    void sobel(){
        int sbl1[3][3]={1,0,-1,2,0,-2,1,0,-1};
        int sbl2[3][3]={-1,-2,-1,0,0,0,1,2,1};
        for(int i=0;i<heigth;i++){
            for(int j=0;j<width;j++){
                for(int k=0;k<3;k++){
                    for(int l=0;l<3;l++){
                        img[j*(i+1)]=img[j*(i+1)+k]*sbl1[k][l]+img[j*(i+1)+k]*sbl2[k][l];
                    }
                }
            }
        }
        heigth-=2;
        width-=2;
    }

    void threshold(int dgr){
        for(int i=0;i<heigth;i++){
            for(int j=0;j<width;j++){
                if(img[i]>=dgr)  { img[i]=1; }
                else    { img[i]=1; }
            }
        }
    }
};

fstream& operator>>(fstream& file,image& obj){
                    cout<<"ok";
    if(file.is_open()){
        int h,x;
        int temp=1;
        for(int k=0;k<8;k++){
            file>>temp;cout<<"ok"<<temp;
            x+=(temp*pow(2,k));
        }
        obj.setwidth(x);
        temp=1;
        for(int k=0;k<8;k++){
            file>>temp;cout<<"ok";
            h+=(temp*pow(2,k));
        }
        obj.setheigth(h);
        for(int i=0;i<obj.getheigth();i++){
            for(int j=0;j<obj.getwidth();j++){
                temp=1;
                for(int k=0;k<8;k++){
                    file>>temp;cout<<"ok";
                    x+=(temp*pow(2,k));
                }
                obj.setimg(i,x);
            }
        }
    }
    return file;
}

 fstream& operator <<(fstream& file,image& obj){
    if(file.is_open()){
        for(int i=0;i<obj.getheigth();i++){
            for(int j=0;j<obj.getwidth();j++){
                if(obj.getimg(i)==1)    { cout<<"*";file<<"*"; }
                else    { cout<<"*";file<<"-"; }
            }
        }
    }
    return file;
}

 image operator +(image &obj1,image &obj2){
    image obj3;
    obj3.setheigth(obj1.getheigth());
    obj3.setwidth(obj2.getwidth());
    for(int i=0;i<obj3.getheigth();i++){
        for(int j=0;j<obj3.getwidth();j++){
            if(obj1.getimg(i)+obj2.getimg(i)>=1)    { obj3.setimg(i,1); }
            else    {obj3.setimg(i,0); }
        }
    }
    return obj3;
}

 image operator *(image &obj1,image &obj2){
    image obj3;
    obj3.setheigth(obj1.getheigth());
    obj3.setwidth(obj2.getwidth());
    for(int i=0;i<obj3.getheigth();i++){
        for(int j=0;j<obj3.getwidth();j++){
            obj3.setimg(i,obj1.getimg(i)*obj2.getimg(i));
        }
    }
    return obj3;
}

 image operator !(image &obj1){
    image obj2;
    obj2.setheigth(obj1.getheigth());
    obj2.setwidth(obj1.getwidth());
    for(int i=0;i<obj1.getheigth();i++){
        for(int j=0;i<obj1.getwidth();j++){
            if(obj1.getimg(i)==1)    { obj2.setimg(i,0); }
            else     { obj2.setimg(i,1); }
        }
    }
    return obj2;
}

int main(){                                         cout<<"ok"<<endl;
    fstream file1,file2,file3;                      cout<<"ok"<<endl;
    file1.open("image1.txt",ios::in);   cout<<"ok"<<endl;
    file2.open("image2.txt",ios::in);   cout<<"ok"<<endl;
    file3.open("sonuc.txt",ios::out|ios::app);      cout<<"ok"<<endl;
    int temp;
    while(!file1.eof()){
       temp=file1.read(temp); cout<<temp<<endl;}
    image photo1,photo2;                          cout<<"ok"<<endl;
    file1>>photo1;                                cout<<"ok"<<endl;
    file2>>photo2;                                cout<<"ok"<<endl;
    photo1.sobel();                               cout<<"ok"<<endl;
    photo2.sobel();                               cout<<"ok"<<endl;
    photo1.threshold(100);                        cout<<"ok"<<endl;
    photo2.threshold(100);                        cout<<"ok"<<endl;
    file3<<photo1;                                cout<<"ok"<<endl;
    file3<<photo2;                                cout<<"ok"<<endl;

    return 0;
}
