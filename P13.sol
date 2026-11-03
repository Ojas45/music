// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

contract StudentData {

    // Structure to store student information
    struct Student {
        uint256 rollNo;
        string name;
        uint256 age;
        string course;
    }

    // Array of students
    Student[] public students;

    // Add student data
    function addStudent(
        uint256 _rollNo,
        string memory _name,
        uint256 _age,
        string memory _course
    ) public {
        students.push(
            Student(
                _rollNo,
                _name,
                _age,
                _course
            )
        );
    }

    // Get student data
    function getStudent(uint256 _index)
        public
        view
        returns (
            uint256,
            string memory,
            uint256,
            string memory
        )
    {
        Student memory student = students[_index];

        return (
            student.rollNo,
            student.name,
            student.age,
            student.course
        );
    }

    // Return total number of students
    function getStudentCount() public view returns (uint256) {
        return students.length;
    }

    // Fallback function
    fallback() external payable {
        // Executed when the contract receives
        // an unknown function call or unmatched data.
    }

    // Receive Ether directly
    receive() external payable {}
}