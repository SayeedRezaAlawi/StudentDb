/*
 * StudentDb.cpp
 *
 *  Created on: Aug 8, 2020
 *      Author: Reza
 */

#include "StudentDb.h"
#include <iostream>
#include "Address.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/JSON/JSON.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"

StudentDb::StudentDb()
{
	noOfStudents=0;
	noOfCourses=0;
	noOfEnrollments=0;
}

void StudentDb::addNewCourse()
{
	unsigned char coursetype;
	unsigned int courseKey;
	std::string title;
	unsigned char major;
	float creditPoints;
	std::string startdate;
	std::string enddate;
	std::string starttime;
	std::string endtime;
	unsigned int dayofweek;
	Poco::DateTime::DaysOfWeek dayOfWeek;
	Poco::Data::Date startDate;
	Poco::Data::Date endDate;
	Poco::Data::Time startTime;
	Poco::Data::Time endTime;

	std::cout << std::endl<<"Enter course key" << std::endl;
	std::cin >> courseKey;
	std::cin.ignore();

	std::cout << std::endl<<"Enter course title" << std::endl;
	std::getline(std::cin, title);

	std::cout<<std::endl<<"Enter Major: Automation(A)/Embedded(E)/Power(P)"
				"/Communications(C)"<<std::endl;
	std::cin >> major;
	std::cin.ignore();

	std::cout<<std::endl<<"Enter course credit points"<<std::endl;
	std::cin >> creditPoints;
	std::cin.ignore();

	std::cout<< "Please select your course type. W:WeeklyCourse, B:BlockCourse" << std::endl;
	std::cin >> coursetype;
	switch(coursetype)
	{
	case 'W':
		std::cout << std::endl<< "Enter the day of week for course."
				" 1:Monday, 2:Tuesday,3:Wednesday,4:Thursday, 5:Friday,6:Saturday" << std::endl;
		std::cin >> dayofweek;
		switch(dayofweek)
		{
			case 1: dayOfWeek=Poco::DateTime::MONDAY;break;
			case 2: dayOfWeek=Poco::DateTime::TUESDAY;break;
			case 3: dayOfWeek=Poco::DateTime::WEDNESDAY;break;
			case 4: dayOfWeek=Poco::DateTime::THURSDAY;break;
			case 5: dayOfWeek=Poco::DateTime::FRIDAY;break;
			case 6: dayOfWeek=Poco::DateTime::SATURDAY;break;
		}
		std::cin.ignore();
		std::cout <<std::endl<<"Enter Start Time (HH:MM)"<< std::endl;
		std::getline(std::cin,starttime);
		startTime=Course::getTime(starttime);
		std::cout <<std::endl<<"Enter Start Time (HH:MM)"<< std::endl;
		std::getline(std::cin,endtime);
		endTime=Course::getTime(endtime);
		courses.insert({courseKey,std::move(std::unique_ptr<Course>(new WeeklyCourse{courseKey,title,
		major,creditPoints,Course::WEEKLYCOURSE,dayOfWeek,startTime,endTime}))});
		noOfCourses++;
		break;
	case 'B':
		std::cin.ignore();
		std::cout << std::endl<< "Enter Start Date (DD.MM.YYYY)" << std::endl;
		std::getline(std::cin, startdate);
		startDate=Course::getDate(startdate);
		std::cout << std::endl<< "Enter End Date (DD.MM.YYYY)" << std::endl;
		std::getline(std::cin, enddate);
		endDate=Course::getDate(enddate);
		std::cout <<std::endl<<"Enter Start Time (HH:MM)"<< std::endl;
		std::getline(std::cin,starttime);
		startTime=Course::getTime(starttime);
		std::cout <<std::endl<<"Enter Start Time (HH:MM)"<< std::endl;
		std::getline(std::cin,endtime);
		endTime=Course::getTime(endtime);
		courses.insert({courseKey,std::move(std::unique_ptr<Course>(new BlockCourse(courseKey,title,major,
				creditPoints,Course::BLOCKCOURSE,startDate,endDate,startTime,endTime)))});
		noOfCourses++;
		break;
	}
}

void StudentDb::listCourse()
{
	for(auto& value:courses)
	{
		value.second->print();
	}
}

void StudentDb::addNewStudent()
{
	std::string firstName;
	std::string lastName;
	std::string dateofbirth;
	Poco::Data::Date dateOfBirth;
	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;
	std::cin.ignore();
	std::cout << std::endl << "Enter first name" << std::endl;
	std::getline(std::cin, firstName);
	std::cout << std::endl << "Enter last name" << std::endl;
	std::getline(std::cin, lastName);
	std::cout << std::endl << "Enter date of birth(DD.MM.YY)" << std::endl;
	std::getline(std::cin, dateofbirth);
	dateOfBirth=Course::getDate(dateofbirth);
	std::cout << std::endl << "Enter street" << std::endl;
	std::getline(std::cin, street);

	std::cout << std::endl << "Enter postal code" << std::endl;
	std::cin >> postalCode;

	std::cin.ignore();
	std::cout << std::endl << "Enter city name" << std::endl;
	std::getline(std::cin, cityName);

	std::cout << std::endl << "Enter additiona info" << std::endl;
	std::getline(std::cin, additionalInfo);

	Address* address= new Address{street,postalCode,cityName,additionalInfo};
	Student student{firstName,lastName,dateOfBirth,*address};
	students.insert({student.getMatrikelNumber(),student});
	noOfStudents++;

}
void StudentDb::addNewEnrollment()
{
	unsigned int matrikelnumber;
	unsigned int coursekey;
	std::string semester;
	std::cout << std::endl << "Enter matrikel number" << std::endl;
	std::cin >> matrikelnumber;

	if(students.find(matrikelnumber) == students.end())
	{
		std::cout << "Student with Matirkel number: " << matrikelnumber << " not present "
						"in the DB" <<	std::endl;
		return;
	}

	std::cout << std::endl << "Enter course key" << std::endl;
	std::cin >> coursekey;
	if(courses.find(coursekey) == courses.end())
	{
		std::cout << "Course with key: " << coursekey << " not present "
								"in the DB" <<	std::endl;
		return;
	}

	std::cout << std::endl << "Enter semester" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, semester);
	if(!students.empty())
	{
		students.at(matrikelnumber).addEnrollment(Enrollment{semester,*courses[coursekey].get()});
	}
	noOfEnrollments++;
}
void StudentDb::printStudent()
{
	int matrikelNumber;

	std::cout<<std::endl<<"Enter Matrikel Number"<<std::endl;
	std::cin>>matrikelNumber;

	if(students.find(matrikelNumber) != students.end()) {
		students.find(matrikelNumber)->second.print();
//		students.at(matrikelNumber).printEnrollments();
	}
	else
		std::cout << "Student with the matrikelnummer is not present in the db" << std::endl;
}
void StudentDb::searchStudent()
{
	std::string sub_str;
	std::cout << "Enter your search string" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, sub_str);
	for(auto& student:students)
	{
		if((student.second.getFirstName().find(sub_str) !=std::string::npos) ||
				(student.second.getLastName().find(sub_str) !=std::string::npos))
		{
			std::cout << student.second.getMatrikelNumber() << ";" << student.second.getLastName() << ";"
					<< student.second.getFirstName() << std::endl;
		}
	}
}
void StudentDb::updateStudent()
{
	unsigned int matrikelnumber;
	std::cout << "Enter the Matrikel Number" << std::endl;
	std::cin >> matrikelnumber;
	if(students.find(matrikelnumber) != students.end())
	{
		students.find(matrikelnumber)->second.update();
	}
}

void StudentDb::write(std::ostream& out)
{

	if(courses.size() > 0)
	{
		out << courses.size()<<std::endl;
		for(auto& value:courses)
		{
			value.second->write(out);
		}
	}

	if(students.size() > 0)
	{
		out << students.size()<<std::endl;
		for(auto& value:students)
		{
			value.second.write(out);
		}
	}

	if(noOfEnrollments> 0)
	{
		out << noOfEnrollments<<std::endl;
		for(auto& student:students)
		{
			for(auto& enrollment:student.second.getEnrollments())
			{
				out<<student.second.getMatrikelNumber()<<";";
				enrollment.write(out);
			}
		}
	}

	out<<noOfEnrollments<<std::endl;
		if(noOfEnrollments > 0) {
			for(auto studentIterator:students) {
				for(auto enrollmentIterator:studentIterator.second.getEnrollments()) {
					out<<studentIterator.second.getMatrikelNumber()<<";";
					enrollmentIterator.write(out);
				}
			}
		}
}

void StudentDb::read(std::istream& in)
{
	students.clear();
	courses.clear();
	unsigned int noofcourses,noofstudents,noofenrollment;
	std::string line;
	std::getline(in,line);
	noofcourses=atoi(line.c_str());
	for(unsigned int i=0; i < noofcourses;i++)
	{
		std::getline(in,line);
		readCourses(line);
	}
	std::getline(in, line);
	noofstudents=atoi(line.c_str());
	for(unsigned int i=0; i < noofstudents;i++)
	{
		std::getline(in,line);
		readStudents(line);
	}
	std::getline(in, line);
	noofenrollment=atoi(line.c_str());
	for(unsigned int i=0; i < noofenrollment;i++)
	{
		std::getline(in,line);
		readEnrollments(line);
	}
}

StudentDb::~StudentDb()
{
	// TODO Auto-generated destructor stub
}

void StudentDb::readStudents(std::string &str)
{
	unsigned int matrikelNumber;
	std::string firstName;
	std::string lastName,dateofbirth;
	Poco::Data::Date dateOfBirth;
	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;
	int sempos,nextsempos;

	sempos=str.find(";");
	matrikelNumber=atoi(str.substr(0,sempos).c_str());

	nextsempos=str.find(";",sempos+1);
	lastName=str.substr(sempos+1, nextsempos-sempos+1);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	firstName=str.substr(sempos+1, nextsempos-sempos+1);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	dateofbirth=str.substr(sempos+1, nextsempos-sempos+1);

	dateOfBirth=Course::getDate(dateofbirth);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	street=str.substr(sempos+1, nextsempos-sempos+1);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	postalCode=atoi(str.substr(sempos+1, nextsempos-sempos+1).c_str());

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	cityName=str.substr(sempos+1, nextsempos-sempos+1);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	additionalInfo=str.substr(sempos+1, nextsempos-sempos+1);

	Address* address=new Address{street,postalCode,cityName,additionalInfo};
	Student student{firstName,lastName,dateOfBirth,*address};
	students.insert({student.getMatrikelNumber(),student});
}

void StudentDb::readCourses(std::string &str)
{
	unsigned int courseKey,dayofweek;
	std::string title;
	std::string major;
	float creditPoints;
	Course::course_t courseType;
	std::string coursetype;
	int sempos,nextsempos;
	sempos=str.find(";");
	coursetype=str.substr(0,sempos);
	if(coursetype == "W") courseType=Course::WEEKLYCOURSE;
	else if(coursetype == "B") courseType=Course::BLOCKCOURSE;

	nextsempos=str.find(";",sempos+1);
	courseKey=atoi(str.substr(sempos+1, nextsempos-sempos+1).c_str());

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	title=str.substr(sempos+1, nextsempos-sempos+1);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	major=str.substr(sempos+1, nextsempos-sempos+1);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	creditPoints=stof(str.substr(sempos+1, nextsempos-sempos+1));
	if(coursetype == "W")
	{
		Poco::DateTime::DaysOfWeek dayOfWeek;
		Poco::Data::Time startTime;
		Poco::Data::Time endTime;
		std::string starttime,endtime;
		sempos=nextsempos;
		nextsempos=str.find(";",sempos+1);
		dayofweek=atoi(str.substr(sempos+1, nextsempos-sempos+1).c_str());
		switch(dayofweek)
		{
		case 1:dayOfWeek=Poco::DateTime::MONDAY;break;
		case 2:dayOfWeek=Poco::DateTime::TUESDAY;break;
		case 3:dayOfWeek=Poco::DateTime::WEDNESDAY;break;
		case 4:dayOfWeek=Poco::DateTime::THURSDAY;break;
		case 5:dayOfWeek=Poco::DateTime::FRIDAY;break;
		case 6:dayOfWeek=Poco::DateTime::SATURDAY;break;
		}
		sempos=nextsempos;
		nextsempos=str.find(";",sempos+1);
		starttime=str.substr(sempos+1, nextsempos-sempos+1);
		startTime=Course::getTime(starttime);

		sempos=nextsempos;
		nextsempos=str.find(";",sempos+1);
		endtime=str.substr(sempos+1, nextsempos-sempos+1);
		endTime=Course::getTime(endtime);

		courses.insert({courseKey,std::unique_ptr<Course> (new WeeklyCourse{courseKey,title,major,
			creditPoints,courseType,dayOfWeek,
			startTime,endTime})});
		noOfCourses++;
	}
	else if(coursetype == "B")
	{
		Poco::Data::Date startDate,endDate;
		Poco::Data::Time startTime,endTime;
		std::string startdate,enddate,starttime,endtime;

		sempos=nextsempos;
		nextsempos=str.find(";",sempos+1);
		startdate=str.substr(sempos+1, nextsempos-sempos+1);
		startDate=Course::getDate(startdate);

		sempos=nextsempos;
		nextsempos=str.find(";",sempos+1);
		enddate=str.substr(sempos+1, nextsempos-sempos+1);
		endDate=Course::getDate(enddate);

		sempos=nextsempos;
		nextsempos=str.find(";",sempos+1);
		starttime=str.substr(sempos+1, nextsempos-sempos+1);
		startTime=Course::getTime(starttime);

		sempos=nextsempos;
		nextsempos=str.find(";",sempos+1);
		endtime=str.substr(sempos+1, nextsempos-sempos+1);
		endTime=Course::getTime(endtime);

		courses.insert({courseKey,std::unique_ptr<Course> (new BlockCourse{courseKey,title,major,
			creditPoints,courseType,startDate,endDate,startTime,endTime})});
			noOfCourses++;
	}
}

void StudentDb::readEnrollments(std::string &str)
{
	unsigned int matrikelNumber;
	unsigned int courseKey;
	float grade;
	std::string semester;
	int sempos,nextsempos;
	sempos=str.find(";");
	matrikelNumber=atoi(str.substr(0,sempos).c_str());

	nextsempos=str.find(";",sempos+1);
	courseKey=atoi(str.substr(sempos+1, nextsempos-sempos+1).c_str());

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	semester=str.substr(sempos+1, nextsempos-sempos+1);

	sempos=nextsempos;
	nextsempos=str.find(";",sempos+1);
	grade=stof(str.substr(sempos+1, nextsempos-sempos+1));

	if(!students.empty()) {
		students.at(matrikelNumber).addEnrollment(
				Enrollment{semester,grade,*courses[courseKey].get()}); // Adding enrollment
	}
}

std::string StudentDb::getInfoFromServer()
{
	Poco::Net::SocketAddress address("127.0.0.1", 3333);
	Poco::Net::StreamSocket socket(address);
	Poco::Net::SocketStream stream(socket);

	std::string line, jsonString;

	stream << "generate\r\n";
	stream.flush();

	std::getline(stream, line);
	jsonString=line;

	stream << "QUIT\r";
	stream.flush();

	socket.close();
	stream.close();

	return jsonString;
}

void StudentDb::addServerInfoToDb(std::string& info)
{
	std::cout << "received info: " << info << std::endl;
	std::string firstName,lastName,street,cityName,addInfo;
	unsigned short postalCode;
	int day,month,year;

	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result=parser.parse(info);
	Poco::JSON::Object::Ptr infoObject = result.extract<Poco::JSON::Object::Ptr>();
	Poco::Dynamic::Var nameVar= infoObject->get("name");
	Poco::JSON::Object::Ptr nameObj=nameVar.extract<Poco::JSON::Object::Ptr>();
	nameVar= nameObj->get("firstName");
	firstName=nameVar.toString();

	nameVar= nameObj->get("lastName");
	lastName=nameVar.toString();

	Poco::Dynamic::Var addressVar= infoObject->get("location");
	Poco::JSON::Object::Ptr addrObj=addressVar.extract<Poco::JSON::Object::Ptr>();
	addressVar= addrObj->get("city");
	cityName=addressVar.toString();

	addressVar= addrObj->get("street");
	street=addressVar.toString();

	addressVar = addrObj->get("state");
	addInfo = addressVar.toString();

	addressVar= addrObj->get("postCode");
	postalCode=std::stoi(addressVar.toString());

	Poco::Dynamic::Var dobVar= infoObject->get("dateOfBirth");
	Poco::JSON::Object::Ptr dobObj=dobVar.extract<Poco::JSON::Object::Ptr>();
	dobVar= dobObj->get("day");
	day=std::stoi(dobVar.toString());

	dobVar=dobObj->get("month");
	month=std::stoi(dobVar.toString());

	dobVar=dobObj->get("year");
	year=std::stoi(dobVar.toString());
	Address* address=new Address{street,postalCode,cityName,addInfo};
	Student student{firstName,lastName,Poco::Data::Date{year,month,day},*address};
	students.insert({student.getMatrikelNumber(),student});
	noOfStudents++;
}

void StudentDb::getServerData()
{
	int noOfAdditions=0;
	std::cout << "Enter number of students to add: ";
	std::cin>>noOfAdditions;
	for(int i=0; i < noOfAdditions;i++)
	{
		std::string info=getInfoFromServer();
		addServerInfoToDb(info);
	}
}
