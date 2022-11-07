/*
 * BlockCourse.h
 *
 *  Created on: Aug 7, 2020
 *      Author: Reza
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_
#include "Course.h"

class BlockCourse:public Course
{
private:
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;
public:
	BlockCourse(unsigned int courseKey, std::string title, unsigned char major,
				float creditPoints,course_t courseType,
				Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime,
				Poco::Data::Time endTime);
	BlockCourse(unsigned int courseKey, std::string title, std::string major,
					float creditPoints,course_t courseType,
					Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime,
					Poco::Data::Time endTime);
	BlockCourse(const Course& blockCourse);

	const Poco::Data::Date getStartDate() const;
	const Poco::Data::Date getEndDate() const;
	const Poco::Data::Time getStartTime() const;
	const Poco::Data::Time getEndTime() const;

	void print() const;
	void write(std::ostream& out) const;

	virtual ~BlockCourse();
};

#endif /* BLOCKCOURSE_H_ */
