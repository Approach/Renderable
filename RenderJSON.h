#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <typeinfo>
#include "RenderNode.h"

using namespace std;
typedef pair<uint64_t, string> JSON_Property;
typedef unsigned short ushort;

namespace Approach {
namespace Renderable {

class RenderJSON : RenderNode <std::ostream> //: RenderNode
{

//ENUM_FLAGS(MemberJSON)
enum class MemberJSON
{
ObjMember = 0x1,
ArrayMember = 0x2,
StringMember = 0x4,
DecimalMember = 0x8,
IntMember = 0x100,
};

    RenderFlags RenderState;
    MemberJSON JSONFlags;
//    RenderFlags RenderFlags;

bool IsArray;
uint64_t counter, cursor;

map<JSON_Property, int64_t> IntegerValues;
map<JSON_Property, double> DecimalValues;
map<JSON_Property, string> StringValues;
map<JSON_Property, pair<bool, RenderJSON*> > children;

map<uint64_t, MemberJSON> TotalOrdering;

RenderJSON(bool _IsArray=false) : counter(0), cursor(0), IsArray(_IsArray)
{
//TODO call base constructor?

TotalOrdering.clear();
IntegerValues.clear();
DecimalValues.clear();
StringValues.clear();

children.clear();
TotalOrdering.clear();


}

template <typename Numeric>
string to_string(Numeric number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/** Rendering Pipeline Starts Below **/


bool addItem(int64_t property)
{
IntegerValues.insert( make_pair( make_pair(counter, static_cast<string>("")), property) ) ;
TotalOrdering.insert( make_pair( this->counter, MemberJSON::IntMember ));
++this->counter;
}

bool addItem(double property)
{
DecimalValues.insert( make_pair( make_pair(counter, static_cast<string>("")), property) ) ;
TotalOrdering.insert( make_pair( counter, MemberJSON::DecimalMember) );

++counter;
}
bool addItem(string property)
{
StringValues.insert( make_pair( make_pair(counter, static_cast<string>("")), property) ) ;
TotalOrdering.insert( make_pair(counter, MemberJSON::StringMember) );

++counter;
}

bool addItem(pair<bool, RenderJSON*> property)
{
children.insert( make_pair( make_pair( counter, static_cast<string>("") ),property ) );

if(property.first) TotalOrdering.insert( make_pair(counter, MemberJSON::ArrayMember) );
else TotalOrdering.insert( make_pair(counter, MemberJSON::ObjMember) );

++counter;
}

bool addItem(pair<string, int64_t> property)
{
IntegerValues.insert( make_pair( make_pair(counter, property.first ),property.second ) );
TotalOrdering.insert( make_pair( counter, MemberJSON::IntMember) );

++counter;
}

bool addItem(pair<string, double> property)
{
DecimalValues.insert( make_pair( make_pair(counter, property.first ),property.second ) );
TotalOrdering.insert( make_pair( counter, MemberJSON::DecimalMember) );

++counter;
}

bool addItem( pair<string, pair<bool, RenderJSON*> > property)
{
children.insert( make_pair( make_pair(counter, property.first ),property.second ) );

if(property.second.first) TotalOrdering.insert( make_pair( counter, MemberJSON::ArrayMember) );
else TotalOrdering.insert( make_pair(counter, MemberJSON::ObjMember) );

++counter;
}


inline void RenderHead(ostream& outputstream)
{
    if (RenderState != RenderFlags::ContentOnly && RenderState != RenderFlags::OpenRendered)
    {
        if (IsArray) outputstream<<"[";
        else outputstream<<"{";


      RenderState = RenderState & RenderFlags::OpenRendered;//set open rendered flag on
    }

    RenderState = RenderState & RenderFlags::ContentRendered; //Set ContentRendered flag on
}

//TODO
inline void RenderCorpus(ostream& outputstream)
{
if (this->RenderState != RenderFlags::ContentRendered)
        {
            //for loop. each key and value pair item in TotalOrdering
            for (auto& iter : TotalOrdering)
            {
                if (iter.first != 0) outputstream<<",";
                switch(iter.second)
                {
                    case (MemberJSON::IntMember) : //TODO iter.second is of type integer
                        //search integerValues for proper element.
                        for (auto &iter2 : IntegerValues)
                        {
                            if(iter.first == iter2.first.first){ //Integer values is a map<map<uint64_t, string>, uint64_t>
                            outputstream<<"\"" + (iter2.first.second.empty() ? to_string(iter2.first.first) : iter2.first.second) + "\" : " + to_string(iter2);
                            }
                        }
                    break;

                    case (MemberJSON::DecimalMember) : //TODO iter.second is of type double                        //search integerValues for proper element.
                        for (auto &iter2 : DecimalValues)
                        {
                            if(iter.first == iter2.first.first){ //Integer values is a map<map<uint64_t, string>, uint64_t>
                            outputstream<<"\"" + (iter2.first.second.empty() ? to_string(iter2.first.first) : iter2.first.second) + "\" : " + to_string(iter2);
                            }
                        }
                    break;

                    case (MemberJSON::StringMember) : //TODO iter.second is of type String
                        //search integerValues for proper element.
                        for (auto &iter2 : StringValues)
                        {
                            if(iter.first == iter2.first.first){ //Integer values is a map<map<uint64_t, string>, uint64_t>
                            outputstream<<"\"" + (iter2.first.second.empty() ? to_string(iter2.first.first) : iter2.first.second) + "\" : \"" + to_string(iter2) + "\"";
                            }
                        }
                        break;

                    case (MemberJSON::ArrayMember):
                    case (MemberJSON::ObjMember):
                        for (auto &iter2 : children)
                        {
                            if(iter.first == iter2.first.first){
                                outputstream<<((iter2.first.second.empty() ? ((iter2.second.first) ? "" : "\"" + to_string(iter2.first) + "\"") :"\"" + to_string(iter2.second.second) +"\"") + " : ");
                                iter2.second.second->render(outputstream);
                            }
                        }
                        break;

                    default: break;
                }
            }
            RenderState = this->RenderState & RenderFlags::ContentRendered; //Set ContentRendered flag on
        }
    }

inline void RenderTail(ostream& outputstream)
{
if (this->RenderState != RenderFlags::ContentOnly)
{
//outputstream<<endl;
if(IsArray) outputstream<<"]";
else outputstream<<"}";
}
}

inline void prerender(ostream& outputstream)
{
this->RenderHead(outputstream);
this->RenderTail(outputstream);
}

inline void render(ostream& outputstream)
{
RenderHead(outputstream);
RenderCorpus(outputstream);
RenderTail(outputstream);
}

/////////////////////////////////
///stream functions
/////////////////////////////////

inline void operator>>(ostream& outputstream) {this->render(outputstream);}

inline friend ostream& operator << (ostream& outputstream, RenderJSON &obj) {obj.render(outputstream);}
/*
inline void Add(RenderJSON &incoming)
{
    //children.add(new map<ulong_t , to_stringstring>(counter, NULL), new map<bool, RenderJSON>(incoming.IsArray, incoming));
    children.insert(make_pair(counter, NULL), make_pair(incoming.IsArray, incoming));
    TotalOrdering.insert(counter, (incoming.IsArray) ? (ushort)MemberJSON->ArrayMember : (ushort)MemberJSON->ObjMember);
    counter++;
}
*/
void Add(RenderJSON &incoming){
    addItem(make_pair(incoming.IsArray, &incoming));
}

void Add(string key, RenderJSON &incoming)
{
    addItem(make_pair(string(key), make_pair(incoming.IsArray, &incoming)));
}

};
}
