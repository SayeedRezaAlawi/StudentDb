/*
 * Course.h
 *
 *  Created on: Aug 7, 2020
 *      Author: Reza
 */

#ifndef COURSE_H_
#define COURSE_H_
#include <map>
#include <string>
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"
#include "Poco/DateTime.h"
#include "Poco/Data/Data.h"

class Course
{
public:
	enum course_t {BLOCKCOURSE,WEEKLYCOURSE,OTHER};
	Course(unsigned courseKey, std::string title, std::string major, float creditPoints, course_t courseType);
	Course(unsigned courseKey, std::string title, unsigned char major, float creditPoints, course_t courseType);
	Course &operator=(const Course&) = delete;
	virtual ~Course()=0;
	const unsigned int getCourseKey() const;
	const course_t getCourseType() const;
	const float getCreditPoints() const;
	const std::string& getTitle() const;
	const std::string getMajor() const;
	virtual void print() const;
	virtual void write(std::ostream& out) const;
	static Poco::Data::Date getDate(std::string& str);
	static Poco::Data::Time getTime(std::string& str);

private:
	static std::map<unsigned char, std::string> majorById;
	unsigned int courseKey;
	std::string title;
	unsigned char major;
	float creditPoints;
	course_t courseType;
	const unsigned char getMajorByValue(const std::string majorString) const;
};

#endif /* COURSE_H_ */
