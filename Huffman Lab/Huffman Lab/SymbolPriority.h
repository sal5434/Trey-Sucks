// SymbolPriority.h - HUffman code Lab
// Written by: Sarah Lakos

#pragma once

#include <iostream>

using namespace std;

struct SymbolPriority
{
   SymbolPriority(char symbol, int priority);

   char Symbol;
   int Priority;

   bool operator > (const SymbolPriority& compareTo) const;
   bool operator < (const SymbolPriority& compareTo) const;
   bool operator == (const SymbolPriority& compareTo) const;
};

// Constructor
SymbolPriority::SymbolPriority(char symbol,int priority)
	: Symbol(symbol)
	, Priority(priority)
{
}

bool SymbolPriority::operator > (const SymbolPriority& compareTo) const
{
	return(this->Priority < compareTo.Priority);
}

bool SymbolPriority::operator < (const SymbolPriority& compareTo) const
{
	return(this->Priority < compareTo.Priority);
}

bool SymbolPriority::operator == (const SymbolPriority& compareTo) const
{
    return(this->Priority == compareTo.Priority);
}

ostream& operator << (ostream& stream, const SymbolPriority& object) 
// The '<<' operator // Stream out-put operator                                                                                                                    
{
	return stream << "[ '" << object.Symbol << "', " << object.Priority << " ]" << flush;
}