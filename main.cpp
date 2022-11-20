#include <iostream>
#include <string>

using namespace std;

class Design{
    private:
        float weight;
        string color;

    public:
        Design()
        :weight(1),
         color("black")
         {}

        Design(const float w, const string c)
        :weight(w),
         color(c)
         {}
        
        Design(const Design &design)
        :weight(design.weight),
         color(design.color)
         {}

        float getWeight(){
            return weight;
        }

        string getColor(){
            return color;
        }
};

class ComplexNumber{
    protected:
        float re;
        float img;
        Design* design;

    public:
        ComplexNumber()
        :re(0),
         img(0),
         design(new Design())
         {}

        ComplexNumber(const float a, const float b, Design d)
        :re(a),
         img(b),
         design(&d)
         {}

        ComplexNumber(const ComplexNumber& number){
            cout<<"In copy constructor"<<endl;
            re=number.img;
            img=number.re;
            design=new Design(*number.design);
        }

        ComplexNumber& operator=(const ComplexNumber& number){
            cout<<"In copy assignment operator"<<endl;
            re=number.re;
            img=-number.img;
            Design *dOrig=design;
            design=new Design(*number.design);
            delete dOrig;
            return *this;
        }

        ComplexNumber& operator+=(const ComplexNumber& number){
            cout<<"In += operator"<<endl;
            re+=number.re;
            img+=number.img;
            return *this;
        }

        float getRe(){
            return re;
        }

        float getImg(){
            return img;
        }

        Design getDesign(){
            return *design;
        }
};

class StilishedComplexNumber : public ComplexNumber{
    private:
        string style;
    public:
        StilishedComplexNumber()
        :ComplexNumber(),
         style("solid")
         {}

        StilishedComplexNumber(const float a, const float b, Design d, const string s)
        :ComplexNumber(a,b,d),
         style(s)
         {}

        StilishedComplexNumber(const StilishedComplexNumber& number)
        :ComplexNumber(number),
         style(number.style)
         {
            cout<<"In stilished copy constructor"<<endl;
         }
 
        StilishedComplexNumber& operator=(const StilishedComplexNumber& number){
            cout<<"In stilished copy assignment operator"<<endl;
            ComplexNumber::operator=(number);
            style=number.style;
            return *this;
        }

        string getStyle(){
            return style;
        }
};

int main()
{
    Design design(1.5,"red");
    // ComplexNumber number1(2,3,design);
    // cout<<"number1 = "<<number1.getRe()<<" + "<<number1.getImg()<<"i"<<"; weight:"<<number1.getDesign().getWeight()<<" pt; color:"<<number1.getDesign().getColor()<<endl;
    // ComplexNumber number2(number1);
    // cout<<"number2 = "<<number2.getRe()<<" + "<<number2.getImg()<<"i"<<"; weight:"<<number2.getDesign().getWeight()<<" pt; color:"<<number2.getDesign().getColor()<<endl;
    // ComplexNumber number3, number4;
    // cout<<"number3 = "<<number3.getRe()<<" + "<<number3.getImg()<<"i"<<"; weight:"<<number3.getDesign().getWeight()<<" pt; color:"<<number3.getDesign().getColor()<<endl;
    // number4 = number3 = number1;
    // cout<<"number3 = "<<number3.getRe()<<" + "<<number3.getImg()<<"i"<<"; weight:"<<number3.getDesign().getWeight()<<" pt; color:"<<number3.getDesign().getColor()<<endl;
    // cout<<"number4 = "<<number4.getRe()<<" + "<<number4.getImg()<<"i"<<"; weight:"<<number4.getDesign().getWeight()<<" pt; color:"<<number4.getDesign().getColor()<<endl;
    // number4+=number3+=number2;
    // cout<<"number4 = "<<number4.getRe()<<" + "<<number4.getImg()<<"i"<<"; weight:"<<number4.getDesign().getWeight()<<" pt; color:"<<number4.getDesign().getColor()<<endl;
    // number2 = number2;

    try{
        StilishedComplexNumber stilishedNumber(5,7,design,"dotted");
        cout<<"stilishedNumber = "<<stilishedNumber.getRe()<<" + "<<stilishedNumber.getImg()<<"i"<<"; style:"<<stilishedNumber.getStyle()<<endl;
        cout<<stilishedNumber.getDesign().getColor();
        StilishedComplexNumber stilishedNumber2;
        stilishedNumber2 = stilishedNumber;
    }
    catch (const bad_alloc& e) {
        cout << "Allocation failed: " << e.what() <<endl;
    }
    return 0;
}
