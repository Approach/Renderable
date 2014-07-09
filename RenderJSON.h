#include <iostream>
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

typedef unsigned long long int ProcUnit;
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
enum class T;

bool IsArray;
uint64_t counter, cursor;

map<JSON_Property, int64_t> IntegerValues;
map<JSON_Property, double> DecimalValues;
map<JSON_Property, string> StringValues;
map<JSON_Property, pair<bool, RenderJSON*> > children;

map<uint64_t, ushort> TotalOrdering;

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


/** Rendering Pipeline Starts Below **/

/*
bool addItem(int64_t property)
{
IntegerValues.insert( (new JSON_Property(this->counter, NULL)), property);
TotalOrdering.insert(this->counter, MemberJSON::IntMember);
++this->counter;
}

bool addItem(double property)
{
DecimalValues.insert( new JSON_Property(this.counter, NULL), property);
TotalOrdering.insert(this.counter, MemberJSON::DecimalMember);

++this.counter;
}
bool addItem(string property)
{
StringValues.insert( new JSON_Property(this.counter, NULL), property);
TotalOrdering.insert(this.counter, MemberJSON::StringMember);

++this.counter;
}

bool addItem(pair<bool, RenderJSON> property)
{
children.insert( property.first, property.second);

if(property.first) TotalOrdering.insert(this.counter, MemberJSON::ArrayMember);
else TotalOrdering.insert(this.counter, MemberJSON::ObjMember);

++this.counter;
}

bool addItem(pair<string, int64_t> property)
{
IntegerValues.insert( new JSON_Property( this.counter, property.first ),property.second);
TotalOrdering.insert(this.counter, MemberJSON::IntMember);

++this.counter;
}

bool addItem(pair<string, double> property)
{
DecimalValues.insert( new JSON_Property(this.counter, property.first), property.second);
TotalOrdering.insert(this.counter, MemberJSON::DecimalMember);

++this.counter;
}
bool addItem( pair<string, pair<bool, RenderJSON> > property)
{
children.insert( new JSON_Property(this.counter, property.first), property.second);

if(property.second.first) TotalOrdering.insert(this.counter, MemberJSON::ArrayMember);
else TotalOrdering.insert(this.counter, MemberJSON::ObjMember);

++this.counter;
}

*/


inline void RenderHead(ostream& outputstream)
{
    if (RenderState != RenderFlags::ContentOnly && RenderState != RenderFlags::OpenRendered)
    {
        if (IsArray) outputstream<<"[";
        else outputstream<<"{";

        RenderState = flags(RenderState & RenderFlags::OpenRendered);
    }

    this->RenderState = this->RenderState & RenderFlags::ContentRendered; //Set ContentRendered flag on
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
                switch(typeid(iter.second))
                {
                    case (typeid(int)): //TODO iter.second is of type integer
                        //loop through every element in IntegerValues
                        for (auto& iter2 : IntegerValues)
                        {
                            if(iter.first == iter2.first){
                                ostream<<"\""<<((iter2.second == NULL) ? iter2.first.)
                            }
                        }
                        break;

                    default: break;
                }
            }
            this->RenderState = this->RenderState & RenderFlags->ContentRendered; //Set ContentRendered flag on
        }
    }

inline void RenderTail(ostream& outputstream)
{
if (this->RenderState != RenderFlags->ContentOnly)
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

inline ostream& render()
{
ostream& outputstream;
this->render(outputstream);
return outputstream;
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

    inline void Add(RenderJSON &incoming)
    {
        children.Add(new map<ulong_t , string>(counter, NULL), new map<bool, RenderJSON>(incoming.IsArray, incoming));
        TotalOrdering.Add(counter, (incoming.IsArray) ? (ushort)MemberJSON.ArrayMember : (ushort)MemberJSON.ObjMember);
        counter++;
    }
    void Add(string key, RenderJSON &incoming)
    {
        children.Add(new map<ulong, string>(counter, key), new map<bool, RenderJSON>(incoming.IsArray, incoming));
        TotalOrdering.Add(counter, (incoming.IsArray) ? (ushort)MemberJSON.ArrayMember : (ushort)MemberJSON.ObjMember);
        counter++;
    }
};
}
