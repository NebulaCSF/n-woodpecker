/*
* <one line to give the program's name and a brief idea of what it does.>
* Copyright (C) 2021  <copyright holder> <email>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ATOMEXTRAS_VALUESPROPERTIES_H
#define ATOMEXTRAS_VALUESPROPERTIES_H


#include <string>
#include <map>
#include <vector>

namespace Atom
{
    namespace Extras
    {
        class ValuesProperties;
    }
}

class AtomExtras::ValuesProperties
{
    public:
        ValuesProperties();
        ValuesProperties(std::string value, bool quotes = true);
        ~ValuesProperties();

        friend bool operator==(ValuesProperties& a, ValuesProperties& b)
        {
            if(a.GetFinalValue() == b.get_value())
                return true;
            else
                return false;
        }

        friend bool operator!=(ValuesProperties& a, ValuesProperties& b)
        {
            if(a.GetFinalValue() != b.GetFinalValue())
                return true;
            else
                return false;
        }
        friend bool operator==(const ValuesProperties& a, const ValuesProperties& b)
        {
            if(a.GetFinalValue() == b.get_value())
                return true;
            else
                return false;
        }

        friend bool operator!=(const ValuesProperties& a, const ValuesProperties& b)
        {
            if(a.GetFinalValue() != b.GetFinalValue())
                return true;
            else
                return false;
        }

        std::string& get_value()
        {
            auto& var = value_;
            return var;
        }
        std::string get_value() const {return value_;}
        bool get_quotes() const {return quotes_;}

        void set_value(std::string value) {value_ = value;}
        void set_quotes(bool quote) {quotes_ = quote;}

        std::string GetFinalValue();
        std::string GetFinalValue() const;

    private:
        std::string value_;
        bool quotes_;
};

#endif // ATOMEXTRAS_VALUESPROPERTIES_H
