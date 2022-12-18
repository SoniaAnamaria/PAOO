#include <iostream>
#include <string>
#include <thread>         
#include <mutex> 
#include <memory>

using namespace std;

mutex mtx;

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
         design(new Design(d))
         {}

        ComplexNumber(const ComplexNumber& number){
            re=number.img;
            img=number.re;
            design=new Design(*number.design);
        }

        ComplexNumber& operator=(const ComplexNumber& number){
            re=number.re;
            img=-number.img;
            Design *dOrig=design;
            design=new Design(*number.design);
            delete dOrig;
            return *this;
        }

        ComplexNumber& operator+=(const ComplexNumber& number){
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

//am adaugat functia care creeaza un numar complex in functie de parametru: 0-numar complex de tipul ComplexNumber
//                                                                          1-numar complex de tipul StilishedComplexNumber
ComplexNumber* createComplexNumber(int type){
    if(type==0){
        return new ComplexNumber();
    }
    return new StilishedComplexNumber();
}

//am folosit smart pointer-ul shared_ptr care numara cate referinte exista catre obiectul respectiv si 
//elibereaza spatiul respectiv cand nu mai exista referinte catre acel obiect
void print(int type){
    //c1 pointeaza catre obiectul returnat de createComplexNumber
    shared_ptr<ComplexNumber> c1(createComplexNumber(type));
    //si c1 si c2 pointeaza catre acelasi obiect
    shared_ptr<ComplexNumber> c2(c1);

    c1=c2;

    cout<<c1->getRe()<<" + "<<c1->getImg()<<"i"<<endl;
    cout<<c2->getRe()<<" + "<<c2->getImg()<<"i"<<endl;
}

class Uncopyable {
    protected: 
        Uncopyable() {} 
        ~Uncopyable() {} 
        Uncopyable(const Uncopyable&)=delete; 
        Uncopyable& operator=(const Uncopyable&)=delete;
};

//clasa Lock din laborator, modificata astfel incat sa nu permita copierea unui obicet de tip Lock
class Lock : public Uncopyable{
    private:
        mutex *mutexPtr;
    public:
        explicit Lock(mutex *pm)
        : mutexPtr(pm)
        { 
            mutexPtr->lock();
        }
        ~Lock() 
        { 
            mutexPtr->unlock(); 
        } 
};

void printComplexNumber(ComplexNumber c){
    Lock ml(&mtx);
    //eroare,ml e Uncopyable
    //Lock ml2(ml);
    for(int i=0;i<500;i++)
        cout<<c.getRe()<<" + "<<c.getImg()<<"i"<<endl;
}

int main()
{
    Design design(1.5,"red");
    ComplexNumber number1(2,3,design);
    // cout<<"number1 = "<<number1.getRe()<<" + "<<number1.getImg()<<"i"<<"; weight:"<<number1.getDesign().getWeight()<<" pt; color:"<<number1.getDesign().getColor()<<endl;
    ComplexNumber number2(number1);
    // cout<<"number2 = "<<number2.getRe()<<" + "<<number2.getImg()<<"i"<<"; weight:"<<number2.getDesign().getWeight()<<" pt; color:"<<number2.getDesign().getColor()<<endl;
    // ComplexNumber number3, number4;
    // cout<<"number3 = "<<number3.getRe()<<" + "<<number3.getImg()<<"i"<<"; weight:"<<number3.getDesign().getWeight()<<" pt; color:"<<number3.getDesign().getColor()<<endl;
    // number4 = number3 = number1;
    // cout<<"number3 = "<<number3.getRe()<<" + "<<number3.getImg()<<"i"<<"; weight:"<<number3.getDesign().getWeight()<<" pt; color:"<<number3.getDesign().getColor()<<endl;
    // cout<<"number4 = "<<number4.getRe()<<" + "<<number4.getImg()<<"i"<<"; weight:"<<number4.getDesign().getWeight()<<" pt; color:"<<number4.getDesign().getColor()<<endl;
    // number4+=number3+=number2;
    // cout<<"number4 = "<<number4.getRe()<<" + "<<number4.getImg()<<"i"<<"; weight:"<<number4.getDesign().getWeight()<<" pt; color:"<<number4.getDesign().getColor()<<endl;
    // number2 = number2;

    // StilishedComplexNumber stilishedNumber(5,7,design,"dotted");
    // cout<<"stilishedNumber = "<<stilishedNumber.getRe()<<" + "<<stilishedNumber.getImg()<<"i"<<"; weight:"<<stilishedNumber.getDesign().getWeight()
    //     <<" pt; color:"<<stilishedNumber.getDesign().getColor()<<"; style:"<<stilishedNumber.getStyle()<<endl;
    // StilishedComplexNumber stilishedNumber2(stilishedNumber), stilishedNumber3;
    // stilishedNumber3 = stilishedNumber;


    print(0);
    //am creat 2 thread-uri, cate unul pentru fiecare numar complex
    //datorita lui Lock, numerele nu vor fi afisate intercalat, se va afisa un numar de 500 de ori, apoi celalalt
    thread th1 (printComplexNumber,number1);
    thread th2 (printComplexNumber,number2);
    th1.join();
    th2.join();
    return 0;
}