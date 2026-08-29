# 42 C++ Modules

This repository contains my work for the C++ modules of the 42 Lausanne Common Core. The exercises progress from the foundations of C++98 to object-oriented design, generic programming and the Standard Template Library.

## Modules

| Module | Main concepts |
|---|---|
| [CPP00](cpp00) | Namespaces, classes, member functions, streams and basic object design |
| [CPP01](cpp01) | Memory allocation, references, pointers and object lifetime |
| [CPP02](cpp02) | Orthodox Canonical Form, operator overloading and fixed-point numbers |
| [CPP03](cpp03) | Inheritance and class hierarchies |
| [CPP04](cpp04) | Runtime polymorphism, abstract classes and interfaces |
| [CPP05](cpp05) | Exceptions and robust class design |
| [CPP06](cpp06) | Type conversion, C++ casts, serialization and RTTI |
| [CPP07](cpp07) | Function and class templates |
| [CPP08](cpp08) | STL containers, iterators and algorithms |

## What this work demonstrates

- Designing classes with clear ownership and lifecycle rules
- Applying inheritance and polymorphism without losing control of resources
- Selecting the correct cast for a conversion or runtime type check
- Writing reusable generic code with templates
- Working with STL containers, iterators and algorithms
- Debugging memory, compilation and object-lifetime problems

## Building the exercises

Each exercise is self-contained and includes its own Makefile. For example:

~~~bash
cd cpp08/ex00
make
./easyfind
~~~

The projects are compiled with strict warnings and, unless a subject states otherwise, target the C++98 standard.

## Context

These modules are part of my transition from low-level C and Unix programming toward larger C++ systems. That foundation is directly relevant to my goal of working on robotics software and the deployment of autonomous systems.
