// Класс Figure
function Figure() {}

Figure.prototype.area = function() {
  throw new Error("This method should be implemented in subclass");
};

Figure.prototype.perimeter = function() {
  throw new Error("This method should be implemented in subclass");
};

// Класс Rectangle
function Rectangle(width, height) {
  Figure.call(this);
  this.width = width;
  this.height = height;
}

Rectangle.prototype = Object.create(Figure.prototype);
Rectangle.prototype.constructor = Rectangle;

Rectangle.prototype.area = function() {
  return this.width * this.height;
};

Rectangle.prototype.perimeter = function() {
  return 2 * (this.width + this.height);
};

// Класс Circle
function Circle(radius) {
  Figure.call(this);
  this.radius = radius;
}

Circle.prototype = Object.create(Figure.prototype);
Circle.prototype.constructor = Circle;

Circle.prototype.area = function() {
  return Math.PI * this.radius * this.radius;
};

Circle.prototype.perimeter = function() {
  return 2 * Math.PI * this.radius;
};
