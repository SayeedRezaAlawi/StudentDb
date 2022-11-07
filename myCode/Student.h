/*
 * Student.h
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include <string>
#include <vector>
#include "Poco/Data/Date.h"
#include "Enrollment.h"
#include "Address.h"


class Student
{
private:
	static unsigned int nextMatrikelNumber;
	unsigned int matrikelNumber;
	std::string firstName;
	std::string lastName;
	Poco::Data::Date dateOfBirth;
	std::vector<Enrollment> enrollments;
	Address* address;
	unsigned int noOfEnrollments;
	void newAddress();

public:
	Student(std::string firstName,std::string lastName,Poco::Data::Date dateOfBirth, Address& address);
	const std::string getFirstName() const;
	const std::string getLastName() const;
	const unsigned int getMatrikelNumber() const;
	const std::vector<Enrollment> getEnrollments()const;
	const Address* getAddress() const;
	void addEnrollment(const Enrollment& enrollment);
	void update();
	void print() const;
	void write(std::ostream& out) const;
	void writeEnrollment(std::ostream& out) const;
	virtual ~Student();
};

#endif /* STUDENT_H_ */
