#include <iostream>

using namespace std;

class ComplexNumber{
    protected:
        float re;
        float img;

    public:
        ComplexNumber()
        :re(0),
         img(0)
         {}

        ComplexNumber(const float a, const float b)
        :re(a),
         img(b)
         {}

        ComplexNumber(const ComplexNumber& number){
            cout<<"In copy constructor"<<endl;
            re=number.img;
            img=number.re;
        }

        ComplexNumber& operator=(const ComplexNumber& number){
            cout<<"In copy assignment operator"<<endl;
            re=number.re;
            img=-number.img;
            return *this;
        }

        float getRe(){
            return re;
        }

        float getImg(){
            return img;
        }

        void setRe(float a){
            re=a;
        }

        void setImg(float b){
            img=b;
        }
};

class Uncopyable {
    protected: 
        Uncopyable() {} 
        ~Uncopyable() {} 
        Uncopyable(const Uncopyable&)=delete; 
        Uncopyable& operator=(const Uncopyable&)=delete;
};

class UncopyableComplexNumber : public ComplexNumber, public Uncopyable{
    public:
        UncopyableComplexNumber(const float a, const float b)
            :ComplexNumber(a,b)
            {}
    //using ComplexNumber::ComplexNumber;
};

int main()
{
    int *a;
    char b;
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;

    ComplexNumber number(2,3);
    cout<<"number = "<<number.getRe()<<" + "<<number.getImg()<<"i"<<endl;
    ComplexNumber number2(number);
    cout<<"number2 = "<<number2.getRe()<<" + "<<number2.getImg()<<"i"<<endl;
    ComplexNumber number3;
    number3 = number;
    cout<<"number3 = "<<number3.getRe()<<" + "<<number3.getImg()<<"i"<<endl;

    UncopyableComplexNumber uncopyableNumber(5,7);
    cout<<"uncopyable = "<<uncopyableNumber.getRe()<<" + "<<uncopyableNumber.getImg()<<"i"<<endl;
    //UncopyableComplexNumber copy(uncopyableNumber);
    return 0;
}
