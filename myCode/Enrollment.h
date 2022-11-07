/*
 * Enrollment.h
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_
#include <string>
#include "Course.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"

class Enrollment
{
private:
	float grade;
	std::string semester;
	Course* course;
public:
	Enrollment(std::string semester,const Course& course);
	Enrollment(std::string semester,float grade,const Course& course);
	const float getGrade() const;
	const std::string getSemester() const;
	const Course& getCourse() const;
	void update();
	virtual ~Enrollment();
	void setGrade(float grade);
	void write(std::ostream& out) const;
	void setSemester(const std::string &semester);
};

#endif /* ENROLLMENT_H_ */
