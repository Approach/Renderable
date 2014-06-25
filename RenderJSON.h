#include <iostream>
#include <vector>
#include <map>
#include <ostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include "RenderNode.h"

using namespace std;

typedef unsigned long long int ProcUnit;
typedef pair<uint64_t, string> JSON_Property;
typedef unsigned short ushort;

namespace Approach {
namespace Renderable {
struct RenderJSON //: RenderNode
{
    enum class MemberJSON
	{
		ObjMember = 0x1,
		ArrayMember = 0x2,
		StringMember = 0x4,
		DecimalMember = 0x8,
		IntMember = 0x100,
	};

    MemberJSON flags;

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




/*
    RenderJSON(vector<typename someType> _properties, bool _IsArray=false)
	{
		//TODO call base constructor?
        MemberJSON flags = 0;

		counter = 0; cursor = 0; TotalOrdering = new map<ulong, ushort>;
		IsArray = _IsArray;

		IntegerValues = new map<map<UInt64, string>, Int64>;
		DecimalValues = new map<map<ulong, string>, double>;
	    StringValues = new map<map<ulong, string>, string>;
		children = new map<map<ulong, string>, map<bool, RenderJSON>>;
		TotalOrdering = new map<ulong, ushort>;

		vector<someType>::iterator iter = _properties.begin();
		while(itr != _properties.end())
		{
		    string TypeInUse = typeid(_properties[itr]);

		    if(TypeInUse == typeid(int64_t))
		    {
		        IntegerValues.Add( new map<uint64_t, string>(counter, null), (int64_t)property);
		        TotalOrdering.Add( counter, (ushort)MemberJSON.IntMember);

		        counter++;

		    }
		    if(TypeInUse == typeid(double))
		    {
		        DecimalValues.Add( new map<uint64_t, string>(counter, null), (double)property);
		        TotalOrdering.Add( counter, (ushort)MemberJSON.DecimalMember);

		        counter++;

		    }
		    if(TypeInUse == typeid(string)
		    {
		        StringValues.Add( new map<uint64_t, string>(counter, null), (string)property);
		        TotalOrdering.Add( counter, (ushort)MemberJSON.StringMember);

		        counter++;

		    }
		    if(TypeInUse == typeid(map<bool, RenderJSON>))
		    {
		        children.Add( new map<uint64_t, string>(counter, null), (map<bool, RenderJSON>)property);

		        if(((map<bool, RenderJSON>)property).first) TotalOrdering.Add(counter, (ushort)MemberJSON.ArrayMember);
		        else TotalOrdering.Add(counter, (ushort)MemberJSON.ObjMember);

		        counter++;

		    }
		    if(TypeInUse == typeid(map<string, int64_t))
		    {
		        IntegerValues.Add( new map<uint64_t, string>(counter, ((map<string, int64_t>property).first),
                                             ((map<string, int64_t>)property).second;
		        TotalOrdering.Add( counter, (ushort)MemberJSON.IntMember);

		        counter++;

		    }
		    if(TypeInUse == typeid(map<string, double>))
		    {
		        DecimalValues.Add( new map<uint64, string>(counter, ((map<string, double>)property).first),
                            ((map<string, double>)property).second);
                TotalOrdering.Add(counter, (ushort)MemberJSON.DecimalMember);

		        counter++;

		    }
		    if(TypeInUse == typeid(map<string, map<bool, RenderJSON>>))
		    {
		        children.Add( new map<uint64_t, string>(counter, ((map<string, map<bool, RenderJSON>>)property).first),
                       ((map<string, map<bool, RenderJSON)property).second);

                if(((map<string, map<bool, RenderJSON>>)property).second.first) TotalOrdering.Add(counter, (ushort)MemberJSON.ArrayMember);
		        else TotalOrdering.Add(counter, (ushort)MemberJSON.ObjMember);

		        counter++;

		    }

		    //last resort
		    children.Add(new map<uint64_t, string(counter, null), new map<bool, RenderJSON>(flase, null) )
		    counter++;
		}
	}
*/








/**	Rendering Pipeline Starts Below	**/


bool addItem(int64_t property)
{
	//IntegerValues.insert( new JSON_Property(this->counter, NULL), property); //origoinal
	IntegerValues[make_pair(this->counter, NULL)] = property; //correct syntax
	TotalOrdering.insert(this->counter, MemberJSON::IntMember);
	++this.counter;
}

bool addItem(double property)
{
	DecimalValues.insert( new JSON_Property(this.counter, null), property);
	TotalOrdering.insert(this.counter, MemberJSON::DecimalMember);

	++this.counter;
}
bool addItem(string property)
{
	StringValues.insert( new JSON_Property(this.counter, null), property);
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




	inline void RenderHead(ostream& outputstream)
	{
		if (this->flags != MemberJSON.ContentOnly && this->flags != MemberJSON->OpenRendered)
		{
			if (IsArray) outputstream<<"[";
			else outputstream<<"{";

			this->flags = this->flags & MemberJSON->OpenRendered;
		}

		this->flags = this->flags & MemberJSON->ContentRendered //Set ContentRendered flag on
	}

	//TODO
	inline void RenderCorpus(ostream& outputstream)
	{
		if (this->flags != MemberJSON.ContentRendered)
        {
            //for loop. each keyvaluepair item in totalordering
            map<uint64_t, ushort>::iterator iter;
            for(iter = TotalOrdering.begin(); i != TotalOrdering.end(); i++)
            {
                if (item.Key != 0) outputstream<<",";
                switch(item.second)
                {
                    case:
                        map<uint64_t, string>::iterator iter2;
                        for(iter2 = IntegerValues.begin(); iter2 != IntegerValues.end();iter2++ )
                        {
                            if(item.first == iter2->first){
                                ostream<<"\""<<((iter2.second == null) ? iter2.first.)
                            }
                        }
                        break;

                    default: break;
                }
            }
            this.flags = this.flags & MemberJSON.ContentRendered; //Set ContentRendered flag on
        }
    }

	inline void RenderTail(ostream& outputstream)
	{
		ifthis->flags != MemberJSON.Contentonly)
		{
			//outputstream<<endl;
			if(isArray) outputstream<<"]";
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
		ostream outputstream;
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

    inline void Add(RenderJSON incoming)
    {
        children.Add(new map<ulong, string>(counter, null), new map<bool, RenderJSON>(incoming.IsArray, incoming));
        TotalOrdering.Add(counter, (incoming.IsArray) ? (ushort)MemberJSON.ArrayMember : (ushort)MemberJSON.ObjMember);
        counter++;
    }
    void add(string key, RenderJSON incoming)
    {
        children.Add(new map<ulong, string>(counter, key), new map<bool, RenderJSON>(incoming.IsArray, incoming));
        TotalOrdering.Add(counter, (incoming.IsArray) ? (ushort)MemberJSON.ArrayMember : (ushort)MemberJSON.ObjMember);
        counter++;
    }
};
}
