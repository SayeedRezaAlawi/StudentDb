/*
 * WeeklyCourse.h
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_
#include "Course.h"

class WeeklyCourse:public Course
{
private:
	Poco::DateTime::DaysOfWeek dayOfWeek;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
public:
	WeeklyCourse(unsigned int courseKey, std::string title, unsigned char major,
			float creditPoints,course_t courseType,Poco::DateTime::DaysOfWeek dayOfWeek,
			Poco::Data::Time startTime,Poco::Data::Time endTime);
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
				float creditPoints,course_t courseType,Poco::DateTime::DaysOfWeek dayOfWeek,
				Poco::Data::Time startTime,Poco::Data::Time endTime);
	WeeklyCourse(const Course& course);
	const Poco::DateTime::DaysOfWeek getDayOfWeek() const;
	const Poco::Data::Time getStartTime() const;
	const Poco::Data::Time getEndTime() const;
	void print() const;
	void write(std::ostream& out) const;
	virtual ~WeeklyCourse();
};

#endif /* WEEKLYCOURSE_H_ */
