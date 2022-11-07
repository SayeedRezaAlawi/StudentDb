/*
 * WeeklyCourse.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#include "WeeklyCourse.h"
#include <iostream>

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title, unsigned char major,
		float creditPoints,course_t courseType,Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime,Poco::Data::Time endTime):
		Course(courseKey,title,major,creditPoints,courseType),
		dayOfWeek(dayOfWeek),startTime(startTime),endTime(endTime)
{
}
WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
		float creditPoints,course_t courseType,Poco::DateTime::DaysOfWeek dayOfWeek,
		Poco::Data::Time startTime,Poco::Data::Time endTime):
		Course(courseKey,title,major,creditPoints,courseType),
		dayOfWeek(dayOfWeek),startTime(startTime),endTime(endTime)
{
}

WeeklyCourse::WeeklyCourse(const Course& course):Course(course.getCourseKey(),
		course.getTitle(),course.getMajor(),course.getCreditPoints(),Course::WEEKLYCOURSE)
{
}


WeeklyCourse::~WeeklyCourse()
{
	// TODO Auto-generated destructor stub
}

const Poco::DateTime::DaysOfWeek WeeklyCourse::getDayOfWeek() const
{
	return dayOfWeek;
}

const Poco::Data::Time WeeklyCourse::getStartTime() const
{
	return startTime;
}

const Poco::Data::Time WeeklyCourse::getEndTime() const
{
	return endTime;
}

void WeeklyCourse::print() const
{
	std::cout << "W;" << getCourseKey() << ";" << getTitle() << ";" << getMajor() << ";"
			<< getCreditPoints() << ";" << dayOfWeek
			<< ";" << startTime.hour() << ":" << startTime.minute() << ";" << endTime.hour() << ":"
			<< endTime.minute() << std::endl;
}

void WeeklyCourse::write(std::ostream& out) const
{
	out << "W;";
	Course::write(out);
	out << getCourseKey() << ";" << getTitle() << ";" << getMajor() << ";"
				<< getCreditPoints() << ";" << dayOfWeek
				<< ";" << startTime.hour() << ":" << startTime.minute() << ";" << endTime.hour() << ":"
				<< endTime.minute() << std::endl;
}
