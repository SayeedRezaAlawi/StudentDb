/*
 * Student.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#include "Student.h"
#include <iostream>

unsigned int Student::nextMatrikelNumber=100000;

Student::Student(std::string firstName,std::string lastName,Poco::Data::Date dateOfBirth, Address& address):
matrikelNumber(nextMatrikelNumber),firstName(firstName),lastName(lastName),dateOfBirth(dateOfBirth),address(&address)
{
	nextMatrikelNumber++;
	noOfEnrollments=0;
}

const std::string Student::getFirstName() const
{
	return firstName;
}

const std::string Student::getLastName() const
{
	return lastName;
}

const unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

const Address* Student::getAddress() const
{
	return address;
}

const std::vector<Enrollment> Student::getEnrollments()const
{
	return enrollments;
}

void Student::addEnrollment(const Enrollment& enrollment)
{
	enrollments.push_back(enrollment);
}

void Student::update()
{
	int choice = -1;
	while(choice) {
		std::cout<<std::endl<<"Properties to Update:"<<std::endl;
		std::cout<<"1. First Name"<<std::endl<<
				"2. Last Name"<<std::endl<<
				"3. Date of Birth"<<std::endl<<
				"4. Enrollment Info"<<std::endl<<
				"5. Address Info"<<std::endl<<
				"Enter Choice of Property (0 to terminate)"<<std::endl;
		std::cin>>choice;

		std::string userString;
		switch(choice) {
		case 1: {
			std::cout<<"Enter First Name"<<std::endl;
			std::cin>>userString;
			firstName = userString;
			break;
		}
		case 2: {
			std::cout<<"Enter Last Name"<<std::endl;
			std::cin>>userString;
			lastName = userString;
			break;
		}
		case 3: {
			std::cout<<std::endl<<"Enter Birth Date (DD.MM.YYYY)"<<std::endl;
			std::cin>>userString;
			dateOfBirth = Course::getDate(userString);
			break;
		}
		case 4: {
			unsigned int courseKey;
			std::string semester;
			std::cout<<std::endl<<"Enter Details of the enrollment "
					"which has to be updated"<<std::endl<<"Course Key: ";
			std::cin>>courseKey;
			std::cout<<"Semester: "<<std::endl;
			std::cin>>semester;

			auto iterator=enrollments.begin();
			while(iterator->getCourse().getCourseKey() !=courseKey ||
					semester.compare(iterator->getSemester()))
			{
				iterator=std::next(iterator,1);
				if(iterator == enrollments.end())
				{
					break;
				}
			}
			if(iterator != enrollments.end())
			{
				int select=-1;
				while(select)
				{
					std::cout << std::endl << "Enter operation type" << std::endl;
					std::cout << "1. Remove the enrollment" << std::endl
							  << "2. Update properties of the enrollment" << std::endl
							  << "0. Termination"<<std::endl;
					std::cin >> select;
					if(select == 1)
					{
						enrollments.erase(iterator);
					}
					else if (select == 2)
					{
						iterator->update();
					}
				}
			}
			else
			{
			std::cout << "Enrollment of the entered course key and the entered semester" <<
					std::endl << "not present for the student in the db" << std::endl;
			}
			break;
		}
		case 5: {
			newAddress();
			break;
		}
		}
	}
}

void Student::newAddress()
{
	int choice = -1;
	std::string street = (*address).getStreet();
	std::string cityName = (*address).getCityName();
	std::string addInfo = (*address).getAdditionalInfo();
	unsigned short postalCode = (*address).getPostalCode();

	while(choice) {
		std::cout<<std::endl<<"Properties to Update:"<<std::endl;
		std::cout<<"1. Street"<<std::endl<<
				"2. Postal Code"<<std::endl<<
				"3. City Name"<<std::endl<<
				"4. Additional Info"<<std::endl<<
				"Enter Choice of Property (0 to terminate)"<<std::endl;
		std::cin>>choice;
		switch(choice) {
		case 1: {
			std::string streetUpdate;
			std::cout<<"Enter New Street"<<std::endl;
			std::cin>>streetUpdate;
			street = streetUpdate;
			break;
			}
		case 2: {
			unsigned short postalCodeUpdate;
			std::cout<<"Enter New Postal Code"<<std::endl;
			std::cin>>postalCodeUpdate;
			postalCode = postalCodeUpdate;
			break;
			}
		case 3: {
			std::string cityUpdate;
			std::cout<<"Enter New City"<<std::endl;
			std::cin>>cityUpdate;
			cityName = cityUpdate;
			break;
		}
		case 4: {
			std::string addInfoUpdate;
			std::cout<<"Enter New Additional Info"<<std::endl;
			std::cin>>addInfoUpdate;
			addInfo = addInfoUpdate;
			break;
		}
		}
	}
	address = new Address(street, postalCode, cityName, addInfo);
}

Student::~Student()
{
	// TODO Auto-generated destructor stub
}

void Student::print() const
{
	std::cout<<matrikelNumber<<";"<<lastName<<";"<<firstName<<";"<<
	dateOfBirth.day()<<"."<<dateOfBirth.month()<<"."<<dateOfBirth.year()<<";"
	<<address->getStreet()
	<<";"<<address->getPostalCode()<<";"
	<<address->getCityName()<<";"
	<<address->getAdditionalInfo()
	<<std::endl;
}

void Student::write(std::ostream& out) const
{
	out<<matrikelNumber<<";"<<lastName<<";"<<firstName<<";"<<
	dateOfBirth.day()<<"."<<dateOfBirth.month()<<"."<<dateOfBirth.year()<<";"
	<<address->getStreet()
	<<";"<<address->getPostalCode()<<";"
	<<address->getCityName()<<";"
	<<address->getAdditionalInfo()
	<<std::endl;
}

void Student::writeEnrollment(std::ostream& out) const
{
	if(enrollments.size() > 0)
	{
		out<<matrikelNumber<<";";
		for(auto& value:enrollments)
		{
			out << value.getCourse().getCourseKey()<<";";
		}
	}
}
