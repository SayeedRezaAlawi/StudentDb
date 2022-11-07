/*
 * Enrollment.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#include "Enrollment.h"
#include <iostream>

Enrollment::Enrollment(std::string semester,const Course& course):semester(semester),grade(0.0)
{
	if(course.getCourseType() == Course::BLOCKCOURSE) {
			this->course = new BlockCourse(course);
	}
	else if(course.getCourseType() == Course::WEEKLYCOURSE) {
				this->course = new WeeklyCourse(course);
	}

}

Enrollment::Enrollment(std::string semester,float grade,const Course& course):semester(semester),grade(grade)
{
	if(course.getCourseType() == Course::BLOCKCOURSE) {
			this->course = new BlockCourse(course);
	}
	else if(course.getCourseType() == Course::WEEKLYCOURSE) {
				this->course = new WeeklyCourse(course);
	}

}

const float Enrollment::getGrade() const
{
	return grade;
}

const std::string Enrollment::getSemester() const
{
	return semester;
}

const Course& Enrollment::getCourse() const
{
	return *course;
}

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}

void Enrollment::setSemester(const std::string &semester)
{
	this->semester = semester;
}

void Enrollment::update()
{
	int choice = -1;
	while(choice) {
	std::cout<<std::endl<<"Properties to Update:"<<std::endl;
	std::cout<<"1. Grade"<<std::endl<<
			"2. Semester"<<std::endl<<
			"Enter Choice of Property (0 to terminate)"<<std::endl;
	std::cin>>choice;
	switch(choice) {
	case 1: {
		std::string gradeUser;
		std::cout<<"Enter Grade"<<std::endl;
		std::cin>>gradeUser;
		grade = std::atof(gradeUser.c_str());
		break;
		}
	case 2: {
		std::string sem;
		std::cout<<"Enter Semester"<<std::endl;
		std::cin>>sem;
		semester = sem;
		break;
		}
	}
	}
}

void Enrollment::write(std::ostream& out) const
{
	out << course->getCourseKey() << ";" << semester << ";" << grade << std::endl;
}

Enrollment::~Enrollment()
{
	// TODO Auto-generated destructor stub
}

