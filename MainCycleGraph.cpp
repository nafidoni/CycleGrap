// cycleChordless.cpp : définit le point d'entrée pour l'application console.
//

//#include "stdafx.h"
#include <iostream>
#include<conio.h>
#include <vector>
#include <string>
#include<set>

using namespace std;

//define the class sommet
class Sommet {
private:
    double x;
    double y;
    std::string label;

    int mNum;
    static int & MyStatic()
    {
        static int mStatic = 1;
        return mStatic;
    }

public:

    int   GetMyStaticValue() const { return MyStatic(); }
    int & GetMyStaticVar() { return MyStatic(); }
    static bool isMyStatic(int & num) { return &num == &MyStatic(); }
    int getId() const {return mNum;}

    double getX() const { return x; }
    double getY() const { return y; }
    std::string getLabel() const { return label; }
    void setX(double _x) { x = (_x); }
    void setY(double _y) { y = (_y); }
    void setLabel(std::string lbl) { label = lbl; }


    //display a list of vertex
    ostream& displayVertex(ostream& out) const {
        //out << label << "(" << x <<"; "<< y << ")";
        out << label << "(" << mNum << ")";
        return out;
    }

    bool IsLessThan(const Sommet& A) const {
        return this->mNum < A.mNum;
    }

    //Sommet() { }
    Sommet(double _x, double _y, std::string lbl) {

        mNum = GetMyStaticValue();
        GetMyStaticVar() = mNum + 1;
        x = _x; y = _y; label = lbl;
    }
};

ostream& operator<<(ostream& out, Sommet const& B)
{
    return B.displayVertex(out);
}


//define the class ArcPoints
class ArcPoints
{
private:
    Sommet first;
    Sommet second;
    static int id;

    int mNum;
    static int & MyStatic()
    {
        static int mStatic = 1;
        return mStatic;
    }

public:
    int   GetMyStaticValue() const { return MyStatic(); }
    int & GetMyStaticVar() { return MyStatic(); }
    static bool isMyStatic(int & num) { return &num == &MyStatic(); }

    //display a list of vertex
    ostream& displayArc(ostream& out) const {
        out << mNum << "-[" << first << ", " << second << "]";
        return out;
    }

    bool IsLessThan(const ArcPoints& A) const {
        return this->mNum < A.mNum;
    }

    ArcPoints(Sommet s1, Sommet s2) : first(s1), second(s2) {
        mNum = GetMyStaticValue();
        GetMyStaticVar() = mNum + 1;
        id++;
    }

    Sommet getFirst() const { return first; }
    Sommet getSecond() const { return second; }
    /*void setFirst(Sommet s) { first = s; }
    void setSecond(Sommet s) { second = s; }*/
};
int ArcPoints::id(0);

//define the class graphePoint
class GraphePoint
{
private:
    vector<ArcPoints> listArc;
    vector<Sommet> listSommet;
    vector<ArcPoints> getListArc()const { return listArc; }
    vector<Sommet> getListSommet()const { return listSommet; }
public:

    void setListArc(vector<ArcPoints>vec) { listArc = vec; }
    void setListSommet(vector<Sommet>vec) { listSommet = vec; }

};

//define a vector of sommet
vector<Sommet> listSommet;

double distancePoinToPoint(Sommet A, Sommet B)
{
    double c = sqrt((B.getX() - A.getX())*(B.getX() - A.getX()) + (B.getY() - A.getY())*(B.getY() - A.getY()));
    return c;
}


template<typename T>
void removeElt(T som, vector<T>& list) {

    auto it = std::find(list.begin(), list.end(), (T)som);
    if (it != list.end())
        list.erase(it);
}


void removeSom(Sommet som, vector<Sommet> list){
    removeElt(som,list);
}

template<typename T>
bool containsElt(T const& som, vector<T> const& list) {
    return (!list.empty() && (std::find(list.begin(), list.end(), (T)som) != list.end()));
}


bool operator==(Sommet const& A, Sommet const& B)
{
    if (A.getId() == B.getId() || A.getX() == B.getX() && A.getY() == B.getY() || distancePoinToPoint(A, B) <= 0.01) return true;
    return false;
}

bool operator!=(Sommet const& A, Sommet const& B)
{
    return !(A == B);
}

bool operator<(Sommet const& A, Sommet const& B)
{
    return (A.IsLessThan(B));
}

bool operator>(Sommet const& A, Sommet const& B)
{
    return (!A.IsLessThan(B) && A!=B);
}


bool operator==(ArcPoints const& A, ArcPoints const& B)
{
    return (A.getFirst() == B.getFirst() && A.getSecond() == B.getSecond());
}

bool operator!=(ArcPoints const& A, ArcPoints const& B)
{
    return !(A == B);
}

bool operator<(ArcPoints const& A, ArcPoints const& B)
{
    //return distancePoinToPoint(A.getFirst(), A.getSecond()) < distancePoinToPoint(B.getFirst(), B.getSecond());
    return (A.IsLessThan(B));
}

ostream& operator<<(ostream& out, ArcPoints const& B)
{
    return B.displayArc(out);
}

//display a list of vertex
void displayListVertex(set<Sommet> list) {
    //Sommet som;
    //cout<<"List of vertex"<<endl;
    for (std::set<Sommet>::iterator it = list.begin(); it != list.end(); ++it)
    {
        Sommet som = *it;
        cout << som << endl;
    }

}



void displayListArcs(set<ArcPoints> listArc) {
    //cout<<"List of edge"<<endl;
    for (std::set<ArcPoints>::iterator it = listArc.begin(); it != listArc.end(); ++it) {
        ArcPoints arc = *it;
        cout << arc << endl;

    }
}


//define the class Cycle
class Cycle {
private:
    vector<Sommet> cycle;
    int id;

    static int & MyStatic()
    {
        static int mStatic = 1;
        return mStatic;
    }

public:
    Cycle(){
        id = GetMyStaticValue();
        GetMyStaticVar() = id + 1;
    }
    unsigned int getSize() const { return cycle.size();}
    const Sommet& get(unsigned int i) const {return cycle[i];}

    int   GetMyStaticValue() const { return MyStatic(); }
    int & GetMyStaticVar() { return MyStatic(); }
    static bool isMyStatic(int & num) { return &num == &MyStatic(); }

    bool equal(Cycle const& B) const {
        if(cycle.size()!=B.getSize()) return false;
        for(unsigned int i=0; i<B.getSize();i++){
            if( cycle[i]!= B.get(i)) return false;
            //if( !B.containsVertex(cycle[i])) return false;
        }
        return true;
    }
    bool containsVertex(Sommet const& som) const{
        return containsElt(som, cycle);
    }

    void addVertex(Sommet som){
        if(containsVertex(som)) return;
        cycle.push_back(som);
    }

    void cpyData(Cycle C){
        this->cycle = C.cycle;
    }

    void removeVertex(Sommet som){removeElt(som, cycle);}


    //display a list of vertex
    ostream& displayCycle(ostream& out) const {
        //out << label << "(" << x <<"; "<< y << ")";
        out  << "(" << id<< ")";
        return out;
    }
};

bool operator==(Cycle const& A, Cycle const& B)
{
    return A.equal(B);
}

bool compareListycle(vector<Cycle> A, Cycle B){
    for(unsigned int i=0;i<A.size();i++){
        if(A[i]== B) return true;
    }
    return false;
}

bool operator!=(Cycle const& A, Cycle const& B)
{
    return !(A == B);
}


ostream& operator<<(ostream& out, Cycle const& B)
{
    return B.displayCycle(out);
}



//for a vertex return all adjacent vertex
set<Sommet> searchAllAdjacentVertex(Sommet searchSommet, set<ArcPoints> listArcs, Sommet intruder) {
    // cout << "searchAllAdjacentVertex" <<searchSommet<<endl;

    set<Sommet> list;
    for (set<ArcPoints>::iterator it = listArcs.begin(); it != listArcs.end(); it++)
    {
        ArcPoints arcs = *it;
        if ((arcs.getFirst() == searchSommet)&&(arcs.getSecond() != intruder)) {
            list.insert(arcs.getSecond());
        }
        else if ((arcs.getSecond() == searchSommet)&&(arcs.getFirst() != intruder)) {
            list.insert(arcs.getFirst());
        }
    }

    return list;
}

// for a set of vertex return all possible couple of vertex
set<ArcPoints> coupleVertex(set<Sommet> som) {

    set<ArcPoints> setEdge;
    for (std::set<Sommet>::iterator it = som.begin(); it != som.end(); ++it) {
        for (std::set<Sommet>::iterator ots = next(it); ots != som.end(); ++ots) {
            ArcPoints arcs(*it, *ots);
            setEdge.insert(arcs);
        }
    }
    return setEdge;
}

// for two vertex return true if they are adjacents otherwise false
bool testAdjacentVertex(Sommet a, Sommet b, set<ArcPoints> list) {


    // cout << "=======================testAdjacentVertex\n";
    for (std::set<ArcPoints>::iterator it = list.begin(); it != list.end(); ++it) {
        ArcPoints arc = *it;
        if ((arc.getFirst() == a && arc.getSecond() == b) || (arc.getFirst() == b && arc.getSecond() == a))
        {
            return true;
        }
    }
    return false;

}


//bool testExistVertex(Sommet som, Cycle list){

//    for(int i=0;i<0;i++){
//        if(som == list.get(i)) return true;
//    }
//    return false;
//}


//display a list of vertex
void displayVectVertex(Cycle list) {
    //Sommet som;
    //cout<<"List of vertex"<<endl;
    for (unsigned int i=0;i<list.getSize();i++ )
    {
        cout << list.get(i) << endl;
    }

}
//for a vector of vertex verify if the last vertex don't have link with internal vertex
bool testInternalLinkWithLastVertex(Cycle som, set<ArcPoints> list) {

    // cout << "=======================testInternalLinkWithLastVertex\n";
    for (unsigned int i = 1; i<som.getSize() - 2; i++) {
        if (testAdjacentVertex(som.get(i), som.get(som.getSize() - 1), list)) {
            return true;
        }

    }
    //  cout << "Endd=======================testInternalLinkWithLastVertex\n";
    return false;
}

//for a vector of vertex verify if the last vertex  have link with the first vertex
bool testFirstVertesWithLastVertex(Cycle som, set<ArcPoints> list) {
    //cout << "=======================testFirstVertesWithLastVertex\n";
    return testAdjacentVertex(som.get(0), som.get(som.getSize() - 1), list);
    // cout << "Endd=======================testFirstVertesWithLastVertex\n";
}

//remove edge that are link with a vertex
void  RemoveLinkVertex(Sommet som, set<ArcPoints>& arcSet) {
    for (auto it = arcSet.begin(); it != arcSet.end(); ) {
        ArcPoints arcs = *it;
        if (arcs.getFirst() == som || arcs.getSecond() == som) it = arcSet.erase(it);
        else it++;
    }

}

bool existVertex(Sommet som, set<Sommet> list){

    for (set<Sommet>::iterator iit = list.begin(); iit != list.end(); iit++)
    {

        //cout<<"\n\n=======================the couple vertex"<<som<<*iit<<endl;
        if(som == *iit) return true;
    }

    return false;
}

bool existCycle(Sommet som, Cycle list){

    for (int i=0;i< list.getSize(); i++)
    {

        //cout<<"\n\n=======================the couple vertex"<<som<<*iit<<endl;
        if(som == list.get(i)) return true;
    }

    return false;
}

bool verifyIfCycle(Cycle list, set<ArcPoints> listArc, set<Sommet> listSom){
    set<Sommet> listSommet;

    for (set<Sommet>::iterator som = listSom.begin(); som != listSom.end(); som++)
    {
        int i;
        bool el=false;
        for(i=0;i<list.getSize();i++){
            if(list.get(i)==*som)el=true;
        }
        if(el==false)listSommet.insert(*som);
    }
    int valu=0;
    for (set<Sommet>::iterator som = listSommet.begin(); som != listSommet.end(); som++)
    {
      set<Sommet> listCycle;
      bool trouver=false;
      listCycle = searchAllAdjacentVertex(*som, listArc,*som);
      int k=0;
      for (set<Sommet>::iterator curSom = listCycle.begin(); curSom != listCycle.end(); curSom++)
      {
          if(existCycle(*curSom, list)) k++;
          if(k==2) trouver=true;
       }
        if(trouver) valu=1;
    }
    if(valu==1)return true;
    return false;

}

vector<Cycle> findCycleAllElement(set<Sommet> listSommet, set<ArcPoints> listArc) {

    vector<Cycle> listcycle;
    set<Sommet> listAdjacentVertex;
    vector<Cycle> potentielCycles;

    for (set<Sommet>::iterator curSom = listSommet.begin(); curSom != listSommet.end(); curSom++)
    {
        Sommet som=*curSom;
        listAdjacentVertex = searchAllAdjacentVertex(som, listArc,som);
        set<ArcPoints> vertexcouple = coupleVertex(listAdjacentVertex);

        for (set<ArcPoints>::iterator vex = vertexcouple.begin(); vex != vertexcouple.end(); vex++)
        {
            ArcPoints arc = *vex;
            Cycle sommetCycle;
            if((som<arc.getFirst())&&(arc.getFirst()<arc.getSecond()))
            {
                sommetCycle.addVertex(arc.getFirst());
                sommetCycle.addVertex(*curSom);
                sommetCycle.addVertex(arc.getSecond());
                //displayVectVertex(sommetCycle);

                if (testAdjacentVertex(arc.getFirst(), arc.getSecond(), listArc)) listcycle.push_back(sommetCycle);
                else potentielCycles.push_back(sommetCycle);
            }
        }
    }

    cout << "\n EndEnd=======================findCycle - BIG WHILE: "<<potentielCycles.size()<<endl;

//        for (size_t i = 0; i<potentielCycles.size(); i++) {
//            cout<<"\n\n The potential cycle number i:"<<i<<endl;
//            Cycle v = potentielCycles[i];
//            displayVectVertex(v);
//        }

//        for (size_t i = 0; i<listcycle.size(); i++) {
//            cout<<"\n\n The former cycle number i:"<<i<<endl;
//            Cycle v = listcycle[i];
//            displayVectVertex(v);
//        }


    //search cycles
    int n=0;
    while(n<potentielCycles.size()){
        set<Sommet> interCycle ;
        Cycle p = potentielCycles[n];
        removeElt(potentielCycles[n],potentielCycles);
        n=0;

        //cout << "\n =======================Begin Potentiel Cycle "<<n<<endl;
        interCycle = searchAllAdjacentVertex(p.get(p.getSize() - 1), listArc, p.get(p.getSize() - 2));
//        cout<<"\n\nElement "<<p.get(p.getSize() - 1)<<endl;

//        displayVectVertex(p);


        for (set<Sommet>::iterator iit = interCycle.begin(); iit != interCycle.end(); iit++)
        {
            Sommet current=*iit;
            //nodeAdjacent.addVertex(current);
            Cycle c;
            c.cpyData(p);
            c.addVertex(current);


            //displayVectVertex(nodeAdjacent);
            if((current>p.get(1))&&(!testInternalLinkWithLastVertex(c, listArc)))
            {
                set<Sommet> interne=searchAllAdjacentVertex(p.get(0), listArc, p.get(1));
                if(existVertex(current,interne)){

                   if(!verifyIfCycle(c,listArc,listSommet))
                    listcycle.push_back(c);
                }
                else potentielCycles.push_back(c);

            }

        }
        //  cout << "\n EndEnd=======================display all Potentiel Cycle "<<potentielCycles.size()
        //<<endl;
       // n++;

    }

    return listcycle;
}

////find a cycle in the graph
//vector<Cycle> findCycle(set<Sommet> listSommet, set<ArcPoints> listArc) {

//    vector<Cycle> listcycle;
//    set<Sommet> listAdjacentVertex;
//    //int i = 0;

//    //while( i<listSommet.size()&&listSommet.size()!=0)
//    for (set<Sommet>::iterator curSom = listSommet.begin(); curSom != listSommet.end(); curSom++)
//    {

//        Sommet som=*curSom;
//        vector<Cycle> potentielCycles;
//        cout << "=======================findCycle - BIG WHILE: "<<som<<endl;
//        listAdjacentVertex = searchAllAdjacentVertex(som, listArc,som);
//        set<ArcPoints> vertexcouple = coupleVertex(listAdjacentVertex);
//       // cout << "=======================findCycle - vertexcouple-size: " << vertexcouple.size() << endl;

//        for (set<ArcPoints>::iterator vex = vertexcouple.begin(); vex != vertexcouple.end(); vex++) {
//           // cout << "*********************findCycle - vertexcouple-size: " << endl;
//            ArcPoints arc = *vex;
//           // cout<<*curSom<<","<<arc.getFirst()<<","<<arc.getSecond()<<endl;
//            if (testAdjacentVertex(arc.getFirst(), arc.getSecond(), listArc)) {
//                Cycle sommetCycle;
//                sommetCycle.addVertex(*curSom);
//                sommetCycle.addVertex(arc.getFirst());
//                sommetCycle.addVertex(arc.getSecond());
//               if(!compareListycle(listcycle, sommetCycle)) listcycle.push_back(sommetCycle);

//                //cout << "*********************Cycle has found " << endl;
//                //displayListVertex(sommetCycle);
//                }
//            else{
//                set<Sommet> nodeAdjacent;

//                //find all adjacent vertex for a node
//                nodeAdjacent = searchAllAdjacentVertex(arc.getFirst(), listArc,*curSom);
//               // nodeAdjacent.erase(curSom);
//               // displayListVertex(nodeAdjacent);

//                // create a vector k2Ak1ni
//                //cout<<"nodeAdjacent.size()"<<nodeAdjacent.size()<<endl;
//                for (set<Sommet>::iterator adjN = nodeAdjacent.begin(); adjN != nodeAdjacent.end(); adjN++) {
//                    Cycle interne;
//                    interne.addVertex(arc.getSecond());//k2
//                    interne.addVertex(*curSom); //A
//                    interne.addVertex(arc.getFirst());//k1
//                    interne.addVertex(*adjN);//ni
//                    //cout << "\n\n=======================interneBoucle\n"<<endl;
//                    //displayVectVertex(interne);
//                    potentielCycles.push_back(interne);
//                }
//                // create a list of potential cycle
//                for (int n = 0; n<potentielCycles.size(); n++) {

////                    cout << "=======================findCycle - SECOND WHILE\n" << n << endl;
////                    cout << "the potential cycle n:" <<n <<potentielCycles[n];
////                    displayVectVertex(potentielCycles[n]);
////                    cout << "End the potential cycle n:" <<n<< endl;

//                    if (testInternalLinkWithLastVertex(potentielCycles[n], listArc)) removeElt(potentielCycles[n],potentielCycles);
//                    else {
//                        if(testFirstVertesWithLastVertex(potentielCycles[n], listArc)){
//                            if(!compareListycle(listcycle, potentielCycles[n])) listcycle.push_back(potentielCycles[n]);
//                        }
//                        else {
//                        Cycle nodeAdjacent = potentielCycles[n];

//                       // cout<<"\n\n\n====================display node Adjacent\n\n"<<endl;
//                       // displayVectVertex(nodeAdjacent);
//                        set<Sommet> interCycle = searchAllAdjacentVertex(nodeAdjacent.get(nodeAdjacent.getSize() - 1), listArc, nodeAdjacent.get(nodeAdjacent.getSize() - 2));

//                        for (set<Sommet>::iterator iit = interCycle.begin(); iit != interCycle.end(); iit++)
//                        {
//                            Cycle findVertex = nodeAdjacent;
//                            findVertex.addVertex(*iit);
//                            potentielCycles.push_back(findVertex);
//                            cout << "=======================interPossibleCycle num:"<<endl;
//                            displayVectVertex(findVertex);
//                        }

//                    }
//                }
//              }
//            }
//        }
//        //remove all link of current vertex
//        RemoveLinkVertex(*curSom, listArc);

//        // remove the current vertex in the list
//        curSom = listSommet.erase(curSom);
//        cout<<"\n=================the find cycle\n\n"<<endl;
//        for (size_t i = 0; i<listcycle.size(); i++) {
//            cout<<"\n\n The cycle number i:"<<i<<endl;
//            Cycle v = listcycle[i];
//            displayVectVertex(v);
//        }

//        cout<<"\n\n====================== the list of arcs\n\n"<<endl;
//        displayListArcs(listArc);
//    }

//    return listcycle;
//}


int main(int argc, char *argv[])
{
    vector<Cycle> listCycle;


    //define a vector of list arc

    Sommet s1(1.0, 1.1, "L1");
    Sommet s2(2.0, 2.1, "L2");
    Sommet s3(3.0, 3.1, "L3");
    Sommet s4(4.0, 4.1, "L4");
    Sommet s5(5.0, 5.1, "L5");
    Sommet s6(6.0, 6.1, "L6");
    Sommet s7(7.0, 7.1, "L7");
    Sommet s8(8.0, 8.1, "L8");
    Sommet s9(9.0, 9.1, "L9");
    Sommet s10(10.0, 10.1, "L10");
    Sommet s11(11.0, 11.1, "L11");
    Sommet s12(12.0, 12.1, "L12");
    Sommet s13(13.0, 13.1, "L13");


    set<Sommet> V;
    V.insert(s1);
    V.insert(s2);
    V.insert(s3);
    V.insert(s4);
    V.insert(s5);
    V.insert(s6);
    V.insert(s7);
    V.insert(s8);
    V.insert(s9);
    V.insert(s10);
    V.insert(s11);
    V.insert(s12);
    V.insert(s13);


    ArcPoints arc1(s1, s2);
    ArcPoints arc2(s2, s3);
    ArcPoints arc3(s3, s4);
    ArcPoints arc4(s4, s5);
    ArcPoints arc5(s6, s5);
    ArcPoints arc6(s7, s6);
    ArcPoints arc7(s7, s8);
    ArcPoints arc8(s13, s5);
    ArcPoints arc9(s13, s7);
    ArcPoints arc10(s9, s12);
    ArcPoints arc11(s12, s13);
    ArcPoints arc12(s3, s12);
    ArcPoints arc13(s10, s9);
    ArcPoints arc14(s2, s10);
    ArcPoints arc15(s11, s10);
    ArcPoints arc16(s1, s11);
    ArcPoints arc17(s9, s8);

    set<ArcPoints> E;
    if (!E.insert(arc1).second) { cout << "Failed to insert " << arc1 << "\n"; }
    if (!E.insert(arc2).second) { cout << "Failed to insert " << arc2 << "\n"; }
    if (!E.insert(arc3).second) { cout << "Failed to insert " << arc3 << "\n"; }
    if (!E.insert(arc4).second) { cout << "Failed to insert " << arc4 << "\n"; }
    if (!E.insert(arc5).second) { cout << "Failed to insert " << arc5 << "\n"; }
    if (!E.insert(arc6).second) { cout << "Failed to insert " << arc6 << "\n"; }
    if (!E.insert(arc7).second) { cout << "Failed to insert " << arc7 << "\n"; }
    if (!E.insert(arc8).second) { cout << "Failed to insert " << arc8 << "\n"; }
    if (!E.insert(arc9).second) { cout << "Failed to insert " << arc9 << "\n"; }
    if (!E.insert(arc10).second) { cout << "Failed to insert " << arc10 << "\n"; }
    if (!E.insert(arc11).second) { cout << "Failed to insert " << arc11 << "\n"; }
    E.insert(arc1);
    E.insert(arc2);
    E.insert(arc3);
    E.insert(arc4);
    E.insert(arc5);
    E.insert(arc6);
    E.insert(arc7);
    E.insert(arc8);
    E.insert(arc9);
    E.insert(arc10);
    E.insert(arc11);
    E.insert(arc12);
    E.insert(arc13);
    E.insert(arc14);
    E.insert(arc15);
    E.insert(arc16);
    E.insert(arc17);




    //faire la recherche des cycles dans un graphe

    cout << "List of vertex" << endl;
    displayListVertex(V);
    cout << "\nList of edge" << endl;
    displayListArcs(E);
    cout << "\nEnd-List of edge" << endl;

    system("pause");

    listCycle = findCycleAllElement(V, E);


    cout << "\ndisplay all element of cycle" << endl;
    for (size_t i = 0; i<listCycle.size(); i++) {
        cout<<"\n\n The cycle number i:"<<i<<endl;
        Cycle v = listCycle[i];
        displayVectVertex(v);
    }

    cout << "End of execution" << endl;
    system("pause");
    return 0;
}

