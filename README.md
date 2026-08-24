# Soft Body Simulation

A soft-body physics simulation implemented in C++ with OpenGL.

The simulation represents a bunny-shaped object as a collection of particles
connected by spring-like strut forces. The object is affected by gravity,
spring forces, and friction, and is simulated inside a spherical boundary.

## Features

- Soft-body particle simulation
- Spring-like strut forces
- Friction between connected particles
- Gravity simulation
- Spherical boundary collision
- OBJ model loading
- OpenGL visualization
- Leap-Frog numerical integration

## Controls

- `S` / `s`: Increase or decrease spring strength
- `V` / `v`: Increase or decrease friction

## Credits

Some source files and the PBA framework were provided as course starter code
by Jerry Tessendorf.

My work focuses on implementing and modifying the soft-body simulation,
spring forces, friction, gravity, collision handling, and physics integration.

## Academic Context

This project was developed as part of a
Physically-Based Modeling and Animation course assignment.
