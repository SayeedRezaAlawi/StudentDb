/*
 * BlockCourse.cpp
 *
 *  Created on: Aug 7, 2020
 *      Author: Reza
 */

#include "BlockCourse.h"
#include <iostream>
BlockCourse::BlockCourse(unsigned int courseKey, std::string title, unsigned char major,
		float creditPoints,course_t courseType,
		Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime):
		Course(courseKey, title, major, creditPoints, courseType),
		startDate(startDate), endDate(endDate), startTime(startTime), endTime(endTime)
{}

BlockCourse::BlockCourse(unsigned int courseKey, std::string title, std::string major,
		float creditPoints,course_t courseType,
		Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime):
		Course(courseKey, title, major, creditPoints, courseType),
		startDate(startDate), endDate(endDate), startTime(startTime), endTime(endTime)
{}

BlockCourse::BlockCourse(const Course& blockCourse):
		Course(blockCourse.getCourseKey(), blockCourse.getTitle(),
				blockCourse.getMajor(), blockCourse.getCreditPoints(), Course::BLOCKCOURSE)
{}

BlockCourse::~BlockCourse()
{
	// TODO Auto-generated destructor stub
}

const Poco::Data::Date BlockCourse::getStartDate() const
{
	return startDate;
}

const Poco::Data::Date BlockCourse::getEndDate() const
{
	return endDate;
}

const Poco::Data::Time BlockCourse::getStartTime() const
{
	return startTime;
}

const Poco::Data::Time BlockCourse::getEndTime() const
{
	return endTime;
}

void BlockCourse::print() const
{
	std::cout << "B;" << getCourseKey() << ";" << getTitle() << ";" << getMajor() << ";"
			<< getCreditPoints() << ";" << startDate.day() << "." << startDate.month() << "."
			<< startDate.year() << ";" << endDate.day() << "." << endDate.month() << "." << endDate.year()
			<< ";" << startTime.hour() << ":" << startTime.minute() << ";" << endTime.hour() << ":"
			<< endTime.minute() << std::endl;
}

void BlockCourse::write(std::ostream& out) const
{
	out << "B;";
	Course::write(out);
	out << startDate.day() << "." << startDate.month() << "."
			<< startDate.year() << ";" << endDate.day() << "." << endDate.month() << "." << endDate.year()
			<< ";" << startTime.hour() << ":" << startTime.minute() << ";" << endTime.hour() << ":"
			<< endTime.minute() << std::endl;
}

