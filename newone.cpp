
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include<bits/stdc++.h>

using namespace std;

// Abstract Base Class for Persons (Abstraction)
class Person {
protected:
    string name;
    int age;
public:
    Person(const string& n, int a) : name(n), age(a) {}
    virtual ~Person() {}

    string getName() const { return name; }
    int getAge() const { return age; }

    virtual void display() const = 0; // Pure virtual function (Abstract Method)
};

// Derived Class for Patients
class Patient : public Person {
private:
    string medicalRecord;
    int patientID;
public:
    Patient(const string& n, int a, const string& record, int id)
        : Person(n, a), medicalRecord(record), patientID(id) {}

    void setMedicalRecord(const string& record) { medicalRecord = record; }
    string getMedicalRecord() const { return medicalRecord; }
    int getPatientID() const { return patientID; }

    void display() const override {
        cout << "Patient: " << name << ", Age: " << age << ", Record: " << medicalRecord << ", ID: " << patientID << endl;
    }
};

// Derived Class for Doctors
class Doctor : public Person {
private:
    string specialty;
    int doctorID;
public:
    Doctor(const string& n, int a, const string& spec, int id)
        : Person(n, a), specialty(spec), doctorID(id) {}

    void setSpecialty(const string& spec) { specialty = spec; }
    string getSpecialty() const { return specialty; }
    int getDoctorID() const { return doctorID; }

    void display() const override {
        cout << "Doctor: " << name << ", Age: " << age << ", Specialty: " << specialty << ", ID: " << doctorID << endl;
    }
};

// Class for managing hospital operations (Composition)
class Hospital {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    int nextPatientID = 1;
    int nextDoctorID = 1;

public:
    // Add a new patient
    void addPatient(const string& name, int age, const string& record) {
        Patient newPatient(name, age, record, nextPatientID++);
        patients.push_back(newPatient);
        cout << "Patient added successfully." << endl;
    }

    // Add a new doctor
    void addDoctor(const string& name, int age, const string& specialty) {
        Doctor newDoctor(name, age, specialty, nextDoctorID++);
        doctors.push_back(newDoctor);
        cout << "Doctor added successfully." << endl;
    }

    // Assign doctor to a patient
    void assignDoctorToPatient(int patientID, int doctorID) {
        auto patientIt = find_if(patients.begin(), patients.end(),
                                 [patientID](const Patient& p) { return p.getPatientID() == patientID; });
        auto doctorIt = find_if(doctors.begin(), doctors.end(),
                                [doctorID](const Doctor& d) { return d.getDoctorID() == doctorID; });

        if (patientIt != patients.end() && doctorIt != doctors.end()) {
            cout << "Assigned doctor " << doctorIt->getName() << " to patient " << patientIt->getName() << "." << endl;
        } else {
            cout << "Doctor or Patient not found." << endl;
        }
    }

    // Display all patients
    void displayPatients() const {
        cout << "Patients List:" << endl;
        for (const auto& patient : patients) {
            patient.display();
        }
    }

    // Display all doctors
    void displayDoctors() const {
        cout << "Doctors List:" << endl;
        for (const auto& doctor : doctors) {
            doctor.display();
        }
    }

    // Demonstrating Polymorphism by displaying all persons
    void displayAllPersons() const {
        cout << "All Persons in Hospital:" << endl;
        for (const auto& patient : patients) {
            patient.display();
        }
        for (const auto& doctor : doctors) {
            doctor.display();
        }
    }
};


int main() {
    Hospital hospital;

    int choice;
    string name, specialty, medicalRecord;
    int age, patientID, doctorID;

    while (true) {
        cout << "\nHospital Management System Menu:\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Assign Doctor to Patient\n";
        cout << "4. Display Patients\n";
        cout << "5. Display Doctors\n";
        cout << "6. Display All Persons\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character left in the buffer

        switch (choice) {
            case 1:
                cout << "Enter Patient Name: ";
                getline(cin, name);
                cout << "Enter Patient Age: ";
                cin >> age;
                cin.ignore(); // Ignore newline character
                cout << "Enter Medical Record: ";
                getline(cin, medicalRecord);
                hospital.addPatient(name, age, medicalRecord);
                break;
            case 2:
                cout << "Enter Doctor Name: ";
                getline(cin, name);
                cout << "Enter Doctor Age: ";
                cin >> age;
                cin.ignore(); // Ignore newline character
                cout << "Enter Specialty: ";
                getline(cin, specialty);
                hospital.addDoctor(name, age, specialty);
                break;
            case 3:
                cout << "Enter Patient ID: ";
                cin >> patientID;
                cout << "Enter Doctor ID: ";
                cin >> doctorID;
                hospital.assignDoctorToPatient(patientID, doctorID);
                break;
            case 4:
                hospital.displayPatients();
                break;
            case 5:
                hospital.displayDoctors();
                break;
            case 6:
                hospital.displayAllPersons();
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
