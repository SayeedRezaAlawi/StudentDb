/*
 * Course.cpp
 *
 *  Created on: Aug 7, 2020
 *      Author: Reza
 */

#include "Course.h"
#include <iostream>

std::map<unsigned char, std::string> Course::majorById=
{{'A',"Automation"},{'E',"Embedded"},{'C',"Communication"},{'P', "Power"}};


Course::Course(unsigned courseKey, std::string title, std::string major, float creditPoints, course_t courseType):
courseKey{courseKey},title{title},creditPoints{creditPoints},courseType{courseType}
{
	for(auto& value:majorById)
	{
		if(value.second == major)
		{
			this->major=value.first;
		}
	}
}

Course::Course(unsigned courseKey, std::string title, unsigned char major, float creditPoints, course_t courseType):
courseKey{courseKey},title{title},major{major},creditPoints{creditPoints},courseType{courseType}
{
}

Course::~Course() {}

const std::string Course::getMajor() const
{
	return majorById[major];
}

const unsigned int Course::getCourseKey() const
{
	return courseKey;
}

const Course::course_t Course::getCourseType() const
{
	return courseType;
}

const float Course::getCreditPoints() const
{
	return creditPoints;
}

const std::string& Course::getTitle() const
{
	return title;
}

void Course::print() const
{
	std::cout << std::endl << getCourseKey() << ";" << getTitle() << ";" << getMajor()<< ";"
			<< getCreditPoints() << ";" << std::endl;
}

void Course::write(std::ostream& out) const
{
	out << getCourseKey() << ";" << getTitle() << ";" << getMajor()<< ";"
			<< getCreditPoints() << ";";
}

Poco::Data::Date Course::getDate(std::string &str)
{
	int day,month,year;
	int daydotpos,monthdotpos,yeardotpos;
	daydotpos=str.find(".");
	day=atoi(str.substr(0,daydotpos).c_str());
	monthdotpos=str.find(".",daydotpos+1);
	month=atoi(str.substr(daydotpos+1,monthdotpos-daydotpos+1).c_str());
	yeardotpos=str.find(".",monthdotpos+1);
	year=atoi(str.substr(monthdotpos+1,yeardotpos-monthdotpos+1).c_str());
	return Poco::Data::Date{year,month,day};
}

Poco::Data::Time Course::getTime(std::string &str)
{
	int hour,minute;
	int colpos;
	colpos=str.find(":");
	hour=atoi(str.substr(0,colpos).c_str());
	minute=atoi(str.substr(colpos+1).c_str());
	return Poco::Data::Time{hour,minute,00};
}

const unsigned char Course::getMajorByValue(const std::string majorString) const
{
	unsigned char key;
	for(auto& value:majorById)
	{
		if(value.second == majorString)
		{
			key=value.first;
		}
	}
	return key;
}
