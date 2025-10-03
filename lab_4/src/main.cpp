#include "../include/Shape.h"
#include "../include/Circle.h"
#include "../include/Rectangle.h"
#include "../include/Triangle.h"
#include "../include/Sphere.h"
#include "../include/Cube.h"
#include "../include/Cylinder.h"
#include <iostream>
#include <limits>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double getPositiveInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Error: Please enter a positive number!" << endl;
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

void displayMenu() {
    cout << "\n\tGEOMETRIC SHAPES MANAGER" << endl;
    cout << "1. Add Circle" << endl;
    cout << "2. Add Rectangle" << endl;
    cout << "3. Add Triangle" << endl;
    cout << "4. Add Sphere" << endl;
    cout << "5. Add Cube" << endl;
    cout << "6. Add Cylinder" << endl;
    cout << "7. Show All Shapes" << endl;
    cout << "8. Show Only 2D Shapes" << endl;
    cout << "9. Show Only 3D Shapes" << endl;
    cout << "10. Delete All Shapes" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";
}

void resizeShapeArray(Shape**& shapes, int& capacity, int count) {
    int newCapacity = capacity * 2;
    Shape** newShapes = new Shape*[newCapacity];
    
    for (int i = 0; i < count; ++i) {
        newShapes[i] = shapes[i];
    }
    
    delete[] shapes;
    shapes = newShapes;
    capacity = newCapacity;
}

void addCircle(Shape**& shapes, int& count, int& capacity) {
    if (count >= capacity) {
        resizeShapeArray(shapes, capacity, count);
    }
    
    double radius = getPositiveInput("Enter circle radius: ");
    shapes[count++] = new Circle(radius);
    cout << "Circle added successfully!" << endl;
}

void addRectangle(Shape**& shapes, int& count, int& capacity) {
    if (count >= capacity) {
        resizeShapeArray(shapes, capacity, count);
    }
    
    double width = getPositiveInput("Enter rectangle width: ");
    double height = getPositiveInput("Enter rectangle height: ");
    shapes[count++] = new RectangleShape(width, height);
    cout << "Rectangle added successfully!" << endl;
}

void addTriangle(Shape**& shapes, int& count, int& capacity) {
    if (count >= capacity) {
        resizeShapeArray(shapes, capacity, count);
    }
    
    double base = getPositiveInput("Enter triangle base: ");
    double height = getPositiveInput("Enter triangle height: ");
    shapes[count++] = new Triangle(base, height);
    cout << "Triangle added successfully!" << endl;
}

void addSphere(Shape**& shapes, int& count, int& capacity) {
    if (count >= capacity) {
        resizeShapeArray(shapes, capacity, count);
    }
    
    double radius = getPositiveInput("Enter sphere radius: ");
    shapes[count++] = new Sphere(radius);
    cout << "Sphere added successfully!" << endl;
}

void addCube(Shape**& shapes, int& count, int& capacity) {
    if (count >= capacity) {
        resizeShapeArray(shapes, capacity, count);
    }
    
    double side = getPositiveInput("Enter cube side length: ");
    shapes[count++] = new Cube(side);
    cout << "Cube added successfully!" << endl;
}

void addCylinder(Shape**& shapes, int& count, int& capacity) {
    if (count >= capacity) {
        resizeShapeArray(shapes, capacity, count);
    }
    
    double radius = getPositiveInput("Enter cylinder radius: ");
    double height = getPositiveInput("Enter cylinder height: ");
    shapes[count++] = new Cylinder(radius, height);
    cout << "Cylinder added successfully!" << endl;
}

void showAllShapes(Shape** shapes, int count) {
    if (count == 0) {
        cout << "No shapes created!" << endl;
        return;
    }
    
    cout << "\n\tALL SHAPES (" << count << ")" << endl;
    for (int i = 0; i < count; ++i) {
        cout << "\n--- Shape " << i + 1 << " ---" << endl;
        shapes[i]->print();
        cout << "Area: " << shapes[i]->area() << endl;
        cout << "Volume: " << shapes[i]->volume() << endl;
        cout << "Visualization:" << endl;
        shapes[i]->draw();
    }
}

void show2DShapes(Shape** shapes, int count) {
    cout << "\n\t2D SHAPES" << endl;
    bool found = false;
    
    for (int i = 0; i < count; ++i) {
        if (dynamic_cast<TwoDShape*>(shapes[i])) {
            found = true;
            cout << "\n--- Shape " << i + 1 << " ---" << endl;
            shapes[i]->print();
            cout << "Area: " << shapes[i]->area() << endl;
            cout << "Visualization:" << endl;
            shapes[i]->draw();
        }
    }
    
    if (!found) {
        cout << "No 2D shapes found!" << endl;
    }
}

void show3DShapes(Shape** shapes, int count) {
    cout << "\n\t3D SHAPES" << endl;
    bool found = false;
    
    for (int i = 0; i < count; ++i) {
        if (dynamic_cast<ThreeDShape*>(shapes[i])) {
            found = true;
            cout << "\n--- Shape " << i + 1 << " ---" << endl;
            shapes[i]->print();
            cout << "Surface Area: " << shapes[i]->area() << endl;
            cout << "Volume: " << shapes[i]->volume() << endl;
            cout << "Visualization:" << endl;
            shapes[i]->draw();
        }
    }
    
    if (!found) {
        cout << "No 3D shapes found!" << endl;
    }
}

void deleteAllShapes(Shape**& shapes, int& count, int& capacity) {
    for (int i = 0; i < count; ++i) {
        delete shapes[i];
    }
    delete[] shapes;
    
    capacity = 5;
    shapes = new Shape*[capacity];
    count = 0;
    cout << "All shapes deleted!" << endl;
}

int main() {
    Shape** shapes = new Shape*[5];
    int shapeCount = 0;
    int capacity = 5;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cout << "Invalid input! Please enter a number." << endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addCircle(shapes, shapeCount, capacity);
                break;
            case 2:
                addRectangle(shapes, shapeCount, capacity);
                break;
            case 3:
                addTriangle(shapes, shapeCount, capacity);
                break;
            case 4:
                addSphere(shapes, shapeCount, capacity);
                break;
            case 5:
                addCube(shapes, shapeCount, capacity);
                break;
            case 6:
                addCylinder(shapes, shapeCount, capacity);
                break;
            case 7:
                showAllShapes(shapes, shapeCount);
                break;
            case 8:
                show2DShapes(shapes, shapeCount);
                break;
            case 9:
                show3DShapes(shapes, shapeCount);
                break;
            case 10:
                deleteAllShapes(shapes, shapeCount, capacity);
                break;
            case 0:
                for (int i = 0; i < shapeCount; ++i) {
                    delete shapes[i];
                }
                delete[] shapes;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}