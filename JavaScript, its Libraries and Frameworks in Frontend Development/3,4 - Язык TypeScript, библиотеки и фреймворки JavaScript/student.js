// Определение класса Student
class Student {
  #name;
  #age;
  #grade;

  constructor(name, age, grade) {
    this.#name = name;
    this.#age = age;
    this.#grade = grade;
  }

  getName() {
    return this.#name;
  }

  setName(name) {
    this.#name = name;
  }

  getAge() {
    return this.#age;
  }

  setAge(age) {
    this.#age = age;
  }

  getGrade() {
    return this.#grade;
  }

  setGrade(grade) {
    this.#grade = grade;
  }
}
