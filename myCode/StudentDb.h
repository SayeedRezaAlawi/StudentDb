/*
 * StudentDb.h
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_
#include <map>
#include <memory>
#include "Student.h"
#include "Course.h"
class StudentDb
{
private:
	std::map<int, Student> students;
	std::map<int, std::unique_ptr<const Course>> courses;
	unsigned int noOfStudents, noOfCourses, noOfEnrollments;

public:
	StudentDb();
	void addNewCourse();
	void listCourse();
	void addNewStudent();
	void addNewEnrollment();
	void printStudent();
	void searchStudent();
	void updateStudent();
	void write(std::ostream& out);
	void read(std::istream& in);
	void readStudents(std::string& str);
	void readCourses(std::string& str);
	void readEnrollments(std::string& str);
	std::string getInfoFromServer();
	void addServerInfoToDb(std::string& info);
	void getServerData();
	virtual ~StudentDb();
};

#endif /* STUDENTDB_H_ */
